#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "cliente.h"
#include "databaseConnection.h"
#include "clienteController.h"
#include "contaController.h"
#include "conta.h"
#include "generalScreens.h"
#include "clientScreens.h"
#include "consoleUtils.h"




void cadastroConta();
void telaDeposito(struct Conta *conta);
void telaSaque(struct Conta *conta);
void telaTransacao(struct Conta *conta);
void setLocale();


int main() {
	setLocale();
	const connectionMySqlSuceed = initMySqlConnection();
	if(!connectionMySqlSuceed)
	printf("fim");
	initHConsole();
	setDefaultColorTextConsole();
    telaInicial();

    return 0;
}

void setLocale() {
	setlocale(LC_ALL, "Portuguese");
}

void telaConta(struct Conta *conta) {
    int escolha;
    
    system("cls");
    Propriedade cpfProp = setPropriedade("FK_Cliente_CPF", "string", cpf);
	Conta conta = readContaByField(cpfProp);
	
    do {
        // Exibir informa��es da conta
        printf("\n--- Tela Inicial ---\n");
        printf("N�mero da Agencia: %d\n", conta.numAgencia);
        printf("N�mero da Conta: %d\n", conta.numeroConta);
        printf("Saldo: R$ %.2f\n", conta.saldo);
        printf("\nOp��es:\n");
        printf("1. Depositar\n");
        printf("2. Sacar\n");
        printf("3. Transa��o\n");
        printf("4. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                telaDeposito(conta);
                break;
            case 2:
                telaSaque(conta);
                break;
            case 3:
                telaTransacao(conta);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (escolha != 4);
}

void telaDeposito(Conta conta) {
    float valor;

    // Solicitar valor do dep�sito
    printf("\n--- Tela de Dep�sito ---\n");
    printf("Saldo atual: R$ %.2f\n", conta.saldo);
    printf("Digite o valor a ser depositado: R$ ");
    scanf("%f", &valor);

    // Verificar valor v�lido
    if (valor > 0) {
        conta.saldo += valor;
        printf("Dep�sito realizado com sucesso!\n");
        printf("Novo saldo: R$ %.2f\n", conta.saldo);
    } else {
        printf("Valor inv�lido. Tente novamente.\n");
    }
}

void telaSaque(Conta conta) {
    float valor;

    // Solicitar valor do saque
    printf("\n--- Tela de Saque ---\n");
    printf("Saldo atual: R$ %.2f\n", conta.saldo);
    printf("Digite o valor a ser sacado: R$ ");
    scanf("%f", &valor);

    // Verificar se h� saldo suficiente
    if (valor > 0 && valor <= conta.saldo) {
        conta.saldo -= valor;
        printf("Saque realizado com sucesso!\n");
        printf("Novo saldo: R$ %.2f\n", conta.saldo);
    } else {
        printf("Saldo insuficiente ou valor inv�lido. Tente novamente.\n");
    }
}

void telaTransacao(Conta conta) {
    float valor;

    // Solicitar valor da transa��o
    printf("\n--- Tela de Transa��o ---\n");
    printf("Saldo atual: R$ %.2f\n", conta.saldo);
    printf("Digite o valor da transa��o: R$ ");
    scanf("%f", &valor);

    // Atualizar saldo com o valor da transa��o
    conta.saldo += valor;
    printf("Transa��o realizada com sucesso!\n");
    printf("Novo saldo: R$ %.2f\n", conta.saldo);
}
