#include "Item.h"

Item_p ItemNew(){
    return ItemSetVoid();
}

void ItemFree(Item_p item){
    free(item);
}

Key KeyGet(Item_p item){
    return  item->nome;
}

int KeyCompare(Key a, Key b){
    return strcmp(a,b);
}
int ItemCompare(Item_p a, Item_p b){
    return KeyCompare(KeyGet(a),KeyGet(b));
}

Item_p Itemscan(FILE * fp){
    Item_p new=ItemSetVoid();
    if(fp!=NULL && !feof(fp))
        fscanf(fp,"%s %d %d %d",new->nome,&(new->val),&(new->sx),&(new->dx));
    return new;
}

void ItemShow(Item_p item,FILE * fp){
    fprintf(fp,"%s %d %d %d",item->nome,item->val,item->sx,item->dx);
}

Item_p ItemSetVoid(){
    Item_p ret=(Item_p)malloc(sizeof(Item));
    ret->nome[0]='\0';
    ret->val=-1;
}

int ItemCheckVoid(Item_p item){
    if(item->nome[0]=='\0' || item->val==-1)
        return 1;
    return 0;
}

int GetVal(Item_p item){
    return item->val;
}
void ItemSetVal(Item_p item,int val ){
    item->val=val;
}
void ItemSetKey(Item_p item_p, Key key){
    strcpy(item_p->nome,key);
}

int ItemGetDx(Item_p item){
    return item->dx;
}

int ItemGetSx(Item_p item){
    return  item->sx;
}

void  ItemSetDx(Item_p item, int v){
    item->dx=v;
}
void  ItemSetSx(Item_p item, int v){
    item->sx=v;
}