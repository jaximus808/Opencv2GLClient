#pragma once
#ifndef PACKET_H
#define PACKET_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include<winsock2.h>
#include<iostream>
#include <vector>

#include<glm/glm.hpp>

class Packet
{
public:
    Packet();
    Packet(char packet[]);

    int readInt();

    float readFloat();

    glm::vec3 readVector3();

    void Write(int n);

    void printVector();

    char* readPacket();

    int size();

    void clearPacket();

    void setPacket(char packet[]);

    char* getCharBuffer();

    void setBuffPacketToReadableBuffer();

    void setIp(char* ipSet);

private:
    char* bufferPacket;
    int readPos = 0;
    int packetLen;
    std::vector<char> buffer;
    char* ip;

};

#endif // !PACKET_H
