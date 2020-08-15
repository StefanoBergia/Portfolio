#include <stdio.h>
#include <stdlib.h>

#define MAXD 50

typedef struct{
    int i;
    int j;
}posizione;

posizione verificaMossa(posizione current,char M [][MAXD],char V[][MAXD],int r,int c,int x,int y,int* flag);    //restituisce la posizione finale dopo uno spostamento di coordinate x e y (di cui una a 0)
                                                                                                                //il puntatore a intero flag serve per informare il main che si è passati in una cella già percorsa

int main(int argc, char *argv[]) {

    char M[MAXD][MAXD];
    char visite[MAXD][MAXD];            //la matrice visite tiene traccia delle celle già visitate

    FILE * fp;
    int r,c,i,j,lunghezza=0,flag_s=1;
    posizione I,U,current;


    if(argc==3){

        fp=fopen(argv[1],"r");                  //apro il file "matrice.txt" e leggo la matrice carattere per carattere
        fscanf(fp,"%d %d\n",&r,&c);
        for(i=0;i<r;i++) {
            for (j = 0; j < c; j++) {
                fscanf(fp, "%c", &M[i][j]);
                visite[i][j]=0;
                if(M[i][j]=='I')
                {
                    I.i=i;
                    I.j=j;
                }
                if(M[i][j]=='U'){
                    U.i=i;
                    U.j=j;
                }
            }
            fscanf(fp,"\n");
        }
        fclose(fp);

        current.i=I.i;              //inizializzo la posizione corrente
        current.j=I.j;

        fp=fopen(argv[2],"r");      //apro il file "mosse.txt"

        while((current.i!=U.i || current.j!=U.j) && fscanf(fp,"%d %d\n",&i,&j)==2){         //ciclo finchè non ho terminato le mosse o non ho raggiunto l'uscita
            current=verificaMossa(current,M,visite,r,c,i,j,&flag_s);
            if(current.i==-1)                                                               //VerificaMossa resituisce una posizione con i pari a -1 per indicare una mossa non valida
                break;
            lunghezza+=abs(i);
            lunghezza+=abs(j);
        }
        fclose(fp);

        if(current.i==-1)
            printf("percorso inserito non valido\n");
        else if (current.i==U.i && current.j==U.j){
            printf("il percorso inserito è un cammino valido\n");
            if(flag_s)
                printf("il percorso è semplice\n");
            else
                printf("il percorso non è semplice\n");
            printf("la lunghezza del percorso è %d",lunghezza);

        }else
            printf("il percorso inserito non permette di raggiungere l'uscita\n");


    }
    return 0;
}

posizione verificaMossa(posizione current,char M [][MAXD],char V[][MAXD],int r,int c,int x,int y,int* flag){
    int offset,k;
    posizione fine=current;
    if(x==0){                                                   //spostamento lungo le colonne
        if(y<0)                                                 //verifico se si tratta di uno spostamento in orizzontale o verticale
            offset=1;
        else
            offset=-1;
        for(k=0;fine.i<r && k<abs(y);k++,fine.i+=offset){       //scorro la matrice secondo quanto indicato dalla mossa
            if(M[fine.i][fine.j]=='X')                          //se incontro un muro finisco anticipatamente la funzione
            {
                fine.i=-1;
                return fine;
            }
            if(V[fine.i][fine.j]>0)                             //se sono già passato in una cella, azzero il flag
                *flag=0;
            V[fine.i][fine.j]++;                                //incremento il numero di visite della cella
        }

    }
    if (y==0){                                                  //spostamento lungo le righe
        if(x>0)
            offset=1;
        else
            offset=-1;
        for(k=0;fine.j<c && k<abs(x);k++,fine.j+=offset){
            if(M[fine.i][fine.j]=='X')
            {
                fine.i=-1;
                return fine;
            }
            if(V[fine.i][fine.j]>0)
                *flag=0;
            V[fine.i][fine.j]++;
        }
    }
    return fine;

}