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
    criarTela(200,1,42,opcoes.itens_pagina+3,"SELECIONE A CATEGORIA");    
    FILE *fpcategoria;
    
    struct reg_categoria categoria;  
    int cod;                
    int a = 1; 
    int auxY = 2;
    int aux = 1;
    int pagina = 1;
    int paginas = 0;
    int aux_ordem = 1;
    int quantidade = 0;
  
    quantidade = quantidadeDeRegistro(arquivoCategoria);    
    paginas = (quantidade/opcoes.itens_pagina);    
    if(quantidade%opcoes.itens_pagina != 0)
        paginas++;

    while(a==1){     
        aux = 1;
        auxY = 2;
        fpcategoria = fopen(arquivoCategoria,"rb");
        fseek(fpcategoria,(pagina-1)*sizeof(categoria)*opcoes.itens_pagina, 0);
        while ((fread(&categoria,sizeof(categoria),1,fpcategoria) ==1)&&(aux<=opcoes.itens_pagina)){
            textoDoMenu(2,auxY,aux,categoria.categoria,COR_LETRA); 
            gotoxy(33,auxY);
            printf("R$ %5.2f",categoria.preco);
            auxY++;
            aux++;   
        }        
        fclose(fpcategoria);
            
        textoDoMenu(2,opcoes.itens_pagina+2,aux,"<<<<",COR_MENU);          
        textoDoMenu(10,opcoes.itens_pagina+2,aux+1,"Adicionar",COR_MENU);
        textoDoMenu(23,opcoes.itens_pagina+2,aux+2,">>>>",COR_MENU);
        andarMenu(aux+2); 
        if (TECLA==13){
            if(OPC==aux) {OPC = 1; pagina--; if(pagina<1) pagina = paginas; campo(2,2,42,opcoes.itens_pagina+1,BLACK," ");}
            else if(OPC==aux+1) {system("start cadastrarCategoria.exe"); getch(); system("start selecionarCategoria.exe"); exit(0);}
            else if(OPC==aux+2) {OPC = 1; pagina++; if(pagina>paginas) pagina = 1; campo(2,2,42,opcoes.itens_pagina+1,BLACK," ");}
            else{            
                cod = OPC+((pagina-1)*opcoes.itens_pagina);
                fpcategoria = fopen(arquivoCategoria,"rb");     
                fseek(fpcategoria,sizeof(categoria)*(cod-1),0);
                fread(&categoria,sizeof(categoria),1,fpcategoria);
                fclose(fpcategoria);
                cod = categoria.codigo;
                a = 2;
            }
        }                                     
    }//FIM DO WHILE A
    fpcategoria = fopen("selecionarCategoria.dat","wb");
    fwrite(&cod,sizeof(cod),1,fpcategoria); 
    fclose(fpcategoria);
    return 0;
}//FIM MAIN      
