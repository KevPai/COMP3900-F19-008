#include <iostream>
#include <ws2tcpip.h> //gives functions for winsock

#pragma  comment (lib, "ws2_32.lib")
//port for the game session
#define gameport 50001
//port for joining the game
#define port 50000
#define ip 127.0.0.1
using namespace std;
/*
int main() {

	//startup up winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2); //picks the version of winsock closes to the desired one
	int wsOK = WSAStartup(version, &data);
	if (wsOK != 0) 
	{
		cout << "Cant Start Winsock" << wsOK;
	}
	//bind socket to ip address and port
	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
	
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //give me any addres, whatever the ip of the card
	serverHint.sin_family = AF_INET;
	//message port
	serverHint.sin_port = htons(5000); //convert from little to beg endian  htons = Host to network tons short

	if (bind(in, (sockaddr*)& serverHint, sizeof(serverHint)) == SOCKET_ERROR) 
	{
		cout << "Cant bind socket! " << WSAGetLastError() << endl;
		return 1;
	}


	// memory for client info
	sockaddr_in client;
	int clientLength = sizeof(client);
	ZeroMemory(&client, clientLength); //client information

	sockaddr_in Clients[3];
	for (int i = 0; i < 3; i++) {
		ZeroMemory(&Clients[i], clientLength);
	}
	//memory for message
	char buff[1024];

	//connecting clients to the server


	//enter a loop
	while (true) {
		//buffer where message is received
		ZeroMemory(buff, 1024); //buffer is zeroed everytime to receive from remote client
		//wait for message
		int bytesIn = recvfrom(in, buff, 1024, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == ERROR) {
			cout << "Error receiving from client" << WSAGetLastError() << endl;
		}
		//display message and client info
		char clientIp[256];
		ZeroMemory(clientIp, 256);
		//inet ntop pointer 
		inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
		cout << "Message recv from" << clientIp << " : " << buff << endl;
		
		sendto(in, buff, 1024, 0, (sockaddr*)&client, clientLength); //echoes message back to clients
	}
	//close socket
	closesocket(in);
	//shutdown winsock
	WSACleanup();

	return 0;
} */