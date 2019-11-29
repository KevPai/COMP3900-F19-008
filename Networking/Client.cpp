#include "Client.h"
#include <conio.h>

Client::Client() {
	version = MAKEWORD(2, 2);
	int wsOK = WSAStartup(version, &data);
	isClientRunning = true;
	if (wsOK != 0) {
		cout << "Cant start winsock" << wsOK << endl;
	}
}
Client::~Client() {
}

void Client::createClient() {
	isServer = false;
	out = socket(AF_INET, SOCK_DGRAM, 0);
	//serverHint.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(5000);
	inet_pton(AF_INET, "142.232.159.144", &serverHint.sin_addr);
	
	/*if (bind(out, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
		cout << "error " << WSAGetLastError() << endl;
	}*/
	ser_length = sizeof(server);
	ZeroMemory(&server, ser_length);
}

void Client::createServer() {
	//creates a socket and sets it to UDP
	isServer = true;
	in = socket(AF_INET, SOCK_DGRAM, 0);
	serverHint.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //give me any addres, whatever the ip of the card
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(5000);
	if (bind(in, (sockaddr*)& serverHint, sizeof(serverHint)) == SOCKET_ERROR) //binds the socket to a port
	{
		cout << "Cant bind socket! " << WSAGetLastError() << endl;
		exit(2);
	}
	clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);
}



string Client::updateReceive() {
	setsockopt(in, SOL_SOCKET, SO_RCVTIMEO, buf, BUFFSIZE);
		if (isServer) 
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
			if (bytesIn != 0 && bytesIn != -1) {
				puts(buf);
				BroadCastMessageToAll(buf);
				return buf;
			}
		}
		else 
		{
			ZeroMemory(buf, BUFFSIZE);
			if ((bytesIn = recvfrom(out, buf, BUFFSIZE, 0, (sockaddr*)& server, &ser_length)) == ERROR) {
				perror("rip");
			}
			if (bytesIn != 0 && bytesIn != -1) {
				puts(buf);
				return buf;
			}
		}
		return NULL;
}


string Client::updatePos() {
	if (isServer) 
	{
		string s;
		//setsockopt(in, SOL_SOCKET, SO_RCVTIMEO, buf, BUFFSIZE);
		ZeroMemory(buf, BUFFSIZE);
		if ((bytesIn = recvfrom(in, buf, BUFFSIZE, 0, (sockaddr*)& client, &clientLength)) == ERROR) {
			perror("rip");
		}

		//cout << bytesIn << " " << WSAGetLastError() << endl;

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


		if (bytesIn != 0 && bytesIn != -1) {
			s = buf;
			puts(buf);
		}
		return s;
	}
	else 
	{
		string s;
		ZeroMemory(buf, BUFFSIZE);
		if ((bytesIn = recvfrom(out, buf, BUFFSIZE, 0, (sockaddr*)& server, &ser_length)) == ERROR) {
			perror("rip");
		}

		//cout << bytesIn << " " << WSAGetLastError() << endl;

		if (bytesIn != 0 && bytesIn != -1) {
			s = buf;
			puts(buf);
		}
		return s;
	}
}

void Client::updateSend() {
	char mes[BUFFSIZE];
	int c = 0;
	boolean press1;
	while (isClientRunning) {
		if (isServer) {
			cin >> mes;
			cout << endl;
			BroadCastMessageToAll(mes);
		}
		else {
			press1 = false;
			cin >> mes;
			cout << endl;
			sendMessage(mes);
		}
	}
}

void Client::HandleMessage() {


}

bool Client::isserver()
{
	return isServer;
}




void Client::BroadcastMessage(string message, sockaddr_in dest) {
	clientLength = sizeof(dest);
	sendto(in, message.c_str(), 1024, 0, (sockaddr*)& dest, clientLength);
}

void Client::BroadCastMessageToAll(string message) {
	for (int i = 0; i < clients.size(); i++) {
		BroadcastMessage(message, clients[i]);
	}
}

bool Client::CompareClients(sockaddr_in c1, sockaddr_in c2) {

	return (c1.sin_addr.s_addr == c2.sin_addr.s_addr);
}

void Client::sendMessage(string message) {
	int n;
	n = sendto(out, message.c_str(), BUFFSIZE, 0, (sockaddr*)&serverHint, sizeof(serverHint));
}

void Client::closeClient() {
	if (isServer) 
	{
		closesocket(in);
	}
	WSACleanup();
}