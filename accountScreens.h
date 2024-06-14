#include <stdio.h>
#include <string.h>
#include "configScreens.h"
#include "transactionScreens.h"

Account account;

void createAccountScreen(Client client);
void infoAccountScreen();
void loginAccountScreen(Client client);
void loginOptionAccountScreen(Client client);
void depositAccountScreen();
void withdrawAccountScreen();

void createAccountScreen(Client client) {
	int tamanho, isValidPassword;
    system("cls");
    printf("====================================\n");
    printf("=         Cadastro de Conta        =\n");
    printf("====================================\n");
	printf("(0 - sair)\n");
	
	do {
		printf("Digite a senha da sua conta: ");
	    readInput(account.password, 255);  
		
		if (strcmp(account.password, "0") == 0) {
			loginOptionAccountScreen(client);
		}
		
		tamanho = strlen(account.password);
		
		isValidPassword = tamanho > 3;
		
		if(!isValidPassword){
			setErrorColorTextConsole();
			printf("Senha muito curta, no m�nimo 4 caracteres.\n");
			setDefaultColorTextConsole();
		}
				   
	} while(!isValidPassword);
	
	printf("\n Criando cadastro... \n");
    strcpy(account.agencyCode, "777");

	account.fk_Client_ID = client.id;
    account.balance = 0.00;    

    ResponseAccount responseAccount;
    responseAccount = createAccount(account);

    strcpy(account.accountNumber, responseAccount.account.accountNumber);
    system("cls");
	printf("Enter para continuar..");
    if(responseAccount.success) {
        setSuccessColorTextConsole(); 
        system("cls");
        printf("===============================================\n");
        printf("=         Voc� agora possui uma conta :)      =\n");
        printf("===============================================\n");
        printf("Aperte enter para continuar.");
        clearBuffer(); 
        infoAccountScreen(); 
    } else {
        setErrorColorTextConsole(); 
        system("cls");
        printf("===============================================\n");
        printf("=        N�o foi poss�vel criar sua conta     =\n");
        printf("===============================================\n");
        printf("Aperte enter para continuar.");
        clearBuffer(); 
        clientInfoScreen(0); 
    }
   
}

void infoAccountScreen() {
    int option;
	setDefaultColorTextConsole();
	
	system("cls");
	printf("====================================\n");
	printf("=             Menu Conta           =\n");
	printf("====================================\n");
	printf("N�mero da Agencia: %s\n", account.agencyCode);
    printf("N�mero da Conta: %s\n", account.accountNumber);
    printf("Saldo: R$ %.2f\n", account.balance);
        
    do {
        printf("\nOp��es:\n");
        printf("1. Depositar\n");
        printf("2. Sacar\n");
        printf("3. Transa��o\n");
        printf("4. Configura��es\n");
        printf("5. Sair\n");
        printf("Escolha uma op��es: ");
        scanf("%d", &option);
		getchar();
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
                initialScreen();
                break;
            default:
            	setErrorColorTextConsole();
                printf("Op��o inv�lida. Tente novamente.");
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
    printf("(0 - Sair)\n");
    printf("Saldo atual: R$%.2f\n", account.balance);
    printf("Digite o quanto deseja depositar: R$");

    scanf("%s", str);
    
    if (strcmp(str, "0") == 0)
    	infoAccountScreen();

    while (!isNumber(str)) {
    	setErrorColorTextConsole();
        printf("Entrada inv�lida!\n");
        setDefaultColorTextConsole();
        printf("Por favor, digite um número: R$");
        scanf("%s", str);
    }
    value = atof(str);
    
    account.balance = account.balance + value;
    
    Property numAccountProp = setProperty("accountNumber", "string", account.accountNumber);
    
    ResponseAccount responseAccount;
    responseAccount = updateAccount(account, numAccountProp);
    
    if (responseAccount.success) {
    	system("cls");
    	setSuccessColorTextConsole();
    	printf("====================================\n");
    	printf("=         Deposito realizado!      =\n");
    	printf("=         Novo saldo: R$%.2f       =\n", account.balance);
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
    	printf("(0 - Sair)\n");
	    printf("Saldo atual: R$%.2f\n", account.balance);
	    printf("Digite o quanto deseja sacar: R$");
	
	    scanf("%s", str);
	    if (strcmp(str, "0") == 0)
    		infoAccountScreen();
    		
	    while (!isNumber(str)) {
	    	setErrorColorTextConsole();
	        printf("Entrada inv�lida!\n");
	        setDefaultColorTextConsole();
	        printf("Por favor, digite um n�mero: R$");
	        scanf("%s", str);
	    }
	    value = atof(str);
	    
	    if (value > account.balance){
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
			account.balance = account.balance - value;
	    
		    Property numAccountProp = setProperty("accountNumber", "string", account.accountNumber);
		    
		    ResponseAccount responseAccount;
		    responseAccount = updateAccount(account, numAccountProp);
		    
		    if (responseAccount.success) {
		    	system("cls");
		    	setSuccessColorTextConsole();
		    	printf("====================================\n");
		    	printf("=         Saque realizado!         =\n");
		    	printf("=         Novo saldo: R$%.2f       =\n", account.balance);
		    	printf("====================================\n");
		    	printf("Aperte enter para continuar.");
		    	clearBuffer();
		    	getchar();
			    infoAccountScreen();
			} else {
				system("cls");
		    	setErrorColorTextConsole();
				printf("================================================\n");
		   	 	printf("=    Oops... Erro ocorrido durante opera��o    =\n");
		    	printf("================================================\n");
		    	printf("Aperte enter para continuar.");
		    	clearBuffer();
		    	getchar();
		    	setDefaultColorTextConsole();
		    	infoAccountScreen();
			}
		}
	} while(value > account.balance);
   
    
}

void loginOptionAccountScreen(Client client) {
	system("cls");
	int option;		
	printf("====================================\n");
	printf("=               Login              =\n");
	printf("====================================\n");
	printf("J� possui uma CONTA para logar?\n");
	do {

		printf("1. Sim\n2. N�o\n3. Voltar\n");
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
			case 3:
				system("cls");
				clientInfoScreen(1);
				break;
			default:
				setErrorColorTextConsole();
                printf("Op��o inv�lida. Tente novamente.\n");
                setDefaultColorTextConsole();
				break;
		}
	}
	while(option != 1 && option != 2);
}

