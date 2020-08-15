#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "Utente.h"
#include "BST.h"

#define MAXC 10
typedef struct{
    char stationId[MAXC+1];
    int nBici;
    int nPosti;
    int nNoleggi;
}Stazione;

void stampaStazioni(Stazione * stazioni,int N);
Stazione * leggiStazioni(FILE * fp, int* N);
int leggiTessera(char *cardId, char *stationId,Stazione * stazioni,int N, BST  utenti,int time);
int  Ricerca(char * stationId,Stazione * stazioni,int N);

void stampamenu(){
    printf("inserisci comando:\n");
    printf("1-visualizza stazioni\n");
    printf("2-visualizza utenti\n");
    printf("3-leggi tessera\n");
}

int main(int argc, char ** argv) {
    int cmd,N,time;
    char cardId[MAXC+1],stationId[MAXC+1];
    FILE * fp;
    BST utenti=BSTinit();
    Stazione * stazioni;
    fp=fopen(argv[1],"r");
    stazioni=leggiStazioni(fp,&N);
    stampamenu();
    scanf("%d",&cmd);
    while(cmd!=0){
        switch (cmd){
            case 1:
                stampaStazioni(stazioni,N);
                break;
            case 2:
                BST_print(utenti);
                break;
            case 3:
                printf("inserisci cardid, stationid e time ==> ");
                scanf("%s %s %d",cardId,stationId,&time);
                leggiTessera(cardId,stationId,stazioni,N,utenti,time);
                break;
        }
        stampamenu();
        scanf("%d",&cmd);
    }
    return 0;
}

void stampaStazioni(Stazione * stazioni,int N){
    int i;
    for(i=0;i<N;i++)
        printf("nome:%s\tnPosti:%d\tnBici:%d\tnNoleggi%d\n",stazioni[i].stationId,stazioni[i].nPosti,stazioni[i].nBici,stazioni[i].nNoleggi);
    printf("\n");
}

Stazione * leggiStazioni(FILE * fp, int* N){
    int i;
    Stazione * ret;
    fscanf(fp,"%d",N);
    ret=(Stazione *)malloc(*N*sizeof(Stazione));
    for(i=0;i<*N;i++){
        fscanf(fp,"%s %d %d",ret[i].stationId,&ret[i].nBici,&ret[i].nPosti);
        ret[i].nNoleggi=0;
    }
    return ret;
}

 int  Ricerca(char * stationId,Stazione * stazioni,int N){
    int i;
    for(i=0;i<N;i++)
        if(strcmp(stazioni[i].stationId,stationId)==0)
            return i;
    return -1;
}

int leggiTessera(char *cardId, char *stationId,Stazione * stazioni,int N, BST  utenti,int time){
    int id =Ricerca(stationId,stazioni,N);
    Stazione * station=&stazioni[id];
    Utente * utente;
    if(id !=-1){
        utente=BST_search(utenti,cardId);
        if(utente==NULL)
        {
            utente=New(cardId,N);
            BSTinsert(utenti,utente);
        }

        if(utente->flag){
            if((station->nPosti-station->nBici)>0){
                station->nBici++;
                utente->fine=time;
                utente->flag=0;
                printf("noleggio utente %s dalle %d alle %d finito nella stazione %s\n",cardId,utente->inizio,utente->fine,stationId);
            }else
                printf("non ci sono posti liberi disponibili nella seguente stazione:%s\n",stationId);
        }else{
            if(station->nBici>0){
                station->nBici--;
                station->nNoleggi++;
                utente->stazioni[id]++;
                utente->inizio=time;
                utente->flag=1;
                printf("noleggio utente %s iniziato alle %d nella stazione %s\n",cardId,utente->inizio,stationId);
            }else
                printf("non ci sono bici disponibili nella seguente stazione:%s\n",stationId);

        }
    }else
        printf("stazione inesistente\n");
}