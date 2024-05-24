#ifndef tarefa_h
#define tarefa_h

#define MAX_CLIENTES 1000
#define NOME 50
#define SOBRENOME 50
#define CPF 15
#define SENHA 50
#define TIPO_CONTA 10

typedef struct {
    char nome[NOME];
    char sobrenome[SOBRENOME];
    char cpf[CPF];
    char senha[SENHA];
    char tipoConta[TIPO_CONTA];
    float saldo;
    float debito;
} Cliente;

void novoCliente(Cliente lista[], int *numClientes);
void listarClientes(Cliente lista[], int numClientes);
void deletarCliente(Cliente lista[], int *numClientes);
void clearBuffer();

#endif

