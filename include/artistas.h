// Arquivo: include/artistas.h | Autor: Alan
#ifndef ARTISTAS_H
#define ARTISTAS_H

#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_ARTISTAS 50


struct Artista {
    int idArtista;
    char nomeArtista[40];
    char paisOrigem[30];
    int quantidadeAlbuns;
    int ativo; // 1 para ativo, 0 para inativo
};

struct Artista cadastroArtistas[MAX_ARTISTAS];
int totalArtistas = 0;
int proximoIdArtista = 1;

// Lê um inteiro (não trava se o usuário digitar letras)
int lerInteiroArtista(int *valor) {
    if (scanf("%d", valor) != 1) {
        while (getchar() != '\n');
        return 0;
    }
    return 1;
}


// Salva todos os artistas no CSV. Retorna 1 se salvou, 0 se falhou
int salvarArtistasCSV() {
    int i;
    FILE *arq = fopen("data/artistas.csv", "w"); // w apaga tudo e regrava
    if (arq == NULL) {
        printf("[ERRO] Não foi possível salvar o arquivo artistas.csv!\n");
        return 0;
    }

    fprintf(arq, "idArtista;nomeArtista;paisOrigem;quantidadeAlbuns;ativo\n");
    for (i = 0; i < totalArtistas; i++) {
        fprintf(arq, "%d;%s;%s;%d;%d\n",
                cadastroArtistas[i].idArtista,
                cadastroArtistas[i].nomeArtista,
                cadastroArtistas[i].paisOrigem,
                cadastroArtistas[i].quantidadeAlbuns,
                cadastroArtistas[i].ativo);
    }
    fclose(arq);
    return 1;
}

// Carrega os artistas do CSV, se o arquivo existir
void carregarArtistasCSV() {
    FILE *arq = fopen("data/artistas.csv", "r");
    if (arq == NULL) return; // primeira execução: inicia vazio

    char linha[200];
    fgets(linha, sizeof(linha), arq); // pula o cabeçalho

    totalArtistas = 0;
    proximoIdArtista = 1;

    while (totalArtistas < MAX_ARTISTAS && fgets(linha, sizeof(linha), arq) != NULL) {
        struct Artista a;
        if (sscanf(linha, "%d;%39[^;];%29[^;];%d;%d",
                   &a.idArtista, a.nomeArtista, a.paisOrigem,
                   &a.quantidadeAlbuns, &a.ativo) == 5) {
            cadastroArtistas[totalArtistas++] = a;
            if (a.idArtista >= proximoIdArtista) {
                proximoIdArtista = a.idArtista + 1;
            }
        }
    }
    fclose(arq);
}

/* ---------- Buscas ---------- */

// Retorna a posição do artista pelo nome, ou -1 se não existir
int buscarArtistaPorNome(char *nomeProcurado) {
    int i;
    for (i = 0; i < totalArtistas; i++) {
        if (strcasecmp(cadastroArtistas[i].nomeArtista, nomeProcurado) == 0) {
            return i;
        }
    }
    return -1;
}

// Retorna a posição do artista pelo ID, ou -1 se não existir
int buscarArtistaPorId(int idProcurado) {
    int i;
    for (i = 0; i < totalArtistas; i++) {
        if (cadastroArtistas[i].idArtista == idProcurado) {
            return i;
        }
    }
    return -1;
}

/* ---------- Operações ---------- */

