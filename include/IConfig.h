#ifndef ICONFIG_H
#define ICONFIG_H

#include "InnerStruct.h"

#define RISK_ID_MAXDEFICIT 0x0001

enum EServerType
{
	ctp,
	ustp
};

class IConfig {
public:
	virtual EServerType GetServerType() = 0;

	virtual void Release() = 0;

	//获取账号密码的配置
	virtual void GetAccount(vector<CAccountField> &vecAccountField)=0;

	//获取单个账号密码的配置
	virtual CAccountField* GetAccount(const char * name)=0;

	//获取Broker Id
	virtual const char* GetBrokerId()=0;

	//获取交易行情的配置
	virtual void GetServer(vector<CServerField> &vecServerField)=0;

	//获取策略配置
	virtual void GetStrategy(vector<CStrategyField> & vecStrategyField)=0;

	//获取单个策略配置
	virtual CStrategyField* GetStrategy(const char *name)=0;

	//获取单个策略期货合约配置
	virtual void GetInstrument(const char *name, vector<string>& vecInstrument)=0;

	//获取全部期货合约配置
	virtual void GetInstrument(vector<string>& vecInstrument)=0;

	//获取code配置
	virtual void GetCode(const char *name, vector<string>& vecCode)=0;

	//获取全部code配置
	virtual void GetCode(vector<string>& vecCode)=0;
};


extern "C"
{
	IConfig* _cdecl GetConfig();
};

#endif