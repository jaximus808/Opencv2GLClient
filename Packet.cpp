#include"Packet.h"

Packet::Packet()
{
	packetLen = 0;
}

Packet::Packet(char packet[])
{
	packetLen = sizeof(packet);
	buffer.insert(buffer.begin(), &packet[0], &packet[packetLen-1]);
}

int Packet::readInt()
{
	
		int i = (buffer[readPos + 3] << 24) | (buffer[readPos + 2] << 16) | (buffer[readPos + 1] << 8) | (buffer[readPos]);
		readPos += 4;
		return i;
}

char* Packet::getCharBuffer()
{
	return bufferPacket;
}

void Packet::setBuffPacketToReadableBuffer()
{
	packetLen = sizeof(bufferPacket);
	buffer.insert(buffer.begin(), &bufferPacket[0], &bufferPacket[packetLen-1]);
	readPos = 0; 
}

void Packet::Write(int n)
{

	char bytes[sizeof(n)];
	std::copy(static_cast<const char*>(static_cast<const void*>(&n)),
		static_cast<const char*>(static_cast<const void*>(&n)) + sizeof(n),
		bytes);
	buffer.insert(buffer.end(), &bytes[0], &bytes[sizeof(n)]);

}

void Packet::printVector()
{
	for (int i = 0; i < buffer.size(); i++)
	{
		std::cout << buffer[i] << std::endl;
	}
}

char* Packet::readPacket()
{
	char* x = &buffer[0];
	return x;
}

int Packet::size()
{
	return buffer.size();
}

void Packet::setPacket(char packet[])
{
	packetLen = sizeof(packet);
	buffer.insert(buffer.begin(), &packet[0], &packet[packetLen-1]);
}

void Packet::clearPacket()
{
	buffer.clear();
	packetLen = 0; 
	readPos = 0; 
}

void Packet::setIp(char* ipSet)
{
	ip = ipSet;
}