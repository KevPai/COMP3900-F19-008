#include "Client.h"
#include <thread>

Client myclient;
thread readthread, writethread;

void readfunc() {
	myclient.updateReceive();
}
void writefunc() {
	myclient.updateSend();
	exit(0);
}


int main() {
	myclient.createClient();
	readthread = thread(readfunc);
	writethread = thread(writefunc);
	readthread.join();
	writethread.join();
}