#include <stdio.h>
#include <string.h>

#define MAXR 200
#define MAXS 30

//struct per rappresentare le sostituzioni, contiene un intero indicante la lunghezza
// delle parole da sostituire e un vettore di caratteri contenente la stringa da inserire al posto delle parole sostituite
typedef struct{
    int l;
    char sost[MAXS];
} sostituzione;


//legge il file sost.txt e carica un vettore si struct sostituzione
int leggiS(sostituzione s[],FILE *fp);

//dato un vettore di caratteri 'parola' restituisce la sostituzione (o la parola stessa in caso essa non possa essere sostituita
char* cercaS(sostituzione s[],int sl, char parola[]);

int main(int argc, char *argv[]) {

    char riga[MAXR+1];
    char * token;
    int sl;
    sostituzione s[MAXS];
    FILE *fps,*fpin,*fpout;

    if(argc==4){

        fps=fopen(argv[2],"r"); //apro il file sost.txt
        sl=leggiS(s,fps);       //carico il vettore delle sostituzionni
        fclose(fps);

        fpin=fopen(argv[1],"r");        //apro il file src.txt
        fpout=fopen(argv[3],"w");       //apro il file dest.txt

        while(fgets(riga,MAXR,fpin)){   //leggo una riga per volta dal file src.txt
            token=strtok(riga," ");     // tramite strtok splitto la riga usando come carattere di separazione lo spazio in modo da recuperare le singole parola
            while(token !=NULL){
                fprintf(fpout,"%s ",cercaS(s,sl,token));    //stampo sul file la sostituzione determinata da 'cercaS'
                token = strtok(NULL, " ");
            }
            fprintf(fpout,"\n");
        }
        fclose(fpin);                   //chiudo i file
        fclose(fpout);
    }
    return 0;
}

int leggiS(sostituzione s[],FILE *fp){
    int l,i;
    fscanf(fp,"%d\n",&l);       //leggo il numero di record del file (che assumo già aperto)
    for(i=0;i<l;i++){
        fscanf(fp,"%d %s\n",&(s[i].l),s[i].sost);   //leggo il file riga per riga e ne carico il contenuto nel vettore 'sost'
    }
    return l;
}

char* cercaS(sostituzione s[],int sl, char parola[]){
    int i,l;
    l=strlen(parola);       //recupero la lunghezza della parola da sostituire
    for (i=0;i<sl;i++){     //scorro il vettore delle sostituzioni
        if(s[i].l==l) {         //se trovo una lunghezza corrispondente a quella della parola
            return s[i].sost;   //ritorno la sostituzione
        }
    }
    return parola;          //nel caso non venga restituita alcuna sostituzione, ritorno la parola stessa in modo che venga copiata nel file dest.txt
}
