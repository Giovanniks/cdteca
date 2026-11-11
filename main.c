#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "include/albuns.h"
#include "include/musica.h"



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

// 4. Perspectiva do Giovanni: Músicas Curtidas e Relatórios
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
// PARTE 2: FUNÇÕES DE INTERFACE E MÓDULOS DE CADA INTEGRANTE
// ============================================================================

// Função Visual Comum da Equipe
void exibirCabecalho() {
    printf("\n======================================================\n");
    printf("         CDTECA PESSOAL - MINHA COLE��O MUSICAL       \n");
    printf("======================================================\n");
}


// ----------------------------------------------------------------------------
// MÓDULO 3: PERSPECTIVA DE ARTISTAS / BANDAS
// Autor: Integrante C Alan (47135221)
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
    
            case 1: {
                if (totalArtistas >= 50) {
                    printf("\n[ERRO] Limite de 50 artistas atingido!\n");
                } else {
                    printf("\n--- [CADASTRO DE NOVO ARTISTA] ---\n");
                    cadastroArtistas[totalArtistas].idArtista = proximoIdArtista;

                    printf("Nome do Artista: ");
                    scanf(" %39[^\n]", cadastroArtistas[totalArtistas].nomeArtista);
                    
                    printf("País de origem: ");
                    scanf(" %29[^\n]", cadastroArtistas[totalArtistas].paisOrigem);

                    int qtd;
                    do {
                        printf("Quantidade de álbuns: ");
                        scanf("%d", &qtd);
                        
                        if (qtd < 0) {
                            printf("[ERRO] A quantidade não pode ser negativa!\n");
                        }
                    } while (qtd < 0);

                    cadastroArtistas[totalArtistas].quantidadeAlbuns = qtd;
                    cadastroArtistas[totalArtistas].ativo = 1;

                    printf("\n[OK] Artista \"%s\" cadastrado com ID %d!\n", 
                           cadastroArtistas[totalArtistas].nomeArtista, 
                           cadastroArtistas[totalArtistas].idArtista);

                    totalArtistas++;
                    proximoIdArtista++;
                }
                break;
            }

            case 2: {
                printf("\n--- [LISTA DE ARTISTAS] ---\n");
                if (totalArtistas == 0) {
                    printf("Nenhum artista cadastrado ainda.\n");
                } else {
                    for (i = 0; i < totalArtistas; i++) {
                        printf("\nID: %d\n", cadastroArtistas[i].idArtista);
                        printf("Nome: %s\n", cadastroArtistas[i].nomeArtista);
                        printf("País de origem: %s\n", cadastroArtistas[i].paisOrigem);
                        printf("Álbuns: %d\n", cadastroArtistas[i].quantidadeAlbuns);
                        
                        if (cadastroArtistas[i].ativo == 1) {
                            printf("Status: Ativo\n");
                        } else {
                            printf("Status: Inativo\n");
                        }
                    }
                }
                break;
            }

            case 3: {
                int idBusca;
                int achou = 0;

                printf("\n--- [ATUALIZAR ARTISTA] ---\n");
                printf("Digite o ID do artista: ");
                scanf("%d", &idBusca);

                for (i = 0; i < totalArtistas; i++) {
                    if (cadastroArtistas[i].idArtista == idBusca) {
                        printf("Novo nome: ");
                        scanf(" %39[^\n]", cadastroArtistas[i].nomeArtista);

                        printf("Novo país de origem: ");
                        scanf(" %29[^\n]", cadastroArtistas[i].paisOrigem);

                        int qtdNova;
                        do {
                            printf("Nova quantidade de álbuns: ");
                            scanf("%d", &qtdNova);
                            if (qtdNova < 0) {
                                printf("[ERRO] A quantidade não pode ser negativa!\n");
                            }
                        } while (qtdNova < 0);

                        cadastroArtistas[i].quantidadeAlbuns = qtdNova;
                        printf("\n[SUCESSO] Artista atualizado!\n");
                        
                        achou = 1;
                        break;
                    }
                }

                if (!achou) {
                    printf("\n[ERRO] Artista com ID %d não encontrado!\n", idBusca);
                }
                break;
            }

            case 4: {
                int idBusca;
                int achou = 0;

                printf("\n--- [DESATIVAR ARTISTA] ---\n");
                printf("Digite o ID do artista: ");
                scanf("%d", &idBusca);

                for (i = 0; i < totalArtistas; i++) {
                    if (cadastroArtistas[i].idArtista == idBusca) {
                        cadastroArtistas[i].ativo = 0;
                        printf("\n[SUCESSO] Artista \"%s\" desativado!\n", cadastroArtistas[i].nomeArtista);
                        achou = 1;
                        break;
                    }
                }

                if (!achou) {
                    printf("\n[ERRO] Artista com ID %d não encontrado!\n", idBusca);
                }
                break;
            }

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
// Autor: Integrante A (Giovanni)
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
        printf("1. M�dulo de �lbuns / CDs (Giovanni)\n");
        printf("2. M�dulo de M�sicas / Faixas (Vinicius)\n");
        printf("3. M�dulo de Artistas / Bandas (Alan)\n");
        printf("4. M�dulo de Curtidas e Relat�rios (Giovanni)\n");
        printf("0. Encerrar o Sistema\n");
        printf("------------------------------------------------------\n");
        printf("Digite a op��o desejada: ");
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
                printf("\nEncerrando o sistema CDteca Pessoal... At� logo!\n");
                break;
            default:
                 printf("\n[ALERTA] Op��o inv�lida! Digite um n�mero de 0 a 4.\n");
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
