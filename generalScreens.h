void initialScreen();
void initialScreen() {
	system("cls");
	setDefaultColorTextConsole();
	printf("====================================\n");
    printf("=           Tela Inicial           =\n");
    printf("====================================\n");
	char response;
	
	printf("Voc� j� � cliente? (S/N): ");
	
	do {
    scanf(" %c", &response);
		  if (response == 'S' || response == 's') {
		  	clientInfoScreen(0);
	    } else if (response == 'N' || response == 'n') {
	       createClientScreen();
	    } else {
	        printf("Op��o inv�lida. Responda com S ou N.\n");
	    }
	}	while(response != 'S' || response != 's' || response != 'N' || response != 'n');
}
