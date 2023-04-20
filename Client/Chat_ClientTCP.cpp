#include "Chat_ClientTCP.h"

Chat_ClientTCP::~Chat_ClientTCP()
{   
    // закрытие сокета, завершение соединения
    close(socket_file_descriptor);
}

bool Chat_ClientTCP::createSocket()
{
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        std::cout << "Не удалось создать сокет!" << std::endl;
        return false;
    }

    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
	return true;
}

void Chat_ClientTCP::connectServer()
{
    // Установим соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if (connection == -1) {
        std::cout << "Соединение с сервером не удалось!" << std::endl;
        exit(1);
    }
    std::cout << "Соединение с сервером в порядке..." << std::endl;
    communication();
}

void Chat_ClientTCP::communication()
{
    // Взаимодействие с сервером
    while (1) {
    
        // Ждем ответа от сервера
        bzero(message, sizeof(message));
        read(socket_file_descriptor, message, sizeof(message));
        std::cout << "Сообщение для Сервера: " << message << std::endl;
        
        bzero(message, sizeof(message));
        std::cout << "Сообщение для клиента: ";
        std::cin.getline(message, MESSAGE_LENGTH);
        if ((strncmp(message, "end", 3)) == 0) {
            write(socket_file_descriptor, message, sizeof(message));
            std::cout << "Клиент вышел" << std::endl;
            std::cout << "Нажмите любую клавишу для выхода..." << std::endl;
            std::cin.get();
            return;
        }
        ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if (bytes >= 0) {
            std::cout << "Данные успешно отправлены на сервер!" << std::endl;
        }

    }
}
