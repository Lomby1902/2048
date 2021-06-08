#ifndef GRIGLIA_H
#define GRIGLIA_H

#include <stdio.h>
#include "linea.h"
#include "classifica.h"


//griglia
struct nodo_griglia{
        linea linea;
	struct nodo_griglia* next;
	struct nodo_griglia* prec;
};

struct griglia{
	int parz;
	giocatore player;
	struct nodo_griglia* head;
	struct nodo_griglia* tail;
};

typedef struct griglia* griglia;





griglia crea_griglia();

int popola_griglia(griglia my_griglia,int n,giocatore player);

void stampa_griglia(griglia my_griglia,int n,int punteggio);

int griglia_piena(griglia my_griglia, int n);

void inserisci_random_griglia(griglia my_griglia,int n);

void muovi_destra_griglia(griglia my_griglia, int n, classifica new_classifica);

void muovi_sinistra_griglia(griglia my_griglia,int n,  classifica new_classifica);

void muovi_sopra(griglia my_griglia,int n, classifica new_classifica);

void muovi_sotto(griglia my_griglia,int n,  classifica new_classifica);

int controlla_colonne(griglia my_griglia);

int controlla_mosse(griglia my_griglia,int n);

void elimina_griglia(griglia my_griglia);

void game_over(griglia my_griglia,giocatore player, int punteggio, classifica new_classifica);

void salva(giocatore player,int punteggio, classifica new_classifica,griglia my_griglia);


#endif


