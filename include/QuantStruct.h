#ifndef DEFINEH
#define  DEFINEH


#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_API_EXPORT
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT __declspec(dllimport)
#endif
#else
#define API_EXPORT 
#endif

//////////////////////////////////////////////////////////////////////////
//买卖方向
typedef char TQuantBSDirection;
#define QUANT_D_Buy     '0'
#define QUANT_D_Sell     '1'
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//开平方向
typedef char TQuantOpenFlag;
///开仓
#define QUANT_OF_Open '0'
///平仓
#define QUANT_OF_Close '1'
///强平
#define QUANT_OF_ForceClose '2'
///平今
#define QUANT_OF_CloseToday '3'
///平昨
#define QUANT_OF_CloseYesterday '4'
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//套保
typedef char TQuantHedgeType;
///投机
#define QUANT_HT_Speculation '1'
///套利
#define QUANT_HT_Arbitrage '2'
///套保
#define QUANT_HT_Hedge '3'

/////////////////////////////////////////////////////////////////////////
///有效期类型类型
typedef char TQuantTimeConditionType;
///立即完成，否则撤销
#define QUANT_TC_IOC '1'
///本节有效
#define QUANT_TC_GFS '2'
///当日有效
#define QUANT_TC_GFD '3'
///指定日期前有效
#define QUANT_TC_GTD '4'
///撤销前有效
#define QUANT_TC_GTC '5'
///集合竞价有效
#define QUANT_TC_GFA '6'

/////////////////////////////////////////////////////////////////////////
///报单类别
typedef char TQuantPriceOrderType;
///任意价
#define QUANT_OPT_AnyPrice '1'
///限价
#define QUANT_OPT_LimitPrice '2'

//////////////////////////////////////////////////////////////////////////
//报单状态
typedef char TQuantOrderStatusType;
///全部成交
#define QUANT_OST_AllTraded '0'
///部分成交还在队列中
#define QUANT_OST_PartTradedQueueing '1'
///部分成交不在队列中
#define QUANT_OST_PartTradedNotQueueing '2'
///未成交还在队列中
#define QUANT_OST_NoTradeQueueing '3'
///未成交不在队列中
#define QUANT_OST_NoTradeNotQueueing '4'
///撤单
#define QUANT_OST_Canceled '5'


//////////////////////////////////////////////////////////////////////////
///报单列别
typedef char TQuantActionType;
//报单
#define QUANT_AT_INSERT  '1'
//撤单
#define QUANT_AT_DELETE  '2'

//////////////////////////////////////////////////////////////////////////
///k线周期
typedef char TQuantDataPeriod;
//日线
#define QUANT_DATA_DAY   '1'
//60分钟
#define QUANT_DATA_HOUR  '2'
//30分钟
#define QUANT_DATA_30MIN  '3'
//15分钟
#define QUANT_DATA_15MIN  '4'
//1分钟
#define QUANT_DATA_1MIN  '5'
//tick
#define QUANT_DATA_TICK   '6'

///深度行情
struct CQuantDepthQuoteDataField
{
	///交易日
	char	TradingDay[9];
	///合约代码
	char	InstrumentID[31];
	///交易所代码
	char	ExchangeID[9];
	///合约在交易所的代码
	char	ExchangeInstID[9];
	///最新价
	double 	LastPrice;
	///上次结算价
	double	PreSettlementPrice;
	///昨收盘
	double	PreClosePrice;
	///昨持仓量
	double	PreOpenInterest;
	///今开盘
	double	OpenPrice;
	///最高价
	double	HighestPrice;
	///最低价
	double	LowestPrice;
	///数量
	int 	Volume;
	///成交金额
	double	Turnover;
	///持仓量
	double	OpenInterest;
	///今收盘
	double	ClosePrice;
	///本次结算价
	double	SettlementPrice;
	///涨停板价
	double	UpperLimitPrice;
	///跌停板价
	double	LowerLimitPrice;
	///昨虚实度
	double	PreDelta;
	///今虚实度
	double	CurrDelta;
	///最后修改时间
	char	UpdateTime[9];
	///最后修改毫秒
	int 	UpdateMillisec;
	///申买价一
	double	BidPrice1;
	///申买量一
	int 	BidVolume1;
	///申卖价一
	double	AskPrice1;
	///申卖量一
	int 	AskVolume1;
	///申买价二
	double	BidPrice2;
	///申买量二
	int 	BidVolume2;
	///申卖价二
	double	AskPrice2;
	///申卖量二
	int 	AskVolume2;
	///申买价三
	double	BidPrice3;
	///申买量三
	int 	BidVolume3;
	///申卖价三
	double	AskPrice3;
	///申卖量三
	int 	AskVolume3;
	///申买价四
	double	BidPrice4;
	///申买量四
	int 	BidVolume4;
	///申卖价四
	double	AskPrice4;
	///申卖量四
	int 	AskVolume4;
	///申买价五
	double	BidPrice5;
	///申买量五
	int 	BidVolume5;
	///申卖价五
	double	AskPrice5;
	///申卖量五
	int 	AskVolume5;
	///当日均价
	double	AveragePrice;
};

