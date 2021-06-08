#include "griglia.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>




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
void titolo();
















//crea una griglia vuota
griglia crea_griglia(){
	griglia new_griglia=(griglia)malloc(sizeof(struct griglia));
	if(new_griglia==NULL) return NULL;
	new_griglia->head=NULL;
	new_griglia->tail=NULL;
	//inizializzo il punteggio parziale a 0
	new_griglia->parz=0;
	return new_griglia;
}






/*crea n linee, le popola con 0 e 2, poi aggiunge le linee
in testa alla griglia e associa il nickname alla griglia*/
int popola_griglia(griglia my_griglia,int n,giocatore player){
	//inserisce il giocatore
	my_griglia->player=player;
	//genera un numero random per stabilire dove inserire il 2 iniziale
	time_t t;
	srand((unsigned) time(&t));
	int r =rand() % (n*n);
	//contatore per l'elemento casuale
	int j=0;
	//crea n linee e nodi_griglia
	for(int i=0;i<n;i++){
		//chiamo la funzione crea_linea per creare la linea di dimesione 
		linea new_linea=crea_linea();
		//inserisce n-1 volte lo 0 in testa alle linee e una volta un 2
		for(int k=0;k<n;k++){
			//se l'elemento random è uguale al valore del contatore inserisco il 2, altrimenti 0
			if(j==r)
				//crea un nodo della linea con il 2 in data
				inserisci_cella(new_linea,2);
			else
				//crea un nodo della linea con lo 0 in data
				inserisci_cella(new_linea,0);
			j++;
		}
		//crea un nuovo nodo della griglia
     		struct nodo_griglia* p=(struct nodo_griglia*)malloc(sizeof(struct nodo_griglia));
		//inserisco la linea creata nel nuovo nodo
		p->linea=new_linea;
		//il nuovo nodo punta alla vecchia testa
		p->next=my_griglia->head;
		p->prec = NULL;
        	if (my_griglia->head==NULL) // se la lista è vuota
                	my_griglia->tail=p;
        	else
                	my_griglia->head->prec = p;
		//la testa della griglia punta al nuovo nodo 
		my_griglia->head=p;
		}
		return 0;
}







//controlla se la griglia è piena tramite linea_piena(). Restituisce 1 se è piena.
int griglia_piena(griglia my_griglia, int n){
	//variabile d'appoggio per il nodo
	struct nodo_griglia* my_nodo=my_griglia->head;
	//il ciclo scorre le linee
	while(my_nodo!=NULL){
		//se la linea non è piena ritorna 0
		if(!linea_piena(my_nodo->linea))
			return 0;
		//vado al nodo successivo
		my_nodo=my_nodo->next;
	}

	//se tutte le linee sono piene ritorna 1
	return 1;



}
















//inserisce tramite inserisci_random() un elemento tra 2 e 4 in una cella random vuota
void inserisci_random_griglia(griglia my_griglia,int n){

	//genera un numero casuale tra 0 e n-1 per scegliere la linea
	int r =rand() % n;
	//variabile d'appoggio per il nodo_griglia
	struct nodo_griglia* my_nodo=my_griglia->head;
	//contatore
	int k=0;
	//ciclo che scorre la griglia
	while(k<r){
		//vado al nodo successivo
		my_nodo=my_nodo->next;
		//incremento il contatore
		k++;
	}
	
	//se la linea non è piena inserisco l'elemento random
	if(!linea_piena(my_nodo->linea))
		inserisci_random(my_nodo->linea,n);

	/*visto che prima di chiamare questa funzione viene controllato se 
	la griglia non sia piena, allora nel caso in cui la linea fosse piena posso
	richiamare la funzione inserisci_random_griglia() ricorsivamente fino a quando non 
	trova una linea disponibile*/
	else
		inserisci_random_griglia(my_griglia,n);
}











//controlla se ci sono mosse disponibili in verticale. Ritorna 1 se ci sono, 0 in caso contrario
int controlla_colonne(griglia my_griglia){
	//nodo superiore
	struct nodo_griglia* sup=my_griglia->head;
	//nodo inferiore
	struct nodo_griglia* inf=sup->next;
	/*questo ciclo prende in esame due linee e controlla
		i nodi in posizioni uguali */
		while(inf!=NULL){
			//nodo linea superiore		
			struct nodo_linea* sup_int=sup->linea->head;
			//nodo linea inferiroe
			struct nodo_linea* inf_int=inf->linea->head;
			/* questo ciclo sposta i due nodi linea verso
			destra, in modo da controllare le due linee 
			per interi*/
			while(inf_int!=NULL){		
				/*se il nodo superiore e inferiore sono uguali oppure almeno 
				uno dei due è nullo fermo il ciclo e ritorno 1*/
				if(confronta_celle(*sup_int,*inf_int)==0 || sup_int->data ==0 || inf_int->data ==0)
					return 1;
				//porto avanti il puntatore superiore
				sup_int=sup_int->next;
				//porto avanti il puntatore inferiore
				inf_int=inf_int->next;
			}
			
				//porto avanti il puntatore al nodo griglia superiore
				sup=sup->next;
				//porto avanti il puntatore al nodo griglia inferiore
				inf=inf->next;
		}
		//se alla fine del ciclo non ci sono mosse ritorno 0
		return 0;
				
}













