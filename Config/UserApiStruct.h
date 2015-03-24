//config文件的数据结构设计，根据文件需求来确定数据结构

#ifndef USER_API_STRUCT_H
#define USER_API_STRUCT_H

#include <string>
#include <vector>
#include <map>

using namespace std;

typedef struct {
     char   m_szUserId[20];  
     char	m_szPwd[20]; 
} CAccountField;

typedef struct {
	 char   m_szName[20];
     char	m_szTrade[30];
	 char   m_szMd[30];  
} CServerField;

typedef struct {
     char	m_szStrategyName[20];
     char	m_szUserId[20];   
     float	m_fFund;	
     vector<string>	m_vecInstrument;
	 vector<string>	m_vecCode;
     map<string,float> m_mapRisk;  
} CStrategyField;

#endif USER_API_STRUCT_H