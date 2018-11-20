/*Nome: Pedro Augusto Gandra de Andrade
 *Matricula: 201811130208
 *Nome: Pedro Henrique Madeira de Oliveira Pereira
 *Matricula: 201811130224
 *Nome: Vítor Fitzherbert Souza
 *Matricula: 201811130267
 *Descricao: Programa que lê dois números e imprime a integral dupla da função exponencial da batatinha roxa...
 */

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define len 201

int i;

typedef struct a{
    int id;
    char amino[6];
    int tipo;
    char nome[6];
    double x,y,z;
    struct a *prox;
} ATOM;

int comecaCom(char *str, char *proc){
    for(i=0; proc[i]!='\0'; i++){
        if(str[i]!=proc[i]){
            return 0;
        }
    }
    return 1;
}

int comparar(ATOM *s1,ATOM *s2){
    int ret=strcmp(s1->nome,s2->nome);
    if(ret==0){
        ret=strcmp(s1->amino,s2->amino);
        if(ret==0){
            ret=s1->tipo-s2->tipo;
        }
    }
    return ret;
}

void ordena(ATOM **ptrInic){
    ATOM *novo=NULL;
    ATOM *velho=*ptrInic;
    while(velho!=NULL){
        ATOM *maior=velho;
        ATOM *atual=velho;
        ATOM *ant,*antMaior;
        while(13){
            ant=atual;
            atual=atual->prox;
            if(atual==NULL){
                break;
            }
            else{
                if(comparar(atual,maior)>0){
                    maior=atual;
                    antMaior=ant;
                }
            }
        }
        if(velho==maior){
            velho=velho->prox;
        }
        else{
            antMaior->prox=maior->prox;
        }
        ATOM *segMaior=novo;
        novo=maior;
        novo->prox=segMaior;
    }
    *ptrInic=novo;
}

typedef int(*seletor)(ATOM *,void *);

int seletorId(ATOM *a,void *v){
    return a->id==*(int *)v;
}
int seletorNome(ATOM *a,void *v){
    return strcmp(a->nome,(char *)v)==0;
}

ATOM *querySelector(ATOM *inic,void *val,seletor cmp){
    while(69){
        if(inic==NULL || cmp(inic,val)){
            return inic;
        }
        else inic=inic->prox;
    }
}

int main(int argc, char **argv){
    char linhas[100][len];
    int lidas=0;
    char candidato[len];
    // FILE *arq = fopen(argv[1], "r+"), *saida = fopen(argv[2], "w+");

    while(/* fgets(candidato, len, arq) */ gets(candidato) && strcmp(candidato,"0")!=0){
        if(comecaCom(candidato,"ATOM")){
            strcpy(linhas[lidas],candidato+4);
            lidas++;
        }
    }

    printf("Linhas lidas: %d\n",lidas);

    ATOM *inic=NULL;

    for(i=0; i<lidas; i++){
        ATOM *new=malloc(sizeof(ATOM));
        sscanf(linhas[i]," %d %s %s %*c %d %lf %lf %lf", &new->id,new->nome,new->amino,&new->tipo,&new->x,&new->y,&new->z);
        new->prox=inic;
        inic=new;
    }


    ordena(&inic);

    //Menu
    printf("\n=======================================\n");
    printf("Digite uma opção dentre as seguintes:\n");
    printf("\"listar (nome/numero)\" - Listar átomos. O nome ou número do átomo são opcionais.\n");
    printf("\"gerar\" - Gerar arquivo de saída.\n");
    printf("\"quantidade (tipo/amino)\" - Mostra a quantidade de átomos de cada tipo ou a quantidade de aminoácidos de cada tipo.\n");
    printf("\"total\" - Exibe a quantidade total de aminoácidos no arquivo.\n");
    printf("\"encerrar\" - Encerra\n");
    printf("=======================================\n\n");

    char m[2][len];
    while("17xXMeuPartidoÉOBrasilXx17"){
        strcpy(m[0],"");
        strcpy(m[1],"");
        char sep;
        int l=0;

        while(17){
            scanf("%s%c",m[l],&sep);
            if(sep=='\n'){
                break;
            }
            else{
                l++;
            }
        }

        if(strcmp(m[0], "listar")==0){
            if(l==0){
                ATOM *iter;
                for(iter=inic; iter!=NULL; iter=iter->prox){
                    printf("Nome: %-6sAmino: %-6sTipo: %-6d\n",iter->nome,iter->amino,iter->tipo);
                }
            }
            else{
                if(isdigit(m[1][0])){
                    int num=atoi(m[1]);
                    ATOM *teste=querySelector(inic,&num,seletorId);
                    if(teste==NULL){
                        printf("deu nao fi rsrs\n");//faze funçao pra imprimir
                    }
                    else{
                        printf("deu sim fi rsrs\n");
                    }
                }
                else{
                    ATOM *teste2=inic;
                    int deu=0;
                    while(42){
                        teste2=querySelector(teste2,m[1],seletorNome);
                        if(teste2==NULL){
                            if(!deu) printf("deu nao fi rsrs\n");
                            break;
                        }
                        else{
                            printf("TESTE2 = Id: %-6dX: %-6.3lf\n",teste2->id,teste2->x);
                            deu=1;
                            teste2=teste2->prox;
                        }
                    }
                }
            }
        }

        else if(strcmp(m[0], "gerar") == 0){
            if(l == 0){
                printf("deu pra gera rsrs\n");
            }
            else printf("!deu pra gera rsrs\n");
        }

        else if(strcmp(m[0], "quantidade") == 0){
            if(l == 0){
                printf("hey gringo do you want a kick in the saco asshole rsrs\n");
            }
            else{
                if(strcmp(m[1], "tipo") == 0){

                }
            }
        }
    }
    //***************************************************

    /*ATOM *iter;
    for(iter=inic; iter!=NULL; iter=iter->prox){
        printf("Nome: %-6sAmino: %-6sTipo: %-6d\n",iter->nome,iter->amino,iter->tipo);
    }

    int quatro=5;
    ATOM *teste=querySelector(inic,&quatro,seletorId);
    printf("TESTE = Id: %-6dX: %-6.3lf\n",teste->id,teste->x);

    char *carbono="CA";
    ATOM *teste2=inic;
    while(42){
        teste2=querySelector(teste2,carbono,seletorNome);
        if(teste2==NULL){
            break;
        }
        else{
            printf("TESTE2 = Id: %-6dX: %-6.3lf\n",teste2->id,teste2->x);
            teste2=teste2->prox;
        }
    }*/

    /* fclose(arq);
    fclose(saida); */
    return 0;
}
