//多态继承文件，对IConfig文件的继承
//通过CAccount m_account; CServer m_server; CStrategy m_strategy;实例化实现函数，达到实现和继承分离的功能

#ifndef CONFIG_CONFIG_H
#define CONFIG_CONFIG_H

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>  
#include <libxml/parser.h>
#include <algorithm>
#include "UserApiStruct.h"
#include "ConfigAccount.h"
#include "ConfigServer.h"
#include "ConfigStrategy.h"
#include "IConfig.h"

class CConfig : public IConfig
{
public:
	//构造函数初始化private成员
	CConfig()
	{
		//两个解析文件初始化
		m_account.ParseDoc("server.xml");
	    m_server.ParseDoc("server.xml");
		m_strategy.ParseDoc("strategy.xml",&m_account.GetAccountField());
	}	
	//Get函数实现配置文件的读取返回
	void GetAccount(vector<CAccountField> &vecAccountField);
	CAccountField* GetAccount(const char * name);
	int GetBrokerId();
	void GetServer(vector<CServerField> &vecServerField);

	void GetStrategy(vector<CStrategyField> & vecStrategyField);
	CStrategyField* GetStrategy(const char *name);
	void GetInstrument(const char *name, vector<string>& vecInstrument);
	void GetInstrument(vector<string>& vecInstrument);
	void GetCode(const char *name, vector<string>& vecCode);
	void GetCode(vector<string>& vecCode);

private:
	//类实例化，然后实现调用统一继承函数读取不同类的实现函数
	CAccount m_account;
	CServer m_server;
	CStrategy m_strategy;
};

#endif