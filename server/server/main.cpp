#include "server.hpp"
#include <thread>

Server myserver;
thread readthread, writethread;

void readfunc() {
	myserver.UpdateRecv();
}
void writefunc() {
	myserver.UpdateSend();
	exit(0);
}

int main() {
	myserver.CreateServer();
	myserver.UpdateRecv();
	//readthread = thread(readfunc);
	//writethread = thread(writefunc);

	//readthread.join();
	//writethread.join();
}