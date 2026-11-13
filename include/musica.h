// Arquivo: musica.h | Autor: Integrante B (Vinicius- (47511818))
#ifndef MUSICAS_H
#define MUSICAS_H

#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_MUSICAS 50

// ----------------------------------------------------------------------------
// 1. ESTRUTURA E ARRAYS GLOBAIS
// ----------------------------------------------------------------------------
struct Musica {
    int idMusica;
    char nomeMusica[40];
    float duracaoMinutos;
    char generoMusica[30];
    int anoLancamento;
};
struct Musica listaMusicas[MAX_MUSICAS];
int totalMusicas = 0;

// ----------------------------------------------------------------------------
// 2. PERSISTﾃ劾CIA: Salva todo o vetor no arquivo musicas.csv
// ----------------------------------------------------------------------------
void salvarMusicasCSV() {
    int i;
    FILE *arq = fopen("data/musicas.csv", "w"); 
    
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar data/musicas.csv!\n");
        return;
    }
    for (i = 0; i < totalMusicas; i++) {
        fprintf(arq, "%d;%s;%.2f;%s;%d\n",
                listaMusicas[i].idMusica,
                listaMusicas[i].nomeMusica,
                listaMusicas[i].duracaoMinutos,
                listaMusicas[i].generoMusica,
                listaMusicas[i].anoLancamento);
    }
    fclose(arq);
}

// ----------------------------------------------------------------------------
// 3. PERSISTﾃ劾CIA: Carrega os dados do arquivo musicas.csv ao abrir o programa
// ----------------------------------------------------------------------------
void carregarMusicasCSV() {
    FILE *arq = fopen("data/musicas.csv", "r");
    if (arq == NULL) return; // Se nﾃ｣o existir arquivo ainda, mantem totalMusicas = 0

    totalMusicas = 0; // Reseta o contador para preencher do zero a partir do arquivo
    
    // Leitura ajustada para nﾃ｣o quebrar no final da linha
    while (totalMusicas < MAX_MUSICAS &&
           fscanf(arq, "%d;%39[^;\n];%f;%39[^;\n];%d\n",
                  &listaMusicas[totalMusicas].idMusica,
                  listaMusicas[totalMusicas].nomeMusica,
                  &listaMusicas[totalMusicas].duracaoMinutos,
                  listaMusicas[totalMusicas].generoMusica,
                  &listaMusicas[totalMusicas].anoLancamento) == 5) {
        totalMusicas++;
    }
    fclose(arq);
}

// ----------------------------------------------------------------------------
// 4. FUNﾃ�グ CHAVE-MESTRA: Retorna o ﾃｭndice onde o ID estﾃ｡, ou -1 se nﾃ｣o existir
// ----------------------------------------------------------------------------
int buscarIndiceMusica(int idProcurado) {
    int i;
    for (i = 0; i < totalMusicas; i++) {
        if (listaMusicas[i].idMusica == idProcurado) return i;
    }
    return -1;
}

// ----------------------------------------------------------------------------
// 5. SUBFUNﾃ�グ DE CADASTRO
// ----------------------------------------------------------------------------
void cadastrarMusica() {
    int id;
    if (totalMusicas >= MAX_MUSICAS) {
        printf("\n[ERRO] Limite de 50 musicas atingido!\n");
        return;
    }

    printf("\n--- [CADASTRO DE NOVA Mﾃ售ICA] ---\n");
    printf("Digite o ID da nova musica: ");
    scanf("%d", &id);

    if (buscarIndiceMusica(id) != -1) {
        printf("[ERRO] Ja existe uma musica com o ID %d!\n", id);
        return;
    }

    listaMusicas[totalMusicas].idMusica = id;
    printf("Nome da música: ");
    scanf(" %39[^\n]", listaMusicas[totalMusicas].nomeMusica);
    printf("Duracao em minutos (ex: 3.5): ");
    scanf("%f", &listaMusicas[totalMusicas].duracaoMinutos);
    printf("Genero musical: ");
    scanf(" %29[^\n]", listaMusicas[totalMusicas].generoMusica);
    printf("Ano de lançamento: ");
    scanf("%d", &listaMusicas[totalMusicas].anoLancamento);

    

    totalMusicas++;
    salvarMusicasCSV();

    printf("\n[SUCESSO] Musica cadastrada com sucesso!\n");
}

