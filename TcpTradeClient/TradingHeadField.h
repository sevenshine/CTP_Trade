#pragma once

#include <math.h>
#include <stdint.h>
#include <string.h>

typedef	char account_id_t[20];
typedef char instrument_id_t[16];
typedef int64_t volume_t;
typedef int64_t price_t;
typedef double value_t;
typedef int64_t timestamp_t;
typedef uint32_t order_id_t;
typedef int32_t error_id_t;


//0,1,2,3,4
enum KEXCHANGE_TYPE {
	ET_NONE = 0,
	CFFEX,
	SHFE,  /// not supported
	DCE,   /// not supported
	CZCE   /// not supported
};

enum KACTION_TYPE {
	AT_NONE = 0,
	INSERT,
	CANCEL
};

enum KORDER_SIDE {
	UNKNOWN = 0,
	BID,	//买
	ASK		//卖
};

enum KOPENCLOSE_TYPE {
	OCT_NONE = 0,
	OCT_OPEN,
	OCT_CLOSE
};

enum KSPECULATOR_TYPE {
	ST_NONE = 0,
	ST_SPECULATE,
	ST_HEDGE,     /// not supported 套利
	ST_ARBITRAGE  /// not supported 保利
};

enum KORDER_TYPE {
	OT_NONE = 0,
	OT_LIMIT,    
	OT_MARKET,   /// not supported
	OT_FAK
};

enum KORDER_STATUS {
	OS_NONE = 0,
	ALL_TRADED,          /// order has been complated traded
	CANCELED,            /// order has been canceled
	ON_MARKET,           /// order is still on market, including partically filled order
	PENDING,             /// some intermediate status used by kkm
	ON_MARKET_PENDING,   /// some intermediate status used by kkm
	OS_TRANSITION        /// some intermediate status used by kkm
};

enum KRESPONSE_TYPE {
	RT_NONE = 0,
	RT_ORDER,            /// normal order update
	RT_TRADE,            /// trade confirmation
	RT_INSERT_REJECTED,  /// insert reject
	RT_CANCEL_REJECTED   /// cancel reject
};

/// order request struct type
struct fa{
	char a;
	int b;
};

struct KOrderRequest{
	KOrderRequest() { }
	KOrderRequest(const KOrderRequest& req) {
		memcpy(this, &req, sizeof(KOrderRequest));
	}
	inline KOrderRequest& operator=(const KOrderRequest& req) {
		memcpy(this, &req, sizeof(KOrderRequest));
		return *this;
	}
	account_id_t account_id;     //增加
	instrument_id_t instrument_id;
	order_id_t orderid;			//委托号
	KACTION_TYPE action;		//订单状态，订单，撤单
	KORDER_SIDE side;
	KOPENCLOSE_TYPE open_close;		//打开关闭状态	
	KSPECULATOR_TYPE speculator;	//投机者
	KORDER_TYPE order_type;
	volume_t volume_original;
	price_t price_original;
};

/// order response struct type
/// this includes: Normal order update, Fill (Trade confirmation), Insert Reject, Cancel Reject
/// check KRESPONSE_TYPE rsp_type to find out what type of response it is;
/// check KORDER_STATUS order_status to find out current order status

struct KOrderResponse {
	KOrderResponse() { }
	KOrderResponse(const KOrderResponse& rsp) {
		memcpy(this, &rsp, sizeof(KOrderResponse));
	}
	inline KOrderResponse& operator=(const KOrderResponse& rsp) {
		memcpy(this, &rsp, sizeof(KOrderResponse));
		return *this;
	}
	account_id_t account_id;  
	instrument_id_t instrument_id;
	order_id_t orderid;
	error_id_t error_id;
	KRESPONSE_TYPE rsp_type;
	KORDER_STATUS order_status;
	KORDER_SIDE side;
	KOPENCLOSE_TYPE open_close;
	price_t price_original;
	volume_t volume_original;
	volume_t volume_remaining;
	price_t price_traded;
	volume_t volume_traded;
};