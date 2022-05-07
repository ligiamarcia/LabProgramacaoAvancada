//Laboratório de Programação Avançada
// Laboratório 8
// Assunto: Arquivos e Memória III
// Aluna: Lígia Márcia do Nascimento Teixeira


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char const *argv[]){

    FILE *mpeg_file = fopen(argv[1], "rb");
    unsigned char bytes[50];

    while (!feof(mpeg_file)) {
        fread(bytes, 1, 3, mpeg_file);
        if (feof(mpeg_file)){
            break;
        }
        if (memcmp(bytes, "\x00\x00\x01", 3) != 0) {
            fseek(mpeg_file, -2, SEEK_CUR);
            continue;
        }
        fread(bytes, 1, 1, mpeg_file);

        if (bytes[0] == 0xba) {
            printf("--> Código: ba -- Pack\n");
        } 
        else if (bytes[0] == 0xbb) {
            printf("--> Código: bb -- System\n");
        }
        else if (bytes[0] == 0xb3) {
            printf("--> Código: b3 -- Sequence Header -- ");
            fread(bytes, 1, 4, mpeg_file);
            printf("Width = %u, ", (bytes[0] << 4) + (bytes[1] >> 4));
            printf("Height = %u ", ((bytes[1] & 0x0f) << 8) + bytes[2]);
            printf("-- Frame rate = ");

            switch (bytes[3] & 0x0f) {
                case 1:
                    printf("23.976fps\n");
                    break;
                case 2:
                    printf("24.000fps\n");
                    break;
                case 3:
                    printf("25.000fps\n");
                    break;
                case 4:
                    printf("29.970fps\n");
                    break;
                case 5:
                    printf("30.000fps\n");
                    break;
                case 6:
                    printf("50.000fps\n");
                    break;
                case 7:
                    printf("59.940fps\n");
                    break;
                default:
                    printf("60.000fps\n");
                    break;
            }
        }     
        else if (bytes[0] == 0xb8) {
            printf("--> Código: b8 -- Group of Pictures\n");
        }   
        else if (bytes[0] == 0) {
            printf("--> Código: 00 -- Picture -- ");
            fread(bytes, 1, 2, mpeg_file);
            printf("Tipo = ");

            if ((bytes[1] & 0x38) >> 3 == 1) printf("I\n");
            else if ((bytes[1] & 0x38) >> 3 == 2) printf("P\n");
            else printf("B\n");
        }
        else if (bytes[0] > 0 && bytes[0] <= 0xaf) {
            printf("--> Código: %.2x -- Slice\n", bytes[0]);
        }
        else if (bytes[0] >= 0xc0 && bytes[0] <= 0xdf) {
            printf("--> Código: %.2x -- Packet Video\n", bytes[0]);
        }
        else if (bytes[0] >= 0xe0 && bytes[0] <= 0xef) {
            printf("--> Código: %.2x -- Packet Audio\n", bytes[0]);
        }

    }
    fclose(mpeg_file);
}