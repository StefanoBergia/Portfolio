#include <stdio.h>

#define MAXV 20

//legge un vettore inserito da tastiera
int leggiVettore(int V[]);
//unisce due vettori in un terzo vettore
int unione(int V1[],int l1,int V2[],int l2,int V3[]);
//esegue la differenza insiemistica di due vettori inserendo il risultato in un terzo vettore
int differenza(int V1[],int l1,int V2[],int l2,int V3[]);
//esegue l'intersezione di due vettori inserendo il risultato in un terzo vettore
int intersezione(int V1[],int l1,int V2[],int l2,int V3[]);
//restituisce 1 se un intero 'n' è contenuto nel vettore V
int contiene(int V[],int l, int n);
//stampa a video il vettore V
void stampaVettore(int V[],int l);

int main() {

    int V1 [MAXV];
    int V2 [MAXV];
    int V3 [2*MAXV];
    int l1,l2,l3;

    printf("caricamento del primo vettore...\n");
    l1=leggiVettore(V1);

    printf("\ncaricamento del secondo vettore...\n");
    l2=leggiVettore(V2);


    printf("unione:\n");
    l3=unione(V1,l1,V2,l2,V3);
    stampaVettore(V3,l3);

    printf("\ndifferenza:\n");
    l3=differenza(V1,l1,V2,l2,V3);
    stampaVettore(V3,l3);

    printf("\nintersezione:\n");
    l3=intersezione(V1,l1,V2,l2,V3);
    stampaVettore(V3,l3);

    return 0;
}

int leggiVettore(int V[]){
    int l,i;

    do {
        printf("inserisci lunghezza vettore--> ");
        scanf("%d",&l);
    }while(l>20 || l<1);

    for(i=0;i<l;i++){
        printf("inserisci elemeno %d ",i+1);
        scanf("%d",&V[i]);
    }
    return l;
};

int unione(int V1[],int l1,int V2[],int l2,int V3[]){
    int i,j;

    //scorro il primo vettore e ne inserisco tutti gli elementi nel terzo
    for(i=0,j=0;j<l1;j++) {

        if(contiene(V3,i,V1[j])==-1) {  //prima di inserire un lemento controllo che esso non sia già presente
            V3[i] = V1[j];
            i++;
        }
    }

    //scorro il secondo vettore e ne inserisco tutti gli elemento nel terzo
    for(j=0;j<l2;j++) {
        if(contiene(V3,i,V2[j])==-1) {  //prima di inserire un lemento controllo che esso non sia già presente
            V3[i] = V2[j];
            i++;
        }
    }
    //ritorno la lunghezza di V3
    return i;
}

int  differenza(int V1[],int l1,int V2[],int l2,int V3[]){
    int i,j;

    //scorro il primo vettore
    for(i=0,j=0;j<l1;j++){
        //controllo che ogni elemnto del primo vettore non sia contenuto nel secondo e che non sia già stato inserito
        if(contiene(V2,l2,V1[j])==-1 && contiene(V3,i,V1[j])==-1){
            V3[i]=V1[j];
            i++;
        }
    }

    //scorro il secondo vettore
    for(j=0;j<l2;j++){
        //controllo che ogni elemnto del secondo vettore non sia contenuto nel primo e che non sia già stato inserito
        if(contiene(V1,l1,V2[j])==-1 && contiene(V3,i,V2[j])==-1){
            V3[i]=V2[j];
            i++;
        }
    }

    //ritorno la lunghezza di V3
    return i;
}

int intersezione(int V1[],int l1,int V2[],int l2,int V3[]){
    int i,j;
    //scorro il primo vettore
    for(i=0,j=0;j<l1;j++){
        //controllo che ogni elemnto del primo vettore sia contenuto nel secondo e che non sia già stato inserito
        if(contiene(V2,l2,V1[j])==1 &&  contiene(V3,i,V1[j])==-1){
            V3[i]=V1[j];
            i++;
        }
    }

    //ritorno la lunghezza di V3
    return i;
}

int contiene(int V[],int l, int n){
    int i;

    for(i=0;i<l;i++)
        if(V[i]==n)
            return 1;

    return -1;
}

void stampaVettore(int V[],int l){
    int i;
    printf("{ ");
    for (i=0;i<l;i++)
        printf("%d ",V[i]);
    printf("}\n");
}