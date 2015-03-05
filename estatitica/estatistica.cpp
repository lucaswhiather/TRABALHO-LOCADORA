#include "funcoes.h"

main(){
    //criarTela(200,1,45,20,"ESTATISTICAS");
    char arquivoFilme[20] = {"save\\filme.dat"};
    FILE *fpcliente;
    FILE *fpfilme;
    FILE *fplocadev;
    FILE *fpcategoria;
    FILE *fpgenero;
    struct reg_cliente cliente;
    struct reg_filme filme;
    int quantidade = quantidadeDeRegistro(arquivoFilme);
    printf("Quantidade = %i",quantidade);
    //int codigo_filme[4];
    char titulo_filme[quantidade][30];
    int aux = 0;
    texto(2,2,GREEN,"Titulo");
    texto(34,2,GREEN,"Locacoes");

    texto(2,4,BLUE,"Filmes mais locados");
    fpfilme = fopen(arquivoFilme,"rb");
    while (fread(&filme,sizeof(filme),1,fpfilme)==1){
        int verificador = 0;
        for(int x = 0; x<quantidade; x++)
            if(strcmp(filme.titulo,titulo_filme[aux])==0)
                verificador = 1;
        printf("Verificador = %i",verificador);
        getch();
        if(verificador==0)
            strcpy(titulo_filme[aux],filme.titulo);
        aux++;
    }

    getch();
    for(int x = 0; x<aux; x++)
        printf("\nTitulo = %s",titulo_filme[x]);



    fclose(fpfilme);




    texto(2,19,BLUE,"Filmes nunca locados");
    getch();
}