// Cadastrar artista 
void cadastrarArtista() {
    if (totalArtistas >= MAX_ARTISTAS) {
        printf("\n[ERRO] Limite de %d artistas atingido!\n\n", MAX_ARTISTAS);
        return;
    }

    char nomeTemp[40];
    printf("\n--- [CADASTRO DE NOVO ARTISTA] ---\n");
    printf("Nome do Artista: ");
    scanf(" %39[^\n]", nomeTemp);

    if (strchr(nomeTemp, ';') != NULL) {
        printf("[ERRO] O nome não pode conter o caractere ';'!\n\n");
        return;
    }

    if (buscarArtistaPorNome(nomeTemp) != -1) {
        printf("[ERRO] Já existe um artista cadastrado com o nome \"%s\"!\n\n", nomeTemp);
        return;
    }

    strcpy(cadastroArtistas[totalArtistas].nomeArtista, nomeTemp);
    cadastroArtistas[totalArtistas].idArtista = proximoIdArtista;

    printf("País de origem: ");
    scanf(" %29[^\n]", cadastroArtistas[totalArtistas].paisOrigem);

    int qtd;
    do {
        printf("Quantidade de álbuns: ");
        if (!lerInteiroArtista(&qtd)) {
            qtd = -1;
        }
        if (qtd < 0) {
            printf("[ERRO] Digite um número válido (não negativo)!\n");
        }
    } while (qtd < 0);

    cadastroArtistas[totalArtistas].quantidadeAlbuns = qtd;
    cadastroArtistas[totalArtistas].ativo = 1;

    printf("\n[SUCESSO] Artista \"%s\" cadastrado com ID %d!\n\n",
           cadastroArtistas[totalArtistas].nomeArtista,
           cadastroArtistas[totalArtistas].idArtista);

    totalArtistas++;
    proximoIdArtista++;
    salvarArtistasCSV();
}

// Lista todos os artistas
void listarArtistas() {
    int i;
    printf("\n--- [LISTA DE ARTISTAS] (%d itens) ---\n", totalArtistas);
    if (totalArtistas == 0) {
        printf("Nenhum artista cadastrado ainda.\n\n");
        return;
    }

    for (i = 0; i < totalArtistas; i++) {
        printf("ID: %d | Nome: %s | País: %s | Álbuns: %d | Status: %s\n\n",
               cadastroArtistas[i].idArtista,
               cadastroArtistas[i].nomeArtista,
               cadastroArtistas[i].paisOrigem,
               cadastroArtistas[i].quantidadeAlbuns,
               cadastroArtistas[i].ativo == 1 ? "Ativo" : "Inativo");
    }
}

// Atualizar dados do artista
void atualizarArtista() {
    int idBusca;
    printf("\n--- [ATUALIZAR ARTISTA] ---\n");
    printf("Digite o ID do artista: ");
    if (!lerInteiroArtista(&idBusca)) {
        printf("[ERRO] ID inválido!\n\n");
        return;
    }

    int pos = buscarArtistaPorId(idBusca);
    if (pos == -1) {
        printf("\n[ERRO] Artista com ID %d não encontrado!\n\n", idBusca);
        return;
    }

    printf("\nArtista encontrado: [%d] %s (%s)\n\n",
           cadastroArtistas[pos].idArtista,
           cadastroArtistas[pos].nomeArtista,
           cadastroArtistas[pos].paisOrigem);

    char nomeTemp[40];
    printf("Novo nome: ");
    scanf(" %39[^\n]", nomeTemp);

    if (strchr(nomeTemp, ';') != NULL) {
        printf("[ERRO] O nome não pode conter o caractere ';'!\n\n");
        return;
    }

    int outro = buscarArtistaPorNome(nomeTemp);
    if (outro != -1 && outro != pos) {
        printf("[ERRO] Já existe outro artista com o nome \"%s\"!\n\n", nomeTemp);
        return;
    }
    strcpy(cadastroArtistas[pos].nomeArtista, nomeTemp);

    printf("Novo país de origem: ");
    scanf(" %29[^\n]", cadastroArtistas[pos].paisOrigem);

    int qtdNova;
    do {
        printf("Nova quantidade de álbuns: ");
        if (!lerInteiroArtista(&qtdNova)) {
            qtdNova = -1;
        }
        if (qtdNova < 0) {
            printf("[ERRO] Digite um número válido (não negativo)!\n");
        }
    } while (qtdNova < 0);
    cadastroArtistas[pos].quantidadeAlbuns = qtdNova;

    int status;
    printf("Status (1 = Ativo, 0 = Inativo): ");
    if (lerInteiroArtista(&status) && (status == 0 || status == 1)) {
        cadastroArtistas[pos].ativo = status;
    } else {
        printf("[INFO] Status inválido, mantido o valor anterior.\n");
    }

    if (salvarArtistasCSV()) {
        printf("\n[SUCESSO] Artista atualizado e salvo com sucesso!\n\n");
    }
}

