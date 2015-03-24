#include "StdAfx.h"
#include "UstpTradeSpi.h"
#include "Trade.h"
#include "..\log\c-log-master\src\log.h"


CUstpTradeSpi::CUstpTradeSpi(CTrade* pTrade)
{
	m_pTrade = pTrade;
}


CUstpTradeSpi::~CUstpTradeSpi(void)
{
}

void CUstpTradeSpi::OnFrontConnected()
{
	if (m_pTrade)
	{
		m_pTrade->Login();
	}
	LOG_NOTICE("femas trade connected");
}

void CUstpTradeSpi::OnFrontDisconnected( int nReason )
{
	if (m_pTrade)
	{
		m_pTrade->OnDisConnected();
	}
	LOG_ERROR("femas trade disconnected");
}

void CUstpTradeSpi::OnRspUserLogin( CUstpFtdcRspUserLoginField *pRspUserLogin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (pRspInfo)
	{
		//suc
		if (pRspInfo->ErrorID == 0)
		{
			m_pTrade->SetMaxOrderID(atol(pRspUserLogin->MaxOrderLocalID));
			m_pTrade->OnLogined();
			LOG_NOTICE("femas trade login suc, %s", pRspUserLogin->UserID);		
		}
		else
		{
			LOG_ERROR("femas trade login failed, %s, ErrMsg: %s", pRspUserLogin->UserID, pRspInfo->ErrorMsg);
		}
	}
}

void CUstpTradeSpi::OnRspOrderInsert( CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	//printf("OnRspOrderInsert: %s \r\n", pInputOrder->UserOrderLocalID);
	CQuantOrderField order;
	memset(&order,0,sizeof(order));
	strcpy(order.BrokerID,pInputOrder->BrokerID);
	order.Direction = pInputOrder->Direction;
	order.HedgeFlag = pInputOrder->HedgeFlag;
	strcpy(order.InstrumentID, pInputOrder->InstrumentID);
	strcpy(order.InvestorID, pInputOrder->InvestorID);
	order.LimitPrice = pInputOrder->LimitPrice;
	order.OffsetFlag = pInputOrder->OffsetFlag;
	order.OrderRef = atol(pInputOrder->UserOrderLocalID);
	order.StopPrice = pInputOrder->StopPrice;
	strcpy(order.UserID, pInputOrder->UserID);
	order.VolumeTotalOriginal = pInputOrder->Volume;
	strcpy(order.StatusMsg, pRspInfo->ErrorMsg);
	order.ErrorID = pRspInfo->ErrorID;
	if (m_pTrade)
	{
		m_pTrade->OnRtnOrder(&order);
	}
}

void CUstpTradeSpi::OnRspOrderAction( CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	CQuantOrderField order;
	memset(&order,0,sizeof(order));
	strcpy(order.BrokerID,pOrderAction->BrokerID);
	strcpy(order.InvestorID, pOrderAction->InvestorID);
	order.LimitPrice = pOrderAction->LimitPrice;
	order.OrderRef = atol(pOrderAction->UserOrderLocalID);
	strcpy(order.UserID, pOrderAction->UserID);
	strcpy(order.StatusMsg, pRspInfo->ErrorMsg);
	order.ErrorID = pRspInfo->ErrorID;
	if (m_pTrade)
	{
		m_pTrade->OnRtnOrder(&order);
	}
}

void CUstpTradeSpi::OnRtnOrder( CUstpFtdcOrderField *pOrder )
{
	//printf("OnRtnOrder: %s, %c\r\n", pOrder->UserOrderLocalID, pOrder->OrderStatus);
	CQuantOrderField order;
	memset(&order,0,sizeof(order));
	strcpy(order.BrokerID,pOrder->BrokerID);
	strcpy(order.CancelTime,pOrder->CancelTime);
	order.Direction = pOrder->Direction;
	order.HedgeFlag = pOrder->HedgeFlag;
	strcpy(order.InsertTime, pOrder->InsertTime);
	strcpy(order.InstrumentID, pOrder->InstrumentID);
	strcpy(order.InvestorID, pOrder->InvestorID);
	order.LimitPrice = pOrder->LimitPrice;
	order.OffsetFlag = pOrder->OffsetFlag;
	order.OrderRef = atol(pOrder->UserOrderLocalID);
	order.OrderStatus = pOrder->OrderStatus;
	strcpy(order.OrderSysID, pOrder->OrderSysID);
	order.StopPrice = pOrder->StopPrice;
	strcpy(order.TradingDay, pOrder->TradingDay);
	strcpy(order.UserID, pOrder->UserID);
	order.VolumeTotalOriginal = pOrder->Volume;
	order.VolumeTraded = pOrder->VolumeTraded;
	order.ErrorID = 0;
	if (m_pTrade)
	{
		m_pTrade->OnRtnOrder(&order);
	}
}

