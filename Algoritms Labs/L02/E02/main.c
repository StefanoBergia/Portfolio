#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXR 200
#define MAXS 5
#define MAXPR 20

int getParola(char riga[],int startindex);                  //dato l'indice del primo carattere di una parola, resistuisce l'indice finale
int chkPrefisso(char prefisso[],char riga[],int s,int f);   //verifica che una parola inizi con un dato prefisso
void printWord(char riga[],int s,int f);                    //stampa a schermo una parola

int main(int argc, char *argv[]) {

    FILE *fp;
    char riga[MAXR+1];                  //vettore di caratteri per contenere la riga corrente del file
    char prefissi[MAXPR][MAXS+1];       //vettore di stringhe contenente i prefissi
    int lpr,i,j,l,lr,count,flag=1;

    if(argc==3) {

        fp = fopen(argv[1], "r");           //apro il file 'sequenze.txt'
        fscanf(fp,"%d\n",&lpr);             //recupero il numero di record del file
        for (i=0;i<lpr;i++){
            fscanf(fp,"%s\n",prefissi[i]);  //leggo ogni prefisso e lo inserisco nel vettore 'prefissi'
        }
        fclose(fp);

        for(j=0;j<lpr;j++) {                //ciclo per ogni prefisso
            fp = fopen(argv[2], "r");       //apro il file 'testo.txt'
            count = 1;                      //inizializzo il contatore delle parole

            flag=1;                         //flag viene solo utilizzato per mostrare correttamente
                                            //il prefisso in cima alla lista di occorenze trovate
                                            //in modo che nel caso non vengano trovate occorrenze
                                            //anche il relativo prefisso non venga visualizzto

            while (fgets(riga, MAXR, fp)) {     //leggo il file riga per riga
                i=0;                            //inizializzo l'indice per scorrere la riga
                lr=strlen(riga);
                while(i<lr) {                   //cerco parole finchè l'indice non eccede la dimensione della riga stessa

                    for (; (!isalnum(riga[i]))&& i<lr; i++);        //salto i caratteri non alphanumerici iniziali
                    if(i<lr) {
                        l = getParola(riga, i);                         //recupero l'indice finale della parola corrente (l'indice iniziale è pari a i)
                        if (chkPrefisso(prefissi[j], riga, i, l)) {     //controllo che vi sia la corrispondenza con il prefisso
                            if(flag) {
                                printf("\n%s\n", prefissi[j]);          //se sono alla prima iterazione stampo il prefisso
                                flag=0;                                 //e azzero il flag
                            }
                            printWord(riga, i, l);                      //stampo la parola trovata
                            printf(" %d\n", count);                     //stampo la posizione della parola
                        }
                        count++;                                        //incremento il contatore delle parole
                        i = l + 1;                                      //posiziono correttamente l'indice
                    }
                }
            }
            printf("\n");
            fclose(fp);
        }
    }
    return 0;
}

void printWord(char riga[],int i,int l){
    for (;i<=l;i++)
        printf("%c",riga[i]);
}

int getParola(char riga[],int startindex){
    int endIndex,l;
    l=strlen(riga);
    for (endIndex=startindex;isalnum(riga[endIndex]) && endIndex<l;endIndex++);     //cicla sulla riga partendo da startindex fino
                                                                                    // fino a che non viene raggiunta la fine della
                                                                                    //riga oppure non si trova un carattere non alfanumerico
    endIndex--;         //decremento l'indice finale per
                        // ovviare al ciclo di uscita del for
    return endIndex;
}

int chkPrefisso(char prefisso[],char riga[],int s,int f){
    int i,l,flag=1;                     //la variabile flag serve per effettura l'uscita anticipata dal ciclo in caso anche solo un carattere non corrisponda
    char supp1,supp2;                   //caratteri di supporto per effettuare il confronto tra caratteri
    l=strlen(prefisso);
    for(i=0;i<l && i+s<=f && flag;i++){
        supp1=tolower(prefisso[i]);
        supp2=tolower(riga[s+i]);
        if(supp1!=supp2)                //confronto ogni carattere del pefisso con ogni carattere della parola alla stessa posizione
            flag=0;
    }
    return flag;
}
