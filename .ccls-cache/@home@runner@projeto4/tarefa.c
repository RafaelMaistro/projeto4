#include "tarefa.h"
#include <stdio.h>
#include <string.h>

// Função para limpar o buffer do teclado
void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void novoCliente(Cliente lista[], int *numClientes) {
  if (*numClientes >= MAX_CLIENTES) {
    printf("Lista cheia.\n");
    return;
  }

  printf("Digite o seu nome: ");
  scanf("%49s", lista[*numClientes].nome);
  clearBuffer();

  printf("Digite o seu sobrenome: ");
  scanf("%49s", lista[*numClientes].sobrenome);
  clearBuffer();

  printf("Tipo de conta (comum ou plus): ");
  scanf("%9s", lista[*numClientes].tipoConta);
  clearBuffer();

  printf("Digite o seu CPF: ");
  scanf("%14s", lista[*numClientes].cpf);
  clearBuffer();

  for (int i = 0; i < *numClientes; i++) {
    if (strcmp(lista[i].cpf, lista[*numClientes].cpf) == 0) {
      printf("Já existe um cliente cadastrado com esse CPF.\n");
      return;
    }
  }
  printf("Digite o seu saldo: ");
  scanf("%f", &lista[*numClientes].saldo);
  clearBuffer();

  printf("Digite a sua senha: ");
  scanf("%49s", lista[*numClientes].senha);
  clearBuffer();

  (*numClientes)++;

  if (numClientes > 0 &&
      strcmp(lista[*numClientes - 1].cpf, lista[*numClientes - 2].cpf) != 0) {
    printf("Cliente cadastrado com sucesso!\n");
  } else {
    printf("Erro ao cadastrar cliente!\n");
    (*numClientes)--;
  }
}

void listarClientes(Cliente lista[], int numClientes) {
  if (numClientes == 0) {
    printf("Nenhum cliente cadastrado.\n");
    return;
  }

  printf("Lista de Clientes:\n");
  printf("\n");
  for (int i = 0; i < numClientes; i++) {
    printf("NOME: %s\n", lista[i].nome);
    printf("SOBRENOME: %s\n", lista[i].sobrenome);
    printf("CONTA: %s\n", lista[i].tipoConta);
    printf("SENHA: %s\n", lista[i].senha);
    printf("CPF: %s\n", lista[i].cpf);
    printf("SALDO: %.2f\n", lista[i].saldo);
    printf("\n");
  }
}

void deletarCliente(Cliente lista[], int *numClientes) {
    if (*numClientes == 0) {
      printf("Não há clientes cadastrados!\n");
      return;
    }

    char cpf[CPF];
    printf("Digite o CPF do cliente que deseja deletar: ");
    scanf("%14s", cpf);
    clearBuffer();

    int achouCliente = 0;
    for (int i = 0; i < *numClientes; i++) {
      if (strcmp(lista[i].cpf, cpf) == 0) {
        achouCliente = 1;

        for (int j = i; j < *numClientes - 1; j++) {
          lista[j] = lista[j + 1];
        }

        (*numClientes)--;
        printf("O cliente foi deletado com sucesso!\n");
        break;
      }
    }

    if (!achouCliente) {
      printf("Cliente não cadastrado!\n");
    }
}