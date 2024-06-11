#include <stdio.h>
#include <string.h>
#include "configScreens.h"
#include "transactionScreens.h"

Conta account;

void createAccountScreen(Cliente client);
void infoAccountScreen();
void loginAccountScreen(Cliente client);
void loginOptionAccountScreen(Cliente client);
void depositAccountScreen();
void withdrawAccountScreen();

void createAccountScreen(Cliente client) {
	system("cls");
    printf("====================================\n");
    printf("=         Cadastro de Conta        =\n");
    printf("====================================\n");
    
	printf("Digite a senha da sua conta: ");
	scanf("%s", &account.senha);
	
	printf("\n Criando cadastro... \n");
	
	strcpy(account.numAgencia, "777");
	strcpy(account.cpfCliente, client.cpf);
	account.saldo = 0.00;	
    
	ResponseAccount responseAccount;
	responseAccount = createConta(account);
	
	strcpy(account.numeroConta, responseAccount.account.numeroConta);

	if(responseAccount.success) {
    	setSuccessColorTextConsole();
    	system("cls");
       	printf("===============================================\n");
	    printf("=         Você agora possui uma conta :)      =\n");
	    printf("===============================================\n");
	    printf("Aperte enter para continuar.");
	    clearBuffer();
		infoAccountScreen();
	} else {
		printf("DEU PAU");
	}

}

void infoAccountScreen() {
    int option;
	setDefaultColorTextConsole();
	
	system("cls");
	printf("====================================\n");
	printf("=             Menu Conta           =\n");
	printf("====================================\n");
	printf("Número da Agencia: %s\n", account.numAgencia);
    printf("Número da Conta: %s\n", account.numeroConta);
    printf("Saldo: R$ %.2f\n", account.saldo);
        
    do {
        // Exibir informações da conta
        printf("\nOpções:\n");
        printf("1. Depositar\n");
        printf("2. Sacar\n");
        printf("3. Transação\n");
        printf("4. Configurações\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);
		getchar();
        // Executar a ação correspondente à escolha do usuário
        switch (option) {
            case 1:
                depositAccountScreen();
                break;
            case 2:
                withdrawAccountScreen();
                break;
            case 3:
                transactionMenuScreen(&account);
                break;
            case 4:
                configMenuScreen(&account);
                break;
            case 5:
            	system("cls");
                telaInicial();
                break;
            default:
            	setErrorColorTextConsole();
                printf("Opção inválida. Tente novamente.");
                setDefaultColorTextConsole();
        }
    } while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5);
	
}

void depositAccountScreen() {
	char str[100];
	double value;
	
	system("cls");
    printf("====================================\n");
    printf("=              Deposito            =\n");
    printf("====================================\n");
    printf("Saldo atual: R$%.2f\n", account.saldo);
    printf("Digite o quanto deseja depositar: R$");

    scanf("%s", str);
    while (!isNumber(str)) {
    	setErrorColorTextConsole();
        printf("Entrada inválida!\n");
        setDefaultColorTextConsole();
        printf("Por favor, digite um número: R$");
        scanf("%s", str);
    }
    value = atof(str);
    
    account.saldo = account.saldo + value;
    
    Propriedade numAccountProp = setPropriedade("numeroConta", "string", account.numeroConta);
    
    ResponseAccount responseAccount;
    responseAccount = updateAccount(account, numAccountProp);
    
    if (responseAccount.success) {
    	system("cls");
    	setSuccessColorTextConsole();
    	printf("====================================\n");
    	printf("=         Deposito realizado!      =\n");
    	printf("=         Novo saldo: R$%.2f       =\n", account.saldo);
    	printf("====================================\n");
    	printf("Aperte enter para continuar.");
    	clearBuffer();
	    getchar();
	    infoAccountScreen();
	} else {
		system("cls");
    	setErrorColorTextConsole();
		printf("================================================\n");
   	 	printf("=    Oops... Erro ocorrido durante operação    =\n");
    	printf("================================================\n");
    	printf("Aperte enter para continuar.");
    	clearBuffer();
	    getchar();
	    infoAccountScreen();
	}
}

