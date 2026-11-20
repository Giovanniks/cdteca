// Arquivo: musica.h | Autor: Integrante B (Vinicius- (47511818))
#ifndef MUSICAS_H
#define MUSICAS_H

#include <stdio.h>
#include <string.h>
#include "artistas.h"

#define MAX_MUSICAS 50

void listarAlbuns();
int buscarAlbumPorId(int idProcurado);
void listarArtistas();
int buscarArtistaPorId(int idProcurado);

// ----------------------------------------------------------------------------
// 1. ESTRUTURA E ARRAYS GLOBAIS
// ----------------------------------------------------------------------------
struct Musica {
    int idMusica;
    char nomeMusica[40];
    float duracaoMinutos;
    char generoMusica[30];
    int anoLancamento;
    int idAlbum;
    int idArtista;
};
struct Musica listaMusicas[MAX_MUSICAS];
int totalMusicas = 0;

// ----------------------------------------------------------------------------
// 2. PERSIST??CIA: Salva todo o vetor no arquivo musicas.csv
// ----------------------------------------------------------------------------
void salvarMusicasCSV() {
    int i;
    FILE *arq = fopen("data/musicas.csv", "w"); 
    
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar data/musicas.csv!\n");
        return;
    }
    for (i = 0; i < totalMusicas; i++) {
	    fprintf(arq, "%d;%s;%.2f;%s;%d;%d;%d\n",
            listaMusicas[i].idMusica,
			listaMusicas[i].nomeMusica,
			listaMusicas[i].duracaoMinutos,
			listaMusicas[i].generoMusica,
			listaMusicas[i].anoLancamento,
			listaMusicas[i].idArtista,
			listaMusicas[i].idAlbum);
	}
	fclose(arq);
}

// ----------------------------------------------------------------------------
// 3. PERSIST??CIA: Carrega os dados do arquivo musicas.csv ao abrir o programa
// ----------------------------------------------------------------------------
void carregarMusicasCSV() {
    FILE *arq = fopen("data/musicas.csv", "r");

    if (arq == NULL) {
        return;
    }

    totalMusicas = 0;

    while (totalMusicas < MAX_MUSICAS &&
       fscanf(arq, "%d;%39[^;\n];%f;%29[^;\n];%d;%d;%d",
              &listaMusicas[totalMusicas].idMusica,
              listaMusicas[totalMusicas].nomeMusica,
              &listaMusicas[totalMusicas].duracaoMinutos,
              listaMusicas[totalMusicas].generoMusica,
              &listaMusicas[totalMusicas].anoLancamento,
              &listaMusicas[totalMusicas].idArtista,
              &listaMusicas[totalMusicas].idAlbum) == 7) {

    totalMusicas++;
}

    fclose(arq);
}
// ----------------------------------------------------------------------------
// 4. FUN? ? CHAVE-MESTRA: Retorna o ??ndice onde o ID est??, ou -1 se n??o existir
// ----------------------------------------------------------------------------
int buscarIndiceMusica(int idProcurado) {
    int i;
    for (i = 0; i < totalMusicas; i++) {
        if (listaMusicas[i].idMusica == idProcurado) return i;
    }
    return -1;
}

// ----------------------------------------------------------------------------
// 5. SUBFUN? ? DE CADASTRO
// ----------------------------------------------------------------------------
void cadastrarMusica() {
    int id;
    int idAlbum;
    int idArtista;
    int posArtista;
    int c;
    if (totalMusicas >= MAX_MUSICAS) {
        printf("\n[ERRO] Limite de 50 musicas atingido!\n");
        return;
    }

    printf("\n--- [CADASTRO DE NOVA M??ICA] ---\n");
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
   
   printf("\n--- ARTISTAS DISPONIVEIS ---\n");
   if (totalArtistas == 0) {
    printf("[ERRO] Cadastre um artista primeiro!\n");
    return;
	}
	listarArtistas();
	
	do {
        printf("\nDigite o ID do artista (-1 para cancelar): ");

        if (scanf("%d", &idArtista) != 1) {
            printf("[ERRO] Digite apenas numeros!\n");

            while ((c = getchar()) != '\n' && c != EOF) {
        }

            idArtista = -2;
    }

        if (idArtista == -1) {
            printf("Cadastro cancelado!\n");
            return;
        }
	
	    posArtista = buscarArtistaPorId(idArtista);

        if (posArtista == -1) {
        printf("[ERRO] Artista nao encontrado!\n");
		}
        else if (cadastroArtistas[posArtista].ativo == 0) {
            printf("[ERRO] Artista inativo! Escolha outro.\n");
            posArtista = -1;
    }

    } while (posArtista == -1);

    listaMusicas[totalMusicas].idArtista = idArtista;
   
   
   
   	printf("\n--- ALBUNS DISPONIVEIS ---\n");
    listarAlbuns();

    do {
        printf("\nDigite o ID do album (0 para nenhum): ");

        if (scanf("%d", &idAlbum) != 1) {
            printf("[ERRO] Digite apenas numeros!\n");
            while ((c = getchar()) != '\n' && c != EOF) {
        }

            idAlbum = -1;
        }

        if (idAlbum != 0 && buscarAlbumPorId(idAlbum) == -1) {
            printf("[ERRO] Album nao encontrado!\n");
    }

    } while (idAlbum != 0 && buscarAlbumPorId(idAlbum) == -1);

    listaMusicas[totalMusicas].idAlbum = idAlbum;

    totalMusicas++;
    salvarMusicasCSV();

    printf("\n[SUCESSO] Musica cadastrada com sucesso!\n");
}
// ----------------------------------------------------------------------------
// 6. SUBFUN? ? DE LISTAGEM
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
    printf("Ano: %d\n", listaMusicas[i].anoLancamento);
    printf("ID do Artista: %d\n", listaMusicas[i].idArtista);

    if (listaMusicas[i].idAlbum == 0) {
        printf("Album: Nenhum (Single)\n");
    }
    else {
        printf("ID do Album: %d\n", listaMusicas[i].idAlbum);
    }

    printf("------------------------------------\n");
}
        printf("ID do Artista: %d\n", listaMusicas[i].idArtista);
		if (listaMusicas[i].idAlbum == 0) {
            printf("Album: Nenhum (Single)\n");
		}
        else {
            printf("ID do Album: %d\n", listaMusicas[i].idAlbum);
        }
}

