#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h> 
#include <mysql.h>
#include <mysqld_error.h>
#include "databaseConnection.h"

#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

typedef struct {
    char Nome[50];
    char Tipo[10];
    char Valor[50]; 
} Propriedade;

Propriedade setPropriedade(char nome[50], char tipo[10], char valor[50]){
	Propriedade P;
	strcpy(P.Nome, nome); 
	strcpy(P.Tipo, tipo);
	strcpy(P.Valor, valor); 

	return P;
}

const int create(char tabela[50], int numPropriedades, ...) {
    char scriptSQL[500]; 
    sprintf(scriptSQL, "INSERT INTO %s (", tabela);
    va_list args;
    va_start(args, numPropriedades);
    
    Propriedade propriedadesArray[numPropriedades];
    int i;
    for (i = 0; i < numPropriedades; ++i) {
         propriedadesArray[i] = va_arg(args, Propriedade);
        
  
        sprintf(scriptSQL + strlen(scriptSQL), "%s", propriedadesArray[i].Nome);

        if (i < numPropriedades - 1) {
            sprintf(scriptSQL + strlen(scriptSQL), ", ");
        }
    }

    sprintf(scriptSQL + strlen(scriptSQL), ") VALUES (");

    for (i = 0; i < numPropriedades; ++i) {

        int resultado = strcmp(propriedadesArray[i].Tipo, "double");
        
        if (strcmp(propriedadesArray[i].Tipo, "int") == 0)
		{
            int valorInt = atoi(propriedadesArray[i].Valor);
            sprintf(scriptSQL + strlen(scriptSQL), "%d", valorInt);
        } else if (strcmp(propriedadesArray[i].Tipo, "double") == 0) 
		{
            double valorDouble = atof(propriedadesArray[i].Valor);
            sprintf(scriptSQL + strlen(scriptSQL), "%.2f", valorDouble);
        } else 
		{
            sprintf(scriptSQL + strlen(scriptSQL), "'%s'", propriedadesArray[i].Valor);
        }

		const isLastItem = i == numPropriedades - 1;
        if (!isLastItem) {
            sprintf(scriptSQL + strlen(scriptSQL), ", ");
        }
    }

    sprintf(scriptSQL + strlen(scriptSQL), ");\n");

    va_end(args);
    
    printf(scriptSQL);

  	int success = 0;
			    if (mysql_ping(mySqlInstance)) {
			        printf("ERROR: Impossível conectar.\n");
			        printf("%s\n", mysql_error(mySqlInstance));
			    }
			
			    if (mysql_query(mySqlInstance, scriptSQL)) {
			        printf("ERROR: %s\n", mysql_error(mySqlInstance));
			        rewind(stdin);
			        getchar();
			    } else {
			        printf("Informações adicionadas corretamente.\n");
			        success = 1;
			    }
  			
				mysql_store_result(mySqlInstance);
				
    return success;
}


#endif

