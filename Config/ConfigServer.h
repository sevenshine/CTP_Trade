#ifndef CONFIG_SERVER_H
#define CONFIG_SERVER_H

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>  
#include <libxml/parser.h>
#include <iostream>
#include "UserApiStruct.h"

class CServer 
{
public:
	void ParseDoc(string docname);
	void ParseServer(xmlDocPtr doc, xmlNodePtr cur);

	int GetBrokerId()
	{return m_nBrokerId; }
	vector<CServerField> GetServerField()
	{return m_vecServer; }
private:
	int m_nBrokerId;
	vector<CServerField> m_vecServer;
};

#endif 