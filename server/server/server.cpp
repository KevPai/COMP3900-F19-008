#include "server.hpp"
#include <exception>
using namespace std;


int get_Input_Message(char *message) {
	int ch = 0, len;
	fgets(message, BUFFSIZE, stdin);
	len = strlen(message);

	while ((ch = getchar()) != '\n' && ch != EOF)

		return len;
}

Server::Server() {
	WORD version = MAKEWORD(2,2);
	int wsOk;
	isServRunning = true;
		if( (wsOk = WSAStartup(version, &data)) != 0) {
			cout << "winsock couldn't be started" << endl;
		}
		
}

Server::~Server() {
}

void Server::CreateServer() {
	//creates a socket and sets it to UDP
	in = socket(AF_INET, SOCK_DGRAM, 0);
	serverHint.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //give me any addres, whatever the ip of the card
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(5000);
	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Cant bind socket! " << WSAGetLastError() << endl;
		exit(2);
	}
	clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);
	
}

void Server::UpdateRecv() {
	
	//setsockopt(in, SOL_SOCKET, SO_RCVTIMEO, buf, BUFFSIZE);

	while (isServRunning) 
	{
		ZeroMemory(buf, 1024);

		if ((bytesIn = recvfrom(in, buf, BUFFSIZE, 0, (sockaddr*)& client, &clientLength)) == ERROR)
		{
			cout << "error receiving from client" << endl;
		};

		//checks if client is in the client list
		int match = 0;
		for (int i = 0; i < clients.size(); i++) 
		{
			if (clients[i].sin_addr.s_addr == client.sin_addr.s_addr) 
			{
				match = 1;
				break;
			}
		}
		if (match == 0) {
			clients.push_back(client);
		}
		std::puts(buf);
		BroadCastMessageToAll(buf);
		
	}
	
	
}


void Server::UpdateSend() {
	char mes[BUFFSIZE];
	while (isServRunning)
	{
		
		cin >> mes;
		cout << endl;
		BroadCastMessageToAll(mes);
		
	};
}

void Server::HandleMessage() {
	//handling data from clients
	//decrypt the buffer
	//BroadcastMessage(buf,);

}

void Server::BroadcastMessage(string message, sockaddr_in dest) {
	clientLength = sizeof(dest);
	sendto(in, message.c_str(), 1024, 0, (sockaddr*)& dest, clientLength);
}

void Server::BroadCastMessageToAll(string message) {
	for (int i = 0; i < clients.size(); i++) {
		BroadcastMessage(message, clients[i]);
	}
}

bool Server::CompareClients(sockaddr_in c1, sockaddr_in c2) {
	
	return (c1.sin_addr.s_addr == c2.sin_addr.s_addr);
}

void Server::CloseServer() {
	closesocket(in);
	WSACleanup();
}

