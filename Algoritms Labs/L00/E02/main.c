#include <stdio.h>
#include <string.h>

#define MAXR 10

int conta_consonanti(char parola[]);

int main(int argc,char**argv) {

    FILE *fpin, *fpout1, *fpout2;
    char riga [MAXR+1];
    char P [MAXR+1];
    int n=0,i,consonanti;

    if(argc==4)
    {
        fpin=fopen(argv[1],"r");
        fpout1=fopen(argv[2],"w");
        fpout2=fopen(argv[3],"w");
    }
    fscanf(fpin,"%d %s\n",&n,P);
    consonanti=conta_consonanti(P);

    for(i=0;i<n;i++){
        fscanf(fpin,"%s\n",riga);
        if(strcmp(P,riga)<0)
            fprintf(fpout1,"%s\n",riga);
        if(conta_consonanti(riga)>consonanti)
            fprintf(fpout2,"%s\n",riga);

    }

    fclose(fpin);
    fclose(fpout1);
    fclose(fpout2);

    return 0;
}

int conta_consonanti(char parola[]){
    int l,i,count=0;
    char c;
    l=strlen(parola);
    for(i=0;i<l;i++){
        c=parola[i];
        if(parola[i]!='a'&& parola[i]!='A' && parola[i]!='e' && parola[i]!='E' && parola[i]!='i' && parola[i]!='I'
           && parola[i]!='o' && parola[i]!='O' && parola[i]!='u' && parola[i]!='U' )
            count++;
    }
    return count;

}
