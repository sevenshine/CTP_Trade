#pragma once

#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <winsock.h>
#include <io.h>
#include "TradingHeadField.h"
using namespace std;

/* 要使用winsock API，就要包含ws2_32.lib这个库 */
#pragma comment(lib, "ws2_32.lib")

typedef int SocketId;
typedef string Ip;
typedef unsigned int Port;
typedef int socklen_t;


//接收消息结构体
struct RecvMsgStruct
{
	SOCKET  clientSocket;
	struct sockaddr_in ServerAddr;
};
DWORD WINAPI RecvOrderThread(LPVOID lpParameter);
DWORD WINAPI RecvHeartBeatThread(LPVOID lpParameter);


//构造数据结构，初始化sockaddr_in数据，返回各个参数值
struct Address : protected sockaddr_in
{
private:
	void InitAddress(Ip, Port);

public:
	//两种不同参数的构造函数，分别调用InitAddress
	//默认IP，port初始化，"0.0.0.0", 0
	Address();
	//server端只传入port
	Address(Port);
	//传入IP，port初始化
	Address(Ip, Port);
	
	//返回IP
	Ip GetIp();
	Ip GetIp(Ip);
	//返回端口
	Port GetPort();
	Port GetPort(Port);
};

class CommonSocket
{
private:
	//初始化 Winsock.dll
	void InitSocket(void);

protected:
	SocketId m_nSocketId;
	int m_nSocketType;
	bool m_bOpened;
	bool m_bBinded;

public:
	//构造函数,初始化准备工作
	//Winsock.dll,flag初始化,建立socket
	CommonSocket(int);
	//析构函数clean socket
	~CommonSocket(void);

	//建立socket
	void Open(void);
	//关闭socket
	void Close(void);
};

class TCP : public CommonSocket
{
private:
	Address m_strAddress;
	//map保存接收到的数据
	map<order_id_t,KOrderResponse>  m_vecResponseOrders;
public:
	TCP();

	SocketId GetSocketId();
	Ip GetIp();
	Port GetPort();
	Address GetAddress();

	//server函数;传入监听端口和listeners
	void BindListenPort(Port port, unsigned int listeners);
	TCP AcceptClient();

	void ServerReceive();

	//接收后然后发送数据测试
	bool RecvOrder();

};


