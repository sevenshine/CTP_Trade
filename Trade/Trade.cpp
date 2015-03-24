// Trade.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Trade.h"
#include <string.h>


map<string, CTrade*> CTrade::m_mapTrade;
map<string, CQuantInstrumentField*> CTrade::m_mapInstrument;
ITrade* CreateTrade(const char* lpAccount)
{
	map<string, CTrade*>::iterator iter;
	iter = CTrade::m_mapTrade.find(lpAccount);
	if (iter == CTrade::m_mapTrade.end())
	{
		CTrade* pTrade = new CTrade(lpAccount);
		CTrade::m_mapTrade[lpAccount] = pTrade;
		return pTrade;
	}
	else
	{
		return (ITrade*)iter->second;
	}
}

CTrade::CTrade(const char* lpAccount):m_strAccount(lpAccount)
{
	m_ulMaxLocalID = 0;
	m_pCTPTradeApi = NULL;
	m_pUstpTradeApi =NULL;
	m_bReady = false;
	m_pConfig = GetConfig();
	if (m_pConfig)
	{
		vector<CServerField> vecServer;
		m_pConfig->GetServer(vecServer);
		if (m_pConfig->GetServerType() == ctp)
		{
			//CTP初始化
			m_pCTPTradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi("");
			m_pCTPTradeSpi = new CFtdcTradeSpi(this);
			m_pCTPTradeApi->RegisterSpi(m_pCTPTradeSpi);
			m_pCTPTradeApi->SubscribePrivateTopic(THOST_TERT_QUICK);
			m_pCTPTradeApi->SubscribePrivateTopic(THOST_TERT_QUICK);

			//注册综合交易系统服务器地址
			//多个备用，通过config里读取传入
			for (int i=0;i<vecServer.size(); i++)
			{
				char* pAddr = vecServer[i].m_szTrade;
				m_pCTPTradeApi->RegisterFront(pAddr);		
			}
			m_pCTPTradeApi->Init();
		}
		else if (m_pConfig->GetServerType() == ustp)
		{
			//femas
			m_pUstpTradeApi = CUstpFtdcTraderApi::CreateFtdcTraderApi("");
			m_pUstpTradeSpi = new CUstpTradeSpi(this);
			m_pUstpTradeApi->SubscribePrivateTopic(USTP_TERT_QUICK); //pri info flow
			m_pUstpTradeApi->SubscribePublicTopic(USTP_TERT_QUICK);  //pub info flow
			m_pUstpTradeApi->RegisterSpi(m_pUstpTradeSpi);  //注册回调接口 UstpFtdcTraderApi.h
			for (int i=0;i<vecServer.size(); i++)
				m_pUstpTradeApi->RegisterFront(vecServer.at(i).m_szTrade);	
			m_pUstpTradeApi->Init();

		}
	
		m_pAccount = GetAccount(lpAccount);
		if (m_pAccount)
		{
			m_pAccount->SetCtpTradeApi(m_pCTPTradeApi);
			m_pAccount->SetUstpTradeApi(m_pUstpTradeApi);
		}
	}	
}


CTrade::~CTrade(void)
{
	if (m_pCTPTradeApi)
	{
		m_pCTPTradeApi->Release();
		m_pCTPTradeApi = NULL;
	}

	if (m_pCTPTradeSpi)
	{
		delete m_pCTPTradeSpi;
		m_pCTPTradeSpi = NULL;
	}

	if (m_pUstpTradeApi)
	{
		m_pUstpTradeApi->RegisterSpi(NULL);
		m_pUstpTradeApi->Release();
		m_pUstpTradeApi = NULL;
	}

	if (m_pUstpTradeSpi)
	{
		delete m_pUstpTradeSpi;
		m_pUstpTradeSpi = NULL;
	}
}

void CTrade::Release()
{
	delete this;
}

void CTrade::Login()
{
	if (m_pAccount)
	{
		m_pAccount->OnConnected();
	}
}

