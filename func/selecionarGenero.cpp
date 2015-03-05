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
    criarTela(200,1,33,opcoes.itens_pagina+3,"SELECIONAR GENERO");    
    FILE *fpgenero;
    struct reg_genero genero;  
    int cod;                
    int a = 1; 
    int auxY = 2;
    int aux = 1;
    int pagina = 1;
    int paginas = 0;
    int aux_ordem = 1;
    
    paginas = quantidadeDePaginas(arquivoGenero);

    while(a==1){     
        aux = 1;
        auxY = 2;
        fpgenero = fopen(arquivoGenero,"rb");
        fseek(fpgenero,(pagina-1)*sizeof(genero)*opcoes.itens_pagina, 0);
        while ((fread(&genero,sizeof(genero),1,fpgenero) ==1)&&(aux<=opcoes.itens_pagina)){
            textoDoMenu(2,auxY,aux,genero.genero,COR_LETRA); 
            auxY++;
            aux++;   
        }        
        fclose(fpgenero);
            
        textoDoMenu(2,opcoes.itens_pagina+2,aux,"<<<<",COR_MENU);          
        textoDoMenu(13,opcoes.itens_pagina+2,aux+1,"Adicionar",COR_MENU);
        textoDoMenu(24,opcoes.itens_pagina+2,aux+2,">>>>",COR_MENU);
        andarMenu(aux+2);
        if (TECLA==13){
            if(OPC==aux) {OPC = 1; pagina--; if(pagina<1) pagina = paginas; campo(2,2,32,opcoes.itens_pagina+1,BLACK," ");}
            else if(OPC==aux+1) {system("start cadastrarGenero.exe"); getch(); system("start selecionarGenero.exe"); exit(0);}
            else if(OPC==aux+2) {OPC = 1; pagina++; if(pagina>paginas) pagina = 1; campo(2,2,32,opcoes.itens_pagina+1,BLACK," ");}
            else{            
                cod = OPC+((pagina-1)*opcoes.itens_pagina);
                fpgenero = fopen(arquivoGenero,"rb");     
                fseek(fpgenero,sizeof(genero)*(cod-1),0);
                fread(&genero,sizeof(genero),1,fpgenero);
                fclose(fpgenero);
                cod = genero.codigo;
                a = 2;
            }
        }                                     
    }//FIM DO WHILE A
    fpgenero = fopen("selecionarGenero.dat","wb");
    fwrite(&cod,sizeof(cod),1,fpgenero); 
    fclose(fpgenero);
    return 0;
}//FIM MAIN      
