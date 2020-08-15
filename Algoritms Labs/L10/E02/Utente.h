//
// Created by stefano on 16/01/18.
//

#ifndef E02_UTENTE_H
#define E02_UTENTE_H

#define MAXC 10

typedef struct{
    char cardID[MAXC +1];
    int * stazioni;
    int inizio;
    int fine;
    int flag;
    int n;
}Utente;

Utente * New(char * cardID, int n);
Utente * ItemSetVoid();
int ITEMCompare(Utente*,Utente*);
void ITEMprint(Utente *);
#endif //E02_UTENTE_H
