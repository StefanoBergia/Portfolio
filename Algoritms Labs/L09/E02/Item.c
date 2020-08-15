#include "Item.h"
#include <malloc.h>
#include <memory.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


Item_p ItemNew(){
    Item_p  new=ItemSetVoid();
    new->void_flag=0;
    return  new;
}

void ItemFree(Item_p item){
    free(item);
}

Item_p ItemSetVoid(){
    Item_p new=malloc(sizeof(*new));
    new->nome[0]='\0';
    new->punti=0;
    new->void_flag=1;
}

int ItemCheckVoid(Item_p item){
    return item->void_flag;
}

int ItemGetPunti(Item_p item){
    return item->punti;
}

char * ItemGetNome(Item_p item){
    char *ret=malloc(11*sizeof(char));
    strcpy(ret,item->nome);
    return  ret;
}

void ItemSetPunti(Item_p item,int pt){
    item->punti=pt;
}

void ItemSetNome(Item_p item, char * nome){
    strcpy(item->nome,nome);
}

Item_p  IteamScan(FILE * fp){
    Item_p new=ItemSetVoid();
    if(fp!=NULL && !feof(fp)) {
        if(fscanf(fp,"%s %d",new->nome,&(new->punti))==2){
            new->void_flag=0;
        }
    }
    return new;
}

void ItemPrint(Item_p item,FILE * fp){
    if(fp!=NULL)
        fprintf(fp,"%s %d\n",item->nome,item->punti);
}

Item_p ItemMatch(Item_p item1,Item_p item2){
    int pt;
    srand((unsigned int)time(NULL));
    if(rand() < RAND_MAX/2){
        pt=ceil(item2->punti*0.25);
        item1->punti+=pt;
        item2->punti-=pt;
        return item1;
    }else{
        pt=ceil(item1->punti*0.25);
        item1->punti-=pt;
        item2->punti+=pt;
        return item2;
    }
}

int ITEMless(Item i1,Item i2){
    return i1.punti<i2.punti;
}

int ITEMGreater(Item i1,Item i2){
    return i1.punti>i2.punti;
}