#ifndef ISTRATEGYH
#define ISTRATEGYH
#include "IFactor.h"
#include "IFunction.h"
#include "QuantStruct.h"

class IStrategy;
typedef void (*OnZDQHOrderRsp)(CQuantOrderField*, IStrategy* pStrategy);
typedef void (*OnZDQHTradeRsp)(CQuantTradeField*, IStrategy* pStrategy);
typedef void (*OnZDQHMarkerDataRsp)(CQuantDepthQuoteDataField*, IStrategy* pStrategy);
typedef void (*OnZDQHErrInfoRsp)(void*, IStrategy* pStrategy);

class IStrategy
{
public:
	virtual void Release() = 0;

	//交易
	virtual unsigned long ReqOrderInsert(const char* pIntrument,double dLimitPrice, int nOrderNum, TQuantBSDirection bs, TQuantOpenFlag of,TQuantHedgeType ht, TQuantPriceOrderType ordertype, TQuantTimeConditionType tcType) = 0;

	//撤单
	virtual unsigned long ReqOrderDelete(unsigned long ulOrderID) = 0;

	//获取策略资金信息
	virtual CQuantInvestorAccountField* GetAccountFund() = 0;

	//获取策略持仓信息
	virtual void GetAccountPosition(CQuantPositionField** ppPosition, int& nCount) = 0;

	//获取历史tick行情
	virtual long GetMarketData(const char* lpInstrument,CQuantDepthQuoteDataField** ppMarketData, long lDataNum) = 0;

	//获取历史k线行情
	virtual long GetKLineData(const char* lpInstrument,CQuantKLineDataField** ppMarketData, long lDataNum, TQuantDataPeriod period) = 0;

	//获取合约信息
	virtual CQuantInstrumentField* GetInstrument(const char* pInstrumentUD) = 0;

	//注册报单回报
	virtual void RegOrderRsp(OnZDQHOrderRsp fOrderRsp) = 0;

	//注册成交回报
	virtual void RegTradeRsp(OnZDQHTradeRsp fTradeRsp) = 0;

	//注册期货行情通知
	virtual void RegMarketDataRsp(OnZDQHMarkerDataRsp fMarketDataRsp) = 0;	

	//获取函数库接口
	virtual IFunction* GetFunction() = 0;

	//获取因子库接口
	virtual IFactor* GetFactor() = 0;
};

extern "C"
{
	void _cdecl InitQuant();
	IStrategy* _cdecl CreateStrategy(const char* pStrategyName);
};


#endif