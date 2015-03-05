#include "..\funcoes.h"

char cor_letra[16][20] = {       
        "PRETO",                //0
        "AZUL",                 //1
        "VERDE",                //2
        "VERDE-\265GUA",        //3
        "VERMELHO",             //4 
        "ROXO",                 //5
        "AMARELO",              //6
        "BRANCO",               //7 
        "CINZA",                //8
        "AZUL CLARO",           //9
        "VERDE CLARO",          //10
        "VERDE-\265GUA CLARO",  //11
        "VERMELHO CLARO",       //12
        "LIL\265S",             //13
        "AMARELO CLARO",        //14
        "BRANCO BRILHANTE"      //15
};

main(){
    criarTela(400,310,22,18,"SELECIONAR COR");
    
    int cor;
                
    int a = 1; 
    while(a==1){     
            textoDoMenu(2,2,1,cor_letra[0],WHITE);
            textoDoMenu(2,3,2,cor_letra[1],1);
            textoDoMenu(2,4,3,cor_letra[2],2);
            textoDoMenu(2,5,4,cor_letra[3],3);
            textoDoMenu(2,6,5,cor_letra[4],4);
            textoDoMenu(2,7,6,cor_letra[5],5);
            textoDoMenu(2,8,7,cor_letra[6],6);
            textoDoMenu(2,9,8,cor_letra[7],7);
            textoDoMenu(2,10,9,cor_letra[8],8);
            textoDoMenu(2,11,10,cor_letra[9],9);   
            textoDoMenu(2,12,11,cor_letra[10],10);
            textoDoMenu(2,13,12,cor_letra[11],11);
            textoDoMenu(2,14,13,cor_letra[12],12);
            textoDoMenu(2,15,14,cor_letra[13],13);
            textoDoMenu(2,16,15,cor_letra[14],14);
            textoDoMenu(2,17,16,cor_letra[15],15);
            andarMenu(16);    
        
            if(TECLA==27){cor = -1; a = 2;}  //tecla esc  
            else if (TECLA==13) {cor = OPC-1; a = 2;}                                     
    }//FIM DO WHILE A
    FILE *fpcor;

    fpcor = fopen("selecionarCor.dat","wb");
    fwrite(&cor,sizeof(cor),1,fpcor); 
    fclose(fpcor);
    return 0;
}//FIM MAIN      
