#include <stdio.h>
#include "Graph.h"
#define MAXC 30

Graph leggiGrafo(FILE * fp);
int leggiCmd();

int main(int argc, char **argv) {
    Graph G;
    FILE * fp;
    int cmd;
    char cardId[MAXC+1];
    if(argc==2){
        fp=fopen(argv[1],"r");
        G=leggiGrafo(fp);
        //printAdj(G);
        fclose(fp);
        cmd=leggiCmd();
        while(cmd!=0){
            switch (cmd){
                case 1:
                    GRAPHshowAllV(G);
                    printf("\n");
                    break;
                case 2:
                    printf("inserisci cardId:");
                    scanf("%s",cardId);
                    printf("\n");
                    GRAPHshowV(G,cardId);
                    printf("\n\n");
                    break;
                case 3:
                    printf("\n");
                    GeneraMatrice(G);
                    MostraMatrice(G);
                    printf("\n\n");
                    break;
                case 4:
                    printf("flusso interno:%d, flusso esterno %d\n",Get_flusso(G,'I'),Get_flusso(G,'E'));
                case 0:
                    break;
                default:
                    printf("comando non riconosciuto\n");
            }
            cmd=leggiCmd();
        }
    }
    return 0;
}

int leggiCmd(){
    int cmd;
    printf("inserisci comando\n");
    printf("1-visualizza vertici\n");
    printf("2-visualizza vertici adiacenti\n");
    printf("3-visualizza matrice adiacenze\n");
    printf("4-Calcola flussi\n");
    printf("0-esci\n");
    scanf("%d",&cmd);
    return cmd;
}

Graph leggiGrafo(FILE * fp){
    Graph  G;
    int n,i,wt;
    char str1[MAXC+1],str2[MAXC+1];
    fscanf(fp,"%d",&n);
    G=GRAPHinit(n);
    for(i=0;i<n;i++){
        fscanf(fp,"%s %s",str1,str2);
        GRAPHaddV(G,NEW(str1,str2));
    }
    while(fscanf(fp,"%s %s %d",str1,str2,&wt)==3){
        GRAPHaddE(G,str1,str2,wt);
    }
    return G;
}

