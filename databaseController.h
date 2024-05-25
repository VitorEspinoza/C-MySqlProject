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

MYSQL_RES *result;

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

typedef void (*filler_func)(void*, MYSQL_ROW);

void** readAll(char tableName[50], filler_func fill, size_t structSize) {
    char scriptSQL[500];
    sprintf(scriptSQL, "SELECT * FROM %s;", tableName);

    void** array = NULL;
    int count = 0;

    if (mySqlInstance == NULL) {
        printf("ERROR: mySqlInstance é NULL\n");
        return NULL;
    }

    if (mysql_ping(mySqlInstance)) {
        printf("ERROR: Impossível conectar.\n");
        printf("%s\n", mysql_error(mySqlInstance));
        return NULL;
    }


    if (mysql_query(mySqlInstance, scriptSQL) == 0) {
        MYSQL_RES *result = mysql_store_result(mySqlInstance);

        if (result) {
            MYSQL_ROW row;

            while ((row = mysql_fetch_row(result))) {
                array = realloc(array, (count + 1) * sizeof(void*));
                array[count] = malloc(structSize);
                fill(array[count], row);

                count++;
            }
            mysql_free_result(result);
        } else {
            printf("Erro ao obter resultados: %s\n", mysql_error(mySqlInstance));
        }
    } else {
        printf("Erro na consulta: %s\n", mysql_error(mySqlInstance));
    }

    return array;
}

MYSQL_ROW readByField(char tabela[50], Propriedade field)
{
	char scriptSQL[500];
	
	sprintf(scriptSQL, "SELECT* FROM %s WHERE %s = %s;", tabela, field.Nome, field.Valor); 
	
	 if (mysql_query(mySqlInstance, scriptSQL) == 0) {
       result = mysql_store_result(mySqlInstance);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) 
               return row;
        } else {
            fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mySqlInstance));
        }
    } else {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(mySqlInstance));
    }
	
}

clearResult() {
	mysql_free_result(result);
}



#endif

