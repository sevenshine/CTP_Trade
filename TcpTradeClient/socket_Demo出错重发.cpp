// WindowsSocketClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Winsock2.h>
#include <Windows.h>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "tinystr.h"
#include "tinyxml.h"
#pragma comment(lib,"Ws2_32.lib")

using namespace std;

#define PORT 8080
#define IP_ADDRESS "172.16.20.181"

#define LISTEN_PORT 8081
#define LISTEN_IP_ADDRESS "172.16.20.181"
//发送消息结构体
struct SendMsgStruct
{
    SOCKET clientSocket;
    string msg;
    struct sockaddr_in ServerAddr;
};

//接收消息结构体
struct RecvMsgStruct
{
    SOCKET  clientSocket;
    struct sockaddr_in ServerAddr;
};

//发送消息子线程
DWORD WINAPI SendThread(LPVOID lpParameter);

//接收消息子线程
DWORD WINAPI RecvThread(LPVOID lpParameter);

//去除字符串首尾空格
void trim(string &str);

//监听服务器的连接
DWORD WINAPI ListenServerThread(LPVOID lpParameter);

int _tmain(int argc, _TCHAR* argv[])
{
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN); 

    WSADATA  Ws;
     SOCKET ClientSocket,ServerSocket;
     struct sockaddr_in ServerAddr;
     int Ret = 0;
     int AddrLen = 0;
     HANDLE hThread = NULL;
     HANDLE hSendThread = NULL;
     HANDLE hRevcThread = NULL;
     HANDLE hListenThread = NULL;
     //The WSAStartup function initiates use of WS2_32.DLL by a process.
     //初始化 Windows Socket
     if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
     {
         cout<<"初始化 Socket 失败:"<<GetLastError()<<endl;
         return -1;
     }
 
     //创建 Socket
     ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
     if ( ClientSocket == INVALID_SOCKET )
     {
         cout<<"创建 Socket 失败:"<<GetLastError()<<endl;
         return -1;
     }
 
     ServerAddr.sin_family = AF_INET;
     ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
     ServerAddr.sin_port = htons(PORT);
    
     //设置ServerAddr中前8个字符为0x00
     memset(ServerAddr.sin_zero, 0x00, 8);

     Ret = connect(ClientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));

    if( Ret == SOCKET_ERROR )
    {
        cout<<"建立连接过程发生错误:"<<GetLastError()<<endl;
    }
    else
    {
        cout<<"连接建立成功"<<endl;
    }
    //创建一个子线程，监听从服务器过来的连接
    /*hListenThread = CreateThread(NULL, 0, ListenServerThread, NULL, 0, NULL);
    WaitForSingleObject(hListenThread,INFINITE);
    if( hListenThread == NULL )
    {
        cout<<"创建监听服务器对客户端的连接子线程失败"<<endl;
        system("pause");
        return -1;
    }*/
    //创建一个子线程，用于向服务器端发送消息
    struct SendMsgStruct *msgSend = new struct SendMsgStruct();
    msgSend->clientSocket = ClientSocket;
    msgSend->msg = "你好,Msg From Client";
    msgSend->ServerAddr = ServerAddr;
    //传递一个struct
    hSendThread = CreateThread(NULL, 0, SendThread, (LPVOID)msgSend, 0, NULL);
    WaitForSingleObject(hSendThread, INFINITE);

    if( hSendThread == NULL )
    {
        cout<<"创建发送消息子线程失败"<<endl;
        system("pause");
        return -1;
    }

    //创建一个子线程，用于接收从服务器端发送过来的消息
    struct RecvMsgStruct *msgRecv = new struct RecvMsgStruct();
    msgRecv->clientSocket = ClientSocket;
    msgRecv->ServerAddr = ServerAddr;
    //传递一个struct指针参数
    hRevcThread = CreateThread(NULL,0,RecvThread,(LPVOID)msgRecv,0,NULL);
    WaitForSingleObject(hRevcThread, INFINITE);

    if( hRevcThread == NULL )
    {
        cout<<"创建接收消息子线程失败"<<endl;
        system("pause");
        return -1;
    }

    //客户端输入exit，退出
    string  clientString ;
    do
    {
        getline(cin,clientString);

    }while( clientString != "exit" && clientString !="EXIT");
     closesocket(ClientSocket);
     WSACleanup();
    system("pause");
     return 0;
 }

