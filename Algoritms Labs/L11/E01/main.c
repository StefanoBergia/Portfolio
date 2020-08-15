#include <stdio.h>
#include <malloc.h>
#include <values.h>
#include "Graph.h"
#include "Edge.h"

void powerset(Graph G,int k, int* sol);
int powerset_r(Graph G, int k, int* sol, int n, int pos, int start);
void RicollegaAlberi(Graph G);

int main(int argc, char ** argv) {
    FILE * fp;
    Graph G;
    int * sol;
    if(argc==2){

        fp=fopen(argv[1],"r");
        G=GRAPHread(fp);
        fclose(fp);

        printf("Il grafo letto dal file è:\n");

        GRAPHshow(G);
        GRAPHdistances(G);

        printf("\ntabella distanze minime:\n");
        GRAPHprintDistances(G);

        printf("\n");


        Graph copy;
        copy=GraphCopy(G);


        printf("Nodi da rimuovere per rendere grafo aciclico:\n\n");
        sol=malloc(GRAPHnV(G)*sizeof(int));
        powerset(G,GRAPHnV(G),sol);
        free(sol);
        GRAPHfree(G);



    }
    return 0;
}

void powerset(Graph G,int k, int* sol){
    int flag = 0, n;
    if(!GRAPHcycle(G)) {
        printf("il grafo è già aciclico\n");
        return;
    }
    for(n = 1; n <= k && ! flag; n++)
         flag=(powerset_r( G,k, sol, n, 0, 0)>0);

    return ;
}

int powerset_r(Graph G, int k, int* sol, int n, int pos, int start){
    int count=0 ,i;
    Graph copy;
    if (pos == n){
        copy=GraphCopy(G);

        for(i=0;i<n;i++)
            GraphRemoveV(copy, sol[i]);

        if(!GRAPHcycle(copy)){

            printf("nodi rimossi: { ");
            for(i=0;i<n;i++)
                printf("%s ",GRAPHgetNode(G,sol[i]));
            printf("}\n");

            RicollegaAlberi(copy);
            GRAPHfree(copy);

            return 1;
        }
        return 0;

    }
    for (i = start; i < k; i++){
        sol[pos] = i;
        count+=powerset_r( G,k, sol, n, pos+1, i+1);
    }
    return count;
}

void RicollegaAlberi(Graph G){
    int * cc=GRAPHcc(G);
    int n=INT_MIN,i,j,k,min=INT_MAX;
    Edge e;
    for(i=0;i<GRAPHnV(G);i++) {
        if (cc[i] > n)
            n = cc[i];
        //printf("%s:%d ",GRAPHgetV(G,i),cc[i]);
    }
    //printf("|%d \n",n);
    if(n==0){
        printf("\t=>non è necessario aggiungere nessun arco\n\n");
    }
    for(k=0;k<n;k++){
        for(i=0;i<GRAPHnV(G);i++){
            if(cc[i]<=k && cc[i]>=0)
            {
                for(j=0;j<GRAPHnV(G);j++)
                {
                    if(cc[j]==k+1)
                    {
                        if(GRAPHdistance(G,i,j)<min){
                            min=GRAPHdistance(G,i,j);
                            e.v=i;
                            e.w=j;
                            e.wt=min;
                        }
                    }
                }
            }
        }
        printf("\tAggiunto arco da %s a %s di peso %d\n",GRAPHgetV(G,e.v),GRAPHgetV(G,e.w),e.wt);
        GRAPHaddE(G,GRAPHgetV(G,e.v),GRAPHgetV(G,e.w),e.wt);
    }
    printf("\n");
}

