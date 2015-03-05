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
    criarTela(200,1,45,opcoes.itens_pagina+9,"LISTA DE CLIENTES");
    char arquivo[20] = {"..\\save\\cliente.dat"};
    struct reg_cliente cliente;
    FILE *fpcliente;
    int pagina = 1;
    int paginas = 0;
    int a = 1;
    int quantidade = 0;

    quantidade = quantidadeDeRegistro(arquivo);

    if(quantidade==0){
        texto(2,2,RED,"Nenhum cliente cadastrado");
        textoDoMenu(2,4,1,"Sair",COR_MENU);
        getch();
        return 0;
    }

    paginas = (quantidade/opcoes.itens_pagina);
    if(quantidade%opcoes.itens_pagina != 0)
        paginas++;

    textoDoMenu(2,2,5,"Clientes cadastrados:",COR_LETRA);
    printf(" %i", quantidade);

    texto(2,4,GREEN,"C\242digo");
    texto(12,4,GREEN,"Nome");

    while(a==1){
        int aux = 1;
        int auxY = 5;
        campo(2,5,45,opcoes.itens_pagina+4,BLACK," ");
        gotoxy(36,2);
        printf("P\240gina: %i",pagina);

        fpcliente = fopen(arquivo,"rb");
        fseek(fpcliente,(pagina-1)*sizeof(cliente)*opcoes.itens_pagina, 0);
        while ((fread(&cliente,sizeof(cliente),1,fpcliente) ==1)&&(aux<=opcoes.itens_pagina)){
            gotoxy(2,auxY);
            printf("%i",cliente.codigo);
            gotoxy(12,auxY);
            printf("%s",cliente.nome);
            auxY++;
            aux++;
        }
        fclose(fpcliente);

        int b = 1;
        while(b==1){
            textoDoMenu(2,opcoes.itens_pagina+7,1,"<<<<",COR_MENU);
            textoDoMenu(8,opcoes.itens_pagina+7,2,"Sair",COR_MENU);
            textoDoMenu(13,opcoes.itens_pagina+7,3,"Atualizar",COR_MENU);
            textoDoMenu(30,opcoes.itens_pagina+7,4,">>>>",COR_MENU);
            andarMenu(4);
            if(TECLA==27) return 0; //tecla esc
            if (TECLA==13){
                if(OPC==1){ pagina--; if(pagina<1) pagina = paginas; b = 2;}   //voltar pagina
                else if(OPC==2)return 0;                           //sair
                else if(OPC==3){system("start listarCliente.exe"); exit(0);}        //atualizar
                else if(OPC==4){ pagina++; if(pagina>paginas) pagina = 1; b = 2;}   //avançar pagina
            }
        }//FIM WHILE b
    }//FIM WHILE a
}
