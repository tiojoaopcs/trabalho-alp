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
int seletorAmino(ATOM *a,void *v){
    return strcmp(a->amino,(char *)v)==0;
}

ATOM *querySelector(ATOM *inic,void *val,seletor cmp){
    while(69){
        if(inic==NULL || cmp(inic,val)){
            return inic;
        }
        else inic=inic->prox;
    }
}

//FUNÇÃO PARA IMPRIMIR
void print1(ATOM *a){
    printf("Nome: %-6sAminoacido: %-6sTipo: %-6dID: %-6d\n", a->nome, a->amino, a->tipo, a->id);
}
void impressora(ATOM *lista){
    for(; lista!=NULL; lista=lista->prox){
        print1(lista);
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


    // Aqui ordena por Select Sort
    ordena(&inic);

    //Menu
    printf("\n=======================================\n");
    printf("Digite uma opcao dentre as seguintes:\n");
    printf("\"listar (nome/numero)\" - Listar atomos. O nome ou numero do atomo sao opcionais.\n");
    printf("\"gerar\" - Gerar arquivo de saida.\n");
    printf("\"quantidade (nome X/amino XYZ)\" - Mostra a quantidade de atomos de cada tipo ou a quantidade de aminoacidos de cada tipo.\n");
    printf("\"total\" - Exibe a quantidade total de aminoacidos no arquivo.\n");
    printf("\"encerrar\" - Encerra\n");
    printf("=======================================\n\n");

    char m[2][len];

    while(";-;"){
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
        printf("\n");
        if(strcmp(m[0], "listar")==0){
            if(l==0){
                ATOM *aux;
                aux = inic;
                ordena(&aux);
                impressora(aux);
            }
            else{
                if(isdigit(m[1][0])){
                    int num=atoi(m[1]);
                    ATOM *teste=querySelector(inic,&num,seletorId);
                    if(teste==NULL){
                        printf("Nao foi possivel encontrar o ID %s\n", m[1]);
                    }
                    else{
                        print1(teste);
                    }
                }
                else{
                    ATOM *teste2=inic;
                    int deu=0;
                    while(42){
                        teste2=querySelector(teste2,m[1],seletorNome);
                        if(teste2==NULL){
                            if(!deu) printf("Nao foi possivel listar os atomos com o nome \"%s\"\n", m[1]);
                            break;
                        }
                        else{
                            print1(teste2);
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
            if(l < 1){
                printf("Poucos argumentos para listar a quantidade. Digite \"quantidade + nome + [nome]\" ou \"quantidade + amino + [aminoacido]\"\n");
            }

            else{
                int ok;
                if(strcmp(m[1],"nome")==0){
                    ok=1;
                }
                else if(strcmp(m[1],"amino")==0){
                    ok=2;
                }
                else{
                    ok=0;
                    printf("po colabora man\n");
                }

                if(ok){
                    if(l==1){
                        int size=0;
                        char dados[100][6];
                        int qtds[100];
                        ATOM *li=inic;
                        
                        do{
                            int eNovo=1;
                            for(i=0; i<size; i++){
                                char const *str=ok==1? li->nome: li->amino;
                                if(strcmp(dados[i],str)==0){
                                    qtds[i]++;
                                    eNovo=0;
                                    break;
                                }
                            }

                            if(eNovo){
                                qtds[size]=1;
                                strcpy(dados[size],ok==1? li->nome: li->amino);
                                size++;
                            }

                            li=li->prox;
                        }while(li!=NULL);

                        char const *str2=ok==1? "nome": "aminoacido";
                        for(i=0; i<size; i++){
                            printf("Ha %d atomo%s com o %s %s\n",
                                qtds[i],
                                qtds[i]>1? "s": "",
                                str2,
                                dados[i]);
                        }
                    }

                    else{
                        seletor func=ok==1? seletorNome: seletorAmino;
                        ATOM *qtd = querySelector(inic, m[2], func);
                        if(qtd == NULL) printf("Nao foi possivel encontrar \"%s\"\n", m[2]);
                        else{
                            int contador=1;
                            while(666){
                                qtd=querySelector(qtd->prox,m[2],func);
                                if(qtd!=NULL) contador++;
                                else break;
                            }
                            printf("Ha %d atomo%s com o %s %s\n",
                                contador,
                                contador>1? "s": "",
                                ok==1? "nome": "aminoacido",
                                m[2]);
                        }
                    }
                }
            }
        }

        else if(strcmp(m[0], "total") == 0){
            
        }

        else if(strcmp(m[0], "encerrar") == 0){
            return 0;
        }

        else{
            printf("comando invalido presta atencao mano\n");
        }

        printf("\n");
    }

    /* fclose(arq);
    fclose(saida); */
    return 0;
}

/*
ENTRADA
ATOM      1  N   GLY A   1      -4.788  -8.935   3.453  1.00 11.53           N
ATOM      2  CA  GLY A   1      -4.218 -10.294   3.312  1.00  9.54           C
ATOM      3  C   GLY A   1      -3.815 -10.534   1.870  1.00  8.53           C
ATOM      4  O   GLY A   1      -4.276  -9.836   0.965  1.00  7.01           O
ATOM      5  N   CYS A   2      -3.045 -11.594   1.654  1.00  7.14           N
ATOM      6  CA  CYS A   2      -2.531 -11.945   0.337  1.00  7.39           C
ATOM      7  C   CYS A   2      -3.485 -11.922  -0.844  1.00  7.12           C
*/
