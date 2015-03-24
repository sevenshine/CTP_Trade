#include "ConfigServer.h"


void CServer::ParseServer(xmlDocPtr doc, xmlNodePtr cur)
{
	//读取BrokerId数据
	if (!xmlStrcmp(cur->properties->name, BAD_CAST "brokerid"))
    {
		xmlChar* szAttr = xmlGetProp(cur,BAD_CAST "brokerid");
		//xmlChar*转换为int
		m_nBrokerId=atoi((char*)szAttr);
		xmlFree(szAttr);
	}

	CServerField serValue;
	xmlNodePtr propNodePtr = cur->xmlChildrenNode;	
	propNodePtr = propNodePtr->next;
	while(propNodePtr!=NULL)
	{
		if (!xmlStrcmp(propNodePtr->name,BAD_CAST "item"))
		{
			xmlAttrPtr attrPtr = propNodePtr->properties;
			while (attrPtr != NULL)
			{
				if (!xmlStrcmp(attrPtr->name, BAD_CAST "name"))
				{
					xmlChar* szAttr = xmlGetProp(propNodePtr,attrPtr->name);
					strcpy(serValue.m_szName,(char*)szAttr);
					xmlFree(szAttr);
				} 
				else if (!xmlStrcmp(attrPtr->name, BAD_CAST "tradefront"))
				{
					//trade
					xmlChar* szAttr = xmlGetProp(propNodePtr,attrPtr->name);
					strcpy(serValue.m_szTrade,(char*)szAttr);
					xmlFree(szAttr);
				}
				else 
				{
					//md
					xmlChar* szAttr = xmlGetProp(propNodePtr,attrPtr->name);
					strcpy(serValue.m_szMd,(char*)szAttr);
					xmlFree(szAttr);
				}
				attrPtr = attrPtr->next;
			}
			m_vecServer.push_back(serValue);
		}	
		propNodePtr = propNodePtr->next;
	}	
	return ;
}

void CServer::ParseDoc(string docname)
{
	//定义解析文档指针，xmlDoc是一个struct，保存了一个xml的相关信息；xmlDocPtr等于xmlDoc*
	xmlDocPtr doc;           
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
	   if ((!xmlStrcmp(curNode->name, BAD_CAST "server")))
       {
           ParseServer(doc, curNode);
       }
       curNode = curNode->next;
    }    
    xmlFreeDoc(doc);
    return ;
}