#include "CSocket.h"

void Address::InitAddress(Ip ip, Port port)
{
	sin_family = AF_INET;
	GetPort(port);		//sin_port = htons(port);
	GetIp(ip);		//sin_addr.s_addr = inet_addr ("127.0.0.1");
}

Address::Address()
{
	InitAddress("0.0.0.0", 0);
}

Address::Address(Port port)
{
	InitAddress("0.0.0.0", port);
}

Address::Address(Ip ip, Port port)
{
	InitAddress(ip, port);
}

Port Address::GetPort()
{
	return ntohs(sin_port);
}

Port Address::GetPort(Port port)
{
	sin_port = htons(port);
	return GetPort();
}

Ip Address::GetIp()
{
	return inet_ntoa(sin_addr);
}

Ip Address::GetIp(Ip ip)
{
	unsigned long address = inet_addr(ip.c_str());

	if (address == INADDR_NONE)
	{
		cerr<< "[ip] with [ip=" << ip << "] Invalid ip address provided";
	}
	else
	{
		sin_addr.S_un.S_addr = address;
	}

	return GetIp();
}


void CommonSocket::InitSocket()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("fail to init winsock.dll!\n");
		exit(-1);
	}
}

CommonSocket::CommonSocket(int socket_type)
{
	InitSocket();
	m_nSocketType = socket_type;
	m_bOpened = false;
	m_bBinded = false;
	Open();
}

CommonSocket::~CommonSocket()
{
	WSACleanup();
}


void CommonSocket::Open()
{
	if (!m_bOpened)
	{
		if ((m_nSocketId = socket(AF_INET, m_nSocketType, 0)) == -1)
			cerr<<"[open] Cannot create socket"<<endl;
		m_bOpened = true;
		m_bBinded = false;
	}
}

void CommonSocket::Close()
{
	if (m_bOpened)
	{
		closesocket(m_nSocketId);
		m_bOpened = false;
		m_bBinded = false;
	}
}

//构造函数，初始化列表
TCP::TCP() : CommonSocket(SOCK_STREAM)
{
}

SocketId TCP::GetSocketId()
{
	return m_nSocketId;
}

Ip TCP::GetIp()
{
	return m_strAddress.GetIp();
};

Port TCP::GetPort()
{
	return m_strAddress.GetPort();
};

Address TCP::GetAddress()
{
	return m_strAddress;
}

void TCP::BindListenPort(Port port, unsigned int listeners = 20)
{
	if (m_bBinded)	
	{
		cerr<<"[ListenPort] Socket already binded to a port, close the socket before to re-bind"<<endl;
		//exit(-1);
	}	
	if (!m_bOpened)	Open();	
	//address初始化
	Address address(port);
	if (bind(m_nSocketId, (sockaddr*)&address, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		cerr<<"[ListenPort] with [port=" << port << "] Cannot bind socket";
		//exit(-1);
	}
	m_bBinded = true;
	if (listen(m_nSocketId,listeners) == SOCKET_ERROR)
	{
		cerr<<"[listen_on_port] with [port=" << port << "] [listeners=" << listeners << "] Cannot bind socket";
		//exit(-1);
	}
	cout<<"Server "<<address.GetPort()<<" is listening..."<<endl;
}

TCP TCP::AcceptClient()
{
	//临时变量，返回有问题？？？
	TCP ret;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	if((ret.m_nSocketId = accept(m_nSocketId,(sockaddr*)&ret.m_strAddress, &addrlen))==INVALID_SOCKET)
	{
		cerr<<"[AcceptClient]cannot accept"<<endl;
		//exit(-1);
	}
	cout<<"Accept connection from "<<ret.GetIp()<<endl;
	m_bOpened=true;
	m_bBinded=true;
	return ret;
}

void TCP::ServerReceive()
{
	char buf[4096];
	while (1)
	{
		int bytes;
		//client对象传递正确，recv不能阻塞？？？
		if ((bytes = recv(m_nSocketId, buf, 1024, 0)) == SOCKET_ERROR)
		{
			printf("recv error!\n");
			//exit(-1);		//抛出异常检测哪里出错
		}
		buf[bytes] = '\0';
		printf("%s\n", buf);
		//printf("Message from %s:%s\n", GetIp(), buf);
		if (send(m_nSocketId, buf, bytes, 0) == SOCKET_ERROR)
		{
			printf("send error!\n");
			exit(-1);
		}
	}
}

bool TCP::RecvOrder()
{
	while (1)
	{
		int bytes;
		KOrderRequest orderTest;
		if ((bytes = recv(m_nSocketId, (char*)&orderTest, sizeof(orderTest), 0)) == SOCKET_ERROR)
		{
			printf("recv error!\n");
			exit(-1);
		}
		cout<<orderTest.account_id<<endl<<orderTest.instrument_id<<endl
			<<orderTest.action<<endl<<orderTest.volume_original<<endl
			<<orderTest.order_type<<endl<<orderTest.open_close<<endl<<endl;

		if (send(m_nSocketId, (char*)&orderTest, bytes, 0) == SOCKET_ERROR)
		{
			printf("send error!\n");
			exit(-1);
		}
	}
}

