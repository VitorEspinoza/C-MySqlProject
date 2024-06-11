#include <stdio.h>
#include <string.h>
#include "accountScreens.h"
#define CPF_SIZE 12
#define RG_SIZE 13
#define NAME_SIZE 101
#define ADDRESS_SIZE 40
#define PHONE_SIZE 12
#define MARITAL_STATUS_SIZE 2

Cliente client;

void createClientScreen();
void printInitialMenuHeader();
void clientInfoScreen(int haveData);
void updateClientScreen();
void deleteClientScreen(int haveData);
	
	
	
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void readInput(char* buffer, int size) {
    fgets(buffer, size, stdin);
     buffer[strcspn(buffer, "\n")] = 0;
}

char* formatPhoneNumber(char* phoneNumber) {
	long long number;
    sscanf(phoneNumber, "%lld", &number);
    char formattedNumber[16] = {0}; 
    sprintf(formattedNumber, "(%02lld) %05lld-%04lld", number / 1000000000, (number % 1000000000) / 10000, number % 10000);
    return formattedNumber;
}
 
typedef int (*ValidatorFunc)(const char*);

void readDocument(char* document, int size, ValidatorFunc validator, const char* documentName, int onlyNumbers) {
    int valid = 0;

    while (!valid) {
    	setDefaultColorTextConsole();
    	
    	if(onlyNumbers)
        	printf("Digite o %s (somente números): ", documentName);
        else
        	printf("Digite o %s: ", documentName);
        	
        scanf("%s", document);
        if (validator(document)) {
            valid = 1;
        } else {
        	setErrorColorTextConsole();
            printf("%s inválido! Digite novamente.\n", documentName);
        }
    }
}

void createClientScreen() {
    system("cls");
    printf("====================================\n");
    printf("=        Cadastro de Cliente       =\n");
    printf("====================================\n");

    clearBuffer();
    
  	char cpf[12];
    readDocument(cpf, sizeof(cpf), isValidCpf, "CPF", 1);
    strcpy(client.cpf, cpf);
    
    clearBuffer();
    
    char rg[13];
    readDocument(rg, sizeof(rg), isValidRg, "RG", 0);
    strcpy(client.rg, rg);
	clearBuffer();
	
    printf("Digite o nome: ");
    readInput(client.nome, NAME_SIZE);

    printf("Digite o endereço: ");
    readInput(client.endereco, ADDRESS_SIZE);

    printf("\nDigite o telefone (Somente números): ");
    readInput(client.telefone, PHONE_SIZE);

	printf("Digite o estado civil (1 - Solteiro, 2 - Casado): ");	
	int maritalStatus; 
	scanf("%d", &maritalStatus);
	clearBuffer();
	
	while(maritalStatus != 1 && maritalStatus != 2) {
	    printf("Por favor, digite um valor válido.");
	    printf("Estado civil (1 - Solteiro, 2 - Casado): ");
	    scanf("%d", &maritalStatus);
	    clearBuffer();
	}

	client.estadoCivil = maritalStatus == 1 ? Solteiro : Casado;

	
    int success = createClient(client);
    
    if(success) {
    	setSuccessColorTextConsole();
    	system("cls");
       	printf("===============================================\n");
	    printf("=   Você é oficialmente um cliente nosso :)   =\n");
	    printf("===============================================\n");
        clientInfoScreen(true);
    }
    else{
    	system("cls");
    	setErrorColorTextConsole();
    	printf("=============================================================================================\n");
	 	printf("=     Ops, parece que houve algo de errado ao te cadastrar. Tente novamente mais tarde.     =\n");
	    printf("=============================================================================================\n");
    }
}

void printInitialMenuHeader() {
	printf("====================================\n");
    printf("=           Menu Inicial           =\n");
    printf("====================================\n");
}
void clientInfoScreen(int haveData) {
	setDefaultColorTextConsole();
	if(!haveData) 
		system("cls");

	printInitialMenuHeader();	
	
	if(!haveData) 
	{
		int result;
		do {
			setDefaultColorTextConsole();
			int c;
			while ((c = getchar()) != '\n' && c != EOF) {}
			printf("Por favor, digite o seu CPF para que possamos te identificar: ");
			char cpf[11];
			scanf("%s", &cpf);
			Propriedade cpfProp = setPropriedade("cpf", "string", cpf);
			client = readClientByField(cpfProp);
			result = strcmp(client.rg, "NULL");
		
			if(result == 0){
				setErrorColorTextConsole();
				printf("CPF não cadastrado na base, tente novamente.\n\n");
			}
			else {
				system("cls");
				printInitialMenuHeader();
			}
		}
		while(result == 0);
	}
	
    setDetachColorTextConsole();
    printf("\n\nSeja bem vindo, %s!\n", client.nome);
	printf("Informações do seu cadastro:\n\n");
	setDefaultColorTextConsole();
	printf("CPF: %s\n", client.cpf);
	printf("RG: %s\n", client.rg);
	printf("Nome: %s\n", client.nome);
	printf("Endereço: %s\n", client.endereco);
	printf("Telefone: %s\n", formatPhoneNumber(client.telefone));
	printf("Estado Civil: %s\n", client.estadoCivil == Solteiro ? "Solteiro" : "Casado");
	

	int option;
	do {
	
			printf("Selecione como deseja prosseguir: \n");
			printf("1. Fazer login na conta e realizar transações\n");
			printf("2. Editar as informações atuais\n");
			printf("3. Excluir meu cadastro\n");
			
			scanf("%d", &option);
			getchar();
			
			switch(option) {
			    case 1:
			        loginOptionAccountScreen(client);	
			        break;
			    case 2:
			        updateClientScreen();
			        break;
			    case 3:
			        deleteClientScreen(0);
			        break;
			    default:
            	setErrorColorTextConsole();
                printf("Opção inválida. Tente novamente.\n");
                setDefaultColorTextConsole();
			}
		}
	while(option != 1 && option != 2 && option != 3);
}	
	


