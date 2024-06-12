#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "databaseController.h"

void fillCliente(void* structToFill, MYSQL_ROW row);
EstadoCivil stringToEstadoCivil(char* str);


Propriedade* setPropriedadesCliente(Cliente client) {
    char estadoCivilConvertido[10];
    strcpy(estadoCivilConvertido, EstadoCivilToString(client.estadoCivil));

    static Propriedade propriedades[7];

    propriedades[0] = setPropriedade("rg", "string", client.rg);
    propriedades[1] = setPropriedade("cpf", "string", client.cpf);
    propriedades[2] = setPropriedade("nome", "string", client.nome);
    propriedades[3] = setPropriedade("endereco", "string", client.endereco);
    propriedades[4] = setPropriedade("telefone", "string", client.telefone);
    propriedades[5] = setPropriedade("estadoCivil", "string", estadoCivilConvertido);

    return propriedades;
}

int createClient(Cliente client) {
	
   	Propriedade* propriedades = setPropriedadesCliente(client);
  
	int success = create("Cliente", 6, propriedades[0], propriedades[1], propriedades[2], propriedades[3], propriedades[4], propriedades[5]);

	return success;
}


Cliente** readAllClients() {
	int numberOfRowsCliente;
	Cliente** clientes = (Cliente**)readAll("Cliente", fillCliente, sizeof(Cliente), "", &(numberOfRowsCliente));
	return clientes;
}


void fillCliente(void* structToFill, MYSQL_ROW row) {
    if (structToFill == NULL || row == NULL) {
        printf("Erro: structToFill ou row � NULL\n");
        return;
    }

    Cliente* cliente = (Cliente*)structToFill;
    if (row[0] != NULL) cliente->id = atoi(row[0]);
    if (row[1] != NULL) strcpy(cliente->cpf, row[1]);
    if (row[2] != NULL) strcpy(cliente->rg, row[2]);
    if (row[3] != NULL) strcpy(cliente->nome, row[3]);
    if (row[4] != NULL) strcpy(cliente->endereco, row[4]);
    if (row[5] != NULL) strcpy(cliente->telefone, row[5]);
    if (row[6] != NULL) cliente->estadoCivil = stringToEstadoCivil(row[6]);
}


Cliente readClientByField(Propriedade propriedade) {
	MYSQL_ROW row = readByField("cliente", propriedade);
	

	Cliente cliente;
	
	if(row == NULL) {
		strcpy(cliente.rg, "NULL");
		clearResult();
		return cliente;
	}
	
	cliente.id = atoi(row[0]);
	strcpy(cliente.cpf, row[1]); 
	strcpy(cliente.rg, row[2]); 
	strcpy(cliente.nome, row[3]); 
	strcpy(cliente.endereco, row[4]); 
	strcpy(cliente.telefone, row[5]); 
	cliente.estadoCivil = stringToEstadoCivil(row[6]);
	clearResult();
	return cliente;
}

int updateClient(Cliente client, Propriedade identifierField) {
	
	char estadoCivilConvertido[10];
	strcpy(estadoCivilConvertido, EstadoCivilToString(client.estadoCivil));
    

  	Propriedade* propriedades = setPropriedadesCliente(client);
  
	int success = update("Cliente", identifierField, 6, propriedades[0], propriedades[1], propriedades[2], propriedades[3], propriedades[4], propriedades[5]);
	return success;
}


int deleteClient(Propriedade identifierField) {
	int success = deleteRegister("cliente", identifierField);
	return success;
}



