#ifndef CLASSIFICA_H
#define CLASSIFICA_H
#include <stdio.h>

//classifica
struct giocatore{
	char nickname[10];
	char password[10];
	int punteggio;
	struct giocatore* next;

};


typedef struct giocatore* giocatore;

struct classifica{
	struct giocatore* head;
};

typedef struct classifica* classifica;


classifica carica_classifica();

void stampa_classifica(classifica my_classifica);

int esiste_nickname(classifica my_classifica,char* nickname);

giocatore inserisci_giocatore(classifica my_classifica,char* nickname,char* password,int punteggio);

giocatore login(classifica my_classifica, char* nickname,char* password);

int elimina_giocatore(classifica my_classifica,char* nickname);

void cancella_classifica(classifica my_classifica);

int aggiorna_punteggio(classifica my_classifica, giocatore player,int punteggio);

void salva_classifica(classifica my_classifica);



#endif
