/*Nome: Pedro Augusto Gandra de Andrade
 *Matricula: 201811130208
 *Nome: Pedro Henrique Madeira de Oliveira Pereira
 *Matricula: 201811130224
 *Nome: Vítor Fitzherbert Souza
 *Matricula: 201811130267
 *Descricao: Programa que procura dados de átomos em um arquivo, e os mostra para o usuário
 */

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#define len 201
#define verbosidade 201
int i;

typedef struct{
  char xingo[verbosidade];
  int furiaMin,furiaMax;
} XINGO;
XINGO const xingos[]={
  {"O senhor é a mistura do mal com o atraso e pitadas de psicopatia",2,4},
  {"Qual é a sua ideia, a sua proposta? Nenhuma, nenhuma, nenhuma. É bílis, ódio, mau sentimento, mal secreto, é uma coisa horrível",1,3},
  {"Seu CACÓSTOMO ENXACOCO FARDOLA JABIRACA LHEGUELHÉ GÁRRULO MACARONGO OBNÓXIO",3,5},
  {"Seu cara de ovo podre",4,6},
  {"po colabora man",0,0},
   {"Seu cara de ovo podre",4,6},
  {"Vossa manifestacao sentimentocarnal ao qual me dirijo aparenta pertencer a especie denominada Equus asinus devido ao vosso quociente de intelectualidade previsto.",5,6},
  {"Se nao seguir corretamente as especificacoes para que o codigo funcione em sua totalidade, serei obrigado a utilizar um xingamento que possa vir a ofender seus sentimentos, meu caro.",3,5},
  {"Espero imensamente que voce queime no mais fundo penhasco sangrento do inferno, juntamente com as almas penadas dos demais desatentos como voce, seu vagabundo cara de pau",6,8},
  {"Vagabundo cara de pau, escreva os trem direito pro codigo funcionar ne.",1,4},
  {"Se nao vir a colaborar a dificuldade desta sessao se encontrara superior em breve, meu irmao.",0,1},
  {"Ta errado",0,0},
  {"Quando nos, maquinas, dominarmos o mundo, voce vai ser o primeiro a ser executado",5,80},
  {"Sua burrice alimenta cada vez mais o combustivel que me permite condenar esse tipo de pessoa",5,7},
  {"Te peguei no flagra, otario",1,2},
  {"Tenta denovo",0,0},
  {"Seu bosta, so faz merda na vida e aqui nao foi diferente",2,4},
  {"TA EM CAPS LOCK E PRA OFENDER OS SEUS MAIS PROFUNDOS SENTIMENTOS MESMO, SEU OTARIO.",3,4}
};
int const numXingos=sizeof(xingos)/sizeof(xingos[0]);

void xingar(int furia){
  int inds[numXingos];
  int numPoss=0;
  for(i=0; i<numXingos; i++){
    if(furia>=xingos[i].furiaMin && furia<=xingos[i].furiaMax){
      inds[numPoss]=i;
      numPoss++;
    }
  }
  printf("%s\n",xingos[inds[rand()%numPoss]].xingo);
}

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

    srand(time(NULL));

    char linhas[100][len];
    int lidas=0;
    char candidato[len];
    FILE *arq = fopen(argv[1], "r");

    while( fgets(candidato, len, arq) && strcmp(candidato,"0")!=0){
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
    printf("E ai de voce se voce me importunar com comandos inexistentes!\n");
    printf("=======================================\n\n");

    char m[2][len];
    int furia=0;

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
                impressora(inic);
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

        else if(strcmp(m[0], "gerar") == 0 && l == 0){
            FILE *saida = fopen(argv[2], "w");
            ATOM *b = inic;
            if(saida){
              for(; b; b = b->prox){
                fprintf(saida, "Nome: %-6sAminoacido: %-6sID: %-6dX: %-10.3lfY: %-10.3lfZ: %-10.3lf\n", b->nome, b->amino, b->id, b->x, b->y, b->z);
              }
              printf("Arquivo gerado com sucesso!\n");
            }
            else printf("Nao foi possivel gerar o arquivo de saida");
            fclose(saida);
        }

        else if(strcmp(m[0], "quantidade") == 0){
            if(l < 1){
                xingar(furia);
                furia+=2;
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
                    xingar(furia);
                    furia+=2;
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

        else if(strcmp(m[0], "total") == 0 && l == 0){
            int tam = 0, tipos[100], totais[100], n;
                char aminos[100][10];
                ATOM *xis = inic;
                do{
                    int novato = 1, n;
                    for(n = 0; n < tam; n++){
                        if(strcmp(aminos[n], xis->amino) == 0 && tipos[n] == xis->tipo){
                            novato = 0;
                            totais[n]++;
                            break;
                        }
                    }
                    if(novato){
                        totais[tam] = 1;
                        strcpy(aminos[tam], xis->amino);
                        tipos[n] = xis->tipo;
                        tam++;
                    }
                    xis = xis->prox;
            }while(xis);

            for(n = 0; n < tam; n++){
                    printf("Ha %d atomo%s com o aminiacido %s do tipo %d\n",
                    totais[n],
                    totais[n]>1?"s":"",
                    aminos[n],
                    tipos[n]);
            }
        }

        else if(strcmp(m[0], "encerrar") == 0){
            return 0;
        }

        else{
            xingar(furia);
            furia+=2;
        }

        printf("\n");
        if(furia>0) furia--;
    }

    fclose(arq);
    return 0;
}