struct CQuantKLineDataField 
{
	//周期
    TQuantDataPeriod  KLinePeriod;
	///交易日
	char	TradingDay[9];
	//时间
	char    TradingTime[9];  
	///合约代码
	char	InstrumentID[31];
	///最新价
	double	LastPrice;
	///上次结算价
	double	PreSettlementPrice;
	///昨收盘
	double	PreClosePrice;
	///今开盘
	double	OpenPrice;
	///最高价
	double	HighestPrice;
	///最低价
	double	LowestPrice;
	///数量
	int Volume;
	///成交金额
	double	Turnover;
	///持仓量
	int businessAmount;
	///今收盘
	double	ClosePrice;
	///本次结算价
	double	SettlementPrice;
	///涨停板价
	double	UpperLimitPrice;
	///跌停板价
	double	LowerLimitPrice;
};

//报单
struct CQuantOrderField
{
	///经纪公司代码
	char	BrokerID[11];
	///投资者代码
	char	InvestorID[13];
	///客户代码
	char    UserID[20];	
	///合约代码
	char	InstrumentID[31];
	///报单引用
	unsigned long	OrderRef;
	///买卖方向
	TQuantBSDirection	Direction;
	///开平标志
	TQuantOpenFlag	    OffsetFlag;
	///投机套保标志
	TQuantHedgeType	    HedgeFlag;
	///价格
	double          	LimitPrice;
	///数量
	int	                VolumeTotalOriginal;
	///止损价
	double           	StopPrice;
	///交易日
	char				TradingDay[9];
	///报单编号
	char				OrderSysID[21];
	//报单状态
	TQuantOrderStatusType	OrderStatus;
	///今成交数量
	int					VolumeTraded;
	///报单日期
	char				InsertDate[9];
	///委托时间
	char				InsertTime[9];
	///最后修改时间
	char				UpdateTime[9];
	///撤销时间
	char				CancelTime[9];
	///操作类别
	TQuantActionType    ActionType;                
	///错误号
    int					ErrorID;
	///状态信息
	char				StatusMsg[81];
};

///成交
struct CQuantTradeField
{
	///经纪公司代码
	char		BrokerID[11];
	///投资者代码
	char	InvestorID[13];
	///合约代码
	char	InstrumentID[31];
	///报单引用
	unsigned long	OrderRef;
	///用户代码
	char	UserID[20];
	///成交编号
	char	TradeID[21];
	///买卖方向
	TQuantBSDirection	Direction;
	///开平标志
	TQuantOpenFlag	    OffsetFlag;
	///投机套保标志
	TQuantHedgeType	    HedgeFlag;
	///报单编号
	char				OrderSysID[21];
	///价格
	double	Price;
	///数量
	int	Volume;
	///成交时期
	char	TradeDate[9];
	///成交时间
	char	TradeTime[9];
	///交易日
	char	TradingDay[9];
	///结算编号
	int	SettlementID;
};

