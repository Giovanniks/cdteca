#include <stdio.h>
#include <string.h>
#include <locale.h>

// ============================================================================
// PARTE 1: MODELAGEM DE DADOS (ESCOPO GLOBAL - 4 STRUCTS)
// ============================================================================

// 1. Perspectiva do Giovanni(48079391): Catálogo de Álbuns / CDs
struct Album {
    int idAlbum;
    char tituloAlbum[50];
    int anoLancamento;
    char genero[30];
    int disponivelNaColecao; // 1 = Sim, 0 = Emprestado/Perdido
};
struct Album catalogoAlbuns[50];
int totalAlbuns = 0;

// 2. Perspectiva do Vinicius(47511818): Gestão de Músicas / Faixas
struct Musica {
    int idMusica;
    char nomeMusica[40];
    float duracaoMinutos;
    int idAlbumPertencente;
    int numeroFaixa;
};
struct Musica listaMusicas[50];
int totalMusicas = 0;

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

// 4. Perspectiva do Giovanni: Músicas Curtidas e Relatórios
struct MusicaCurtida {
    int idCurtida;
    int idMusicaFavorita;
    int notaEstrelas; // 1 a 5
    int vezesOuvida;
};
struct MusicaCurtida historicoCurtidas[50];
int totalCurtidas = 0;


// ============================================================================
// PARTE 2: FUNÇÕES DE INTERFACE E MÓDULOS DE CADA INTEGRANTE
// ============================================================================

// Função Visual Comum da Equipe
void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("         CDTECA PESSOAL - MINHA COLEÇÃO MUSICAL       \n");
    printf("======================================================\n");
}

// ----------------------------------------------------------------------------
// MÓDULO 1: PERSPECTIVA DE ÁLBUNS / CDS
// Autor: Integrante A (Giovanni 48079391)
// ----------------------------------------------------------------------------
void moduloAlbuns() {
    int opcaoAlbum;
    do {
        printf("\n--- [MÓDULO 1: CATÁLOGO DE ÁLBUNS (Giovanni )] ---\n");
        printf("1. Cadastrar Novo Álbum\n");
        printf("2. Listar / Buscar Álbuns\n");
        printf("3. Editar Dados do Álbum\n");
        printf("4. Remover Álbum\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma ação: ");
        scanf("%d", &opcaoAlbum);

        switch (opcaoAlbum) {
            case 1:
                printf("\n[Em construção] Rotina de Cadastro de Álbum...\n");
                break;
            case 2:
                printf("\n[Em construção] Rotina de Listagem e Busca de Álbuns...\n");
                break;
            case 3:
                printf("\n[Em construção] Rotina de Edição de Álbum...\n");
                break;
            case 4:
                printf("\n[Em construção] Rotina de Remoção de Álbum...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida no Módulo de Álbuns!\n");
        }
    } while (opcaoAlbum != 0);
}

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
                printf("\n[Em construção] Cadastrando Nova Música...\n");
                break;
            case 2:
                printf("\n[Em construção] Listando músicas cadastradas...\n");
                break;
            case 3:
                printf("\n[Em construção] Atualizando dados da música...\n");
                break;
            case 4:
                printf("\n[Em construção] Removendo música...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida no Módulo de Músicas!\n");
        }
    } while (opcaoMusica != 0);
}

// ----------------------------------------------------------------------------
// MÓDULO 3: PERSPECTIVA DE ARTISTAS / BANDAS
// Autor: Integrante C (Alan)
// ----------------------------------------------------------------------------
void moduloArtistas() {
    int opcaoArtista;
    do {
        printf("\n--- [MÓDULO 3: CADASTRO DE ARTISTAS (Alan)] ---\n");
        printf("1. Cadastrar Novo Artista / Banda\n");
        printf("2. Consultar / Listar Artistas\n");
        printf("3. Atualizar Dados do Artista\n");
        printf("4. Desativar / Remover Artista\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma ação: ");
        scanf("%d", &opcaoArtista);

        switch (opcaoArtista) {
            case 1:
                printf("\n[Em construção] Cadastrando novo artista...\n");
                break;
            case 2:
                printf("\n[Em construção] Listando artistas...\n");
                break;
            case 3:
                printf("\n[Em construção] Editando dados de artista...\n");
                break;
            case 4:
                printf("\n[Em construção] Removendo artista...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida no Módulo de Artistas!\n");
        }
    } while (opcaoArtista != 0);
}

// ----------------------------------------------------------------------------
// MÓDULO 4: PERSPECTIVA DE MÚSICAS CURTIDAS E RELATÓRIOS
// Autor: Integrante C (Giovanni)
// ----------------------------------------------------------------------------
void moduloCurtidasRelatorios() {
    int opcaoCurtida;
    do {
        printf("\n--- [MÓDULO 4: CURTIDAS E RELATÓRIOS (Giovanni)] ---\n");
        printf("1. Registrar Música Curtida / Favorita\n");
        printf("2. Listar Histórico de Curtidas\n");
        printf("3. Atualizar Nota ou Vezes Ouvida\n");
        printf("4. [RELATÓRIO] Música Mais Ouvida\n");
        printf("5. [RELATÓRIO] Álbum com Mais Músicas Cadastradas\n");
        printf("6. [RELATÓRIO] Músicas com Nota Máxima (5 Estrelas)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma ação: ");
        scanf("%d", &opcaoCurtida);

        switch (opcaoCurtida) {
            case 1:
                printf("\n[Em construção] Registrando música curtida...\n");
                break;
            case 2:
                printf("\n[Em construção] Exibindo histórico de curtidas...\n");
                break;
            case 3:
                printf("\n[Em construção] Atualizando avaliação...\n");
                break;
            case 4:
                printf("\n[Em construção] Calculando música mais ouvida...\n");
                break;
            case 5:
                printf("\n[Em construção] Identificando álbum destaque...\n");
                break;
            case 6:
                printf("\n[Em construção] Filtrando músicas 5 estrelas...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida no Módulo de Curtidas e Relatórios!\n");
        }
    } while (opcaoCurtida != 0);
}


// ============================================================================
// PARTE 3: FUNÇÃO PRINCIPAL (MAIN) - DESPACHANTE DE MENUS
// ============================================================================
int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcaoPrincipal;

    do {
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
