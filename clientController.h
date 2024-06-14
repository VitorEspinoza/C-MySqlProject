#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "databaseController.h"


typedef struct {
	int numberOfRows;
	Client** clients;
}ResponseReadAllClients;

void fillClient(void* structToFill, MYSQL_ROW row);
MaritalStatus stringToMaritalStatus(char* str);
void freeClients(ResponseReadAllClients* response);

Property* setPropertiesClient(Client client) {
    char convertedMaritalStatus[10];
    strcpy(convertedMaritalStatus, MaritalStatusToString(client.maritalStatus));

    static Property properties[6];

    properties[0] = setProperty("rg", "string", client.rg);
    properties[1] = setProperty("cpf", "string", client.cpf);
    properties[2] = setProperty("name", "string", client.name);
    properties[3] = setProperty("address", "string", client.address);
    properties[4] = setProperty("phone", "string", client.phone);
    properties[5] = setProperty("maritalStatus", "string", convertedMaritalStatus);
   
    return properties;
}

int createClient(Client client) {
	
   	Property* properties = setPropertiesClient(client);
  
	int success = create("Client", 6, properties[0], properties[1], properties[2], properties[3], properties[4], properties[5]);

	return success;
}


Client** readAllClients() {
	int numberOfRowsClient;
	Client** clients = (Client**)readAll("Client", fillClient, sizeof(Client), "", &(numberOfRowsClient));
	return clients;
}


void fillClient(void* structToFill, MYSQL_ROW row) {
    if (structToFill == NULL || row == NULL) {
        return;
    }

    Client* client = (Client*)structToFill;
    if (row[0] != NULL) client->id = atoi(row[0]);
    if (row[1] != NULL) strcpy(client->cpf, row[1]);
    if (row[2] != NULL) strcpy(client->rg, row[2]);
    if (row[3] != NULL) strcpy(client->name, row[3]);
    if (row[4] != NULL) strcpy(client->address, row[4]);
    if (row[5] != NULL) strcpy(client->phone, row[5]);
    if (row[6] != NULL) client->maritalStatus = stringToMaritalStatus(row[6]);
    if (row[7] != NULL) client->active = atoi(row[7]);
}


Client readClientByField(Property property) {
	MYSQL_ROW row = readByField("client", property);
	

	Client client;
	
	if(row == NULL) {
		strcpy(client.rg, "NULL");
		clearResult();
		return client;
	}
	
	client.id = atoi(row[0]);
	strcpy(client.cpf, row[1]); 
	strcpy(client.rg, row[2]); 
	strcpy(client.name, row[3]); 
	strcpy(client.address, row[4]); 
	strcpy(client.phone, row[5]); 
	client.maritalStatus = stringToMaritalStatus(row[6]);
	client.active = atoi(row[6]);
	clearResult();
	return client;
}

int updateClient(Client client, Property identifierField) {
	
	char convertedMaritalStatus[10];
	strcpy(convertedMaritalStatus, MaritalStatusToString(client.maritalStatus));
    

  	Property* properties = setPropertiesClient(client);
  
	int success = update("Client", identifierField, 6, properties[0], properties[1], properties[2], properties[3], properties[4], properties[5]);
	return success;
}


int deleteClient(Property identifierField) {
	Property activeClientProp = setProperty("active", "int", "0");
	int success = update("client", identifierField, 1, activeClientProp);
	return success;
}

Client* clientAlreadyExists(Property identifierField) {
	char whereClause[70];
	
	ResponseReadAllClients response;
	
	sprintf(whereClause, "WHERE %s = %s", identifierField.Name, identifierField.Value);
	
	response.clients = (Client**)readAll("client", fillClient, sizeof(Client), whereClause, &(response.numberOfRows));
	
	Client* client = NULL;
	
	int i;
	for (i=0; response.clients[i] != NULL; i++) {
	    if(response.clients[i]->active == 1) {
	        client = malloc(sizeof(Client));
	        *client = *response.clients[i];
	        break;  
	    }
	}
		
	freeClients(&response);	
	return client;
}

void freeClients(ResponseReadAllClients* response) {
	int i = 0;
    for (i; i < response->numberOfRows; i++) {
        free(response->clients[i]);
    }
    free(response->clients);
}