void CUstpTradeSpi::OnRtnTrade( CUstpFtdcTradeField *pTrade )
{
	CQuantTradeField trade;
	memset(&trade, 0, sizeof(trade));
	strcpy(trade.BrokerID,pTrade->BrokerID);
	trade.Direction = pTrade->Direction;
	trade.HedgeFlag = pTrade->HedgeFlag;
	strcpy(trade.TradeTime, pTrade->TradeTime);
	strcpy(trade.InstrumentID, pTrade->InstrumentID);
	strcpy(trade.InvestorID, pTrade->InvestorID);
	trade.OrderRef = atol(pTrade->UserOrderLocalID);
	trade.OffsetFlag = pTrade->OffsetFlag;
	strcpy(trade.OrderSysID, pTrade->OrderSysID);
	strcpy(trade.TradeID, pTrade->TradeID);
	trade.Price = pTrade->TradePrice;
	strcpy(trade.TradingDay, pTrade->TradingDay);
	strcpy(trade.UserID, pTrade->UserID);
	trade.Volume = pTrade->TradeVolume;

	if (m_pTrade)
	{
		m_pTrade->OnRtnTrade(&trade);
	}
}

void CUstpTradeSpi::OnErrRtnOrderInsert( CUstpFtdcInputOrderField *pInputOrder, CUstpFtdcRspInfoField *pRspInfo )
{
	CQuantOrderField order;
	memset(&order,0,sizeof(order));
	strcpy(order.BrokerID,pInputOrder->BrokerID);
	order.Direction = pInputOrder->Direction;
	order.HedgeFlag = pInputOrder->HedgeFlag;
	strcpy(order.InstrumentID, pInputOrder->InstrumentID);
	strcpy(order.InvestorID, pInputOrder->InvestorID);
	order.LimitPrice = pInputOrder->LimitPrice;
	order.OffsetFlag = pInputOrder->OffsetFlag;
	order.OrderRef = atol(pInputOrder->UserOrderLocalID);
	order.StopPrice = pInputOrder->StopPrice;
	strcpy(order.UserID, pInputOrder->UserID);
	order.VolumeTotalOriginal = pInputOrder->Volume;
	strcpy(order.StatusMsg, pRspInfo->ErrorMsg);
	order.ErrorID = pRspInfo->ErrorID;
	if (m_pTrade)
	{
		m_pTrade->OnRtnOrder(&order);
	}
}

void CUstpTradeSpi::OnErrRtnOrderAction( CUstpFtdcOrderActionField *pOrderAction, CUstpFtdcRspInfoField *pRspInfo )
{
	CQuantOrderField order;
	memset(&order,0,sizeof(order));
	strcpy(order.BrokerID,pOrderAction->BrokerID);
	strcpy(order.OrderSysID, pOrderAction->OrderSysID);
	strcpy(order.InvestorID, pOrderAction->InvestorID);
	order.LimitPrice = pOrderAction->LimitPrice;
	order.OrderRef = atol(pOrderAction->UserOrderLocalID);
	strcpy(order.UserID, pOrderAction->UserID);
	order.VolumeTotalOriginal = pOrderAction->VolumeChange;
	strcpy(order.StatusMsg, pRspInfo->ErrorMsg);
	order.ErrorID = pRspInfo->ErrorID;
	if (m_pTrade)
	{
		m_pTrade->OnRtnOrder(&order);
	}
}

void CUstpTradeSpi::OnRspQryUserInvestor( CUstpFtdcRspUserInvestorField *pRspUserInvestor, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade)
	{
		m_pTrade->SetInvestID(pRspUserInvestor->InvestorID);
	}

	if (bIsLast)
	{
		//查询合约、资金、保证金、费率
		Sleep(1000);
		m_pTrade->ReqFund();
	}
}

