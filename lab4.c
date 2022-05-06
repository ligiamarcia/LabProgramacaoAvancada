// Laboratório 4, Laboratório de Programação Avançada
// Assunto: Eventos Discretos
// Aluna: Lígia Márcia do Nascimento Teixeira
// Este código possui um arquivo de texto de entrada "testeLab4.txt"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int tamanho;
double comunicacao;

typedef struct evento_t{
    double tempo;
    int alvo;
    int tipo;
}evento_t;

typedef struct lista_eventos_t{
    evento_t *evento;
    struct lista_eventos_t * proximo;
}lista_eventos_t;


typedef struct no_t{
   int id; 
   double pos_x;
   double pos_y;
   bool pacote_enviado;
}no_t;


//Tipo Lista de nós
typedef struct lista_vizinhos_t{
    no_t *no;
    struct lista_vizinhos_t *vizinhos;
}lista_vizinhos_t;


evento_t* criar_evento(double tempo, int alvo, int tipo){
    evento_t *aux = (evento_t*) malloc(sizeof(evento_t));
    
    if(aux != NULL){
        aux->tempo =  tempo;
        aux->alvo = alvo;
        aux->tipo = tipo;
    }
    
    
    return aux;
}



//Adicionando no inicio
bool lista_eventos_adicionar_inicio(evento_t* evento, lista_eventos_t **lista){
    lista_eventos_t *aux = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));

    aux->evento = evento;
    aux->proximo = *lista;
    *lista = aux;

    return true;
}
//Adicionando ordenadamente
bool lista_eventos_adicionar_ordenado(evento_t* evento, lista_eventos_t **lista){
    lista_eventos_t *aux = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));
    lista_eventos_t *novo_evento = (lista_eventos_t*)malloc(sizeof(lista_eventos_t));

    aux = *lista;
    novo_evento->evento = evento;
    novo_evento->proximo = NULL;

    if(aux == NULL){
        *lista = novo_evento;
    }else if(evento->tempo < aux->evento->tempo){
        lista_eventos_adicionar_inicio(evento, lista);
        return true;
    }else{
        while(aux->proximo != NULL && aux->proximo->evento->tempo < evento->tempo){
            aux = aux->proximo;
        }
        novo_evento->proximo = aux->proximo;
        aux->proximo = novo_evento;
        return true;
    }
}


//Adicionar vizinhos na lista
bool lista_vizinhos_adicionar(no_t* no, lista_vizinhos_t **lista){
    lista_vizinhos_t *aux = (lista_vizinhos_t*)malloc(sizeof(lista_vizinhos_t));

    aux->no = no;
    aux->vizinhos = *lista;
    *lista = aux;
    return true;
}

//Imprimindo a lista de vizinhos
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


void simulacao_iniciar(lista_eventos_t* l_eventos, lista_vizinhos_t** grafo){

    lista_eventos_t *aux = l_eventos;
    double tempo;

    while(aux!= NULL){
        evento_t *prim_evento = aux->evento;
        l_eventos = aux->proximo;

        printf("[%3.6f] Nó %d recebeu pacote.\n", prim_evento->tempo, prim_evento->alvo);
        if(grafo[prim_evento->alvo]->no->pacote_enviado != true){
          lista_vizinhos_t *aux_vizinhos = grafo[prim_evento->alvo]->vizinhos;
            while(aux_vizinhos != NULL){
               printf("\t--> Repassando pacote para o nó %d ...\n", aux_vizinhos->no->id);
                tempo = prim_evento->tempo + (0.1 + (grafo[aux_vizinhos->no->id]->no->id * 0.01));
                evento_t *evento = criar_evento(tempo, grafo[aux_vizinhos->no->id]->no->id, 1);
                lista_eventos_adicionar_ordenado(evento, &aux);
                aux_vizinhos = aux_vizinhos->vizinhos;
            }
            grafo[prim_evento->alvo]->no->pacote_enviado = true;
        }
         aux = aux->proximo;
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
            no->pacote_enviado = false;
            lista_vizinhos_adicionar(no, &grafo[i]);
            i++;
            no = (no_t*)malloc(sizeof(no_t));               
        }
        grafo_atualizar_vizinhos(tamanho, comunicacao, grafo);
        //grafo_imprimir(tamanho, grafo);
    }

    lista_eventos_t *lista = NULL;
    evento_t *event = criar_evento(1.0, grafo[0]->no->id, 1);

    lista_eventos_adicionar_ordenado(event, &lista);

    simulacao_iniciar(lista, grafo);

    fclose(arq);
    return 0;
}