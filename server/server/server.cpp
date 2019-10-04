#include "server.hpp"
#include <exception>



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
	puts("server created");
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
	puts("what");
		while (isServRunning) {
			ZeroMemory(buf, 1024);
			puts("running");
			if ((bytesIn = recvfrom(in, buf, BUFFSIZE, 0, (sockaddr*)& client, &clientLength)) == ERROR) {
				cout << "error receiving from client" << endl;
			};
	
			 
			//for (int i = 0; i < clients.size(); i++) {
				//if (clients[i].sin_addr.s_addr == client.sin_addr.s_addr) {
					clients.push_back(client);

				//}
			//}
			puts(buf);
			//sendto(in, buf, 1024, 0, (sockaddr*)& client, clientLength);
			//puts(buf);
			//HandleMessage();
			//BroadcastMessage(buf, client);
			BroadCastMessageToAll(buf);
		}
	
	
	puts("end of the receive");
}
/*
void Server::UpdateRecv() {

	while (isServRunning) {
		//puts("running");
		if (bytesIn = recvfrom(in, buf, BUFFSIZE, 0, (sockaddr*)& client, &clientLength) == -1) {
			//puts("running");
			return;
		}
		if (bytesIn > 0) {
			puts("running");
			sendto(in, buf, 1024, 0, (sockaddr*)& client, clientLength);
			//puts(buf);
			//HandleMessage();
			//BroadcastMessage(buf, (sockaddr*)&client);
		}
	}
}
*/

void Server::UpdateSend() {
	char mes[BUFFSIZE];
	while (isServRunning) {
		int messageLen = get_Input_Message(mes);
		if (messageLen == -1)
		{
			return;
		}
		else if (strcmp(mes, "/end") == 0)
		{
			BroadCastMessageToAll("Server shutdown");
			//shut the server
			isServRunning = false;
		}
		else
		{
			BroadcastMessage(mes, client);
		}
	}
}

void Server::HandleMessage() {
	//handling data from clients
	//decrypt the buffer
	//BroadcastMessage(buf,);

}

void Server::BroadcastMessage(string message, sockaddr_in dest) {
	clientLength = sizeof(dest);
	cout << message;
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

