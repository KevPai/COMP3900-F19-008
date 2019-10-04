#include <iostream>
#include <ws2tcpip.h> //gives functions for winsock
#include <stdio.h>
#pragma  comment (lib, "ws2_32.lib")

using namespace std;

int main(int argc, char* argv[]) { // we can pass in command line values

	//startup up winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2); //picks the version of winsock closes to the desired one
	int wsOK = WSAStartup(version, &data);
	if (wsOK != 0)
	{
		cout << "Cant Start Winsock" << wsOK;
		return 1;
	}
	
	//create a hint structure for the server
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(5000);

	inet_pton(AF_INET, "192.168.1.75", &serverHint.sin_addr);

	//socket creation
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
	//write out to that socket
	/*string s(argv[1]);
	int sendOK = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&serverHint, sizeof(serverHint));
	if (sendOK == SOCKET_ERROR) {
		cout << "THAT DIDNT ORK" << WSAGetLastError() << endl;
		return 1;
	}*/

	//memory for server info
	sockaddr_in server;
	int ser_length = sizeof(server);
	ZeroMemory(&server, ser_length);//server information
	//memory for message from client
	char buf[1024];
	char message[1024];
	char s[] = "received from server: ";
	while (true) {
		ZeroMemory(buf, 1024);
		printf("Enter message: ");
		fgets(message, 1024, stdin);
		sendto(out, message, strlen(message), 0, (sockaddr*)& serverHint, sizeof(serverHint));
		recvfrom(out, buf, 1024, 0, (sockaddr*)&server, &ser_length);
		puts(s);
		puts(buf);
	}
	//close socket
	closesocket(out);

	WSACleanup();
	return 0;
}



