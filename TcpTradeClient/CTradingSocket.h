#pragma once
#include "CSocket.h"

class CTradingSocket 
{
public:
	CTradingSocket()
	{
		//构造函数初始化成员变量数据，获取接收端Map数据
		m_CTtcp.RecvThreadOrder();
	}
	~CTradingSocket(){}
	/*  报单
	/* @Param
	/*  InstrumentID  合约
	/*  Direciton     买卖方向 “osdBuy” 买  "osdSell" 卖
	/*	Volumn	      数量
	/*	Type	      报单类型  "otStopLimit" 止损单   "otLimit"限价单(只支持限价单)
	/*  LimitPrice    报单价格
	/*  StopPrice     止损价格
	/*  Duration      有效期类型 “odGoodTillCanceled” 撤销前有效    "odDay" 当天有效	 "odIOC" 立即成交否则撤销
	/*  Transit_Now   True 马上发送
	/*  OffsetFlag    开平仓标志 "ofOpen" 开仓  "ofClose" 平仓  "ofForceClose"强平  "ofCloseToday"平今  "ofCloseYesterday"平昨   
	/*  HedgeFlag	  套保标志  "ohSpeculation"投机   "ohArbitrage"套利   "ohHedge"套保	
	/*  Account       帐号
	/* @Return
	/*  成功返回委托号，否则返回0
	*/
	LONG ReqOrder(LPCTSTR InstrumentID, LPCTSTR Direciton, LONG Volumn,LPCTSTR Type, DOUBLE LimitPrice,DOUBLE StopPrice,LPCTSTR Duration,BOOL Transit_Now,  LPCTSTR OffsetFlag, LPCTSTR HedgeFlag, LPCTSTR Account);
	
	/* 撤单
	/* @Param
	/*  orderID       报单ID
	/* @Return
	/*  成功1  0失败
	*/
	SHORT Cancel(LONG orderID);
	
	/* 获取报单信息
	/* @Param
	/*  orderID       报单ID
	/*  Type :         类型
	/*        Fills				   (price_traded)获取成交均价       
	/*        FilledQuantity	(volume_original)获取成交数量
	/*		  GWStatus			   (order_status)获取报单状态 “osRejectGW”报单拒绝 “osCanceled”撤单  “osFilled”成交 “osPending”已报 “osPartCanceled”部分撤单  "osPartFilled"部分成交
	/*        CanBeCanceled			   (rsp_type)判断是否能撤单   “1”可撤 “0”不能撤
	/* @Return
	/*  
	*/
	//LPCTSTR即char*，BSTR即WCHAR*
	BSTR GetExecInfo(LONG OrderID, LPCTSTR Type);

private:
	TCP m_CTtcp;
};