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
    criarTela(200,1,44,opcoes.itens_pagina+3,"SELECIONAR FILME");    
    FILE *fpfilme;
    struct reg_filme filme;  
    int cod;                
    int a = 1; 
    int auxY = 2;
    int aux = 1;
    int pagina = 1;
    int paginas = 0;
    int aux_ordem = 1;
    
    paginas = quantidadeDePaginas(arquivoFilme);

    while(a==1){     
        aux = 1;
        auxY = 2;
        fpfilme = fopen(arquivoFilme,"rb");
        fseek(fpfilme,(pagina-1)*sizeof(filme)*opcoes.itens_pagina, 0);
        while ((fread(&filme,sizeof(filme),1,fpfilme) ==1)&&(aux<=opcoes.itens_pagina)){
            textoDoMenu(2,auxY,aux,filme.titulo,COR_LETRA); 
            if(filme.situacao==0)texto(34,auxY,GREEN,"Disponivel");
            else texto(34,auxY,RED,"Alugado");
            auxY++;
            aux++;   
        }        
        fclose(fpfilme);
            
        textoDoMenu(16,opcoes.itens_pagina+2,aux,"<<<<",COR_MENU);          
        textoDoMenu(24,opcoes.itens_pagina+2,aux+1,">>>>",COR_MENU);
        andarMenu(aux+1);
        if (TECLA==13){
            if(OPC==aux) {OPC = 1; pagina--; if(pagina<1) pagina = paginas; campo(2,2,43,opcoes.itens_pagina+1,BLACK," ");}
            else if(OPC==aux+1) {OPC = 1; pagina++; if(pagina>paginas) pagina = 1; campo(2,2,43,opcoes.itens_pagina+1,BLACK," ");}
            else{            
                cod = OPC+((pagina-1)*opcoes.itens_pagina);
                fpfilme = fopen(arquivoFilme,"rb");     
                fseek(fpfilme,sizeof(filme)*(cod-1),0);
                fread(&filme,sizeof(filme),1,fpfilme);
                fclose(fpfilme);
                cod = filme.codigo;
                a = 2;
            }
        }                                     
    }//FIM DO WHILE A
    fpfilme = fopen("selecionarFilme.dat","wb");
    fwrite(&cod,sizeof(cod),1,fpfilme); 
    fclose(fpfilme);
    return 0;
}//FIM MAIN      
