#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "include/albuns.h"
#include "include/musica.h"
#include "include/artistas.h"



// 3. Perspectiva do Alan (47135221): Cadastro de Artistas / Bandas
struct Artista {
    int idArtista;
    char nomeArtista[40];
    char paisOrigem[30];
    int quantidadeAlbuns;
    int ativo; // 1 = Ativo, 0 = Inativo
};
struct Artista cadastroArtistas[50];
int totalArtistas = 0;
int proximoIdArtista = 1;

// 4. Perspectiva do Giovanni: MÃºsicas Curtidas e RelatÃ³rios
struct MusicaCurtida {
    int idCurtida;
    int idMusicaFavorita;
    int notaEstrelas; // 1 a 5
    int vezesOuvida;
};
struct MusicaCurtida historicoCurtidas[50];
int totalCurtidas = 0;
int i;
int j;


// ============================================================================
// PARTE 2: FUNÃ‡Ã•ES DE INTERFACE E MÃ“DULOS DE CADA INTEGRANTE
// ============================================================================

// FunÃ§Ã£o Visual Comum da Equipe
void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("         CDTECA PESSOAL - MINHA COLEÇÃO MUSICAL       \n");
    printf("======================================================\n");
}


// ----------------------------------------------------------------------------
// MÃ“DULO 4: PERSPECTIVA DE MÃšSICAS CURTIDAS E RELATÃ“RIOS
// Autor: Integrante A (Giovanni)
// ----------------------------------------------------------------------------
void moduloCurtidasRelatorios() {
    int opcaoCurtida;
    do {
        printf("\n--- [MÃ“DULO 4: CURTIDAS E RELATÃ“RIOS (Giovanni)] ---\n");
        printf("1. Registrar MÃºsica Curtida / Favorita\n");
        printf("2. Listar HistÃ³rico de Curtidas\n");
        printf("3. Atualizar Nota ou Vezes Ouvida\n");
        printf("4. [RELATÃ“RIO] MÃºsica Mais Ouvida\n");
        printf("5. [RELATÃ“RIO] Ãlbum com Mais MÃºsicas Cadastradas\n");
        printf("6. [RELATÃ“RIO] MÃºsicas com Nota MÃ¡xima (5 Estrelas)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma aÃ§Ã£o: ");
        scanf("%d", &opcaoCurtida);

        switch (opcaoCurtida) {
            case 1:
                printf("\n[Em construÃ§Ã£o] Registrando mÃºsica curtida...\n");
                break;
            case 2:
                printf("\n[Em construÃ§Ã£o] Exibindo histÃ³rico de curtidas...\n");
                break;
            case 3:
                printf("\n[Em construÃ§Ã£o] Atualizando avaliaÃ§Ã£o...\n");
                break;
            case 4:
                printf("\n[Em construÃ§Ã£o] Calculando mÃºsica mais ouvida...\n");
                break;
            case 5:
                printf("\n[Em construÃ§Ã£o] Identificando Ã¡lbum destaque...\n");
                break;
            case 6:
                printf("\n[Em construÃ§Ã£o] Filtrando mÃºsicas 5 estrelas...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] OpÃ§Ã£o invÃ¡lida no MÃ³dulo de Curtidas e RelatÃ³rios!\n");
        }
    } while (opcaoCurtida != 0);
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

    int opcaoPrincipal;

    do {
    	
    	limparTela();
    	
        exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA DO SISTEMA:\n");
        printf("1. Módulo de Álbuns / CDs (Giovanni)\n");
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
                 printf("\n[ALERTA] Opção inválida! Digite um número de 0 a 4.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
