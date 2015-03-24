/////////////////////////////////////////////////////////////////////////
///@system 新一代行情柜台系统
///@company 浙江中大期货有限公司
///@file ftdcfieldstruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
///20141202	杨鹏	创建该文件
/////////////////////////////////////////////////////////////////////////


#ifndef FTDC_FIELD_STRUCT_H
#define FTDC_FIELD_STRUCT_H

#include "ftdctypes.h"

//namespace ftdclib
//{
	///用户登录请求
	struct CFtdcReqUserLoginField
	{
		///交易日
		TFtdcDateType	TradingDay;
		///经纪公司代码
		TFtdcBrokerIDType	BrokerID;
		///用户代码
		TFtdcUserIDType	UserID;
		///密码
		TFtdcPasswordType	Password;
		///用户端产品信息
		TFtdcProductInfoType	UserProductInfo;
		///接口端产品信息
		TFtdcProductInfoType	InterfaceProductInfo;
		///协议信息
		TFtdcProtocolInfoType	ProtocolInfo;
		///Mac地址
		TFtdcMacAddressType	MacAddress;
		///动态密码
		TFtdcPasswordType	OneTimePassword;
		///终端IP地址
		TFtdcIPAddressType	ClientIPAddress;
	};

	///用户登录应答
	struct CFtdcRspUserLoginField
	{
		///交易日
		TFtdcDateType	TradingDay;
		///登录成功时间
		TFtdcTimeType	LoginTime;
		///经纪公司代码
		TFtdcBrokerIDType	BrokerID;
		///用户代码
		TFtdcUserIDType	 UserID;
		///交易系统名称
		TFtdcSystemNameType	SystemName;
		///前置编号
		TFtdcFrontIDType	FrontID;
		///会话编号
		TFtdcSessionIDType	SessionID;
		///最大报单引用
		TFtdcOrderRefType	MaxOrderRef;
		///上期所时间
		TFtdcTimeType	SHFETime;
		///大商所时间
		TFtdcTimeType	DCETime;
		///郑商所时间
		TFtdcTimeType	CZCETime;
		///中金所时间
		TFtdcTimeType	FFEXTime;
	};

	///用户登出请求
	struct CFtdcUserLogoutField
	{
		///经纪公司代码
		TFtdcBrokerIDType	BrokerID;
		///用户代码
		TFtdcUserIDType	UserID;
	};


	///客户端认证请求
	struct CFtdcReqAuthenticateField
	{
		///经纪公司代码
		TFtdcBrokerIDType	BrokerID;
		///用户代码
		TFtdcUserIDType	UserID;
		///用户端产品信息
		TFtdcProductInfoType	UserProductInfo;
		///认证码
		TFtdcAuthCodeType	AuthCode;
	};

	///客户端认证响应
	struct CFtdcRspAuthenticateField
	{
		///经纪公司代码
		TFtdcBrokerIDType	BrokerID;
		///用户代码
		TFtdcUserIDType	UserID;
		///用户端产品信息
		TFtdcProductInfoType	UserProductInfo;
	};

	///客户端认证信息
	struct CFtdcAuthenticationInfoField
	{
		///经纪公司代码
		TFtdcBrokerIDType	BrokerID;
		///用户代码
		TFtdcUserIDType	UserID;
		///用户端产品信息
		TFtdcProductInfoType	UserProductInfo;
		///认证信息
		TFtdcAuthInfoType	AuthInfo;
		///是否为认证结果
		TFtdcBoolType	IsResult;
	};

	///响应信息
	struct CFtdcRspInfoField
	{
		///错误代码
		TFtdcErrorIDType	ErrorID;
		///错误信息
		TFtdcErrorMsgType	ErrorMsg;
	};

	///产品
	struct CFtdcProductField
	{
		///产品代码
		TFtdcInstrumentIDType	ProductID;
		///产品名称
		TFtdcProductNameType	ProductName;
		///交易所代码
		TFtdcExchangeIDType	ExchangeID;
		///产品类型
		TFtdcProductClassType	ProductClass;
		///合约数量乘数
		TFtdcVolumeMultipleType	VolumeMultiple;
		///最小变动价位
		TFtdcPriceType	PriceTick;
		///市价单最大下单量
		TFtdcVolumeType	MaxMarketOrderVolume;
		///市价单最小下单量
		TFtdcVolumeType	MinMarketOrderVolume;
		///限价单最大下单量
		TFtdcVolumeType	MaxLimitOrderVolume;
		///限价单最小下单量
		TFtdcVolumeType	MinLimitOrderVolume;
		///持仓类型
		TFtdcPositionTypeType	PositionType;
		///持仓日期类型
		TFtdcPositionDateTypeType	PositionDateType;
	};

	///合约
	struct CFtdcInstrumentField
	{
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///交易所代码
		TFtdcExchangeIDType	ExchangeID;
		///合约名称
		TFtdcInstrumentNameType	InstrumentName;
		///合约在交易所的代码
		TFtdcExchangeInstIDType	ExchangeInstID;
		///产品代码
		TFtdcInstrumentIDType	ProductID;
		///产品类型
		TFtdcProductClassType	ProductClass;
		///交割年份
		TFtdcYearType	DeliveryYear;
		///交割月
		TFtdcMonthType	DeliveryMonth;
		///市价单最大下单量
		TFtdcVolumeType	MaxMarketOrderVolume;
		///市价单最小下单量
		TFtdcVolumeType	MinMarketOrderVolume;
		///限价单最大下单量
		TFtdcVolumeType	MaxLimitOrderVolume;
		///限价单最小下单量
		TFtdcVolumeType	MinLimitOrderVolume;
		///合约数量乘数
		TFtdcVolumeMultipleType	VolumeMultiple;
		///最小变动价位
		TFtdcPriceType	PriceTick;
		///创建日
		TFtdcDateType	CreateDate;
		///上市日
		TFtdcDateType	OpenDate;
		///到期日
		TFtdcDateType	ExpireDate;
		///开始交割日
		TFtdcDateType	StartDelivDate;
		///结束交割日
		TFtdcDateType	EndDelivDate;
		///合约生命周期状态
		TFtdcInstLifePhaseType	InstLifePhase;
		///当前是否交易
		TFtdcBoolType	IsTrading;
		///持仓类型
		TFtdcPositionTypeType	PositionType;
		///持仓日期类型
		TFtdcPositionDateTypeType	PositionDateType;
		///多头保证金率
		TFtdcRatioType	LongMarginRatio;
		///空头保证金率
		TFtdcRatioType	ShortMarginRatio;
	};


	///行情最新成交属性
	struct CFtdcMarketDataLastMatchField
	{
		///最新价
		TFtdcPriceType	LastPrice;
		///数量
		TFtdcVolumeType	Volume;
		///成交金额
		TFtdcMoneyType	Turnover;
		///持仓量
		TFtdcLargeVolumeType	OpenInterest;
	};

	///行情更新时间属性
	struct CFtdcMarketDataUpdateTimeField
	{
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///最后修改时间
		TFtdcTimeType	UpdateTime;
		///最后修改毫秒
		TFtdcMillisecType	UpdateMillisec;
	};

	///指定的合约
	struct CFtdcSpecificInstrumentField
	{
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
	};

	///后期添加Ｋ线查询域结构体

	//历史tick
	struct CFtdcReqQryHisTickField
	{
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///本次查询时间
		TFtdcStartQryTimeType LastQryTime;
		///查询条数
		TFtdcQryNumType QryNum;
	};

	struct CFtdcRspQryHisTickField 
	{
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
	};

	struct CFtdcHisTickField
	{
		///交易日
		TFtdcDateType	TradingDay;
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///交易所代码
		TFtdcExchangeIDType	ExchangeID;
		///最新价
		TFtdcPriceType	LastPrice;
		///上次结算价
		TFtdcPriceType	PreSettlementPrice;
		///昨收盘
		TFtdcPriceType	PreClosePrice;
		///昨持仓量
		TFtdcLargeVolumeType	PreOpenInterest;
		///今开盘
		TFtdcPriceType	OpenPrice;
		///最高价
		TFtdcPriceType	HighestPrice;
		///最低价
		TFtdcPriceType	LowestPrice;
		///数量
		TFtdcVolumeType	Volume;
		///成交金额
		TFtdcMoneyType	Turnover;
		///持仓量
		TFtdcVolumeType businessAmount;
		///今收盘
		TFtdcPriceType	ClosePrice;
		///本次结算价
		TFtdcPriceType	SettlementPrice;
		///涨停板价
		TFtdcPriceType	UpperLimitPrice;
		///跌停板价
		TFtdcPriceType	LowerLimitPrice;
		///最后修改时间
		TFtdcTimeType	UpdateTime;
		///最后修改毫秒
		TFtdcMillisecType	UpdateMillisec;
		///申买价一
		TFtdcPriceType	BidPrice1;
		///申买量一
		TFtdcVolumeType	BidVolume1;
		///申卖价一
		TFtdcPriceType	AskPrice1;
		///申卖量一
		TFtdcVolumeType	AskVolume1;
		///申买价二
		TFtdcPriceType	BidPrice2;
		///申买量二
		TFtdcVolumeType	BidVolume2;
		///申卖价二
		TFtdcPriceType	AskPrice2;
		///申卖量二
		TFtdcVolumeType	AskVolume2;
		///申买价三
		TFtdcPriceType	BidPrice3;
		///申买量三
		TFtdcVolumeType	BidVolume3;
		///申卖价三
		TFtdcPriceType	AskPrice3;
		///申卖量三
		TFtdcVolumeType	AskVolume3;
		///申买价四
		TFtdcPriceType	BidPrice4;
		///申买量四
		TFtdcVolumeType	BidVolume4;
		///申卖价四
		TFtdcPriceType	AskPrice4;
		///申卖量四
		TFtdcVolumeType	AskVolume4;
		///申买价五
		TFtdcPriceType	BidPrice5;
		///申买量五
		TFtdcVolumeType	BidVolume5;
		///申卖价五
		TFtdcPriceType	AskPrice5;
		///申卖量五
		TFtdcVolumeType	AskVolume5;
	};

	struct CFtdcReqQryKLineDayField 
	{
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///交易日
		TFtdcStartQryTimeType TradingDay;
		///查询条数
		TFtdcQryNumType QryNum;
	};
	
	struct CFtdcRspQryKLineDayField 
	{
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
	};

	struct CFtdcKLineDayField 
	{
		///交易日
		TFtdcDateType	TradingDay;
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///交易所代码
		TFtdcExchangeIDType	ExchangeID;
		///最新价
		TFtdcPriceType	LastPrice;
		///上次结算价
		TFtdcPriceType	PreSettlementPrice;
		///昨收盘
		TFtdcPriceType	PreClosePrice;
		///今开盘
		TFtdcPriceType	OpenPrice;
		///最高价
		TFtdcPriceType	HighestPrice;
		///最低价
		TFtdcPriceType	LowestPrice;
		///数量
		TFtdcVolumeType Volume;
		///成交金额
		TFtdcMoneyType	Turnover;
		///持仓量
		TFtdcVolumeType businessAmount;
		///今收盘
		TFtdcPriceType	ClosePrice;
		///本次结算价
		TFtdcPriceType	SettlementPrice;
		///涨停板价
		TFtdcPriceType	UpperLimitPrice;
		///跌停板价
		TFtdcPriceType	LowerLimitPrice;
		///最后修改时间
		//TFtdcTimeType	UpdateTime;
		///最后修改毫秒
		//TFtdcMillisecType	UpdateMillisec;
	};

	struct CFtdcReqQryKLine1MinuteField
	{
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///上次查询时间
		TFtdcStartQryTimeType StartQryKLine1MinuteTime;
		///查询条数
		TFtdcQryNumType QryNum;
	};

	struct CFtdcRspQryKLine1MinuteField 
	{
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
	};

	struct CFtdcKLine1MinuteField
	{
		///交易日
		TFtdcDateType	TradingDay;
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///交易所代码
		TFtdcExchangeIDType	ExchangeID;
		///最新价
		TFtdcPriceType	LastPrice;
		///上次结算价
		TFtdcPriceType	PreSettlementPrice;
		///昨收盘
		TFtdcPriceType	PreClosePrice;
		///今开盘
		TFtdcPriceType	OpenPrice;
		///最高价
		TFtdcPriceType	HighestPrice;
		///最低价
		TFtdcPriceType	LowestPrice;
		///数量
		TFtdcVolumeType Volume;
		///成交金额
		TFtdcMoneyType	Turnover;
		///持仓量
		TFtdcVolumeType businessAmount;
		///今收盘
		TFtdcPriceType	ClosePrice;
		///本次结算价
		TFtdcPriceType	SettlementPrice;
		///涨停板价
		TFtdcPriceType	UpperLimitPrice;
		///跌停板价
		TFtdcPriceType	LowerLimitPrice;
		///最后修改时间
		TFtdcTimeType	UpdateTime;
		///最后修改毫秒
		//TFtdcMillisecType	UpdateMillisec;
	};

