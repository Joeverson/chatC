#include "ServerSocket.h"

// construtor
ServerSocket::ServerSocket(int port){
    portno = port;
}

/**
metodo para rodar todo o socket server;
**/
void ServerSocket::run (){
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0){
        std::cout << "ERROR opening socket" << endl;
    }


    //bzero((char *) &serv_addr, sizeof(serv_addr));
    malloc(sizeof(serv_addr));

    //Porta que irá ouvir
    //portno = ;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        cout << "ERROR on binding" << endl;
    }

    cout << "Aguardando Conexoes..." << endl;
    listen(sockfd,5);

    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0){
        cout << "ERROR on accept" << endl;
    }

    //bzero(buffer,256);
    malloc(256);

    //capturando o dado que veio do cliente
    //n = read(newsockfd,buffer,255);
    if (read(newsockfd,buffer,255) < 0) {
        cout << "ERROR reading from socket" << endl;
    }

    cout << "Friend say - "<< buffer << endl;

    //            n = write(newsockfd,"I got your message",18);
    //            if (n < 0) error("ERROR writing to socket");
    close(newsockfd);
    close(sockfd);
}
