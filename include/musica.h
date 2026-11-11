// Arquivo: musica.h | Autor: Integrante B (Vinicius- (47511818))
#ifndef MUSICAS_H
#define MUSICAS_H

#include <stdio.h>
#include <string.h>

#define MAX_MUSICAS 50

// ----------------------------------------------------------------------------
// 1. ESTRUTURA E ARRAYS GLOBAIS
// ----------------------------------------------------------------------------
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
// 2. PERSISTÊNCIA: Salva todo o vetor no arquivo musicas.csv
// ----------------------------------------------------------------------------
void salvarMusicasCSV() {
    int i;
    FILE *arq = fopen("data/musicas.csv", "w"); 
    
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar data/musicas.csv!\n");
        return;
    }
    for (i = 0; i < totalMusicas; i++) {
        fprintf(arq, "%d;%s;%.2f;%d;%d\n",
                listaMusicas[i].idMusica,
                listaMusicas[i].nomeMusica,
                listaMusicas[i].duracaoMinutos,
                listaMusicas[i].idAlbumPertencente,
                listaMusicas[i].numeroFaixa);
    }
    fclose(arq);
}

// ----------------------------------------------------------------------------
// 3. PERSISTÊNCIA: Carrega os dados do arquivo musicas.csv ao abrir o programa
// ----------------------------------------------------------------------------
void carregarMusicasCSV() {
    FILE *arq = fopen("data/musicas.csv", "r");
    if (arq == NULL) return;

    totalMusicas = 0;
    while (totalMusicas < MAX_MUSICAS &&
           fscanf(arq, "%d;%39[^;];%f;%d;%d\n",
                  &listaMusicas[totalMusicas].idMusica,
                  listaMusicas[totalMusicas].nomeMusica,
                  &listaMusicas[totalMusicas].duracaoMinutos,
                  &listaMusicas[totalMusicas].idAlbumPertencente,
                  &listaMusicas[totalMusicas].numeroFaixa) == 5) {
        totalMusicas++;
    }
    fclose(arq);
}

// ----------------------------------------------------------------------------
// 4. FUNÇÃO CHAVE-MESTRA: Retorna o índice onde o ID está, ou -1 se não existir
// ----------------------------------------------------------------------------
int buscarIndiceMusica(int idProcurado) {
    int i;
    for (i = 0; i < totalMusicas; i++) {
        if (listaMusicas[i].idMusica == idProcurado) return i;
    }
    return -1;
}

// ----------------------------------------------------------------------------
//5- SUBFUNÇÃO DE CADASTRO
// ----------------------------------------------------------------------------
void cadastrarMusica(){
    int id;
    if (totalMusicas >= MAX_MUSICAS) {
        printf("\n[ERRO] Limite de 50 musicas atingido!\n");
        break;
    }
    printf("\n--- [CADASTRO DE NOVA MÚSICA] ---\n");
    printf("\nDigite o ID da nova musica: ");
    scanf("%d", &id);
    if (buscarIndiceMusica(id) != -1) {
        printf("[ERRO] Ja existe uma musica com o ID %d!\n", id);
        return;
    }
    listaMusicas[totalMusicas].idMusica = id;
    printf("Nome da musica (com espaços):  ");
    scanf(" %39[^\n]", listaMusicas[totalMusicas].nomeMusica);
    printf("Duracao em minutos (ex: 3.5): ");
    scanf("%f", &listaMusicas[totalMusicas].duracaoMinutos);
    printf("ID do album pertencente: ");
    scanf("%d", &listaMusicas[totalMusicas].idAlbumPertencente);
    printf("Numero da faixa no album: ");
    scanf("%d", &listaMusicas[totalMusicas].numeroFaixa);
    
    totalMusicas++;
    salvarMusicasCSV();
    printf("\n[SUCESSO] Musica cadastrada com sucesso!\n");
    break;
}
}

// ----------------------------------------------------------------------------
// 6. SUBFUNÇÃO DE LISTAGEM
// ----------------------------------------------------------------------------
void listarMusicas(){
    int i;
    printf("\n--- CATALOGO DE MÚSICAS (%d itens) ---\n", totalMusicas);
    if (totalMusicas == 0) {
        printf("Nenhuma musica cadastrada.\n");
        return;
    }
     for (int i = 0; i < totalMusicas; i++) {
         printf("\nID: %d\n", listaMusicas[i].idMusica);
         printf("Nome: %s\n", listaMusicas[i].nomeMusica);
         printf("Duracao: %.2f min\n", listaMusicas[i].duracaoMinutos);
         printf("ID do Album: %d\n", listaMusicas[i].idAlbumPertencente);
         printf("Numero da Faixa: %d\n", listaMusicas[i].numeroFaixa);
         printf("------------------------------------\n");
     }
}

// ----------------------------------------------------------------------------
//7- SUBFUNÇÃO DE DE BUSCA TEXTUAL COM STRSTR
//----------------------------------------------------------------------------
void buscarMusicaPorNome(){
    int i;
    int encontradas = 0;
    char termo[30];

    printf("\nDigite parte do nome da musica para buscar: ");
    scanf(" %29[^\n]", termo);
    
    for (i = 0; i < totalMusicas; i++) {
        if (strstr(listaMusicas[i].nomeMusica, termo) != NULL) {
            printf(" -> Encontrada: [%d] %s (%.2f min) - Faixa %d\n",
                   listaMusicas[i].idMusica, 
                   listaMusicas[i].nomeMusica, 
                   listaMusicas[i].duracaoMinutos,
                   listaMusicas[i].numeroFaixa);
            encontradas++;
        }
    }
    if (encontradas == 0) {
        printf("[INFO] Nenhuma musica encontrada com o termo '%s'.\n", termo);
    }
}


    

// ----------------------------------------------------------------------------
// MÓDULO 3: PERSPECTIVA DE MÚSICAS / FAIXAS
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
                cadastrarMusica();
                break;
        }
                
                
            case 2:
                listarMusicas();
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
