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
    criarTela(240,1,40,20,"CADASTRAR CLIENTE");
    FILE *fpcliente;
    struct reg_cliente cliente;

    int a = 1;
    while(a==1){
        cliente.codigo = gerarCodigo(arquivoCliente);

        texto(2,3,3,"C\242digo: "); printf("%i",cliente.codigo);
        texto(2,5,3,"Nome:");
        texto(2,7,3,"Rua:");
        texto(2,9,3,"N\247:");
        texto(2,11,3,"Telefone:");
        texto(2,13,3,"Email:");

        campo(8,6,38,6,3,"\304");    //nome
        campo(7,8,38,8,3,"\304");    //rua
        campo(6,10,12,10,3,"\304");  //nº
        campo(12,12,25,12,3,"\304"); //telefone
        campo(9,14,38,14,3,"\304");  //email

        campoDeString(8,5,sizeof(cliente.nome),COR_LETRA,BLACK,&cliente.nome[0]);
        campoDeString(7,7,sizeof(cliente.end_rua),COR_LETRA,BLACK,&cliente.end_rua[0]);
        campoDeInt(6,9,5,COR_LETRA,BLACK,&cliente.end_numero);
        campoDeInt(12,11,10,COR_LETRA,BLACK,&cliente.telefone);
        campoDeString(9,13,sizeof(cliente.email),COR_LETRA,BLACK,&cliente.email[0]);
        int b = 1;
        while(b==1){
            textoDoMenu(2,15,1,"Gravar e sair",COR_LETRA);
            textoDoMenu(2,17,2,"Gravar e continuar",COR_LETRA);
            textoDoMenu(2,19,3,"N\306o gravar",COR_LETRA);
            andarMenu(3);
            if(TECLA==27) return 0; //tecla esc
            if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
                if(OPC==1){ //GRAVAR E SAIR----------------------------
                    cliente.codigo = gerarCodigo(arquivoCliente);
                    fpcliente = fopen(arquivoCliente,"ab+");
                    fwrite(&cliente,sizeof(cliente),1,fpcliente);
                    fclose(fpcliente);
                    texto(2,19,GREEN,"Cadastro efetuado com sucesso");
                    _sleep(3000);
                    return 0;
                }
                if(OPC==2){ //GRAVAR E CONTINUAR------------------------
                    cliente.codigo = gerarCodigo(arquivoCliente);
                    fpcliente = fopen(arquivoCliente,"ab+");
                    fwrite(&cliente,sizeof(cliente),1,fpcliente);
                    fclose(fpcliente);
                    texto(2,19,GREEN,"Cadastro efetuado com sucesso");
                    _sleep(3000);
                    b = 2;
                    campo(5,5,79,24,BLACK," ");
                }
                if(OPC==3){b = 2; a = 2;} //VOLAR
            }
        }//FIM WHILE b
    }//FIM WHILE a
}
