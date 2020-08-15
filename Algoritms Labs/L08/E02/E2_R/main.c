#include <stdio.h>
#include <malloc.h>
#include <values.h>

int verificaSol(int * sequenza,int * sol, int n);
void disp_r (int pos,int * sequenza,int *val,int *sol,int l,int nv,int *min,int * best);


int main(int argc, char **argv) {
    int * sequenza, *best ,*sol;
    int i,n,val[]={0,1};
    n=argv[1][0]-'0';
    sequenza=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++) {
        sequenza[i] = argv[1][i + 1] - '0';
       // printf("%d",sequenza[i]);
    }
    printf("\n");

    best=(int *)malloc(n*sizeof(int));
    sol=(int *)malloc(n*sizeof(int));

    for(i=0;i<n;i++){
        best[i]=0;
        sol[i]=0;
    }

    int min=INT_MAX;
    disp_r(0,sequenza,val,sol,n,2,&min,best);

    printf("insieme minimo degli scambi:{ ");
    for(i=0;i<n;i++)
        if(best[i])
            printf("%d ",i);
    printf("}\n");

    return 0;
}

void disp_r (int pos,int * sequenza,int *val,int *sol,int l,int nv,int *min,int * best){
    int i,c=0;
    if(pos>=l){
        if(verificaSol(sequenza,sol,l)){
            for(i=0;i<l;i++)
                c+=sol[i];
            if(c<*min){
                *min=c;
                for(i=0;i<l;i++)
                    best[i]=sol[i];
            }
        }
        return;
    }
    for(i=0;i<nv;i++){
        sol[pos]=val[i];
        disp_r(pos+1,sequenza,val,sol,l,nv,min,best);
    }
    return;
}

int verificaSol(int * sequenza,int * sol, int l){
    int i;
    int * scambi=(int *)malloc(l*sizeof(int));

    for(i=0;i<l;i++)
        scambi[i]=sequenza[i]^sol[i];

    int sum[]={0, 0};
    sum[scambi[0]]++;
    for(i=1;i<l;i++){
        if(scambi[i-1]==1 && scambi[i]==0)
        {
            if(scambi[0]!=0) {
                if (sum[0] != sum[1]){
                    free(scambi);
                    return 0;
                }

            }
            sum[0] = 0;
            sum[1] = 0;
        }
        sum[scambi[i]]++;
    }
    free(scambi);
    if(sum[0]!=sum[1])
        return 0;
    return 1;
}