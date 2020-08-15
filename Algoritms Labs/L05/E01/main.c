#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAXC 25

typedef struct{
    char codice[5+1];
    char nome[MAXC+1];
    char cognome[MAXC+1];
    char categoria[MAXC +1];
    char data[10+1];
    int ore;

    char dataR[10+1];           //memorizzo la data in ordine inverso in modo da poter effetuare i confronti con la strcmp
    char *chiave;               //utilizzo un puntatore a char per decidere in bas a quale campo ordinare
} atleta;

atleta ** leggiFile(FILE *fp,int *n);
void stampaTabella(FILE *fp,atleta ** atleti,int n);
int leggiComando();
void setChiaveCodice(atleta ** atleti,int n);
void setChiaveCognome(atleta ** atleti,int n);
void setChiaveNome(atleta ** atleti,int n);
void setChiaveData(atleta ** atleti,int n);
void setChiaveCategoria(atleta ** atleti,int n);
void ordina(atleta **atleti,int n);
void MergeSort(atleta **atleti,atleta ** supp,int l,int r);
void Merge(atleta **atleti,atleta ** supp,int l,int q,int r);
void raggruppAtleti(atleta ** atleti,int n);
atleta ** RicercaLineare(atleta ** atleti,int n,char * chiave, int *l);
atleta** RicercaDicotomicaM(atleta ** atleti,int l,int r,char * chiave,int *n);
atleta * RicercaDicotomica(atleta ** atleti,int l,int r,char * chiave,int *i);


int main(int argc, char **argv) {
    FILE *fp;
    atleta **atleti,**supp;
    int n, cmd,ordine=0,i,agg,n_supp;
    char ricerche[MAXC];
    if (argc == 2) {
        fp = fopen(argv[1], "r");
        atleti = leggiFile(fp, &n);
        fclose(fp);

        do {
             cmd = leggiComando();
             switch (cmd) {
                 case 1:
                     stampaTabella(stdout,atleti,n);
                     break;
                 case 2:
                     setChiaveData(atleti,n);
                     ordine=1;
                     ordina(atleti,n);
                     printf("comando eseguito");
                     break;
                 case 3:
                     setChiaveCodice(atleti,n);
                     ordine=2;
                     ordina(atleti,n);
                     printf("comando eseguito");
                     break;
                 case 4:
                     setChiaveNome(atleti,n);
                     ordina(atleti,n);              //ordino prima per nome (chiave secondaria) in modo da sfruttare la stabilità del mergesort
                     setChiaveCognome(atleti,n);
                     ordine=3;
                     ordina(atleti,n);
                     printf("comando eseguito");
                     break;
                 case 5:
                     raggruppAtleti(atleti,n);
                     switch (ordine){
                         case 1:
                             setChiaveData(atleti,n);
                             ordina(atleti,n);
                             break;
                         case 2:
                             setChiaveCodice(atleti,n);
                             ordina(atleti,n);
                             break;
                         case 3:
                             setChiaveCognome(atleti,n);
                             ordina(atleti,n);
                             break;
                     }
                     printf("comando eseguito");
                     break;
                 case 6:
                     printf("inserisci codice e aggiornamento ");
                     scanf("%s %d",ricerche,&agg);
                     setChiaveCodice(atleti,n);
                     if(ordine==2)
                         supp=RicercaDicotomicaM(atleti,0,n-1,ricerche,&n_supp);
                     else
                         supp=RicercaLineare(atleti,n,ricerche,&n_supp);
                     if(supp!=NULL) {
                         supp[0]->ore = agg;
                         printf("elemento aggiornato");
                     }
                     else
                         printf("elemento non trovato\n");
                     switch (ordine){
                         case 1:
                             setChiaveData(atleti,n);
                             break;
                         case 2:
                             setChiaveCodice(atleti,n);
                             break;
                         case 3:
                             setChiaveCognome(atleti,n);
                             break;
                     }
                    free(supp);
                     break;
                 case 7:
                     printf("inserisci codice-->");
                     scanf("%s",ricerche);
                     setChiaveCodice(atleti,n);
                     if(ordine==2)
                         supp=RicercaDicotomicaM(atleti,0,n-1,ricerche,&n_supp);
                     else
                         supp=RicercaLineare(atleti,n,ricerche,&n_supp);
                     if(supp!=NULL)
                         stampaTabella(stdout,supp,n_supp);
                     else
                         printf("elemento non trovato\n");
                     switch (ordine){
                         case 1:
                             setChiaveData(atleti,n);
                             break;
                         case 2:
                             setChiaveCodice(atleti,n);
                             break;
                         case 3:
                             setChiaveCognome(atleti,n);
                             break;
                     }
                     free(supp);
                     break;
                 case 8:
                     printf("inserisci cognome-->");
                     scanf("%s",ricerche);
                     setChiaveCognome(atleti,n);
                     if(ordine==3)
                         supp=RicercaDicotomicaM(atleti,0,n-1,ricerche,&n_supp);
                     else
                         supp=RicercaLineare(atleti,n,ricerche,&n_supp);
                     if(supp!=NULL)
                         stampaTabella(stdout,supp,n_supp);
                     else
                         printf("elemento non trovato\n");
                     switch (ordine){
                         case 1:
                             setChiaveData(atleti,n);
                             break;
                         case 2:
                             setChiaveCodice(atleti,n);
                             break;
                         case 3:
                             setChiaveCognome(atleti,n);
                             break;
                     }
                     free(supp);
                     break;
                 case 0:
                     printf(" fine programma");
                     break;
                 default:
                     printf("comando non riconosciuto");
                     break;
             }
         } while(cmd>0);

        for(i=0;i<n;i++)
            free(atleti[i]);
        free(atleti);
    }

    return 0;
}


