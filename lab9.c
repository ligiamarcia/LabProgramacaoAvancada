//Laboratório de Programação Avançada
// Laboratório 9
// Assunto: Arquivos e Memória IV
// Aluna: Lígia Márcia do Nascimento Teixeira

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <netinet/in.h>
void main(int argc, char const *argv[]) {
    FILE *file_entrada = fopen(argv[1], "rb");
    FILE* file_saida;
    int ctam;
    int tamMax;
    tamMax = atoi(argv[2]) * 1000000;
    buffer = (char*) malloc(tamMax);
    file_saida = fopen("video_parte_1.mpg", "w");

    char* buffer;
    int btam;
    char file_name[50];
    int cont=1;
    char bytes[50];
   
    while (true) {
    fread(bytes, 1, 4, file_entrada);
    if (!feof(file_entrada) && memcmp(bytes, "\x00\x00\x01\xB3", 4) != 0) {
      buffer[btam++] = bytes[0];
      fseek(file_entrada, -3, SEEK_CUR);
      continue;
    }
    if (ctam + btam > tamMax) {
      fclose(file_saida);
      snprintf(file_name, 50, "video_parte_%d.mpg", ++cont);
      file_saida = fopen(file_name, "w");
      ctam = 0;
    }
    fwrite(buffer, 1, btam, file_saida);
    ctam += btam;
    btam = 0;
    if (feof(file_entrada)) {
      fclose(file_saida);
      fclose(file_entrada);
      break;
    }
    memcpy(buffer, bytes, 4);  
    bsize = 4;
  }

  free(buffer);
}