#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

/**
    para poder usar essa classe deve ser herdada, e em seguida a classe que herda
    esta aqui deve implementar um metodo chamado run.. no caso um pointeiro da função
    *work();
**/
using namespace std;

class ThreadM{
    private :
        pthread_t thread;

    public :
        void run(){
            int result;

            //criando a thread
            result = pthread_create(&thread, NULL, _exec, (void *)this);

            if(result){
                cout << "Houve um erro ao criar a thread :(" << endl;
            }
        }

        void stop(){
          pthread_exit(NULL);
        }

        static void *_exec(void *instance) {
            //pegando a referencia da classe
            ThreadM *pThis = reinterpret_cast<ThreadM *>(instance);
            bool exitRet;
            //chamando o metodo run
            exitRet = pThis->work();

            pthread_exit(NULL);
    	}

        //metodo que vai ser implementado nas classes a baixo
        virtual bool work() = 0;
};

/*
###########################################################################
                                SERVER
###########################################################################
*/

class ServerSocket : public ThreadM{
private:
    int n;
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];

public:
    // construtor
    ServerSocket(int port){
        portno = port;
        run();
    }

    bool work(){
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

      do{
        listen(sockfd,5);

        clilen = sizeof(cli_addr);

        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0){
            cout << "ERROR on accept" << endl;
        }

        bzero(buffer,256);
        //malloc(sizeof(buffer));

        //capturando o dado que veio do cliente
        //n = read(newsockfd,buffer,255);
        fflush(stdin);
        if (read(newsockfd,buffer,sizeof(buffer)) < 0) {
            cout << "\n\n*ERROR: reading from socket ... :(" << endl;
        }
        fflush(stdin);
        cout << "\nhim: " << buffer;

        //            n = write(newsockfd,"I got your message",18);
        //            if (n < 0) error("ERROR writing to socket");
        close(newsockfd);
      }while(1);
      return 0;
    }

    void finish(){
        close(sockfd);
    }
};






/*
###########################################################################
                                Client
###########################################################################
*/

class ClientSocket{
private:
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[255];
    char *host;
public:
    ClientSocket(char *h,int port){
        portno = port;
        host = h;
        create(host);
        //send();
    }

    void create(char *host){

        //func socket init
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0){
            cout << "\n\n*ERROR: opening the socket .. :(" << endl;
            exit(-1);
        }

        server = gethostbyname(host);
        if (server == NULL) {
            cout << "\n\n*ERROR: no such host .. :(" << endl;
            exit(0);
        }

        malloc(sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;

        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);

        serv_addr.sin_port = htons(portno);
    }

    void send(){
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0){
            cout << "\n\n*ERROR: opening the socket .. :(" << endl;
            exit(-1);
        }

        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
            cout << "\n\n*ERROR - connecting with Server.. :'(" << endl;
            exit(-1);
        }

        cout << "\nyou: ";
        bzero(buffer,255);

        //escrevendo na variavel
        cin >> buffer;
        n = write(sockfd,buffer,strlen(buffer));

        if (n < 0){
            cout << "\n\n*ERROR: writing to socket .. :(" << endl;
            exit(-1);
        }

        /*/  | esta basicamente lendo a resposta do servidor
        //  v
        bzero(buffer,256);

        n = read(sockfd,buffer,255);

        if (n < 0)
          cout << "\n\n*ERROR: reading from socket ... :(" << endl;

        if( strlen(buffer) != 0){
          cout << "him: " << buffer << endl;
        }
        //printf("%s\n",buffer);*/
    }

    void header() {
      system("clear");
      cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"  << endl;
      cout << "                            CHAT BK7                                 "  << endl;
      cout << ":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"  << endl << endl;
    }


    void finish(){
        close(sockfd);
    };
};




/*
###########################################################################
                                MAIN
###########################################################################
*/

int main(int argc, char const *argv[]) {
    char host[225];
    int port;

    system("clear");
    
  //escrevendo na variavel
  cout << "\nAdicione o host: ";
  cin >> host;
  cout << "\nAdicione a porta: ";
  cin >> port;

  //configuração qu cria os servidor e fica ouvindo
  ServerSocket sv(port);//porta que vai ouvir
  sleep(1);//tempo para subir o servidor
  //configuração basica para conectar com o servidor.
  ClientSocket cli(host, port);
  cli.header();
  while(1){
    cli.send();
  }

    return 0;
}
