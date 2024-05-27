#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "databaseController.h"

void fillCliente(void* structToFill, MYSQL_ROW row);
EstadoCivil stringToEstadoCivil(char* str);

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


Cliente** readAllClients() {

	Cliente** clientes = (Cliente**)readAll("Cliente", fillCliente, sizeof(Cliente));
	return clientes;
}


void fillCliente(void* structToFill, MYSQL_ROW row) {
    if (structToFill == NULL || row == NULL) {
        printf("Erro: structToFill ou row é NULL\n");
        return;
    }

    Cliente* cliente = (Cliente*)structToFill;
    if (row[0] != NULL) strcpy(cliente->cpf, row[0]);
    if (row[1] != NULL) strcpy(cliente->rg, row[1]);
    if (row[2] != NULL) strcpy(cliente->nome, row[2]);
    if (row[3] != NULL) strcpy(cliente->endereco, row[3]);
    if (row[4] != NULL) strcpy(cliente->telefone, row[4]);
    if (row[5] != NULL) cliente->estadoCivil = stringToEstadoCivil(row[5]);
}

EstadoCivil stringToEstadoCivil(char* str) {
    if (str == NULL) {
        printf("Erro: str é NULL\n");
        return Solteiro; 
    }

    if (strcmp(str, "SOLTEIRO") == 0) {
        return Solteiro;
    } else if (strcmp(str, "CASADO") == 0) {
        return Casado;
    }
}

Cliente readClientByField(Propriedade propriedade) {
	MYSQL_ROW row = readByField("cliente", propriedade);
	
	Cliente cliente;
	
	strcpy(cliente.cpf, row[0]); 
	strcpy(cliente.rg, row[1]); 
	strcpy(cliente.nome, row[2]); 
	strcpy(cliente.endereco, row[3]); 
	strcpy(cliente.telefone, row[4]); 
	cliente.estadoCivil = stringToEstadoCivil(row[5]);
	clearResult();
	return cliente;
}

int updateClient(Cliente client, Propriedade identifierField) {
	
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
  
	int success = update("Cliente", identifierField, 6, cpfProp, rgProp, nomeProp, enderecoProp, telefoneProp, estadoCivilProp);
	return success;
}


int deleteClient(Propriedade identifierField) {
	int success = deleteRegister("cliente", identifierField);
	return success;
}