void loginAccountScreen(Client client) {
	char password[100];
	int isNumAccountNull;
	setDefaultColorTextConsole();
	system("cls");
	printf("====================================\n");
	printf("=            Fazer Login           =\n");
	printf("====================================\n");
	
	do {
		
		printf("(0 - sair)\n");
		printf("Digite o numero da sua conta: ");
		scanf("%s", &account.accountNumber);
		
		if(strcmp(account.accountNumber, "0") == 0){
			system("cls");
			loginOptionAccountScreen(client);
		}
		
		Property numAccountProp = setProperty("accountNumber", "string", account.accountNumber);
		account = readAccountByField(numAccountProp);
		
		isNumAccountNull = strcmp(account.accountNumber, "NULL") == 0 || account.fk_Client_ID != client.id;
			
		if (isNumAccountNull) {
			system("cls");
			setWarningColorTextConsole();
			printf("====================================\n");
			printf("=    Numero de Conta inexistente.  =\n");
			printf("=    Tente novamente.               =\n");
			printf("====================================\n");
			setDefaultColorTextConsole();
		} else {
			if(account.active == 0)
			{
				system("cls");
				printf("====================================\n");
				printf("=          Conta desativada        =\n");
				printf("====================================\n");
				
				printf("Identificamos que voc� tinha uma conta conosco mas a excluiu.\n");
				printf("Deseja recuperar sua conta? (S/N):");
					char resposta;
					do {
					    scanf(" %c", &resposta);
						if (resposta == 'S' || resposta == 's') {
						
							int reactivateSuccess = reactiveAccount(numAccountProp);
							system("cls");
							if(reactivateSuccess)
							{
								setSuccessColorTextConsole();
								printf("====================================\n");
								printf("=          Conta Recuperda         =\n");
								printf("=       Fa�a o login novamente     =\n");
								printf("====================================\n");
								printf("Aperte enter para continuar.");
					            clearBuffer();
					            getchar();
								loginAccountScreen(client);
							}			
							else 
							{
								setErrorColorTextConsole();
								printf("===========================================\n");
								printf("=   N�o foi poss�vel recuperar sua conta  =\n");
								printf("=       Tente novamente mais tarde        =\n");
								printf("===========================================\n");
								printf("Aperte enter para continuar.");
					            clearBuffer();
					            getchar();
								loginAccountScreen(client);
							}																	
					    } else if (resposta == 'N' || resposta == 'n') {
					       	createAccountScreen(client);
					    } else {
					        printf("Op��o inv�lida. Responda com S ou N.\n");
					    }
					}	while(resposta != 'S' || resposta != 's' || resposta != 'N' || resposta != 'n');
				
			}
			else {
				int success;
				int attempts = 0;
				
				do{
					printf("Digite sua senha: ");
					scanf("%s", &password);
					
					if (strcmp(password, "0") == 0)
    					loginOptionAccountScreen(client);
    				
					success = strcmp(account.password, password) == 0;
					
					if(success) {
						infoAccountScreen();
					} else {
						system("cls");
						setWarningColorTextConsole();
						printf("=====================================\n");
						printf("= Senha incorreta. Tente Novamente. =\n");
						printf("=====================================\n");
						setDefaultColorTextConsole();
						printf("(0 - sair)\n");
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
			    	exit(0);
				}
			}
			

			
		}
	} while (isNumAccountNull);
}
