#include <stdio.h>
#include <string.h>

void configMenuScreen(Account* account);
void changePasswordScreen(Account* account);
void deleteAccountScreen(Account* account);

void configMenuScreen(Account* account) {
	int option;
	system("cls");
	printf("====================================\n");
    printf("=       Configurações de Conta     =\n");
    printf("====================================\n");
    
	do {	
	    printf("1. Trocar senha\n");
	    printf("2. Excluir conta\n");
	    printf("3. Voltar\n");
	    scanf("%d", &option);
	    getchar();
	    
	    switch(option) {
	    	case 1:
	    		changePasswordScreen(account);
	    		break;
	    	case 2:
	    		system("cls");
	    		deleteAccountScreen(account);
	    		break;
	    	case 3:
	    		infoAccountScreen();
	    		break;
	    	default:
	    		setErrorColorTextConsole();
	    		printf("Opção inválida. Tente novamente.\n");
	    		setDefaultColorTextConsole();
		}
		
	} while (option != 1 && option != 2 && option != 3);

}

void changePasswordScreen(Account* account) {
    char oldPassword[100];
    char newPassword[100];
    char confirmPassword[100];
    int isPasswordCorrect, isEqualPassword, attempts = 0;

    system("cls");
    printf("====================================\n");
    printf("=             Trocar Senha         =\n");
    printf("====================================\n");

	do {    
		printf("Digite sua senha atual: ");
	    scanf("%s", oldPassword);
		attempts++;
	    isPasswordCorrect = strcmp(oldPassword, account->password) == 0;
	    
		if(isPasswordCorrect) {
			do {
			
		        printf("Digite sua nova senha: ");
		        scanf("%s", newPassword);
		
		        printf("Confirme sua nova senha: ");
		        scanf("%s", confirmPassword);
		
				isEqualPassword = strcmp(newPassword, confirmPassword) == 0;
				
		        if (isEqualPassword) {
		            strcpy(account->password, confirmPassword);
					
					Property accountNumberProp = setProperty("accountNumber", "string", account->accountNumber);
		            updateAccount(*account, accountNumberProp);
		
		            system("cls");
		            setSuccessColorTextConsole();
		            printf("====================================\n");
		            printf("=     Senha trocada com sucesso.   =\n");
		            printf("====================================\n");
		            printf("Aperte enter para continuar.");
		            clearBuffer();
		            getchar();
		            infoAccountScreen();
		        } else {
		        	setErrorColorTextConsole();
		        	printf("As senhas não são iguais. Tente novamente!\n");
		        	setDefaultColorTextConsole();
				}
		        
			} while(!isEqualPassword);
	        
        } else if (attempts == 3) {
	    	setErrorColorTextConsole();
	    	printf("Número de tentativas excedido.\n");
			setDefaultColorTextConsole();
	    	printf("Aperte enter para voltar");
	    	clearBuffer();
	    	getchar();
	    	infoAccountScreen();
	    	
		} else {
        	setErrorColorTextConsole();
        	printf("Senha incorreta! Tente novamente\n");
        	setDefaultColorTextConsole();
		}
		

		
	} while (!isPasswordCorrect && attempts < 3);
    

}

void deleteAccountScreen(Account* account){
	int option;
	int success;
	int password[100];
	int isPasswordCorrect;
	
	
    setWarningColorTextConsole();
	printf("===============================================\n");
    printf("=  Tem certeza que deseja excluir sua conta?  =\n");
    printf("===============================================\n");

    
    do{    
		printf("1. Sim\n");
	    printf("2. NÃ£o\n");
	    scanf("%d", &option);
	    getchar();
    	switch(option){
    		case 1:
    			printf("Senha: ");
    			scanf("%s", password);
    			
    			isPasswordCorrect = strcmp(account->password, password) == 0;
    			
    			if (isPasswordCorrect){ 
    			
					success = deleteAccount(numAccountProp);
	    			
	    			if (success) {
			            system("cls");
			            setSuccessColorTextConsole();
			            printf("====================================\n");
			            printf("=    Account excluida com sucesso.   =\n");
			            printf("====================================\n");
			            printf("Aperte enter para continuar.");
			            clearBuffer();
	            		getchar();
	            		system("cls");
	            		initialScreen();
					}
				}
				break;
    		case 2:
    			infoAccountScreen();
    			break;
    		default:
    			setErrorColorTextConsole();
    			printf("OpÃ§Ã£o invÃ¡lida. Tente novamente.\n");
    			setWarningColorTextConsole();
		}
	}while(option != 1 && option != 2);
            
}
