#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "account.h"
#include "databaseController.h"

typedef struct {
	int success;
	Account account;
} ResponseAccount;

char* randomFourDigitNumber();
Account readAccountByField(Property property);

Property* setPropertiesAccount(Account account) {
	
    static Property properties[5];
	
	char accountBalance[50];
	sprintf(accountBalance, "%lf", account.balance);
	
	char clientId[50];
	sprintf(clientId, "%d", account.fk_Client_ID);
	
    properties[0] = setProperty("fk_Client_ID", "int", clientId);
    properties[1] = setProperty("agencyCode", "string", account.agencyCode);
    properties[2] = setProperty("balance", "double", accountBalance);
    properties[3] = setProperty("password", "string", account.password);
    properties[4] = setProperty("accountNumber", "string", account.accountNumber);

    return properties;
}

ResponseAccount createAccount(Account account) {
	
	char* generatedNumber;
	Property numAccountProp;
	Account existingAccount;
	int isExist;
	
	do {
		generatedNumber = randomFourDigitNumber();
		numAccountProp = setProperty("accountNumber", "string", generatedNumber);
		existingAccount = readAccountByField(numAccountProp);
		isExist = strcmp(existingAccount.accountNumber, "NULL") != 0;
		
	} while(isExist);

    strcpy(account.accountNumber, generatedNumber);
    free(generatedNumber);
    
	Property* properties = setPropertiesAccount(account);

	
	ResponseAccount responseAccount;
	responseAccount.success = create("Account", 5, properties[0], properties[1], properties[2], properties[3], properties[4]);
	
	responseAccount.account = account;
	
	return responseAccount;
}

Account readAccountByField(Property property) {
	MYSQL_ROW row = readByField("account", property);

	Account account;
	
	if(row == NULL) {
		strcpy(account.accountNumber, "NULL");
		clearResult();
		return account;
	}
	
	strcpy(account.accountNumber, row[0]);
	account.balance = atof(row[1]);
	strcpy(account.agencyCode, row[2]);
	account.fk_Client_ID = atoi(row[3]);
	strcpy(account.password, row[4]);
	account.active = atoi(row[5]);
	clearResult();
	return account;

}

ResponseAccount updateAccount(Account account, Property identifierField) {

  	Property* properties = setPropertiesAccount(account);
  	
  	ResponseAccount responseAccount;
	responseAccount.success = update("Account", identifierField, 5, properties[0], properties[1], properties[2], properties[3], properties[4]);
	
	responseAccount.account = account;
	
	return responseAccount;
}

int deleteAccount(Property identifierField) {
	Property activeAccount = setProperty("active", "int", "0");
	int success = update("account", identifierField, 1, activeAccount);
	return success;
}

int reactiveAccount(Property identifierField) {
	Property activeAccount = setProperty("active", "int", "1");
	int success = update("account", identifierField, 1, activeAccount);
	return success;
}


char* randomFourDigitNumber() {
    srand(time(NULL));
    int number = rand() % 9000 + 1000; 

    char* str = malloc(5 * sizeof(char)); 
    if (str == NULL) {
        exit(1);
    }

    sprintf(str, "%d", number); 

    return str;
}
