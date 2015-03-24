
#ifndef BT_FUNCSDLL_H
#define BT_FUNCSDLL_H

#include <windows.h>
#include "QuantStruct.h"

#ifdef LIB_API_EXPORT
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT __declspec(dllimport)
#endif

//订单响应
typedef int(*BTOrderRsp)(CQuantOrderField*, const char*);
//成交回报
typedef int(*BTBarginRsp)(CQuantTradeField*, const char*);


/*******************************************************************************
* Function: BTMarketDataInsert
* -----------------------------------------------------------------------------
* Description: 行情数据录入接口
* Function:
******************************************************************************/
int API_EXPORT BTMarketDataInsert(CQuantDepthQuoteDataField* stmarket);

/*******************************************************************************
* Function: BTOrderInsert
* -----------------------------------------------------------------------------
* Description: 报单录入接口
* Function:
******************************************************************************/
int API_EXPORT BTOrderInsert(CQuantOrderField * stOrder,const char* strName);

/*******************************************************************************
* Function: BTOrderCancel
* -----------------------------------------------------------------------------
* Description: 报单撤销录入接口
* Function:
******************************************************************************/
int  API_EXPORT BTOrderCancel(CQuantOrderField * stOrder,const char* strName);
/*******************************************************************************
* Function: BTRegOrderRsp
* -----------------------------------------------------------------------------
* Description: 订单响应回调注册函数
* Function:
******************************************************************************/
bool API_EXPORT BTRegOrderRsp(BTOrderRsp call);
/*******************************************************************************
* Function: BTRegBarginRsp
* -----------------------------------------------------------------------------
* Description: 成交回报回调注册函数
* Function:
******************************************************************************/
bool API_EXPORT BTRegBarginRsp(BTBarginRsp call);


/*******************************************************************************
* Class:  CBTJob
* -----------------------------------------------------------------------------
* Description:  回测入口类
*
* Function:
*
******************************************************************************/
class API_EXPORT CBTJob
{
public:
	CBTJob();
	~CBTJob();
	//初始化
	void init();
	//读取xml配置
	void ReadConfig();
	//Python
	int Python();
	//交易，行情，回测
	void ProxyStart();
	//清理
	void destroy();

	void Join();
};

#endif