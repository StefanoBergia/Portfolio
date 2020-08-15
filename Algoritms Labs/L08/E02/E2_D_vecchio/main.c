#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int * calcola_scambi(int * sequenza,int n);
int sumScambi(int * sol,int * sequenza,int n);
void generaSol(int * cursol,int * splitter, int n);
int verificaSol(int * sequenza, int l);
void printSequenza(int * seq ,int n);


int main(int argc, char ** argv){
    int * sequenza,*sol;
    int i,n;
    //n=argv[1][0]-'0';
    n=atoi(argv[1]);
    sequenza=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        sequenza[i] = argv[2][i] - '0';
    sol=calcola_scambi(sequenza,n);

    printf("\n");
    if(sol==NULL)
        printf("nessuno scambio necessario");
    else {

        printf("insieme minimo degli scambi:{ ");
        for (i = 0; i < n; i++) {
            if (sol[i] != sequenza[i])
                printf("%d ", i);
        }
        printf("}\n");
    }


    return 0;
}

int * calcola_scambi(int * sequenza, int n){
    int n_scontri,min_scambi,* curSol,*bestSol,i,j,k,*splitter,*bestsplitter,*suppsplitter,sum,sup;

    bestSol=(int *)malloc(n*sizeof(int));
    curSol=(int *)malloc(n*sizeof(int));
    splitter=(int *)malloc((n/2+1)*sizeof(int));
    bestsplitter=(int *)malloc((n/2+1)*sizeof(int));
    suppsplitter=(int *)malloc((n/2+1)*sizeof(int));
    splitter[0]=0;
    splitter[n/2]=n;

    if(verificaSol(sequenza,n))
        return NULL;

    for(i=0;i<n;i++) {
        bestSol[i] = i % 2;
        curSol[i]=bestSol[i];
    }

    for(i=1;i<n/2;i++) {
        splitter[i] = 2 * i;
        bestsplitter[i]=splitter[i];
    }

    min_scambi=sumScambi(bestSol,sequenza,n);

    printf("\n\n");
    printSequenza(bestSol,n);
    printf(" numero scambi:%d\n",min_scambi);

    for(n_scontri=n/2;n_scontri>0;n_scontri--){
        for(i=1;i<=n_scontri;i++){

            sup=splitter[i];
            for(k=i;k<n && splitter[k]==sup;k++)
                splitter[k]=splitter[i-1];


            generaSol(curSol,splitter,n);
            sum=sumScambi(curSol,sequenza,n);

            /*printSequenza(curSol,n);
            printf(" numero scambi:%d\n",sum);*/

            if(sum<=min_scambi){
                min_scambi=sum;
                for(j=0;j<n;j++)
                    bestSol[j]=curSol[j];
                for(j=1;j<=n/2;j++)
                    suppsplitter[j]=splitter[j];
            }
            splitter[i]=bestsplitter[i];
        }
        for(j=1;j<=n/2;j++) {
            bestsplitter[j] = suppsplitter[j];
            splitter[j]=suppsplitter[j];
        }

        printf("\n\n");
        printSequenza(bestSol,n);
        printf(" numero scambi:%d\n",min_scambi);
    }

    return bestSol;
}

int sumScambi(int * sol,int * sequenza,int n){
    int sum,i;
    for(i=0,sum=0;i<n;i++)
        if(sol[i]!=sequenza[i])
            sum++;
    return sum;
}

void generaSol(int * cursol,int * splitter, int n){


    int l,r,i,j,split;

    for(i=0;i<=n/2;i++)
        printf("%d ",splitter[i]);

    for(i=0;i<n/2;i++){
        if(splitter[i]!=splitter[i+1]){
            l=splitter[i];
            r=splitter[i+1];
            split=(r+l)/2;

            for(j=l;j<r;j++){
                if(j<split)
                    cursol[j]=0;
                else
                    cursol[j]=1;
            }
        }
    }
    printSequenza(cursol,n);
    printf("\n");
}

void printSequenza(int * seq ,int n){
    int i;
    for(i=0;i<n;i++){
        if(i%2==0)
            printf(" ");
        if(seq[i]==0)
            printf(">");
        else
            printf("<");
    }
}

int verificaSol(int * sequenza, int l){
    int i;
    int sum[]={0, 0};

    sum[sequenza[0]]++;
    for(i=1;i<l;i++){
        if(sequenza[i-1]==1 && sequenza[i]==0)
        {
            if(sum[0]!=0) {
                if (sum[0] != sum[1])
                    return 0;
            }
            sum[0] = 0;
            sum[1] = 0;
        }
        sum[sequenza[i]]++;
    }
    if(sum[0]!=sum[1])
        return 0;
    return 1;
}