//}//end namespace
	////重要入手结构体
	///深度行情
#ifdef VERSION2
	struct CFtdcDepthMarketDataField
	{
		//char test[2];
		///最后修改时间
		///最后修改时间
		TFtdcTimeType	UpdateTime;
		///最后修改毫秒
		TFtdcMillisecType UpdateMillisec;


	};
#else
	struct CFtdcDepthMarketDataField //LEVEL_5
	{
		///交易日
		TFtdcDateType	TradingDay;
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///交易所代码
		TFtdcExchangeIDType	ExchangeID;
		///合约在交易所的代码
		TFtdcExchangeInstIDType	ExchangeInstID;
		///最新价
		TFtdcPriceType	LastPrice;
		///上次结算价
		TFtdcPriceType	PreSettlementPrice;
		///昨收盘
		TFtdcPriceType	PreClosePrice;
		///昨持仓量
		TFtdcLargeVolumeType	PreOpenInterest;
		///今开盘
		TFtdcPriceType	OpenPrice;
		///最高价
		TFtdcPriceType	HighestPrice;
		///最低价
		TFtdcPriceType	LowestPrice;
		///数量
		TFtdcVolumeType	Volume;
		///成交金额
		TFtdcMoneyType	Turnover;
		///持仓量
		//TFtdcVolumeType businessAmount;
		TFtdcLargeVolumeType	OpenInterest; //yangpeng
		///今收盘
		TFtdcPriceType	ClosePrice;
		///本次结算价
		TFtdcPriceType	SettlementPrice;
		///涨停板价
		TFtdcPriceType	UpperLimitPrice;
		///跌停板价
		TFtdcPriceType	LowerLimitPrice;
		///昨虚实度
		TFtdcRatioType	PreDelta;
		///今虚实度
		TFtdcRatioType	CurrDelta;
		///最后修改时间
		TFtdcTimeType	UpdateTime;
		///最后修改毫秒
		TFtdcMillisecType	UpdateMillisec;
		///申买价一
		TFtdcPriceType	BidPrice1;
		///申买量一
		TFtdcVolumeType	BidVolume1;
		///申卖价一
		TFtdcPriceType	AskPrice1;
		///申卖量一
		TFtdcVolumeType	AskVolume1;
		///申买价二
		TFtdcPriceType	BidPrice2;
		///申买量二
		TFtdcVolumeType	BidVolume2;
		///申卖价二
		TFtdcPriceType	AskPrice2;
		///申卖量二
		TFtdcVolumeType	AskVolume2;
		///申买价三
		TFtdcPriceType	BidPrice3;
		///申买量三
		TFtdcVolumeType	BidVolume3;
		///申卖价三
		TFtdcPriceType	AskPrice3;
		///申卖量三
		TFtdcVolumeType	AskVolume3;
		///申买价四
		TFtdcPriceType	BidPrice4;
		///申买量四
		TFtdcVolumeType	BidVolume4;
		///申卖价四
		TFtdcPriceType	AskPrice4;
		///申卖量四
		TFtdcVolumeType	AskVolume4;
		///申买价五
		TFtdcPriceType	BidPrice5;
		///申买量五
		TFtdcVolumeType	BidVolume5;
		///申卖价五
		TFtdcPriceType	AskPrice5;
		///申卖量五
		TFtdcVolumeType	AskVolume5;
		///当日均价
		TFtdcPriceType	AveragePrice;
	};
