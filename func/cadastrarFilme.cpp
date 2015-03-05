#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "..\lib\conio.c"
char arquivoCliente[25] = {"..\\save\\cliente.dat"};
char arquivoLocadev[25] = {"..\\save\\locadev.dat"};
char arquivoFilme[25] = {"..\\save\\filme.dat"};
char arquivoCategoria[25] = {"..\\save\\categoria.dat"};
char arquivoGenero[20] = {"..\\save\\genero.dat"};

#include "..\variaveis.h"
#include "..\funcoes.h"

int selecionarGenero(){//SLECIONAR O GENERO
     system("start selecionarGenero.exe");
     FILE *fparquivo;
     struct reg_genero genero;
     int cod = 0;
     while((fparquivo = fopen("selecionarGenero.dat","rb"))==NULL)
         _sleep(1000);

    fread(&cod,sizeof(cod),1,fparquivo);
    fclose(fparquivo);
    _sleep(1000);
    system("Del selecionarGenero.dat");
    return cod;
}//FIM selecionarGenero

int selecionarCategoria(){//SELECIONAR A CATEGORIA
     system("start selecionarCategoria.exe");
     FILE *fparquivo;
     struct reg_categoria categoria;
     int cod = 0;

     while((fparquivo = fopen("selecionarCategoria.dat","rb"))==NULL)
         _sleep(1000);

     fread(&cod,sizeof(cod),1,fparquivo);
     fclose(fparquivo);
     _sleep(1000);
     system("Del selecionarCategoria.dat");

     return cod;
}//FIM selecionarCategoria

main(){
    criarTela(240,1,40,20,"CADASTRAR FILME");
    struct reg_filme filme;
    struct reg_genero genero;
    struct reg_categoria categoria;
    FILE *fpfilme;
    FILE *fpgenero;
    FILE *fpcategoria;
    int codigo_genero = 1;
    int codigo_categoria = 1;
    int a = 1;

    while(a==1){
        filme.codigo = gerarCodigo(arquivoFilme);

        texto(2,3,3,"C\242digo: "); printf("%i",filme.codigo);
        texto(2,5,3,"Titulo:");
        texto(2,7,3,"G\210nero:");
        texto(2,9,3,"Categoria:");
        texto(2,11,3,"Pre\207o:");

        campo(10,6,38,6,3,"\304");
//--------------------TITULO DO FILME
        campoDeString(10,5,sizeof(filme.titulo),COR_LETRA,BLACK,&filme.titulo[0]);
//--------------------GÊNERO
        codigo_genero = selecionarGenero();
        fpgenero = fopen(arquivoGenero,"rb");
        while (fread(&genero,sizeof(genero),1,fpgenero)==1)
            if(codigo_genero==genero.codigo)
                break;
        fclose(fpgenero);
        texto(10,7,COR_LETRA,genero.genero);
//--------------------GÊNERO
        codigo_categoria = selecionarCategoria();
        fpcategoria = fopen(arquivoCategoria,"rb");
        while (fread(&categoria,sizeof(categoria),1,fpcategoria)==1)
            if(codigo_categoria==categoria.codigo)
                break;
        fclose(fpcategoria);
        texto(13,9,COR_LETRA,categoria.categoria);
        gotoxy(9,11);
        printf("R$%5.2f",categoria.preco);
//-----------------------
        int b = 1;
        while(b==1){
            textoDoMenu(2,13,1,"Gravar e sair",COR_LETRA);
            textoDoMenu(2,15,2,"Gravar e continuar",COR_LETRA);
            textoDoMenu(2,17,3,"N\306o gravar",COR_LETRA);
            andarMenu(3);
            if(TECLA==27) return 0; //tecla esc
            if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
                if(OPC==1){ //GRAVAR E SAIR----------------------------
                    filme.codigo = gerarCodigo(arquivoFilme);
                    filme.genero = codigo_genero;
                    filme.categoria = codigo_categoria;
                    filme.situacao = 0;
                    fpfilme = fopen(arquivoFilme,"ab+");
                    fwrite(&filme,sizeof(filme),1,fpfilme);
                    fclose(fpfilme);
                    texto(2,17,GREEN,"Cadastro efetuado com sucesso");
                    _sleep(3000);
                    return 0;
                }
                if(OPC==2){ //GRAVAR E CONTINUAR------------------------
                    filme.codigo = gerarCodigo(arquivoFilme);
                    filme.genero = codigo_genero;
                    filme.categoria = codigo_categoria;
                    filme.situacao = 0;
                    fpfilme = fopen(arquivoFilme,"ab+");
                    fwrite(&filme,sizeof(filme),1,fpfilme);
                    fclose(fpfilme);
                    texto(2,17,GREEN,"Cadastro efetuado com sucesso");
                    _sleep(3000);
                    b = 2;
                    campo(5,5,79,24,BLACK," ");
                }
                if(OPC==3)return 0;//NAO GRAVAR E SAIR----------------------
            }//FIM TELCA ENTER
        }//FIM WHILE b
    }//FIM WHILE a
}
