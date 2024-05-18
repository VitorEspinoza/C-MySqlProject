#include <locale.h>
#include <stdio.h>
#include "cliente.h"
#include "databaseConnection.h"
#include "clienteController.h"
#include "conta.h"

void telaInicial();
void cadastroConta();
void telaDeposito(struct Conta *conta);
void telaSaque(struct Conta *conta);
void telaTransacao(struct Conta *conta);
void setLocale();
int main() {
	setLocale();
	const connectionMySqlSuceed = initMySqlConnection();
	if(!connectionMySqlSuceed)
	printf('fim');

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
	
	printf("Voc� j� tem uma conta? (S/N): ");
	
	do {
    scanf(" %c", &resposta);
		  if (resposta == 'S' || resposta == 's') {
		  	printf("Bem-vindo! Fa�a login na sua conta.\n");
	        // Aqui voc� pode adicionar a l�gica para o login
	    } else if (resposta == 'N' || resposta == 'n') {
	       cadastroCliente();
	    } else {
	        printf("Op��o inv�lida. Responda com S ou N.\n");
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

    printf("Digite o endere�o: ");
    scanf("%40s", &client.endereco);

    printf("Digite o telefone: ");
    scanf("%11s", &client.telefone);

    printf("Estado civil (0 - Solteiro, 1 - Casado): ");
    scanf("%d", &client.estadoCivil);
    
    int success = createClient(client);
    
    if(success) {
    	printf("Voc� foi adicionado como cliente, agora vamos ao cadastro da sua conta no nosso sistema:");
    	
	}
	else{
		printf("Ops, parece que houve algo de errado ao te cadastrar. Tente novamente mais tarde.");
	}
	
}


void telaConta(struct Conta *conta) {
    int escolha;

    do {
        // Exibir informa��es da conta
        printf("\n--- Tela Inicial ---\n");
        printf("N�mero da Conta: %d\n", conta->numeroConta);
        printf("Saldo: R$ %.2f\n", conta->saldo);
        printf("\nOp��es:\n");
        printf("1. Depositar\n");
        printf("2. Sacar\n");
        printf("3. Transa��o\n");
        printf("4. Sair\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &escolha);

        // Executar a a��o correspondente � escolha do usu�rio
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

void telaDeposito(struct Conta *conta) {
    float valor;

    // Solicitar valor do dep�sito
    printf("\n--- Tela de Dep�sito ---\n");
    printf("Saldo atual: R$ %.2f\n", conta->saldo);
    printf("Digite o valor a ser depositado: R$ ");
    scanf("%f", &valor);

    // Verificar valor v�lido
    if (valor > 0) {
        conta->saldo += valor;
        printf("Dep�sito realizado com sucesso!\n");
        printf("Novo saldo: R$ %.2f\n", conta->saldo);
    } else {
        printf("Valor inv�lido. Tente novamente.\n");
    }
}

void telaSaque(struct Conta *conta) {
    float valor;

    // Solicitar valor do saque
    printf("\n--- Tela de Saque ---\n");
    printf("Saldo atual: R$ %.2f\n", conta->saldo);
    printf("Digite o valor a ser sacado: R$ ");
    scanf("%f", &valor);

    // Verificar se h� saldo suficiente
    if (valor > 0 && valor <= conta->saldo) {
        conta->saldo -= valor;
        printf("Saque realizado com sucesso!\n");
        printf("Novo saldo: R$ %.2f\n", conta->saldo);
    } else {
        printf("Saldo insuficiente ou valor inv�lido. Tente novamente.\n");
    }
}

void telaTransacao(struct Conta *conta) {
    float valor;

    // Solicitar valor da transa��o
    printf("\n--- Tela de Transa��o ---\n");
    printf("Saldo atual: R$ %.2f\n", conta->saldo);
    printf("Digite o valor da transa��o: R$ ");
    scanf("%f", &valor);

    // Atualizar saldo com o valor da transa��o
    conta->saldo += valor;
    printf("Transa��o realizada com sucesso!\n");
    printf("Novo saldo: R$ %.2f\n", conta->saldo);
}