void CTrade::OnLogined()
{
	if (m_pAccount)
	{
		m_pAccount->OnLogined();

		if (m_pUstpTradeApi)
		{
			CUstpFtdcQryUserInvestorField req;
			memset(&req, 0 ,sizeof(req));
			sprintf(req.BrokerID,"%s", m_pConfig->GetBrokerId());
			strcpy(req.UserID, m_strAccount.c_str());
			m_pUstpTradeApi->ReqQryUserInvestor(&req,1);
		}
	}
}

void CTrade::OnDisConnected()
{
	if (m_pAccount)
	{
		m_pAccount->OnDisconnected();
	}
}

unsigned long CTrade::ReqOrderInsert( const char* pIntrument,double dLimitPrice, int nOrderNum, TQuantBSDirection bs, TQuantOpenFlag of,TQuantHedgeType ht, TQuantPriceOrderType ordertype ,TQuantTimeConditionType tcType)
{
	if(m_pCTPTradeApi)
	{
		//报单结构体
		CThostFtdcInputOrderField reqField;
		memset(&reqField,0,sizeof(reqField));
		strncpy_s(reqField.InstrumentID, pIntrument, sizeof(reqField.InstrumentID));
		sprintf(reqField.OrderRef,"%ld", GetOrderID());
		sprintf(reqField.BrokerID,"%s" ,m_pConfig->GetBrokerId());
		strcpy(reqField.UserID, m_strAccount.c_str());
		strcpy(reqField.InvestorID, m_strAccount.c_str());
		reqField.CombHedgeFlag[0] = ht;
		//买卖
		reqField.Direction = bs;
		reqField.CombOffsetFlag[0] = of;

		//数量
		reqField.VolumeTotalOriginal = nOrderNum;
		///成交量类型：任何数量
		reqField.OrderPriceType = ordertype;
		reqField.VolumeCondition = THOST_FTDC_VC_AV;
		/// 最小成交量：1
		reqField.MinVolume = 1;
		/// 强平原因：非强平
		reqField.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
		/// 自动挂起标志：否
		reqField.IsAutoSuspend = 0;
		///用户强评标志：否
		reqField.UserForceClose = 0;
		reqField.ContingentCondition = THOST_FTDC_CC_Immediately;	
		///有效期类型类型：立即完成，否则撤销
		reqField.TimeCondition = tcType;
		reqField.LimitPrice = dLimitPrice;

		int ret = m_pCTPTradeApi->ReqOrderInsert(&reqField,0);
		if (ret != 0)
			return ret;
		else
			return atol(reqField.OrderRef);
	}

	if (m_pUstpTradeApi)
	{
		CUstpFtdcInputOrderField req;
		memset(&req, 0, sizeof(req));

		req.OffsetFlag = of;
		req.Direction = bs;
		req.LimitPrice = dLimitPrice;
		req.Volume = nOrderNum;

		sprintf(req.BrokerID,"%s", m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strInvestID.c_str());
		strcpy(req.UserID,m_strAccount.c_str());
		strcpy(req.InstrumentID, pIntrument);
		strcpy(req.ExchangeID, "CFFEX");
		sprintf(req.UserOrderLocalID, "%012d", GetOrderID());

		req.OrderPriceType = ordertype;
		req.HedgeFlag = ht; 
		req.TimeCondition = tcType;
		req.VolumeCondition = USTP_FTDC_VC_AV;
		req.MinVolume = 1;
		req.IsAutoSuspend = 0;
		req.ForceCloseReason = USTP_FTDC_FCR_NotForceClose;

		int ret = m_pUstpTradeApi->ReqOrderInsert(&req, 0);
		if (ret != 0)
			return ret;
		else
			return atol(req.UserOrderLocalID);
	}
	return -1;
}

