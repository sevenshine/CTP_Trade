#include "ConfigAccount.h"


void CAccount::ParseAccount(xmlDocPtr doc, xmlNodePtr cur)
{
	CAccountField accValue;
	xmlNodePtr propNodePtr = cur->xmlChildrenNode;	
	propNodePtr = propNodePtr->next;
	while(propNodePtr!=NULL)
	{
		//通过传递accValue，将结点信息push到vector
		if (!xmlStrcmp(propNodePtr->name,BAD_CAST "item"))
		{
			xmlAttrPtr attrPtr = propNodePtr->properties;
			while (attrPtr != NULL)
			{
				//查找带有属性userid的节点，对带属性文件的解析
				if (!xmlStrcmp(attrPtr->name, BAD_CAST "userid"))
				{
					xmlChar* szAttr = xmlGetProp(propNodePtr,attrPtr->name);
					strcpy(accValue.m_szUserId,(char*)szAttr);
					xmlFree(szAttr);
				} 
				else 
				{
					//读取pwd属性
					xmlChar* szAttr = xmlGetProp(propNodePtr,attrPtr->name);
					strcpy(accValue.m_szPwd,(char*)szAttr);
					xmlFree(szAttr);
				}
				attrPtr = attrPtr->next;
			}
			//错误检测：重复账号配置读取时日志打印，直接控制台上打印输出
			int t=1;
			for (vector<string>::size_type i=0; i< m_vecAccount.size(); i++)
			{
				if (!strcmp(m_vecAccount[i].m_szUserId,accValue.m_szUserId))
				{
					cerr<<"account user id "<<m_vecAccount[i].m_szUserId<<" must not be the same"<<endl;
					t=0;
				}
			}
			if(t)
				m_vecAccount.push_back(accValue);
		}	
		propNodePtr = propNodePtr->next;
	}
	return ;
}

void CAccount::ParseDoc(string docname)
{
	xmlDocPtr doc;           //定义解析文档指针
    xmlNodePtr curNode;      //定义结点指针

	doc = xmlParseFile(docname.c_str()); //解析文件
	//检查解析文档是否成功，如果不成功，libxml将指一个注册的错误并停止。
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
	   if ((!xmlStrcmp(curNode->name, BAD_CAST "account")))
       {
           ParseAccount(doc, curNode);
       }
       curNode = curNode->next;
    }    
    xmlFreeDoc(doc);
    return ;
}

