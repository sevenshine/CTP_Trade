#include "CSocket.h"
//#include "CTradingSocket.h"
#include <stdlib.h>
#include <wtypes.h>
#include <comutil.h>

#pragma comment(lib, "comsuppw.lib")
#pragma comment(lib, "kernel32.lib")

using namespace std;

#define IP   "127.0.0.1"
#define PORT 10000
extern map<order_id_t,KOrderResponse> g_mapResponseOrders;

//测试
void TestReturnValue()
{
	TCP server;
	server.Connect(Address(IP, PORT));
	int socket=server.GetSocketId();
	int port=server.GetPort();
	string strIP=server.GetIp();
}

//测试CSocket.h中的SendOrder(KOrderRequest)和RecvOrder()函数,发送和接收一起测试
void TestSendRecv()
{
	TCP server;
	KOrderRequest orderRequest;
	map<order_id_t,KOrderResponse>  responseOrders;
	
	char* Account="it is Account";
	char* InstrumentID="it is InstrumentID"; 
	LONG Volumn=100;
	char* Type="OT_NONE";
	char* OffsetFlag="OCT_NONE";

	strcpy(orderRequest.account_id,Account);
	strcpy(orderRequest.instrument_id,InstrumentID);
	orderRequest.action=INSERT;
	orderRequest.volume_original=Volumn;
	int nType=atoi(Type);
	orderRequest.order_type=(KORDER_TYPE)nType;
	int nOffsetFlag=atoi(OffsetFlag);
	orderRequest.open_close=(KOPENCLOSE_TYPE)nOffsetFlag;

	server.Connect(Address(IP, PORT));

	cout << "sending ..." << endl;
	server.SendOrder(orderRequest);		//测试发送数据
	//responseOrders=server.GetRecvOrders();	//测试接收到的数据，放在Map容器里面

	/*线程函数测试  :直接在线程中加断点看是否有对象读入，成功*/
	//创建一个子线程，用于接收从服务器端发送过来的消息;初始化连接信息
	struct RecvMsgStruct *msgRecv = new struct RecvMsgStruct();
	msgRecv->clientSocket = server.GetSocketId();
	msgRecv->ServerAddr.sin_family = AF_INET;
	msgRecv->ServerAddr.sin_port = htons(server.GetPort());
	//GetIp()返回string类型,需要将string类型转到const char*  
	string strIP=server.GetIp();
	msgRecv->ServerAddr.sin_addr.s_addr = inet_addr(strIP.c_str());

	HANDLE hRevcThread = CreateThread(NULL,0,RecvOrderThread,(LPVOID)msgRecv,0,NULL);
	HANDLE hHeartBeatThread = CreateThread(NULL,0,RecvHeartBeatThread,(LPVOID)msgRecv,0,NULL);
	WaitForSingleObject(hRevcThread, INFINITE);
	WaitForSingleObject(hHeartBeatThread, INFINITE);
}

//TestReq(),TestReqOrder()测试数据传入KOrderRequest strOrderRequest结构体中，成功
void TestReqOrder(LPCTSTR InstrumentID, LONG Volumn,LPCTSTR Type,LPCTSTR OffsetFlag, LPCTSTR Account)
{
	KOrderRequest strOrderRequest;
	strcpy(strOrderRequest.account_id,Account);
	strcpy(strOrderRequest.instrument_id,InstrumentID);
	strOrderRequest.action=INSERT;
	strOrderRequest.volume_original=Volumn;
	int nType=atoi(Type);
	strOrderRequest.order_type=(KORDER_TYPE)nType;
	int nOffsetFlag=atoi(OffsetFlag);
	strOrderRequest.open_close=(KOPENCLOSE_TYPE)nOffsetFlag;
}
void TestReq()
{
	LPCTSTR Account="it is Account";
	LPCTSTR InstrumentID="it is InstrumentID"; 
	LONG Volumn=100;
	LPCTSTR Type="OT_NONE";
	LPCTSTR OffsetFlag="OCT_NONE";
	TestReqOrder(InstrumentID, Volumn, Type, OffsetFlag, Account);
}

//GetExecInfo(LONG OrderID, LPCTSTR Type)函数测试
void LPCTSTR_Char_BSTR( LPCTSTR Type)
{	
	int64_t price=100;
	char str[20]={NULL};
	int t=strcmp(Type,"Fills");
	itoa(price,str,10);
	BSTR bstrText = _com_util::ConvertStringToBSTR(str);
}
BSTR TestGetExecInfo(LPCTSTR Type)
{
	KOrderResponse  orderResponse;
	orderResponse.price_traded=1000;
	orderResponse.volume_original=2000;
	orderResponse.order_status=CANCELED;
	orderResponse.rsp_type=RT_CANCEL_REJECTED;

	//str用于保存中间数据，然后转换成BSTR返回
	char str[20]={NULL};
	if (!strcmp(Type,"Fills"))
	{
		itoa(orderResponse.price_traded,str,10);
	}
	else if(!strcmp(Type,"FilledQuantity"))
	{
		itoa(orderResponse.volume_original,str,10);
	}
	//(order_status)获取报单状态 “osRejectGW”报单拒绝 “osCanceled”撤单
	//“osFilled”成交 “osPending”已报 “osPartCanceled”部分撤单  "osPartFilled"部分成交
	//通过switch来判断选择相应的enum变量
	else if (!strcmp(Type,"GWStatus"))
	{
		switch(orderResponse.order_status)
		{
		case CANCELED:
			strcpy(str,"osCanceled");
			break;
		case ALL_TRADED:
			strcpy(str,"osFilled");
			break;
		}
	}
	else if (!strcmp(Type,"CanBeCanceled"))
	{
		if (orderResponse.rsp_type==RT_CANCEL_REJECTED)
		{
			strcpy(str,"1");
		}
		else
			strcpy(str,"0");		
	}

	BSTR returnText = _com_util::ConvertStringToBSTR(str);
	return returnText;
}

void ClientTest()
{
	TCP client;
	client.Connect(Address(IP, PORT));

	cout << "sending ..." << endl;
	client.RecvThreadOrder();

	//发送orderRequest
	KOrderRequest orderRequest;
	char* Account="it is Account";
	char* InstrumentID="it is InstrumentID"; 
	LONG Volumn=100;
	char* Type="OT_NONE";
	char* OffsetFlag="OCT_NONE";
	strcpy(orderRequest.account_id,Account);
	strcpy(orderRequest.instrument_id,InstrumentID);
	orderRequest.action=INSERT;
	orderRequest.volume_original=Volumn;
	int nType=atoi(Type);
	orderRequest.order_type=(KORDER_TYPE)nType;
	int nOffsetFlag=atoi(OffsetFlag);
	orderRequest.open_close=(KOPENCLOSE_TYPE)nOffsetFlag;

	while (1)
	{
		client.SendOrder(orderRequest);		//测试发送数据
		Sleep(4000);
		orderRequest.volume_original++;
	}

}


int main()
{
	ClientTest();

	system ("pause");
}