#pragma once
#include <string>
#include "..\include\IAccount.h"
#include "..\include\ctp\ThostFtdcTraderApi.h"
#include "FtdcTradeSpi.h"
#include "..\include\femas\USTPFtdcTraderApi.h"
#include "UstpTradeSpi.h"
#include "..\include\ITrade.h"
#include <string>
#include <map>
#include "..\include\IConfig.h"
#include "..\common\ZDQHMutex.h"

using namespace std;
class CTrade : public ITrade
{
public:
	CTrade(const char* lpAccount);
	~CTrade(void);
	virtual void Release();
	void OnDisConnected();

	void SetMaxOrderID(unsigned long ulMaxOrderID);

	void OnLogined();
	void Login();

	void ReqFund();
	void OnFundRsp(CQuantInvestorAccountField* pRspData);

	void ReqInstrument();
	void OnInstrumentRsp(CQuantInstrumentField* pRspData);

	//手续费
	void ReqFee();
	void OnFeeRsp(CQuantFeeField* pRspData);

	//保证金
	void ReqMargin();
	void OnMarginRsp(CQuantMarginField* pRspData);

	void ReqPosition();
	void OnPositionRsp(CQuantPositionField* pRspData);

	void SetInvestID(string strInvestID) {m_strInvestID = strInvestID;}
	unsigned long GetOrderID();
	string   GetAccountID(){return m_strAccount;}
	CThostFtdcTraderApi* GetCTPTradeApi() {return m_pCTPTradeApi;}
	CUstpFtdcTraderApi*  GetUstpTradeApi() {return m_pUstpTradeApi;}

	CQuantMarginField* GetMarginField(const char* lpInstrumentID);
	CQuantFeeField* GetFeeField(const char* lpInstrumentID);
	CQuantInstrumentField* GetInstrument(const char* lpInstrumentID);
	virtual CQuantInvestorAccountField* GetAccountFund(){return &m_Fund;}

	virtual unsigned long ReqOrderInsert(const char* pIntrument,double dLimitPrice, int nOrderNum, TQuantBSDirection bs, TQuantOpenFlag of,TQuantHedgeType ht, TQuantPriceOrderType ordertype,TQuantTimeConditionType tcType);
	virtual unsigned long ReqOrderDelete(unsigned long ulOrderID, const char* pOrderSysID, const char* pInstrumengID);

	virtual bool IsReady(){return m_bReady;}
	void Ready(bool ready){m_bReady = ready;}

	//??
	void OnRtnOrder(CQuantOrderField* pOrder);
	void OnRtnTrade(CQuantTradeField* pTrade);
	void OnRspStatus(ETradeStatus status);

	void UpdatePosition(CQuantTradeField* pTrade);
	void UpdateAccountFund(CQuantTradeField* pTrade);

	//遍历m_mapFuncOrderRsp 将没出现过的OnRecvOrder放到map容器里
	//OnRecvOrder fOrderRsp是回调函数，回调函数放到map的value里
	virtual void RegOrderRsp(OnRecvOrder fOrderRsp, long lHandle);
	virtual void RegTradeRsp(OnRecvTrade fOrderRsp, long lHandle);
	virtual void RegTradeStatus(OnStatus fStatus, long lHandle);
private:
	bool   m_bReady;
	//<acconut, ctrade>
	string m_strAccount;
	string m_strInvestID;
	IAccount* m_pAccount;
	//飞马或者ctp柜台接口
	//ctp
	CThostFtdcTraderApi* m_pCTPTradeApi;
	CFtdcTradeSpi*       m_pCTPTradeSpi;
	//femas
	CUstpFtdcTraderApi* m_pUstpTradeApi;
	CUstpTradeSpi*	    m_pUstpTradeSpi;
	unsigned long       m_ulMaxLocalID;

	//config
	IConfig*			m_pConfig;
	CZDQHMutex          m_mutex;

	map<long, OnRecvOrder> m_mapFuncOrderRsp;
	map<long, OnRecvTrade> m_mapFuncTradeRsp;
	map<long, OnStatus> m_mapFuncStatusRsp;

	//资金
	CQuantInvestorAccountField  m_Fund;
	//保证金率
	map<string,CQuantMarginField*> m_mapMatgin;
	//费率
	map<string, CQuantFeeField*> m_mapFee;
	//持仓
	multimap<string,CQuantPositionField*> m_mapPosition;
public:
	static map<string, CTrade*> m_mapTrade;
	//合约
	static map<string, CQuantInstrumentField*> m_mapInstrument;
};

