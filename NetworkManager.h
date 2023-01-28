#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include<iostream>
#include<WS2tcpip.h>
#include"Packet.h"
class NetworkManager
{
public: 
	NetworkManager(const char* _ip, int _port);


	int SendData(Packet packet);

	void CloseSocket();
private:
	WSADATA data; 
	WORD version = MAKEWORD(2, 2);
	sockaddr_in server;
	SOCKET out; 
	Packet packet; 


	const char* ip;
	int port; 
};


#endif // !NETWORKMANAGER_H
