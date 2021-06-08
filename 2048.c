#include "griglia.h"
#include "classifica.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>


#define BOLD_WHITE "\033[1m"
#define STANDARD_WHITE "\033[0m"
#define BOLD_RED "\033[1;31m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_PURPLE "\033[1;35m"
#define BOLD_MAGENTA "\033[1:30m"
#define BOLD_CYAN "\033[1;36m"
#define BACKGROUND_BLUE "\e[44m"
#define BACKGROUND_GREEN "\e[42m"
#define RESET "\e[0m"






//stampa del titolo
void titolo(){
   	printf(BOLD_YELLOW);
        printf(" _____________________________\n");
        printf("|   ____   ___  _ _    ___    |\n");
        printf("|  |___ \\ / _ \\| | |  ( _ )   |\n");
        printf("|    __) | | | | | |_ / _ \\   |");
        printf("\n");
        printf("|   / __/| |_| |__  _| (_) |  |\n");
        printf("|  |_____|\\___/  |_|  \\___/   |\n");
        printf("|_____________________________|\n");
	printf("\n");
        printf("\n");
	printf(RESET);
	
}






















//stampa i comandi
void comandi(griglia my_griglia,int n,classifica new_classifica){
		while(1){
			//se non ci sono più mosse disponibili finisce la partita altrimenti stampa i comandi
			if(!controlla_mosse(my_griglia,n)){
				//chiama la funzione di fine partita
				game_over(my_griglia,my_griglia->player,my_griglia->parz, new_classifica);
				//esce dal ciclo
				break;
				//esce dalla funzione
				return;
			}
			//altrimenti stampa i comandi	
			else{
				//utilizzo una stringa in modo da poter gestire tramite la fgets un input vuoto
				char scelta[2];
				printf("\n");
				printf("Comandi\n");
				printf(BOLD_RED);
		       	printf("(0) menu principale\n");
		       	printf(BOLD_BLUE);
		       	printf("(w) muovi su\n");
		       	printf(BOLD_GREEN);
		       	printf("(s) muovi giù\n");
		       	printf(BOLD_PURPLE);
		       	printf("(d) muovi a destra\n");
		       	printf(RESET);
		       	printf(BOLD_WHITE);
		       	printf("(a) muovi a sinistra\n");
		       	fgets(scelta, 2, stdin);
		       	switch(scelta[0]) {
				       	case '0': salva(my_griglia->player,my_griglia->parz,new_classifica,my_griglia);break;
				       	case 'w': muovi_sopra(my_griglia,n,new_classifica); break;
				       	case 's': muovi_sotto(my_griglia,n,new_classifica); break;
				       	case 'd': muovi_destra_griglia(my_griglia,n,new_classifica); break;
				    		case 'a': muovi_sinistra_griglia(my_griglia,n,new_classifica); break;
				    		default:/*comando non riconosciuto */ system("clear"); titolo(); stampa_griglia(my_griglia,n,my_griglia->parz);
		       	}
		       	
				//se l'utente ha inserito 0 la funzione torna indietro
				if(scelta[0]=='0'){
					//esce dal ciclo
					break;
					//esce dalla funzione
					return;
				}
			}
       	}
}
















//crea la griglia
void inizia_gioco(int n,giocatore player, classifica new_classifica){
		system("clear");
		titolo();
		printf(RESET);
		printf(BOLD_WHITE);
		//crea la griglia
		griglia my_griglia=crea_griglia();
		//popola la griglia
        	popola_griglia(my_griglia,n,player);
        	//stampa la griglia
        	stampa_griglia(my_griglia,n,my_griglia->parz);
        	//chiama la funzione per stampare i comandi
        	comandi(my_griglia,n, new_classifica);
        	
}





















//scelta della dimensione
void dimensione(giocatore player, classifica new_classifica){
	int n=0;
	system("clear");
	titolo();
	printf(BOLD_RED);
	printf("Scrivere 0 per tornare indietro\n");
	printf("\n");
	printf(RESET);
	printf(BOLD_WHITE);
	printf("Inserire il numero corrispondente alle righe e colonne: ");
	scanf("%d",&n);
	if(n==0){
		return;
	}
	else{
		inizia_gioco(n,player,new_classifica);
	}
	

}



















