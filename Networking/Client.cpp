#include "Client.h"
#include <conio.h>

Client::Client() {
	//responsible for starting up winsock
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
	//marks the client as a client and not a server
	isServer = false;

	//creates the profile for the client output
	out = socket(AF_INET, SOCK_DGRAM, 0);
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(5000);
	//hardcoded ip to connect
	inet_pton(AF_INET, "192.168.1.75", &serverHint.sin_addr);
	
	ser_length = sizeof(server);
	ZeroMemory(&server, ser_length);
}

void Client::createServer() {
	isServer = true;
	//creates a socket and sets it to UDP
	in = socket(AF_INET, SOCK_DGRAM, 0);
	serverHint.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  //gives me the addres, whatever the ip of the card
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(5000); //sets the port to 5000
	if (bind(in, (sockaddr*)& serverHint, sizeof(serverHint)) == SOCKET_ERROR) //binds the socket to a port
	{
		cout << "Cant bind socket! " << WSAGetLastError() << endl;
		exit(2);
	}
	clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);
}



string Client::updateReceive() {
	//sets the socket to non blocking
	setsockopt(in, SOL_SOCKET, SO_RCVTIMEO, buf, BUFFSIZE);
		if (isServer) 
		{
			ZeroMemory(buf, 1024);

			if ((bytesIn = recvfrom(in, buf, BUFFSIZE, 0, (sockaddr*)& client, &clientLength)) == ERROR)
			{
				cout << "error receiving from client" << endl;
			};

			//checks if client is in the client list, if so it doesn't add it to the client list
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
		ZeroMemory(buf, BUFFSIZE);
		if ((bytesIn = recvfrom(in, buf, BUFFSIZE, 0, (sockaddr*)& client, &clientLength)) == ERROR) {
			perror("rip");
		}

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



//server sending to a specific client
void Client::BroadcastMessage(string message, sockaddr_in dest) {
	clientLength = sizeof(dest);
	sendto(in, message.c_str(), 1024, 0, (sockaddr*)& dest, clientLength);
}

//server sending message to all client
void Client::BroadCastMessageToAll(string message) {
	for (int i = 0; i < clients.size(); i++) {
		BroadcastMessage(message, clients[i]);
	}
}

bool Client::CompareClients(sockaddr_in c1, sockaddr_in c2) {
	return (c1.sin_addr.s_addr == c2.sin_addr.s_addr);
}

//client sending message to server
void Client::sendMessage(string message) {
	int n;
	n = sendto(out, message.c_str(), BUFFSIZE, 0, (sockaddr*)&serverHint, sizeof(serverHint));
}

//closes the client and cleans up the winsock, if server also closes the socket
void Client::closeClient() {
	if (isServer) 
	{
		closesocket(in);
	}
	WSACleanup();
}