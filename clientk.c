//Cliente.
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "socket_qualquer"

int main(void) {

	int descServidor1, comprimento;
	struct sockaddr_un cliente;

	if( ( descServidor1 = socket( AF_UNIX, SOCK_STREAM, 0 ) ) == -1 ) {
		perror("Cliente - Erro na funcao socket( ) ");
		return 1;
	}

	cliente.sun_family = AF_UNIX;
	strcpy(cliente.sun_path, SOCK_PATH);
	comprimento = strlen(cliente.sun_path) + sizeof(cliente.sun_family);

	if( connect( descServidor1, ( struct sockaddr * )&cliente, comprimento ) == -1 ) {
		perror("Cliente - Erro na funcao connect( ) ");
		return 1;
	}

	printf("Cliente - voce esta conectado.\n");
	printf("Cliente - Digite um numero para ser enviado ao servidor.\n");
	printf("Cliente - numero: ");
	int val;
	scanf("%d", &val);
	if( send( descServidor1, &val, 4, 0 ) == -1 ) {
		perror("Cliente - Erro na funcao send( ) ");
		return 1;
	}

	close( descServidor1 );

	return 0;

}