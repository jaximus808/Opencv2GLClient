#include"NetworkManager.h"

NetworkManager::NetworkManager(const char* _ip, int _port)
{
	packet = Packet();
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		// Not ok! Get out quickly
		std::cout << "Can't start Winsock! " << wsOk<<std::endl;
		return;
	}
	ip = _ip;
	port = _port; 
	server.sin_family = AF_INET;
	server.sin_port = htons(_port);
	inet_pton(AF_INET, ip, &server.sin_addr);
	out = socket(AF_INET, SOCK_DGRAM, 0);	
}

//void NetworkManager::ConnectToMeta()
//{
//	Packet initalPacket;
//
//	initalPacket.Write(0);
//
//}

void NetworkManager::BeginThread(std::vector<Packet>* packetQueue, bool* listeningToServer)
{
	recieveThread = std::thread(&NetworkManager::ReceiveFromServer, this,  packetQueue, listeningToServer);
}

void NetworkManager::ReceiveFromServer(std::vector<Packet> *packetQueue, bool *listeningToServer)
{	
	in = socket(AF_INET, SOCK_DGRAM, 0);

	sockaddr_in clientSocket;
	clientSocket.sin_addr.S_un.S_addr = ADDR_ANY; 
	clientSocket.sin_family = AF_INET;
	clientSocket.sin_port = htons(8001);
	if (bind(in, (sockaddr*)&clientSocket, sizeof(clientSocket)) == SOCKET_ERROR)
	{
		std::cout << "Can't bind socket! " << WSAGetLastError() << std::endl;
		return;
	}
	sockaddr_in server;
	int serverLength = sizeof(server);

	Packet packetBuffer;
	char buf[1024];
	while (*listeningToServer)
	{
		std::cout << "listening" << std::endl;
		ZeroMemory(&server, serverLength); // Clear the client structure
		ZeroMemory(buf, 1024); // Clear the receive buffer
		int bytesIn = recvfrom(in, buf, 1024, 0, (sockaddr*)&server, &serverLength);
		if (bytesIn == SOCKET_ERROR)
		{
			std::cout << *listeningToServer << std::endl;
			std::cout << "Error receiving from client " << WSAGetLastError() << std::endl;
			continue;
		}
		std::cout << "data recieved " << std::endl;
		char clientIp[256];
		ZeroMemory(clientIp, 256);

		inet_ntop(AF_INET, &server.sin_addr, clientIp, 256);
		packetBuffer.clearPacket();
		packetBuffer.setPacket(buf);
		packetQueue->push_back(packetBuffer);
	}
	closesocket(in);

	// Shutdown winsock
	WSACleanup();
	std::cout << "UDP stream closed" << std::endl;
}

int NetworkManager::SendData(Packet packet)
{
	int returnData = sendto(out, packet.readPacket(), packet.size() + 1, 0, (sockaddr*)&server, sizeof(server));

	if (returnData == SOCKET_ERROR)
	{
		std::cout << "ERROR: "<< WSAGetLastError() << std::endl;
		return -1;
	}
	std::cout << "packet sent successfully"<<std::endl;
	return 1;

	
}

void NetworkManager::StopThread()
{
	closesocket(in);
	recieveThread.join();
}

void NetworkManager::CloseSocket()
{
	closesocket(out);

	WSACleanup();
}

