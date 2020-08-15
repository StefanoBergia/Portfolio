#ifndef E01_EDGE_H
#define E01_EDGE_H

typedef struct edge{
    int v;
    int w;
    int wt;
}Edge;

Edge EDGECreate(int v,int w,int wt);

#endif
