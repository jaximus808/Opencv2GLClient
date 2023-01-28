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

void NetworkManager::CloseSocket()
{
	closesocket(out);

	WSACleanup();
}

