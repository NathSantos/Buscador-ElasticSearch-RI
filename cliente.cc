// Exemplo criado por Edleno Silva de Moura em 23/03/2015 
// Feito para aulas de lab de programacao


#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>



#define BUFFER_SIZE 32768

#define PORTNUM 5000
//#define SERV_HOST_ADDR "72.07.47.44" // exemplo de endereco IP
//#define SERV_HOST_ADDR "127.0.0.1" // AQUI O ENDERECO DO SERVIDOR!!!


using namespace std;


int main(int argc, char **argv)
{
  char resp[BUFFER_SIZE];
  int sockfd;
  struct sockaddr_in serv_addr;
  char consulta[200];
  char resposta[BUFFER_SIZE];
  memset((char *) &serv_addr, 0, sizeof(serv_addr));

  if(argc != 2) {
    printf("uso: clinete <endereco>\n");
    exit(1);
  }


  // Dados do servidor com quem vamos nos conectar: porta, endereco IP e
  // AF_INET significa que é uma conexao de internet. Tem outros tipos de conexao, por exemplo AF_BLUETOOTH pra se conectar via bluetooth com algum processo/dispositivo
 


  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(PORTNUM);
  

  // cria o socket

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    perror("clientsoc: nao pude abrir o socket"), exit(0);


  // conecta com o servidor na porta especificada
  // se tiver algum processo  "ouvindo", vai se conectar a ele
	
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	perror("clientsoc: can't connect to server"), exit(0);
	

  cout << "entre com uma mensagem:";
   cin.getline(consulta, 100); 
  // Agora que esta conectado, vou mandar uma mensagem. Geralmente
  //    o cliente comeca a conversa com o servidor 
  // Afinal, ele faz a chamada. Tem que dizer pelo penos "oi", algo assim :)

   write(sockfd, consulta, strlen(consulta));
	
  // pode ler dados com read ou com recv. recv tem opcao de ficar esperando
  read( sockfd, resposta, BUFFER_SIZE -1 );
  //  recv(sockfd, (void *)resposta,  (BUFFER_ENV_SIZE-1)*sizeof(char),MSG_WAITALL);
	
  cout << "resposta do servidor:" << resposta << endl;
	close(sockfd);

	return 0;
}
