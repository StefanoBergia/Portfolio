#ifndef E03_ITEM_H
#define E03_ITEM_H


#define MAXC 30

typedef struct Node Item;

struct Node{
    char id_elab[MAXC+1];
    char id_rete[MAXC+1];
    int id;
};

Item NEW(char *, char *);
Item ITEMSetVoid();
int ITEMIsVoid(Item);
void ITEMshow(Item);
char * KEYget(Item);
#endif //E03_ITEM_H