void CUstpTradeSpi::OnRspQryInvestorAccount( CUstpFtdcRspInvestorAccountField *pRspInvestorAccount, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade)
	{
		if (pRspInvestorAccount)
		{
			CQuantInvestorAccountField data;
			memset(&data, 0, sizeof(CQuantInvestorAccountField));
			strcpy(data.AccountID,pRspInvestorAccount->AccountID);
			data.PreBalance = pRspInvestorAccount->PreBalance;
			data.Available = pRspInvestorAccount->Available;
			data.CloseProfit = pRspInvestorAccount->CloseProfit;
			data.Deposit = pRspInvestorAccount->Deposit;
			data.Withdraw = pRspInvestorAccount->Withdraw;
			data.Fee = pRspInvestorAccount->Fee;
			data.DynamicRights = pRspInvestorAccount->DynamicRights;
			data.FrozenFee = pRspInvestorAccount->FrozenFee;
			data.FrozenMargin = pRspInvestorAccount->FrozenMargin;
			data.Margin = pRspInvestorAccount->Margin;
			data.PositionProfit = pRspInvestorAccount->PositionProfit;
			m_pTrade->OnFundRsp(&data);
		}	
	}
	if (bIsLast)
	{
		//查询保证金
		Sleep(1000);
		m_pTrade->OnRspStatus(AccountFundRsp);
		m_pTrade->ReqMargin();
	}
}

void CUstpTradeSpi::OnRspQryInvestorFee( CUstpFtdcInvestorFeeField *pInvestorFee, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade)
	{
		if (pInvestorFee)
		{
			CQuantFeeField data;
			memset(&data,0,sizeof(data));
			strcpy(data.InstrumentID, pInvestorFee->InstrumentID);
			data.OffsetFeeAmt = pInvestorFee->OffsetFeeAmt;
			data.OffsetFeeRate = pInvestorFee->OffsetFeeRate;
			data.OpenFeeAmt = pInvestorFee->OpenFeeAmt;
			data.OpenFeeRate = pInvestorFee->OpenFeeRate;
			data.OTFeeAmt = pInvestorFee->OTFeeAmt;
			data.OTFeeRate = pInvestorFee->OTFeeRate;
			m_pTrade->OnFeeRsp(&data);
		}	
	}
	if (bIsLast)
	{
		//合约
		Sleep(1000);
		m_pTrade->ReqInstrument();
	}
}

void CUstpTradeSpi::OnRspQryInvestorMargin( CUstpFtdcInvestorMarginField *pInvestorMargin, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade)
	{
		if (pInvestorMargin)
		{
			CQuantMarginField data;
			memset(&data,0,sizeof(data));
			strcpy(data.InstrumentID, pInvestorMargin->InstrumentID);
			data.LongMarginAmt = pInvestorMargin->LongMarginAmt;
			data.LongMarginRate = pInvestorMargin->LongMarginRate;
			data.ShortMarginAmt = pInvestorMargin->ShortMarginAmt;
			data.ShortMarginRate = pInvestorMargin->ShortMarginRate;
			m_pTrade->OnMarginRsp(&data);
		}		
	}
	if (bIsLast)
	{
		//费率
		Sleep(1000);
		m_pTrade->ReqFee();
	}
}

void CUstpTradeSpi::OnRspQryInstrument( CUstpFtdcRspInstrumentField *pInstrument, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
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

		if (bIsLast)
		{
			Sleep(1000);
			m_pTrade->ReqPosition();
		}
	}
}

void CUstpTradeSpi::OnRspQryInvestorPosition( CUstpFtdcRspInvestorPositionField *pInvestorPosition, CUstpFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast )
{
	if (m_pTrade)
	{
		if (pInvestorPosition)
		{
			CQuantPositionField data;
			memset(&data,0,sizeof(data));
			data.Direction = pInvestorPosition->Direction;
			data.HedgeFlag = pInvestorPosition->HedgeFlag;
			strcpy(data.InstrumentID, pInvestorPosition->InstrumentID);
			strcpy(data.InvestorID,pInvestorPosition->InvestorID);
			data.Position = pInvestorPosition->Position;
			data.PositionCost = pInvestorPosition->PositionCost;
			data.UsedMargin = pInvestorPosition->UsedMargin;
			data.YdPosition = pInvestorPosition->YdPosition;
			m_pTrade->OnPositionRsp(&data);
		}
	

		if (bIsLast)
		{
			m_pTrade->Ready(true);
		}
	}
}
