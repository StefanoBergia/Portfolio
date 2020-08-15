#include "BST.h"

typedef struct BSTnode * link;
link NEW(Item_p,link ,link );
link BSTreadPreOrderR(BST,FILE * );
void BSTwritePreOrderR(BST,link,int,FILE * );
void BSTFreeLinkR(BST,link);
int BSTcountR(BST,link,int,int,int);
int BSTmarkPath(BST,link,Key);
int BSTcountFlag(BST,link);
void BSTmirrorR(BST,link);


struct BSTnode{
    Item_p data;
    link l;
    link r;

    int flag;
};

struct binarysearchtree{
    link root;
    link z;
};

link NEW(Item_p item,link l,link r){
    link new=malloc(sizeof(*new));
    new->data=item;
    new->l=l;
    new->r=r;
    new->flag=0;
    return new;
}

BST BSTinit(){
    BST bst=malloc(sizeof(*bst));
    bst->root=(bst->z=NEW(ItemSetVoid(),NULL,NULL));
    return  bst;
}

BST BSTreadPreorder(FILE * fp){
    BST bst=BSTinit();
    bst->root=BSTreadPreOrderR(bst,fp);
    return bst;
}

link BSTreadPreOrderR(BST bst,FILE * fp){
    link sup=NULL;
    if(!feof(fp)){
        sup=NEW(Itemscan(fp),NULL,NULL);
        if(!ItemCheckVoid(sup->data))
        {
            if(ItemGetSx(sup->data))
                sup->l=BSTreadPreOrderR(bst,fp);
            else
                sup->l=bst->z;
            if(ItemGetDx(sup->data))
                sup->r=BSTreadPreOrderR(bst,fp);
            else
                sup->r=bst->z;
        }
    }
    return sup;
}

void BSTwritePreOrderR(BST bst,link node,int level,FILE * fp ){
    int i;
    if(node!=bst->z){
        for(i=0;i<level;i++)
            fprintf(fp,"\t");
        ItemShow(node->data,fp);
        printf("\n");
        BSTwritePreOrderR(bst,node->l,level+1,fp);
        BSTwritePreOrderR(bst,node->r,level+1,fp);
    }

}

void BSTwritePreorder(BST bst,FILE * fp){
    BSTwritePreOrderR(bst,bst->root,0,fp);
}

int BSTcount(BST bst,int min,int max){
    if(min>max)
        return -1;
    return BSTcountR(bst,bst->root,min,max,0);
}

int BSTcountR(BST bst,link cur,int min,int max,int level){
    int count=0;
    if(cur->l==bst->z || cur->r==bst->z)
        return 0;
    if(level<=max){
        count=BSTcountR(bst,cur->l,min,max,level+1)+BSTcountR(bst,cur->r,min,max,level+1);
        if(level>=min)
            count++;
    }
    return  count;

}

int BSTdistance(BST bst, Key k1,Key k2){
    if( BSTmarkPath(bst,bst->root,k1) && BSTmarkPath(bst,bst->root,k2))
        return BSTcountFlag(bst,bst->root);
    BSTcountFlag(bst,bst->root);
    return -1;
}

int BSTmarkPath(BST bst,link node, Key k){
    int cmp;
    if(node!=bst->z) {
        node->flag = !node->flag;
        cmp = KeyCompare(KeyGet(node->data), k);
        if (cmp == 0)
            return 1;
        else if(cmp>0)
            return BSTmarkPath(bst,node->l,k);
        else
            return BSTmarkPath(bst,node->r,k);
    }
    return 0;
}

int BSTcountFlag(BST bst,link node){
    int c=0;
    if(node!=bst->z){
        c=BSTcountFlag(bst,node->l)+BSTcountFlag(bst,node->r);
        c+=node->flag;
        if(node->flag)
            node->flag=0;
        return c;
    }
    return 0;
}

void BSTmirror(BST bst){
    BSTmirrorR(bst,bst->root);
}

void BSTmirrorR(BST bst,link node){
    link sup;
    int fsup;
    if(node!=bst->z){
        sup=node->l;
        node->l=node->r;
        node->r=sup;
        fsup=ItemGetDx(node->data);
        ItemSetDx(node->data,ItemGetSx(node->data));
        ItemSetSx(node->data,fsup);
        BSTmirrorR(bst,node->r);
        BSTmirrorR(bst,node->l);
    }
    return ;
}

void BSTfree(BST bst){
    BSTFreeLinkR(bst,bst->root);
    ItemFree(bst->z->data);
    free(bst->z);
    free(bst);
}

void BSTFreeLinkR(BST bst,link node){
    if(node!=bst->z){
        BSTFreeLinkR(bst,node->l);
        BSTFreeLinkR(bst,node->r);
        ItemFree(node->data);
        free(node);
    }
}
