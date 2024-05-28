#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "cliente.h"
#include "databaseConnection.h"
#include "clienteController.h"
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

    do {
        // Exibir informações da conta
        printf("\n--- Tela Inicial ---\n");
        printf("Número da Conta: %d\n", conta->numeroConta);
        printf("Saldo: R$ %.2f\n", conta->saldo);
        printf("\nOpções:\n");
        printf("1. Depositar\n");
        printf("2. Sacar\n");
        printf("3. Transação\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
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
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 4);
}

void telaDeposito(struct Conta *conta) {
    float valor;

    // Solicitar valor do depósito
    printf("\n--- Tela de Depósito ---\n");
    printf("Saldo atual: R$ %.2f\n", conta->saldo);
    printf("Digite o valor a ser depositado: R$ ");
    scanf("%f", &valor);

    // Verificar valor válido
    if (valor > 0) {
        conta->saldo += valor;
        printf("Depósito realizado com sucesso!\n");
        printf("Novo saldo: R$ %.2f\n", conta->saldo);
    } else {
        printf("Valor inválido. Tente novamente.\n");
    }
}

void telaSaque(struct Conta *conta) {
    float valor;

    // Solicitar valor do saque
    printf("\n--- Tela de Saque ---\n");
    printf("Saldo atual: R$ %.2f\n", conta->saldo);
    printf("Digite o valor a ser sacado: R$ ");
    scanf("%f", &valor);

    // Verificar se há saldo suficiente
    if (valor > 0 && valor <= conta->saldo) {
        conta->saldo -= valor;
        printf("Saque realizado com sucesso!\n");
        printf("Novo saldo: R$ %.2f\n", conta->saldo);
    } else {
        printf("Saldo insuficiente ou valor inválido. Tente novamente.\n");
    }
}

void telaTransacao(struct Conta *conta) {
    float valor;

    // Solicitar valor da transação
    printf("\n--- Tela de Transação ---\n");
    printf("Saldo atual: R$ %.2f\n", conta->saldo);
    printf("Digite o valor da transação: R$ ");
    scanf("%f", &valor);

    // Atualizar saldo com o valor da transação
    conta->saldo += valor;
    printf("Transação realizada com sucesso!\n");
    printf("Novo saldo: R$ %.2f\n", conta->saldo);
}

