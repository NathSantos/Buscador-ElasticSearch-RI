// Exemplo criado por Edleno Silva de Moura em 23/03/2015 
// Feito para aulas de lab de programacao

#include <semaphore.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "fixSemaphore.h"

using namespace std;

class Usuario {
public:
  string nome;
  string data;
  string email;
  string senha;
  unordered_set<string> listaAmigos;
};

unordered_map<string,Usuario> rede;








// AQUI ALGUMAS VARIAVEIS E CONSTANTES GLOBAIS. ALGUMAS PODERIAM SER LOCAIS.

const static int BUFFER_SIZE = 1024;

int sock;   // socket usado para todas as threads
rk_sema libAreaCritica; //semaforo de controle de acesso ao socket.

// as threads sempre tem que ter apenas 1 argumento que é passado como void*. Voce pode passar qualquer coisa ai, um endereco de memoria, um numero. Costumo passar um numero que identifica a thread. Pode-se passar uma struct com parametros uteis para a thread tambem.

void *FuncaoQueExecutaServico(void *arg)
{

  Usuario tmpUser;
  int meuSocket;
    char buffer[BUFFER_SIZE];
    int i;
    int thread_id = (intptr_t) arg;
    while( 1 ){

 // na linha abaixo, espera por vez para atender requisições
 // Funcao trava até que libAreaCritrica esteja liberado!
      rk_sema_wait(&libAreaCritica);
      // a partir daqui, toma conta do socket
      // abaixo, abre o socket com o proximo cliente que aparecer
      // fica esperando alguem fazer requisicao...

      // Podemos aceitar multiplas conexoes 
      //  No mesmo socket (porta/endereco de rede) ao mesmo tempo
      // O retorno do accept me da um descritor para a conexao
      //  a partir dai, posso usa-lo para saber em que conexao estou
      // lendo/ escrevendo

      meuSocket = accept( sock, NULL, NULL );

      // abaixo, alguem se conectou e vamos em frente
      // memset é uma funcao para zerar o buffer. Nada relacionado com sockets  
        memset(buffer, 0, BUFFER_SIZE);

        // funcao read le dados do socket. Pede pra ler 1024 bytes.
        // usa man read para ver como ela funciona!
        if( read( meuSocket, buffer, 1024 ) < 0){
            printf("ERRO: Leitura do socket!!!\n");
            rk_sema_post(&libAreaCritica); // libera libAreaCritica e sai da funcao!
            pthread_exit(NULL);
        }

	cout << "Recebi: " << buffer  << endl;
	
	char *last=NULL, *token;
      token = strtok_r(buffer, ":",&last);
      cout << "Comando: " <<  token << endl;
	// abaixo, libera libAreaCritica. Com isso outras threads podem receber tarefas

      if(!strcmp(buffer,"inserir")) {
        char *tmp;

	while(*token!='\"') token++;
	token++;
	tmp = token;
	while(*token!='\"') token++;
	*token = 0;
        tmpUser.nome = tmp;
	cout << "Nome: "<< tmp << endl;
	token++;
	while(*token!='\"') token++;
	token++;
	tmp = token;
	while(*token!='\"') token++;
	*token=0;
	tmpUser.data = tmp;
  	cout << "Data: "<< tmp << endl;
	token++;
	while(*token!='\"') token++;
	token++;
	tmp = token;
	while(*token!='\"') token++;
	*token=0;
	tmpUser.email = tmp;
  	cout << "Email: "<< tmp << endl;
	token++;
	while(*token!='\"') token++;
	token++;
	tmp = token;
	while(*token!='\"') token++;
	*token=0;
	tmpUser.senha = tmp;
  	cout << "Senha: "<< tmp << endl;
	tmpUser.listaAmigos.clear();
	}


	rk_sema_post(&libAreaCritica); 
	
        // AQUI EXECUTA ALGUMA TAREFA. SEMPRE FORA DA AREA CRITICA. SE TIVER OUTRO recurso critico ENTAO USA OUTRO SEMAFORO PRA CONTROLAR. POSSO TER QUANTOS SEMAFOROS QUISER!
	
        
	char mensagem[1000];
	snprintf(mensagem,1000," Servico foi executado por thread %d.\n",thread_id);
	
	// AO TERMINAR A TAREFA, ESCREVE MENSAGEM DE VOLTA! Feito abaixo.
	write( meuSocket, mensagem , strlen(mensagem));
	
    }
}

