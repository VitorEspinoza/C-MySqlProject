void telaInicial();
void telaInicial() {
	setDefaultColorTextConsole();
	printf("====================================\n");
    printf("=           Tela Inicial           =\n");
    printf("====================================\n");
	char resposta;
	
	printf("Voc� j� tem uma conta? (S/N): ");
	
	do {
    scanf(" %c", &resposta);
		  if (resposta == 'S' || resposta == 's') {
		  	clientInfoScreen(0);
	    } else if (resposta == 'N' || resposta == 'n') {
	       createClientScreen();
	    } else {
	        printf("Op��o inv�lida. Responda com S ou N.\n");
	    }
	}	while(resposta != 'S' || resposta != 's' || resposta != 'N' || resposta != 'n');
}