#endif

struct CFtdcMarketDataField  //LEVEL_1
	{
		///交易日
		TFtdcDateType	TradingDay;
		///合约代码
		TFtdcInstrumentIDType	InstrumentID;
		///交易所代码
		TFtdcExchangeIDType	ExchangeID;
		///合约在交易所的代码
		TFtdcExchangeInstIDType	ExchangeInstID;
		///最新价
		TFtdcPriceType	LastPrice;
		///上次结算价
		TFtdcPriceType	PreSettlementPrice;
		///昨收盘
		TFtdcPriceType	PreClosePrice;
		///昨持仓量
		TFtdcLargeVolumeType	PreOpenInterest;
		///今开盘
		TFtdcPriceType	OpenPrice;
		///最高价
		TFtdcPriceType	HighestPrice;
		///最低价
		TFtdcPriceType	LowestPrice;
		///数量
		TFtdcVolumeType	Volume;
		///成交金额
		TFtdcMoneyType	Turnover;
		///持仓量
		//TFtdcVolumeType businessAmount;
		TFtdcLargeVolumeType	OpenInterest; //yangpeng
		///今收盘
		TFtdcPriceType	ClosePrice;
		///本次结算价
		TFtdcPriceType	SettlementPrice;
		///涨停板价
		TFtdcPriceType	UpperLimitPrice;
		///跌停板价
		TFtdcPriceType	LowerLimitPrice;
		///昨虚实度
		TFtdcRatioType	PreDelta;
		///今虚实度
		TFtdcRatioType	CurrDelta;
		///最后修改时间
		TFtdcTimeType	UpdateTime;
		///最后修改毫秒
		TFtdcMillisecType	UpdateMillisec;
		///申买价一
		TFtdcPriceType	BidPrice1;
		///申买量一
		TFtdcVolumeType	BidVolume1;
		///申卖价一
		TFtdcPriceType	AskPrice1;
		///申卖量一
		TFtdcVolumeType	AskVolume1;
	};

