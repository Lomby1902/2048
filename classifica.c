#include "classifica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>














//inserisce ordinatamente un nuovo giocatore. restituisce il puntatore al nuovo giocatore
giocatore inserisci_giocatore(classifica my_classifica,char* nickname,char* password,int punteggio){
	 //due puntatori di appoggio che faccio puntare inizialmente alla testa
	giocatore r = my_classifica->head; 
    	giocatore q = my_classifica->head;
	//creo un nuovo giocatore
	giocatore new_giocatore=(giocatore)malloc(sizeof(struct giocatore));
	//in caso di errore
	if(new_giocatore==NULL)
		return NULL;
	//inizializzo il giocatore con i parametri inseriti
	strcpy(new_giocatore->nickname, nickname);
	strcpy(new_giocatore->password, password);
	new_giocatore->punteggio=punteggio;


	if (my_classifica->head==NULL){ /*la lista è vuota*/
		new_giocatore->next=NULL;
		my_classifica->head=new_giocatore;
		//restituisce il puntatore al nuovo giocatore inserito
		return new_giocatore;
	}
	/* trova il punto di inserimento */
	while ((q != NULL) && (q->punteggio > new_giocatore->punteggio)){
		//r raggiunge q
        	r = q;
        	//q va avanti di uno
        	q = q->next;
        }
	if(q == my_classifica->head){ /*inserimento in testa*/
		new_giocatore->next=my_classifica->head;
		my_classifica->head=new_giocatore;
	}
	else{ /*caso generico*/
		r->next=new_giocatore;
		new_giocatore->next=q;
	}
	
	//se tutto è andato a buon fine restituisce il puntatore al giocatore appena inserito
	return new_giocatore;
	


}
















//carica la classifica da file
classifica carica_classifica(){
	//crea una classifica
	classifica new_classifica=(classifica)malloc(sizeof(struct classifica));
	//verifica se ci sono errori
	if(new_classifica==NULL)
		return NULL;
	
	//inizializza la testa della classifica a NULL
	new_classifica->head=NULL;
	//apre il file in lettura
	FILE* f = fopen("classifica.txt", "r");
	//verifica se ci sono errori
	if (f==NULL) {
		perror("Errore nell'apertura del file classifica");
		exit(1);
	}
	//variabili per salvare l'input letto
	char nickname[10];
	char password[10];
	int punteggio;
	//ciclo di lettura file
	while(fscanf(f,"%s%s%d\n",nickname,password,&punteggio ) != EOF)
		//se non ci sono errori inserisce ordinatamente i vari giocatori letti nella classifica creata
		if(inserisci_giocatore(new_classifica,nickname,password,punteggio)==NULL){
			perror("Errore nella lettura della classifica");
			exit(1);
		}
	//chiude la lettura
	fclose(f);
	//restituisce la classifica
	return new_classifica;
}






























/*verifica i dati immessi dall'utente ed in caso positivo resitusice 
il puntatore al giocatore che esegue il login*/
giocatore login(classifica my_classifica, char* nickname,char* password){
	//puntatore d'appoggio
	giocatore p;
	//parte dalla testa della classifica
	p=my_classifica->head;
	//esegue una ricerca esaustiva
	while(p!=NULL){
		//se trovo l'utente ne restituisco il puntatore
		if(strcmp(p->nickname,nickname)==0 && strcmp(p->password,password)==0)
			return p;
		//vado avanti con la ricerca
		p=p->next;
	}

	//se alla fine non trovo nulla restituisco NULL
	return NULL;

}











//verifica se il nickname inserito è già in uso. Restituisce 1 se lo è.
int esiste_nickname(classifica my_classifica,char* nickname){
	//puntatore d'appoggio
	struct giocatore* p;
	//se la classifica è vuota ritorna 0
	if(my_classifica->head==NULL)
		return 0;
	//parte dalla testa della classifica
	p=my_classifica->head;
	//esegue una ricerca esaustiva
	while(p!=NULL){
		//se trova il nickname restituisce 1
		if(strcmp(p->nickname,nickname)==0){
			return 1;
		}
		//vado avanti con la ricerca
		p=p->next;
	}

	//se alla fine non lo trova restituisce 0
	return 0;

}
















