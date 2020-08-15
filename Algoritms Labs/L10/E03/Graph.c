#include <malloc.h>
#include <memory.h>
#include "Graph.h"
#define MAXV 100
#define MAX 10

typedef struct node *link;
struct node{
    int v;
    int wt;
    link next;
};

struct graph{
    int V;
    int E;
    int M;
    link *adj;
    ST tab;
    link z;
    int ** mat;
};

link NEWlink(int v,int wt,link next){
    link x=malloc(sizeof(*x));
    x->v=v;
    x->wt=wt;
    x->next=next;
    return x;
}

Graph GRAPHinit(int V){
    int v;
    Graph G=malloc(sizeof(*G));
    G->M=V;
    G->V=0;
    G->E=0;
    G->z=NEWlink(-1,-1,NULL);
    G->adj=malloc(G->M*sizeof(link));
    for(v=0;v<G->M;v++)
        G->adj[v]=G->z;
    G->tab=STinit(V);
    if(G->tab==NULL)
        return NULL;
    return G;
}


int GRAPHaddV(Graph G,Item item){
    if(G->V<G->M) {
        item.id = G->V;
        G->V++;
        STinsert(G->tab, item);
        return 1;
    }
    return 0;
}

void GRAPHaddE(Graph G, char * k1, char * k2, int wt){
    link supp;
    int i;
    Item item1=STsearch(G->tab,k1);
    Item item2=STsearch(G->tab,k2);
    supp=G->adj[item1.id];

    if(supp==G->z)
        G->adj[item1.id]=NEWlink(item2.id,wt,G->z);
    else {
        while (supp->next != G->z)
            supp = supp->next;
        supp->next=NEWlink(item2.id,wt,G->z);
    }

    supp=G->adj[item2.id];
    if(supp==G->z)
        G->adj[item2.id]=NEWlink(item1.id,wt,G->z);
    else {
        while (supp->next != G->z)
            supp = supp->next;
        supp->next=NEWlink(item1.id,wt,G->z);
    }

    G->E++;
}

void GRAPHshowAllV(Graph G){
    STdisplay(G->tab);
}

void GRAPHshowV(Graph G, char* k){
    link supp;
    Item nodo;
    int count=0;
    Item item=STsearch(G->tab,k);
    if(ITEMIsVoid(item))
    {
        printf("nodo non trovato\n");
        return;
    }
    supp=G->adj[item.id];
    if(supp==G->z) {
        printf("il nodo %s non ha archi", k);
        return;
    }
    printf("nodi connessi a %s:\n",k);
    while(supp!=G->z){
        nodo=STGet(G->tab,supp->v);
        printf("nodo:%s\n",nodo.id_elab);
        supp=supp->next;
        count++;
    }

    printf("il numero totale di archi è %d",count);

}

void GeneraMatrice(Graph G){
    int i;
    link sup;
    G->mat=malloc(G->M*sizeof(int *));
    for(i=0;i<G->M;i++)
        G->mat[i]=calloc(G->M,sizeof(int));
    for(i=0;i<G->M;i++){
        sup=G->adj[i];
        while(sup!=G->z){
            G->mat[i][sup->v]=sup->wt;
            sup=sup->next;
        }
    }
}

void MostraMatrice(Graph G){
    int i,j;
    for(i=0;i<G->M;i++){
        printf("%s\t",STGet(G->tab,i).id_elab);
        for(j=0;j<G->M;j++)
            printf("%d ",G->mat[i][j]);
        printf("\n");
    }
}

int Get_flusso(Graph G,char tipo){
    int i,j,count=0;
    GeneraMatrice(G);
    for(i=0;i<G->M;i++){
        for(j=0;j<G->M;j++){
            if(strcmp(STGet(G->tab,i).id_rete,STGet(G->tab,j).id_rete)==0) {
                if (tipo == 'I')
                    count+= G->mat[i][j];
            }
            else{
                if(tipo=='E')
                    count+=G->mat[i][j];
            }
        }
    }
    return count/2;
}

void printAdj(Graph G){
    int i;
    link supp;
    for(i=0;i<G->M;i++){
        printf("%s\t",STGet(G->tab,i).id_elab);
        supp=G->adj[i];
        while(supp!=G->z)
        {
            printf("v:%d wt:%d->",supp->v,supp->wt);
            supp=supp->next;
        }
        printf("\n");
    }
}