//schermata di login
void login_screen(classifica new_classifica){
	titolo();
	char nickname[10];
	char password[10];
	printf(RESET);
	printf(BOLD_WHITE);
	printf("            ");
	printf("LOGIN");
	printf(BOLD_RED);
	printf("\n");
	printf("\n");
	printf("Scrivere 0 per tornare indietro\n");
	printf("\n");
	printf(RESET);
	printf("    ");
	printf(BACKGROUND_BLUE);
	printf("Inserire nome utente:\n");
	printf(RESET);
	printf("    ");
	printf(BOLD_BLUE);
	scanf("%s",nickname);
	//se inserisce 0 torna indietro
	if(strcmp(nickname,"0")==0){
		return;
	}
	//altrimenti fa inserire la password
	else{
		printf(RESET);
		printf("\n");
		printf("    ");
		printf(BACKGROUND_GREEN);
		printf("Inserire la password:\n");
		printf(RESET);
		printf("    ");
		printf(BOLD_GREEN);
		scanf("%s",password);
		printf(RESET);
		printf("\n");
		//verifica se l'utente esiste. Se non esiste torna indietro
		if(login(new_classifica,nickname,password)!=NULL)
			dimensione(login(new_classifica,nickname,password),new_classifica);
		else{
			return;
		}
	}
}








//schermata di registrazione
void registrazione(classifica new_classifica){
	titolo();
	char nickname[10];
	char password[10];
	printf(RESET);
	printf(BOLD_WHITE);
	printf("         ");
	printf("REGISTRAZIONE");
	printf(BOLD_RED);
	printf("\n");
	printf("\n");
	printf("Scrivere 0 per tornare indietro\n");
	printf("\n");
	printf(RESET);
	printf("    ");
	printf(BACKGROUND_BLUE);
	printf("Inserire nome utente:\n");
	printf(RESET);
	printf("    ");
	printf(BOLD_BLUE);
	scanf("%s",nickname);
	if(strcmp(nickname,"0")==0){
		return;
	}else{
		printf(RESET);
		printf("\n");
		printf("    ");
		printf(BACKGROUND_GREEN);
		printf("Inserire la password:\n");
		printf(RESET);
		printf("    ");
		printf(BOLD_GREEN);
		scanf("%s",password);
		printf(RESET);
		printf("\n");
		/*se il nickname non è gia in uso, registra il nuovo giocatore.
		Altrimenti torna indietro*/
		if(!esiste_nickname(new_classifica,nickname)){
			//inserisce il nuovo giocatore
			giocatore new_giocatore=inserisci_giocatore(new_classifica,nickname,password,0);
			//salva la classifica su file
			salva_classifica(new_classifica);	
			dimensione(new_giocatore,new_classifica);
		}
		else{
			return;
		
		}
		
	}

}








//mostra la classifica
void mostra_classifica(classifica new_classifica){
 	system("clear");
        titolo();
	printf(RESET);
	printf(BOLD_WHITE);
	printf("         ");
	printf("CLASSIFICA\n");
	printf("\n");
	stampa_classifica(new_classifica);
	printf(BOLD_RED);
	printf("Inserire un carattere per tornare indietro: ");
	char c;
	//pulisco il buffer
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
	scanf("%c",&c);
	
	
	
}















//stampa il menu principale
void menu_principale(){
	while(1){  
		titolo();
		//carica la classifica
		classifica new_classifica=carica_classifica();
		//utilizzo una stringa in modo da poter gestire tramite la fgets un input vuoto
		char scelta[2];
		printf(BOLD_BLUE);
		printf("        (1) Login\n");
		printf(BOLD_GREEN);
		printf("        (2) Registrati\n");
		printf(BOLD_PURPLE);
		printf("        (3) Classifica\n");
		printf(BOLD_RED);
		printf("        (0) Esci\n");
		printf(STANDARD_WHITE);
		fgets(scelta, 2, stdin);
		switch(scelta[0]) {
		        case '0': cancella_classifica(new_classifica); exit(0); 
		        case '1': system("clear"); login_screen(new_classifica);break;
		        case '2': system("clear"); registrazione(new_classifica);break;
		        case '3': mostra_classifica(new_classifica); break;
		        default:/*comando non riconosciuto */ system("clear");
		}
		/*libera lo spazio allocato per la classifica */
		cancella_classifica(new_classifica);
	}

}







int main(){
	system("clear");	
	menu_principale();
	
}
