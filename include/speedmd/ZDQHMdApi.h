/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company  中大期货
///@file ZDQHMdApi.h
///@brief 定义了客户端行情接口
///@history 
///20130923	徐旦		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef ZDQHMDAPIH
#define ZDQHMDAPIH

#include "ZDQHUserApiStruct.h"




class CZDQHFtdcMdSpi
{
public:
	///当客户端与交易后台建立起通信连接时
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接。
	virtual void OnFrontDisconnected(){};
		
	///订阅行情应答
	virtual void OnRspSubMarketData(CZDQHFtdcSpecificInstrumentField *pSpecificInstrument, CZDQHFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CZDQHFtdcSpecificInstrumentField *pSpecificInstrument, CZDQHFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CZDQHFtdcDepthQuoteDataField *pDepthMarketData) {};

	///价差行情通知
	virtual void OnRtnBasisQuote(CZDQHFtdcRspBasisQuoteField *pDepthMarketData) {};

	///level2股票行情
	virtual void OnRtnLevel2StockQuote(CLevel2ZDQHFtdcLevel2MarketDataField* pDepthMarketData){};

	///level2指数行情
	virtual void OnRtnLevel2IndexQuote(CLevel2ZDQHFtdcNGTSIndexField* pDepthMarketData){};
};



class API_EXPORT CZDQHFtdcMdApi
{
public:
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///接收现货行情开关
	///@param bEnable true接收  false 不接受
	virtual void EnableGetStockQuote(bool bEnable=true) = 0;

	///初始化,连接服务器
	virtual void Init() = 0;	
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CZDQHFtdcMdSpi *pSpi) = 0;
	
	///订阅行情。
	///@param exchangeID 交易所ID  
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark   返回0 成功  非0失败
	virtual int SubscribeMarketData(TZDQHExchangeType exchangeID[] ,char *ppInstrumentID[], int nCount) = 0;
	
	///退订行情。
	///@param exchangeID 交易所ID  
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(TZDQHExchangeType exchangeID[],char *ppInstrumentID[], int nCount) = 0;

	///订阅价差行情
	///@param pReqBasisQuote 订阅价差请求 
	///@return 0 成功 非0失败
	///@remark 
	virtual int SubscribeBasisQuote(CZDQHFtdcReqBasisQuoteField* pReqBasisQuote) = 0 ;

	///退订价差行情
	///@param pReqBasisQuote 退订价差请求 
	///@return 0 成功 非0失败
	///@remark  如果没有输入合约，则退订所有订阅请求
	virtual int UnSubscribeBasisQuote(CZDQHFtdcReqBasisQuoteField* pReqBasisQuote) = 0;

	///订阅股票level2行情
	///@param pReqSubLevel2 订阅的股票信息  
	///@param nCount 要订阅/退订行情的合约个数
	///@param bIndex 是否是指数
	///@return 0 成功 非0失败
	///@remark 
	virtual int SubStockLevel2Quote(CZDQHStockLevel2Field* pReqSubLevel2, int nCount, bool bIndex=false) = 0;

	///退订股票level2行情
	///@param pReqSubLevel2 退订的股票信息  
	///@param nCount 要订阅/退订行情的合约个数
	///@param bIndex 是否是指数
	///@return 0 成功 非0失败
	///@remark 
	virtual int UnSubStockLevel2Quote(CZDQHStockLevel2Field* pReqSubLevel2, int nCount, bool bIndex=false) = 0;


protected:
	virtual ~CZDQHFtdcMdApi(){};
};

extern "C"
{
	CZDQHFtdcMdApi* CDECL CreateFtdcMdApi(const char *pszFlowPath = "");
}

#endif