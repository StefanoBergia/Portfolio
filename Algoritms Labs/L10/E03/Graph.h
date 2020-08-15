#ifndef E03_GRAPH_H
#define E03_GRAPH_H

#include <stdio.h>
#include "ST.h"
#include "Item.h"

typedef struct graph * Graph;

Graph GRAPHinit(int V);
int GRAPHaddV(Graph G,Item item);
void GRAPHaddE(Graph G, char * k1, char * k2, int wt);
void GRAPHshowAllV(Graph G);
void GRAPHshowV(Graph G, char* k);
void GeneraMatrice(Graph G);
void MostraMatrice(Graph G);
int Get_flusso(Graph G,char tipo);

void printAdj(Graph G);

#endif