int leggiComando(){
    int n;
    printf("\n1-visualizza dati\n");
    printf("2-ordina secondo la data\n");
    printf("3-ordina secondo il codice\n");
    printf("4-ordina secondo il cognome\n");
    printf("5-raggruppa atleti\n");
    printf("6-aggiorna monte ore\n");
    printf("7-ricerca per codice\n");
    printf("8-ricerca per cognome\n");
    printf("0-fine\n");
    printf("inserisci comando-->");
    scanf("%d",&n);
    return n;
}

atleta ** leggiFile(FILE *fp,int *n){
    int i,s_anno,s_mese,s_giorno;
    fscanf(fp,"%d",n);
    atleta ** atleti,**supp;
    atleti=(atleta **)malloc((*n)*sizeof(atleta*));
    supp=atleti;
    for(i=0;i<*n;i++,atleti++) {
        (*atleti)=(atleta *)malloc(sizeof(atleta));
        fscanf(fp, "%s %s %s %s %s %d", (*atleti)->codice, (*atleti)->nome, (*atleti)->cognome, (*atleti)->categoria, (*atleti)->data,
               &((*atleti)->ore));
        (*atleti)->chiave=NULL;
        sscanf((*atleti)->data,"%d/%d/%d",&s_giorno,&s_mese,&s_anno);
        sprintf((*atleti)->dataR,"%d/%d/%d",s_anno,s_mese,s_giorno);
    }
    return supp;

}

void stampaTabella(FILE *fp,atleta ** atleti,int n){

    int i;
    printf("\n");
    for (i=0;i<n;i++,atleti++)
        fprintf(fp,"%s  %s %s %s %s %d\n",(*atleti)->codice,(*atleti)->nome,(*atleti)->cognome,(*atleti)->categoria,(*atleti)->data,(*atleti)->ore);
    printf("\n");
}

void setChiaveCodice(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->codice;
}

void setChiaveCognome(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->cognome;
}

void setChiaveNome(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->nome;
}

void setChiaveData(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->dataR;
}

void setChiaveCategoria(atleta ** atleti,int n){
    int i;
    for(i=0;i<n;i++)
        atleti[i]->chiave=atleti[i]->categoria;
}

void ordina(atleta **atleti,int n){
    atleta **supp=(atleta **)malloc(n*sizeof(atleta *));
    MergeSort(atleti,supp,0,n-1);
    free(supp);

}

void MergeSort(atleta **atleti,atleta ** supp,int l,int r){
    int q=(l+r)/2;
    if(l>=r)
        return;
    MergeSort(atleti,supp,l,q);
    MergeSort(atleti,supp,q+1,r);
    Merge(atleti,supp,l,q,r);

    return;
}

void Merge(atleta **atleti,atleta ** supp,int l,int q,int r){
    int i,j,k;
    i=l;
    j=q+1;
    for(k=l;k<=r;k++){
        if(i>q)
            supp[k]=atleti[j++];
        else if(j>r)
            supp[k]=atleti[i++];
        else if(strcmp(atleti[i]->chiave,atleti[j]->chiave)<=0)
            supp[k]=atleti[i++];
        else
            supp[k]=atleti[j++];
    }
    for(k=l;k<=r;k++)
        atleti[k]=supp[k];

    return ;

}

void raggruppAtleti(atleta ** atleti,int n){
    int i;
    char * cur_cat=NULL;
    setChiaveCategoria(atleti,n);
    ordina(atleti,n);                               //per effettuare il raggruppamento
    for(i=0;i<n;i++){
        if(cur_cat==NULL || strcmp(cur_cat,atleti[i]->categoria)!=0){
            cur_cat=atleti[i]->categoria;
            printf("\n%s\n",cur_cat);
        }
        printf("%s\n",atleti[i]->codice);
    }
    printf("\n");

}

atleta ** RicercaLineare(atleta ** atleti,int n,char * chiave,int *l){
    atleta ** ret;
    int i,j,count=0;
    for(i=0;i<n ;i++){
        if(strcmp(atleti[i]->chiave,chiave)==0)
            count++;
    }
    ret=(atleta **)malloc(count*sizeof(atleta *));
    for(i=0,j=0;i<n ;i++){
        if(strcmp(atleti[i]->chiave,chiave)==0)
            ret[j++]=atleti[i];
    }
    *l=count;
    return ret;
}

atleta** RicercaDicotomicaM(atleta ** atleti,int l,int r,char * chiave,int *n){     //esegue una ricerca dicotomica ma ritorna tutte le occorrenze
    atleta ** ret=NULL;
    *n=0;
    int count=1,j,i;
    atleta * supp=RicercaDicotomica(atleti,l,r,chiave,&i);
    /*for(i=l;i<=r;i++)
        if(atleti[i]==supp)
            break;*/
    if(supp!=NULL){
        for(i++; i<=r && strcmp(supp->chiave,atleti[i]->chiave)==0;count++,i++) ;
        for(i-=count; i>=l && strcmp(supp->chiave,atleti[i]->chiave)==0;count++,i--) ;
        count--;
        ret=(atleta **)malloc(count*sizeof(atleta *));
        for(j=0,i++;j<count;j++,i++)
            ret[j]=atleti[i];
        *n=count;
    }
    return ret;
}

atleta * RicercaDicotomica(atleta ** atleti,int l,int r,char * chiave,int *i){
    int q=(l+r)/2,supp;
    supp=strcmp(atleti[q]->chiave,chiave);
    if(supp==0) {
        *i=q;
        return atleti[q];
    }
    if(l>=r)
        return NULL;

    if(supp>0)
        return RicercaDicotomica(atleti,l,q,chiave,i);

    return RicercaDicotomica(atleti,q+1,r,chiave,i);

}
