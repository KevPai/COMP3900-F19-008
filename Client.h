#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include <algorithm>
#pragma  comment (lib, "ws2_32.lib")
using namespace std;
#define port 5000
#define BUFFSIZE 1024
#pragma once

class Client
{
public:
	Client();
	~Client();
	void createClient();
	void runClient();
	void updateReceive();
	string updatePos();
	void updateSend();
	void sendMessage(string message);
	void closeClient();
	bool isClientRunning;
private:
	WSADATA data;
	WORD version;
	sockaddr_in serverHint , server;
	SOCKET out;
	int ser_length, bytesIn;
	char buf[BUFFSIZE], remoteIP[INET6_ADDRSTRLEN];
};