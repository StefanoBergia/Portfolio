#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <values.h>


int confronta(int * sequenza,int n,int start,int size);             //restituisce il numero di scambi per una sottostruttura ottima
void calcola_costi(int * sequenza, int ** costi, int n);            //popola la matrice con i costi degli scambi per le sotto-strutture ottime
int * costruisci_soluzione(int * sequenza,int ** costi,int n);      //ricostruisce la soluzione migliore
int print_insieme(int * sequenza,int *sol,int n);                   //stampa la soluzione

int main(int argc, char ** argv){
    int * sequenza, ** costi,*sol;
    int i,n;
    n=atoi(argv[1]);
    sequenza=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        sequenza[i] = argv[2][i] - '0';

    costi=(int **)malloc(n/2*sizeof(int *));
    for(i=0;i<n/2;i++)
        costi[i]=(int *)malloc(n/2*sizeof(int));

    calcola_costi(sequenza,costi,n);

    printf("matrice sottostrutture ottime\n");
    int j;
    for(i=0;i<n/2;i++) {
        for (j = 0; j < n / 2; j++) {
            if(costi[i][j]!=-1)
                printf("%d ", costi[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("blocchi trovati: ");
    sol=costruisci_soluzione(sequenza,costi,n);

    for(i=0;i<n/2;i++)
        if(sol[i]!=-1)
            printf("%d ",sol[i]);

    printf("\n\nl'iniseme minimo di scambi è: ");
    print_insieme(sequenza,sol,n);

    free(sol);
    free(sequenza);
    for(i=0;i<n/2;i++)
        free(costi[i]);
    free(costi);

    return 0;
}

void calcola_costi(int * sequenza, int ** costi, int n){
    int i,j;

    for(i=0;i<n/2;i++)
        for(j=0;j<n/2;j++)
            costi[i][j]=-1;

    for(i=0;i<n/2;i++)
        for(j=0;j<n/2-i;j++)
            costi[i][j]=confronta(sequenza,n,2*i,2+2*j);

}

int confronta(int * sequenza,int n,int start,int size){
    int i,cur=0,split,sum=0;
    split=start+size/2;                                 //calcolo la posizione dello scontro
    for(i=start;i<start+size;i++){
        if(i==split)
            cur++;
        if(sequenza[i]!=cur)
            sum++;
    }
    return sum;
}

//costruisco la soluzione scgliendo la soluzione ottimale che di
//volta in volta ha numero di scambi minore

int * costruisci_soluzione(int * sequenza,int ** costi,int n){
    int * sol=(int *)malloc(n/2*sizeof(int));
    int min,min_s,i,j,k,cursize=0;
    for(i=0;i<n/2;i++)
        sol[i]=-1;
    i=0;
    k=0;
    while(i<n/2){
        min=INT_MAX;
        for(j=0;j<n/2-i ;j++){      //il -i serve per escludere le sottostrutture che eccedono la soluzione massima
            if(costi[i][j]<=min){
                min=costi[i][j];
                min_s=j;
            }
        }
        cursize+=2+2*min_s;
        sol[k]=2+2*min_s;          //slavo la dimensione dello scontro scelto nella posizione corrente del vettore soluzione
        k++;
        i=cursize/2;               //passo al prossimo livello di soluzioni ottime (salto quelle che per questioni di indici non ossono essere valide)
    }
    return sol;
}

int print_insieme(int * sequenza,int *sol,int n){
    int i,j,js,split,cur;
    printf("{ ");
    for(i=0,j=0,js=0;i<n/2 && sol[i]!=-1;i++){
        split=sol[i]/2;
        cur=0;
        for(;j<js+sol[i];j++){
            if(j==js+split)
                cur++;
            if(sequenza[j]!=cur)
                printf("%d ",j);
        }
        js=j;
    }
    printf("}");
}

