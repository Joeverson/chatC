#include "ClientSocket.h"

ClientSocket::ClientSocket(int port){
    //porta
    portno = port;
}

void ClientSocket::run(char *host){

    //func socket init
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0){
        cout << "ERROR opening socket" << endl;
    }

    server = gethostbyname(host);
    if (server == NULL) {
        cout << "ERROR, no such host" << endl;
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        cout << "ERROR connecting" << endl;
    }

    cout << "Please enter the message: " << endl;
    bzero(buffer,256);

    //escrevendo na variavel
    cin >> buffer;
    //fgets(buffer,255,stdin); //-> não sei que recebe a string mas..
    n = write(sockfd,buffer,strlen(buffer));

    if (n < 0){
        cout << "ERROR writing to socket" << endl;
    }

    //  | esta basicamente lendo a resposta do servidor
    //  v
    //bzero(buffer,256);

    //n = read(sockfd,buffer,255);
    //if (n < 0)
    //error("ERROR reading from socket");
    //printf("%s\n",buffer);
    close(sockfd);
}
