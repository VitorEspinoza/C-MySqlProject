#include <stdio.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <stdlib.h>

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

// Resto do seu código aqui
char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "csharppass31";
MYSQL* mySqlInstance;


int initMySqlConnection() {
		
	bool ProgramIsOpened = 1;
	int answer;
	
	char* consult;
	char* sentence;
	char sentence_aux[200];
	
	if(!(mySqlInstance = mysql_init(0)))
	{
        printf("ERROR: Não foi possível criar o objeto MySQL.\n");
    	return 0;
	}

	if(!mysql_real_connect(mySqlInstance, HOST, USER, PASS, "bankfinaltrab", 3306, NULL, 0))
	{
		printf("ERROR: Alguma informação do banco de dados está incorreta ou não existe.\n");
        return 0;
	}
		 
	return 1;
		

}




#endif // DATABASECONNECTION_H


