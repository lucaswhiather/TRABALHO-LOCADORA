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
char arquivoOpcoes[20] = {"..\\save\\opcoes.dat"};
#include "..\variaveis.h"
#include "..\funcoes.h"

main(){
    int itens_pagina = 5;
    criarTela(200,1,69,20,"LISTA DE LOCAÇÕES",TRUE);
    FILE *fplocadev;
    FILE *fpfilme;
    FILE *fpcliente;
    struct reg_locadev locadev;
    struct reg_filme filme;
    struct reg_cliente cliente;
    struct data data;
    int pagina = 1;
    int paginas = 0;
    int a = 1;
    int quantidade = 0;
    char dataString[20];

    quantidade = quantidadeDeRegistro(arquivoLocadev);
    paginas = (quantidade/itens_pagina);
    if(quantidade%itens_pagina != 0)
        paginas++;

    textoDoMenu(2,2,5,"Loca\207\344es feitas:",COR_LETRA);
    printf(" %i", quantidade);

    texto(2,4,GREEN,"Data loca\207\306o");
    texto(20,4,GREEN,"Filme / Cliente");
    texto(53,4,GREEN,"Data devolu\207\306o");

    while(a==1){
        int aux = 1;
        int auxY = 5;
        int b = 1;
        campo(2,5,69,(itens_pagina*3)+4,BLACK," ");
        fplocadev = fopen(arquivoLocadev,"rb");
        fseek(fplocadev,(pagina-1)*sizeof(locadev)*itens_pagina, 0);
        while ((fread(&locadev,sizeof(locadev),1,fplocadev) ==1)&&(aux<=itens_pagina)){
            //-------------------------informa a data de locação----------------------
            gotoxy(2,auxY);
            strcpy(dataString,dataFormatada(locadev.locacao,1,FALSE));
            printf("%s",dataString);
            gotoxy(2,auxY+1);
            strcpy(dataString,dataFormatada(locadev.locacao,2,FALSE));
            printf("%s",dataString);

            //-------------------------informa a data de devolução--------------------
            if(locadev.devolucao.dia>0){
                gotoxy(53,auxY);
                strcpy(dataString,dataFormatada(locadev.devolucao,1,FALSE));
                printf("%s",dataString);
                gotoxy(53,auxY+1);
                strcpy(dataString,dataFormatada(locadev.devolucao,2,FALSE));
                printf("%s",dataString);

            }else
                texto(53,auxY,RED,"Nao encerrada");
            //-------------------------busca o titulo do filme-----------------------
            gotoxy(20,auxY);
            fpfilme = fopen(arquivoFilme,"rb");
            while (fread(&filme,sizeof(filme),1,fpfilme)==1)
                if(locadev.filme==filme.codigo)
                    break;
            fclose(fpfilme);

            if(locadev.filme==filme.codigo)
                printf("%s",filme.titulo);
            else
                texto(20,auxY,RED,"Filme deletado");
            //-------------------------busca o nome do cliente-----------------------
            fpcliente = fopen(arquivoCliente,"rb");
            while(fread(&cliente,sizeof(cliente),1,fpcliente)==1)
                if(locadev.cliente==cliente.codigo)
                    break;
            fclose(fpcliente);
            if(locadev.cliente==cliente.codigo)
                texto(20,auxY+1,COR_LETRA,cliente.nome);
            else
                texto(20,auxY+1,RED,"Cliente deletado");
            //----------------------------------------------------------------------
            auxY = auxY+3;
            aux++;
        }
        fclose(fplocadev);
        while(b==1){
            gotoxy(58,2);
            printf("P\240gina: %i",pagina);
            textoDoMenu(22,(itens_pagina*3)+6,1,"<<<<",COR_MENU);
            textoDoMenu(28,(itens_pagina*3)+6,2,"Sair",COR_MENU);
            textoDoMenu(33,(itens_pagina*3)+6,3,"Atualizar",COR_MENU);
            textoDoMenu(43,(itens_pagina*3)+6,4,">>>>",COR_MENU);
            andarMenu(4);
            if(TECLA==27) return 0; //tecla esc
            if (TECLA==13){
                if(OPC==1){ pagina--; if(pagina<1) pagina = paginas; b = 2;}        //voltar pagina
                else if(OPC==2) return 0;                                           //sair
                else if(OPC==3){system("start listarLocacao.exe"); exit(0);}        //atualizar
                else if(OPC==4){ pagina++; if(pagina>paginas) pagina = 1; b = 2;}   //avançar pagina
            }
        }//FIM WHILE b
    }//FIM WHILE a
}//FIM MAIN
