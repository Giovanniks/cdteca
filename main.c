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
            case 1:
                if (totalArtistas >= 50) {
                    printf("\n[ERRO] Limite de 50 artistas atingido!\n");
                } else {
                    printf("\n--- [CADASTRO DE NOVO ARTISTA] ---\n");
                    cadastroArtistas[totalArtistas].idArtista = proximoIdArtista;

                    printf("Nome do Artista: ");
                    scanf(" %39[^\n]", cadastroArtistas[totalArtistas].nomeArtista);
                    
                    printf("País de origem: ");
                    scanf(" %29[^\n]", cadastroArtistas[totalArtistas].paisOrigem);

                    printf("Quantidade de álbuns: ");
                    scanf("%d", &cadastroArtistas[totalArtistas].quantidadeAlbuns);
                    
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

                    printf("\n[OK] Artista \"%s\" cadastrado com ID %d!\n", cadastroArtistas[totalArtistas].nomeArtista, cadastroArtistas[totalArtistas].idArtista);

                    totalArtistas++;
                    proximoIdArtista++;
                }
                break;

           	case 2:
    				printf("\n--- [LISTA DE ARTISTAS] ---\n");
   				if (totalArtistas == 0) {
        			printf("Nenhum artista cadastrado ainda.\n");
    			} else {
        			for (int i = 0; i < totalArtistas; i++) {
            			printf("\nID: %d\n", cadastroArtistas[i].idArtista);
            			printf("Nome: %s\n", cadastroArtistas[i].nomeArtista);
            			printf("País de origem: %s\n", cadastroArtistas[i].paisOrigem);
            			printf("Álbuns: %d\n", cadastroArtistas[i].quantidadeAlbuns);
            
            // Substituição do operador ternário por if-else tradicional
            	if (cadastroArtistas[i].ativo == 1) {
               		printf("Status: Ativo\n");
            	} else {
                	printf("Status: Inativo\n");
            	}
            		printf("------------------------\n");
        	}
    }
    			break;

            case 3: {
    			int idBusca;
    			int achou = 0;

    			printf("\n--- [ATUALIZAR ARTISTA] ---\n");
    			printf("Digite o ID do artista: ");
    			scanf("%d", &idBusca);

    			for (int i = 0; i < totalArtistas; i++) {
        			if (cadastroArtistas[i].idArtista == idBusca) {
            			printf("Novo nome: ");
            			scanf(" %39[^\n]", cadastroArtistas[i].nomeArtista);

            			printf("Novo país de origem: ");
            			scanf(" %29[^\n]", cadastroArtistas[i].paisOrigem);

            			printf("Nova quantidade de álbuns: ");
            			scanf("%d", &cadastroArtistas[i].quantidadeAlbuns);

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

                for (int i = 0; i < totalArtistas; i++) {
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