//richiama controlla_linea e controlla colonna per ogni linea e ogni colonna. Restituisce 1 se ci sono mosse disponibili.
int controlla_mosse(griglia my_griglia,int n){
	//variabile d'appoggio per il nodo griglia
	 struct nodo_griglia* my_nodo=my_griglia->head;
	 //questo ciclo chiama controlla_linea per ogni linea
	 for(int k=0;k<n;k++){
	 	/*se controlla linea restituisce 1 vuol dire che ci sono mosse disponibili sulla linea
	 	quindi esco dal ciclo e ritorno 1*/
	 	if(controlla_linea(my_nodo->linea))
	 		return 1;
		//vado al nodo griglia successivo
		my_nodo=my_nodo->next;	
	
	}
	
	//se ci sono mosse disponibili sulle colonne esco dal ciclo e ritorno 1.
	if(controlla_colonne(my_griglia))
		return 1;

	//se alla fine non ci sono mosse disponibili su tutta la griglia ritorno 0
	return 0;


}


















//elimina la griglia e tutte le linee. Ritorna 1 in caso positivo
void elimina_griglia(griglia my_griglia){
	//flag per l'eliminazione delle linee
	int result;
	//puntatori di appoggio
	struct nodo_griglia* p=my_griglia->head;
	struct nodo_griglia* q=my_griglia->head;
	//se la griglia è vuota
	if(my_griglia==NULL)
		return;
	//cancella tutti i nodi linea e le rispettive linee
	while(q != NULL){
		//p raggiunge q
    		p=q;
    		//q va avanti
        	q = q->next;
		//se non riesce a cancellare una linea restituisce 0
		elimina_linea(p->linea);
		free(p);
	}
	free(q);
	//cancello la griglia
	free(my_griglia);


}














//salvataggio della partita
void salva(giocatore player,int punteggio, classifica new_classifica,griglia my_griglia){
	char n;
	system("clear");
	titolo();
	printf(RESET);
	printf(BOLD_WHITE);
	printf("Vuoi salvare la partita[s/n] ? ");
	int ch;
	//pulisco il buffer
	while ((ch = getchar()) != '\n' && ch != EOF);
	scanf("%c",&n);
	if(n=='s'){
 		system("clear");
 		//se il punteggio viene aggiornato correttamente lo salva sul file
		if(aggiorna_punteggio(new_classifica,player,punteggio))
			//salva su file
			salva_classifica(new_classifica);
		//cancella la griglia
		elimina_griglia(my_griglia);
		return;
	}
	else if(n=='n'){
		//cancella la griglia
		elimina_griglia(my_griglia);
		return;
	}






}













//viene chiamata se il giocatore finisce le mosse e mostra i messaggi di errore e di uscita
void game_over(griglia my_griglia,giocatore player, int punteggio, classifica new_classifica){
		printf(RESET);
		//rosso grassetto
		printf(BOLD_RED);
		//stampa il messaggio di fine partita
		printf("GAME OVER. Hai esaurito le mosse. Premere un carattere per tornare indietro e salvare\n");
		//reset del colore
		printf(RESET);
		char c;
		//pulisco il buffer
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		scanf("%c",&c);
		//fa scegliere se salvare la partita
		salva(player,punteggio, new_classifica, my_griglia);
}































//chiama n volte muovi_destra()
void muovi_destra_griglia(griglia my_griglia,int n, classifica new_classifica){
	//variabile d'appoggio per il nodo griglia
	 struct nodo_griglia* my_nodo=my_griglia->head;
	 //questo ciclo chiama muovi_destra per ogni linea
	 for(int k=0;k<n;k++){
	 	//chiama la funzione muovi linea
	 	muovi_destra(my_nodo->linea,&(my_griglia->parz),n);
		//vado al nodo griglia successivo
		my_nodo=my_nodo->next;	
	
	}
	
	
	
	//se la griglia non è piena inserisce un nuovo elemento in posizione random
	if(!griglia_piena(my_griglia,n))
		inserisci_random_griglia(my_griglia,n);	
	//pulisce l'output
	system("clear");
	//stampa il titolo
	titolo();
	//stampa la griglia
	stampa_griglia(my_griglia,n,my_griglia->parz);
	
	
	//ritorna ai comandi
	return ;

}








