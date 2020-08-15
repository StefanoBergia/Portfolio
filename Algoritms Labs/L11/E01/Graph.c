#include <malloc.h>
#include <values.h>
#include "Graph.h"
#include "ST.h"
#include "PQ.h"
#include "Edge.h"
#define MAXC 30

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
    int ** distanze;
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
    G->distanze=NULL;
    if(G->tab==NULL)
        return NULL;
    return G;
}

int GRAPHaddV(Graph G,char * v){
    if(G->V<G->M) {
        G->V++;
        STinsert(G->tab, v);
        return 1;
    }
    return 0;
}

void GRAPHaddE(Graph G, char * k1, char * k2, int wt){
    link supp;
    int i;
    int id1=STsearch(G->tab,k1);
    int id2=STsearch(G->tab,k2);

    G->adj[id1]=NEWlink(id2,wt,G->adj[id1]);
    G->adj[id2]=NEWlink(id1,wt,G->adj[id2]);

    G->E++;
}

void GRAPHshowV(Graph G, int id){
    link supp;
    char * nodo=STGet(G->tab,id);
    if(nodo==NULL)
    {
        printf("nodo non trovato\n");
        return;
    }
    supp=G->adj[id];
    if(supp==G->z) {
        printf("il nodo %s non ha archi", nodo);
        free(nodo);
        return;
    }
    printf("nodi connessi a %s\t==>",nodo);
    free(nodo);
    while(supp!=G->z){
        nodo=STGet(G->tab,supp->v);
        printf("%s:%d",nodo,supp->wt);
        if(supp->next!=G->z)
            printf("\t->\t");
        supp=supp->next;
        free(nodo);
    }
}

void GRAPHshow(Graph G){
    int i;
    for(i=0;i<G->M;i++){
        GRAPHshowV(G,i);
        printf("\n");
    }
}

Graph GRAPHread(FILE * fp){
    Graph  G;
    int n,i,wt;
    char v1[MAXC+1];
    char v2[MAXC+1];
    fscanf(fp,"%d",&n);
    G=GRAPHinit(n);
    for(i=0;i<n;i++){
        fscanf(fp,"%s",v1);
        GRAPHaddV(G,v1);
    }
    while(fscanf(fp,"%s %s %d",v1,v2,&wt)==3)
        GRAPHaddE(G,v1,v2,wt);
    return G;
}

int * GRAPHspD(Graph G,int s){
    int v,w;
    link t;
    PQ pq=PQUEUEinit(G->M);
    int * st,*d;
    if(STGet(G->tab,v)==NULL)
        return NULL;
    st=malloc(G->M*sizeof(int));
    d=malloc(G->M*sizeof(int));

    for(v=0;v<G->V;v++){
        st[v]=-1;
        d[v]=INT_MAX;
        PQUEUEinsert(pq,d,v);
    }
    d[s]=0;
    st[s]=s;
    PQUEUEchange(pq,s,d);
    while(!PQUEUEempty(pq)){
        if(d[v=PQUEUEextractMin(pq,d)]!=INT_MAX){
            for(t=G->adj[v];t!=G->z;t=t->next){
                if(d[v]+t->wt<d[w=t->v]){
                    d[w]=d[v]+t->wt;
                    PQUEUEchange(pq,w,d);
                    st[w]=v;
                }
            }
        }
    }
    free(st);
    return d;
}

void GRAPHdistances(Graph G){
    int i;
    G->distanze=malloc(G->M*sizeof(int));
    for(i=0;i<G->M;i++) {
        G->distanze[i] = GRAPHspD(G, i);
    }
}

int GRAPHdistance(Graph G,int v1,int v2){
    if(G->distanze==NULL)
        GRAPHdistances(G);
    return G->distanze[v1][v2];
}


void GRAPHprintDistances(Graph G){
    int i,j;
    for(i=0;i<G->M;i++){
        printf("%s\t",STGet(G->tab,i));
        for(j=0;j<G->M;j++)
            printf("%d ",G->distanze[i][j]);
        printf("\n");
    }
}

Graph GraphCopy(Graph G){
    int i;
    link sup;
    Graph new=GRAPHinit(G->M);
    new->V=G->V;
    new->E=G->E;
    new->tab=STcopy(G->tab);

    //non alloco una nuova matrice delle distanze, tanto non viene modificata
    new->distanze=G->distanze;

    for(i=0;i<G->M;i++){
        for(sup=G->adj[i];sup!=G->z;sup=sup->next)
            new->adj[i]=NEWlink(sup->v,sup->wt,new->adj[i]);
    }

    return new;
}

int dfsR(Graph G,Edge e,int * time,int * pre){
    link t;
    int w=e.w;
    pre[w]=(*time)++;

   // printf("%s %d\n",STGet(G->tab,w),pre[w]);

    for(t=G->adj[w];t!=G->z;t=t->next){
        if(pre[t->v]==-1) {
            if (dfsR(G, EDGECreate(w, t->v, t->wt), time, pre) > 0)
                return 1;
        }
        else{
            if(pre[w]<pre[t->v])
                return 1;
        }
    }
    return 0;
}

int GRAPHcycle(Graph G){
    int v,i,time=1,*pre,*post,*st;
    pre=malloc(G->M*sizeof(int));
    for(v=0;v<G->M;v++){
        pre[v]=-1;
    }
    for(v=0;v<G->M;v++)
        if(pre[v]==-1) {
            if (dfsR(G, EDGECreate(v, v, 0), &time, pre))
                return 1;
        }
    return 0;
}


void dfsRcc(Graph G,int v,int id,int *cc){
    link t;
    cc[v]=id;
    for(t=G->adj[v];t!=G->z;t=t->next)
        if(cc[t->v]==-1 )
            dfsRcc(G,t->v,id,cc);
}

int * GRAPHcc(Graph G){
    int v, id=0,*cc;
    cc=malloc(G->M*sizeof(int));
    for(v=0;v<G->M;v++)
        cc[v]=-1;
    for(v=0;v<G->M;v++)
        if(!STisEliminated(G->tab,v) && cc[v]==-1)
            dfsRcc(G,v,id++,cc);
    return cc;
}

void GraphRemoveV(Graph G,int id){
    int i;
    link t,s;
    if(STGet(G->tab,id)==NULL)
        return;
    for(i=0;i<G->V;i++) {
        if(i==id){
            t=G->adj[i];
            while(t!=G->z)
            {
                G->adj[i]=t->next;
                free(t);
                t=G->adj[i];
            }

        }
        else
        {
            s=G->adj[i];
            t=G->adj[i]->next;
            while(t!=G->z && t!=NULL){
                if(t->v==id)
                {
                    s->next=t->next;
                    free(t);
                    t=s->next;
                }
                else{
                    s=t;
                    t=t->next;
                }
            }
            if(G->adj[i]->v==id){
                t=G->adj[i];
                G->adj[i]=t->next;
                free(t);
            }
        }
    }
    STdelete(G->tab,STGet(G->tab,id));
}

void GRAPHfree(Graph G){
    int i;
    link t;
    for(i=0;i<G->M;i++){
        t=G->adj[i];
        while(t!=G->z)
        {
            G->adj[i]=t->next;
            free(t);
            t=G->adj[i];
        }
    }
    free(G->adj);
    free(G);
}

char * GRAPHgetNode(Graph G,int id){
    return STGet(G->tab,id);
}

int GRAPHnV(Graph G){
    return G->M;
}

char * GRAPHgetV(Graph G,int id){
    return STGet(G->tab,id);
}