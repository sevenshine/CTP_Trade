/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company  中大期货
///@file ZDQHUserApiStruct.h
///@brief 定义了客户端接口业务数据结构
///@history 
///20130923	徐旦		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef ZDQHUSERAPISTRUCTH
#define ZDQHUSERAPISTRUCTH

#include "ZDQHUserApiType.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT __declspec(dllimport)
#endif
#else
#define API_EXPORT 
#endif

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_MD_API_EXPORT
#define CDECL    __cdecl
#else
#define CDECL __cdecl
#endif
#else
#define CDECL 
#endif

///市场 CZCE-郑州,DCE-大连,SHFE-上海,CFFEX-中金
typedef char TZDQHExchangeType[9];

#pragma  pack(1)

struct CZDQHAddressField
{
    TZDQHIpType						Ip;     ///< 交易服务器IP地址
    TZDQHPortType					Port;   ///< 交易服务器端口号
};

///价差行情订阅请求
struct CZDQHFtdcReqBasisQuoteField
{
	///订阅类型 1 订阅 2退订
	TZDQHFtdcSubType  SubType;
	///第一腿合约市场ID
	TZDQHFtdcExchangeIDType	ExchangeID1;
	///第一腿合约，如果是订阅沪深300指数的行情，默认取000300，ExchangeID1可为空
	TZDQHFtdcInstrumentIDType	InstrumentID1;
	///第二腿合约市场ID
	TZDQHFtdcExchangeIDType	ExchangeID2;
	///第二腿合约
	TZDQHFtdcInstrumentIDType	InstrumentID2;
};

///价差行情通知
struct CZDQHFtdcRspBasisQuoteField
{
	///第一腿合约市场ID
	TZDQHFtdcExchangeIDType	ExchangeID1;
	///第一腿合约，如果是订阅沪深300指数的行情，默认取000300，ExchangeID1可为空
	TZDQHFtdcInstrumentIDType	InstrumentID1;
	///第二腿合约市场ID
	TZDQHFtdcExchangeIDType	ExchangeID2;
	///第二腿合约
	TZDQHFtdcInstrumentIDType	InstrumentID2;
	///价差 （第一腿合约 - 第二腿合约）
	TZDQHFtdcBasisQuoteType		BasisQuote;
};


///用户登录请求
struct CZDQHFtdcReqUserLoginField
{
	///交易日
	TZDQHFtdcDateType	TradingDay;
	///经纪公司代码
	TZDQHFtdcBrokerIDType	BrokerID;
	///用户代码
	TZDQHFtdcUserIDType	UserID;
	///密码
	TZDQHFtdcPasswordType	Password;
	///用户端产品信息
	TZDQHFtdcProductInfoType	UserProductInfo;
	///接口端产品信息
	TZDQHFtdcProductInfoType	InterfaceProductInfo;
	///协议信息
	TZDQHFtdcProtocolInfoType	ProtocolInfo;
	///Mac地址
	TZDQHFtdcMacAddressType	MacAddress;
	///动态密码
	TZDQHFtdcPasswordType	OneTimePassword;
	///终端IP地址
	TZDQHFtdcIPAddressType	ClientIPAddress;
};

///用户登录应答
struct CZDQHFtdcRspUserLoginField
{
	///交易日
	TZDQHFtdcDateType	TradingDay;
	///登录成功时间
	TZDQHFtdcTimeType	LoginTime;
	///经纪公司代码
	TZDQHFtdcBrokerIDType	BrokerID;
	///用户代码
	TZDQHFtdcUserIDType	UserID;
	///交易系统名称
	TZDQHFtdcSystemNameType	SystemName;
	///前置编号
	TZDQHFtdcFrontIDType	FrontID;
	///会话编号
	TZDQHFtdcSessionIDType	SessionID;
	///最大报单引用
	TZDQHFtdcOrderRefType	MaxOrderRef;
	///上期所时间
	TZDQHFtdcTimeType	SHFETime;
	///大商所时间
	TZDQHFtdcTimeType	DCETime;
	///郑商所时间
	TZDQHFtdcTimeType	CZCETime;
	///中金所时间
	TZDQHFtdcTimeType	FFEXTime;
};

///用户登出请求
struct CZDQHFtdcUserLogoutField
{
	///经纪公司代码
	TZDQHFtdcBrokerIDType	BrokerID;
	///用户代码
	TZDQHFtdcUserIDType	UserID;
};

