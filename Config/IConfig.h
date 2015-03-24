//接口部分，IConfig基类，给其他模块提供接口
//总体功能：实现对配置文件server.xml和strategy.xml文件读取，并给其他模块提供接口

#ifndef ICONFIG_H
#define ICONFIG_H

#include "UserApiStruct.h"

#define STRATEGY_CANNOT_FIND_ERROR 1

using namespace std;

class IConfig {
public:
	//获取账号密码的配置
	virtual void GetAccount(vector<CAccountField> &vecAccountField)=0;

	//获取单个账号密码的配置
	virtual CAccountField* GetAccount(const char * name)=0;

	//获取Broker Id
	virtual int GetBrokerId()=0;

	//获取交易行情的配置
	virtual void GetServer(vector<CServerField> &vecServerField)=0;

	//获取策略配置
	virtual void GetStrategy(vector<CStrategyField> &vecStrategyField)=0;

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

//全局函数返回 IConfig*，隐藏继承的实现头文件，通过一个全局函数来提供接口文件
extern IConfig* GetConfig();

/*
extern "C"
{
	IConfig*  GetConfig();
};*/

#endif