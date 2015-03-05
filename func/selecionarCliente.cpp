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
    criarTela(200,1,33,opcoes.itens_pagina+3,"SELECIONAR CLIENTE");    
    FILE *fpcliente;
    struct reg_cliente cliente;  
    int cod;                
    int a = 1; 
    int auxY = 2;
    int aux = 1;
    int pagina = 1;
    int paginas = 0;
    int aux_ordem = 1;
    int quantidade = 0;
  
    quantidade = quantidadeDeRegistro(arquivoCliente);
    
    paginas = (quantidade/opcoes.itens_pagina);
    
    if(quantidade%opcoes.itens_pagina != 0)
        paginas++;

    while(a==1){     
        aux = 1;
        auxY = 2;
        fpcliente = fopen(arquivoCliente,"rb");
        fseek(fpcliente,(pagina-1)*sizeof(cliente)*opcoes.itens_pagina, 0);
        while ((fread(&cliente,sizeof(cliente),1,fpcliente) ==1)&&(aux<=opcoes.itens_pagina)){
            textoDoMenu(2,auxY,aux,cliente.nome,COR_LETRA); 
            auxY++;
            aux++;   
        }        
        fclose(fpcliente);
            
        textoDoMenu(2,opcoes.itens_pagina+2,aux,"<<<<",COR_MENU);          
        textoDoMenu(20,opcoes.itens_pagina+2,aux+1,">>>>",COR_MENU);
        andarMenu(aux+1); 
        if (TECLA==13){
            if(OPC==aux) {OPC = 1; pagina--; if(pagina<1) pagina = paginas; campo(2,2,32,opcoes.itens_pagina+1,BLACK," ");}
            else if(OPC==aux+1) {OPC = 1; pagina++; if(pagina>paginas) pagina = 1; campo(2,2,32,opcoes.itens_pagina+1,BLACK," ");}
            else{            
                cod = OPC+((pagina-1)*opcoes.itens_pagina);
                fpcliente = fopen(arquivoCliente,"rb");     
                fseek(fpcliente,sizeof(cliente)*(cod-1),0);
                fread(&cliente,sizeof(cliente),1,fpcliente);
                fclose(fpcliente);
                cod = cliente.codigo;
                a = 2;
            }
        }                                     
    }//FIM DO WHILE A
    fpcliente = fopen("selecionarCliente.dat","wb");
    fwrite(&cod,sizeof(cod),1,fpcliente); 
    fclose(fpcliente);
    return 0;
}//FIM MAIN      
