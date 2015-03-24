//具体的xml文件解析，解析Account字段

#ifndef CONFIG_API_H
#define CONFIG_API_H

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>  
#include <libxml/parser.h>
#include <iostream>
#include "UserApiStruct.h"

class CAccount 
{
public:
	//文档读取
	void ParseDoc(string docname);
	//具体字段读取
	void ParseAccount(xmlDocPtr doc, xmlNodePtr cur);
		
	//返回引用
	vector<CAccountField>& GetAccountField()
	{return m_vecAccount;}
private:
	vector<CAccountField> m_vecAccount;
};

#endif