struct CFTDMarketDataUpdateTimeField
	{
		///\u5408\u7ea6\u4ee3\u7801
		TFtdcInstrumentIDType	InstrumentID;
		///\u6700\u540e\u4fee\u6539\u65f6\u95f4
		TFtdcTimeType	UpdateTime;
		///\u6700\u540e\u4fee\u6539\u6beb\u79d2
		TFtdcMillisecType	UpdateMillisec;
	};
struct CFTDMarketDataStaticField
	{
     	///\u4eca\u5f00\u76d8
		TFtdcPriceType	OpenPrice;
		///\u6700\u9ad8\u4ef7
		TFtdcPriceType	HighestPrice;
		///\u6700\u4f4e\u4ef7
		TFtdcPriceType	LowestPrice;
		///\u4eca\u6536\u76d8
		TFtdcPriceType	ClosePrice;
		///\u6da8\u505c\u677f\u4ef7
		TFtdcPriceType	UpperLimitPrice;
		///\u8dcc\u505c\u677f\u4ef7
		TFtdcPriceType	LowerLimitPrice;
        ///\u672c\u6b21\u7ed3\u7b97\u4ef7
		TFtdcPriceType	SettlementPrice;
	};
#if 1
struct CFTDMarketDataLastMatchField
	{
      	///\u6700\u65b0\u4ef7
		TFtdcPriceType	LastPrice;
		///\u6570\u91cf
		TFtdcVolumeType	Volume;
		///\u6210\u4ea4\u91d1\u989d
		TFtdcMoneyType	Turnover;
		///\u6301\u4ed3\u91cf
		TFtdcLargeVolumeType	OpenInterest;
	};
