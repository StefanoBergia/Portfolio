#include <stdio.h>

#define MAXV 30

int mediaMobile(int V[], int v, int k, float M[]);

int main() {
    int V[MAXV];
    float M[MAXV];
    int k,l,i,lm;

    do {
        printf("inserisci lunghezza vettore ");
        scanf("%d", &l);
    }while(l>30 || l<0);

    for(i=0;i<l;i++){
        printf("\ninserisci elemento alla posizione %d ",i);
        scanf("%d",&V[i]);
    }

    do {
        printf("\ninserisci valore di k ");
        scanf("%d", &k);
    }while(k>l || k<0);

    lm=mediaMobile(V,l,k,M);

    printf("\n il vettore delle medie è { ");
    for(i=0;i<lm;i++)
        printf("%.3f ",M[i]);
    printf("}");
    return 0;
}

int mediaMobile(int V[], int v, int k, float M[]){
    int s=0,y=0,i,j;


    //ciclo dalla posizione 0 alla posizione v-k (lunghezza del vettore media)
    /*la variabile j viene utilizzata come contatore per determinare a quale gruppo
      di valori appartiene quello nella posizione corrente del vettore*/
    //la variabile y viene usata come indice per il vettore delle medie

    for (i=0,j=0;i<v-k+1;j++){
        if(j<k){
            s+=V[i+j];          //incremento la variabile s(somma) del valore corrente nel vettore dei valori
        }else {
            j = -1;             //porto j a -1 in modo che valga 0 nel prossimo ciclo
            M[y]=(float)s/k;    //calcolo la media
            s=0;
            y++;
            i++;
        }
    }
    return y;                   //restituisco la lunghezza del vettore media
}