//监听服务器连接子线程
DWORD WINAPI ListenServerThread(LPVOID lpParameter)
{
     //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
      //SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN); 

      //system("ipconfig /all >log.txt");
      //WSADATA 结构体主要包含了系统所支持的Winsock版本信息
      WSADATA  Ws;
      SOCKET ServerSocket, ClientSocket;
      //TCP/IP 套接字指定套接字的地址
      struct sockaddr_in LocalAddr, ServerAddr;
      int Ret = 0;
      int AddrLen = 0;
      HANDLE hThread = NULL;
  
      //初始化Winsock2.2.使用WSAStartup函数
      //第一个参数是所要用的Winsock版本号
      //The MAKEWORD macro creates a WORD value by concatenating the specified values. 
      //第二个参数就是WSADATA 结构体的指针。如果初始化成功则返回0
      //要注意任何WinsockAPI函数都必须在初始化后使用，包括错误检查函数
      if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
      {
          cout<<"初始化 Socket 失败:"<<GetLastError()<<endl;
          return 0;
      }
      //Create Socket
      ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      if ( ClientSocket == INVALID_SOCKET )
      {
          cout<<"创建客户端 Socket 失败:"<<GetLastError()<<endl;
          system("pause");
          return 0;
      }

      //the address of family specification
      LocalAddr.sin_family = AF_INET;

      //The inet_addr function converts a string containing an (Ipv4) Internet Protocol dotted address into a proper address for the IN_ADDR structure.
      LocalAddr.sin_addr.s_addr = inet_addr(LISTEN_IP_ADDRESS); 

      //The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).
      LocalAddr.sin_port = htons(LISTEN_PORT);

      //Sets buffers to a specified character.
      memset(LocalAddr.sin_zero, 0x00, 8);
  
      //Bind Socket,The bind function associates a local address with a socket.
      Ret = bind(ClientSocket, (struct sockaddr*)&LocalAddr, sizeof(LocalAddr));
      if ( Ret != 0 )
      {
          cout<<"绑定 Socket 失败:"<<GetLastError()<<endl;
          return 0;
      }
    
      //listen 命令套接字监听来自服务端的连接.
      //第二个参数是最大连接数.
      Ret = listen(ClientSocket, 10);
      if ( Ret != 0 )
      {
          cout<<"监听 Server Socket 失败:"<<GetLastError()<<endl;
          return 0;
      }
    
      cout<<"客户端已经启动，正在监听"<<endl;

          AddrLen = sizeof(ServerAddr);

          //The accept function permits an incoming connection attempt on a socket.
          //接收即将到来的客户端连接。
          ServerSocket = accept(ClientSocket, (struct sockaddr*)&ServerAddr, &AddrLen);
        
          if ( ClientSocket == INVALID_SOCKET )
          {
              cout<<"接收服务器端消息失败 :"<<GetLastError()<<endl;
              system("pause");
             // break;
          }
          else
          {
              //The inet_ntoa function converts an (Ipv4) Internet network address into a string in Internet standard dotted format.
              cout<<"\n服务器端连接 :"<<inet_ntoa(ServerAddr.sin_addr)<<":"<<ServerAddr.sin_port<<endl;
          }
     string cmdstr ; 
     do
     {
         getline(cin,cmdstr);
     }while(cmdstr != "exit" && cmdstr != "EXIT");
     closesocket(ClientSocket);
     //最初这个函数也许有些拥簇，现在保留它只是为了向后兼容。
     //但是调用它可能会更安全，可能某些实现会使用它来结束ws2_32.DLL
     WSACleanup();

    return 0;
}

//发送消息子线程
DWORD WINAPI SendThread(LPVOID lpParameter)
{    
    SendMsgStruct *myStruct = (SendMsgStruct *)lpParameter;
    SOCKET ClientSocket = myStruct->clientSocket;
    string SendMsg = myStruct->msg;
    struct sockaddr_in ServerAddr = myStruct->ServerAddr;

    while( true )
    {    
        int flag = 0;
        int bufSize = SendMsg.length();
        char * buf = const_cast<char*>(SendMsg.c_str());
        flag = send(ClientSocket, buf, bufSize, 0);

        //判断当前时候存在可用连接,如果没有，再次连接
        while( flag == -1 || flag == 0)
        {
            cout<<"准备重连"<<endl;
            //shutdown(ClientSocket,2);
            closesocket(ClientSocket);
            ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            int cunnectFlag = connect(ClientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
            
            if( cunnectFlag == SOCKET_ERROR )
            {
                cout<<"重连失败 :"<<GetLastError()<<endl;
                Sleep(5000);
                //cunnectFlag = connect(ClientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
            }
            else
            {
                break;
            }
        }

        //传输过程中报错
        //if( flag == SOCKET_ERROR )
        //{
        //        cout<<"消息发送过程中报错:"<<GetLastError()<<endl;
        //}
        //没有传输完成
        //else if( flag < bufSize )
        if( flag < bufSize )
        {
            flag = send(ClientSocket, buf, bufSize - flag, 0);
        }
        //传输成功
        else
        {
            cout<<"\n消息传输成功"<<endl;
        }

        //每5秒发送一次
        Sleep(5000);
    }
    return 0;
}

//接收消息子线程
DWORD WINAPI RecvThread(LPVOID lpParameter)
{

    RecvMsgStruct *recvStruct=(RecvMsgStruct *)lpParameter;
    SOCKET clientSocket = recvStruct->clientSocket;
    struct sockaddr_in ServerAddr = recvStruct->ServerAddr;
    char recvBuf[500]={"0"}; 
     int byteRecv = recv(clientSocket, recvBuf, 500, 0);
     int connectState;
     while( byteRecv == 0 )
     {
         //连接断开，重连
        cout<<"byteRecv == 0"<<endl;
        shutdown(clientSocket,2);
        //closesocket(ClientSocket);
        clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        connectState = connect(clientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));

        if( connectState == SOCKET_ERROR )
        {
            cout<<"建立连接发生错误,错误代码:"<<GetLastError()<<endl;
        }
        else
        {
            cout<<"-----------------------------------------------In"<<endl;
            byteRecv = recv(clientSocket, recvBuf, 500, 0);//建立连接后，重新获取一次消息
            recvBuf[byteRecv]=0;
        }
        Sleep(5000);
     }
    cout<<recvBuf<<endl;
    return 0;
}

//移除字符串首尾空格
void trim(string &str)
{
      str.erase(str.find_last_not_of(' ')+1,string::npos);
      str.erase(0,str.find_first_not_of(' '));
}