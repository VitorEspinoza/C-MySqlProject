#include <stdio.h>
#include <string.h>
#include "transacao.h"
#include "transactionController.h"

void transactionMenuScreen(Conta* account);
void realizeTransaction(Conta* account);
void consultBalance();
int isDestinationAccountReal(char numDestinationAccount[100]);

Transaction transaction;

void transactionMenuScreen(Conta* account) {
	int option;
	
	system("cls");
	printf("====================================\n");
    printf("=         Menu de Transações        =\n");
    printf("====================================\n");

    do{    
		printf("Escolha o que deseja fazer:\n");
	    printf("1. Realizar transação\n");
	    printf("2. Consultar transações\n");
	    printf("3. Voltar\n");
	    printf("Digite sua escolha: ");
	    scanf("%d", &option);
	    getchar();
	    
    	switch(option){
    		case 1:
    			realizeTransaction(account);
    			break;
    		case 2:
    			consultBalance(account);
    			break;
    		case 3:
    			infoAccountScreen();
    			break;
    		default:
    			setErrorColorTextConsole();
    			printf("Opção inválida. Tente novamente.\n");
    			setDefaultColorTextConsole();
    			break;
		}
	} while (option != 1 && option != 2 && option != 3);
}

void realizeTransaction(Conta* account) {
	int isSufficientSaldo;
	char str[100];
	double value;
	
	system("cls");
	printf("====================================\n");
    printf("=             Transação            =\n");
    printf("====================================\n");
    
    strcpy(transaction.numeroConta, account->numeroConta);
			    
	printf("Saldo atual: R$ %.2f\n", account->saldo);
    printf("Digite o valor da transação: R$ ");
    scanf("%s", str);
    while (!isNumber(str)) {
    	setErrorColorTextConsole();
        printf("Entrada inválida!\n");
        setDefaultColorTextConsole();
        printf("Por favor, digite um número: R$");
        scanf("%s", str);
    }
    value = atof(str);
    
    transaction.quantia = value;
    
    isSufficientSaldo = transaction.quantia <= account->saldo;
    
    if (isSufficientSaldo) {
    	
		printf("Digite o numero da conta destino da transação: ");
	    scanf("%s", &transaction.contaDestino);
	    
	    while (!isNumber(transaction.contaDestino)) {
	    	setErrorColorTextConsole();
	        printf("Entrada inválida!\n");
	        setDefaultColorTextConsole();
	        printf("Por favor, digite um número de conta: ");
	        scanf("%s", &transaction.contaDestino);
	    }
	    
	    while (!isDestinationAccountReal(transaction.contaDestino)) {
	    	setErrorColorTextConsole();
	        printf("Conta destino inexistente!\n");
	        setDefaultColorTextConsole();
	        printf("Por favor, um número de conta existente: ");
	        scanf("%s", &transaction.contaDestino);
	    }
	    
	    printf("Tipo pagamento (0 - Credito, 1 - Debito): ");
		scanf("%d", &transaction.paymentType);
		
	    while (transaction.paymentType != 0 && transaction.paymentType != 1) {
	    	setErrorColorTextConsole();
	        printf("Entrada inválida!\n");
	        setDefaultColorTextConsole();
			printf("Tipo pagamento (0 - Credito, 1 - Debito): ");
			scanf("%d", &transaction.paymentType);
		}
		
		time_t t = time(NULL);
	    struct tm *tm = localtime(&t);
	    char strDate[64], strHour[64];
	    
	    strftime(strDate, sizeof(strDate), "%Y-%m-%d", tm);
	    strftime(strHour, sizeof(strHour), "%H:%M:%S", tm);
	    
	    strDate[11]= '\0';
	    strcpy(transaction.data, strDate);
	    strcpy(transaction.hora, strHour);
	    createTransaction(transaction);
	    
	    account->saldo = account->saldo - transaction.quantia;
	    
	    Propriedade numAccountSourceProp = setPropriedade("numeroConta", "string", transaction.numeroConta);
	    updateAccount(*account, numAccountSourceProp);
	    
	    Propriedade numAccountDestinationProp = setPropriedade("numeroConta", "string", transaction.contaDestino);
	    Conta accountDestination = readContaByField(numAccountDestinationProp);
	    
	    accountDestination.saldo = accountDestination.saldo + transaction.quantia;
	    updateAccount(accountDestination, numAccountDestinationProp);
	    
		system("cls");
		setSuccessColorTextConsole();
		printf("====================================\n");
    	printf("= Transação realizada com sucesso! =\n");
    	printf("====================================\n");
    	printf("Aperte enter para continuar.");
    	clearBuffer();
    	getchar();
		infoAccountScreen();
	}
}

void consultBalance(Conta account){
    int i;
	char numContaString[50];
	int option;
	strcpy(numContaString, account.numeroConta);
				
	ResponseTransactions responseTransactions;				
	responseTransactions = readAllTransactions(numContaString);
	
	system("cls");
	printf("====================================\n");
	printf("=      Histórico de Transações     =\n");
	printf("====================================\n");
	if (responseTransactions.numberOfRows == 0) {
		setWarningColorTextConsole();
		printf("Você ainda não fez transações.\n");
	} else {
		for (i=0; responseTransactions.transactions[i] != NULL; i++) {
			printf("\n--------------------------------------------\n");
			printf("Data: %s  Hora: %s\n", responseTransactions.transactions[i]->data, responseTransactions.transactions[i]->hora);
			printf("Valor: %.2f  Tipo de pagamento: %s\n", responseTransactions.transactions[i]->quantia, PaymentTypeToString(responseTransactions.transactions[i]->paymentType));
			printf("Conta destino: %s", responseTransactions.transactions[i]->contaDestino);
			printf("\n--------------------------------------------\n");
		}
	}
	setDefaultColorTextConsole();
	printf("Digite 1 para voltar: ");
	scanf("%d", &option);
	getchar();
	if (option == 1){
		infoAccountScreen();
	}
}

int isDestinationAccountReal(char numDestinationAccount[100]) {
	Propriedade numDestAccountProp = setPropriedade("numeroconta", "string", numDestinationAccount);
	Conta destAccount = readContaByField(numDestAccountProp);
	
	int accountExist = strcmp(destAccount.numeroConta, "NULL") != 0;

	if (accountExist)
		return 1;
	 else 
		return 0;
}
