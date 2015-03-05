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

main(){
    configurarOpcoes("carregar");
    criarTela(200,1,73,opcoes.itens_pagina+12,"LISTA DE FILMES");
    struct reg_filme filme;
    struct reg_genero genero;
    struct reg_categoria categoria;
    FILE *fpfilme;
    FILE *fpgenero;
    FILE *fpcategoria;
    int pagina = 1;
    int paginas = 0;
    int a = 1;
    int quantidade = 0;
    char filtro[30] = {"\0"};

    quantidade = quantidadeDeRegistro(arquivoFilme);
    paginas = (quantidade/opcoes.itens_pagina);
    if(quantidade%opcoes.itens_pagina != 0)
        paginas++;

    textoDoMenu(2,2,5,"Filmes cadastrados:",COR_LETRA);
    printf(" %i", quantidade);
    texto(2,4,GREEN,"C\242digo");
    texto(12,4,GREEN,"Titulo");
    texto(34,4,GREEN,"G\210nero");
    texto(65,4,GREEN,"Pre\207o");

    while(a==1){
        campo(2,5,73,opcoes.itens_pagina+4,BLACK," ");
        int aux = 1;
        int auxY = 5;
        fpfilme = fopen(arquivoFilme,"rb");
        fseek(fpfilme,(pagina-1)*sizeof(filme)*opcoes.itens_pagina, 0);
        while ((fread(&filme,sizeof(filme),1,fpfilme) ==1)&&(aux<=opcoes.itens_pagina)){
            gotoxy(2,auxY);
            printf("%i",filme.codigo);
            texto(12,auxY,COR_LETRA,filme.titulo);
            fpgenero = fopen(arquivoGenero,"rb");
            while (fread(&genero,sizeof(genero),1,fpgenero)==1)
                if(filme.genero==genero.codigo)
                    break;
            fclose(fpgenero);

            texto(34,auxY,COR_LETRA,genero.genero);
            fpcategoria = fopen(arquivoCategoria,"rb");
            while (fread(&categoria,sizeof(categoria),1,fpcategoria)==1)
                if(filme.categoria==categoria.codigo)
                    break;
            fclose(fpcategoria);
            gotoxy(65,auxY);
            printf("%5.2f",categoria.preco);
            auxY++;
            aux++;
        }//FIM WHILE leitura filme
        fclose(fpfilme);

        int b = 1;
        while(b==1){
            gotoxy(36,2);
            printf("Pagina: %i",pagina);

            textoDoMenu(2,opcoes.itens_pagina+7,1,"<<<<",COR_MENU);
            textoDoMenu(8,opcoes.itens_pagina+7,2,"Sair",COR_MENU);
            textoDoMenu(15,opcoes.itens_pagina+7,3,"Atualizar",COR_MENU);
            textoDoMenu(41,opcoes.itens_pagina+7,4,">>>>",COR_MENU);
            andarMenu(4);
            if(TECLA==27) return 0; //tecla esc
            if (TECLA==13){
                if(OPC==1){ pagina--; if(pagina<1) pagina = paginas; b = 2;}   //voltar pagina
                if(OPC==2){a = 2; b = 2;; OPC = 1;}                             //sair
                if(OPC==3){system("start listarFilme.exe"); return 0;}        //atualizar
                if(OPC==4){ pagina++; if(pagina>paginas) pagina = 1; b = 2;}   //avançar pagina
            }//FIM TECLA ENTER
        }//FIM WHILE b
    }//FIM WHILE a
}