unsigned long CTrade::ReqOrderDelete( unsigned long ulOrderID ,const char* pOrderSysID, const char* pInstrumengID)
{
	if(m_pCTPTradeApi)
	{
		CThostFtdcInputOrderActionField reqField;
		memset(&reqField, 0, sizeof(CThostFtdcInputOrderActionField));
		reqField.OrderActionRef =  GetOrderID();
		sprintf(reqField.BrokerID,"%s" ,m_pConfig->GetBrokerId());
		strcpy(reqField.UserID, m_strAccount.c_str());
		strcpy(reqField.InvestorID, m_strAccount.c_str());
		sprintf(reqField.OrderRef,"%ld", ulOrderID);
		strcpy(reqField.OrderSysID, pOrderSysID);
		strcpy(reqField.ExchangeID, pInstrumengID);
		reqField.ActionFlag = THOST_FTDC_AF_Delete;
		reqField.OrderActionRef = GetOrderID();
		int ret = m_pCTPTradeApi->ReqOrderAction(&reqField,m_ulMaxLocalID);		
		if (ret != 0)
			return ret;
	}
	if (m_pUstpTradeApi)
	{
		CUstpFtdcOrderActionField req;
		memset(&req, 0, sizeof(req));
		strcpy(req.UserID,m_strAccount.c_str());
		sprintf(req.BrokerID,"%s" ,m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strInvestID.c_str());
		sprintf(req.UserOrderLocalID, "%012d",ulOrderID);  // complained access violation!!
		sprintf(req.OrderSysID,"%s",pOrderSysID);
		strcpy(req.ExchangeID, pInstrumengID);
		sprintf(req.UserOrderActionLocalID, "%012d", GetOrderID());
		req.ActionFlag = USTP_FTDC_AF_Delete;
		int ret = m_pUstpTradeApi->ReqOrderAction(&req, m_ulMaxLocalID);
		if (ret != 0)
			return ret;
	}
	return ulOrderID;
}



unsigned long CTrade::GetOrderID()
{
	m_mutex.lock();
	unsigned long orderid = ++m_ulMaxLocalID;
	m_mutex.unlock();
	return orderid;
}

void CTrade::RegTradeStatus( OnStatus fStatus, long lHandle )
{
	if (fStatus == NULL)
	{
		return;
	}
	map<long, OnStatus>::iterator iter;
	iter = m_mapFuncStatusRsp.find(lHandle);
	if (iter != m_mapFuncStatusRsp.end())
	{
		if (iter->second == fStatus)
		{
			return ;
		}
		iter->second = fStatus;
	}
	m_mapFuncStatusRsp[lHandle] = fStatus;
}

void CTrade::OnRspStatus( ETradeStatus status )
{
	map<long, OnStatus>::iterator iter = m_mapFuncStatusRsp.begin();
	while(iter != m_mapFuncStatusRsp.end())
	{
		iter->second(status,iter->first);
		iter++;
	}
}

//遍历m_mapFuncOrderRsp 将没出现过的OnRecvOrder放到map容器里
void CTrade::RegOrderRsp( OnRecvOrder fOrderRsp , long lHandle)
{
	if (fOrderRsp == NULL)
	{
		return;
	}
	map<long, OnRecvOrder>::iterator iter;
	iter = m_mapFuncOrderRsp.find(lHandle);
	if (iter != m_mapFuncOrderRsp.end())
	{
		if (iter->second == fOrderRsp)
		{
			return ;
		}
		iter->second = fOrderRsp;
	}
	m_mapFuncOrderRsp[lHandle] = fOrderRsp;
}

void CTrade::OnRtnOrder( CQuantOrderField* pOrder )
{
	map<long, OnRecvOrder>::iterator iter = m_mapFuncOrderRsp.begin();
	while(iter != m_mapFuncOrderRsp.end())
	{
		iter->second(pOrder,iter->first);
		iter++;
	}
}

