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
	void createClient(string s);
	string updateReceive();
	string updatePos();
	void updateSend();
	void sendMessage(string message);
	void closeClient();
	bool isClientRunning;

	//server stuff
	void createServer();
	void HandleMessage();
	bool isserver();
	void BroadcastMessage(std::string message, sockaddr_in receiver);
	void BroadCastMessageToAll(string message);
	bool CompareClients(sockaddr_in c1, sockaddr_in c2);

private:
	WSADATA data;
	WORD version;
	sockaddr_in serverHint ,server;
	SOCKET out;
	int ser_length, bytesIn, clientLength;
	char buf[BUFFSIZE], remoteIP[INET6_ADDRSTRLEN];

	//server stuff
	SOCKET in;
	sockaddr_in client;
	vector<sockaddr_in>clients;
	bool isServer;
	bool isClient(sockaddr_in c1, sockaddr_in c2);
};