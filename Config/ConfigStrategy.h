#ifndef CONFIG_STRATEGY_H
#define CONFIG_STRATEGY_H

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>  
#include <libxml/parser.h>
#include <iostream>
#include "UserApiStruct.h"

class CStrategy 
{
public:
	void ParseDoc(string docname,vector<CAccountField>* vec);
	void ParseStrategy(xmlDocPtr doc, xmlNodePtr cur, vector<CAccountField>* vec);
	void ParseRisk(xmlDocPtr doc, xmlNodePtr cur);
	void ParseInstreument(xmlDocPtr doc, xmlNodePtr cur);
	void ParseCode(xmlDocPtr doc, xmlNodePtr cur);
	vector<CStrategyField>& GetStrategyField()
	{return m_vecStrategy;}

private:
	CStrategyField m_strValue;
	vector<CStrategyField> m_vecStrategy;
};

#endif