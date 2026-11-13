// Arquivo: include/albuns.h | Autor: Giovanni (48079391)
#ifndef ALBUNS_H
#define ALBUNS_H

#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_ALBUNS 50

struct Album {
	int idAlbum;
	char tituloAlbum[50];
	int anoLancamento;
	char genero[30];
	int disponivelNaColecao; // 1 para sim, 0 para não
};

struct Album catalogoAlbuns[MAX_ALBUNS];
	int totalAlbuns = 0;	

// Salva tudo dentro do CSV
void salvarAlbunsCSV() {
	int i;
	FILE *arq = fopen("data/albuns.csv", "w"); // w exclui tudo e regrava novamente
	if (arq == NULL) {
		printf("[ERRO] Não foi possivel gravar o arquivo albuns.csv!\n");
		return;
	}
	for (i = 0; i < totalAlbuns; i++) {
		fprintf(arq, "%d;%s;%d;%s;%d\n",
		catalogoAlbuns[i].idAlbum,
		catalogoAlbuns[i].tituloAlbum,
		catalogoAlbuns[i].anoLancamento,
		catalogoAlbuns[i].genero,
		catalogoAlbuns[i].disponivelNaColecao);
	}
	fclose(arq);
}

// Carrega os albuns do arquivos se tiver
void carregarAlbunsCSV() {
	int i;
	FILE *arq = fopen("data/albuns.csv", "r");
	if (arq == NULL) return; // inicia vazio caso nn tenha arquivo
	
	totalAlbuns = 0;
    while (totalAlbuns < MAX_ALBUNS &&
           fscanf(arq, "%d;%49[^;];%d;%29[^;];%d\n",
                  &catalogoAlbuns[totalAlbuns].idAlbum,
                  catalogoAlbuns[totalAlbuns].tituloAlbum,
                  &catalogoAlbuns[totalAlbuns].anoLancamento,
                  catalogoAlbuns[totalAlbuns].genero,
                  &catalogoAlbuns[totalAlbuns].disponivelNaColecao) == 5) {
        totalAlbuns++;
    }
    fclose(arq);
}

// Procura e ve se o albúm existe, se existir também passa a posição.
int buscarAlbumPorNome (char *nomeProcurado) {
	int i;
	for (i = 0; i < totalAlbuns; i++) {
		if (strcasecmp(catalogoAlbuns[i].tituloAlbum, nomeProcurado) == 0) {
			return i;
		}
	}
	return -1;
}

// Validador de ID
int buscarAlbumPorId(int idProcurado) {
	int i;
    for (i = 0; i < totalAlbuns; i++) {
        if (catalogoAlbuns[i].idAlbum == idProcurado) {
            return i;
        }
    }
    return -1; // Não existe
}

// Cadastrar Album contendo trava de titulo repitido 
void cadastrarAlbum() {
	if (totalAlbuns >= MAX_ALBUNS) {
		printf("\n[ERRO] Catálogo de álbuns lotado!\n\n");
        return;
	}
	
	char tituloTemp[50];
	printf("\n--- [CADASTRAR NOVO ÁLBUM] ---\n");
	printf("Título do Álbum: ");
	scanf(" %[^\n]", tituloTemp);
	
	if (buscarAlbumPorNome(tituloTemp) != -1) {
        printf("[ERRO] Já existe um álbum cadastrado com o título \"%s\"!\n\n", tituloTemp);
        return;
    }
    
    strcpy(catalogoAlbuns[totalAlbuns].tituloAlbum, tituloTemp);
    
    int idTemp;
    printf("ID numérico do Álbum: ");
    scanf("%d", &idTemp);

    if (buscarAlbumPorId(idTemp) != -1) {
        printf("[ERRO] Já existe um álbum cadastrado com o ID %d!\n\n", idTemp);
        return;
    }
    catalogoAlbuns[totalAlbuns].idAlbum = idTemp;

    printf("Ano de Lançamento: ");
    scanf("%d", &catalogoAlbuns[totalAlbuns].anoLancamento);
    printf("Gênero Musical: ");
    scanf(" %[^\n]", catalogoAlbuns[totalAlbuns].genero);
    catalogoAlbuns[totalAlbuns].disponivelNaColecao = 1; // 1 para disponível
    
    totalAlbuns++;
    salvarAlbunsCSV();
    printf("\n[SUCESSO] Álbum cadastrado e salvo com sucesso!\n\n");
    
}

