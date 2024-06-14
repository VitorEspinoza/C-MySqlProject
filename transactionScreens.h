#include <stdio.h>
#include <string.h>
#include "transaction.h"
#include "transactionController.h"

void transactionMenuScreen(Account* account);
void realizeTransaction(Account* account);
void consultBalance();
int isTargetAccountReal(char numTargetAccount[100]);

Transaction transaction;

void transactionMenuScreen(Account* account) {
	int option;
	
	system("cls");
	printf("====================================\n");
    printf("=         Menu de Transação        =\n");
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

void realizeTransaction(Account* account) {
	int isSufficientBalance;
	char str[100];
	double value;
	
	system("cls");
	printf("====================================\n");
    printf("=             Transação           =\n");
    printf("====================================\n");
    
    strcpy(transaction.accountNumber, account->accountNumber);
			    
	printf("Saldo atual: R$ %.2f\n", account->balance);
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
    
    transaction.amount = value;
    
    isSufficientBalance = transaction.amount <= account->balance;
    
    if (isSufficientBalance) {
    	
		printf("Digite o numero da conta destino da transação: ");
	    scanf("%s", &transaction.targetAccount);
	    
	    while (!isNumber(transaction.targetAccount)) {
	    	setErrorColorTextConsole();
	        printf("Entrada inválida!\n");
	        setDefaultColorTextConsole();
	        printf("Por favor, digite um número de conta: ");
	        scanf("%s", transaction.targetAccount);
	    }
	    
	    while (!isTargetAccountReal(transaction.targetAccount)) {
	    	setErrorColorTextConsole();
	        printf("Conta destino inexistente!\n");
	        setDefaultColorTextConsole();
	        printf("Por favor, um número de conta existente: ");
	        scanf("%s", &transaction.targetAccount);
	    }
	    
	    while (strcmp(transaction.targetAccount, account->accountNumber) == 0) {
			setErrorColorTextConsole();
	        printf("Você não pode realizar uma auto transação!\n");
	        printf("Tente novamente\n");
	        setDefaultColorTextConsole();
	        printf("Por favor, digite um número de conta: ");
	        scanf("%s", transaction.targetAccount);     
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
	    strcpy(transaction.date, strDate);
	    strcpy(transaction.hour, strHour);
	    createTransaction(transaction);
	    
	    account->balance = account->balance - transaction.amount;
	    
	    Property numAccountSourceProp = setProperty("accountNumber", "string", transaction.accountNumber);
	    updateAccount(*account, numAccountSourceProp);
	    
	    Property numTargetAccountProp = setProperty("accountNumber", "string", transaction.targetAccount);
	    Account targetAccount = readAccountByField(numTargetAccountProp);
	    
	    targetAccount.balance = targetAccount.balance + transaction.amount;
	    updateAccount(targetAccount, numTargetAccountProp);
	    
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

void consultBalance(Account account){
    int i;
	char numAccountString[50];
	int option;
	strcpy(numAccountString, account.accountNumber);
				
	ResponseTransactions responseTransactions;				
	responseTransactions = readAllTransactions(numAccountString);
	
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
			printf("Data: %s  Hora: %s\n", responseTransactions.transactions[i]->date, responseTransactions.transactions[i]->hour);
			printf("Valor: %.2f  Tipo de pagamento: %so\n", responseTransactions.transactions[i]->amount, PaymentTypeToString(responseTransactions.transactions[i]->paymentType));
			printf("Conta destino: %s", responseTransactions.transactions[i]->targetAccount);
			printf("\n--------------------------------------------\n");
		}
	}
	setDefaultColorTextConsole();
	printf("Digite 1 para voltar: ");
	scanf("%d", &option);
	getchar();
	if (option == 1){
		freeTransactions(&responseTransactions);
		infoAccountScreen();
	}
}

int isTargetAccountReal(char numTargetAccount[100]) {
	Property numTargetAccountProp = setProperty("accountNumber", "string", numTargetAccount);
	Account targetAccount = readAccountByField(numTargetAccountProp);
	
	int accountExist = strcmp(targetAccount.accountNumber, "NULL") != 0 && targetAccount.active == 1;

	if (accountExist)
		return 1;
	 else 
		return 0;
}
