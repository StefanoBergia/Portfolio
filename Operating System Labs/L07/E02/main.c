#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void sort(int * vet,int n);

typedef struct{
    char *in;
    char * out;
    int id;
} data;

void *tF(void *ptr){
    FILE * fpin,*fpout;
    data * file=(data *)ptr;
    int n,i;
    int * vet;
    //printf("Thread %d  in:%s out%s\n",file->id,file->in,file->out);

    printf("Thread %d in esecuzione\n",file->id);

    fpin=fopen(file->in,"r");
    fpout=fopen(file->out,"w");
    fscanf(fpin,"%d",&n);

    //printf("Thread %d lunghezza file %d\n",file->id,n);

    vet=(int *)malloc(n*sizeof(int));

    for(i=0;i<n;i++)
        fscanf(fpin,"%d",&vet[i]);
    sort(vet,n);
    for(i=0;i<n;i++)
        fprintf(fpout,"%d\n",vet[i]);
    fclose(fpin);
    fclose(fpout);
    free(vet);
    printf("Thread %d concluso\n",file->id);
    pthread_exit(NULL);
}

int main(int argc, char ** argv) {
    int n,i=0;
    data * datithread;
    char * token;
    void * status=NULL;
    pthread_t * threads;

    printf("Inizio programma\n");

    n=atoi(argv[1]);
    datithread=(data *) malloc(n*sizeof(data));
    threads=(pthread_t *)malloc(n*sizeof(pthread_t));

    token=strtok(argv[2],",");
    while (token != NULL)
    {
        datithread[i].in=token;
        token = strtok(NULL, ",");
        i++;
    }
    i=0;
    token=strtok(argv[3],",");
    while (token != NULL)
    {
        datithread[i].out=token;
        token = strtok(NULL, ",");
        i++;
    }

    for(i=0;i<n;i++){
        datithread[i].id=i;
        if(pthread_create(&threads[i],NULL,tF,(void *) &datithread[i])!=0){
            printf("Errore creazione thread\n");
            return -1;
        }
    }

    for(i=0;i<n;i++){
        pthread_join(threads[i],&status);
    }

    free(threads);
    free(datithread);
    printf("Fine programma\n");

    return 0;
}

void sort(int * vet,int n){
    int i,j,supp;
    int min;
    for(i=0;i<n;i++){
        min=i;
        for(j=i+1;j<n;j++){
            if(vet[j]<vet[min])
                min=j;
        }
        supp=vet[i];
        vet[i]=vet[min];
        vet[min]=supp;
    }
}