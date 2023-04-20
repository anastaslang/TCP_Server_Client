#include "Chat_ServerTCP.h"
#include <arpa/inet.h>

Chat_ServerTCP::~Chat_ServerTCP()
{
    // закрытие сокета, завершение соединения
    close(socket_file_descriptor);
}

bool Chat_ServerTCP::createSocket()
{
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
   
    if (socket_file_descriptor == -1) {
        std::cout << "Не удалось создать сокет!" << std::endl;
        return false;
    }
    
    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // Зададим номер порта для связи
    serveraddress.sin_port = htons(PORT);
    
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    
    // Привяжем сокет
    bind_status = bind(socket_file_descriptor, (struct sockaddr*)&serveraddress,
        sizeof(serveraddress));
    
    if (bind_status == -1) {
        std::cout << "Ошибка привязки сокета!" << std::endl;
        return false;;
    }
    return true;
}

void Chat_ServerTCP::connectClient()
{
    // Поставим сервер на прием данных 
    connection_status = listen(socket_file_descriptor, 5);
    if (connection_status == -1) {
        std::cout << "Сокет не может принимать новые соединения!" << std::endl;
        exit(1);
    }
    else {
        std::cout << "Сервер ожидает нового соединения..." << std::endl;
    }

    length = sizeof(client);
    connection = accept(socket_file_descriptor, (struct sockaddr*)&client, &length);
    
    if (connection == -1) {
        std::cout << "Сервер не может принять данные от клиента!" << std::endl;
        exit(1);
    }

    std::cout << "Сервер: получил соединение от" << inet_ntoa(client.sin_addr)  << " порт " << ntohs(client.sin_port) << std::endl;
    communication();
}

void Chat_ServerTCP::communication()
{
    // установление коммуникации
    while (1) {
        bzero(message, MESSAGE_LENGTH);
        std::cout << "Сообщение для Сервера: ";
        std::cin.getline(message, MESSAGE_LENGTH);
        ssize_t bytes = write(connection, message, sizeof(message));
        // Если передали >= 0  байт, значит пересылка прошла успешно
        if (bytes >= 0) {
            std::cout << "Данные успешно отправлены клиенту!" << std::endl;
        }

        bzero(message, MESSAGE_LENGTH);
        read(connection, message, sizeof(message));
        if (strncmp("end", message, 3) == 0) {
            std::cout << "Клиент вышел" << std::endl;
            std::cout << "Нажмите любую клавишу для выхода..." << std::endl;
            std::cin.get();
            return;
        }
        std::cout << "Сообщение для клиента: " << message << std::endl;
    }
}
