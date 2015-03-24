#include "CSocket.h"
#include <stdlib.h>

using namespace std;

#define PORT 10000

void ServerTest()
{
	TCP server;
	server.BindListenPort(PORT,5);
	TCP client=server.AcceptClient();

	cout << "receiving ..." << endl;
	//client.ServerReceive();
	client.RecvOrder();
	//client.ReceiveFile("output.bmp");
}

int main()
{
	ServerTest();
	system ("pause");
}