void withdrawAccountScreen() {
	double value;
	char str[100];
	
	setDefaultColorTextConsole();
	system("cls");
	printf("====================================\n");
    printf("=               Saque              =\n");
    printf("====================================\n");
    
    do { 
	    printf("Saldo atual: R$%.2f\n", account.saldo);
	    printf("Digite o quanto deseja depositar: R$");
	
	    scanf("%s", str);
	    while (!isNumber(str)) {
	    	setErrorColorTextConsole();
	        printf("Entrada inválida!\n");
	        setDefaultColorTextConsole();
	        printf("Por favor, digite um número: R$");
	        scanf("%s", str);
	    }
	    value = atof(str);
	    
	    if (value > account.saldo){
	    	system("cls");
	    	setWarningColorTextConsole();
	    	printf("================================================\n");
	    	printf("=      Saldo insuficiente. Tente novamente.    =\n");
	    	printf("================================================\n");
	    	setDefaultColorTextConsole();
			printf("====================================\n");
    		printf("=               Saque              =\n");
   		 	printf("====================================\n");
	    	
		} else {
			account.saldo = account.saldo - value;
	    
		    Propriedade numAccountProp = setPropriedade("numeroConta", "string", account.numeroConta);
		    
		    ResponseAccount responseAccount;
		    responseAccount = updateAccount(account, numAccountProp);
		    
		    if (responseAccount.success) {
		    	system("cls");
		    	setSuccessColorTextConsole();
		    	printf("====================================\n");
		    	printf("=         Saque realizado!         =\n");
		    	printf("=         Novo saldo: R$%.2f       =\n", account.saldo);
		    	printf("====================================\n");
		    	printf("Aperte enter para continuar.");
		    	clearBuffer();
		    	getchar();
			    infoAccountScreen();
			} else {
				system("cls");
		    	setErrorColorTextConsole();
				printf("================================================\n");
		   	 	printf("=    Oops... Erro ocorrido durante operação    =\n");
		    	printf("================================================\n");
		    	printf("Aperte enter para continuar.");
		    	clearBuffer();
		    	getchar();
		    	setDefaultColorTextConsole();
		    	infoAccountScreen();
			}
		}
	} while(value > account.saldo);
   
    
}

void loginOptionAccountScreen(Cliente client) {
	system("cls");
	int option;		
	printf("====================================\n");
	printf("=               Login              =\n");
	printf("====================================\n");
	printf("Já possui uma CONTA para logar?\n");
	do {

		printf("1. Sim\n2. Não\n");
		printf("Digite sua escolha: ");
		
		scanf("%d", &option);
		getchar();
		
		switch (option) {
			case 1:
				loginAccountScreen(client);
				break;
			case 2:
				createAccountScreen(client);
				break;
			default:
				setErrorColorTextConsole();
                printf("Opção inválida. Tente novamente.\n");
                setDefaultColorTextConsole();
				break;
		}
	}
	while(option != 1 && option != 2);
}

void loginAccountScreen(Cliente client) {
	char password[100];
	int isNumAccountNull;
	
	system("cls");
	printf("====================================\n");
	printf("=            Fazer Login           =\n");
	printf("====================================\n");
	
	do {
		setDefaultColorTextConsole();
		printf("Digite o numero da sua conta: ");
		scanf("%s", &account.numeroConta);
		
		Propriedade numAccountProp = setPropriedade("numeroconta", "string", account.numeroConta);
		account = readContaByField(numAccountProp);
		
		isNumAccountNull = strcmp(account.cpfCliente, "NULL") == 0;
			
		if (isNumAccountNull) {
			system("cls");
			setWarningColorTextConsole();
			printf("====================================\n");
			printf("=    Numero de Conta inexistente.  =\n");
			printf("=    Tente novamente.               =\n");
			printf("====================================\n");
			
		} else {
			int success;
			int attempts = 0;
			
			do{
				setDefaultColorTextConsole();
				printf("Digite sua senha: ");
				scanf("%s", &password);
				
				success = strcmp(account.senha, password) == 0;
				
				if(success) {
					infoAccountScreen();
				} else {
					system("cls");
					setWarningColorTextConsole();
					printf("=====================================\n");
					printf("= Senha incorreta. Tente Novamente. =\n");
					printf("=====================================\n");
				}
				
				attempts++;
				
			} while (!success && attempts < 10);
			
			if (attempts == 10) {
				setErrorColorTextConsole();
				printf("=====================================\n");
				printf("=   Numero de tentativas excedido.  =\n");
				printf("=    Tente novamente mais tarde.    =\n");
				printf("=====================================\n");
		    	setDefaultColorTextConsole();
			}

			
		}
	} while (isNumAccountNull);
}
