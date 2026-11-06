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
