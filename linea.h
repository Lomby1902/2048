#ifndef LINEA_H
#define LINEA_H



//linee
struct nodo_linea{
        int data;
        struct nodo_linea* next; 
        struct nodo_linea* prec;
};

struct linea{
        struct nodo_linea* head;
        struct nodo_linea* tail;
};

typedef struct linea* linea;




linea crea_linea();

int inserisci_cella(linea my_linea,int elem);

void inserisci_random(linea my_linea,int n);

int confronta_celle(struct nodo_linea prec, struct nodo_linea next);

int controlla_linea(linea my_linea);

int somma_celle(struct nodo_linea prec,struct nodo_linea next,int* parz);

int linea_piena(linea my_linea);

void muovi_destra(linea my_linea,int* parz, int n);

void muovi_sinistra(linea my_linea,int* parz, int n);

void elimina_linea(linea my_linea);

#endif




