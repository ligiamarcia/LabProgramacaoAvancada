// Laboratório 1, Laboratório de Programação Avançada
// Assunto: listas encadeadas
// Aluna: Lígia Márcia do Nascimento Teixeira, 21752477
// Data: 18/02/2021


//importando as bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> //necessário para usar o tipo de dado bool



struct evento_t     //struct para armazenar as informações do evento 
{
    double time;    //tempo
    int target;     //alvo
    int type;       //tipo
};
typedef struct evento_t evento_t;


struct lista_eventos_t
{
    evento_t *evento;
    struct lista_eventos_t *prox;  
};

typedef struct lista_eventos_t lista_eventos_t;

//criação do evento




//listar os eventos, ou seja, mostrar os eventos



//------------------------------------------------------------------------------------------------------//

//questão 1: implementar uma pilha
bool lista_eventos_adicionar_inicio(evento_t *evento, lista_eventos_t **lista){ 
    lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); // Alocar o novo item
    if (item_novo == NULL) {  // Falta memória?
        return false;
    } 


    item_novo->evento = evento; // Seta o novo item
    item_novo->prox = *lista; // O próximo do novo item será a lista
    *lista = item_novo; // Aqui, estamos mudando o ponteiro da lista
    return true;
}

//------------------------------------------------------------------------------------------------------//

//questão 2:função de uma lista, adicionar fim

bool eventos_adicionar_fim(evento_t *evento_t, lista_eventos_t **lista){ //Questão 02 -- fila
    lista_eventos_t *aux = *lista;
    lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); //alocando espaço ;*
    if (item_novo == NULL){
        return false;
    }
    item_novo -> evento = evento_t;
    item_novo -> prox = NULL;
    if (*lista == NULL){
        *lista = item_novo;
    }else{
        while(aux->prox !=NULL ){
            aux = aux->prox;
        }
        aux->prox = item_novo;
    }
}

//------------------------------------------------------------------------------------------------------//

//questão 3: função para adicionar um evento já ordenado

bool lista_eventos_adicionar_ordenado(evento_t *evento, lista_eventos_t **lista){
    lista_eventos_t *item_novo = malloc(sizeof(lista_eventos_t)); // Alocar o novo item
    if (item_novo == NULL) {  // Falta memória?
        return false;
    } 

    if((*lista == NULL)  || ((*lista)->evento->time  >  evento->time)){
        return lista_eventos_adicionar_inicio(evento, lista);
    }else if((*lista)-> prox == NULL){
        return eventos_adicionar_fim(evento,lista);
    }else{
        lista_eventos_t *aux = *lista;

        while ((aux->prox != NULL) && (aux->prox->evento->time   <  evento->time))
        {
            aux = aux -> prox;
        }

        item_novo -> evento = evento;
        item_novo -> prox = aux -> prox;
        aux -> prox = item_novo;

        return true;       
        
    }

}

//------------------------------------------------------------------------------------------------------//

evento_t* criar_evento(double time, int target, int type){
    evento_t *novo_evento = malloc(sizeof(evento_t)); //alocação de espaço para a criação do novo evento
    if (novo_evento == NULL){
        return false;
    }
    novo_evento ->time = time;
    novo_evento ->target = target;
    novo_evento ->type = type;

    return novo_evento;
}


//------------------------------------------------------------------------------------------------------//


void lista_eventos_mostrar_lista(lista_eventos_t *lista){

    lista_eventos_t *aux = lista;
    while ( (aux != NULL)){}
    {
        printf("%3.6f\t %d\t %d\t \n", aux->evento->time, aux->evento->target, aux->evento->type);
        aux = aux->prox;
    }
    
}




//------------------------------------------------------------------------------------------------------//

int main(int argc, char *argv[1]){
    double time;    //tempo
    int target;     //alvo
    int type;       //tipo
    lista_eventos_t *lista = NULL;
    evento_t *evento_aux;


    FILE *arquivo = NULL;       
    arquivo = fopen(argv[1], "r+");     //abrindo arquivo para leitura 
        if(!arquivo){
            printf("Erro \n");
            return 1;
        }
        else{
            while((fscanf(arquivo, "%lf  %d  %d ",&time,&target,&type)) !=EOF){

                printf("Variáveis: %lf \n %d \n %d \n",time, target,type);
                evento_aux = criar_evento(time,target,type);
                //questão 1 --> pilha
                //eventos_adicionar_inicio(evento_aux,&lista);


                //questão 2 --> lista
                //eventos_adicionar_fim(evento_aux,&lista);


                //questão 3 --> inserir ordenado
                lista_eventos_adicionar_ordenado(evento_aux,&lista);

            }
        }
    lista_eventos_mostrar_lista(lista);    
    return 0;
}