#ifndef _FILME_H_

int selecionarGenero(){//SLECIONAR O GENERO
     system("cd func&start selecionarGenero.exe");
     FILE *fparquivo;
     struct reg_genero genero;
     int cod = 0;
     while((fparquivo = fopen("func\\selecionarGenero.dat","rb"))==NULL)
         _sleep(1000);

    fread(&cod,sizeof(cod),1,fparquivo);
    fclose(fparquivo);
    _sleep(1000);
    system("Del func\\selecionarGenero.dat");
    return cod;
}//FIM selecionarGenero

void listarFilmePalavraChave(){//LISTAR FILMES POR PALAVRA CHAVE
     FILE *fpfilme;
     struct reg_filme filme;
     int quantidade = 0;
     int aux = 0;
     OPC = 1;
     char busca_titulo[30];
     campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
     if(quantidadeDeRegistro(arquivoFilme)==0){
        campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
        texto(7,8,RED,"Nenhum filme cadastrado");
        OPC = 1;
        textoDoMenu(7,10,1,"Voltar",COR_MENU);
        getch();
        campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
        return;
    }

     texto(7,8,3,"Digite uma palavra: ");
     campoDeString(27,8,sizeof(busca_titulo),COR_LETRA,BLACK,&busca_titulo[0]);
//----------------------------------------------------------------------
    fpfilme = fopen(arquivoFilme,"rb");
    while (fread(&filme,sizeof(filme),1,fpfilme)==1)
            if((strstr(filme.titulo,busca_titulo))!=NULL)
                quantidade++;
    fclose(fpfilme);

    char titulo_filme[quantidade][30];

    fpfilme = fopen(arquivoFilme,"rb");
    while (fread(&filme,sizeof(filme),1,fpfilme)==1)
            if((strstr(filme.titulo,busca_titulo))!=NULL){
                strcpy(titulo_filme[aux],filme.titulo);
                aux++;
            }
    fclose(fpfilme);

    int pagina = 1;
    int paginas = 0;
    paginas = (quantidade/8);
    if(quantidade%8!=0)
    paginas++;
    texto(7,10,COR_LETRA,"Filmes encontrados: ");printf("%i",quantidade);
    int a = 1;
    while(a==1){
        int auxY = 12;
        if(quantidade>0){
            for(int x = 0; x<8; x++)
                if(((pagina-1)*8)+x<quantidade){
                    texto(7,auxY,COR_LETRA,titulo_filme[((pagina-1)*8)+x]);
                    auxY++;
                }
        }
        else
            texto(7,20,RED,"Nenhum titulo foi encontrado com essa palavra");

        textoDoMenu(8,22,1,"<<<<",COR_MENU);
        textoDoMenu(18,22,2,"Voltar",COR_MENU);
        textoDoMenu(25,22,3,">>>>",COR_MENU);

        andarMenu(3);

        if(TECLA==27) {OPC = 1; a = 2;} //tecla esc
        if (TECLA==13){
            if(OPC==1){pagina--; if(pagina<1) pagina = paginas; campo(7,20,tamanhoProgramaX,24,BLACK," ");}
            else if(OPC==2){OPC = 1; a = 2;}
            else if(OPC==3){ pagina++; if(pagina>paginas) pagina = 1; campo(7,20,tamanhoProgramaX,24,BLACK," ");}
        }//FIM TECLA ENTER
    }  //FIM EHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}//FIM LISTAR FILMES POR PALAVRA CHAVE

void listarFilmeGenero(){//LISTA FILMES POR GENERO
     FILE *fpfilme;
     FILE *fpgenero;
     struct reg_genero genero;
     struct reg_filme filme;
     int codigo_genero = 0;
     int quantidade = 0;
     int aux = 0;
     OPC = 1;
     campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
     if(quantidadeDeRegistro(arquivoFilme)==0){
        campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
        texto(7,8,RED,"Nenhum filme cadastrado");
        OPC = 1;
        textoDoMenu(7,10,1,"Voltar",COR_MENU);
        getch();
        campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
        return;
     }



     texto(7,8,3,"G\210nero: ");
     codigo_genero = selecionarGenero();
     fpgenero = fopen(arquivoGenero,"rb");
     while (fread(&genero,sizeof(genero),1,fpgenero)==1)
         if(codigo_genero==genero.codigo)
             break;
     fclose(fpgenero);
     printf("%s",genero.genero);

//----------------------------------------------------------------------
    fpfilme = fopen(arquivoFilme,"rb");
    while (fread(&filme,sizeof(filme),1,fpfilme)==1)
            if(codigo_genero==filme.genero)
                quantidade++;
    fclose(fpfilme);

    char titulo_filme[quantidade][30];

    fpfilme = fopen(arquivoFilme,"rb");
    while (fread(&filme,sizeof(filme),1,fpfilme)==1)
            if(codigo_genero==filme.genero){
                strcpy(titulo_filme[aux],filme.titulo);
                aux++;
            }
    fclose(fpfilme);

    int pagina = 1;
    int paginas = 0;
    paginas = (quantidade/8);
    if(quantidade%8!=0)
    paginas++;
    texto(7,10,COR_LETRA,"Filmes encontrados: ");printf("%i",quantidade);
    int a = 1;
    while(a==1){
        int auxY = 12;
        if(quantidade>0){
            for(int x = 0; x<8; x++)
                if(((pagina-1)*8)+x<quantidade){
                    texto(7,auxY,COR_LETRA,titulo_filme[((pagina-1)*8)+x]);
                    auxY++;
                }
        }
        else
            texto(7,20,RED,"Nenhuma tem nenhum filme com este genero");

        textoDoMenu(12,22,1,"<<<<",COR_MENU);
        textoDoMenu(20,22,2,"Voltar",COR_MENU);
        textoDoMenu(40,22,3,">>>>",COR_MENU);

        andarMenu(3);

        if(TECLA==27) {OPC = 1; a = 2;} //tecla esc
        if (TECLA==13){
            if(OPC==1){pagina--; if(pagina<1) pagina = paginas; campo(7,20,tamanhoProgramaX,24,BLACK," ");}
            else if(OPC==2){OPC = 1; a = 2;}
            else if(OPC==3){ pagina++; if(pagina>paginas) pagina = 1; campo(7,20,tamanhoProgramaX,24,BLACK," ");}
        }//FIM TECLA ENTER
    }  //FIM EHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}//FIM LISTA FILMES POR GENERO

void apresentarFilme(struct reg_filme filme){//APRESENTAR FILME
    FILE *fpfilme;
    FILE *fpcliente;
    FILE *fpgenero;
    FILE *fpcategoria;
    struct reg_genero genero;
    struct reg_cliente cliente;
    struct reg_categoria categoria;
    int a = 1;
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    texto(7,8,3,"C\242digo:");
    printf(" %i",filme.codigo);
    texto(7,10,3,"Titulo:");
    printf(" %s",filme.titulo);
    texto(7,12,3,"G\210nero:");
    fpgenero = fopen(arquivoGenero,"rb");
    while (fread(&genero,sizeof(genero),1,fpgenero)==1)
        if(filme.genero==genero.codigo)
            break;
    fclose(fpgenero);
    printf(" %s",genero.genero);

    texto(7,14,3,"Categoria:");
    fpcategoria = fopen(arquivoCategoria,"rb");
    while (fread(&categoria,sizeof(categoria),1,fpcategoria)==1)
        if(filme.categoria==categoria.codigo)
            break;
    fclose(fpcategoria);
    printf(" %s",categoria.categoria);
    texto(7,16,3,"Pre\207o:");
    printf("R$ %5.2f",categoria.preco);

    if(filme.situacao==0)texto(7,18,GREEN,"Disponivel");
    else {
        fpcliente = fopen(arquivoCliente,"rb");
            while (fread(&cliente,sizeof(cliente),1,fpcliente)==1)
                if(filme.situacao==cliente.codigo)
                    break;
        fclose(fpcliente);
        texto(7,17,RED,"Alugado");
        texto(7,18,3,"Cliente: ");
        printf("%s",cliente.nome);
        texto(38,18,3,"Telefone: ");
        printf("%i",cliente.telefone);
    }
}//FIM APRESENTAR FILME

struct reg_filme selecionarFilmeManualmente(){//SELECIONAR FILME MANUALMENTE
    system("cd func&start selecionarFilme.exe");
    FILE *fpfilme;
    struct reg_filme filme;
    int cod = 1;

    while((fpfilme = fopen("func\\selecionarFilme.dat","rb"))==NULL)
        _sleep(1000);
    fread(&cod,sizeof(cod),1,fpfilme);
    fclose(fpfilme);

    _sleep(2000);
    system("Del func\\selecionarFilme.dat");

    fpfilme = fopen(arquivoFilme,"rb");
    while (fread(&filme,sizeof(filme),1,fpfilme)==1)
        if(cod==filme.codigo)
            break;
    fclose(fpfilme);
    return filme;
}//FIM SELECIONAR FILME MANUALMENTE

struct reg_filme procurarFilmeCodigo(){//PROCURAR FILME PELO CÓDIGO
    struct reg_filme filme;
    FILE *fpfilme;
    int cod = 1;
    int achou = 0;

    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    texto(7,8,COR_LETRA,"Digite o c\242digo do filme:");
    campoDeInt(33,8,4,COR_LETRA,BLACK,&cod);

    fpfilme = fopen(arquivoFilme,"rb");
    while ((!achou)&&(fread(&filme,sizeof(filme),1,fpfilme)==1))
            if(cod==filme.codigo)
                achou = 1;
    fclose(fpfilme);

    if(achou==0){
        texto(7,10,RED,"C\242digo n\306o encontrado");
        OPC = 1;
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        filme.codigo = 0;
        getch();
    }
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return filme;
}//FIM  PROCURAR FILME PELO CÓDIGO

struct reg_filme procurarFilmeTituloInteiro(){//PROCURAR CLIENTE PELO NOME INTEIRO
    struct reg_filme filme;
    FILE *fpfilme;
    char nome[30];
    int achou = 0;

    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    texto(7,8,COR_LETRA,"Digite o titulo inteiro:");
    campoDeString(30,8,sizeof(nome),COR_LETRA,BLACK,&nome[0]);

    fpfilme = fopen(arquivoFilme,"rb");
    while ((!achou)&&(fread(&filme,sizeof(filme),1,fpfilme)==1))
            if(strcmp(filme.titulo,nome)==0)
                achou = 1;
    fclose(fpfilme);

    if(achou==0){
        texto(7,10,RED,"Titulo nao encontrado");
        OPC = 1;
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        filme.codigo = 0;
        getch();
    }
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return filme;
}//FIM PROCURAR CLIENTE PELO NOME INTEIRO

struct reg_filme procurarFilmePalavraChave(){//PROCURAR CLIENTE POR PALAVRA CHAVE NO NOME
    struct reg_filme filme;
    FILE *fpfilme;
    char nome[30];
    int achou = 0;

    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    texto(7,8,COR_LETRA,"Digite uma palavra:");
    campoDeString(28,8,sizeof(nome),COR_LETRA,BLACK,&nome[0]);

    fpfilme = fopen(arquivoFilme,"rb");
    while ((!achou)&&(fread(&filme,sizeof(filme),1,fpfilme)==1))
            if(strstr(filme.titulo,nome)!=NULL)
                achou = 1;
    fclose(fpfilme);

    if(achou==0){
        texto(7,10,RED,"Palavara n\306o encontrada");
        OPC = 1;
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        filme.codigo = 0;
        getch();
    }
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return filme;
}//FIM PROCURAR CLIENTE POR PALAVRA CHAVE NO NOME

struct reg_filme menuSelecionarFilme(){//MENU SELECIONAR FILME
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    OPC = 1;
    struct reg_filme filme;
    int a = 1;
    filme.codigo = 0;
    if(quantidadeDeRegistro(arquivoFilme)==0){
        campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
        texto(7,8,RED,"Nenhum filme cadastrado");
        OPC = 1;
        textoDoMenu(7,10,1,"Voltar",COR_MENU);
        getch();
        a = 2;;
    }

    while(a==1){
        texto(7,8,CYAN,"SELECIONAR FILME");
        textoDoMenu(7,10,1,"Procurar pelo c\242digo",COR_MENU);
        textoDoMenu(7,12,2,"Procurar pelo titulo inteiro",COR_MENU);
        textoDoMenu(7,14,3,"Procurar por palavra chave no titulo",COR_MENU);
        textoDoMenu(7,16,4,"Selecionar manualmente",COR_MENU);
        textoDoMenu(7,18,5,"Voltar",COR_MENU);
        andarMenu(5);
        if(TECLA==27){OPC = 1; a = 2;} //tecla esc
        if (TECLA==13){
            if(OPC==1){OPC = 1; filme = procurarFilmeCodigo();}
            else if(OPC==2){OPC = 1; filme = procurarFilmeTituloInteiro();}
            else if(OPC==3){OPC = 1; filme = procurarFilmePalavraChave();}
            else if(OPC==4){OPC = 1; filme = selecionarFilmeManualmente();}
            else if(OPC==5){OPC = 1; a = 2;}
        }
        if(filme.codigo>0)
            return filme;
    }//FIM WHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return filme;
}//FIM MENU SELECIONAR FILME

void consultarFilme(){//CONSULTAR FILME
    OPC = 1;
    textoDoMenu(7,20,1,"Voltar",COR_MENU);
    getch();
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}//FIM CONSULTAR FILME

void menuPrincipalFilme(){
    struct reg_filme filme;
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    OPC = 1;
    int a = 1;
    while(a==1){
        texto(7,8,CYAN,"MENU PRINCIPAL FILME");
        textoDoMenu(7,10,1,"Cadastrar filme",COR_MENU);
        textoDoMenu(7,12,2,"Consultar filme",COR_MENU);
        textoDoMenu(7,14,3,"Listar filmes",COR_MENU);
        textoDoMenu(7,16,4,"Listar filmes por genero",COR_MENU);
        textoDoMenu(7,18,5,"Listar filmes por palava chave",COR_MENU);
        textoDoMenu(7,20,6,"Cadastar genero",COR_MENU);
        textoDoMenu(7,22,7,"Cadastar categoria",COR_MENU);
        textoDoMenu(7,24,8,"Voltar",COR_MENU);
        andarMenu(8);
        if(TECLA==27) {OPC = 1; a = 2;}   //tecla esc
        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1) system("cd func&start cadastrarFilme.exe");        //CADASTRAR FILME
            else if(OPC==2) {
                filme = menuSelecionarFilme();
                if(filme.codigo>0){
                    apresentarFilme(filme);
                    consultarFilme();
                }
            }
            else if(OPC==3) system("cd func&start listarFilme.exe");
            else if(OPC==4) listarFilmeGenero();
            else if(OPC==5) listarFilmePalavraChave();
            else if(OPC==6) system("cd func&start cadastrarGenero.exe");
            else if(OPC==7) system("cd func&start cadastrarCategoria.exe");
            else if(OPC==8) {OPC = 1; a = 2;}                              //volta
        }
    }//FIM DO WHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}
#endif
