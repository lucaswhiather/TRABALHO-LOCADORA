/*
TRABALHO DE ESTRUTURA DE DADOS

Nome: LUCAS WHIATHER ABRÃO DE SOUZA
Periodo: VESPERTINO

LOCADORA
Versão: 1.97
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "lib\conio.c"

#include "variaveis.h"
char arquivoCliente[25] = {"save\\cliente.dat"};
char arquivoLocadev[25] = {"save\\locadev.dat"};
char arquivoFilme[25] = {"save\\filme.dat"};
char arquivoCategoria[25] = {"save\\categoria.dat"};
char arquivoGenero[20] = {"save\\genero.dat"};
char arquivoOpcoes[20] = {"save\\opcoes.dat"};

int tamanhoProgramaX = 70;
int tamanhoProgramaY = 25;
#include "funcoes.h"
#include "cliente.h"
#include "filme.h"
#include "locadev.h"
#include "opcoes.h"

main(){
    criarTela(200,200,tamanhoProgramaX,tamanhoProgramaY,"LOCADORA",FALSE);
    configurarOpcoes("carregar");
    campo(1,5,tamanhoProgramaX,6,7,"\333");
    campo(4,1,4,tamanhoProgramaY,7,"\333");
    texto(7,2,RED,"VIDEO LOCADORA 1.97");
    texto(30,4,GREEN,"Lucas Whiather Abrao de Souza");

    int a = 1;
    while(a==1){
        textoDoMenu(7,8,1,"Cliente",COR_MENU);
        textoDoMenu(7,10,2,"Filme",COR_MENU);
        textoDoMenu(7,12,3,"Locacao",COR_MENU);
        textoDoMenu(7,14,4,"Estatiticas",COR_MENU);
        textoDoMenu(7,16,5,"Opcoes",COR_MENU);
        textoDoMenu(7,18,6,"Sair",COR_MENU);
        andarMenu(6);

        if(TECLA==27) return 0; //tecla esc
        if(TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1) menuPrincipalCliente();
            else if(OPC==2) menuPrincipalFilme();                      //MENU FILME
            else if(OPC==3) menuPrincipalLocacao();                    //MENU LOCAÇÃO
            else if(OPC==4) {}                                         //ESTATITICAS
            else if(OPC==5) menuPrincipalOpcoes();                     //OPÇÕES
            else if(OPC==6) return 0;                                  //SAIR
        }
    }//FIM DO WHILE A
}//FIM MAIN
