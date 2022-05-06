// Laboratório 3, Laboratório de Programação Avançada
// Assunto: Grafos
// Aluna: Lígia Márcia do Nascimento Teixeira
// Este código possui um arquivo de texto de entrada "testeLab3.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



char* concatenar (char c, char word[]){
    int tamanho = strlen(word);
    char *concat = malloc(tamanho+1);
    for(int i=0; i< tamanho; i++){
        concat[i] = word[i];
    }
    concat[tamanho] = c;
    concat[tamanho + 1] = '\0';
    return concat;
}


int main(int argc, char **argv){
    int tamanho_total = 0;
    int tamanho_caract = 0;
    float possibilidades = 0.0;

    tamanho_total = atoi(argv[1]);
    
    char caract[100];
    strcpy(caract, argv[2]);
    tamanho_caract = strlen(caract);

    possibilidades = pow(tamanho_caract, tamanho_total);
    possibilidades = possibilidades + (possibilidades/2);

    char *word = malloc(tamanho_caract);
    int val = 0;
    int j = 0;

    for(int i = 1; i < (int)possibilidades; i++){
        word = "";
        val = i;
        //for(int j = 0; ((j < tamanho_total) && (j<i)); j++){
        while(j<i && j < tamanho_total){
            int ch = (val-1) % tamanho_caract;
            word = concatenar(caract[ch],word);
            val = (val-1) / tamanho_caract;
            j++;
        }
        j=0;
        printf("%s\n", word);
    }
    

}
