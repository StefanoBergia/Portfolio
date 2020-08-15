#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define MAXC 25

typedef struct{
    char nome[MAXC];
    float costo;
}prodotto;


int comb(int pos,prodotto *val,prodotto *sol,int n,int k,int b,int start,int count,FILE *fp);

int main(int argc, char ** argv) {
    FILE * fp;
    prodotto * prodotti,*sol ;
    int n,i,count=0,k,b;
    if(argc==5){
        k=atoi(argv[3]);
        b=atoi(argv[4]);
        fp=fopen(argv[1],"r");
        fscanf(fp,"%d",&n);
        prodotti=(prodotto *)malloc(n*sizeof(prodotto));                    //alloco un vettore per contenre i prodotti
        sol=(prodotto *)malloc(n*sizeof(prodotto));                         //alloco un vettore per contenere la soluzione (sovradimentionato rispetto a k per contenere tutte le soluzioni)
        for(i=0;i<n;i++){
            fscanf(fp,"%s %f",prodotti[i].nome,&(prodotti[i].costo));
        }
        fclose(fp);
        fp=fopen(argv[2],"w");
        count=comb(0,prodotti,sol,n,k,b,0,0,fp);
        printf("%d combinazioni trovate",count);
        fclose(fp);
        free(prodotti);
    }
    return 0;
}

int comb(int pos,prodotto *val,prodotto *sol,int n,int k,int b,int start,int count,FILE *fp){   //combinazioni di n elementi a gruppi di n con condizione di terminazione per pos>k e per somma dei costi < b
    int i,flag=0;
    float sum;
    if(pos>=k && pos<n){
        for(i=0,sum=0;i<pos;i++)
            sum+=sol[i].costo;
        if(sum<=b){
            fprintf(fp," %.1f\t",sum);
            for(i=0;i<pos;i++)
                fprintf(fp,"%s:%.1f\t\t",sol[i].nome,sol[i].costo);
            fprintf(fp,"\n");
            count ++;
        }
        else
            flag=1;
    }
    for(i=start;i<n && flag==0;i++){
        sol[pos]=val[i];
        count=comb(pos+1,val,sol,n,k,b,i+1,count,fp);
    }

    return count;
}