void CTrade::RegTradeRsp( OnRecvTrade fOrderRsp, long lHandle )
{
	if (fOrderRsp == NULL)
	{
		return;
	}
	map<long, OnRecvTrade>::iterator iter;
	iter = m_mapFuncTradeRsp.find(lHandle);
	if (iter != m_mapFuncTradeRsp.end())
	{
		if (iter->second == fOrderRsp)
		{
			return ;
		}
		iter->second = fOrderRsp;
	}
	m_mapFuncTradeRsp[lHandle] = fOrderRsp;	
}

void CTrade::OnRtnTrade( CQuantTradeField* pTrade )
{
	map<long, OnRecvTrade>::iterator iter = m_mapFuncTradeRsp.begin();
	while(iter != m_mapFuncTradeRsp.end())
	{
		iter->second(pTrade,iter->first);
		iter++;
	}

	//计算持仓、资金
//	UpdatePosition(pTrade);
//	UpdateAccountFund(pTrade);
}

void CTrade::OnFundRsp( CQuantInvestorAccountField* pRspData )
{
	if (pRspData)
		memcpy(&m_Fund, pRspData, sizeof(CQuantInvestorAccountField));

	//通知到strategy

}

void CTrade::ReqFund()
{
	if (m_pCTPTradeApi)
	{
		CThostFtdcQryTradingAccountField req;
		memset(&req, 0, sizeof(req));
		sprintf(req.BrokerID, "%s", m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strAccount.c_str());
		m_pCTPTradeApi->ReqQryTradingAccount(&req, 0);
	}
	if (m_pUstpTradeApi)
	{
		CUstpFtdcQryInvestorAccountField req;
		memset(&req, 0, sizeof(req));
		sprintf(req.BrokerID, "%s", m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strInvestID.c_str());
		m_pUstpTradeApi->ReqQryInvestorAccount(&req, 0);
	}
}

void CTrade::ReqInstrument()
{
	if (m_pCTPTradeApi)
	{
		CThostFtdcQryInstrumentField req;
		memset(&req, 0, sizeof(req));
		m_pCTPTradeApi->ReqQryInstrument(&req, 0);
	}
	if (m_pUstpTradeApi)
	{
		CUstpFtdcQryInstrumentField req;
		memset(&req, 0, sizeof(req));
		m_pUstpTradeApi->ReqQryInstrument(&req, 0);
	}
}

void CTrade::OnInstrumentRsp( CQuantInstrumentField* pRspData )
{
	if (pRspData)
	{
		map<string,CQuantInstrumentField*>::iterator iter;
		iter = m_mapInstrument.find(pRspData->InstrumentID);
		if (iter == m_mapInstrument.end())
		{
			CQuantInstrumentField* pData = new CQuantInstrumentField;
			memcpy(pData, pRspData, sizeof(CQuantInstrumentField));
			m_mapInstrument[pRspData->InstrumentID] = pData;
		}
	}	
}

void CTrade::ReqFee()
{
	if (m_pCTPTradeApi)
	{
		CThostFtdcQryInstrumentCommissionRateField req;
		memset(&req, 0, sizeof(req));
		sprintf(req.BrokerID, "%s", m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strAccount.c_str());
		m_pCTPTradeApi->ReqQryInstrumentCommissionRate(&req, 0);
	}
	if (m_pUstpTradeApi)
	{
		CUstpFtdcQryInvestorFeeField req;
		memset(&req, 0, sizeof(req));
		sprintf(req.BrokerID, "%s", m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strInvestID.c_str());
		m_pUstpTradeApi->ReqQryInvestorFee(&req, 0);
	}

}

void CTrade::OnFeeRsp( CQuantFeeField* pRspData )
{
	if (pRspData)
	{
		map<string,CQuantFeeField*>::iterator iter;
		iter = m_mapFee.find(pRspData->InstrumentID);
		if (iter == m_mapFee.end())
		{
			CQuantFeeField* pData = new CQuantFeeField;
			memcpy(pData, pRspData, sizeof(CQuantFeeField));
			m_mapFee[pRspData->InstrumentID] = pData;
		}
	}
}

