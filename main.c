#include <locale.h>
#include <stdio.h>
#include "cliente.h"
#include "databaseConnection.h"
#include "clienteController.h"
#include "contaController.h"
#include "conta.h"

void telaInicial();
void cadastroCliente();
void cadastroConta(Cliente cliente);
void telaDeposito(Conta conta);
void telaSaque(Conta conta);
void telaTransacao(Conta conta);

int main() {
	setLocale();
	const connectionMySqlSuceed = initMySqlConnection();
	if(!connectionMySqlSuceed)
	printf("fim");

    telaInicial();

    return 0;
}

void setLocale() {
	setlocale(LC_ALL, "Portuguese");
}


void telaInicial() {
	read();
    printf("\n--- Tela Inicial ---\n");	
	char resposta;
	
	printf("Você já tem uma conta? (S/N): ");
	
	do {
    scanf(" %c", &resposta);
		  if (resposta == 'S' || resposta == 's') {
		  	printf("Bem-vindo! Faça login na sua conta.\n");
	        // Aqui você pode adicionar a lógica para o login
	    } else if (resposta == 'N' || resposta == 'n') {
	       cadastroCliente();
	    } else {
	        printf("Opção inválida. Responda com S ou N.\n");
	    }
	}	while(resposta != "S" || resposta != "s" || resposta != "N" || resposta != "n");
}

void cadastroCliente() {
	system("cls");
	printf("\n--- Tela Cadastro de Cliente---\n");
	
	Cliente client; 
	printf("Digite o CPF: ");
    scanf("%11s", &client.cpf);

    printf("Digite o RG: ");
    scanf("%30s", &client.rg);

    printf("Digite o nome: ");
    scanf("%40s", &client.nome);

    printf("Digite o endereço: ");
    scanf("%40s", &client.endereco);

    printf("Digite o telefone: ");
    scanf("%11s", &client.telefone);

    printf("Estado civil (0 - Solteiro, 1 - Casado): ");
    scanf("%d", &client.estadoCivil);
    
    int success = createClient(client);
    
    if(success) {
    	printf("Você foi adicionado como cliente, agora faremos o cadastro da sua conta no nosso sistema:");
    	cadastroConta(client);
	}
	else{
		printf("Ops, parece que houve algo de errado ao te cadastrar. Tente novamente mais tarde.");
	}
	
}

void cadastroConta(Cliente cliente) {
	system("cls");
	printf("\n--- Tela Cadastro de Conta---\n");
	
	Conta conta;
	printf("Digite a senha da sua conta: ");
	scanf("%254s", &conta.senha);
	
	printf("\n Criando cadastro... \n");
	
	conta.numAgencia = 777;
	strcpy(conta.cpfCliente, cliente.cpf);
	conta.saldo = 0;	
    
	int success = createConta(conta);
	
	if(success) {
		system("cls");
		printf("Conta cadastrada com sucesso.");
	} else {
		printf("DEU PAU");
	}
	
}


void telaConta(Conta conta) {
    int escolha;

    do {
        // Exibir informações da conta
        printf("\n--- Tela Inicial ---\n");
        printf("Número da Conta: %d\n", conta.numeroConta);
        printf("Saldo: R$ %.2f\n", conta.saldo);
        printf("\nOpções:\n");
        printf("1. Depositar\n");
        printf("2. Sacar\n");
        printf("3. Transação\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Executar a ação correspondente à escolha do usuário
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

void telaDeposito(Conta conta) {
    float valor;

    // Solicitar valor do depósito
    printf("\n--- Tela de Depósito ---\n");
    printf("Saldo atual: R$ %.2f\n", conta.saldo);
    printf("Digite o valor a ser depositado: R$ ");
    scanf("%f", &valor);

    // Verificar valor válido
    if (valor > 0) {
        conta.saldo += valor;
        printf("Depósito realizado com sucesso!\n");
        printf("Novo saldo: R$ %.2f\n", conta.saldo);
    } else {
        printf("Valor inválido. Tente novamente.\n");
    }
}

void telaSaque(Conta conta) {
    float valor;

    // Solicitar valor do saque
    printf("\n--- Tela de Saque ---\n");
    printf("Saldo atual: R$ %.2f\n", conta.saldo);
    printf("Digite o valor a ser sacado: R$ ");
    scanf("%f", &valor);

    // Verificar se há saldo suficiente
    if (valor > 0 && valor <= conta.saldo) {
        conta.saldo -= valor;
        printf("Saque realizado com sucesso!\n");
        printf("Novo saldo: R$ %.2f\n", conta.saldo);
    } else {
        printf("Saldo insuficiente ou valor inválido. Tente novamente.\n");
    }
}

void telaTransacao(Conta conta) {
    float valor;

    // Solicitar valor da transação
    printf("\n--- Tela de Transação ---\n");
    printf("Saldo atual: R$ %.2f\n", conta.saldo);
    printf("Digite o valor da transação: R$ ");
    scanf("%f", &valor);

    // Atualizar saldo com o valor da transação
    conta.saldo += valor;
    printf("Transação realizada com sucesso!\n");
    printf("Novo saldo: R$ %.2f\n", conta.saldo);
}
