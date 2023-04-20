#pragma once
#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

// Максимальный размер буфера 
#define MESSAGE_LENGTH 1024 

// Будем использовать этот номер порта
#define PORT 7777 

struct Chat_ServerTCP
{
	~Chat_ServerTCP();
	bool createSocket();
	void connectClient();
	void communication();
private:
	struct sockaddr_in serveraddress, client;
	socklen_t length;
	int socket_file_descriptor, connection, bind_status, connection_status;
	char message[MESSAGE_LENGTH];
};
 