///指定的合约
struct CZDQHFtdcSpecificInstrumentField
{
	///合约代码
	TZDQHFtdcInstrumentIDType	InstrumentID;
};



///深度行情
struct CZDQHFtdcDepthQuoteDataField
{
	///交易日
	TZDQHFtdcDateType	TradingDay;
	///合约代码
	TZDQHFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TZDQHFtdcExchangeIDType	ExchangeID;
	///合约在交易所的代码
	TZDQHFtdcExchangeInstIDType	ExchangeInstID;
	///最新价
	TZDQHFtdcPriceType	LastPrice;
	///上次结算价
	TZDQHFtdcPriceType	PreSettlementPrice;
	///昨收盘
	TZDQHFtdcPriceType	PreClosePrice;
	///昨持仓量
	TZDQHFtdcLargeVolumeType	PreOpenInterest;
	///今开盘
	TZDQHFtdcPriceType	OpenPrice;
	///最高价
	TZDQHFtdcPriceType	HighestPrice;
	///最低价
	TZDQHFtdcPriceType	LowestPrice;
	///数量
	TZDQHFtdcVolumeType	Volume;
	///成交金额
	TZDQHFtdcMoneyType	Turnover;
	///持仓量
	TZDQHFtdcLargeVolumeType	OpenInterest;
	///今收盘
	TZDQHFtdcPriceType	ClosePrice;
	///本次结算价
	TZDQHFtdcPriceType	SettlementPrice;
	///涨停板价
	TZDQHFtdcPriceType	UpperLimitPrice;
	///跌停板价
	TZDQHFtdcPriceType	LowerLimitPrice;
	///昨虚实度
	TZDQHFtdcRatioType	PreDelta;
	///今虚实度
	TZDQHFtdcRatioType	CurrDelta;
	///最后修改时间
	TZDQHFtdcTimeType	UpdateTime;
	///最后修改毫秒
	TZDQHFtdcMillisecType	UpdateMillisec;
	///申买价一
	TZDQHFtdcPriceType	BidPrice1;
	///申买量一
	TZDQHFtdcVolumeType	BidVolume1;
	///申卖价一
	TZDQHFtdcPriceType	AskPrice1;
	///申卖量一
	TZDQHFtdcVolumeType	AskVolume1;
	///申买价二
	TZDQHFtdcPriceType	BidPrice2;
	///申买量二
	TZDQHFtdcVolumeType	BidVolume2;
	///申卖价二
	TZDQHFtdcPriceType	AskPrice2;
	///申卖量二
	TZDQHFtdcVolumeType	AskVolume2;
	///申买价三
	TZDQHFtdcPriceType	BidPrice3;
	///申买量三
	TZDQHFtdcVolumeType	BidVolume3;
	///申卖价三
	TZDQHFtdcPriceType	AskPrice3;
	///申卖量三
	TZDQHFtdcVolumeType	AskVolume3;
	///申买价四
	TZDQHFtdcPriceType	BidPrice4;
	///申买量四
	TZDQHFtdcVolumeType	BidVolume4;
	///申卖价四
	TZDQHFtdcPriceType	AskPrice4;
	///申卖量四
	TZDQHFtdcVolumeType	AskVolume4;
	///申买价五
	TZDQHFtdcPriceType	BidPrice5;
	///申买量五
	TZDQHFtdcVolumeType	BidVolume5;
	///申卖价五
	TZDQHFtdcPriceType	AskPrice5;
	///申卖量五
	TZDQHFtdcVolumeType	AskVolume5;
	///当日均价
	TZDQHFtdcPriceType	AveragePrice;
};

///响应信息
struct CZDQHFtdcRspInfoField
{
	///错误代码
	TZDQHFtdcErrorIDType	ErrorID;
	///错误信息
	TZDQHFtdcErrorMsgType	ErrorMsg;
};

///现货level2行情订阅
struct CZDQHStockLevel2Field
{
	///证券代码
	TZDQHFtdcStockIDType	SecurityID;
	///交易所代码    上海"SSE"  深圳 "SZE"
	TZDQHFtdcStockExchangeIDType	ExchangeID;
};

