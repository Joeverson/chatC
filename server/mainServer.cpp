#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;

class ServerSocket {
private:
    std::string nome;
    int n;
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];

public:
    // construtor
    ServerSocket(int port){
        portno = port;
    }

    /**
    metodo para rodar todo o socket server;
    **/
    void run (){
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

        cout << serv_addr.sin_addr.s_addr;

        serv_addr.sin_port = htons(portno);

        if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
            cout << "ERROR on binding" << endl;
        }

        cout << "Aguardando Conexoes..." << endl;

        do{
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
        }while(1);


        close(sockfd);
    }

};
int main(int argc, char const *argv[]) {

    ServerSocket sv(1232);//porta que vai ouvir
    sv.run();

    return 0;
}
