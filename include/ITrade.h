/////////////////////////////////////////////////////////////////////////
///@system   金融量化交易平台
///@company  中大期货
///@file ITrade.h
///@brief    定义了交易接口
///@history 
///20141015	徐旦		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef ITARDEH
#define ITARDEH
#include "QuantStruct.h"

enum ETradeStatus
{
	connected = 0,
	disconnected,
	Logined,
	AccountFundRsp,
	PositionRsp
};

typedef void (*OnRecvOrder)(CQuantOrderField*, long lHandle);
typedef void (*OnRecvTrade)(CQuantTradeField*, long lHandle);
typedef void (*OnStatus)(ETradeStatus status,long lHandle);

class ITrade	
{
public:
	virtual unsigned long ReqOrderInsert(const char* pIntrument,double dLimitPrice, int nOrderNum, TQuantBSDirection bs, TQuantOpenFlag of,TQuantHedgeType ht, TQuantPriceOrderType ordertype,TQuantTimeConditionType tcType) = 0;

	virtual unsigned long ReqOrderDelete(unsigned long ulOrderID, const char* pOrderSysID, const char* pInstrumengID) = 0;

	virtual void Release() = 0;

	virtual void RegOrderRsp(OnRecvOrder fOrderRsp, long lHandle) = 0;

	virtual void RegTradeRsp(OnRecvTrade fOrderRsp, long lHandle) = 0;

	virtual void RegTradeStatus(OnStatus fStatus, long lHandle) = 0;

	virtual CQuantMarginField* GetMarginField(const char* lpInstrumentID) = 0;

	virtual CQuantFeeField* GetFeeField(const char* lpInstrumentID) = 0;

	virtual	CQuantInstrumentField* GetInstrument(const char* lpInstrumentID) = 0;

	virtual CQuantInvestorAccountField* GetAccountFund() = 0;

	virtual bool IsReady() = 0;
};

extern "C"
{;
	ITrade* CreateTrade(const char* lpAccount);
};

#endif