void updateClientScreen() {
    char buffer[40];
 
	int option;
    do {
        system("cls");
        printf("====================================\n");
        printf("=          Editar Cliente          =\n");
        printf("====================================\n");
        printf("1. Editar CPF\n");
        printf("2. Editar RG\n");
        printf("3. Editar nome\n");
        printf("4. Editar endereço\n");
        printf("5. Editar telefone\n");
        printf("6. Editar estado civil\n");
        printf("7. Finalizar\n");
        printf("\nSelecione a opção desejada: ");
		scanf("%d", &option);
		getchar();

        switch(option) {
            case 1:
                printf("CPF atual: %s", client.cpf);
               	char cpf[12];
		   		readDocument(cpf, sizeof(cpf), isValidCpf, "CPF", 1);
		   	 	strcpy(client.cpf, cpf);
		    	clearBuffer();
                break;
            case 2:
                printf("RG atual: %s", client.rg);
               	char rg[13];
		   		readDocument(rg, sizeof(rg), isValidCpf, "RG", 0);
		   	 	strcpy(client.rg, rg);
		    	clearBuffer();
                break;
            case 3:
                printf("Nome atual: %s", client.nome);
                printf("\nDigite o novo nome: ");
                readInput(client.nome, NAME_SIZE);
                break;
            case 4:
                printf("Endereço atual: %s", client.endereco);
                printf("\nDigite o novo endereço: ");
                readInput(client.endereco, ADDRESS_SIZE);
                break;
            case 5:
                printf("Telefone atual: %s", formatPhoneNumber(client.telefone));
                printf("\nDigite o novo telefone (Somente números): ");
                readInput(client.telefone, PHONE_SIZE);
                break;
            case 6:
                printf("Estado civil atual: %s\n", client.estadoCivil == Solteiro ? "Solteiro" : "Casado");
	            printf("Digite o estado civil (1 - Solteiro, 2 - Casado): ");	
           
				int maritalStatus; 
				scanf("%d", &maritalStatus);
				clearBuffer();		
				while(maritalStatus != 1 && maritalStatus != 2) {
				    printf("Por favor, digite um valor válido.");
				    printf("Estado civil (1 - Solteiro, 2 - Casado): ");
				    scanf("%d", &maritalStatus);
				    clearBuffer();
				}
				client.estadoCivil = maritalStatus == 1 ? Solteiro : Casado;
                break;
            case 7:
                printf("Finalizando...\n");
                break;
            default:
            	setErrorColorTextConsole();
                printf("Opção inválida. Tente novamente.\n");
                setDefaultColorTextConsole();
        }
    } while(option != 7);
    system("cls");
    
    Propriedade cpfProp = setPropriedade("cpf", "string", client.cpf);
    const success = updateClient(client, cpfProp);
    
    if(success) {
    	setSuccessColorTextConsole();
    	system("cls");
    	printf("====================================\n");
	    printf("Dados atualizados com sucesso!\n");
	    printf("====================================\n");
	}
	else {
		setErrorColorTextConsole();
		system("cls");
		printf("=============================================\n");
	    printf("Houve um problema ao atualizar seus dados :/\n");
	    printf("Por favor, tente novamente mais tarde.\n");
	    printf("=============================================\n");
	}
    clientInfoScreen(true);
}

void deleteClientScreen(int haveData) {
	if(!haveData)
		system("cls");
	setDefaultColorTextConsole();
	printf("====================================\n");
    printf("=         Exclusão de conta        =\n");
    printf("====================================\n");
    
    setWarningColorTextConsole();
    printf("Tem certeza que deseja excluir sua conta?\n");
    printf("Seus dados e informações serão perdidos.\n");
   	setDefaultColorTextConsole();
    int option;
    	
    do {
		printf("\nSelecione a opção desejada:\n\n");
		printf("1. Excluir conta\n");
		printf("2. Retornar ao menu\n");
		
		scanf("%d", &option);
		getchar();
		
		
    	 switch(option) {
            case 1:     
                printf("Confirme o seu cpf para prosseguir com a exclusão: ");
                char confirmCpf[12];
                fgets(confirmCpf, 12, stdin);
                confirmCpf[strcspn(confirmCpf, "\n")] = 0; 
                
                int result = strcmp(client.cpf, confirmCpf);
                 
                if(result == 0) {
                 	Propriedade cpfProp = setPropriedade("cpf", "string", client.cpf);
                 	
					int deleteSuccess = deleteClient(cpfProp);
					
					if(deleteSuccess) {
						setSuccessColorTextConsole();
						system("cls");
						printf("====================================\n");
						printf("=      Sua conta foi excluída      =\n");
          				printf("====================================\n");
        
          				telaInicial(1);
					}
					else {
						setErrorColorTextConsole();
						system("cls");
						printf("====================================\n");
						printf("=     Houve um erro ao excluir     =\n");
						printf("=    Tente novamente mais tarde    =\n");
          				printf("====================================\n");
          				clientInfoScreen(1);
					}
					
				}
          		else {
          			setErrorColorTextConsole();
          			printf("Cpf digitado inválido.\n");
          			printf("====================================\n");
          			
          			deleteClientScreen(1);
				}
                break;
            case 2:
                clientInfoScreen(0);
                break;
           
            default:
            	setErrorColorTextConsole();
                printf("Opção inválida. Tente novamente.\n");
                setDefaultColorTextConsole();
                break;
        }
    } while(option != 1 && option != 2);
	
}