#endif

#if 0
struct CFTDMarketDataBestPriceField
	{
     	///\u7533\u4e70\u4ef7\u4e00
		TFtdcPriceType	BidPrice1;
		///\u7533\u4e70\u91cf\u4e00
		TFtdcVolumeType	BidVolume1;
		///\u7533\u5356\u4ef7\u4e00
		TFtdcPriceType	AskPrice1;
		///\u7533\u5356\u91cf\u4e00
		TFtdcVolumeType	AskVolume1;

	};
#endif

struct CFTDMarketDataBestPriceField   //字节对齐 yanpeng
{	
	///\u7533\u4e70\u91cf\u4e00
	TFtdcVolumeType	BidVolume1;
	///\u7533\u5356\u91cf\u4e00
	TFtdcVolumeType	AskVolume1;	
	///\u7533\u4e70\u4ef7\u4e00
	TFtdcPriceType	BidPrice1;
	///\u7533\u5356\u4ef7\u4e00
	TFtdcPriceType	AskPrice1;
};
struct CFTDMarketDataPreStaticField
	{
        ///\u4ea4\u6613\u65e5
		TFtdcDateType	TradingDay;
		///\u4e0a\u6b21\u7ed3\u7b97\u4ef7
		TFtdcPriceType	PreSettlementPrice;
		///\u6628\u6536\u76d8
		TFtdcPriceType	PreClosePrice;
		///\u6628\u6301\u4ed3\u91cf
		TFtdcLargeVolumeType	PreOpenInterest;
	};

