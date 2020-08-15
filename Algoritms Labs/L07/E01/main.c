#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define MAXC 20

typedef struct {
    char nome[MAXC+1];
    int popolazione;
    int distanza_assoluta;
    int *distanze;          //memorizza le distanze mutue
}city;


city ** leggi_file(FILE * fp,int *n);

void comb(city ** cities,city ** sol,int *min_sum,city ** cur,int n,int k,int pos,int start);       //utilizzo il modello delle combinazioni semplici
int * calcola_distanze(city ** cities,int n,int pos);
int  somma_distanze(city **cities,city ** ato,int n,int k);
void QuickSort(city ** v,int l,int r );
int partition(city ** v,int l,int r);
void stampa_citta(city **v,int n);

int main(int argc, char ** argv) {
    city ** cities,** sol,** supp;
    int n,k,i,s=-1;
    FILE * fp;
    if(argc==3){
        fp=fopen(argv[1],"r");
        cities=leggi_file(fp,&n);
        fclose(fp);

        //stampa_citta(cities,n);

        k=atoi(argv[2]);
        sol=(city **)malloc(k*sizeof(city *));          //soluzione ottima finale
        supp=(city **)malloc(k*sizeof(city *));         //soluzione ottima corrente
        comb(cities,sol,&s,supp,n,k,0,0);

        printf("{ ");
        for(i=0;i<k;i++)
            printf("%s ",sol[i]->nome);
        printf("}");

        free(sol);
        free(supp);
        for(i=0;i<n;i++)
            free(cities[i]);
        free(cities);
    }

    return 0;
}

city ** leggi_file(FILE * fp,int *n){
    int i;
    city ** cities;
    fscanf(fp,"%d",n);
    cities=(city **)malloc((*n)*sizeof(city *));
    for(i=0;i<*n;i++) {
        cities[i]=(city *)malloc(sizeof(city));
        fscanf(fp, "%s %d %d", cities[i]->nome, &cities[i]->popolazione, &cities[i]->distanza_assoluta);
    }

    QuickSort(cities,0,(*n)-1);                                 //ordino le citta in base alla distanza assoluta con il quicksort
    for(i=0;i<*n;i++) {
        cities[i]->distanze = calcola_distanze(cities, *n, cities[i]->distanza_assoluta);       //alloco e popolo ill vettore delle distanze minime
    }

    return cities;
}

int * calcola_distanze(city ** cities,int n,int pos){
    int i,*dist;
    dist=(int *)malloc(n* sizeof(int));
    for(i=0;i<n;i++)                                        //scorro il vettore delle città
        dist[i]=abs(cities[i]->distanza_assoluta-pos);      //calcolo la distanza mutua per la città corrente
    return  dist;
}

void comb(city ** cities,city ** sol,int * min_sum,city ** cur,int n,int k,int pos,int start){
    int i,j,sum;
    if(pos>=k){                                 //fermo la ricorsione una volta etratti k elementi
        sum=somma_distanze(cities,cur,n,k);     //calcolo la somma per le ato scelte
        if(sum<*min_sum || *min_sum<0){         //verifico se la soluzione trovata è migliore della vecchia soluzione
            for(i=0;i<k;i++)                    //in questo caso aggiorno il vettore sol e la variabile min_sum
                sol[i]=cur[i];
            *min_sum=sum;
        }
        return;
    }
    for(i=start;i<n;i++){
        cur[pos]=cities[i];
        comb(cities,sol,min_sum,cur,n,k,pos+1,i+1);
    }
    return;
}

int  somma_distanze(city **cities,city ** ato,int n,int k){
    int i,sum,cur=0;                                                    //cur è l'indice dell'ATO corrente
    for(i=0, sum=0;i<n;i++){                                            //ciclo sulle città
        if(cur<(k-1) && ato[cur]->distanze[i]>ato[cur+1]->distanze[i])  //quando la distanza con l'ato corrente è più grande
                                                                        // rispetto a quella con l'ato succesiva per la città attualmente visitata)
            cur++;                                                      // aumento l'indice dell'ato corrente
        sum+=ato[cur]->distanze[i]*cities[i]->popolazione;      //calcolo il prdotto distanza*popolazione per la città corrente
    }
    return sum;
}


void QuickSort(city ** v,int l,int r ){
    int q;
    if(l>=r)
        return ;
    q=partition(v,l,r);
    QuickSort(v,l,q-1);
    QuickSort(v,q+1,r);

}

int partition(city ** v,int l,int r){
    int i=l-1,j=r;
    city * pivot=v[r];
    city * supp;
    for(;;){
        while(v[++i]->distanza_assoluta<pivot->distanza_assoluta);
        while(v[--j]->distanza_assoluta>pivot->distanza_assoluta);
        if(j==l)
            break;
        if(i>=j)
            break;
        supp=v[i];
        v[i]=v[j];
        v[j]=supp;
    }
    supp=v[i];
    v[i]=v[r];
    v[r]=supp;
    return i;
}

void stampa_citta(city **v,int n){
    int i,j;
    for(i=0;i<n;i++){
        printf("%s %d %d [ ",v[i]->nome,v[i]->popolazione,v[i]->distanza_assoluta);
        for(j=0;j<n;j++)
            printf("%d ",v[i]->distanze[j]);
        printf("}\n");
    }
}
