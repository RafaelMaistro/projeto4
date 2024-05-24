#include "tarefa.h"
#include <stdio.h>
#include <string.h>

int main() {
  Cliente listaclientes[MAX_CLIENTES];
  int numClientes = 0;
  char opcao;

  do {
    printf("\nMenu Principal:\n");
    printf("1- Novo Cliente\n");
    printf("2- Apagar Cliente\n");
    printf("3- Listar Clientes\n");
    printf("0- Sair\n");
    printf("Escolha uma opção: ");
    scanf(" %c", &opcao);

    switch (opcao) {
    case '1':
      novoCliente(listaclientes, &numClientes);
      break;

    case '2':
      deletarCliente(listaclientes, &numClientes);
      break;

    case '3':
      listarClientes(listaclientes, numClientes);
      break;
   
    case '0':
      printf("Saindo...\n");
      break;

    default:
      printf("Opção inválida.\n");
      break;
    }

  } while (opcao != '0');

  return 0;
}
