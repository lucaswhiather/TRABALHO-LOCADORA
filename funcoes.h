#ifndef _FUNCOES_H_

HWND WINAPI GetConsoleWindowNT(){
    typedef HWND WINAPI (*GetConsoleWindowT)(void);
    GetConsoleWindowT GetConsoleWindow;
    HMODULE hK32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hK32Lib,TEXT("GetConsoleWindow"));
    if ( GetConsoleWindow == NULL ) {
         return NULL;
    }
    return GetConsoleWindow();
}

void criarTela(int posX, int posY, int larg, int alt, char titulo[],bool tipo){
    char title[50] = {"title "};
    strcat(title,titulo);
    system(title);
    _setcursortype(_NOCURSOR); // DESABILITA O CURSOR

    if(tipo==TRUE){
        CONSOLE_SCREEN_BUFFER_INFO SBInfo;
        HWND hWnd = GetConsoleWindowNT();
        MoveWindow(hWnd,posX,posY,1,1,TRUE);
    }
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT sr;
    COORD consoleSize;

    consoleSize.X = larg; consoleSize.Y = alt;

    sr.Top=sr.Left=0;
    sr.Right=larg-1;
    sr.Bottom=alt-1;

    SetConsoleWindowInfo(console, TRUE, &sr);
    SetConsoleScreenBufferSize(console, consoleSize);
    SetConsoleWindowInfo(console, TRUE, &sr);
    SetConsoleScreenBufferSize(console, consoleSize);

}

void campo(int inicioX, int inicioY, int fimX, int fimY, int cor, char texto[]){
    int x,y;
    textcolor(cor);
    for(y = inicioY; y<=fimY; y++){
        gotoxy(inicioX,y); //posiciona o cursor
        for(x = inicioX; x<=fimX; x++)
            printf("%s",texto);
    }
    textcolor(COR_LETRA);
}

void campoDeString(int posX, int posY, int tamanho, int cor_letra,int cor_campo, char *string){
    gotoxy(posX, posY);
    _setcursortype(_NORMALCURSOR); //HABILITA O CURSOR
    textcolor(cor_letra);
    textbackground(cor_campo);

    campo(posX, posY, posX+tamanho, posY, cor_campo," ");
    gotoxy(posX, posY);
    for(int x = 1; x<=tamanho; x++)
        printf(" ");

    gotoxy(posX, posY);
    fflush(stdin);
    scanf("%30[^\n]",string);

    textcolor(COR_LETRA);
    textbackground(COR_FUNDO);
    _setcursortype(_NOCURSOR); // DESABILITA O CURSOR
}
//------------------------------------------------------------------------
int campoDeInt(int posX, int posY, int tamanho, int cor_letra, int cor_campo, int *inteiro){
    gotoxy(posX, posY);
    _setcursortype(_NORMALCURSOR); //HABILITA O CURSOR
    textcolor(cor_letra);
    textbackground(cor_campo);

    campo(posX, posY, posX+tamanho, posY, cor_campo," ");
    gotoxy(posX, posY);
    for(int x = 1; x<=tamanho; x++)
        printf(" ");

    gotoxy(posX, posY);
    fflush(stdin);
    scanf("%i",inteiro);

    textcolor(COR_LETRA);
    textbackground(COR_FUNDO);
    _setcursortype(_NOCURSOR); // DESABILITA O CURSOR
    return *inteiro;
}
//------------------------------------------------------------------------
float campoDeFloat(int posX, int posY, int tamanho, int cor_letra, int cor_campo, float *numeroFloat){
    gotoxy(posX, posY);
    _setcursortype(_NORMALCURSOR); //HABILITA O CURSOR
    textcolor(cor_letra);
    textbackground(cor_campo);

    campo(posX, posY, posX+tamanho, posY, cor_campo," ");
    gotoxy(posX, posY);
    for(int x = 1; x<=tamanho; x++)
        printf(" ");

    gotoxy(posX, posY);
    fflush(stdin);
    scanf("%f",numeroFloat);

    textcolor(COR_LETRA);
    textbackground(COR_FUNDO);
    _setcursortype(_NOCURSOR); // DESABILITA O CURSOR
    return *numeroFloat;
}
//------------------------------------------------------------------------
void texto(int x, int y, int cor, char texto[]){ //CRIA UM TEXTO NAS COORDENADAS PASSADA POR PARAMETRO
    gotoxy(x,y); //posiciona o cursor
    textcolor(cor);
    printf("%s",texto);
    textcolor(COR_LETRA);
}
//------------------------------------------------------------------------
void textoDoMenu(int x, int y, int opc, char texto[],int cor){
    gotoxy(x,y); //posiciona o cursor
    textcolor(cor);
    if(opc == OPC) textbackground(COR_SELECAO);
    printf("%s",texto);
    textcolor(COR_LETRA);
    textbackground(COR_FUNDO);
}
//------------------------------------------------------------------------
void andarMenu(int tamanho_menu){
    fflush(stdin); //limpa o buffer do teclado
    TECLA = getch();

    if(TECLA==80) OPC++; //BAIXO
    else if(TECLA==72) OPC--; //CIMA
    else if(TECLA==75) OPC--; //ESQUERDA
    else if(TECLA==77) OPC++; //DIREITA

    if(OPC<1) OPC = tamanho_menu;
    if(OPC>tamanho_menu) OPC = 1;
}

