#include <stdio.h>
#include "linea.h"
#include <stdlib.h>




//crea una linea vuota
linea crea_linea(){
	//alloco la linea nell'heap
	linea new_linea=(struct linea*)malloc(sizeof(struct linea));
	//in caso di errore restituisco NULL
	if(new_linea==NULL) return NULL;
	//la linea è vuota quindi head e tail saranno NULL
	new_linea->head=NULL;
	new_linea->tail=NULL;
	//ritorna la linea creata
	return new_linea;


}





//inserisce gli elementi nelle celle creando n nodi, ritorna 0 in caso positivo
int inserisci_cella(linea my_linea, int elem){
        struct nodo_linea *p;
        p= (struct nodo_linea *) malloc(sizeof(struct nodo_linea));
        if(p==NULL) return 1;
        p->data = elem;
        p->next = my_linea->head;
        p->prec = NULL;
        if (my_linea->head==NULL) // se la lista è vuota
                my_linea->tail=p;
        else
                my_linea->head->prec = p;
        my_linea->head=p;
        return 0;
}










//verifica se la linea è piena. Restituisce 1 se lo è, 0 se non lo è
int linea_piena(linea my_linea){
//variabile d'appoggio per il nodo linea
	struct nodo_linea* my_nodo=my_linea->head;
	while(my_nodo!=NULL ){
		if(my_nodo->data==0)
			return 0;
		my_nodo=my_nodo->next;
	}
	return 1;
}






//inserisce un 2 o un 4 in una cella random della linea
void inserisci_random(linea my_linea, int n){
	//genera un numero casuale tra 0 e n-1 per la posizione
	int r =rand() % n;
	//genera un numero casuale tra 2 e 4
	int elem=((rand() % 2)+1) * 2;
	//variabile d'appoggio per il nodo_linea
	struct nodo_linea* my_nodo=my_linea->head;
	//contatore
	int k=0;
	//ciclo che scorre la linea
	while(k<r){
		//vado al nodo successivo
		my_nodo=my_nodo->next;
		//incremento il contatore
		k++;
	}
	//quando sono uscito dal ciclo posso inserire il numero nella cella
	
	//se la cella è vuota inserisco l'elemento
	if(my_nodo->data==0)
		my_nodo->data=elem;
	/*visto che prima di chiamare questa funzione viene controllato se 
	la linea non sia piena, allora nel caso in cui la cella sia vuota posso
	richiamare la funzione inserisci_random() ricorsivamente fino a quando non 
	trovo un elemento vuoto */
	else
		inserisci_random(my_linea,n);
}











//confronta il nodo prec con il nodo next, in caso positivo ritorna 0
int confronta_celle(struct nodo_linea prec, struct nodo_linea next){
	//confronta il campo data dei due nodi
	if(prec.data==next.data)
		//in caso positivo ritorna 0
		return 0;
	else 
		//in caso negativo ritorna 1
		return 1;

}







//verifica se ci sono mosse disponibili nella linea. Restituisce 1 se ci sono, 0 altrimenti
int controlla_linea(linea my_linea){
	//variabile d'appoggio per il nodo_linea precedente
	struct nodo_linea* my_nodo_prec=my_linea->head;
	//variabile d'appoggio per il nodo_linea successivo
	struct nodo_linea* my_nodo_next=my_nodo_prec->next;
	//questo ciclo controlla se ci sono due celle vicine uguali
	while(my_nodo_next!=NULL ){
		/*se le due celle sono uguali oppure almeno una delle due è nulla
		si ferma il ciclo e restituisce 1*/
		if(confronta_celle(*my_nodo_prec,*my_nodo_next)==0 || my_nodo_prec->data ==0 || my_nodo_next->data==0)
			return 1;
		//sposto in avanti i puntatori
		my_nodo_prec=my_nodo_prec->next;
		my_nodo_next=my_nodo_next->next;
	}
	
	//se non ho trovato mosse disponibili sulla linea ritorno 0
	return 0;

}

















//esegue la somma del contenuto delle celle prec e next e la restituisce
int somma_celle(struct nodo_linea prec, struct nodo_linea next,int * parz){
		//variabile locale che contiene la somma
		int somma=prec.data+next.data;
		//aggiorna il punteggio salvato in griglia
		*parz=*parz+somma;
		//ritorna la somma
		return somma;	
}