//Catálogo de Albuns
void listarAlbuns() {
	int i;
	printf("\n-- CATÁLOGO DE ÁLBUNS (%d itens) --\n", totalAlbuns);
	if (totalAlbuns == 0) {
		printf("Nenhum Álbum Cadastrado ainda.\n\n");
		return;
	}
	
	for (i = 0; i < totalAlbuns; i++) {
        printf("ID: %d | Título: %s | Ano: %d | Gênero: %s | Status: %s\n\n",
               catalogoAlbuns[i].idAlbum,
               catalogoAlbuns[i].tituloAlbum,
               catalogoAlbuns[i].anoLancamento,
               catalogoAlbuns[i].genero,
               catalogoAlbuns[i].disponivelNaColecao == 1 ? "Disponível" : "Indisponível");
    }
	
}

//Buscar album por nome
void buscarAlbumPorNomeParcial() {
	int i;
	char termo[50];
	printf("\n-- BUSCAR ÁLBUM POR TÍTULO --\n");
	printf("Digite parte do título do álbum: ");
	scanf(" %[^\n]", termo);
	
	int encontrados = 0;
	for (i = 0; i < totalAlbuns; i++) {
		if (strstr(catalogoAlbuns[i].tituloAlbum, termo) != NULL) {
			printf(" -> Encontrado: [%d] %s (%d) - %s\n",
                   catalogoAlbuns[i].idAlbum,
                   catalogoAlbuns[i].tituloAlbum,
                   catalogoAlbuns[i].anoLancamento,
                   catalogoAlbuns[i].genero);
            encontrados++;
        }
	}
	if (encontrados == 0) {
		printf("[INFO] Nenhum álbum encontrado com o termo \"%s\".\n\n", termo);
	}
}

// Editar Álbum
void editarAlbum() {
	int idProcura;
	printf("\n-- EDITAR ÁLBUM --\n");
	printf("Digite o ID do álbum que deseja editar: ");
	scanf("%d", &idProcura);
	
	int pos = buscarAlbumPorId(idProcura);
	if (pos == -1) {
        printf("[ERRO] Álbum com o ID %d não foi encontrado!\n\n", idProcura);
        return;
    }
    
    printf("\nÁlbum encontrado: [%d] %s (%d)\n\n",
           catalogoAlbuns[pos].idAlbum,
           catalogoAlbuns[pos].tituloAlbum,
           catalogoAlbuns[pos].anoLancamento);
    
	printf("\n-- Digite os novos dados --\n");
    
    printf("Novo Título: ");
    scanf(" %[^\n]", catalogoAlbuns[pos].tituloAlbum);

    printf("Novo Ano de Lançamento: ");
    scanf("%d", &catalogoAlbuns[pos].anoLancamento);

    printf("Novo Gênero: ");
    scanf(" %[^\n]", catalogoAlbuns[pos].genero);

    salvarAlbunsCSV();
    printf("\n[SUCESSO] Álbum atualizado e salvo com sucesso\n\n");       
}

//Excluir Album
void excluirAlbum() {
	int i;
	int idProcura;
	printf("\n-- EXCLUIR ÁLBUM --\n");
	printf("Digite o ID do álbum que deseja remover: ");
    scanf("%d", &idProcura);
    
    int pos = buscarAlbumPorId(idProcura);
    if (pos == -1) {
        printf("[ERRO] Álbum com o ID %d não foi encontrado!\n", idProcura);
        return;
    }
    
    printf("Removendo: [%d] %s\n", catalogoAlbuns[pos].idAlbum, catalogoAlbuns[pos].tituloAlbum);
    
    for (i = pos; i < totalAlbuns - 1; i++) {
    	catalogoAlbuns[i] = catalogoAlbuns[i + 1];
	}
	
	totalAlbuns--;
	
	salvarAlbunsCSV();
    printf("\nSUCESSO! Álbum removido com sucesso do catálogo!\n");
}

void moduloAlbuns() {

    int opcaoAlbum;
    setlocale(LC_ALL, "Portuguese");
    do {
        printf("1. Cadastrar novo álbum\n");
        printf("2. Listar todos os álbuns\n");
        printf("3. Buscar álbum por título (parcial)\n");
        printf("4. Editar álbum\n");
        printf("5. Excluir álbum\n");
        printf("0. Sair e salvar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoAlbum);

        switch (opcaoAlbum) {
            case 1:
                cadastrarAlbum();
                break;
            case 2:
                listarAlbuns();
                break;
            case 3:
                buscarAlbumPorNomeParcial();
                break;
            case 4:
                editarAlbum();
                break;
            case 5:
                excluirAlbum();
                break;
            case 0:
                printf("\nA sair do programa... Até à próxima!\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida! Tente novamente.\n");
        }
    } while (opcaoAlbum != 0);
}
#endif
