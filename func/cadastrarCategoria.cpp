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
    criarTela(240,1,40,14,"CADASTRAR CATEGORIA");
    struct reg_categoria categoria;
    FILE *fpcategoria;

    int a = 1;
    while(a==1){
        categoria.codigo = gerarCodigo(arquivoCategoria);

        texto(2,3,3,"C\242digo: "); printf("%i",categoria.codigo);
        texto(2,5,3,"Categoria:");
        texto(2,7,3,"Pre\207o:");

        campoDeString(13,5,sizeof(categoria.categoria),COR_LETRA,BLACK,&categoria.categoria[0]);
        campoDeFloat(9,7,7,COR_LETRA,BLACK,&categoria.preco);
        int b = 1;
        while(b==1){
            textoDoMenu(2,9,1,"Gravar e sair",COR_LETRA);
            textoDoMenu(2,11,2,"Gravar e continuar",COR_LETRA);
            textoDoMenu(2,13,3,"N\306o gravar",COR_LETRA);
            andarMenu(3);
            if(TECLA==27) return 0; //tecla esc
            if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
                if(OPC==1){ //GRAVAR E SAIR----------------------------
                    categoria.codigo = gerarCodigo(arquivoCategoria);
                    fpcategoria = fopen(arquivoCategoria,"ab+");
                    fwrite(&categoria,sizeof(categoria),1,fpcategoria);
                    fclose(fpcategoria);
                    texto(2,13,GREEN,"Cadastro efetuado com sucesso");
                    _sleep(3000);
                    return 0;
                }
                else if(OPC==2){ //GRAVAR E CONTINUAR------------------------
                    categoria.codigo = gerarCodigo(arquivoCategoria);
                    fpcategoria = fopen(arquivoCategoria,"ab+");
                    fwrite(&categoria,sizeof(categoria),1,fpcategoria);
                    fclose(fpcategoria);
                    b = 2;
                    texto(2,13,GREEN,"Cadastro efetuado com sucesso");
                    _sleep(3000);
                    campo(5,10,79,24,BLACK," ");
                }
                else if(OPC==3)return 0; //NAO GRAVAR E SAIR------------------
            }//FIM TELA ENTER
        }//FIM WHILE b
    }//FIM WHILE a
}//FIM main
