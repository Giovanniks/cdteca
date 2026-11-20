// Arquivo: include/curtidas.h | Autor: Giovanni (48079391)
#ifndef CURTIDAS_H
#define CURTIDAS_H

#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "musica.h"

#define MAX_CURTIDAS 50

// Estrutura para gerir as curtidas, avaliações e estatísticas das músicas
struct Curtida {
    int idMusica;       // ID da música (vinculada ao Módulo 2 do Vinicius)
    int estrelas;       // Avaliação de 1 a 5 estrelas
    int vezesOuvida;    // Contador de reproduções
    int favorita;       // 1 para sim, 0 para não
};

struct Curtida listaCurtidas[MAX_CURTIDAS];
int totalCurtidas = 0;

void salvarCurtidasCSV() {
    int i;
    FILE *arq = fopen("data/curtidas.csv", "w");
    
    if (arq == NULL) {
        printf("[ERRO] Nao foi possivel gravar data/curtidas.csv!\n");
        return;
    }
    
    for (i = 0; i < totalCurtidas; i++) {
        fprintf(arq, "%d;%d;%d;%d\n",
                listaCurtidas[i].idMusica,
                listaCurtidas[i].estrelas,
                listaCurtidas[i].vezesOuvida,
                listaCurtidas[i].favorita);
    }
    fclose(arq);
}

void carregarCurtidasCSV() {
    FILE *arq = fopen("data/curtidas.csv", "r");
    if (arq == NULL) return; // Se o arquivo ainda não existir, mantém totalCurtidas = 0

    totalCurtidas = 0;
    
    while (totalCurtidas < MAX_CURTIDAS &&
           fscanf(arq, "%d;%d;%d;%d\n",
                  &listaCurtidas[totalCurtidas].idMusica,
                  &listaCurtidas[totalCurtidas].estrelas,
                  &listaCurtidas[totalCurtidas].vezesOuvida,
                  &listaCurtidas[totalCurtidas].favorita) == 4) {
        totalCurtidas++;
    }
    fclose(arq);
}

//Função para registrar ou avaliar musica se ela ja existe
void registrarCurtida() {
	int idMusicaTemp;
	
	if (totalCurtidas >= MAX_CURTIDAS) {
        printf("\n[ERRO] O limite de registos de curtidas (%d) foi atingido!\n", MAX_CURTIDAS);
        return;
    }
    
    printf("\n--- [REGISTAR CURTIDA / AVALIAÇÃO] ---\n");
    printf("Digite o ID da musica que deseja curtir/avaliar: ");
    scanf("%d", &idMusicaTemp);
    
    if (buscarIndiceMusica(idMusicaTemp) == -1) {
        printf("[ERRO] Nao existe nenhuma musica cadastrada com o ID %d!\n", idMusicaTemp);
        printf("Cadastre a musica no Módulo 2 antes de avaliá-la.\n\n");
        return;
    }
    
    listaCurtidas[totalCurtidas].idMusica = idMusicaTemp;
    
    printf("Digite quantas vezes ouviu esta musica: ");
    scanf("%d", &listaCurtidas[totalCurtidas].vezesOuvida);
    
    
    do {
        printf("Atribua uma nota de 1 a 5 estrelas: ");
        scanf("%d", &listaCurtidas[totalCurtidas].estrelas);
        if (listaCurtidas[totalCurtidas].estrelas < 1 || listaCurtidas[totalCurtidas].estrelas > 5) {
            printf("[ALERTA] A nota tem de ser estritamente entre 1 e 5 estrelas!\n");
        }
    } while (listaCurtidas[totalCurtidas].estrelas < 1 || listaCurtidas[totalCurtidas].estrelas > 5);
    
    
    printf("Marcar como favorita? (1 - Sim / 0 - Não): ");
    scanf("%d", &listaCurtidas[totalCurtidas].favorita);
    
    totalCurtidas++;
    salvarCurtidasCSV();
    
    printf("\n[SUCESSO] Curtida e avaliação registadas com sucesso!\n");
}

//função para listar as curtidas
void listarCurtidas() {
int i;

printf("\n-- HISTÓRICO DE CURTIDAS E AVALIAÇÕES (%d itens) --\n", totalCurtidas);

if (totalCurtidas == 0) {
	printf("Ainda nenhuma música foi curtida ou avaliada.\n");
	return;
}

for (i = 0; i < totalCurtidas; i++) {
       //usa função do musicas.h
        int posMusica = buscarIndiceMusica(listaCurtidas[i].idMusica);
        
        printf("\nRegisto #%d\n", i + 1);
        printf("ID da Música: %d\n", listaCurtidas[i].idMusica);
        
        if (posMusica != -1) {
            printf("Nome da Música: %s\n", listaMusicas[posMusica].nomeMusica);
        } else {
            printf("Nome da Música: [Música não encontrada no catálogo]\n");
        }
        
        printf("Vezes Ouvida: %d\n", listaCurtidas[i].vezesOuvida);
        printf("Avaliação: %d/5 Estrelas\n", listaCurtidas[i].estrelas);
        
        if (listaCurtidas[i].favorita == 1) {
            printf("Favorita: Sim\n\n");
        } else {
            printf("Favorita: Não\n");
        }
        
        printf("------------------------------------\n");
    }

}

