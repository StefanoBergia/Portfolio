#include <stdio.h>
#include <string.h>

#define MAXD 20

//legge il file 'mat.txt' e carica la matrice
void leggiMatrice(char M[MAXD][MAXD],int * r,int *c,FILE *fp);
//ritorna il numero divolte che la stringa s ciene trovata all'interno della matrice (in orizzontale e verticale in entrambi i sensi )
int mat_search (char mat[MAXD][MAXD], int r, int c, char s[MAXD]);

int main(int argc,char * argv[]) {

    char M[MAXD][MAXD];
    char parola[MAXD];
    int r,c,count;
    FILE *fp;

    if(argc==3){
        fp=fopen(argv[1],"r");
        leggiMatrice(M,&r,&c,fp);
        fclose(fp);
        strcpy(parola,argv[2]);     //passo la parola da cercare come argomento al main
        count=mat_search(M,r,c,parola);

        printf("\nla parola %s compare %d volte nella matrice\n",parola,count);
    }
    return 0;
}

//passo r e c come puntatori in modo da poter recuperare nel main le dimensioni della matrice
void leggiMatrice(char M[][MAXD],int * r,int *c,FILE *fp){
    int i,j;
    fscanf(fp,"%d %d\n",r,c);           //recupero le dimensioni della matrice dal primo record del file
    for (i=0;i<*r;i++) {
        for (j = 0; j < *c; j++)
            fscanf(fp,"%c",&M[i][j]);   //leggo la matrice carattere per carattere
        fscanf(fp,"\n");                //consumo il carattere di ritorno a capo
    }
}


int mat_search (char mat[MAXD][MAXD], int r, int c, char s[MAXD]){

    int i,j,l,count=0;
    int w,wr;
    l=strlen(s);    //reucupero la lunghezza della stringa


    //nel primo ciclo scorro la matrice per righe in modo da trovare le corrispondenze sinistra-destra e destra-sinistra
    for (i=0;i<r;i++) {

        w=0;        //w è l'indice con cui scorro la stringa s per cui lo inizializzo dopo aver letto ogni riga
        wr=l-1;     //wr ha la stessa funzione di w, l'unica differenza è che lo utilizzo per scorrere la stringa al contrario
                    //in modo da verificare la presenza della parola anche nella direzione destra-sinistra/basso-alto

        for (j = 0; j < c; j++) {

            if (mat[i][j] == s[w]) {    //controllo se il carattere corrente della matrice corrisponde al carattere corrente della parola
                w++;                    //se è stata trovata la corrispondenza incremento l'indice della parola in modo che alla prossima iterazione venga
                                        //ricercato il carattere successivo della parola

                if (w == l) {           //se l'indice eccede la lunghezza della stringa significa che la parola è stata trovata
                    count++;            //aumento il contatore delle occorrenze della parola
                    w = 0;              //reinizializzo l'indice
                }
            } else
                w = 0;                  //se una corrispondenza non è stat trovata reinizializzo l'indice in modo che alla prossima iterazione
                                        //si riparta dal primo carattere della stringa


            if (mat[i][j] == s[wr]) {   // valgono gli stessi commenti fatti in precedenza con la differenza che l'indice wr viene inizializzato
                wr--;                   // all'ultimo valore utile della stringa e viene decrementato ogni volta che viene trovata una corrispondenza
                if (wr < 0) {
                    count++;
                    wr = l - 1;
                }
            } else
                wr = l - 1;

        }
    }

    //nel secondo ciclo scorro il ciclo per colonne in modo da trovare le corrispondenze alto-basso e basso-alto, valgono le stesse considerazioni fatte in precedenza
    for (j=0;j<c;j++) {

        w=0;
        wr=l-1;

        for (i = 0; i < r; i++) {
            if (mat[i][j] == s[w]) {
                w++;
                if (w == l) {
                    count++;
                    w = 0;
                }
            } else
                w = 0;

            if (mat[i][j] == s[wr]) {
                wr--;
                if (wr < 0) {
                    count++;
                    wr = l - 1;
                }
            } else
                wr = l - 1;

        }
    }
    return count;
}