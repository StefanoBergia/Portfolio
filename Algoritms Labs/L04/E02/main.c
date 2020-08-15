#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXR 60
#define MAXC 80
#define MAXP 1000

typedef struct {
    int i;
    int j;
}point;

int leggiPagina(char pagina[][MAXC+1],int nr,FILE *fp);
int  riconosciParole(char pagina[][MAXC+1],int nr,char *parole[],int maxp);
void ordinaParole(char *parole[],int np);
int ricercaBinaria(char *parole[],int l,int r,char *cerca);
int confrontaParole(char * p1,char *p2);
point recuperacoord(char pagina[][MAXC+1],char * parola);
void stampaParola(char * parola);



int main(int argc,char **argv) {
    FILE *fp;
    char pagina[MAXR][MAXC+1];
    char * parole[MAXP];
    int nr=0,np=0;
    char  comando[MAXR];
    int i,j;
    point supp;

    if(argc==2){
        fp=fopen(argv[1],"r");
        nr=leggiPagina(pagina,MAXR,fp);                                 //richiamo la funzione leggiPagina
        fclose(fp);
        np = riconosciParole(pagina,nr,parole,MAXP);                    //richiamo la funzione riconosciparole
        ordinaParole(parole,np);                                        //ordino le parole
        printf("inserisci parola da cercare-->");
        scanf("%s",comando);
        while (comando!=NULL && strcmp(comando,"$fine")!=0 ){
            i=ricercaBinaria(parole,0,np-1,&comando[0]);                //utilizzo la ricerca binaria per trovare una occorrenza
            supp=recuperacoord(pagina,parole[i]);
            printf("parola ");
            stampaParola(parole[i]);
            printf("trovata in posizione (%d %d)",supp.i,supp.j);
            for(j=i+1;j<np && confrontaParole(parole[i],parole[j])==0;j++) //scorro il vettore delle parole in avanti per trovare altre eventuali occorrenze
            {
                supp=recuperacoord(pagina,parole[j]);
                printf(" (%d %d)",supp.i,supp.j);
            }
            for(j=i-1;j>=0 && confrontaParole(parole[i],parole[j])==0;j--)  //scorro il vettore delle parole indietro per trovare altre eventuali occorrenze
            {
                supp=recuperacoord(pagina,parole[j]);
                printf(" (%d %d)",supp.i,supp.j);
            }


            printf("\ninserisci parola da cercare-->");
            scanf("%s",comando);
        }
    }

    return 0;
}

int leggiPagina(char pagina[][MAXC+1],int nr,FILE *fp){
    int i=0,j=0;
    while(fgets(pagina[i],MAXR,fp)!=NULL && i<nr)
        i++;
    for(i=0;i<nr;i++){
        for(j=0;j<MAXC;j++)
            if(pagina[i][j]=='\n')                      //trasformo gli 'a capo' in spazi semplici in modo da semplificare l'individuazione delle parole
                pagina[i][j]=' ';
            else
                pagina[i][j]=tolower(pagina[i][j]);     //trasformo tutti i caratteri maiuscoli in minuscoli in modo da facilitare la ricerca
    }
    return i;
}

int  riconosciParole(char pagina[][MAXC+1],int nr,char *parole[],int maxp){
    int i,j,y,flag=1;                                    //setto il flag a 1 per la prima parola(suppongo che il testo non inizi con spazi)
    for(i=0,y=0;i<nr && y<maxp;i++){                    //ciclo sulla matrice
        flag=1;
        for(j=0;j<MAXC && y<maxp;j++){
            if(!isalpha(pagina[i][j]))                  //se trovo un carattere non alfabetico imposto il flag a 1
                flag = 1;
            else
            {
                if(flag==1){                            //al primo carattere diverso da uno stazio salvo il puntatore alla parola e resetto il flag
                    parole[y]=&pagina[i][j];
                    y++;
                    flag = 0;
                }
            }
        }
    }
    return y;
}

void ordinaParole(char *parole[],int np){
    int i,j;
    char * tmp;
    for(i=1;i<np;i++){
        tmp=parole[i];
        j=i-1;
        while(j>=0 && confrontaParole(parole[j],tmp)>=0){
            parole[j+1]=parole[j];
            j--;
        }
        parole[j+1]=tmp;
    }
}

int ricercaBinaria(char *parole[],int l,int r,char *cerca){
    int i,c;
    if(r>l) {
        i =l+( r - l) / 2;
        c = confrontaParole(parole[i], cerca);
        if (c == 0)
            return i;
        else if (c<0)
            return ricercaBinaria(parole, i + 1, r, cerca);
        else
            return ricercaBinaria(parole, l, i - 1, cerca);
    }else
        return -1;
}

point recuperacoord(char pagina[][MAXC+1],char * parola){           //dato un puntatore  a carattere ne recupera le coordinate sulla matrice
    point r;
    char * supp=pagina[0];                                          //ciclo sulla matrice con un puntatore finchè non trovo l'occorrenza del puntatore cercato
    for(r.i=0;r.i<MAXR;r.i++){
        for(r.j=0;r.j<MAXC;r.j++){
            if(supp==parola)
                return r;
            else
                supp++;
        }
    }
    return r;
}

int confrontaParole(char * p1,char *p2){
    while(*p1!='\0' && *p2!='\0' && isalpha(*p1) && isalpha(*p2)){
        if(*p1!=*p2)
            if(*p1>*p2)                 //termino l'esecuzione al primo carattere diverso
                return 1;
            else
                return -1;
        p1++;
        p2++;
    }
    if (isalpha(*p1) && (!isalpha(*p2)|| *p2=='\0'))            //se l'esecuzione non è finita determino la precedenza in base alla lunghezza
        return 1;
    else if (isalpha(*p2) && (!isalpha(*p1) || *p1=='\0'))
        return -1;

    else
        return 0;
}

void stampaParola(char * parola){
    while(parola!=NULL && isalpha(*parola)) {
        putchar(*parola);
        parola ++;
    }
}