void CTrade::ReqMargin()
{
	if (m_pCTPTradeApi)
	{
		CThostFtdcQryInstrumentMarginRateField req;
		memset(&req, 0, sizeof(req));
		sprintf(req.BrokerID, "%s", m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strAccount.c_str());
		//req.HedgeFlag = THOST_FTDC_HF_Arbitrage;
		m_pCTPTradeApi->ReqQryInstrumentMarginRate(&req, 0);
	}
	if (m_pUstpTradeApi)
	{
		CUstpFtdcQryInvestorMarginField req;
		memset(&req, 0, sizeof(req));
		sprintf(req.BrokerID, "%s", m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strInvestID.c_str());
		strcpy(req.UserID,m_strAccount.c_str());
		m_pUstpTradeApi->ReqQryInvestorMargin(&req, 0);
	}
}

void CTrade::OnMarginRsp( CQuantMarginField* pRspData )
{
	if (pRspData)
	{
		map<string,CQuantMarginField*>::iterator iter;
		iter = m_mapMatgin.find(pRspData->InstrumentID);
		if (iter == m_mapMatgin.end())
		{
			CQuantMarginField* pData = new CQuantMarginField;
			memcpy(pData, pRspData, sizeof(CQuantMarginField));
			m_mapMatgin[pRspData->InstrumentID] = pData;
		}
	}
}

void CTrade::ReqPosition()
{
	if (m_pCTPTradeApi)
	{
		CThostFtdcQryInvestorPositionField req;
		memset(&req, 0, sizeof(req));
		sprintf(req.BrokerID, "%s", m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strAccount.c_str());
		m_pCTPTradeApi->ReqQryInvestorPosition(&req, 0);
	}
	if (m_pUstpTradeApi)
	{
		CUstpFtdcQryInvestorPositionField req;
		memset(&req, 0, sizeof(req));
		sprintf(req.BrokerID, "%s", m_pConfig->GetBrokerId());
		strcpy(req.InvestorID, m_strAccount.c_str());
		strcpy(req.UserID,m_strInvestID.c_str());
		m_pUstpTradeApi->ReqQryInvestorPosition(&req, 0);
	}
}

void CTrade::OnPositionRsp( CQuantPositionField* pRspData )
{
	if (pRspData->Position > 0)
	{
		CQuantPositionField* pData = new CQuantPositionField;
		memcpy(pData, pRspData, sizeof(CQuantPositionField));
		m_mapPosition.insert(pair<string,CQuantPositionField*>(pRspData->InstrumentID, pData));
	}	
}

