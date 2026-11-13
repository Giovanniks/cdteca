#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "include/albuns.h"
#include "include/musica.h"
#include "include/artistas.h"
#include "include/curtidas.h"

void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("         CDTECA PESSOAL - MINHA COLEÇÃO MUSICAL       \n");
    printf("======================================================\n");
}


void limparTela() {
    #ifdef _WIN32
        system("cls");   // Para Windows
    #else
        system("clear"); // Para Linux
    #endif
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    
    carregarAlbunsCSV();
    carregarMusicasCSV();
    carregarArtistasCSV();
    carregarCurtidasCSV();

    int opcaoPrincipal = 0;

    do {
	    if (opcaoPrincipal >= 0 && opcaoPrincipal <= 4) {
            limparTela();
    }
	    exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA DO SISTEMA:\n");
        printf("1. Módulo de álbuns / CDs (Giovanni)\n");
        printf("2. Módulo de Músicas / Faixas (Vinicius)\n");
        printf("3. Módulo de Artistas / Bandas (Alan)\n");
        printf("4. Módulo de Curtidas e Relatórios (Giovanni)\n");
        printf("0. Encerrar o Sistema\n");
        printf("------------------------------------------------------\n");
        printf("Digite a opção desejada: ");
        scanf("%d", &opcaoPrincipal);

        switch (opcaoPrincipal) {
            case 1:
                moduloAlbuns();
                break;
            case 2:
                moduloMusicas();
                break;
            case 3:
                moduloArtistas();
                break;
            case 4:
                moduloCurtidasRelatorios();
                break;
            case 0:
                printf("\nEncerrando o sistema CDteca Pessoal... Até logo!\n");
                break;
            default:
                 printf("\n[ALERTA] Opção inváliida! Digite um número de 0 a 4.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