char *dataFormatada(struct data data, int tipo, bool arquivo){ //1 para data e 2 para horario
    if(tipo==1){
        char dia[10];
        char mes[10];
        char ano[10];
        char data2[15];
        char *retorno;
        if(data.dia<10)
            sprintf(dia,"0%i",data.dia);
        else
            sprintf(dia,"%i",data.dia);


        if(data.mes<10)
            sprintf(mes,"0%i",data.mes);
        else
            sprintf(mes,"%i",data.mes);

        sprintf(ano,"%i",data.ano);

        if(arquivo==TRUE)
            sprintf(data2,"%s-%s-%s",dia,mes,ano);
        else
            sprintf(data2,"%s/%s/%s",dia,mes,ano);
        retorno = data2;
        return retorno;
    }
    if(tipo==2){
        char hora[5];
        char minuto[5];
        char horario[5];
        char *retorno;
        if(data.hora<10)
            sprintf(hora,"0%i",data.hora);
        else
            sprintf(hora,"%i",data.hora);

        if(data.minuto<10)
            sprintf(minuto,"0%i",data.minuto);
        else
            sprintf(minuto,"%i",data.minuto);

        if(arquivo==TRUE)
            sprintf(horario,"%s-%s",hora,minuto);
        else
            sprintf(horario,"%s:%s",hora,minuto);
        retorno = horario;
        return retorno;
    }
}
//------------------------------------------------------------------------
struct data retornaData(bool tipo){
    struct data data;
    struct tm *local;
    time_t t;
    int dia, mes, ano, hora, min, sec;

    t= time(NULL);
    local=localtime(&t);

    if(tipo==TRUE){
        data.dia=local->tm_mday;
        data.mes=local->tm_mon+1;
        data.ano=local->tm_year+1900;

        data.hora = local->tm_hour;
        data.minuto = local->tm_min;
        data.segundo = local->tm_sec;
    }else{
        data.dia= 0;
        data.mes= 0;
        data.ano= 0;

        data.hora = 0;
        data.minuto = 0;
        data.segundo = 0;
    }

    return data;
}
//--------------------------------------------------------QUANTIDADE DE REGISTRO--------------------------------------------------
int quantidadeDeRegistro(char nome_arquivo[]){
    FILE *fparquivo;
    struct reg_cliente cliente;
    struct reg_filme filme;
    struct reg_genero genero;
    struct reg_categoria categoria;
    struct reg_locadev locadev;
    int quantidade = 0;

    fparquivo = fopen(nome_arquivo,"rb");

    if (strcmp(nome_arquivo,arquivoCliente)==0)
        while (fread(&cliente,sizeof(cliente),1,fparquivo) ==1)
            quantidade++;

    if (strcmp(nome_arquivo,arquivoFilme)==0)
        while (fread(&filme,sizeof(filme),1,fparquivo) ==1)
            quantidade++;

    if (strcmp(nome_arquivo,arquivoGenero)==0)
        while (fread(&genero,sizeof(genero),1,fparquivo) ==1)
            quantidade++;

    if (strcmp(nome_arquivo,arquivoCategoria)==0)
        while (fread(&categoria,sizeof(categoria),1,fparquivo) ==1)
            quantidade++;

    if (strcmp(nome_arquivo,arquivoLocadev)==0)
        while (fread(&locadev,sizeof(locadev),1,fparquivo) ==1)
            quantidade++;

    fclose(fparquivo);
    return  quantidade;
}

int gerarCodigo(char nome_arquivo[]){

    struct reg_cliente cliente;
    struct reg_filme filme;
    struct reg_genero genero;
    struct reg_categoria categoria;
    struct reg_locadev locadev;

    FILE *fparquivo;
    int codigo;

    if ((fparquivo = fopen(nome_arquivo,"rb"))==NULL)
        return 1;

    if (strcmp(nome_arquivo,arquivoCliente)==0)
        while (fread(&cliente,sizeof(cliente),1,fparquivo) ==1)
            codigo = cliente.codigo;

    if (strcmp(nome_arquivo,arquivoFilme)==0)
        while (fread(&filme,sizeof(filme),1,fparquivo) ==1)
            codigo = filme.codigo;

    if (strcmp(nome_arquivo,arquivoGenero)==0)
        while (fread(&genero,sizeof(genero),1,fparquivo) ==1)
            codigo = genero.codigo;

    if (strcmp(nome_arquivo,arquivoCategoria)==0)
        while (fread(&categoria,sizeof(categoria),1,fparquivo) ==1)
            codigo = categoria.codigo;

    if (strcmp(nome_arquivo,arquivoLocadev)==0)
        while (fread(&locadev,sizeof(locadev),1,fparquivo) ==1)
            codigo = locadev.codigo;

    fclose(fparquivo);
    return  codigo+1;
}

void configurarOpcoes(char tipo[]){
     FILE *fpopcoes;

     if((fpopcoes = fopen(arquivoOpcoes,"rb"))==NULL){
         fpopcoes = fopen(arquivoOpcoes,"wb");
         opcoes.cor_letra = 7;
         fwrite(&opcoes,sizeof(opcoes),1,fpopcoes);
         fclose(fpopcoes);
     }

     fclose(fpopcoes);

     if(strcmp(tipo,"carregar")==0){
         fpopcoes = fopen(arquivoOpcoes,"rb");
         fread(&opcoes,sizeof(opcoes),1,fpopcoes);
         fclose(fpopcoes);
         COR_LETRA = opcoes.cor_letra;
     }

     if(strcmp(tipo,"salvar")==0){
         fpopcoes = fopen(arquivoOpcoes,"wb");
         fwrite(&opcoes,sizeof(opcoes),1,fpopcoes);
         fclose(fpopcoes);
     }
}

int quantidadeDePaginas(char arquivo[]){
    configurarOpcoes("carregar");
    int paginas = 0;
    paginas = (quantidadeDeRegistro(arquivo))/ITENS_PAGINA;
    if((quantidadeDeRegistro(arquivo))%ITENS_PAGINA != 0)
        paginas++;
    return paginas;
}
#endif
