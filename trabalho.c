/*Nome: Pedro Augusto Gandra de Andrade
 *Matricula: 201811130208
 *Nome: Pedro Henrique Madeira de Oliveira Pereira  
 *Matricula: 201811130224
 *Nome: Vítor Fitzherbert Souza
 *Matricula: 201811130267
 *Descricao: Programa que lê dois números e imprime a integral dupla da função exponencial da batatinha roxa...
 */

#include <stdio.h>
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

void ordena(ATOM **lista){
    ATOM *aux = *lista;
}

int main(int argc, char **argv){
    char linhas[100][len];
    int lidas=0;
    char candidato[len];    
    FILE *arq = fopen(argv[1], "r+"), *saida = fopen(argv[2], "w+");
    
    while(fgets(candidato, len, arq)){
        printf("while rodando\n");
        if(comecaCom(candidato,"ATOM")){
            strcpy(linhas[lidas],candidato+4);
            lidas++;
        }                        
    }

    printf("Linhas lidas: %d\n",lidas);

    ATOM *inic=NULL;

    for(i=0; i<lidas; i++){
        ATOM *new=malloc(sizeof(ATOM));
        sscanf(linhas[i]," %d %s %s %*c %d %lf %lf %lf", new->id,new->nome,new->amino,new->tipo,new->x,new->y,new->z);
        new->prox=inic;
        inic=new;
    }    
    fclose(arq);
    fclose(saida);
    return 0;
}