///Level2股票深度行情
struct CLevel2ZDQHFtdcLevel2MarketDataField
{
	///交易日
	TZDQHFtdcDateType	TradingDay;
	///时间戳
	TZDQHFtdcTimeType	DataTimeStamp;
	///交易所代码
	TZDQHFtdcExchangeIDType	ExchangeID;
	///证券代码
	TZDQHFtdcStockIDType	SecurityID;
	///昨收盘价
	TZDQHFtdcPriceType	PreClosePx;
	///今开盘价
	TZDQHFtdcPriceType	OpenPx;
	///最高价
	TZDQHFtdcPriceType	HighPx;
	///最低价
	TZDQHFtdcPriceType	LowPx;
	///现价
	TZDQHFtdcPriceType	LastPx;
	///收盘价
	TZDQHFtdcPriceType	ClosePx;
	///成交笔数
	TZDQHFtdcVolumeType	NumTrades;
	///成交总量
	TZDQHFtdcLargeVolumeType	TotalVolumeTrade;
	///成交总金额
	TZDQHFtdcMoneyType	TotalValueTrade;
	///委托买入总量
	TZDQHFtdcLargeVolumeType	TotalBidQty;
	///加权平均委买价
	TZDQHFtdcPriceType	WeightedAvgBidPx;
	///债券加权平均委买价
	TZDQHFtdcPriceType	AltWeightedAvgBidPx;
	///委托卖出总量
	TZDQHFtdcLargeVolumeType	TotalOfferQty;
	///加权平均委卖价
	TZDQHFtdcPriceType	WeightedAvgOfferPx;
	///债券加权平均委卖价格
	TZDQHFtdcPriceType	AltWeightedAvgOfferPx;
	///净值估值
	TZDQHFtdcPriceType	IOPV;
	///到期收益率
	TZDQHFtdcRatioType	YieldToMaturity;
	///权证执行总数量
	TZDQHFtdcLargeVolumeType	TotalWarrantExecQty;
	///权证跌停价格
	TZDQHFtdcPriceType	WarLowerPx;
	///权证涨停价格
	TZDQHFtdcPriceType	WarUpperPx;
	///买价深度
	TZDQHFtdcPriceLevelType	BidPriceLevel;
	///申买价一
	TZDQHFtdcPriceType	BidPx1;
	///申买量一
	TZDQHFtdcVolumeType	BidOrderQty1;
	///实际买总委托笔数一
	TZDQHFtdcVolumeType	BidNumOrder1;
	///申买价二
	TZDQHFtdcPriceType	BidPx2;
	///申买量二
	TZDQHFtdcVolumeType	BidOrderQty2;
	///实际买总委托笔数二
	TZDQHFtdcVolumeType	BidNumOrder2;
	///申买价三
	TZDQHFtdcPriceType	BidPx3;
	///申买量三
	TZDQHFtdcVolumeType	BidOrderQty3;
	///实际买总委托笔数三
	TZDQHFtdcVolumeType	BidNumOrder3;
	///申买价四
	TZDQHFtdcPriceType	BidPx4;
	///申买量四
	TZDQHFtdcVolumeType	BidOrderQty4;
	///实际买总委托笔数四
	TZDQHFtdcVolumeType	BidNumOrder4;
	///申买价五
	TZDQHFtdcPriceType	BidPx5;
	///申买量五
	TZDQHFtdcVolumeType	BidOrderQty5;
	///实际买总委托笔数五
	TZDQHFtdcVolumeType	BidNumOrder5;
	///申买价六
	TZDQHFtdcPriceType	BidPx6;
	///申买量六
	TZDQHFtdcVolumeType	BidOrderQty6;
	///实际买总委托笔数六
	TZDQHFtdcVolumeType	BidNumOrder6;
	///申买价七
	TZDQHFtdcPriceType	BidPx7;
	///申买量七
	TZDQHFtdcVolumeType	BidOrderQty7;
	///实际买总委托笔数七
	TZDQHFtdcVolumeType	BidNumOrder7;
	///申买价八
	TZDQHFtdcPriceType	BidPx8;
	///申买量八
	TZDQHFtdcVolumeType	BidOrderQty8;
	///实际买总委托笔数八
	TZDQHFtdcVolumeType	BidNumOrder8;
	///申买价九
	TZDQHFtdcPriceType	BidPx9;
	///申买量九
	TZDQHFtdcVolumeType	BidOrderQty9;
	///实际买总委托笔数九
	TZDQHFtdcVolumeType	BidNumOrder9;
	///申买价十
	TZDQHFtdcPriceType	BidPxA;
	///申买量十
	TZDQHFtdcVolumeType	BidOrderQtyA;
	///实际买总委托笔数十
	TZDQHFtdcVolumeType	BidNumOrderA;
	///卖价深度
	TZDQHFtdcPriceLevelType	OfferPriceLevel;
	///申卖价一
	TZDQHFtdcPriceType	OfferPx1;
	///申卖量一
	TZDQHFtdcVolumeType	OfferOrderQty1;
	///实际卖总委托笔数一
	TZDQHFtdcVolumeType	OfferNumOrder1;
	///申卖价二
	TZDQHFtdcPriceType	OfferPx2;
	///申卖量二
	TZDQHFtdcVolumeType	OfferOrderQty2;
	///实际卖总委托笔数二
	TZDQHFtdcVolumeType	OfferNumOrder2;
	///申卖价三
	TZDQHFtdcPriceType	OfferPx3;
	///申卖量三
	TZDQHFtdcVolumeType	OfferOrderQty3;
	///实际卖总委托笔数三
	TZDQHFtdcVolumeType	OfferNumOrder3;
	///申卖价四
	TZDQHFtdcPriceType	OfferPx4;
	///申卖量四
	TZDQHFtdcVolumeType	OfferOrderQty4;
	///实际卖总委托笔数四
	TZDQHFtdcVolumeType	OfferNumOrder4;
	///申卖价五
	TZDQHFtdcPriceType	OfferPx5;
	///申卖量五
	TZDQHFtdcVolumeType	OfferOrderQty5;
	///实际卖总委托笔数五
	TZDQHFtdcVolumeType	OfferNumOrder5;
	///申卖价六
	TZDQHFtdcPriceType	OfferPx6;
	///申卖量六
	TZDQHFtdcVolumeType	OfferOrderQty6;
	///实际卖总委托笔数六
	TZDQHFtdcVolumeType	OfferNumOrder6;
	///申卖价七
	TZDQHFtdcPriceType	OfferPx7;
	///申卖量七
	TZDQHFtdcVolumeType	OfferOrderQty7;
	///实际卖总委托笔数七
	TZDQHFtdcVolumeType	OfferNumOrder7;
	///申卖价八
	TZDQHFtdcPriceType	OfferPx8;
	///申卖量八
	TZDQHFtdcVolumeType	OfferOrderQty8;
	///实际卖总委托笔数八
	TZDQHFtdcVolumeType	OfferNumOrder8;
	///申卖价九
	TZDQHFtdcPriceType	OfferPx9;
	///申卖量九
	TZDQHFtdcVolumeType	OfferOrderQty9;
	///实际卖总委托笔数九
	TZDQHFtdcVolumeType	OfferNumOrder9;
	///申卖价十
	TZDQHFtdcPriceType	OfferPxA;
	///申卖量十
	TZDQHFtdcVolumeType	OfferOrderQtyA;
	///实际卖总委托笔数十
	TZDQHFtdcVolumeType	OfferNumOrderA;
};


///Level2指数行情
struct CLevel2ZDQHFtdcNGTSIndexField
{
	///交易日
	TZDQHFtdcDateType	TradingDay;
	///行情时间（秒）
	TZDQHFtdcTimeType	TimeStamp;
	///交易所代码
	TZDQHFtdcExchangeIDType	ExchangeID;
	///指数代码
	TZDQHFtdcStockIDType	SecurityID;
	///前收盘指数
	TZDQHFtdcIndexType	PreCloseIndex;
	///今开盘指数
	TZDQHFtdcIndexType	OpenIndex;
	///参与计算相应指数的成交金额（元）
	TZDQHFtdcMoneyType	TurnOver;
	///最高指数
	TZDQHFtdcIndexType	HighIndex;
	///最低指数
	TZDQHFtdcIndexType	LowIndex;
	///最新指数
	TZDQHFtdcIndexType	LastIndex;
	///今日收盘指数
	TZDQHFtdcIndexType	CloseIndex;
	///成交时间
	TZDQHFtdcTimeType	TradeTime;
	///参与计算相应指数的交易数量（手）
	TZDQHFtdcLargeVolumeType	TotalVolumeTraded;
};

#pragma  pack()
#endif

