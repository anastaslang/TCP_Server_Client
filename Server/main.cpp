#include "Chat_ServerTCP.h"

int main() {

    Chat_ServerTCP server;
    if (server.createSocket())
    {
        server.connectClient();
    }

    return 0;
}

