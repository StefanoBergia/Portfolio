#include <stdio.h>
#include "Item.h"
#include "PQ.h"

#define MAXG 50
#define MAXC 10

int GetCmd();

int main() {

    FILE *fp;
    int cmd=1;
    PQ pq=PQUEUEinit(MAXG);
    Item_p sup;
    Item item1,item2;
    char let[MAXC+1];

    while(cmd!=0){
        cmd=GetCmd();
        switch (cmd){
            case 1:
                printf("inserisci nome del file-->");
                scanf("%s",let);
                fp=fopen(let,"r");
                PQRead(pq,fp);
                fclose(fp);

                //PQWrite(pq,stdout);
                printf("\nlettura eseguita\n");
                break;
            case 2:
                printf("inserisci nome del file-->");
                scanf("%s",let);
                fp=fopen(let,"w");
                PQWrite(pq,fp);
                fclose(fp);
                printf("scrittura eseguita\n");
                break;
            case 3:
                printf("inserisci nome del partecipante-->");
                scanf("%s",let);
                sup=ItemNew();
                ItemSetNome(sup,let);
                ItemSetPunti(sup,10);
                PQUEUEinsert(pq,*sup);
                ItemFree(sup);
                printf("concorrente inserito\n");
                break;
            case 4:
                printf("inserisci nome del partecipante-->");
                scanf("%s",let);
                PQRemove(pq,PQLinearSearch(pq,let));
                printf("concorrente inserito\n");
                break;
                break;
            case 5:
                if(PQUEUEsize(pq)>=2){
                    item1=PQUEUEextractMin(pq);
                    item2=PQUEUEextractMin(pq);
                    printf("Sfida tra %s %s...\n",ItemGetNome(&item1),ItemGetNome(&item2));
                    if(ItemMatch(&item1,&item2)==&item1) {
                        printf("il vincitore è %s\n",ItemGetNome(&item1));
                        PQUEUEinsert(pq,item1);
                        if(ItemGetPunti(&item2)>0)
                            PQUEUEinsert(pq,item2);
                        else
                            printf("%s è stato eliminato\n",ItemGetNome(&item2));
                    }else{
                        printf("il vincitore è %s\n",ItemGetNome(&item2));
                        PQUEUEinsert(pq,item2);
                        if(ItemGetPunti(&item1)>0)
                            PQUEUEinsert(pq,item1);
                        else
                            printf("%s è stato eliminato\n",ItemGetNome(&item1));
                    }
                }else
                    printf("non ci sono abbastanz partecipanti\n");
                break;
            case 6:
                PQShowRank(pq);
                break;
            case 0:
                printf("FINE PROGRAMMA");
                break;
            default:
                printf("ANZIONE! comando non risconosciuto\n");
        }
    }

    return 0;
}

int GetCmd(){
    int c;
    printf("1-LEGGI\n");
    printf("2-SCRIVI\n");
    printf("3-AGGIUNGI\n");
    printf("4-RIMUOVI\n");
    printf("5-SFIDA\n");
    printf("6-MOSTRA\n");
    printf("0-FINE\n");
    printf("-->");
    scanf("%d",&c);
    return  c;
}