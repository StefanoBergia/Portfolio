#include <malloc.h>
#include <memory.h>
#include "BST.h"
#include "Utente.h"

typedef struct BSTnode * link;
struct BSTnode{
    Item * item;
    link  r;
    link l;
    int N;
};

struct binarysearchtree {
    link  root;
    link z;
    int N;
};

link NEW(Item * item,link r ,link l,int N){
    link x=malloc(sizeof(*x));
    x->item=item;
    x->r=r;
    x->l=l;
    x->N=N;
}

BST BSTinit(){
    BST bst =malloc(sizeof(*bst));
    bst->N=0;
    bst->root=(bst->z=NEW(ItemSetVoid(),NULL, NULL,0));
    return  bst;
}

link insertR(link h,Item * x,link z){
    if(h==z)
        return NEW(x,z,z,1);
    if(strcmp(x->cardID,h->item->cardID)<0)
        h->l=insertR(h->l,x,z);
    else
        h->r=insertR(h->r,x,z);
    h->N++;
    return h;
}

void BSTinsert(BST bst,Item *  x){
    bst->root=insertR(bst->root,x,bst->z);
    bst->N++;
}

void BST_printR(link node,link z){
    if(node!=z){
        ITEMprint(node->item);
        BST_printR(node->l,z);
        BST_printR(node->r,z);
    }
}

void BST_print(BST bst){
    BST_printR(bst->root,bst->z);
}

Item * searchR(link h,char * k, link z){
    if(h==z)
        return NULL;
    if(strcmp(k,h->item->cardID)==0)
        return h->item;
    if(strcmp(k,h->item->cardID)<0)
        return searchR(h->l,k,z);
    else
        return searchR(h->r,k,z);
}

Item * BST_search(BST bst, char * key){
    return searchR(bst->root,key,bst->z);
}