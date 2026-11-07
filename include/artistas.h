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
                    for (int i = 0; i < totalArtistas; i++) {
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

                for (int i = 0; i < totalArtistas; i++) {
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

