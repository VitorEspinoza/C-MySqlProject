#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "databaseController.h"				

int createClient(Cliente client) {

	char estadoCivilConvertido[2];
    itoa(client.estadoCivil, estadoCivilConvertido, 2);

	Propriedade rgProp;
    rgProp = setPropriedade("rg", "string", client.rg);
 
 	Propriedade cpfProp;
    cpfProp = setPropriedade("cpf", "string", client.cpf);

    Propriedade nomeProp;
    nomeProp = setPropriedade("nome", "string", client.nome);

    Propriedade enderecoProp;
    enderecoProp = setPropriedade("endereco", "string", client.endereco);

    Propriedade telefoneProp;
    telefoneProp = setPropriedade("telefone", "string", client.telefone);

    Propriedade estadoCivilProp;
	estadoCivilProp =  setPropriedade("estadoCivil", "int", estadoCivilConvertido);
  
	int success = create("Cliente", 6, cpfProp, rgProp, nomeProp, enderecoProp, telefoneProp, estadoCivilProp);

	return success;
	

}

const void read() {
    char scriptSQL[500];
    strcpy(scriptSQL, "SELECT * FROM Cliente");

    if (mysql_query(mySqlInstance, scriptSQL) == 0) {
        MYSQL_RES *result = mysql_store_result(mySqlInstance);
        if (result) {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                // Imprima os valores da linha
                printf("%s\t%s\t%s\n", row[0], row[1], row[2]); // Exemplo: três colunas
            }
            mysql_free_result(result);
        } else {
            fprintf(stderr, "Erro ao obter resultados: %s\n", mysql_error(mySqlInstance));
        }
    } else {
        fprintf(stderr, "Erro na consulta: %s\n", mysql_error(mySqlInstance));
    }
}

