#include <stdio.h>
#include <string.h>

#define MAXN 1000
#define MAXR 30
#define NCMD 5


typedef struct{
    char codice_volo[5+1];
    char partenza[3+1];
    char destinazione[3+1];
    char data_e_ora[19+1];
    char vettore[4+1];

    int flag;           //flag che serve per determinare se la città relativa ad un vettore è già stata stampata
}volo;


typedef enum{
    r_date,
    r_origine,
    r_destinazione,
    r_vettore,
    r_fine
} comando_e;

char comandi[][MAXR]={"date","origine","destinazione","vettore","fine"};

int leggiTabella(FILE *,volo [],int);
comando_e leggiComando();
void selezionaDate(volo [],int,char[],char[]);
void selezionaOrigine(volo [],int,char[]);
void selezionaDestinazione(volo [],int,char[]);
void selezionaVettore(volo [],int,char[]);

int main(int argc, char *argv[]) {
    FILE *fp;
    volo voli[MAXN];
    char arg1[MAXR];
    char arg2[MAXR];
    int nDati;
    comando_e comando;

    if(argc==2){
        fp=fopen(argv[1],"r");
        nDati=leggiTabella(fp,voli,MAXN);
        fclose(fp);

        do{
            comando=leggiComando();
            switch (comando){
                case r_date:
                    scanf("%s %s",arg1,arg2);
                    selezionaDate(voli,nDati,arg1,arg2);
                    break;
                case r_origine:
                    scanf("%s",arg1);
                    selezionaOrigine(voli,nDati,arg1);
                    break;
                case r_destinazione:
                    scanf("%s",arg1);
                    selezionaDestinazione(voli,nDati,arg1);
                    break;
                case r_vettore:
                    scanf("%s",arg1);
                    selezionaVettore(voli,nDati,arg1);
                    break;
                case r_fine:
                default:
                    printf("programma terminato");
            }
        }while(comando!=r_fine);

    }
    return 0;
}

int leggiTabella(FILE * fp,volo voli[],int max){
    int n,i;
    fscanf(fp,"%d",&n);
    for(i=0;i<max && i <n;i++,voli[i].flag=0)
        fscanf(fp,"%s %s %s %s %s",voli[i].codice_volo,voli[i].partenza,voli[i].destinazione,voli[i].data_e_ora,voli[i].vettore);

    return i;
}

comando_e leggiComando(){
    char cmd[13];
    int i;
    printf("inserisci comando==>");
    scanf("%s",cmd);
    for(i=0;i<NCMD;i++)
        if(strcmp(cmd,comandi[i])==0)
            return i;
    return r_fine;
}

void selezionaDate(volo voli[],int n,char data1[],char data2[]){
    int i,cmp1,cmp2;
    printf("\n");
    for(i=0;i<n;i++) {
        cmp1=strcmp(voli[i].data_e_ora, data1);
        cmp2=strcmp(voli[i].data_e_ora, data2);
        if ( cmp1>=0 && cmp2<=0)
            printf("%s\n", voli[i].codice_volo);
    }
    printf("\n");
}

void selezionaOrigine(volo voli [],int n,char origine[]){
    int i;
    printf("\n");
    for(i=0;i<n;i++)
        if(strcmp(voli[i].partenza,origine)==0)
            printf("%s\n",voli[i].codice_volo);
    printf("\n");

}

void selezionaDestinazione(volo voli [],int n,char destinazione[]){
    int i;
    printf("\n");
    for(i=0;i<n;i++)
        if(strcmp(voli[i].destinazione,destinazione)==0)
            printf("%s\n",voli[i].codice_volo);
    printf("\n");
}

void selezionaVettore(volo voli[],int n,char vettore[]){
    int i,j;
    for(i=0;i<n;i++){
        if(strcmp(voli[i].vettore,vettore)==0)
            voli[i].flag=1;                                         //porto il flag di tutti i voli con un certo vettore a 1
    }
    printf("\n");
    for(i=0;i<n;i++){
        if(voli[i].flag==1) {
            printf("%s\n", voli[i].partenza);
            ///
            for(j=0;j<n;j++)                                        //per evitare di ripetere una città dopo averla stampata
                if(strcmp(voli[i].partenza,voli[j].partenza)==0)    //scorro il vettore dei voli e porto a zero il flag se la città
                    voli[j].flag=0;                                 //è uguale a quella appena stampata
            ///
        }
        voli[i].flag=0;
    }

    printf("\n");

}