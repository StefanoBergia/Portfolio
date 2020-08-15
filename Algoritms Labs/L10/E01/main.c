
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <values.h>

typedef struct{
    int r;  //raggio
    int a;  //attacco
    int d;  //difesa
    int c;  //costo
}risorsa;

typedef struct{
    int flag_tipo;  //0 vuoto, 1 alleato, 2 nemico, 3 risorsa
    int v;          //valore
    int supp;       //valore di supporto per il controllo
    risorsa * link;  //collegamento alla risorsa posizionata
}target;

target ** leggi_target(FILE *fp,int R, int C,int tipo);
risorsa * leggi_risorse(FILE * fp,int * N);
int check_resources(target ** m,int  R,int C,int tipo);
void popola_quadrato(target ** m, int R, int C, int i,int j,int r, int v);
void disp_r(int x,int y,target ** a, target ** d, risorsa * res,int N,int R, int C,int money,int* best_money,target ** best_a, target ** best_d);
void print_sol(target ** a, target ** d, risorsa * res,int N,int R, int C);


int main(int argc, char ** argv) {
    target **a,**d,**best_a,**best_d;
    risorsa * res;
    int R,C,N,money,best_money=INT_MIN,i,j;
    FILE * fp;
    if(argc==7){
        R=atoi(argv[1]);
        C=atoi(argv[2]);
        money=atoi(argv[3]);

        fp=fopen(argv[4],"r");
        res=leggi_risorse(fp,&N);
        fclose(fp);

        fp=fopen(argv[5],"r");
        d=leggi_target(fp,R,C,1);
        fclose(fp);

        fp=fopen(argv[6],"r");
        a=leggi_target(fp,R,C,2);
        fclose(fp);

        best_a=(target **)malloc(R*sizeof(target*));
        for(i=0;i<R;i++)
            best_a[i] = (target *) malloc(C * sizeof(target));

        best_d=(target **)malloc(R*sizeof(target*));
        for(i=0;i<R;i++)
            best_d[i] = (target *) malloc(C * sizeof(target));

        /*print_sol(a,d,res,N,R,C);
        printf("\n");*/

        disp_r(0,0,a,d,res,N,R,C,money,&best_money,best_a,best_d);

        if(best_money!=INT_MIN){
            printf("soldi risparmiati %d\n",best_money);
            print_sol(best_a,best_d,res,N,R,C);
        }else
            printf("impossibile soddisfare tutti i requisiti");


    }
    return 0;
}

target ** leggi_target(FILE *fp,int R, int C,int tipo){
    int i,j,N,k,v;
    target ** mat=(target **)malloc(R*sizeof(target*));
    for(i=0;i<R;i++) {
        mat[i] = (target *) malloc(C * sizeof(target));
        for(j=0;j<C;j++) {
            mat[i][j].flag_tipo = 0;
            mat[i][j].v = 0;
            mat[i][j].supp = 0;
            mat[i][j].link = NULL;
        }
    }
    if(fscanf(fp,"%d",&N)==1){
        for(k=0;k<N;k++) {
            fscanf(fp, "%d %d %d", &i, &j, &v);
            if(mat[i][j].flag_tipo==0){
                mat[i][j].v=v;
                mat[i][j].flag_tipo=tipo;
            }
        }
    }
    return mat;
}
risorsa * leggi_risorse(FILE * fp,int * N){
    risorsa * res=NULL;
    int i;
    if(fscanf(fp,"%d",N)==1){
        res=(risorsa *)malloc((*N+1)*sizeof(risorsa));
        for(i=0;i<*N;i++) {
            fscanf(fp, "%d %d %d %d", &(res[i].r), &(res[i].a), &(res[i].d), &(res[i].c));
        }
        res[*N].a=0;
        res[*N].d=0;
        res[*N].r=0;
        res[*N].c=0;
    }
    return  res;
}

void disp_r(int x,int y,target ** a, target ** d, risorsa * res,int N,int R, int C,int money,int* best_money,target ** best_a, target ** best_d){
    int i,j,k;
    if(y>=C){
        y=0;
        x++;
    }
    if(x>=R){
        if(check_resources(a,R,C,2)==1 && check_resources(d,R,C,1)==1) {
            if(money>*best_money){
                *best_money=money;
                for(i=0;i<R;i++){
                    for(j=0;j<C;j++){
                        best_a[i][j]=a[i][j];
                        best_d[i][j]=d[i][j];
                    }
                }
            }

        }
        return;
    }
    if(a[x][y].flag_tipo!=1 && d[x][y].flag_tipo!=1 && a[x][y].flag_tipo!=2 && d[x][y].flag_tipo!=2) {
        for (k = 0; k <= N; k++) {
            if ((money - res[k].c) >= 0) {
                a[x][y].flag_tipo = 3;
                a[x][y].link = &res[k];
                d[x][y].flag_tipo = 3;
                d[x][y].link = &res[k];
                disp_r(x, y + 1, a, d, res, N, R, C, money - res[k].c, best_money, best_a, best_d);
            }
        }
    }else
        disp_r(x, y + 1, a, d, res, N, R, C, money, best_money, best_a, best_d);
    return ;
}

int check_resources(target ** m,int  R,int C,int tipo){

    int i,j,flag=1;
    for(i=0;i<R;i++){
        for(j=0;j<C;j++){
            if(tipo==1 && m[i][j].flag_tipo==3)
                popola_quadrato(m,R,C,i,j,m[i][j].link->r,m[i][j].link->d);
            else if(tipo==2 && m[i][j].flag_tipo==3)
                popola_quadrato(m,R,C,i,j,m[i][j].link->r,m[i][j].link->a);

        }
    }
    for(i=0;i<R;i++){
        for(j=0;j<C;j++){
            if(m[i][j].flag_tipo==tipo){
                if(m[i][j].supp<m[i][j].v)
                    flag= 0;
            }

            m[i][j].supp=0;
        }
    }
    return  flag;
}

void popola_quadrato(target ** m, int R, int C, int i,int j,int r, int v){
    int k,z;
    for(k=i-r;k<=(i+r);k++){
        for(z=j-r;z<=(j+r);z++)
            if(k>=0 && z>=0 && k<R && z<C) {
                if(m[k][z].flag_tipo==1 || m[k][z].flag_tipo==2)
                    m[k][z].supp+=v;
            }
    }
}

void print_sol(target ** a, target ** d, risorsa * res,int N,int R, int C){
    int i,j,k;
    for(k=0;k<N;k++)
        printf("%d: { attacco %d, difesa %d, raggio %d, costo %d}\n",k,res[k].a,res[k].d,res[k].r,res[k].c);
    printf("\n");
    for(i=0;i<R;i++){
        for(j=0;j<C;j++){

            if(a[i][j].flag_tipo==3 && a[i][j].link!=NULL && a[i][j].link->r==0)
            {
                a[i][j].flag_tipo=0;
                d[i][j].flag_tipo=0;
            }

            if(a[i][j].flag_tipo==0 && d[i][j].flag_tipo==0 )
                printf(" -- |");
            else if(a[i][j].flag_tipo==2)
                printf("N:%d |",a[i][j].v);
            else if(d[i][j].flag_tipo==1)
                printf("A:%d |",d[i][j].v);
            else if(a[i][j].flag_tipo==3 && a[i][j].link!=NULL)
            {
                for(k=0;k<N;k++)
                    if(&res[k]==a[i][j].link) {
                        printf("R:%d |", k);
                        break;
                    }
            }

        }
        printf("\n");
    }
}