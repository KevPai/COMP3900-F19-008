#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <ws2tcpip.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <thread>
#pragma  comment (lib, "ws2_32.lib")
#define port 5000
#define BUFFSIZE 1024
using namespace std;
class Server {
public:
	Server();
	~Server();
	bool isServRunning;
	void CreateServer();
	void RunServer();
	void UpdateRecv();
	void UpdateSend();
	string updatePos();
	void HandleMessage();
	void BroadcastMessage(std::string message, sockaddr_in receiver);
	void BroadCastMessageToAll(string message);
	bool CompareClients(sockaddr_in c1, sockaddr_in c2);
	void CloseServer();
private:
	// select stuff
	fd_set master, temp;
	int fdmax; //tracks the largest socket
	//
	int servLength, bytesIn, clientLength;
	WSADATA data;
	WORD version;
	char buf[BUFFSIZE], remoteIP[INET6_ADDRSTRLEN];
	sockaddr_in serverHint, client;
	SOCKET in, maxfdp;
	vector<sockaddr_in> clients;
	bool isClient(sockaddr_in c1, sockaddr_in c2);


};