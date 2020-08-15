#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pthread.h"
#include "semaphore.h"
#include <sys/timeb.h>
#define GROUP 3

typedef struct{
    float c;
    float x;
    int n;
}monomio;

monomio monomi[GROUP];
float   res[GROUP];
sem_t  sem[GROUP];
sem_t  sem4;
FILE * fp;
int offset;


float exp(float b,int e){

    float ret=1;
    int i;
    for(i=0;i<e;i++)
        ret*=b;
    return ret;
}

void * LeggiMonomio(void * par){
    int * n=(int *)par;
    int fine=0;

    while(!fine){
        sem_wait(&sem[*n]);
        fseek(fp,offset+(*n)*sizeof(monomio),SEEK_SET);
        if (fread(&monomi[*n],sizeof(monomio),1,fp)>0) {
            res[*n] = monomi[*n].c * exp(monomi[*n].x, monomi[*n].n);
            fprintf(stdout, "Thread %d-> monomio[%f %f %d]->calcolo %f\n", *n,monomi[*n].c,monomi[*n].x,monomi[*n].n,res[*n]);
        } else {
            res[*n] = 0;
            fine=1;
        }
        sem_post(&sem4);
    }

}

void * SommaMonomi(void* par){
    int fine=0;
    float tot=0;
    int i;
    while(!fine){
        for(i=0;i<GROUP;i++)
            sem_wait(&sem4);
        tot=0;
        for(i=0;i<GROUP;i++)
            tot+=res[i];
        if(tot!=0) {
            fprintf(stdout, "THREAD SOMMATORE----->%f\n", tot);
            offset+=sizeof(monomio)*GROUP;
            for (i = 0; i < GROUP; i++)
                sem_post(&sem[i]);
        } else
            fine=1;

    }
}


int main(int argc, char ** argv) {

    int indexes[GROUP];
    int i;

    offset=0;
    fp=fopen(argv[1],"rb");
    if(fp!=NULL) {
        pthread_t t[GROUP];
        pthread_t t4;
        sem_init(&sem4, 0, 0);

        for (i = 0; i < GROUP; i++) {
            indexes[i] = i;
            sem_init(&sem[i], 0, 1);
            pthread_create(&t[i], NULL, LeggiMonomio, &indexes[i]);
        }
        pthread_create(&t4, NULL, SommaMonomi, NULL);

        for (i = 0; i < GROUP; i++)
            pthread_join(t[i], NULL);

        for (i = 0; i < GROUP; i++)
            sem_destroy(&sem[i]);

        fclose(fp);
        sem_destroy(&sem4);
    }

    return 0;
}