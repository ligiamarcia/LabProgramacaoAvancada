// Laboratório 2, Laboratório de Programação Avançada
// Assunto: Tabelas Hash
// Aluna: Lígia Márcia do Nascimento Teixeira
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



int tamanho_hash;

typedef struct pessoa_t{
    char nome[50];
    long long int cpf;
    int idade;
}pessoa_t;

//Tipo Lista de pessoas
typedef struct lista_pessoas_t{
   pessoa_t *pessoa;
   struct lista_pessoas_t *proximo;
}lista_pessoas_t;


//→ Adiciona uma pessoa a uma lista encadeada (similar ao TP1)
bool lista_pessoas_adicionar(pessoa_t *pessoa, lista_pessoas_t **lista){
    lista_pessoas_t *aux = (lista_pessoas_t*)malloc(sizeof(lista_pessoas_t));
    aux->pessoa = pessoa;
    aux->proximo = *lista;
    *lista = aux;
    return true;
}




//→ Imprime as pessoas em uma lista encadeada (similar ao TP1, mas no formato especificado)
void lista_pessoas_listar(lista_pessoas_t *lista){
    while(lista!=NULL) {
        printf("%s %lld %d\n", lista->pessoa->nome, lista->pessoa->cpf, lista->pessoa->idade);
        lista = lista->proximo;
    }
    printf("\n");
}





//Função Hash
//Aloca memória para um vetor de ponteiros para listas encadeadas e faz cada ponteiro de lista (elemento do vetor) apontar para nulo.
//tabela_hash_t pode ser definido como: typedef lista_pessoas_t** tabela_hash_t;  
void tabela_hash_pessoas_criar(lista_pessoas_t *tabela_hash[]){   
   int i;
   if(tabela_hash != NULL){
       for(i = 0; i < tamanho_hash; i++){
            tabela_hash[i] = NULL;
       }
   }
}


//Calcula a Função Hash de uma pessoa (pessoa->cpf % tabela_hash_tam).
int tabela_hash_pessoas_funcao(pessoa_t *pessoa){
    return pessoa->cpf%tamanho_hash;
}

//Adiciona a pessoa na lista encadeada localizada na posição do vetor especificado pela função acima.
bool tabela_hash_pessoas_adicionar(pessoa_t *pessoa, lista_pessoas_t **tabela_hash){
    
    if(tabela_hash == NULL){
        printf("\nEntrou aqui\n");
        return false;
    }    
    int pos = tabela_hash_pessoas_funcao(pessoa);     
    lista_pessoas_adicionar(pessoa, &tabela_hash[pos]);    
    return true;
}

//Para cada posição do vetor, executa a função lista_pessoas_listar.
void tabela_hash_pessoas_listar(lista_pessoas_t** tabela_hash){
    int i = 0;
    while(i < tamanho_hash){
        printf("POSIÇÃO %d DA TABELA HASH: \n", i);
        lista_pessoas_listar(tabela_hash[i]);
        i++;
    }    
    printf("\n");
}



pessoa_t* criar_pessoa(char nome[], long long int cpf, int idade){
    pessoa_t *aux = (pessoa_t*) malloc(sizeof(pessoa_t));
    
    if(aux != NULL){
        strcpy(aux->nome, nome);
        aux->idade = idade;
        aux->cpf = cpf;
    }       
    return aux;
}



int main(int argc, char **argv){
FILE *arq;

pessoa_t *aux_pessoa;

char nome[50];
long long int cpf;
int idade;

    if(argc < 3){
        printf("Erro\n Por favor, informe o tamanho da tabela hash e o arquivo txt\n");
        return 1; 
    }

    sscanf(argv[1], "%d", &tamanho_hash);

    lista_pessoas_t *tabela_hash[tamanho_hash];
    tabela_hash_pessoas_criar(tabela_hash);

    arq = fopen(argv[2],"r");

    if (arq == NULL){
        printf("Houve problemas na criação do arquivo\n");
    }else{
        while((fscanf(arq, "%50[^\t]\t%lld\t%d\n",nome,  &cpf, &idade)) != EOF){
            aux_pessoa = criar_pessoa(nome, cpf, idade);
            tabela_hash_pessoas_adicionar(aux_pessoa, tabela_hash);            
        }
        tabela_hash_pessoas_listar(tabela_hash);
    }  

    return 0;
}