#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void sort(int * vet,int n);
int * joinvet(int * vet1,int *vet2,int n1,int n2);

typedef struct{
    char *in;
    int * vet;
    int n;
    int id;
} data;

void *tF(void *ptr){
    FILE * fpin;
    data * file=(data *)ptr;
    int n,i;
    int * vet;

    printf("Thread %d in esecuzione\n",file->id);

    fpin=fopen(file->in,"r");
    fscanf(fpin,"%d",&n);

    //printf("Thread %d lunghezza file %d\n",file->id,n);

    vet=(int *)malloc(n*sizeof(int));

    for(i=0;i<n;i++)
        fscanf(fpin,"%d",&vet[i]);
    sort(vet,n);
    file->vet=vet;
    file->n=n;
    fclose(fpin);
    printf("Thread %d concluso\n",file->id);
    pthread_exit(NULL);
}

int main(int argc, char ** argv) {
    int n,i=0,ntot=0;
    data * datithread;
    char * token;
    void * status=NULL;
    int * vet,*sup;
    FILE * fout;
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

    for(i=0;i<n;i++){
        datithread[i].id=i;
        if(pthread_create(&threads[i],NULL,tF,(void *) &datithread[i])!=0){
            printf("Errore creazione thread\n");
            return -1;
        }
    }
    pthread_join(threads[0],&status);
    ntot=datithread[0].n;
    vet=(int *)malloc(ntot*sizeof(int));
    for(i=0;i<ntot;i++)
        vet[i]=datithread[0].vet[i];

    for(i=1;i<n;i++){
        pthread_join(threads[i],&status);
        sup=vet;
        vet=joinvet(sup,datithread[i].vet,ntot,datithread[i].n);
        ntot+=datithread[i].n;
        free(sup);
        free(datithread[i].vet);
    }
    fout=fopen(argv[3],"w");
    for(i=0;i<ntot;i++)
        fprintf(fout,"%d\n",vet[i]);
    fclose(fout);
    free(threads);
    free(datithread);
    free(vet);
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

int * joinvet(int * vet1,int *vet2,int n1,int n2){
    int n=n1+n2;
    int i=0,i1=0,i2=0;
    int * vet=(int *) malloc(n*sizeof(int));
    for(i=0,i1=0,i2=0;i<n;i++){
        if(i1<n1 && i2<n2 && vet1[i1]<=vet2[i2]) {
            vet[i] = vet1[i1];
            i1++;
        }else{
            vet[i]=vet2[i2];
            i2++;
        }
    }
    return vet;
}