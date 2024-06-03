#include <stdio.h>
#include <string.h>
#include "transacao.h"
#include "transactionController.h"

void transactionMenuScreen(Conta* account);
void realizeTransaction(Conta* account);
void consultBalance();

Transaction transaction;

void transactionMenuScreen(Conta* account) {
	int option;
	
	system("cls");
	printf("====================================\n");
    printf("=         Menu de Transa��es        =\n");
    printf("====================================\n");
    printf("Escolha o que deseja fazer:\n");
    printf("1. Realizar transa��o\n");
    printf("2. Consultar transa��es\n");
    printf("3. Voltar\n");
    printf("Digite sua escolha: ");
    scanf("%d", &option);
    
    do{
    	switch(option){
    		case 1:
    			realizeTransaction(account);
    		case 2:
    			consultBalance(account);
    		case 3:
    			printf("voltar");
    		default:
    			printf("Op��o inv�lida. Tente novamente.");
		}
	}while (option != 1 && option != 2 && option != 3);
}

void realizeTransaction(Conta* account) {
	int isSufficientSaldo;
	
	system("cls");
	printf("====================================\n");
    printf("=             Transa��o            =\n");
    printf("====================================\n");
    
    strcpy(transaction.numeroConta, account->numeroConta);
			    
	printf("Saldo atual: R$ %.2f\n", account->saldo);
    printf("Digite o valor da transa��o: R$ ");
    scanf("%lf", &transaction.quantia);
    
    isSufficientSaldo = transaction.quantia <= account->saldo;
    
    if (isSufficientSaldo) {
		printf("Digite o numero da conta destino da transacao: ");
	    scanf("%s", &transaction.contaDestino);
	    
	    printf("Tipo pagamento (0 - Credito, 1 - Debito): ");
	    scanf("%d", &transaction.paymentType);
		
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
    	printf("= Transa��o realizada com sucesso! =\n");
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
    printf("=      Hist�rico de Transa��es     =\n");
    printf("====================================\n");
	if (responseTransactions.numberOfRows == 0) {
		setWarningColorTextConsole();
   	 	printf("Voc� ainda n�o fez transa��es.\n");
	} else {
		for (i=0; responseTransactions.transactions[i] != NULL; i++) {
			if (responseTransactions.transactions[i] != NULL) {		
				printf("\n--------------------------------------------\n");
				printf("Data: %s  Hora: %s\n", responseTransactions.transactions[i]->data, responseTransactions.transactions[i]->hora);
				printf("Valor: %.2f  Tipo de pagamento: %s\n", responseTransactions.transactions[i]->quantia, PaymentTypeToString(responseTransactions.transactions[i]->paymentType));
				printf("Conta destino: %s", responseTransactions.transactions[i]->contaDestino);
				printf("\n--------------------------------------------\n");
			}
		}
	}
	setDefaultColorTextConsole();
	printf("Digite 1 para voltar: ");
	scanf("%d", &option);
	if (option == 1){
		infoAccountScreen();
	}
}