void CTrade::UpdatePosition( CQuantTradeField* pTrade )
{
	double dBalance = 0.0;
	if (pTrade)
	{
		multimap<string,CQuantPositionField*>::iterator iterPosition;
		iterPosition = m_mapPosition.find(pTrade->InstrumentID);
		if (iterPosition != m_mapPosition.end())
		{
			int count = m_mapPosition.count(pTrade->InstrumentID);
			for (int i=0;i<count;i++,iterPosition++)
			{
				CQuantPositionField* position = iterPosition->second;
				if (position)
				{
					if (pTrade->OffsetFlag == QUANT_OF_Open)
					{
						if (pTrade->Direction ==  position->Direction)
						{		
							//持仓数量
							dBalance += (double)position->Position * position->AvePrice;
							position->Position += pTrade->Volume;

							//成交均价
							dBalance += (double)pTrade->Volume * pTrade->Price;
							position->AvePrice = dBalance / (double)position->Position;

							//保证金
							CQuantMarginField* pMargin = NULL;
							map<string,CQuantMarginField*>::iterator iter = m_mapMatgin.find(pTrade->InstrumentID);
							if (iter != m_mapMatgin.end())
								pMargin = iter->second;
							CQuantInstrumentField* pInstrument = NULL;
							map<string,CQuantInstrumentField*>::iterator iter3 = m_mapInstrument.find(pTrade->InstrumentID);
							if (iter3 != m_mapInstrument.end())
								pInstrument = iter3->second;

							if (pMargin)
							{
								if (pTrade->Direction == QUANT_D_Buy)
									position->FrozenMargin = pMargin->LongMarginRate*position->Position*position->AvePrice*pInstrument->VolumeMultiple;
								else
									position->FrozenMargin = pMargin->ShortMarginRate*position->Position*position->AvePrice*pInstrument->VolumeMultiple;
							}
							
						}

					}
					else
					{
						if (pTrade->Direction !=  position->Direction)
						{
							//持仓
							position->Position -= pTrade->Volume;

							if (position->Position <= 0)
							{
								delete position;
								m_mapPosition.erase(iterPosition);
								return;
							}

							//保证金
							CQuantMarginField* pMargin = NULL;
							map<string,CQuantMarginField*>::iterator iter = m_mapMatgin.find(pTrade->InstrumentID);
							if (iter != m_mapMatgin.end())
								pMargin = iter->second;
							CQuantInstrumentField* pInstrument = NULL;
							map<string,CQuantInstrumentField*>::iterator iter3 = m_mapInstrument.find(pTrade->InstrumentID);
							if (iter3 != m_mapInstrument.end())
								pInstrument = iter3->second;

							if (pMargin)
							{
								if (pTrade->Direction == QUANT_D_Buy)
									position->FrozenMargin = pMargin->LongMarginRate*position->Position*position->AvePrice*pInstrument->VolumeMultiple;
								else
									position->FrozenMargin = pMargin->ShortMarginRate*position->Position*position->AvePrice*pInstrument->VolumeMultiple;
							}
							
						}					
					}	
				}
				
			}
		}
		else
		{
			CQuantPositionField* pInsert = new CQuantPositionField;
			memset(pInsert, 0, sizeof(CQuantPositionField));
			strcpy(pInsert->InstrumentID, pTrade->InstrumentID);
			pInsert->Position = pTrade->Volume;
			pInsert->AvePrice = pTrade->Price;
			pInsert->Direction = pTrade->Direction;		

			//保证金
			CQuantMarginField* pMargin = NULL;
			map<string,CQuantMarginField*>::iterator iter = m_mapMatgin.find(pTrade->InstrumentID);
			if (iter != m_mapMatgin.end())
				pMargin = iter->second;
			if (pMargin)
			{
				CQuantInstrumentField* pInstrument = NULL;
				map<string,CQuantInstrumentField*>::iterator iter3 = m_mapInstrument.find(pTrade->InstrumentID);
				if (iter3 != m_mapInstrument.end())
					pInstrument = iter3->second;

				if(pMargin)
				{
					if (pTrade->Direction == QUANT_D_Buy)
						pInsert->FrozenMargin = pMargin->LongMarginRate*pInsert->Position*pInsert->AvePrice*pInstrument->VolumeMultiple;
					else
						pInsert->FrozenMargin = pMargin->ShortMarginRate*pInsert->Position*pInsert->AvePrice*pInstrument->VolumeMultiple;
				}
				
			}
			m_mapPosition.insert(pair<string,CQuantPositionField*>(pTrade->InstrumentID,pInsert));
		}		
	}	
}

