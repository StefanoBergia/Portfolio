#ifndef E01_GRAPH_H
#define E01_GRAPH_H

typedef struct graph * Graph;

Graph GRAPHinit(int V);
int GRAPHaddV(Graph G,char * v);
void GRAPHaddE(Graph G, char * k1, char * k2, int wt);
void GraphRemoveV(Graph G,int id);
void GRAPHshowV(Graph G, int id);
void GRAPHshow(Graph G);
Graph GraphCopy(Graph G);
int * GRAPHspD(Graph G,int v);
int GRAPHdistance(Graph G,int v1,int v2);
Graph GRAPHread(FILE * fp);
void GRAPHdistances(Graph G);
void GRAPHprintDistances(Graph G);
int * GRAPHcc(Graph G);
int GRAPHcycle(Graph G);
void GRAPHfree(Graph G);
char * GRAPHgetNode(Graph G,int id);
int GRAPHnV(Graph G);
char * GRAPHgetV(Graph G,int id);

#endif
