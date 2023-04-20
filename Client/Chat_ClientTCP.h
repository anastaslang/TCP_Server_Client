#pragma once

#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include <arpa/inet.h>

// Максимальный размер буфера 
#define MESSAGE_LENGTH 1024 

// Будем использовать этот номер порта
#define PORT 7777 

struct Chat_ClientTCP
{
	~Chat_ClientTCP();
	bool createSocket();
	void connectServer();
	void communication();
private:
	struct sockaddr_in serveraddress, client;
	int socket_file_descriptor, connection;
	char message[MESSAGE_LENGTH];
};
