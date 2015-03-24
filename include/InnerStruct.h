#ifndef INNER_STRUCT_H
#define INNER_STRUCT_H

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
	char   m_szHisMd[30];
} CServerField;

typedef struct {
	bool    m_bBackTest;
	char	m_szStrategyName[20];
	char	m_szUserId[20];   
	float	m_fFund;	
	vector<string>	m_vecInstrument;
	vector<string>	m_vecCode;
	map<long,float> m_mapRisk;  
} CStrategyField;

#endif