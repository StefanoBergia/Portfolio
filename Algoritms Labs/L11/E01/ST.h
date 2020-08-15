#ifndef E01_ST_H
#define E01_ST_H

typedef struct symboltable *ST;

ST STinit(int);
void STinsert(ST,char *);
int STcount(ST);
int STempty(ST);
int STsearch(ST st,char * k);
void STdelete(ST,char *);
char * STGet(ST st,int id);
ST STcopy(ST);
int STisEliminated(ST st, int id);

#endif
