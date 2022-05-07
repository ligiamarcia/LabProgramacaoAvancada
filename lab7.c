//Laboratório de Programação Avançada
// Laboratório 7
// Assunto: Arquivos e Memória II
// Aluna: Lígia Márcia do Nascimento Teixeira

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


struct chunk {
    int tamanho;
    char tipo[4];
}__attribute__((packed));

struct chunk_IHDR {
    int width;
    int height;
    char bit_depth;
    char color_type;
    char compression_method;
    char filter_method;
    char interface_method;
}__attribute__((packed));

void main(int argc, char const *argv[]) {

    struct chunk* chunk = malloc(sizeof(struct chunk));
    struct chunk_IHDR* png_chunk_ihdr = malloc(sizeof(struct chunk_IHDR));

    FILE *png_file = fopen(argv[1], "rb");

    fseek(png_file, 8, SEEK_CUR);

    int i=0;
    while (!feof(png_file)) {
        fread(chunk, sizeof(struct chunk), 1, png_file);
        printf("Lendo chunk %d:\n", i++);

        printf("    --> Tamanho: %d\n", ntohl(chunk->tamanho));
        printf("    --> Tipo: %.4s\n", chunk->tipo);

        if(strcmp(chunk->tipo, "IHDR") == 0) {
            fread(png_chunk_ihdr, sizeof(struct chunk_IHDR), 1, png_file);
            printf("        --> Largura: %d\n", ntohl(png_chunk_ihdr->width));
            printf("        --> Altura: %d\n", ntohl(png_chunk_ihdr->height));
            fseek(png_file, 4, SEEK_CUR);
        }
        else if (strcmp(chunk->tipo, "IEND") == 0) {
            break;
        }
        else {
            fseek(png_file, ntohl(chunk->tamanho) + 4, SEEK_CUR);
        }
    }
    free(chunk);
    free(png_chunk_ihdr);
    fclose(png_file);
}