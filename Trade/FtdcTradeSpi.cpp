#include "StdAfx.h"
#include "FtdcTradeSpi.h"
#include "..\log\c-log-master\src\log.h"
#include "Trade.h"
#include "QuantStruct.h"



CFtdcTradeSpi::CFtdcTradeSpi(CTrade* pTrade)
{
	m_pTrade = pTrade;
}


CFtdcTradeSpi::~CFtdcTradeSpi(void)
{
}

void CFtdcTradeSpi::OnFrontConnected()
{
	if (m_pTrade)
	{
		m_pTrade->Login();
	}
	LOG_NOTICE("ctp trade connected");
}

void CFtdcTradeSpi::OnFrontDisconnected( int nReason )
{
	if (m_pTrade)
	{
		m_pTrade->OnDisConnected();
	}
	LOG_ERROR("ctp trade disconnected, reason: %d", nReason);
}

void CFtdcTradeSpi::OnRspUserLogin( CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (pRspInfo)
	{
		//suc
		if (pRspInfo->ErrorID == 0)
		{
			m_pTrade->SetMaxOrderID(atol(pRspUserLogin->MaxOrderRef));
			//结算单确认
			CThostFtdcSettlementInfoConfirmField req;
			memset(&req, 0, sizeof(req));
			strcpy(req.BrokerID, pRspUserLogin->BrokerID);
			strcpy(req.InvestorID, m_pTrade->GetAccountID().c_str());
			m_pTrade->GetCTPTradeApi()->ReqSettlementInfoConfirm(&req, 0);

			LOG_NOTICE("ctp trade login suc, %s", pRspUserLogin->UserID);
		}
		else
		{
			LOG_ERROR("ctp trade login failed, %s, ErrMsg: %s", pRspUserLogin->UserID, pRspInfo->ErrorMsg);
		}
	}
}

