// Laboratório 6, Laboratório de Programação Avançada
// Assunto: Grafos
// Aluna: Lígia Márcia do Nascimento Teixeira
// Este código possui um arquivo de texto de entrada "testeLab6.zip"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct zip_file_hdr {
    int signature;
    short version;
    short flags;
    short compression;
    short mod_time;
    short mod_date;
    int crc;
    int compressed_size;
    int uncompressed_size;
    short name_length;
    short extra_field_length;
} __attribute__ ((packed));

int main(int argc, char *argv[]){
    FILE *zip_file = fopen(argv[1], "rb");
    struct zip_file_hdr *file_hdr = malloc(sizeof(struct zip_file_hdr));
    int i = 1;
    

    while(zip_file){ //Enquanto não chega no fim do arquivo
        fread(file_hdr, sizeof(struct zip_file_hdr), 1, zip_file);
        if(file_hdr->signature == 0x04034b50){
            printf("Arquivo %d ..\n", i);
            char* arq_nome = malloc(file_hdr->name_length+1);
            fread(arq_nome, sizeof(char), file_hdr->name_length, zip_file);
            arq_nome[file_hdr->name_length+1] = '\0';

            printf("-->Nome do arquivo: %s\n", arq_nome);
            printf("-->Tamanho compactado: %d\n",file_hdr->compressed_size);
            printf("-->Tamanho descompactado: %d\n", file_hdr->uncompressed_size);

            free(arq_nome);
            fseek(zip_file, file_hdr->extra_field_length + file_hdr->compressed_size, SEEK_CUR);
        }else{
            return 0;
        }
        i++;
    }
    fclose(zip_file);   
}
