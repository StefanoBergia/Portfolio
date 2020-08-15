#include <stdio.h>
#include <limits.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct{
    int id;
    int id_fam;
    unsigned long alberi;
}Koala;

typedef struct{
    int id;
    int nKoala;
    int * alleanze;
}Famiglia;

Koala * leggiHabitat(FILE *fp, int * nKoala,int * nAlberi);
Famiglia * leggiFamiglie(FILE * fp,Koala * koala, int *nFamiglie);
void leggiNemici(FILE * fp,Famiglia * famiglie);
int checkNemici(int * sol,int idAlbero,int m,Koala * koala, Koala * k,Famiglia *famiglie);
int checkAlbero(int idAlbero,Koala *k);
int perm(Koala *val,Famiglia * famiglie,int *sol,int * mark,int nKoala,int saltaAlberi,int T,int m,int a,int * ab );
unsigned long pow( unsigned long x,int y);

int main(int argc, char ** argv) {
    FILE * fp;
    Koala * koala;
    Famiglia * famiglie;
    int N,T,S,m,i,j;
    int * sol,* indici_alberi,*mark;
    fp=fopen(argv[1],"r");
    koala=leggiHabitat(fp,&N,&T);
    fclose(fp);
    fp=fopen(argv[2],"r");
    famiglie=leggiFamiglie(fp,koala,&S);
    fclose(fp);
    fopen(argv[3],"r");
    leggiNemici(fp,famiglie);
    fclose(fp);
    m=atoi(argv[4]);

    sol=(int*)malloc(m*T*sizeof(int));
    mark=(int *)malloc(m*T*sizeof(int));
    for(i=0;i<m*T;i++) {
        sol[i] = -1;
        mark[i]=0;
    }
    indici_alberi=(int *)malloc(T*sizeof(int));
    for(i=0;i<T;i++)
        indici_alberi[i]=0;

    printf("SOLUZIONE CHE NON CONSIDERA I VINCOLI SUGLI ALBERI:\n");
    if(perm(koala,famiglie,sol,mark,N,1,T,m,0,indici_alberi)){
        for(i=0;i<T;i++){
            printf("\nalbero %d\n\n",i);
            for(j=0;j<m;j++){
                if(sol[i*m+j]!=-1)
                    printf("koala %d\tfamiglia %d\n",koala[sol[i*m+j]].id,koala[sol[i*m+j]].id_fam);
            }
            printf("\n\n");
        }
    }
    else
        printf("non esiste nessuna disposizione di koala che permetta la pace\n");

    for(i=0;i<m*T;i++) {
        sol[i] = -1;
        mark[i]=0;
    }
    for(i=0;i<T;i++)
        indici_alberi[i]=0;

    printf("SOLUZIONE CHE CONSIDERA I VINCOLI SUGLI ALBERI:\n");
    if(perm(koala,famiglie,sol,mark,N,0,T,m,0,indici_alberi)){
        for(i=0;i<T;i++){
            printf("\nalbero %d\n\n",i);
            for(j=0;j<m;j++){
                if(sol[i*m+j]!=-1)
                    printf("koala %d\tfamiglia %d\n",koala[sol[i*m+j]].id,koala[sol[i*m+j]].id_fam);
            }
            printf("\n\n");
        }
    }
    else
        printf("non esiste nessuna disposizione di koala che permetta la pace");

    free(sol);
    free(mark);
    free(indici_alberi);
    free(koala);
    for(i=0;i<S;i++)
        free(famiglie[i].alleanze);
    free(famiglie);

    return 0;
}

Koala * leggiHabitat(FILE *fp, int * nKoala,int * nAlberi){
    int i,max=INT_MIN,j,nA,A;
    Koala * koala;
    fscanf(fp,"%d",nKoala);
    koala=(Koala *)malloc(*nKoala*sizeof(Koala));
    for(i=0;i<*nKoala;i++){
        koala[i].id=i;
        koala[i].id_fam=-1;
        koala[i].alberi=0;
        fscanf(fp,"%d",&nA);
        for(j=0;j<nA;j++){
            fscanf(fp,"%d",&A);
            if(A>max)
                max=A;
            koala[i].alberi|=pow(2,A);
        }
    }
    *nAlberi=max+1;
    return koala;
}

Famiglia * leggiFamiglie(FILE * fp,Koala * koala,int *nFamiglie){
    int i,j,idK;
    Famiglia * famiglie;
    fscanf(fp,"%d",nFamiglie);
    famiglie=(Famiglia *)malloc(*nFamiglie*sizeof(Famiglia));
    for(i=0;i<*nFamiglie;i++){
        famiglie[i].id=i;
        fscanf(fp,"%d",&famiglie[i].nKoala);
        famiglie[i].alleanze=(int *)malloc(*nFamiglie*sizeof(int));
        for(j=0;j<*nFamiglie;j++)
            famiglie[i].alleanze[j]=1;
        for(j=0;j<famiglie[i].nKoala;j++){
            fscanf(fp,"%d",&idK);
            koala[idK].id_fam=i;
        }
    }
    return famiglie;
}

void leggiNemici(FILE * fp,Famiglia * famiglie){
    int i,j;
    while(fscanf(fp,"%d %d",&i,&j)==2){
        famiglie[i].alleanze[j]=0;
        famiglie[j].alleanze[i]=0;
    }
}

int perm(Koala *val,Famiglia * famiglie,int *sol,int * mark,int nKoala,int saltaAlberi,int T,int m,int a,int * ab  ){
    int i;
    if(a>=T)
        return 0;
    for(i=0;i<nKoala;i++){
        if(mark[i]==0){
            if(ab[a]<m && (saltaAlberi==1 || checkAlbero(a,&val[i])) && checkNemici(sol,a,m,val,&val[i],famiglie))
            {
                sol[a*m+ab[a]]=val[i].id;
                mark[i]=1;
                ab[a]++;
                if (perm(val,famiglie,sol,mark,nKoala,saltaAlberi,T,m,0,ab))
                    break;
                ab[a]--;
                mark[i]=0;
            }else{
                if(perm(val,famiglie,sol,mark,nKoala,saltaAlberi,T,m,a+1,ab))
                    break;
                else
                    return 0;
            }
        }
    }
    return 1;
}

int checkNemici(int * sol,int idAlbero,int m,Koala * koala, Koala * k,Famiglia *famiglie){
    int i,fam,s;
    fam=k->id_fam;
    for(i=0;i<m && sol[idAlbero*m+i]!=-1;i++)
        if(famiglie[koala[sol[idAlbero*m+i]].id_fam].alleanze[fam]==0)
            return 0;
    return 1;
}

int checkAlbero(int idAlbero,Koala *k){
    return k->alberi&pow(2,idAlbero);
}

unsigned long pow( unsigned long x,int y){
    int i;
    unsigned long s=1;
    for(i=0;i<y;i++)
        s*=x;
    return s;
}