///投资者资金
struct CQuantInvestorAccountField
{
	///经纪公司代码
	char		BrokerID[11];
	///投资者代码
	char	InvestorID[13];
	///资金帐号
	char	AccountID[20];
	///上次结算准备金
	double	PreBalance;
	///入金金额
	double	Deposit;
	///出金金额
	double	Withdraw;
	///冻结的保证金
	double	FrozenMargin;
	///冻结手续费
	double	FrozenFee;
	///冻结权利金
	double	FrozenPremium;
	//手续费
	double Fee;
	///平仓盈亏
	double	CloseProfit;
	///持仓盈亏
	double	PositionProfit;
	///可用资金
	double	Available;
	///多头冻结的保证金
	double	LongFrozenMargin;
	///空头冻结的保证金
	double	ShortFrozenMargin;
	///多头占用保证金
	double	LongMargin;
	///空头占用保证金
	double	ShortMargin;
	///当日释放保证金
	double	ReleaseMargin;
	///动态权益
	double	DynamicRights;
	///今日出入金
	double	TodayInOut;
	///占用保证金
	double	Margin;
	///期权权利金收支
	double	Premium;
	///风险度
	double	Risk;
};
//持仓
struct CQuantPositionField
{
	///经纪公司代码
	char		BrokerID[11];
	///投资者代码
	char	InvestorID[13];
	///合约代码
	char	InstrumentID[31];
	///用户代码
	char	UserID[20];
	///买卖方向
	TQuantBSDirection	Direction;
	///投机套保标志
	TQuantHedgeType	HedgeFlag;
	///占用保证金
	double	UsedMargin;
	///今持仓量
	int	Position;
	///今日持仓成本
	double	PositionCost;
	//持仓均价
	double AvePrice;
	///昨持仓量
	int	YdPosition;
	///昨日持仓成本
	double	YdPositionCost;
	///冻结的保证金
	double	FrozenMargin;
	///开仓冻结持仓
	int	FrozenPosition;
	///平仓冻结持仓
	int	FrozenClosing;
	///冻结的权利金
	double	FrozenPremium;
};

//费率
struct CQuantFeeField
{
	//投资者
	char	InvestorID[13];
	///合约代码
	char	InstrumentID[31];
	///用户代码
	char	UserID[20];
	///开仓手续费按比例
	double	OpenFeeRate;
	///开仓手续费按手数
	double	OpenFeeAmt;
	///平仓手续费按比例
	double	OffsetFeeRate;
	///平仓手续费按手数
	double	OffsetFeeAmt;
	///平今仓手续费按比例
	double	OTFeeRate;
	///平今仓手续费按手数
	double	OTFeeAmt;
};

//保证金
struct CQuantMarginField
{
	///合约代码
	char	InstrumentID[31];
	///用户代码
	char	UserID[20];
	///多头占用保证金按比例
	double	LongMarginRate;
	///多头保证金按手数
	double	LongMarginAmt;
	///空头占用保证金按比例
	double	ShortMarginRate;
	///空头保证金按手数
	double	ShortMarginAmt;
};
//合约
struct CQuantInstrumentField
{
	///交易所代码
	char	ExchangeID[11];
	///品种名称
	char	ProductName[41];
	///合约代码
	char	InstrumentID[31];
	///合约名称
	char	InstrumentName[21];
	///交割年份
	int	DeliveryYear;
	///交割月
	int	DeliveryMonth;
	///限价单最大下单量
	int	MaxLimitOrderVolume;
	///限价单最小下单量
	int	MinLimitOrderVolume;
	///市价单最大下单量
	int	MaxMarketOrderVolume;
	///市价单最小下单量
	int	MinMarketOrderVolume;
	///数量乘数
	int	VolumeMultiple;
	///报价单位
	double	PriceTick;
	///币种
	char	Currency;
	///多头限仓
	int	LongPosLimit;
	///空头限仓
	int	ShortPosLimit;
	///跌停板价
	double	LowerLimitPrice;
	///涨停板价
	double	UpperLimitPrice;
	///昨结算
	double	PreSettlementPrice;
	///合约交易状态
	char	InstrumentStatus;
	///创建日
	char	CreateDate[9];
	///上市日
	char	OpenDate[9];
	///到期日
	char	ExpireDate[9];
	///开始交割日
	char	StartDelivDate[9];
	///最后交割日
	char	EndDelivDate[9];
	///挂牌基准价
	double	BasisPrice;
	///当前是否交易
	int	IsTrading;
};
#endif