//elimina un giocatore. Ritorna 0 in caso positivo
int elimina_giocatore(classifica my_classifica,char* nickname){
	//puntatori che servono a ricollegare i nodi dopo l'eliminazione
 	giocatore r =my_classifica->head; 
    	giocatore q =my_classifica->head; 
   	while ((q != NULL) && strcmp(q->nickname, nickname)!=0){
        	r = q;
        	q = q->next;
    	}
    	//se la lista è vuota
    	if (q == NULL)  
      		return 1;
     	//se devo cancellare in testa
    	if (q==my_classifica->head)
        	my_classifica->head = my_classifica->head->next;
        //caso generale
    	else
        	r->next = q->next;
    	free(q);
    	return 0;

}









//aggiorna il punteggio di un giocatore. Restituisce 1 in caso positivo
//Questa funzione prima cancella il giocatore e poi lo reinserisce ordinatamente
//La funzione aggiornerà il punteggio solo se quello nuovo è migliore del precedente
int aggiorna_punteggio(classifica my_classifica, giocatore player,int punteggio){
	//verifica se il precedente punteggio è migliore
	if(player->punteggio>=punteggio){
		return 1;
	}
	//aggiorna il punteggio
	else{
		//salva i dati del giocatore da dover reinserire
		char nickname[10];
		strcpy(nickname, player->nickname);
		char password[10];
		strcpy(password, player->password);
		//cancella il giocatore
    		int result =elimina_giocatore(my_classifica,player->nickname);
    		//se non è stato cancellato
    		if(result == 1) return 0;
  		//reinserisce il giocatore
   		giocatore result2 = inserisci_giocatore(my_classifica, nickname, password,punteggio);
		//se non è stato inserito
    		if(result2 == NULL) return 0;
    
    		return 1;
	}


}











//libera lo spazio della classifica
void cancella_classifica(classifica my_classifica){

	//puntatori di appoggio
	giocatore p=my_classifica->head;
	giocatore q=my_classifica->head;
	//scorro fino alla fine 
    	while (q != NULL){
    		//p raggiunge q
    		p=q;
    		//q va avanti
        	q = q->next;
        	//cancello p
        	free(p);
    	}
	//cancello q
	free(q);

	free(my_classifica);
}








//salva la classifica su file
void salva_classifica(classifica my_classifica){
	//apre il file in scrittura
	FILE* f = fopen("classifica.txt", "w");
	//verifica se ci sono errori
	if (f==NULL) {
		perror("Errore nella scrittura su file classifica");
		exit(1);
	}
	//puntatore di appoggio
	giocatore p=my_classifica->head;
	//ciclo che stampa ogni utente nel file
	while(p!=NULL){
		fprintf(f,"%s ",p->nickname);
		fprintf(f,"%s ",p->password);
		fprintf(f,"%d ",p->punteggio);
		fprintf(f,"\n");
		//vado al giocatore successivo
		p=p->next;
	}
	
	//chiude la scrittura
	fclose(f);
}












//stampa la classifica
void stampa_classifica(classifica my_classifica){
	
	//se la classifica è vuota
	if(my_classifica->head==NULL){
		printf("Classifica vuota\n");
		return;
	
	}
	//puntatore di appoggio
	giocatore p=my_classifica->head;
        //variabile per stampare la posizione in classifica
    	int i=1;
    	//scorro fino alla fine e stampo
    	while (p != NULL){
        	printf("    (%d) %s       %d\n",i,p->nickname,p->punteggio);
        	p = p->next;
        	i++;
    	}
    printf("\n");

}



