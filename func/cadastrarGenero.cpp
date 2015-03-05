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
    criarTela(240,1,40,12,"CADASTRAR GÊNERO");
    struct reg_genero genero;
    FILE *fpgenero;

    int a = 1;
    while(a==1){
        int b = 1;
        genero.codigo = gerarCodigo(arquivoGenero);

        texto(2,3,3,"C\242digo: "); printf("%i",genero.codigo);
        texto(2,5,3,"G\210nero:");

        campoDeString(10,5,sizeof(genero.genero),COR_LETRA,BLACK,&genero.genero[0]);

        while(b==1){
            textoDoMenu(2,7,1,"Gravar e sair",COR_LETRA);
            textoDoMenu(2,9,2,"Gravar e continuar",COR_LETRA);
            textoDoMenu(2,11,3,"N\306o gravar",COR_LETRA);
            andarMenu(3);
            if(TECLA==27) return 0; //tecla esc
            if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
                if(OPC==1){ //GRAVAR E SAIR----------------------------
                    genero.codigo = gerarCodigo(arquivoGenero);
                    fpgenero = fopen(arquivoGenero,"ab+");
                    fwrite(&genero,sizeof(genero),1,fpgenero);
                    fclose(fpgenero);
                    texto(2,11,GREEN,"Cadastro efetuado com sucesso");
                    _sleep(3000);
                    return 0;
                }
                if(OPC==2){ //GRAVAR E CONTINUAR------------------------
                    genero.codigo = gerarCodigo(arquivoGenero);
                    fpgenero = fopen(arquivoGenero,"ab+");
                    fwrite(&genero,sizeof(genero),1,fpgenero);
                    fclose(fpgenero);
                    b = 2;
                    texto(2,11,GREEN,"Cadastro efetuado com sucesso");
                    _sleep(3000);
                    campo(5,10,79,24,BLACK," ");
                }
                if(OPC==3)return 0;//NAO GRAVAR E SAIR
            }//FIM TELCA ENTER
        }//FIM WHILE b
    }//FIM WHILE a
}//FIM main