// Desativar artista (continua no cadastro, só muda o status)
void desativarArtista() {
    int idBusca;
    printf("\n--- [DESATIVAR ARTISTA] ---\n");
    printf("Digite o ID do artista: ");
    if (!lerInteiroArtista(&idBusca)) {
        printf("[ERRO] ID inválido!\n\n");
        return;
    }

    int pos = buscarArtistaPorId(idBusca);
    if (pos == -1) {
        printf("\n[ERRO] Artista com ID %d não encontrado!\n\n", idBusca);
        return;
    }

    cadastroArtistas[pos].ativo = 0;
    if (salvarArtistasCSV()) {
        printf("\n[SUCESSO] Artista \"%s\" desativado!\n\n", cadastroArtistas[pos].nomeArtista);
    }
}

// Remover artista (exclui definitivamente do cadastro e do CSV)
void removerArtista() {
    int idBusca, i;
    char confirmacao;

    printf("\n--- [REMOVER ARTISTA] ---\n");
    printf("Digite o ID do artista: ");
    if (!lerInteiroArtista(&idBusca)) {
        printf("[ERRO] ID inválido!\n\n");
        return;
    }

    int pos = buscarArtistaPorId(idBusca);
    if (pos == -1) {
        printf("\n[ERRO] Artista com ID %d não encontrado!\n\n", idBusca);
        return;
    }

    printf("\nArtista encontrado: [%d] %s (%s)\n",
           cadastroArtistas[pos].idArtista,
           cadastroArtistas[pos].nomeArtista,
           cadastroArtistas[pos].paisOrigem);
    printf("Tem certeza que deseja REMOVER definitivamente? (s/n): ");
    scanf(" %c", &confirmacao);
    while (getchar() != '\n'); // limpa o resto da linha

    if (confirmacao != 's' && confirmacao != 'S') {
        printf("\n[INFO] Remoção cancelada.\n\n");
        return;
    }

    char nomeRemovido[40];
    strcpy(nomeRemovido, cadastroArtistas[pos].nomeArtista);

    // Desloca os artistas seguintes uma posição para trás
    for (i = pos; i < totalArtistas - 1; i++) {
        cadastroArtistas[i] = cadastroArtistas[i + 1];
    }
    totalArtistas--;

    if (salvarArtistasCSV()) {
        printf("\n[SUCESSO] Artista \"%s\" removido com sucesso!\n\n", nomeRemovido);
    }
}

/* ---------- Menu do módulo ---------- */

void moduloArtistas() {
    int opcaoArtista;
    setlocale(LC_ALL, "Portuguese");
    carregarArtistasCSV();

    do {
        printf("\n--- [MÓDULO 3: CADASTRO DE ARTISTAS (Alan)] ---\n");
        printf("1. Cadastrar Novo Artista / Banda\n");
        printf("2. Consultar / Listar Artistas\n");
        printf("3. Atualizar Dados do Artista\n");
        printf("4. Desativar Artista\n");
        printf("5. Remover Artista\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma ação: ");

        if (!lerInteiroArtista(&opcaoArtista)) {
            opcaoArtista = -1; // cai no default
        }

        switch (opcaoArtista) {
            case 1:
                cadastrarArtista();
                break;
            case 2:
                listarArtistas();
                break;
            case 3:
                atualizarArtista();
                break;
            case 4:
                desativarArtista();
                break;
            case 5:
                removerArtista();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida no Módulo de Artistas!\n");
        }
    } while (opcaoArtista != 0);
}

#endif

#include <stdio.h>