//verifica se la linea è vuota. Restituisce 1 se lo è, 0 se non lo è
int linea_vuota(linea my_linea){
	//variabile d'appoggio per il nodo linea
	struct nodo_linea* my_nodo=my_linea->head;

	while(my_nodo!=NULL ){
		if(my_nodo->data!=0)
			return 0;
		my_nodo=my_nodo->next;
	}
	return 1;

}











//muove a destra gli elementi di una linea
void muovi_destra(linea my_linea,int* parz,int n){
	//variabile d'appoggio per il nodo linea interno
	struct nodo_linea* my_nodo_int=my_linea->tail;
	/*questo ciclo esegue le somme a due a due tornando poi all'inizio per n volte */
	for(int i=0;i<n;i++){
		/*il nodo interno parte dalla fine. Somma gli ultimi elementi uguali e
		 poi sposta gli elementi uno ad uno verso destra*/
		while(my_nodo_int->prec!=NULL){
			//se l'elemento è vuoto devo spostare tutte le celle verso destra
			if(my_nodo_int->data==0){
					//la cella vuota avrò il valore della precedente
					my_nodo_int->data=my_nodo_int->prec->data;
					//la cella precedente si svuota
					my_nodo_int->prec->data=0;
					//vado al nodo precedente
					my_nodo_int=my_nodo_int->prec;
			}
			//verifico se le celle sono uguali
			else if(confronta_celle(*(my_nodo_int->prec),*my_nodo_int)==0){
				//se sono uguali la cella a destra avrà il valore della somma di essa e di quella accanto
				my_nodo_int->data=somma_celle(*(my_nodo_int->prec), *my_nodo_int, parz);
				//la cella di sinistra della coppia si svuota
				my_nodo_int->prec->data=0;
				//vado al nodo precedente
				my_nodo_int=my_nodo_int->prec;
			}
			else{
				//se i due nodi non sono uguali, vado al nodo precedente
				my_nodo_int=my_nodo_int->prec;
			}
		}
		
		//il ciclo torna all'inizio
		my_nodo_int=my_linea->tail;
			
		
	} 
	

}








//Elimina una linea. Restituisce 1 in caso positivo
void elimina_linea(linea my_linea){
	//puntatori di appoggio
	struct nodo_linea* p=my_linea->head;
	struct nodo_linea* q=my_linea->head;
	//se la linea è vuota
	if(my_linea==NULL)
		return;
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

	free(my_linea);
}





























//muove a destra gli elementi di una linea
void muovi_sinistra(linea my_linea,int* parz,int n){
	//variabile d'appoggio per il nodo linea interno
	struct nodo_linea* my_nodo_int=my_linea->head;
	/*questo ciclo esegue le somme a due a due tornando poi all'inizio per n volte */
	for(int i=0;i<n;i++){
		/*il nodo interno parte dall'inizio. Somma i primi elementi uguali e
		 poi sposta gli elementi uno ad uno verso sinistra*/
		while(my_nodo_int->next!=NULL){
			//se l'elemento è vuoto devo spostare tutte le celle verso sinistra
			if(my_nodo_int->data==0){
					//la cella vuota avrà il valore della successiva
					my_nodo_int->data=my_nodo_int->next->data;
					//la cella successiva si svuota
					my_nodo_int->next->data=0;
					//vado al nodo successivo
					my_nodo_int=my_nodo_int->next;
			}
			//verifico se le celle sono uguali
			else if(confronta_celle(*(my_nodo_int->next),*my_nodo_int)==0){
				//se sono uguali la cella a sinistra avrà il valore della somma di essa e di quella accanto
				my_nodo_int->data=somma_celle(*(my_nodo_int->next), *my_nodo_int, parz);
				//la cella di destra della coppia si svuota
				my_nodo_int->next->data=0;
				//vado al nodo successivo
				my_nodo_int=my_nodo_int->next;
			}
			else{
				//se i due nodi non sono uguali, vado al nodo successivo
				my_nodo_int=my_nodo_int->next;
			}
		}
		//il ciclo torna all'inizio
		my_nodo_int=my_linea->head;
			
			
	} 

}