// ----------------------------------------------------------------------------
// 7. SUBFUN? ? DE BUSCA TEXTUAL COM STRSTR
// ----------------------------------------------------------------------------
void buscarMusicaPorNome() {
    int i;
    int encontradas = 0;
    char termo[30];

    printf("\nDigite parte do nome da musica para buscar: ");
    scanf(" %29[^\n]", termo);
    
    for (i = 0; i < totalMusicas; i++) {
        if (strstr(listaMusicas[i].nomeMusica, termo) != NULL) {
            printf("\nID: %d\n", listaMusicas[i].idMusica);
			printf("Nome: %s\n", listaMusicas[i].nomeMusica);
			printf("Duracao: %.2f min\n", listaMusicas[i].duracaoMinutos);
			printf("Genero: %s\n", listaMusicas[i].generoMusica);
			printf("Ano de lancamento: %d\n", listaMusicas[i].anoLancamento);
			printf("ID do Artista: %d\n", listaMusicas[i].idArtista);
			
			if (listaMusicas[i].idAlbum == 0) {
                printf("Album: Nenhum (Single)\n");
            }
            else {
			    printf("ID do Album: %d\n", listaMusicas[i].idAlbum);
            }
			printf("------------------------------------\n");
            encontradas++;
        }
    }
    if (encontradas == 0) {
        printf("[INFO] Nenhuma música encontrada com o termo '%s'.\n", termo);
    }
}

// ----------------------------------------------------------------------------
// 8. EDI? ? NA MEM??IA SEGUIDA DE REESCRITA TOTAL DO CSV
// ----------------------------------------------------------------------------

void editarMusica() {
    int id, pos, idArtista, idAlbum, posArtista, c;

    printf("\nDigite o ID da musica que deseja EDITAR: ");
    if (scanf("%d", &id) != 1) {
        printf("[ERRO] ID invalido!\n");
        while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }

    pos = buscarIndiceMusica(id);

    if (pos == -1) {
        printf("[ERRO] Musica nao encontrada!\n");
        return;
    }

    printf("\n--- EDITANDO MUSICA ---\n");
    printf("Musica atual: %s\n", listaMusicas[pos].nomeMusica);

    // Escolher artista obrigatorio
    listarArtistas();

    do {
        printf("\nNovo ID do artista (-1 para cancelar): ");

        if (scanf("%d", &idArtista) != 1) {
            printf("[ERRO] Digite apenas numeros!\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            idArtista = -2;
        }

        if (idArtista == -1) {
            printf("Edicao cancelada!\n");
            return;
        }

        posArtista = buscarArtistaPorId(idArtista);

        if (posArtista == -1) {
            printf("[ERRO] Artista nao encontrado!\n");
        }
        else if (cadastroArtistas[posArtista].ativo == 0) {
            printf("[ERRO] Artista inativo!\n");
            posArtista = -1;
        }

    } while (posArtista == -1);

    // Escolher album opcional
    listarAlbuns();

    do {
        printf("\nNovo ID do album (0 para nenhum, -1 para cancelar): ");

        if (scanf("%d", &idAlbum) != 1) {
            printf("[ERRO] Digite apenas numeros!\n");
            while ((c = getchar()) != '\n' && c != EOF) {}
            idAlbum = -2;
        }

        if (idAlbum == -1) {
            printf("Edicao cancelada!\n");
            return;
        }

        if (idAlbum != 0 && buscarAlbumPorId(idAlbum) == -1) {
            printf("[ERRO] Album nao encontrado!\n");
        }

    } while (idAlbum != 0 && buscarAlbumPorId(idAlbum) == -1);

    printf("\nNovo nome: ");
    scanf(" %39[^\n]", listaMusicas[pos].nomeMusica);

    printf("Nova duracao: ");
    scanf("%f", &listaMusicas[pos].duracaoMinutos);

    printf("Novo genero: ");
    scanf(" %29[^\n]", listaMusicas[pos].generoMusica);

    printf("Novo ano: ");
    scanf("%d", &listaMusicas[pos].anoLancamento);

    listaMusicas[pos].idArtista = idArtista;
    listaMusicas[pos].idAlbum = idAlbum;

    salvarMusicasCSV();

    printf("\n[SUCESSO] Musica atualizada!\n");
}

// ----------------------------------------------------------------------------
// 9. REMO? ? F??ICA NA MEM??IA SEGUIDA DE REESCRITA TOTAL DO CSV
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
// 10. SUBMENU DO M??ULO DE M??ICAS
// ----------------------------------------------------------------------------
void moduloMusicas() {
    int opcaoMusica;

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