//chiama n volte muovi_sinistra()
void muovi_sinistra_griglia(griglia my_griglia,int n, classifica new_classifica){
	//variabile d'appoggio per il nodo griglia
	 struct nodo_griglia* my_nodo=my_griglia->head;
	  //questo ciclo chiama muovi_sinistra per ogni linea
	 for(int k=0;k<n;k++){
	 	muovi_sinistra(my_nodo->linea,&(my_griglia->parz),n);
		//vado al nodo griglia successivo
		my_nodo=my_nodo->next;	
	
	}
	
	
	//se la griglia non è piena inserisce un nuovo elemento in posizione random
	if(!griglia_piena(my_griglia,n))
		inserisci_random_griglia(my_griglia,n);	
	//pulisce l'output
	system("clear");
	//stampa il titolo
	titolo();
	//stampa la griglia
	stampa_griglia(my_griglia,n,my_griglia->parz);
	
	//ritorna ai comandi
	return ;
}












//muove verso sopra la griglia partendo dall'alto
void muovi_sopra(griglia my_griglia, int n, classifica new_classifica){
	//nodo superiore
	struct nodo_griglia* sup=my_griglia->head;
	//nodo inferiore
	struct nodo_griglia* inf=sup->next;
	
	
	/* questo ciclo confronta due linee e poi torna all'inizio n volte*/
	for(int i=0;i<n;i++){
		/*questo ciclo prende in esame due linee e controlla
		i nodi in posizioni uguali */
		while(inf!=NULL){
			//nodo linea superiore		
			struct nodo_linea* sup_int=sup->linea->head;
			//nodo linea inferiroe
			struct nodo_linea* inf_int=inf->linea->head;
			/* questo ciclo sposta i due nodi linea verso
			destra, in modo da controllare le due linee 
			per interi*/
			while(inf_int!=NULL){
				/*se il nodo superiore è nullo sposto 
				l'inferiore verso l'alto*/
				if(sup_int->data==0){
					//il nodo superiore avrà il valore dell'inferiore
					sup_int->data=inf_int->data;
					//il nodo inferiore si svuota
					inf_int->data=0;
					//porto avanti il puntatore superiore
					sup_int=sup_int->next;
					//poro avanti il puntatore inferiore
					inf_int=inf_int->next;

		
				}		
				//se il nodo superiore e inferiore sono uguali
				else if(confronta_celle(*sup_int,*inf_int)==0){
					//il nodo superiore avrà il valore della somma tra esso e l'inferiore
					sup_int->data=somma_celle(*sup_int,*inf_int,&(my_griglia->parz));
					//il nodo inferiore si svuota
					inf_int->data=0;
					//porto avanti il puntatore superiore
					sup_int=sup_int->next;
					//porto avanti il puntatore inferiore
					inf_int=inf_int->next;

				}
				else{
					//porto avanti il puntatore superiore
					sup_int=sup_int->next;
					//porto avanti il puntatore inferiore
					inf_int=inf_int->next;
					
				}
			}
			
				//porto avanti il puntatore al nodo griglia superiore
				sup=sup->next;
				//porto avanti il puntatore al nodo griglia inferiore
				inf=inf->next;
		}
		
		
		
		//i due puntatori tornano all'inizio		
		sup=my_griglia->head;
		inf=sup->next;

	}
					
	
	
	//se la griglia non è piena inserisce un nuovo elemento in posizione random
	if(!griglia_piena(my_griglia,n))
		inserisci_random_griglia(my_griglia,n);	
	//pulisce l'output
	system("clear");
	//stampa il titolo
	titolo();
	//stampa la griglia
	stampa_griglia(my_griglia,n,my_griglia->parz);
	
	//ritorna ai comandi
	return;

}






































