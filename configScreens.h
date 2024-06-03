#include <stdio.h>
#include <string.h>

void configMenuScreen(Conta* account);
void changePasswordScreen(Conta* account);
void deleteAccountScreen(Conta* account);

void configMenuScreen(Conta* account) {
	int option;

	do {	
		system("cls");
		printf("====================================\n");
	    printf("=       Configurações de Conta     =\n");
	    printf("====================================\n");
	    printf("1. Trocar senha\n");
	    printf("2. Excluir conta\n");
	    printf("3. Voltar\n");
	    scanf("%d", &option);
	    
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
	    		printf("Opção inválida. Tente novamente.");
		}
		
	} while (option != 1 && option != 2 && option != 3);

}

void changePasswordScreen(Conta* account) {
    char oldPassword[100];
    char newPassword[100];
    char confirmPassword[100];
    int isPasswordCorrect, isEqualPassword;

    system("cls");
    printf("====================================\n");
    printf("=             Trocar Senha         =\n");
    printf("====================================\n");
    printf("Digite sua senha atual: ");
    scanf("%s", oldPassword);

    isPasswordCorrect = strcmp(oldPassword, account->senha) == 0;

    if(isPasswordCorrect) {
        printf("Digite sua nova senha: ");
        scanf("%s", newPassword);

        printf("Confirme sua nova senha: ");
        scanf("%s", confirmPassword);

		isEqualPassword = strcmp(newPassword, confirmPassword) == 0;
		
        if (isEqualPassword) {
            strcpy(account->senha, confirmPassword);
			
			Propriedade numAccountProp = setPropriedade("numeroConta", "string", account->numeroConta);
            updateAccount(*account, numAccountProp);

            system("cls");
            setSuccessColorTextConsole();
            printf("====================================\n");
            printf("=     Senha trocada com sucesso.   =\n");
            printf("====================================\n");
            printf("Aperte enter para continuar.");
            clearBuffer();
            getchar();
            infoAccountScreen();
        }
    }
}

void deleteAccountScreen(Conta* account){
	int option;
	int success;
	int password[100];
	int isPasswordCorrect;
	
	Propriedade numAccountProp = setPropriedade("numeroConta", "string", account->numeroConta);
	
    setWarningColorTextConsole();
    printf("=========================================\n");
    printf("= Certeza que deseja excluir sua conta? =\n");
    printf("= Essa operação é irreversível.         =\n");
    printf("=========================================\n");
    printf("1. Sim\n");
    printf("2. Não\n");
    scanf("%d", &option);
    
    do{
    	switch(option){
    		case 1:
    			printf("Senha: ");
    			scanf("%s", &password);
    			
    			isPasswordCorrect = strcmp(account->senha, password) == 0;
    			
    			if (isPasswordCorrect){ 
    			
					success = deleteConta(numAccountProp);
	    			
	    			if (success) {
			            system("cls");
			            setSuccessColorTextConsole();
			            printf("====================================\n");
			            printf("=    Conta excluida com sucesso.   =\n");
			            printf("====================================\n");
			            printf("Aperte enter para continuar.");
			            clearBuffer();
	            		getchar();
	            		system("cls");
	            		telaInicial();
					}
				}
				break;
    		case 2:
    			infoAccountScreen();
    			break;
    		default:
    			printf("Opção inválida. Tente novamente.");
		}
	}while(option != 1 && option != 2);
            
}
