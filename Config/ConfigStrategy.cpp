#include "ConfigStrategy.h"

void CStrategy::ParseRisk(xmlDocPtr doc, xmlNodePtr cur)
{
	CServerField accValue;
	xmlNodePtr propNodePtr = cur->xmlChildrenNode;	
	propNodePtr = propNodePtr->next;
	while(propNodePtr!=NULL)
	{
		//通过传递accValue，将结点信息push到vector
		if (!xmlStrcmp(propNodePtr->name,BAD_CAST "maxopennumber"))
		{
			// 从“double”转换到“float”，可能丢失数据??
			float open=atof((char*)xmlNodeGetContent(propNodePtr));
			m_strValue.m_mapRisk.insert(make_pair("maxopennumber",open));
		}	
		if (!xmlStrcmp(propNodePtr->name,BAD_CAST "maxlossfund"))
		{
			float open=atof((char*)xmlNodeGetContent(propNodePtr));
			m_strValue.m_mapRisk.insert(make_pair("maxlossfund",open));
		}	
		propNodePtr = propNodePtr->next;
	}
	return;
}

//instreument里进行字符串分割成多个合约
void CStrategy::ParseInstreument(xmlDocPtr doc, xmlNodePtr cur)
{
	char a[1024];
	char *ptr = NULL;
	strcpy(a,(char*)xmlNodeGetContent(cur));
	const char *b=",";
	char *p =strtok_s(a,b,&ptr);
	while(p!=NULL)
	{
		m_strValue.m_vecInstrument.push_back(p);
		p = strtok_s(NULL,b,&ptr);
	}	
	return;
}

void CStrategy::ParseCode(xmlDocPtr doc, xmlNodePtr cur)
{
	char a[50];
	strcpy(a,(char*)xmlNodeGetContent(cur));
	const char *b=",";
	char *p =strtok(a,b);
	while(p!=NULL)
	{
		m_strValue.m_vecCode.push_back(p);
		p = strtok(NULL,b);
	}	
	return;
}

void CStrategy::ParseStrategy(xmlDocPtr doc, xmlNodePtr cur, vector<CAccountField>* vec)
{	
	if (!xmlStrcmp(cur->properties->name, BAD_CAST "name"))
    {
		xmlChar* szAttr = xmlGetProp(cur,BAD_CAST "name");
		//xmlChar*转换为char[]
		strcpy(m_strValue.m_szStrategyName,(char*)szAttr);
		xmlFree(szAttr);
	}

	xmlNodePtr propNodePtr = cur->xmlChildrenNode;	
	propNodePtr = propNodePtr->next;
	while(propNodePtr!=NULL)
	{
		if (!xmlStrcmp(propNodePtr->name,BAD_CAST "account"))
		{
			strcpy(m_strValue.m_szUserId,(char*)xmlNodeGetContent(propNodePtr));
			int t=0;
			for (vector<CAccountField>::size_type i=0; i< vec->size(); i++)
			{
				if (!strcmp(m_strValue.m_szUserId,vec->at(i).m_szUserId))
				{
					t=1;
				}
			}
			if (!t)
			{
				//策略的账号不在账号配置中，错误处理函数
				//DoError(STRATEGY_CANNOT_FIND_ERROR);
				cerr<<"strategy user id "<<m_strValue.m_szUserId<<" is not in the account"<<endl;
			}
		}	
		if (!xmlStrcmp(propNodePtr->name,BAD_CAST "fund"))
		{
			m_strValue.m_fFund = atof((char*)xmlNodeGetContent(propNodePtr));
		}	

		if (!xmlStrcmp(propNodePtr->name,BAD_CAST "instreument"))
		{
			ParseInstreument(doc, propNodePtr);
		}

		if (!xmlStrcmp(propNodePtr->name,BAD_CAST "code"))
		{
			ParseCode(doc, propNodePtr);
		}

		if (!xmlStrcmp(propNodePtr->name,BAD_CAST "risk"))
		{
			ParseRisk(doc, propNodePtr);
		}
		propNodePtr = propNodePtr->next;
	}
	
	return ;
}

void CStrategy::ParseDoc(string docname, vector<CAccountField>* vec)
{
	xmlDocPtr doc;           //定义解析文档指针
    xmlNodePtr curNode;      //定义结点指针

	doc = xmlParseFile(docname.c_str()); //解析文件
    if (NULL == doc)
    { 
       fprintf(stderr,"Document not parsed successfully.\n");    
       return ;
    }

    curNode = xmlDocGetRootElement(doc); //确定文档根元素   
    if (NULL == curNode)
    {
       fprintf(stderr,"empty document\n");
       xmlFreeDoc(doc);
       return ;
    }
   
    if (xmlStrcmp(curNode->name, BAD_CAST "root"))	//即#define BAD_CAST (xmlChar *)
    {
       fprintf(stderr,"document of the wrong type, root node != root");
       xmlFreeDoc(doc);
       return ;
    }

    curNode = curNode->xmlChildrenNode;
    while(curNode != NULL)
    {
       //取出节点中的内容，ParseAccount()解析结点内容
	   if ((!xmlStrcmp(curNode->name, BAD_CAST "strategy")))
       {
           ParseStrategy(doc, curNode, vec);
		   //错误检测：strategy唯一性，日志打印
		   int t=1;
		   for (vector<string>::size_type i=0; i< m_vecStrategy.size(); i++)
		   {
			   if (!strcmp(m_vecStrategy[i].m_szStrategyName,m_strValue.m_szStrategyName))
			   {
				   cerr<<"strategy name "<<m_vecStrategy[i].m_szStrategyName<<" must not be the same"<<endl;
				   t=0;
			   }
		   }
		   if(t)
			   m_vecStrategy.push_back(m_strValue);

		   //中间变量m_strValue内的容器对象清空,防止重复输入结构体容器中
		   m_strValue.m_mapRisk.clear();
		   m_strValue.m_vecCode.clear();
		   m_strValue.m_vecInstrument.clear();
       }
       curNode = curNode->next;
    }    
    xmlFreeDoc(doc);

    return ;
}