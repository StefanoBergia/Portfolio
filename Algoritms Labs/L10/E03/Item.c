#include <memory.h>
#include <stdio.h>
#include "Item.h"



Item NEW(char * idElab, char * idRete){
    Item ret;
    strcpy(ret.id_elab,idElab);
    strcpy(ret.id_rete,idRete);
    ret.id=0;
    return  ret;
}

Item ITEMSetVoid(){
    Item ret=NEW("","");
    ret.id=-1;
    return ret;
}
int ITEMIsVoid(Item item){
    if(item.id==-1)
        return 1;
    else
        return 0;
}

void ITEMshow(Item item){
    printf("%s %s",item.id_elab,item.id_rete);
}

char * KEYget(Item item){
    return item.id_elab;
}