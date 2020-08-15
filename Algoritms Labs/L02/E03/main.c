#include <stdio.h>

#define MAXD 20


int main(int argc, char *argv[]) {

    int M[MAXD][MAXD];
    int r,c,dr,dc,i,j;
    int ne,no,se,so;
    FILE *fp;

    if(argc==2){
        fp=fopen(argv[1],"r");          //apri il file 'matrice.txt' in lettura
        fscanf(fp,"%d %d",&dr,&dc);     //leggo le dimensioni della matrice
        for(i=0;i<dr;i++)
            for(j=0;j<dc;j++)
                fscanf(fp,"%d",&M[i][j]); //carico la matrice leggendo i dati dal file
        fclose(fp);

        printf("inserisci riga e colonna da eliminare ==> ");
        scanf("%d %d",&r,&c);

        while(r>0 && r<dr && c>0 && c<dc){          //ciclo finche non vengono inserite dimensioni incompatibili con la patrice

            for(no=0,i=0;i<r;i++){                  //calcolo la somma per la sottomatrice nord-ovest
                for(j=0;j<c;j++)
                    no+=M[i][j];
            }

            for(ne=0,i=0;i<r;i++){                  //calcolo la somma per la sottomatrice nord-est
                for(j=c+1;j<dc;j++)
                    ne+=M[i][j];
            }

            for(so=0,i=r+1;i<dr;i++){               //calcolo la somma per la sottomatrice sud-ovest
                for(j=0;j<c;j++)
                    so+=M[i][j];
            }

            for(se=0,i=r+1;i<dr;i++){               //calcolo la somma per la sottomatrice sud-est
                for(j=c+1;j<dc;j++)
                    se+=M[i][j];
            }

            printf("NE:%d\nNO:%d\nSE:%d\nSO:%d\n",ne,no,se,so);         //stampo il risultato

            printf("\ninserisci riga e colonna da eliminare ==> ");
            scanf("%d %d",&r,&c);
        }
    }

    return 0;
}