//muove verso sotto la griglia partendo dal basso
void muovi_sotto(griglia my_griglia, int n, classifica new_classifica){
	//nodo inferiore
	struct nodo_griglia* inf=my_griglia->tail;
	//nodo superiore
	struct nodo_griglia* sup=inf->prec;
	
	/* questo ciclo confronta due linee e poi torna all'inizio n volte*/
	for(int i=0;i<n;i++){
		/*questo ciclo prende in esame due linee e controlla
		i nodi in posizioni uguali */
		while(sup!=NULL){
			//nodo linea superiore		
			struct nodo_linea* inf_int=inf->linea->head;
			//nodo linea inferiroe
			struct nodo_linea* sup_int=sup->linea->head;
			/* questo ciclo sposta i due nodi linea verso
			destra, in modo da controllare le due linee 
			per interi*/
			while(sup_int!=NULL){
				/*se il nodo superiore è nullo sposto 
				l'inferiore verso l'alto*/
				if(inf_int->data==0){
					//il nodo superiore avrà il valore dell'inferiore
					inf_int->data=sup_int->data;
					//il nodo inferiore si svuota
					sup_int->data=0;
					//porto avanti il puntatore superiore
					inf_int=inf_int->next;
					//poro avanti il puntatore inferiore
					sup_int=sup_int->next;

		
				}		
				//se il nodo superiore e inferiore sono uguali
				else if(confronta_celle(*inf_int,*sup_int)==0){
					//il nodo superiore avrà il valore della somma tra esso e l'inferiore
					inf_int->data=somma_celle(*inf_int,*sup_int,&(my_griglia->parz));
					//il nodo inferiore si svuota
					sup_int->data=0;
					//porto avanti il puntatore superiore
					inf_int=inf_int->next;
					//porto avanti il puntatore inferiore
					sup_int=sup_int->next;

				}
				else{
					//porto avanti il puntatore superiore
					inf_int=inf_int->next;
					//porto avanti il puntatore inferiore
					sup_int=sup_int->next;
					
				}
			}
			
				//porto avanti il puntatore al nodo griglia superiore
				inf=inf->prec;
				//porto avanti il puntatore al nodo griglia inferiore
				sup=sup->prec;
		}
		
		
		
		//i due puntatori tornano all'inizio				
		inf=my_griglia->tail;
		sup=inf->prec;

	}
		
	
	//se la griglia non è piena inserisce un nuovo elemento in posizione random
	if(!griglia_piena(my_griglia,n))
		inserisci_random_griglia(my_griglia,n);	
	//pulisce l'output
	system("clear");
	//stampa il titolo
	titolo();
	//stampa la griglia
	stampa_griglia(my_griglia,n,my_griglia->parz);

	//ritorna ai comandi
	return;





}








































//gestisce gli spazi per le celle
void stampa_cella(int a, char* stringa){
	//ogni cella ha dimensione 7 caratteri
	//se l'elemento della cella è 0 stampa solo spazi
        if(a==0) strcpy(stringa, "       ");
        else{
                //una cifra
                if(a<10){
                        char result[2];
                        sprintf(result,"%d",a);
                        char spazi[8]="   ";
                        strcat(spazi,result);
                        char spazi_2[5]="   ";
                        strcpy(stringa,strcat(spazi,spazi_2));
                }
                //due cifre
                else if(a<100){
                        char result[3];
                        sprintf(result,"%d",a);
                        char spazi[8]="   ";
                        strcat(spazi,result);
                        char spazi_2[3]="  ";
                         strcpy(stringa,strcat(spazi,spazi_2));
                }
                //tre cifre
                else if(a<1000){
                        char result[4];
                        sprintf(result,"%d",a);
                        char spazi[8]="  ";
                        strcat(spazi,result);
                        char spazi_2[3]="  ";
                        strcpy(stringa,strcat(spazi,spazi_2));
                }
                 //quattro cifre
                else if(a>1000){
                        char result[5];
                        sprintf(result,"%d",a);
                        char spazi[8]="  ";
                        strcat(spazi,result);
                        char spazi_2[2]=" ";
                         strcpy(stringa,strcat(spazi,spazi_2));
                }

        }

}




//stampa l'intera griglia e il punteggio
void stampa_griglia(griglia my_griglia,int n,int p){
	printf(BOLD_WHITE);
	printf("Punteggio: %d\n",p);
	//stringa che contiene il valore della cella
	char cella[8];
	//variabile d'appoggio per il nodo griglia
	struct nodo_griglia* my_nodo=my_griglia->head;
	//cicla fino alla fine del nodo griglia
	while(my_nodo!=NULL){
		//le prossime 7 righe servono per stampare la cornice
		for(int i=0;i<((7*n)+(n+1)*2);i++){
			printf(".");
		}
		printf("\n");
		for(int i=0;i<n;i++)
			printf("..       ");
		printf("..");
		printf("\n");
		//variabile di appoggio per il nodo linea
		struct nodo_linea* my_nodol= my_nodo->linea->head;
		//cicla fino alla fine del nodo linea
		while(my_nodol!=NULL){
			//il valore della cella viene converito e inserito nella stringa cella
			stampa_cella(my_nodol->data,cella);
			//stampo il valore nel nodo linea
       			 printf("..%s",cella);
			//vado al nodo linea successivo
		        my_nodol=my_nodol->next;
		}
		//le prossime 6 righe servono per stampare la cornice
		printf("..");
		printf("\n");
		  for(int i=0;i<n;i++) 
                        printf("..       ");
                printf("..");
                printf("\n");
		//vado al nodo griglia successivo
		my_nodo=my_nodo->next;
	}
	//cornice inferiore
	for(int i=0;i<((7*n)+(n+1)*2);i++){
                        printf(".");
                }

	printf("\n");
}

