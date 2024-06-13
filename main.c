#include <locale.h>
#include <stdio.h>
#include <string.h>

#include "client.h"
#include "databaseConnection.h"
#include "clientController.h"
#include "account.h"
#include "accountController.h"
#include "generalScreens.h"
#include "clientScreens.h"
#include "consoleUtils.h"

void setLocale();
int isNumber(char s[]);


int main() {
	setLocale();
	const connectionMySqlSuceed = initMySqlConnection();
	if(!connectionMySqlSuceed)
	printf("fim");
	initHConsole();
	setDefaultColorTextConsole();
    initialScreen();

    return 0;
}

void setLocale() {
	setlocale(LC_ALL, "Portuguese");
	setlocale(LC_NUMERIC, "C");
}

int isNumber(char s[]) {
    int i, len = strlen(s);
    int dotCount = 0;

    for (i = 0; i < len; i++) {
        if (s[i] == '.') {
            dotCount++;
            if (dotCount > 1) return 0;
        } else if (!isdigit(s[i])) {
            return 0;
        }
    }
    return 1;
}



