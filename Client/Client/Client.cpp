#include "Client.h"


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
	out = socket(AF_INET, SOCK_DGRAM, 0);
	//serverHint.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(5000);
	inet_pton(AF_INET, "192.168.1.75", &serverHint.sin_addr);
	
	/*if (bind(out, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
		cout << "error " << WSAGetLastError() << endl;
	} */
	ser_length = sizeof(server);
	ZeroMemory(&server, ser_length);
}

void Client::updateReceive() {
	while (isClientRunning) {
		ZeroMemory(buf, BUFFSIZE);
		if ((bytesIn = recvfrom(out, buf, BUFFSIZE, 0, (sockaddr*)&server, &ser_length)) == ERROR) {
			perror("rip");
		}
		
		//cout << bytesIn << " " << WSAGetLastError() << endl;
		
		if (bytesIn != 0 && bytesIn != -1) {
			puts(buf);
		}
		
	}
}

void Client::updateSend() {
	char mes[BUFFSIZE];
	while (isClientRunning) {
		cin >> mes;
		cout << endl;
		sendMessage(mes, server);
	}

}

void Client::sendMessage(string message, sockaddr_in dest) {
	int n;
	n = sendto(out, message.c_str(), BUFFSIZE, 0, (sockaddr*)&serverHint, sizeof(serverHint));
	cout << n << endl;
}