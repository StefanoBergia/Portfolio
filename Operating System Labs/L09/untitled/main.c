#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void recursive(int mono,int * numbers, int * vet , int level,int level2,int m, int n);
void algoritmo(int * vet,int n);

int main(int argc, char ** argv) {
    int * numbers;
    int * vet;

    int i=0,mono;
    int n=atoi(argv[1]);
    int m=atoi(argv[2]);


    numbers=(int*)malloc(m+1*sizeof(int));
    vet=(int*)malloc(n*sizeof(int));

    for(i=0;i<n;i++){
        vet[i]=0;
    }

    for(i=0;i<m;i++){
        numbers[i]=0;
    }

    for(i=0;i<m;i++){
        mono=i+1;
        numbers[i+1]=1;
        recursive(mono,numbers,vet,0,1,m,n);
        numbers[i+1]=0;
    }


    return 0;
}

void recursive(int mono,int * numbers, int * vet , int level,int level2, int m, int n){
    int i=0;
    int * google;
    if(level>=n){
        printf("vettore: ");
        google=(int *)malloc((3*n+1)*sizeof(int));
        for(i=0;i<n;i++){
            google[3*i]=vet[i];
            google[3*i+1]=vet[i];
            google[3*i+2]=vet[i];
            printf("%d %d %d ",vet[i],vet[i],vet[i]);
        }
        google[3*n]=mono;
        printf("%d ====>",mono);
        algoritmo(google,3*n+1);
    }else{
        for(i=level2;i<m;i++){
            if(numbers[i]==0){
                numbers[i]=1;
                vet[level]=i;
                recursive(mono,numbers,vet,level+1,i+1,m,n);
                numbers[i]=0;
            }
        }
    }
}

void algoritmo(int * vet,int n){
    int sum=0;
    int suppsum=0;
    int i=0;
    for(i=0;i<n;i++)
        sum+=vet[i];
    for(i=0;i<n;i++){
        suppsum=sum-vet[i];
        if(suppsum%3==0){
            if(suppsum%9==0) {
                /*printf("numero unico = %d", vet[i]);
                if (i != n - 1) {
                    printf(" ERRORE!!!!\n");
                } else*/
                    printf("\n");
                return;
            }else{
                printf("numero unico = %d \n", vet[i]);
                return;
            }

        }

    }

    printf("\n");


}