void atualizarAvaliacao() {
	int idMusicaBuscada;
    int i;
    int encontrado = -1;
    
    printf("\n-- ATUALIZAR AVALIAÇÃO / CURTIDA  --\n");
    
    if (totalCurtidas == 0) {
        printf("Ainda não existem curtidas registadas para atualizar.\n");
        return;
    }
    
    printf("Digite o ID da música cuja avaliação deseja atualizar: ");
    scanf("%d", &idMusicaBuscada);
    
    for (i = 0; i < totalCurtidas; i++) {
        if (listaCurtidas[i].idMusica == idMusicaBuscada) {
            encontrado = i;
            break;
        }
    }
	
	if (encontrado == -1) {
        printf("[ERRO] Não foi encontrada nenhuma curtida registada para a música com ID %d!\n", idMusicaBuscada);
        printf("Dica: Certifique-se de que já registou uma curtida para esta música (Opção 1).\n");
        return;
    }
    
    printf("\n[ENCONTRADO] A atualizar o registo da música ID %d:\n", idMusicaBuscada);
    
    printf("Novo número de vezes ouvida (atual: %d): ", listaCurtidas[encontrado].vezesOuvida);
    scanf("%d", &listaCurtidas[encontrado].vezesOuvida);
    
    do {
        printf("Atribua a nova nota de 1 a 5 estrelas (atual: %d): ", listaCurtidas[encontrado].estrelas);
        scanf("%d", &listaCurtidas[encontrado].estrelas);
        if (listaCurtidas[encontrado].estrelas < 1 || listaCurtidas[encontrado].estrelas > 5) {
            printf("[ALERTA] A nota tem de ser estritamente entre 1 e 5 estrelas!\n");
        }
    } while (listaCurtidas[encontrado].estrelas < 1 || listaCurtidas[encontrado].estrelas > 5);
    
    printf("Marcar como favorita? (1 - Sim / 0 - Não) (atual: %d): ", listaCurtidas[encontrado].favorita);
    scanf("%d", &listaCurtidas[encontrado].favorita);
    
    salvarCurtidasCSV();
    
    printf("\n[SUCESSO] Avaliação atualizada e salva no ficheiro com sucesso!\n");
    
}

void relatorioMusicaMaisOuvida() {
	int i;
    int indiceMaisOuvida = 0;
    int maiorReproducoes = -1;
    
    printf("\n-- RELATÓRIO: MÚSICA MAIS OUVIDA --\n");
    
    if (totalCurtidas == 0) {
        printf("Ainda não existem curtidas ou reproduções registadas.\n");
        return;
    }
    
    for (i = 0; i < totalCurtidas; i++) {
        if (listaCurtidas[i].vezesOuvida > maiorReproducoes) {
            maiorReproducoes = listaCurtidas[i].vezesOuvida;
            indiceMaisOuvida = i;
        }
    }
    
    int idAlvo = listaCurtidas[indiceMaisOuvida].idMusica;
    int posMusica = buscarIndiceMusica(idAlvo);
    
    
    printf("\n A música mais ouvida até ao momento:\n");
    if (posMusica != -1) {
        printf("Nome: %s\n", listaMusicas[posMusica].nomeMusica);
        printf("Duração: %.2f min\n", listaMusicas[posMusica].duracaoMinutos);
        printf("ID da Música: %d\n", idAlvo);
    } else {
        printf("ID da Música: %d (Aviso: Música não encontrada no catálogo atual)\n", idAlvo);
    }
    
    printf("Total de reproduções (Vezes Ouvida): %d\n", listaCurtidas[indiceMaisOuvida].vezesOuvida);
    printf("Avaliação atribuída: %d/5 Estrelas\n", listaCurtidas[indiceMaisOuvida].estrelas);
    
    if (listaCurtidas[indiceMaisOuvida].favorita == 1) {
        printf("Marcada como Favorita: Sim\n");
    } else {
        printf("Marcada como Favorita: Não\n");
    }
    
    printf("------------------------------------\n");    
}

void moduloCurtidasRelatorios() {
    int opcaoCurtida;
    setlocale(LC_ALL, "Portuguese");
    do {
        printf("\n--- [MÓDULO 4: CURTIDAS E RELATÓRIOS (Giovanni)] ---\n");
        printf("1. Registar Música Curtida / Favorita\n");
        printf("2. Listar Histórico de Curtidas\n");
        printf("3. Atualizar Nota ou Vezes Ouvida\n");
        printf("4. [RELATÓRIO] Música Mais Ouvida\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma ação: ");
        scanf("%d", &opcaoCurtida);

        switch (opcaoCurtida) {
            case 1:
                registrarCurtida();
                break;
            case 2:
                listarCurtidas();
                break;
            case 3:
                atualizarAvaliacao();
                break;
            case 4:
                relatorioMusicaMaisOuvida();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida no Módulo de Curtidas e Relatórios!\n");
        }
    } while (opcaoCurtida != 0);
}

#endif
