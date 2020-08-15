#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define LEN 100

char* split(char * str,char del,int * index);

int main(int argc, char ** argv) {
    char str[LEN +1];
    char * name,*args[10+1];
    char realname[LEN+1];
    int index=0,i=0;
    FILE * fp;
    fp=fopen(argv[1],"r");
    while(fgets(str,LEN,fp)!=NULL){
        index=0;
        i=0;
        strcpy(realname,"/bin/");
        name=split(str,' ',&index);
        strcat(realname,name);
        args[i]=name;
        i++;
        printf("%s ",args[i]);
        while(index!=-1 && i<10){
            args[i]=split(str,' ',&index);
            printf("%s ",args[i]);
            i++;
        }
        args[i]=(char *) 0;
        if(!fork()){
            //printf("%s %s %d\n",str, realname,index);
            execv (realname,args);
        }else
            sleep(3);
    }
    fclose(fp);
    return 0;
}

char* split(char * str,char del,int * index){
    int i=0,ir;
    char * ret=malloc(LEN+1);
    for(i=(*index),ir=0;str[i]!='\0' &&  str[i]!=del && str[i]!='\n';i++,ir++){
        ret[ir]=str[i];
    }
    ret[ir]='\0';
    if(str[i]=='\0')
        (*index) -1;
    i++;
    (*index)=i;
    return ret;
}