// 2. Perspectiva do Vinicius(47511818): Gestão de Músicas / Faixas
#ifndef MUSICAS_H
#define MUSICAS_H
#include <stdio.h>
#include <string.h>
#define MAX_MUSICAS 50

struct Musica {
    int idMusica;
    char nomeMusica[40];
    float duracaoMinutos;
    int idAlbumPertencente;
    int numeroFaixa;
};
struct Musica listaMusicas[MAX_MUSICAS];
int totalMusicas = 0;

// ----------------------------------------------------------------------------
// MÓDULO 2: PERSPECTIVA DE MÚSICAS / FAIXAS
// Autor: Integrante B (Vinicius)
// ----------------------------------------------------------------------------

void moduloMusicas() {
    int opcaoMusica;
    do {
        printf("\n--- [MÓDULO 2: GESTÃO DE MÚSICAS (Vinicius)] ---\n");
        printf("1. Cadastrar Nova Música / Faixa\n");
        printf("2. Listar / Buscar Músicas\n");
        printf("3. Alterar Duração ou Número da Faixa\n");
        printf("4. Excluir Música\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma ação: ");
        scanf("%d", &opcaoMusica);

        switch (opcaoMusica) {
            case 1:
              if (totalMusicas >= 50) {
                printf("\n[ERRO] Limite de 50 musicas atingido!\n");
              } else {
                printf("\n--- [CADASTRO DE NOVA MÚSICA] ---\n");
                printf("ID da musica: ");
                scanf("%d", &listaMusicas[totalMusicas].idMusica);
                printf("Nome da musica: ");
                scanf(" %[^\n]", listaMusicas[totalMusicas].nomeMusica);
                printf("Duracao em minutos (ex: 3.5): ");
                scanf("%f", &listaMusicas[totalMusicas].duracaoMinutos);
                printf("ID do album pertencente: ");
                scanf("%d", &listaMusicas[totalMusicas].idAlbumPertencente);
                printf("Numero da faixa no album: ");
                scanf("%d", &listaMusicas[totalMusicas].numeroFaixa);
                totalMusicas++;
                printf("\n[SUCESSO] Musica cadastrada com sucesso!\n");
                break;
              }
                
                
            case 2:
              if (totalMusicas == 0) {
                printf("\n[ERRO] Nenhuma musica cadastrada!\n");
              } else {
                printf("\n--- [LISTA DE MÚSICAS CADASTRADAS] ---\n");
                for (int i = 0; i < totalMusicas; i++) {
                  printf("\nID: %d\n", listaMusicas[i].idMusica);
                  printf("Nome: %s\n", listaMusicas[i].nomeMusica);
                  printf("Duracao: %.2f min\n", listaMusicas[i].duracaoMinutos);
                  printf("ID do Album: %d\n", listaMusicas[i].idAlbumPertencente);
                  printf("Numero da Faixa: %d\n", listaMusicas[i].numeroFaixa);
                  printf("------------------------------------\n");
                }
                break;
              }
            case 3:
              if (totalMusicas == 0) {
                printf("\n[ERRO] Nenhuma musica cadastrada para alterar!\n");
              } else {
                int idBusca;
                int achou = 0;
                printf("\n--- [ALTERAR DADOS DA MÚSICA] ---\n");
                printf("Digite o ID da musica que deseja alterar: ");
                scanf("%d", &idBusca);
                for (int i = 0; i < totalMusicas; i++) {
                  if (listaMusicas[i].idMusica == idBusca) {
                    achou = 1;
                    printf("\nMusica Encontrada: %s\n", listaMusicas[i].nomeMusica);
                    printf("Duracao atual: %.2f min | Faixa atual: %d\n", 
                           listaMusicas[i].duracaoMinutos, listaMusicas[i].numeroFaixa);
                    printf("------------------------------------\n");
                    printf("Digite a nova duracao em minutos: ");
                    scanf("%f", &listaMusicas[i].duracaoMinutos);
                    printf("Digite o novo numero da faixa: ");
                    scanf("%d", &listaMusicas[i].numeroFaixa);
                    printf("\n[SUCESSO] Dados da musica atualizados com sucesso!\n");
            }
        }
                if (!achou) {
                  printf("\n[ERRO] Musica com ID %d nao foi encontrada!\n", idBusca);
        }
                break;
    }
            case 4:
              if (totalMusicas == 0) {
                printf("\n[ERRO] Nenhuma musica cadastrada para excluir!\n");
              } else {
                int idExcluir;
                int achou = 0;
                printf("\n--- [EXCLUIR MÚSICA] ---\n");
                printf("Digite o ID da musica que deseja excluir: ");
                scanf("%d", &idExcluir);
                for (int i = 0; i < totalMusicas; i++) {
                  if (listaMusicas[i].idMusica == idExcluir) {
                    achou = 1;
                    for (int j = i; j < totalMusicas - 1; j++) {
                      listaMusicas[j] = listaMusicas[j + 1];
                }
                    totalMusicas--;
                    printf("\n[SUCESSO] Musica com ID %d removida com sucesso!\n", idExcluir);
                break;
            }
        }

        if (!achou) {
            printf("\n[ERRO] Musica com ID %d nao foi encontrada!\n", idExcluir);
        }
    }
    break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida no Módulo de Músicas!\n");
        }
    } while (opcaoMusica != 0);
}