int main(int argc, char* argv[])
{
  struct sockaddr_in serv_addr;
  pthread_t *threads;
  int PORTA;
  int NUM_THREADS;

  long int k,i;
    if( argc != 1) {
        printf("uso: servidor \n");
        exit(1);
    }


    NUM_THREADS = 10;

    string hostnumber = "", hostname;

    // Nesse arquivo costumo ter o nome do host atual
    /*    ifstream fHostName("/etc/hostname", ios::in);
    if(!fHostName.good())
    {
      cout << "Nao foi possivel localizar o hostname" << endl;
    }
    else {
    fHostName >> hostname;
    fHostName.close();
    }
    */
    cout << "HostName: " << hostname << endl;
    for (int i = 0; i < hostname.size();i++)
    {
        if (isdigit(hostname.at(i)))
            hostnumber += hostname.at(i);
    }
    if (hostnumber.size() == 0)
        hostnumber = "0";


    int num_colecoes=0;

    PORTA = 5000; // AQUI O NUMERO DA PORTA.


    // inicia o libAreaCritica usado para controlar a concorrencia entre threads
    // todo libAreaCritica tem que passar por isso
    rk_sema_init(&libAreaCritica, 1);

    // Aloca o vetor de sockets.


    // aloca o vetor de threads.

    threads = (pthread_t*)malloc(sizeof(pthread_t)*NUM_THREADS);

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
      fprintf(stderr,"nao pude abrir  stream socket\n"), exit(0);


    // Pra zerar o serv_addr. Todo mundo faz isso. Nunca perguntei o motivo

    memset((char *) &serv_addr, 0, sizeof(serv_addr));


   // Dados do servidor: porta, endereco IP com quem vai aceitar conexoes 
   // (INADDR_ANY  quer dizer com qualquer endereco) e
   // AF_INET significa que é uma conexao de internet. 
   // Tem outros tipos de conexao, por exemplo AF_BLUETOOTH 
   // pra se conectar via bluetooth com algum processo/dispositivo
   // Outros tipos de conexoes fogem ao nosso escopo atual :)

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORTA);

    // get around "Address is already in use" errors
    int on = 1;







    // Seta valores para os parametros do socket. 
    // Abaixo, SO-REUSEADDR é setado para verdadeiro (1) no on.
    // Usado para que nao de problemas 
    // em execucoes seguidas do servidor. Sem isso ele da endereco em uso, algo     // assim como mensagem de erro por um tempo.
    // Isso acontecia em meus códigos antigos
    // Dai alguem deu essa dica. 
    // Sem usar isso, voce executa o servidor, da ctrl-c e, ao chamar em seguida, ele nao aceita o bind porque a porta esta sendo usada. Demora um tempo pro SO perceber que nao tem mais ninguem usando o endereco.

    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));




    // Associa o socket com o endereco do servidor.
    // 

    if(bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) fprintf(stderr,"Nao pude me ligar a porta\n"), exit(0);

    // AQUI JA ESTA LIGADO NA PORTA E COMECA A ESPERAR POR CONEXOES





    //  O listen diz que estamos esperando conexoes nesse socket e que 
    //  aceitamos  ate 500 esperando na fila. Se demorarmos para atender
    // a requisicoes, a fila pode encher. Quando encher, o servidor vai 
    // recusar conexoes.

    listen(sock, 500);
    /////////////////////////////

    printf ("Servidor Ouvindo Porta: %d\n", PORTA );


    for (k = 0; k < NUM_THREADS; k++ ) {
      // aqui cria as threads que executam a funcao do servidor
      // o k é passado como único parametro da thread.
      // esse valor pode ser usado para ter acesso a outros parametros
      if( pthread_create( &threads[k], NULL, FuncaoQueExecutaServico, (void*)k) ) {
            printf("Nao foi possivel criar threads (%ld)\n", k );
        }
        else{
            printf("Disparando Thread %ld\n", k);
        }
    }
    printf("\n");

    // Nada impede que seu programa crie threads que executem outras
    // funcoes. Voce pode inclusive ter threads criadas para serem clientes
    // de outros programas. Por exemplo, fazer um talk onde você é o servidor
    // em uma thread para receber mensagens e o cliente para enviar.
    // Tente fazer um talk. 
    // Agora o programa principal vai dormir até que todas as threads
    // tenham terminado. O join diz que essa thread (a principal) só continua 
    // quando a thread passada no join termina 
    for ( k = 0; k < NUM_THREADS; k++ ){
        pthread_join(threads[k], NULL);
    }

    cout << "Servidor Terminou!" << endl;
    return 0;
}

