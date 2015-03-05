#ifndef _OPCOES_H_
int selecionarCorManualmente(){
    system("cd func&start selecionarCorLetra.exe");
    FILE *fpcor;
    int cod = 1;

    while((fpcor = fopen("func\\selecionarCor.dat","rb"))==NULL)
        _sleep(1000);
    fread(&cod,sizeof(cod),1,fpcor);
    fclose(fpcor);

     _sleep(2000);
     system("Del func\\selecionarCor.dat");
    return cod;
}

void alterarCor(char tipo[]){
    int cod = selecionarCorManualmente();

    if(strcmp(tipo,"letra")==0){
        COR_LETRA = cod;
        campo(21,10,tamanhoProgramaX,10,BLACK," ");
    }
    else if(strcmp(tipo,"menu")==0){
        COR_MENU = cod;
        campo(20,12,tamanhoProgramaX,12,BLACK," ");
    }
    else if(strcmp(tipo,"selecao")==0){
        COR_SELECAO = cod;
        campo(21,14,tamanhoProgramaX,14,BLACK," ");
    }
    else if(strcmp(tipo,"fundo")==0){
        COR_FUNDO = cod;
        campo(21,16,tamanhoProgramaX,16,BLACK," ");
    }

}

void salvar(){
    configurarOpcoes("salvar");


}



void menuPrincipalOpcoes(){
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

    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    OPC = 1;
    int a = 1;
    while(a==1){
        textoDoMenu(7,10,1,"Cor da letra:",WHITE);
        texto(21,10,COR_LETRA,cor_letra[COR_LETRA]);
        textoDoMenu(7,12,2,"Cor do menu:",WHITE);
        texto(20,12,COR_MENU,cor_letra[COR_MENU]);
        textoDoMenu(7,14,3,"Cor de selecao:",WHITE);
        texto(23,14,COR_SELECAO,cor_letra[COR_SELECAO]);
        textoDoMenu(7,16,4,"Voltar",WHITE);
        andarMenu(4);

        if(TECLA==27){OPC = 1;  a = 2;} //tecla esc
        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1) alterarCor("letra");                              //cor da letra
            else if(OPC==2) alterarCor("menu");
            else if(OPC==3) alterarCor("selecao");                //quantidade de itens por pagina
            else if(OPC==4){OPC = 1;  a = 2;}                             //voltar
        }
    }//FIM DO WHILE A
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}
#endif
