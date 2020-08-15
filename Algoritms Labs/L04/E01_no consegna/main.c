#include <stdio.h>

#define MAXD 50


typedef struct{
    int sx;     //coordinata x dell'angolo in alto a sinistra
    int sy;     //coordinata y dell'angolo in alto a sinistra
    int b;      //ampiezza della base
    int h;      //ampiezza dell'altezza
}regione;


void leggiMatrice(int M[][MAXD],int MAXR,int * nr,int *nc,FILE *fp);
regione cercaRegione(int M[][MAXD],int nr,int nc,int i,int j);  //ricerca nella matrice (M) di dimensioni nr e nc una regione
//a aprtire dalle coordinate i e j, ritorna una regione con
//sx impostato a -1 in caso la regione non sia presente

int main(int argc, char * argv[]) {
    int M[MAXD][MAXD];
    int nr,nc,i,j,count=0;
    regione supp;
    FILE *fp;

    if(argc==2){
        fp=fopen(argv[1],"r");              //apro il file "matrice.txt" in lettura
        leggiMatrice(M,MAXD,&nr,&nc,fp);
        fclose(fp);

        for(i=0;i<nr;i++){                              //scorro la matrice elemento per elemento
            for(j=0;j<nc;j++)
            {
                if(M[i][j]==1){
                    supp=cercaRegione(M,nr,nc,i,j);     //per ogni cella verifico  se sia presente una regione

                    if(supp.sx>=0){                     //verifico che la regione restituita sia valida
                        count++;
                        printf("Regione %d: estr. sup. SX = <%d %d> b=%d h=%d Area=%d\n",count,supp.sx,supp.sy,supp.b,supp.h,supp.b*supp.h);
                    }
                }
            }
        }

    }
    return 0;
}

void leggiMatrice(int M[][MAXD],int MAXR,int * nr,int *nc,FILE *fp){
    int i,j;
    fscanf(fp,"%d %d", nr, nc);          //recupero le dimensioni della matrice
    for(i=0;i<*nr;i++){                  //leggo la matrice elemento per elemento
        for(j=0;j<*nc;j++)
            fscanf(fp,"%d",&M[i][j]);
    }
}

regione cercaRegione(int M[][MAXD],int nr, int nc,int i,int j){
    regione q;
    q.sx=i;
    q.sy=j;
    q.b=0;
    q.h=0;

    int r=0,c=0,flag=1;                     //c e r sono variabili di supporto per il calcolo della base e dell'altezza della regione
    //flag serve per determinare

    for (;j<nc && M[i][j]==1;j++,c++);
    for(j=q.sy;i<nr && M[i][j]==1; i++,r++);

    for (i=0;i<r ;i++)
        for(j=0;j<c ;j++){
            if(M[i+q.sx][j+q.sy]==1)
                M[i+q.sx][j+q.sy]=2;
            else
                flag = 0;   //non esco anticipatamente dal ciclo in modo da rimuovere tutte le caselle nere appartenenti a una forma irregolare
            //in modo che non vengano più considerate in cicli  futuri
        }

    if(flag==0)
        q.sx=-1;

    q.b=c;
    q.h=r;

    return q;
}