void CFtdcTradeSpi::OnRspUserLogout( CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{

}


void CFtdcTradeSpi::OnRspOrderInsert( CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	//printf("OnRspOrderInsert: %s\r\n", pInputOrder->OrderRef);
	CQuantOrderField order;
	memset(&order,0,sizeof(order));
	strcpy(order.BrokerID,pInputOrder->BrokerID);
	order.Direction = pInputOrder->Direction;
	order.HedgeFlag = pInputOrder->CombHedgeFlag[0];
	strcpy(order.InstrumentID, pInputOrder->InstrumentID);
	strcpy(order.InvestorID, pInputOrder->InvestorID);
	order.LimitPrice = pInputOrder->LimitPrice;
	order.OffsetFlag = pInputOrder->CombOffsetFlag[0];
	order.OrderRef = atol(pInputOrder->OrderRef);
	order.StopPrice = pInputOrder->StopPrice;
	strcpy(order.UserID, pInputOrder->UserID);
	order.VolumeTotalOriginal = pInputOrder->VolumeTotalOriginal;
	strcpy(order.StatusMsg, pRspInfo->ErrorMsg);
	order.ErrorID = pRspInfo->ErrorID;
	if (m_pTrade)
	{
		m_pTrade->OnRtnOrder(&order);
	}
}

void CFtdcTradeSpi::OnRspOrderAction( CThostFtdcInputOrderActionField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	CQuantOrderField order;
	memset(&order,0,sizeof(order));
	strcpy(order.BrokerID,pInputOrder->BrokerID);
	strcpy(order.InstrumentID, pInputOrder->InstrumentID);
	strcpy(order.InvestorID, pInputOrder->InvestorID);
	order.LimitPrice = pInputOrder->LimitPrice;
	order.OrderRef = atol(pInputOrder->OrderRef);
	strcpy(order.UserID, pInputOrder->UserID);
	strcpy(order.StatusMsg, pRspInfo->ErrorMsg);
	order.ErrorID = pRspInfo->ErrorID;
	if (m_pTrade)
	{
		m_pTrade->OnRtnOrder(&order);
	}
}

void CFtdcTradeSpi::OnRspError( CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{

}

void CFtdcTradeSpi::OnRtnOrder( CThostFtdcOrderField *pOrder )
{
	//printf("OnRtnOrder: %s, %c, %s \r\n", pOrder->OrderRef, pOrder->OrderStatus,pOrder->StatusMsg);
	CQuantOrderField order;
	memset(&order,0,sizeof(order));
	strcpy(order.BrokerID,pOrder->BrokerID);
	strcpy(order.CancelTime,pOrder->CancelTime);
	order.Direction = pOrder->Direction;
	order.HedgeFlag = pOrder->CombHedgeFlag[0];
	strcpy(order.InsertDate, pOrder->InsertDate);
	strcpy(order.InsertTime, pOrder->InsertTime);
	strcpy(order.InstrumentID, pOrder->InstrumentID);
	strcpy(order.InvestorID, pOrder->InvestorID);
	order.LimitPrice = pOrder->LimitPrice;
	order.OffsetFlag = pOrder->CombOffsetFlag[0];
	order.OrderRef = atol(pOrder->OrderRef);
	order.OrderStatus = pOrder->OrderStatus;
	if (pOrder->OrderStatus  == THOST_FTDC_OST_Unknown)
		order.OrderStatus = QUANT_OST_NoTradeQueueing;
	strcpy(order.OrderSysID, pOrder->OrderSysID);
	strcpy(order.StatusMsg, pOrder->StatusMsg);
	order.StopPrice = pOrder->StopPrice;
	strcpy(order.TradingDay, pOrder->TradingDay);
	strcpy(order.UpdateTime, pOrder->UpdateTime);
	strcpy(order.UserID, pOrder->UserID);
	order.VolumeTotalOriginal = pOrder->VolumeTotalOriginal;
	order.VolumeTraded = pOrder->VolumeTraded;
	order.ErrorID = 0;
	if (m_pTrade)
	{
		m_pTrade->OnRtnOrder(&order);
	}
}

void CFtdcTradeSpi::OnRtnTrade( CThostFtdcTradeField *pTrade )
{
	CQuantTradeField trade;
	memset(&trade, 0, sizeof(trade));
	strcpy(trade.BrokerID,pTrade->BrokerID);
	trade.Direction = pTrade->Direction;
	trade.HedgeFlag = pTrade->HedgeFlag;
	strcpy(trade.TradeDate, pTrade->TradeDate);
	strcpy(trade.TradeTime, pTrade->TradeTime);
	strcpy(trade.InstrumentID, pTrade->InstrumentID);
	strcpy(trade.InvestorID, pTrade->InvestorID);
	trade.OrderRef = atol(pTrade->OrderRef);
	trade.OffsetFlag = pTrade->OffsetFlag;
	strcpy(trade.OrderSysID, pTrade->OrderSysID);
	strcpy(trade.TradeID, pTrade->TradeID);
	trade.Price = pTrade->Price;
	strcpy(trade.TradingDay, pTrade->TradingDay);
	strcpy(trade.UserID, pTrade->UserID);
	trade.Volume = pTrade->Volume;
	
	if (m_pTrade)
	{
		m_pTrade->OnRtnTrade(&trade);
	}
}

void CFtdcTradeSpi::OnRspQryTradingAccount( CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade)
	{
		CQuantInvestorAccountField data;
		memset(&data, 0, sizeof(CQuantInvestorAccountField));
		strcpy(data.AccountID,pTradingAccount->AccountID);
		data.PreBalance = pTradingAccount->PreBalance;
		data.Available = pTradingAccount->Available;
		data.CloseProfit = pTradingAccount->CloseProfit;
		data.Deposit = pTradingAccount->Deposit;
		data.Withdraw = pTradingAccount->Withdraw;
		data.Fee = pTradingAccount->Commission;
		data.DynamicRights = pTradingAccount->DeliveryMargin;
		data.FrozenFee = pTradingAccount->FrozenCommission;
		data.FrozenMargin = pTradingAccount->FrozenMargin;
		data.Margin = pTradingAccount->CurrMargin;
		data.PositionProfit = pTradingAccount->PositionProfit;
		m_pTrade->OnFundRsp(&data);

	}
	//保证金
	if (bIsLast)
	{
		Sleep(1000);
		m_pTrade->OnRspStatus(AccountFundRsp);
		m_pTrade->ReqMargin();
	}
}


void CFtdcTradeSpi::OnRspQryInvestorPosition( CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade && pInvestorPosition)
	{
		CQuantPositionField data;
		memset(&data,0,sizeof(data));
		data.Direction = pInvestorPosition->PosiDirection-'2';
		data.HedgeFlag = pInvestorPosition->HedgeFlag;
		strcpy(data.InstrumentID, pInvestorPosition->InstrumentID);
		strcpy(data.InvestorID,pInvestorPosition->InvestorID);
		data.Position = pInvestorPosition->Position;
		data.PositionCost = pInvestorPosition->PositionCost;
		data.UsedMargin = pInvestorPosition->UseMargin;
		data.YdPosition = pInvestorPosition->YdPosition;
		m_pTrade->OnPositionRsp(&data);
	}

	if (bIsLast )
	{
		m_pTrade->OnRspStatus(PositionRsp);
		if ( CTrade::m_mapInstrument.size() <= 0)
		{
			Sleep(1000);
			m_pTrade->ReqInstrument();
		}
		else
		{
			m_pTrade->Ready(true);
		}
	}
	
}

