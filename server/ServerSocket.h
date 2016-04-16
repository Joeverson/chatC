#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

class ServerSocket {
private:
    std::string nome;
    int n;
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];

public:
    ServerSocket(int port);
    void run ();
};
