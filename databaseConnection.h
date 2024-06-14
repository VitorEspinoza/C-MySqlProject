#include <stdio.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <stdlib.h>

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "";
MYSQL* mySqlInstance;


int initMySqlConnection() {

    bool ProgramIsOpened = 1;
    int answer;

    char* consult;
    char* sentence;
    char sentence_aux[200];

    if(!(mySqlInstance = mysql_init(0)))
    {
        printf("ERROR: N�o foi poss�vel criar o objeto MySQL.\n");
        return 0;
    }

    if(!mysql_real_connect(mySqlInstance, HOST, USER, PASS, "bank", 3306, NULL, 0))
    {
        printf("ERROR: Alguma informa��o do banco de dados est� incorreta ou n�o existe.\n");
        return 0;
    }

    return 1;


}

#endif


