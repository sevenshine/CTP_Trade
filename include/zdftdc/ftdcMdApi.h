/////////////////////////////////////////////////////////////////////////
///@system 新一代行情柜台系统
///@company 浙江中大期货有限公司
///@file ftdcMdApi.h
///@brief 定义了客户端接口
///@history 
///20141202	杨鹏	创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(ZDQHv2_FTDCMDAPI_H)
#define ZDQHv2_FTDCMDAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ftdcfieldstruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define MD_API_EXPORT __declspec(dllexport)
#else
#define MD_API_EXPORT __declspec(dllimport)
#endif
#else
#define MD_API_EXPORT 
#endif

class CFtdcMdSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};


	///登录请求响应
	virtual void OnRspUserLogin(CFtdcRspUserLoginField *pRspUserLogin, CFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	///登出请求响应
	virtual void OnRspUserLogout(CFtdcUserLogoutField *pUserLogout, CFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(CFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅行情应答
	virtual void OnRspSubMarketData(CFtdcSpecificInstrumentField *pSpecificInstrument, CFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};
	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CFtdcSpecificInstrumentField *pSpecificInstrument, CFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CFtdcDepthMarketDataField *pDepthMarketData) {};

	///查询历史tick应答
	virtual void OnRspQryHisTick(CFtdcRspQryHisTickField *pRspQryHisTick, CFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///历史tick通知
	//virtual void OnRtnHisTick(CFtdcRspQryHisTickField *pRspQryHisTick, int nRequestID, bool bIsLast) {};
	virtual void OnRtnHisTick(CFtdcHisTickField *pRspQryHisTick) {};

	///查询日K线应答
	virtual void OnRspQryKLineDay(CFtdcRspQryKLineDayField *pRspQryKLineDay, CFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///日K线通知
	//virtual void OnRtnKLineDay(CFtdcRspQryHisTickField *pRspQryHisTick, int nRequestID, bool bIsLast) {};
	virtual void OnRtnKLineDay(CFtdcKLineDayField *pKLineDay) {};

	///查询1分钟K线应答
	virtual void OnRspQryKLine1Minute(CFtdcRspQryKLine1MinuteField *pRspQryKLine1Minute, CFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///1分钟K线通知
	//virtual void OnRtnKLine1Minute(CFtdcRspQryHisTickField *pRspQryHisTick, int nRequestID, bool bIsLast) {};
	virtual void OnRtnKLine1Minute(CFtdcKLine1MinuteField *pKLine1Minute) {};
};

class MD_API_EXPORT CFtdcMdApi
{
public:
	///创建MdApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	///modify for udp marketdata
	static CFtdcMdApi *CreateFtdcMdApi(const char *pszFlowPath = "", const bool bIsUsingUdp=false);

	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;

	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;

	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;

	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;

	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;

	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(CFtdcMdSpi *pSpi) = 0;

	///订阅行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int SubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;

	///退订行情。
	///@param ppInstrumentID 合约ID  
	///@param nCount 要订阅/退订行情的合约个数
	///@remark 
	virtual int UnSubscribeMarketData(char *ppInstrumentID[], int nCount) = 0;

	///登出请求
	virtual int ReqUserLogout(CFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;

	///备忘：后期添加查询K线接口

	///用户登录请求
	virtual int ReqUserLogin(CFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;

	///查询历史tick
	virtual int ReqQryHisTick(CFtdcReqQryHisTickField *pReqQryHisTickField, int nRequestID) = 0;

	///查询日K线
	virtual int ReqQryKLineDay(CFtdcReqQryKLineDayField *pReqQryHisTickField, int nRequestID) = 0;

	///查询1分钟K线
	virtual int ReqQryKLine1Minute(CFtdcReqQryKLine1MinuteField *pReqQryKLine1MinuteField, int nRequestID) = 0;
protected:
	~CFtdcMdApi(){};
};

#endif