void CFtdcTradeSpi::OnRspSettlementInfoConfirm( CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade)
	{
		m_pTrade->OnLogined();

		//查询资金 合约 保证金 费率
		
		Sleep(1000);
		m_pTrade->ReqFund();
	}
}


void CFtdcTradeSpi::OnRspQryInstrument( CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade)
	{
		CQuantInstrumentField data;
		memset(&data,0,sizeof(data));
		strcpy(data.ExchangeID, pInstrument->ExchangeID);
		strcpy(data.CreateDate, pInstrument->CreateDate);
		data.DeliveryMonth = pInstrument->DeliveryMonth;
		data.DeliveryYear = pInstrument->DeliveryYear;
		strcpy(data.EndDelivDate, pInstrument->EndDelivDate);
		strcpy(data.ExpireDate, pInstrument->ExpireDate);
		strcpy(data.InstrumentID, pInstrument->InstrumentID);
		data.IsTrading = pInstrument->IsTrading;
		data.MaxLimitOrderVolume = pInstrument->MaxLimitOrderVolume;
		data.MaxMarketOrderVolume = pInstrument->MaxMarketOrderVolume;
		data.MinLimitOrderVolume = pInstrument->MinLimitOrderVolume;
		data.MinMarketOrderVolume = pInstrument->MinMarketOrderVolume;
		data.PriceTick = pInstrument->PriceTick;
		data.VolumeMultiple = pInstrument->VolumeMultiple;
		m_pTrade->OnInstrumentRsp(&data);
	}
	if (bIsLast)
	{
		m_pTrade->Ready(true);
	}
}

void CFtdcTradeSpi::OnRspQryInstrumentMarginRate( CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade && pInstrumentMarginRate)
	{
		CQuantMarginField data;
		memset(&data,0,sizeof(data));
		strcpy(data.InstrumentID, pInstrumentMarginRate->InstrumentID);
		data.LongMarginAmt = pInstrumentMarginRate->LongMarginRatioByVolume;
		data.LongMarginRate = pInstrumentMarginRate->LongMarginRatioByMoney;
		data.ShortMarginAmt = pInstrumentMarginRate->ShortMarginRatioByVolume;
		data.ShortMarginRate = pInstrumentMarginRate->ShortMarginRatioByMoney;
		m_pTrade->OnMarginRsp(&data);
	}
	//费率
	if (bIsLast)
	{
		Sleep(1000);
		m_pTrade->ReqFee();
	}
	
}

void CFtdcTradeSpi::OnRspQryInstrumentCommissionRate( CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade && pInstrumentCommissionRate)
	{
		CQuantFeeField data;
		memset(&data,0,sizeof(data));
		strcpy(data.InstrumentID, pInstrumentCommissionRate->InstrumentID);
		data.OffsetFeeAmt = pInstrumentCommissionRate->CloseRatioByVolume;
		data.OffsetFeeRate = pInstrumentCommissionRate->CloseRatioByMoney;
		data.OpenFeeAmt = pInstrumentCommissionRate->OpenRatioByVolume;
		data.OpenFeeRate = pInstrumentCommissionRate->OpenRatioByMoney;
		data.OTFeeAmt = pInstrumentCommissionRate->CloseTodayRatioByVolume;
		data.OTFeeRate = pInstrumentCommissionRate->CloseTodayRatioByMoney;
		m_pTrade->OnFeeRsp(&data);
	}

	if ( bIsLast)
	{
		Sleep(1000);
		m_pTrade->ReqPosition();
	}	
}