void CTrade::UpdateAccountFund( CQuantTradeField* pTrade )
{
	//冻结保证金、手续费、
	if (pTrade)
	{
		CQuantMarginField* pMargin = NULL;
		map<string,CQuantMarginField*>::iterator iter = m_mapMatgin.find(pTrade->InstrumentID);
		if (iter != m_mapMatgin.end())
			pMargin = iter->second;
		CQuantFeeField* pFee = NULL;
		map<string,CQuantFeeField*>::iterator iter2 = m_mapFee.find(pTrade->InstrumentID);
		if (iter2 != m_mapFee.end())
			pFee = iter2->second;
		CQuantInstrumentField* pInstrument = NULL;
		map<string,CQuantInstrumentField*>::iterator iter3 = m_mapInstrument.find(pTrade->InstrumentID);
		if (iter3 != m_mapInstrument.end())
			pInstrument = iter3->second;
		if (pTrade->OffsetFlag == QUANT_OF_Open)
		{
			//手续费
			if (pFee )				
				m_Fund.Fee += pFee->OpenFeeAmt*pTrade->Volume + pTrade->Volume*pTrade->Price*pInstrument->VolumeMultiple*pFee->OpenFeeRate;
			//保证金
			if (pMargin)
			{
				if (pTrade->Direction == QUANT_D_Buy)
					m_Fund.Margin += pMargin->LongMarginRate*pTrade->Volume*pTrade->Price*pInstrument->VolumeMultiple;
				else
					m_Fund.Margin += pMargin->ShortMarginRate*pTrade->Volume*pTrade->Price*pInstrument->VolumeMultiple;
			}	
		}
		else
		{
			//手续费
			if (pFee )	
				m_Fund.Fee += pFee->OffsetFeeAmt*pTrade->Volume + pTrade->Volume*pTrade->Price*pInstrument->VolumeMultiple*pFee->OffsetFeeRate;
			//平仓盈亏
			//保证金
			multimap<string,CQuantPositionField*>::iterator iterPosition;
			iterPosition = m_mapPosition.find(pTrade->InstrumentID);
			if (iterPosition != m_mapPosition.end())
			{
				int count = m_mapPosition.count(pTrade->InstrumentID);
				for (int i=0;i<count;i++,iterPosition++)
				{
					CQuantPositionField* position = iterPosition->second;
					if (position)
					{
						if (pTrade->Direction !=  position->Direction)
						{
							if (pInstrument)
							{
								//保证金 平仓盈亏
								if (pTrade->Direction == QUANT_D_Buy)
								{
									if (pMargin)
										m_Fund.Margin -= pMargin->LongMarginRate*pTrade->Volume*position->AvePrice*pInstrument->VolumeMultiple;
									m_Fund.CloseProfit += (position->AvePrice - pTrade->Price  ) * pTrade->Volume * pInstrument->VolumeMultiple;
								}
								else
								{
									if (pMargin)
										m_Fund.Margin -= pMargin->ShortMarginRate*pTrade->Volume*position->AvePrice*pInstrument->VolumeMultiple;
									m_Fund.CloseProfit += (pTrade->Price - position->AvePrice ) * pTrade->Volume * pInstrument->VolumeMultiple;
								}		
							}												
						}
					}
				}
			}
		}
	}
}

CQuantMarginField* CTrade::GetMarginField( const char* lpInstrumentID )
{
	map<string,CQuantMarginField*>::iterator iter;
	iter = m_mapMatgin.find(lpInstrumentID);
	if (iter != m_mapMatgin.end())
	{
		return iter->second;
	}
	return NULL;
}

CQuantFeeField* CTrade::GetFeeField( const char* lpInstrumentID )
{
	map<string,CQuantFeeField*>::iterator iter;
	iter = m_mapFee.find(lpInstrumentID);
	if (iter != m_mapFee.end())
	{
		return iter->second;
	}
	return NULL;
}

CQuantInstrumentField* CTrade::GetInstrument( const char* lpInstrumentID )
{
	if (m_mapInstrument.size() > 0)
	{
		map<string,CQuantInstrumentField*>::iterator iter;
		iter = m_mapInstrument.find((string)lpInstrumentID);
		if (iter != m_mapInstrument.end())
		{
			return iter->second;
		}
	}
	
	return NULL;
}

void CTrade::SetMaxOrderID( unsigned long ulMaxOrderID )
{
	m_ulMaxLocalID = ulMaxOrderID;
}






