// Laboratório 3, Laboratório de Programação Avançada
// Assunto: Grafos
// Aluna: Lígia Márcia do Nascimento Teixeira
// Este código possui um arquivo de texto de entrada "testeLab3.txt"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int tamanho;
double comunicacao;

typedef struct no_t{
   int id; 
   double pos_x;
   double pos_y;
}no_t;


//Tipo Lista de nós
typedef struct lista_vizinhos_t{
    no_t *no;
    struct lista_vizinhos_t *vizinhos;
}lista_vizinhos_t;




//Adicionando vizinhos na lista
bool lista_vizinhos_adicionar(no_t* no, lista_vizinhos_t **lista){
    lista_vizinhos_t *aux = (lista_vizinhos_t*)malloc(sizeof(lista_vizinhos_t));

    aux->no = no;
    aux->vizinhos = *lista;
    *lista = aux;
    return true;
}

//Imprimir lista de vizinhos
void lista_vizinhos_imprimir(lista_vizinhos_t *lista){
    if(lista == NULL){
        printf("Nao ha vizinhos");
    }

    while(lista!=NULL) {
        printf("%d ", lista->no->id);
        lista = lista->vizinhos;
    }
    printf("\n");
}

//Alocando memória para um vetor de nós
void *grafo_criar(lista_vizinhos_t *grafo[]){
   int i;
   if(grafo != NULL){
       for(i = 0; i < tamanho; i++){
            grafo[i] = NULL;
       }
   }
}

//Atualizando lista de vizinhos
void grafo_atualizar_vizinhos(int tam, double comunicacao, lista_vizinhos_t* grafo[]){
     for (int i = 0; i < tamanho; i++){
        for (int j = 0; j < tamanho; j++){
            if (i != j){
                if (sqrt(pow(grafo[i]->no->pos_x - grafo[j]->no->pos_x, 2) + pow(grafo[i]->no->pos_y - grafo[j]->no->pos_y, 2)) < comunicacao){
                    lista_vizinhos_adicionar(grafo[i]->no, &grafo[j]->vizinhos);
                }
            }
        }
    }
}

//Imprimindo o grafo
void grafo_imprimir(int tam, lista_vizinhos_t* grafo[]){
    for(int i = 0; i < tamanho; i++){
        printf("No %d: ", i);
        lista_vizinhos_imprimir(grafo[i]->vizinhos);
    }
}



int main(int argc, char **argv){
FILE *arq;
int i = 0;
int id;
double pos_x;
double pos_y;

    if(argc < 2){
        printf("Erro\n Por favor, informe o tamanho da tabela hash e o arquivo txt\n");
        return 1; 
    }

    arq = fopen(argv[1],"r");

    fscanf(arq, "%d\t%lf", &tamanho, &comunicacao);

    lista_vizinhos_t* grafo[tamanho];
    grafo_criar(grafo);     
    

    no_t *no = (no_t*)malloc(sizeof(no_t));

    if (arq == NULL){
        printf("Problemas na CRIACAO do arquivo\n");
    }else{
        while(fscanf(arq, "%d\t%lf\t%lf\n", &no->id, &no->pos_x, &no->pos_y) != EOF){
            lista_vizinhos_adicionar(no, &grafo[i]);
            i++;
            no = (no_t*)malloc(sizeof(no_t));               
        }
        grafo_atualizar_vizinhos(tamanho, comunicacao, grafo);
        grafo_imprimir(tamanho, grafo);
    }
    fclose(arq);
    return 0;
}