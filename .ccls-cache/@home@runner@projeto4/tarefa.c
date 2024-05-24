#include "tarefa.h"
#include <stdio.h>
#include <string.h>

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

float debitar(Cliente lista[], int numClientes) {
  if (numClientes == 0) {
    printf("Não há clientes para debitar!\n");
    return 0.0;
  }

  char cpf[CPF];
  char senha[SENHA];
  float valor;
  printf("Digite o CPF do cliente: ");
  scanf("%14s", cpf);
  clearBuffer();

  int clienteEncontrado = 0;
  for (int i = 0; i < numClientes; i++) {
    if (strcmp(lista[i].cpf, cpf) == 0) {
      clienteEncontrado = 1;
      printf("Digite a senha da conta: ");
      scanf("%49s", senha);
      clearBuffer();

      if (strcmp(lista[i].senha, senha) != 0) {
        printf("Senha incorreta! Tente novamente!\n");
        return 0.0;
      }

      printf("Digite o valor a ser debitado: ");
      scanf("%f", &valor);
      clearBuffer();

      if (valor <= 0) {
        printf("Valor inválido para débito!\n");
        return 0.0;
      }

      float taxaDesconto;
      if (strcmp(lista[i].tipoConta, "comum") == 0) {
        taxaDesconto = 0.05;
        if (lista[i].saldo - valor - (valor * taxaDesconto) >= -1000.0) {
          lista[i].saldo -= valor + (valor * taxaDesconto);
          lista[i].debito += valor;
          lista[i].taxaDesconto = taxaDesconto;
          printf("Débito de %.2f realizado com sucesso!\n", valor);
          return valor;
        } else {
          printf("Transação não autorizada. Limite de saldo atingido!\n");
          return 0.0;
        }
      } else if (strcmp(lista[i].tipoConta, "plus") == 0) {
        taxaDesconto = 0.03;
        if (lista[i].saldo - valor - (valor * taxaDesconto) >= -5000.0) {
          lista[i].saldo -= valor + (valor * taxaDesconto);
          lista[i].debito += valor;
          lista[i].taxaDesconto = taxaDesconto;
          printf("Débito de %.2f realizado com sucesso!\n", valor);
          return valor;
        } else {
          printf("Transação não autorizada. Limite de saldo atingido!\n");
          return 0.0;
        }
      } else {
        printf("Tipo de conta inválida!\n");
        return 0.0;
      }
    }
  }

  if (!clienteEncontrado) {
    printf("Cliente não encontrado! Tente novamente!\n");
  }

  return 0.0;
}

float depositoCliente(Cliente lista[], int numClientes) {
  if (numClientes == 0) {
    printf("Não há clientes para realizar o depósito!\n");
    return 0.0;
  }

  char cpf[CPF];
  float valor;
  printf("Digite o CPF do cliente: ");
  scanf("%14s", cpf);
  clearBuffer();

  int clienteEncontrado = 0;
  for (int i = 0; i < numClientes; i++) {
    if (strcmp(lista[i].cpf, cpf) == 0) {
      clienteEncontrado = 1;
      printf("Digite o valor a ser depositado: ");
      scanf("%f", &valor);
      clearBuffer();

      if (valor <= 0) {
        printf("Valor inválido para depósito!\n");
        return 0.0;
      }

      lista[i].saldo += valor;
      lista[i].deposito += valor;
      printf("Depósito de %.2f realizado com sucesso!\n", valor);
      return valor;
    }
  }

  if (!clienteEncontrado) {
    printf("Cliente não encontrado!\n");
  }

  return 0.0;
}

void extrato(Cliente lista[], int numClientes) {
char cpf[CPF];
char senha[SENHA];
printf("Digite o CPF do cliente para ver o extrato: ");
scanf("%14s", cpf);
clearBuffer();

printf("Digite a senha do cliente: ");
scanf("%49s", senha);
clearBuffer();

int clienteEncontrado = 0;
for (int i = 0; i < numClientes; i++) {
if (strcmp(lista[i].cpf, cpf) == 0 && strcmp(lista[i].senha, senha) == 0) {
clienteEncontrado = 1;
FILE *arquivo = fopen("extrato.txt", "w");
if (arquivo == NULL) {
printf("Erro ao abrir o arquivo de extrato.\n");
return;
}

fprintf(arquivo, "Extrato para o cliente %s:\n", lista[i].cpf);
fprintf(arquivo, "Nome: %s\n", lista[i].nome);
fprintf(arquivo, "Sobrenome: %s \n", lista[i].sobrenome);
fprintf(arquivo, "Tipo de conta: %s\n", lista[i].tipoConta);
fprintf(arquivo, "Débitos que foram realizados: %.2f\n", lista[i].debito);
fprintf(arquivo, "Depósitos que foram realizados: %.2f\n", lista[i].deposito);
fprintf(arquivo, "Transferências que foram realizadas: %.2f\n", lista[i].transferencia);
fprintf(arquivo, "Taxa: %.2f\n", lista[i].taxaDesconto);
fprintf(arquivo, "Saldo atual: %.2f\n", lista[i].saldo);

fclose(arquivo);
printf("Extrato salvo com sucesso no arquivo extrato.txt.\n");
return;
}
}

if (!clienteEncontrado) {
printf("CPF ou senha incorretos. Não é possível fazer o extrato.\n");
}
}

void transferencia(Cliente lista[], int numClientes) {
  char cpf_Origem[CPF];
  char cpf_Destino[CPF];
  char senha_Origem[SENHA];
  float valor;

  printf("Digite o CPF do cliente de origem: ");
  scanf("%14s", cpf_Origem);
  clearBuffer();

  printf("Digite a senha da conta de origem: ");
  scanf("%49s", senha_Origem);
  clearBuffer();

  printf("Digite o CPF do cliente de destino: ");
  scanf("%14s", cpf_Destino);
  clearBuffer();

  int clienteOrigemEncontrado = 0;
  int clienteDestinoEncontrado = 0;
  int Cliente_Origem = -1;
  int Cliente_Destino = -1;

  for (int i = 0; i < numClientes; i++) {
    if (strcmp(lista[i].cpf, cpf_Origem) == 0 &&
        strcmp(lista[i].senha, senha_Origem) == 0) {
      clienteOrigemEncontrado = 1;
      Cliente_Origem = i;
      break;
    }
  }


  for (int i = 0; i < numClientes; i++) {
    if (strcmp(lista[i].cpf, cpf_Destino) == 0) {
      clienteDestinoEncontrado = 1;
      Cliente_Destino = i;
      break;
    }
  }

  if (!clienteOrigemEncontrado) {
    printf("CPF ou senha de origem incorretos!\n");
    return;
  }

  if (!clienteDestinoEncontrado) {
    printf("Cliente de destino não encontrado! Tente novamente!\n");
    return;
  }

  
  printf("Digite o valor a ser transferido: ");
  scanf("%f", &valor);
  clearBuffer();

  
  if (valor > lista[Cliente_Origem].saldo) {
    printf("Saldo insuficiente! Não foi possivel realizar a transferência!\n");
    return;
  }

  
  lista[Cliente_Origem].saldo -= valor;
  lista[Cliente_Origem].transferencia -= valor;
  lista[Cliente_Destino].saldo += valor;
  lista[Cliente_Destino].transferencia += valor;

  printf("Transferência de %.2f realizada com sucesso de %s para %s.\n", valor,
         lista[Cliente_Origem].cpf, lista[Cliente_Destino].cpf);
}
