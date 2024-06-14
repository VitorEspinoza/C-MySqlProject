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
    char Name[50];
    char Type[10];
    char Value[50]; 
} Property;

Property setProperty(char name[50], char type[10], char value[50]){
	Property P;
	strcpy(P.Name, name); 
	strcpy(P.Type, type);
	strcpy(P.Value, value); 

	return P;
}

bool propertieIsNumber(Property prop) {
	bool isNumber = strcmp(prop.Type, "int") == 0 || strcmp(prop.Type, "double") == 0;
	return isNumber;
}


char* returnAttribution(Property prop) {
    if (propertieIsNumber(prop)) {
        return "%s = %s";
    } 
    
        return "%s = '%s'";
    
}

int executeQuery(MYSQL* mySqlInstance, const char* scriptSQL) {
    if (mysql_ping(mySqlInstance)) {
        printf("%s\n", mysql_error(mySqlInstance));
        return 0;
    }

    if (mysql_query(mySqlInstance, scriptSQL)) {
        printf("ERROR: %s\n", mysql_error(mySqlInstance));
        rewind(stdin);
        getchar();
        return 0;
    }

    return 1;
}

MYSQL_RES *result;

const int create(char* tabela, int numProperties, ...) {
    char scriptSQL[500]; 
    sprintf(scriptSQL, "INSERT INTO %s (", tabela);
    va_list args;
    va_start(args, numProperties);
    
    Property propertiesArray[numProperties];
    int i;
    for (i = 0; i < numProperties; ++i) {
        propertiesArray[i] = va_arg(args, Property);
        sprintf(scriptSQL + strlen(scriptSQL), "%s", propertiesArray[i].Name);
        const isLastItem = i == numProperties - 1;
        if (!isLastItem) {
            sprintf(scriptSQL + strlen(scriptSQL), ", ");
        }
    }

    sprintf(scriptSQL + strlen(scriptSQL), ") VALUES (");

    for (i = 0; i < numProperties; ++i) {
        char format[20];
        if (propertieIsNumber(propertiesArray[i])) {
            strcpy(format, "%s");
        } 
        else {
            strcpy(format, "'%s'");
        }
        
        sprintf(scriptSQL + strlen(scriptSQL), format, propertiesArray[i].Value);
        const isLastItem = i == numProperties - 1;
        if (!isLastItem) {
            sprintf(scriptSQL + strlen(scriptSQL), ", ");
        }
    }


    sprintf(scriptSQL + strlen(scriptSQL), ");\n");
    va_end(args);

    return executeQuery(mySqlInstance, scriptSQL);                  

}

typedef void (*filler_func)(void*, MYSQL_ROW);

void** readAll(char* tableName, filler_func fill, size_t structSize, char* whereClause, int* numberOfRows) {
    char scriptSQL[500];
    
    if (whereClause[0] == '\0') {
     	sprintf(scriptSQL, "SELECT * FROM %s;", tableName);
	} else {
     	sprintf(scriptSQL, "SELECT * FROM %s %s;", tableName, whereClause);
	}

    void** array = NULL;
    int count = 0;

    if (mySqlInstance == NULL) {
        return NULL;
    }

    if (mysql_ping(mySqlInstance)) {
        printf("%s\n", mysql_error(mySqlInstance));
        return NULL;
    }

    if (mysql_query(mySqlInstance, scriptSQL) == 0) {
        result = mysql_store_result(mySqlInstance);

        if (result) {
            MYSQL_ROW row;

            while ((row = mysql_fetch_row(result))) {
                array = realloc(array, (count + 1) * sizeof(void*));
                array[count] = malloc(structSize);
                fill(array[count], row);
                count++;
            }
            array = realloc(array, (count + 1) * sizeof(void*));
			array[count] = NULL;
            *numberOfRows = count;
            clearResult();
        } else {
            printf("Erro ao obter resultados: %s\n", mysql_error(mySqlInstance));
        }
    } else {
        printf("Erro na consulta: %s\n", mysql_error(mySqlInstance));
    }

    return array;
}

MYSQL_ROW readByField(char* tabela, Property identifierField)
{
	char scriptSQL[500];
	
	
	sprintf(scriptSQL, "SELECT * FROM %s", tabela);
	
 	char* format = returnAttribution(identifierField);
	char whereClause[50];
	sprintf(whereClause, " WHERE %s", format);
    sprintf(scriptSQL + strlen(scriptSQL), whereClause, identifierField.Name, identifierField.Value);
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


int update(char* tabela, Property identifierField, int numProperties, ...) {

	char scriptSQL[500]; 
    sprintf(scriptSQL, "UPDATE %s SET ", tabela);
    va_list args;
    va_start(args, numProperties);
   
	Property propertiesArray[numProperties];
    int i;
    for (i = 0; i < numProperties; ++i) {
   
        propertiesArray[i] = va_arg(args, Property);
         
	    char* format = returnAttribution(identifierField);
		sprintf(scriptSQL + strlen(scriptSQL), format, propertiesArray[i].Name, propertiesArray[i].Value);
		
	
        if (i < numProperties - 1) {
            sprintf(scriptSQL + strlen(scriptSQL), ", ");
        }
    }
    
    char* format = returnAttribution(identifierField);
	char whereClause[50];
	sprintf(whereClause, " WHERE %s", format);
    sprintf(scriptSQL + strlen(scriptSQL), whereClause, identifierField.Name, identifierField.Value);
	
	 return executeQuery(mySqlInstance, scriptSQL);    
}

int deleteRegister(char* tabela, Property identifierField) {
	char scriptSQL[500];
		
	char* format = returnAttribution(identifierField);
	char whereClause[50];
	sprintf(whereClause, format, identifierField.Name, identifierField.Value);

	sprintf(scriptSQL, "DELETE FROM %s WHERE %s;", tabela, whereClause);
	int success = 1;

    return executeQuery(mySqlInstance, scriptSQL);    
}
#endif