#if 0
struct CFTDMarketData5BestPriceField
	{
		///\u7533\u4e70\u4ef7\u4e00
		TFtdcPriceType	BidPrice1;
		///\u7533\u4e70\u91cf\u4e00
		TFtdcVolumeType	BidVolume1;
		///\u7533\u5356\u4ef7\u4e00
		TFtdcPriceType	AskPrice1;
		///\u7533\u5356\u91cf\u4e00
		TFtdcVolumeType	AskVolume1;
		///\u7533\u4e70\u4ef7\u4e8c
		TFtdcPriceType	BidPrice2;
		///\u7533\u4e70\u91cf\u4e8c
		TFtdcVolumeType	BidVolume2;
		///\u7533\u5356\u4ef7\u4e8c
		TFtdcPriceType	AskPrice2;
		///\u7533\u5356\u91cf\u4e8c
		TFtdcVolumeType	AskVolume2;
		///\u7533\u4e70\u4ef7\u4e09
		TFtdcPriceType	BidPrice3;
		///\u7533\u4e70\u91cf\u4e09
		TFtdcVolumeType	BidVolume3;
		///\u7533\u5356\u4ef7\u4e09
		TFtdcPriceType	AskPrice3;
		///\u7533\u5356\u91cf\u4e09
		TFtdcVolumeType	AskVolume3;
		///\u7533\u4e70\u4ef7\u56db
		///申买价四
		TFtdcPriceType	BidPrice4;
		///申买量四
		TFtdcVolumeType	BidVolume4;
		///申卖价四
		TFtdcPriceType	AskPrice4;
		///申卖量四
		TFtdcVolumeType	AskVolume4;
		///申买价五
		TFtdcPriceType	BidPrice5;
		///申买量五
		TFtdcVolumeType	BidVolume5;
		///申卖价五
		TFtdcPriceType	AskPrice5;
		///申卖量五
		TFtdcVolumeType AskVolume5;
};
#endif
#if 1
struct CFTDMarketData5BestPriceField  //字节对齐 yanpeng
{
	TFtdcVolumeType	BidVolume1;	
	TFtdcVolumeType	AskVolume1;	
	TFtdcVolumeType	BidVolume2;	
	TFtdcVolumeType	AskVolume2;
	TFtdcVolumeType	BidVolume3;
	TFtdcVolumeType	AskVolume3;
	///申买量四
	TFtdcVolumeType	BidVolume4;
	///申卖量四
	TFtdcVolumeType	AskVolume4;
	///申买量五
	TFtdcVolumeType	BidVolume5;
	///申卖量五
	TFtdcVolumeType AskVolume5;

	TFtdcPriceType	BidPrice1;
	TFtdcPriceType	AskPrice1;
	TFtdcPriceType	BidPrice2;
	TFtdcPriceType	AskPrice2;
	TFtdcPriceType	BidPrice3;
	TFtdcPriceType	AskPrice3;
	TFtdcPriceType	BidPrice4;
	TFtdcPriceType	AskPrice4;
	TFtdcPriceType	BidPrice5;
	TFtdcPriceType	AskPrice5;
};
#endif

#endif