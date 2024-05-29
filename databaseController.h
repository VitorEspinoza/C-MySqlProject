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

bool propertieIsNumber(Propriedade prop) {
	bool isNumber = strcmp(prop.Tipo, "int") == 0 || strcmp(prop.Tipo, "double") == 0;
	return isNumber;
}


char* returnAttribution(Propriedade prop) {
    if (propertieIsNumber(prop)) {
        return "%s = %s";
    } 
    
        return "%s = '%s'";
    
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
    	
    	
	char format[20];
    if (propertieIsNumber(propriedadesArray[i])) {
       	strcpy(format, "%s");
    } 
    else {
    	strcpy(format, "'%s'");
	}
	
       sprintf(scriptSQL + strlen(scriptSQL), format, propriedadesArray[i].Valor);
		const isLastItem = i == numPropriedades - 1;
        if (!isLastItem) {
            sprintf(scriptSQL + strlen(scriptSQL), ", ");
        }
    }


    sprintf(scriptSQL + strlen(scriptSQL), ");\n");

    va_end(args);
  	
  	int success = 0;
    if (mysql_ping(mySqlInstance)) {
        printf("ERROR: Imposs�vel conectar.\n");
        printf("%s\n", mysql_error(mySqlInstance));
    }

    if (mysql_query(mySqlInstance, scriptSQL)) {
        printf("ERROR: %s\n", mysql_error(mySqlInstance));
        rewind(stdin);
        getchar();
    } else {
        printf("Informa��es adicionadas corretamente.\n");
        success = 1;
    }

		                                                                         
    return success;
}

typedef void (*filler_func)(void*, MYSQL_ROW);

void** readAll(char tableName[50], filler_func fill, size_t structSize, char* whereClause) {
    char scriptSQL[500];
    
    if (whereClause[0] == '\0') {
     	sprintf(scriptSQL, "SELECT * FROM %s;", tableName);
	} else {
     	sprintf(scriptSQL, "SELECT * FROM %s %s;", tableName, whereClause);
	}

    void** array = NULL;
    int count = 0;

    if (mySqlInstance == NULL) {
        printf("ERROR: mySqlInstance � NULL\n");
        return NULL;
    }

    if (mysql_ping(mySqlInstance)) {
        printf("ERROR: Imposs�vel conectar.\n");
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
	
	
	sprintf(scriptSQL, "SELECT * FROM %s", tabela);
	
 	char* format = returnAttribution(field);
	char whereClause[50];
	sprintf(whereClause, " WHERE %s", format);
    sprintf(scriptSQL + strlen(scriptSQL), whereClause, field.Nome, field.Valor);
    
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


int update(char tabela[50], Propriedade identifierField, int numPropriedades, ...) {

	char scriptSQL[500]; 
    sprintf(scriptSQL, "UPDATE %s SET ", tabela);
    va_list args;
    va_start(args, numPropriedades);
   
	Propriedade propriedadesArray[numPropriedades];
    int i;
    for (i = 0; i < numPropriedades; ++i) {
   
        propriedadesArray[i] = va_arg(args, Propriedade);
         
	    char* format = returnAttribution(identifierField);
		sprintf(scriptSQL + strlen(scriptSQL), format, propriedadesArray[i].Nome, propriedadesArray[i].Valor);
		
	
        if (i < numPropriedades - 1) {
            sprintf(scriptSQL + strlen(scriptSQL), ", ");
        }
    }
    
    char* format = returnAttribution(identifierField);
	char whereClause[50];
	sprintf(whereClause, " WHERE %s", format);
    sprintf(scriptSQL + strlen(scriptSQL), whereClause, identifierField.Nome, identifierField.Valor);

	int success = 0;
	printf("%s", scriptSQL);
    if (mysql_ping(mySqlInstance)) {
        printf("ERROR: Imposs�vel conectar.\n");
        printf("%s\n", mysql_error(mySqlInstance));
    }

    if (mysql_query(mySqlInstance, scriptSQL)) {
        printf("ERROR: %s\n", mysql_error(mySqlInstance));
        rewind(stdin);
        getchar();
    } else {
        printf("Informa��es atualizadas corretamente.\n");
        success = 1;
    }
    
    return success;
}

int deleteRegister(char tabela[50], Propriedade identifierField) {
	char scriptSQL[500];
		
	char* format = returnAttribution(identifierField);
	char whereClause[50];
	sprintf(whereClause, format, identifierField.Nome, identifierField.Valor);

	sprintf(scriptSQL, "DELETE FROM %s WHERE %s;", tabela, whereClause);
	int success = 0;
    if (mysql_ping(mySqlInstance)) {
        printf("ERROR: Imposs�vel conectar.\n");
        printf("%s\n", mysql_error(mySqlInstance));
    }

    if (mysql_query(mySqlInstance, scriptSQL)) {
        printf("ERROR: %s\n", mysql_error(mySqlInstance));
        rewind(stdin);
        getchar();
    } else {
        printf("\nInforma��es excluidas corretamente.\n");
        success = 1;
    }

    
    return success;
}
#endif

