#include "Edge.h"

Edge EDGECreate(int v,int w,int wt){
    Edge e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}