// ----------------------------------------------------------------------------
// 6. SUBFUNﾃ�グ DE LISTAGEM
// ----------------------------------------------------------------------------
void listarMusicas() {
    int i;
    printf("\n--- CATALOGO DE MÚSICAS (%d itens) ---\n", totalMusicas);
    if (totalMusicas == 0) {
        printf("Nenhuma musica cadastrada.\n");
        return;
    }
    for (i = 0; i < totalMusicas; i++) {
        printf("\nID: %d\n", listaMusicas[i].idMusica);
        printf("Nome: %s\n", listaMusicas[i].nomeMusica);
        printf("Duracao: %.2f min\n", listaMusicas[i].duracaoMinutos);
        printf("Genero: %s\n", listaMusicas[i].generoMusica);
        printf("Ano de lançamento: %d\n", listaMusicas[i].anoLancamento);
        printf("------------------------------------\n");
    }
}

// ----------------------------------------------------------------------------
// 7. SUBFUNﾃ�グ DE BUSCA TEXTUAL COM STRSTR
// ----------------------------------------------------------------------------
void buscarMusicaPorNome() {
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
                   listaMusicas[i].generoMusica,
                   listaMusicas[i].anoLancamento);
            encontradas++;
        }
    }
    if (encontradas == 0) {
        printf("[INFO] Nenhuma música encontrada com o termo '%s'.\n", termo);
    }
}

// ----------------------------------------------------------------------------
// 8. EDIﾃ�グ NA MEMﾃ迭IA SEGUIDA DE REESCRITA TOTAL DO CSV
// ----------------------------------------------------------------------------
void editarMusica() {
    int id;
    int pos;

    printf("\nDigite o ID da musica que deseja EDITAR: ");
    scanf("%d", &id);

    pos = buscarIndiceMusica(id);

    if (pos == -1) {
        printf("[ERRO] Musica nao encontrada!\n");
        return;
    }

    printf("\n--- EDITANDO MÚSICA ---\n");
    printf("Musica atual: %s\n", listaMusicas[pos].nomeMusica);

    printf("Novo nome da música: ");
    scanf(" %39[^\n]", listaMusicas[pos].nomeMusica);

    printf("Nova duracao em minutos: ");
    scanf("%f", &listaMusicas[pos].duracaoMinutos);

    printf("Novo genero musical: ");
    scanf(" %29[^\n]", listaMusicas[pos].generoMusica);

    printf("Novo ano de lancamento: ");
    scanf("%d", &listaMusicas[pos].anoLancamento);

    salvarMusicasCSV();

    printf("\n[SUCESSO] Musica atualizada com sucesso!\n");
}

// ----------------------------------------------------------------------------
// 9. REMOﾃ�グ Fﾃ拘ICA NA MEMﾃ迭IA SEGUIDA DE REESCRITA TOTAL DO CSV
// ----------------------------------------------------------------------------
void removerMusica() {
    int id;
    int pos;
    int j;

    printf("\nDigite o ID da musica que deseja REMOVER: ");
    scanf("%d", &id);
    pos = buscarIndiceMusica(id);
    if (pos == -1) { 
        printf("[ERRO] Musica nao encontrada!\n"); 
        return; 
    }

    for (j = pos; j < totalMusicas - 1; j++) {
        listaMusicas[j] = listaMusicas[j + 1];
    }
    totalMusicas--;
    salvarMusicasCSV();
    printf("[OK] Musica removida do sistema e do CSV!\n");
}

// ----------------------------------------------------------------------------
// 10. SUBMENU DO Mﾃ泥ULO DE Mﾃ售ICAS
// ----------------------------------------------------------------------------
void moduloMusicas() {
    int opcaoMusica;
    setlocale(LC_ALL, "Portuguese");
    do {
        printf("\n--- [MÓDULO 2: GESTÃO DE MÚSICAS (Vinicius)] ---\n");
        printf("1. Cadastrar Nova Musica / Faixa\n");
        printf("2. Listar / Buscar Musicas\n");
        printf("3. Buscar Música pelo nome\n");
        printf("4. Editar Música\n");
        printf("5. Excluir Música\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoMusica);

        switch (opcaoMusica) {
            case 1:
                cadastrarMusica();
                break;
            case 2:
                listarMusicas();
                break;
            case 3:
                buscarMusicaPorNome();
                break;
            case 4:
                editarMusica();
                break;
            case 5:
                removerMusica();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida no módulo de músicas!\n");
        }
    } while (opcaoMusica != 0);
}

#endif
