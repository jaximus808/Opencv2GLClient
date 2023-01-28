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

class Packet
{
public:
    Packet();
    Packet(char packet[]);

    int readInt();

    void Write(int n);

    void printVector();

    char* readPacket();

    int size();

private:
    char* bufferPacket;
    int readPos = 0;
    int packetLen;
    std::vector<char> buffer;

};

#endif // !PACKET_H
