#ifndef _LOCACAO_H_

void mostrarExtrato(int codigo_cliente, int quantidade, int codigo_locacao){//MOSTRAR EXTRATO
     struct data data;
     struct reg_cliente cliente;
     struct reg_filme filme;
     struct reg_genero genero;
     struct reg_categoria categoria;
     struct reg_locadev locadev;
     data = retornaData(TRUE);
     FILE *fpextrato;
     FILE *fpcliente;
     FILE *fpfilme;
     FILE *fpgenero;
     FILE *fpcategoria;
     FILE *fplocadev;
     char nome_arquivo[16];
     char string[200];
     char abrir_arquivo[50];
     int filmes[quantidade];
     int aux = 0;
     float valorTotal = 0;

     strcpy(nome_arquivo,"extrato\\");
     strcat(nome_arquivo,(dataFormatada(data,1,TRUE)));
     strcat(nome_arquivo,"-");
     strcat(nome_arquivo,dataFormatada(data,2,TRUE));
     strcat(nome_arquivo,".txt");

     fpcliente = fopen(arquivoCliente,"rb");
     while (fread(&cliente,sizeof(cliente),1,fpcliente)==1)
         if(codigo_cliente==cliente.codigo)
             break;
     fclose(fpcliente);

     fplocadev = fopen(arquivoLocadev,"rb");
         fseek(fplocadev,-1*sizeof(locadev),2);
         while ((fread(&locadev,sizeof(locadev),1,fplocadev)==1)&&(aux<quantidade)){
             if(codigo_cliente==locadev.cliente){
                 filmes[aux] = locadev.filme;
                 aux++;
             }
             fseek(fplocadev,-2*sizeof(locadev),1);
         }
     fclose(fplocadev);

     fpextrato = fopen(nome_arquivo,"w");
     fputs("---------------Extrato Locadora---------------",fpextrato);
     sprintf(string,"\n\nData: %s",dataFormatada(data,1,FALSE));
     fputs(string,fpextrato);
     fputs("\n\n----------------------------------------------",fpextrato);
     sprintf(string,"\n\nCliente: %s \nRua: %-30s  Nº: %i \nTelefone: %i \nEmail: %s",cliente.nome,cliente.end_rua,cliente.end_numero,cliente.telefone,cliente.email);
     fputs(string,fpextrato);
     fputs("\n\n---------------Filmes alugados---------------",fpextrato);
     for(int x = 0; x<quantidade; x++){
         fpfilme = fopen(arquivoFilme,"rb");
         while (fread(&filme,sizeof(filme),1,fpfilme)==1)
         if(filmes[x]==filme.codigo)
             break;
         fclose(fpfilme);

         fpgenero = fopen(arquivoGenero,"rb");
         while (fread(&genero,sizeof(genero),1,fpgenero)==1)
         if(filme.genero==genero.codigo)
             break;
         fclose(fpgenero);

         fpcategoria = fopen(arquivoCategoria,"rb");
         while (fread(&categoria,sizeof(categoria),1,fpcategoria)==1)
         if(filme.categoria==categoria.codigo)
             break;
         fclose(fpcategoria);

         valorTotal = valorTotal + categoria.preco;

         sprintf(string,"\n\nCódigo: %i \nTitulo: %s \nGênero: %s \nCategoria: %s \nPreço: %5.2f",filme.codigo,filme.titulo,genero.genero,categoria.categoria,categoria.preco);
         fputs(string,fpextrato);
     }
     fputs("\n\n---------------------------------------------",fpextrato);
     sprintf(string,"\n\nTotal a pagar: R$ %5.2f",valorTotal);
     fputs(string,fpextrato);

     fclose(fpextrato);
     strcpy(abrir_arquivo,"start ");
     strcat(abrir_arquivo,nome_arquivo);
     system(abrir_arquivo);
}//FIM MOSTRAR EXTRATO

struct reg_cliente confirmarCliente(struct reg_cliente cliente){//CONFIRMAR CLIENTE

    if(cliente.codigo==0) return cliente;
    apresentarDadosCliente(5,7,cliente);
    OPC = 1;
    int a = 1;
    while(a==1){
        textoDoMenu(7,20,1,"Confirmar cliente",COR_MENU);
        textoDoMenu(7,22,2,"Voltar",COR_MENU);
        andarMenu(2);
        if(TECLA==27) {OPC = 1; cliente.codigo = 0;} //tecla esc
        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1) {OPC = 1; a = 2;}
            else if(OPC==2) {OPC = 1; a = 2; cliente.codigo = 0;}
        }//FIM TECLA ENTER

    }//FIM WHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return cliente;
};

struct reg_filme confirmarFilme(struct reg_filme filme){
    if(filme.codigo==0) return filme;
    apresentarFilme(filme);
    OPC = 1;
    int a = 1;
    if(filme.situacao>0){
        texto(7,20,RED,"Filme indisponivel");
        textoDoMenu(7,22,1,"Voltar",COR_MENU);
        getch();
        a  = 2;
        filme.codigo = 0;
    }

    while(a==1){
        textoDoMenu(7,20,1,"Confirmar filme",COR_MENU);
        textoDoMenu(7,22,2,"Voltar",COR_MENU);
        andarMenu(2);
        if(TECLA==27) {OPC = 1; filme.codigo = 0;} //tecla esc
        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1) {OPC = 1; a = 2;}
            else if(OPC==2) {OPC = 1; a = 2; filme.codigo = 0;}
        }//FIM TECLA ENTER

    }//FIM WHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return filme;
};

void fazerLocacao(){//FAZER LOCAÇÃO
    FILE *fpfilme;
    FILE *fplocadev;
    FILE *fpcategoria;
    struct reg_cliente cliente;
    struct reg_filme filme;
    struct reg_categoria categoria;
    struct reg_locadev locadev;
    int quantidade = 0;
    int a = 1;
    int codigo_filme = 0;
    int codigo_cliente = 0;
    while(a==1){
        int b = 1;
        while(b==1){
            cliente = confirmarCliente(menuSelecionarCliente());
            if(cliente.codigo==0){
                b = 3; a = 2;
                break;
            }
            b = 2;
        }
        while(b==2){
            filme = confirmarFilme(menuSelecionarFilme());
                if((filme.codigo==0)&&(quantidade==0))
                    break;

            int c = 1;

            if(filme.codigo==0)
                c  = 2;

            while(c==1){
                fpcategoria = fopen(arquivoCategoria,"rb");
                while (fread(&categoria,sizeof(categoria),1,fpcategoria)==1)
                           if(filme.categoria==categoria.codigo)
                               break;
                fclose(fpcategoria);
                texto(7,8,3,"Cliente: ");  printf("%s",cliente.nome);
                texto(7,10,3,"Filme: ");   printf("%s",filme.titulo);
                texto(39,10,3,"R$ ");   printf("%5.2f",categoria.preco);
                textoDoMenu(7,12,1,"Confirmar loca\207\206o",COR_MENU);
                textoDoMenu(7,14,2,"Voltar",COR_MENU);
                andarMenu(2);
                if(TECLA==27) {OPC = 1; b = 2; filme.codigo = 0;} //tecla esc
                if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
                    if(OPC==1){
                        locadev.codigo = gerarCodigo(arquivoLocadev);
                        locadev.locacao = retornaData(TRUE);
                        locadev.devolucao = retornaData(FALSE);
                        locadev.cliente = cliente.codigo;
                        locadev.filme = filme.codigo;
                        fplocadev = fopen(arquivoLocadev,"ab+");
                        fwrite(&locadev,sizeof(locadev),1,fplocadev);
                        fclose(fplocadev);
                        codigo_cliente = cliente.codigo;
                        codigo_filme = filme.codigo;
                        fpfilme = fopen(arquivoFilme,"rb+");
                        while (fread(&filme,sizeof(filme),1,fpfilme)==1)
                           if(codigo_filme==filme.codigo)
                               break;
                        fseek(fpfilme,-1*sizeof(filme),1);
                        filme.situacao = codigo_cliente;
                        fwrite(&filme,sizeof(filme),1,fpfilme);
                        fclose(fpfilme);
                        texto(7,16,GREEN,"Loca\207\306o efetuada com sucesso");
                        quantidade++;
                        filme.codigo = 0;
                        _sleep(4000);
                        c = 2;
                    }
                    else if(OPC==2) {OPC = 1; c = 3; filme.codigo = 0;}
                }//FIM TECLA ENTER
            }//FIM WHILE c
            campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
            while(c==2){
                textoDoMenu(7,8,1,"Selecionar outro filme",COR_MENU);
                textoDoMenu(7,10,2,"Encerrar e mostrar extrato",COR_MENU);
                andarMenu(2);
                if (TECLA==13){
                    if(OPC==1){OPC = 1; c = 3;}
                    else if(OPC==2){OPC = 1; c = 3; b = 3; a = 2; mostrarExtrato(codigo_cliente,quantidade,locadev.codigo);}
                }//AO PRESSIONAR A TECLA
            }//FIM WHILE c
        }//FIM WHILE b
    }//FIM WHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}//FIM FAZER LOCACAO

void fazerDevolucao(){//FAZER DEVOLUÇÃO
    FILE *fpfilme;
    FILE *fpcategoria;
    FILE *fplocadev;
    struct reg_cliente cliente;
    struct reg_filme filme;
    struct reg_locadev locadev;
    int aux = 0;
    int a = 1;
    while(a==1){
        campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
        cliente = confirmarCliente(menuSelecionarCliente());
        if(cliente.codigo==0)
            a  = 2;
        break;
    }//FIM WHILE a
    apresentarDadosCliente(5,7,cliente);

    while(a==1){
        int quantidade = 0;
        fplocadev = fopen(arquivoLocadev,"rb");
        while (fread(&locadev,sizeof(locadev),1,fplocadev)==1)
            if((cliente.codigo==locadev.cliente)&&(locadev.devolucao.dia==0))
                quantidade++;
        fclose(fplocadev);

        if(quantidade==0){
            texto(7,12,RED,"Esse cliente nao tem nenhuma loca\207\306o aberta");
            OPC = 1;
            textoDoMenu(7,14,1,"Voltar",COR_MENU);
            getch();
            campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
            a = 3; break;
        }
        int codigo_filme[quantidade];
        fplocadev = fopen(arquivoLocadev,"rb");
        while (fread(&locadev,sizeof(locadev),1,fplocadev)==1)
                if((cliente.codigo==locadev.cliente)&&(locadev.devolucao.dia==0)){
                    codigo_filme[aux] = locadev.filme;
                    aux++;
                }
        fclose(fplocadev);

        int pagina = 1;
        int paginas = 0;
        paginas = (quantidade/6);
        if(quantidade%6!=0)
            paginas++;

        texto(7,19,RED,"Selecione o filme");

        OPC = 1;
        int b = 1;
        while(b==1){
            int auxY = 20;
            int aux = 1;
            for(int x = (pagina-1)*5; x<quantidade; x++){
                if(aux>5) break;
                fpfilme = fopen(arquivoFilme,"rb");
                while(fread(&filme,sizeof(filme),1,fpfilme)==1)
                    if(codigo_filme[x]==filme.codigo)
                        break;
                fclose(fpfilme);
                textoDoMenu(7,auxY,aux,filme.titulo,COR_MENU);
                auxY++;
                aux++;
            }
            textoDoMenu(7,25,aux,"<<<<",COR_MENU);
            textoDoMenu(20,25,aux+1,"Voltar",COR_MENU);
            textoDoMenu(30,25,aux+2,">>>>",COR_MENU);
            andarMenu(aux+2);
            if (TECLA==13){
                if(OPC==aux){OPC = 1; pagina--; if(pagina<1) pagina = paginas; campo(7,20,tamanhoProgramaX,24,BLACK," ");}
                else if(OPC==aux+1){OPC = 1; b = 2; a = 2;}
                else if(OPC==aux+2){OPC = 1; pagina++; if(pagina>paginas) pagina = 1; campo(7,20,tamanhoProgramaX,24,BLACK," ");}
                else{
                    int codigo = codigo_filme[(OPC-1)+(pagina-1)*5];
                    OPC = 1;
                    int c = 1;
                    while(c==1){
                        campo(7,20,tamanhoProgramaX-1,25,BLACK," ");
                        fpfilme = fopen(arquivoFilme,"rb");
                        while(fread(&filme,sizeof(filme),1,fpfilme)==1)
                            if(codigo==filme.codigo)
                                break;
                        fclose(fpfilme);
                        texto(7,20,GREEN,"Fazer devolucao do filme: ");
                        printf("%s",filme.titulo);
                        textoDoMenu(7,22,1,"Fazer devolu\207\306o",COR_MENU);
                        textoDoMenu(7,24,2,"Voltar",COR_MENU);
                        andarMenu(2);
                        if (TECLA==13){
                            if(OPC==1){

                                fpfilme = fopen(arquivoFilme,"rb+");
                                while(fread(&filme,sizeof(filme),1,fpfilme)==1)
                                    if(codigo==filme.codigo)
                                        break;
                                fseek(fpfilme,-1*sizeof(filme),1);
                                filme.situacao = 0;
                                fwrite(&filme,sizeof(filme),1,fpfilme);
                                fclose(fpfilme);

                                fplocadev = fopen(arquivoLocadev,"rb+");
                                while(fread(&locadev,sizeof(locadev),1,fplocadev)==1)
                                    if((codigo==locadev.filme)&&(locadev.devolucao.dia==0))
                                        break;
                                locadev.devolucao = retornaData(TRUE);
                                fseek(fplocadev,-1*sizeof(locadev),1);
                                fwrite(&locadev,sizeof(locadev),1,fplocadev);
                                fclose(fplocadev);
                                campo(7,7,tamanhoProgramaX-1,25,BLACK," ");
                                texto(7,7,GREEN,"Devolu\207\306o efetuada com sucesso");
                                _sleep(4000);
                                OPC = 1;
                                c = 2;
                                b = 2;
                                a = 2;
                            }
                            else if(OPC==2){OPC = 1; c = 2; b = 2; a = 2;}
                        }
                    }//FIM WHILE c
                }
            }//FIM TECLA ENTER
        }//FIM WHILE b
    }//FIM WHILE a
    campo(5,7,tamanhoProgramaX-1,tamanhoProgramaY,BLACK," ");
}//FIM FAZER DEVOLUÇÃO

void listarLocacoes(){//LISTAR LOCACOES
    FILE *fplocadev;
    FILE *fpfilme;
    FILE *fpcliente;
    struct reg_locadev locadev;
    struct reg_filme filme;
    struct reg_cliente cliente;
    struct data data;
    int pagina = 1;
    int paginas = 0;
    int quantidade = 0;
    char dataString[20];
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    quantidade = quantidadeDeRegistro(arquivoLocadev);
    paginas = (quantidade/4);
    if(quantidade%4 != 0)
        paginas++;

    textoDoMenu(44,23,5,"Loca\207\344es feitas:",COR_LETRA);
    printf(" %i", quantidade);

    texto(7,8,GREEN,"Data loca\207\306o");
    texto(25,8,GREEN,"Filme / Cliente");
    texto(55,8,GREEN,"Data devolu\207\306o");

    int a = 1;
    while(a==1){
        int aux = 1;
        int auxY = 10;
        int b = 1;
        gotoxy(44,24);
        printf("P\240gina: %i",pagina);
        campo(5,10,tamanhoProgramaX,22,BLACK," ");
        fplocadev = fopen(arquivoLocadev,"rb");
        fseek(fplocadev,(pagina-1)*sizeof(locadev)*4, 0);
        while ((fread(&locadev,sizeof(locadev),1,fplocadev) ==1)&&(aux<=4)){
            //-------------------------informa a data de locação----------------------
            gotoxy(7,auxY);
            strcpy(dataString,dataFormatada(locadev.locacao,1,FALSE));
            printf("%s",dataString);
            gotoxy(7,auxY+1);
            strcpy(dataString,dataFormatada(locadev.locacao,2,FALSE));
            printf("%s",dataString);

            //-------------------------informa a data de devolução--------------------
            if(locadev.devolucao.dia>0){
                gotoxy(55,auxY);
                strcpy(dataString,dataFormatada(locadev.devolucao,1,FALSE));
                printf("%s",dataString);
                gotoxy(55,auxY+1);
                strcpy(dataString,dataFormatada(locadev.devolucao,2,FALSE));
                printf("%s",dataString);

            }else
                texto(55,auxY,RED,"Nao encerrada");
            //-------------------------busca o titulo do filme-----------------------
            gotoxy(25,auxY);
            fpfilme = fopen(arquivoFilme,"rb");
            while (fread(&filme,sizeof(filme),1,fpfilme)==1)
                if(locadev.filme==filme.codigo)
                    break;
            fclose(fpfilme);

            if(locadev.filme==filme.codigo)
                printf("%s",filme.titulo);
            else
                texto(25,auxY,RED,"Filme deletado");
            //-------------------------busca o nome do cliente-----------------------
            fpcliente = fopen(arquivoCliente,"rb");
            while(fread(&cliente,sizeof(cliente),1,fpcliente)==1)
                if(locadev.cliente==cliente.codigo)
                    break;
            fclose(fpcliente);
            if(locadev.cliente==cliente.codigo)
                texto(25,auxY+1,COR_LETRA,cliente.nome);
            else
                texto(25,auxY+1,RED,"Cliente deletado");
            //----------------------------------------------------------------------
            auxY = auxY+3;
            aux++;
        }
        fclose(fplocadev);
        while(b==1){
            textoDoMenu(7,23,1,"<<<<",COR_MENU);
            textoDoMenu(14,23,2,"Voltar",COR_MENU);
            textoDoMenu(23,23,3,">>>>",COR_MENU);
            andarMenu(3);
            if(TECLA==27) {a = 2; b = 2; OPC = 1;} //tecla esc
            if (TECLA==13){
                if(OPC==1){ pagina--; if(pagina<1) pagina = paginas; b = 2;}        //voltar pagina
                else if(OPC==2) {a = 2; b = 2; OPC = 1;}                            //voltar
                else if(OPC==3){ pagina++; if(pagina>paginas) pagina = 1; b = 2;}   //avançar pagina
            }
        }//FIM WHILE b
    }//FIM WHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}//FIM LISTAR LOCACOES

void menuPrincipalLocacao(){//MENU PRINCIPAL LOCAÇÃO
    struct reg_filme filme;
    struct reg_cliente cliente;
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    OPC = 1;
    int a = 1;
    while(a==1){
        texto(7,8,CYAN,"MENU PRINCIPAL LOCACAO");
        textoDoMenu(7,10,1,"Fazer loca\207\306o",COR_MENU);
        textoDoMenu(7,12,2,"Fazer devolu\207\306o",COR_MENU);
        textoDoMenu(7,14,3,"Listar loca\207\344es",COR_MENU);
        textoDoMenu(7,16,4,"Voltar",COR_MENU);
        andarMenu(4);
        if(TECLA==27) {OPC = 1;  a = 2;} //tecla esc
        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1) {OPC = 1; fazerLocacao();}
            else if(OPC==2) {OPC = 1; fazerDevolucao();}
            else if(OPC==3) {OPC = 1; listarLocacoes();}
            else if(OPC==4) {OPC = 1;  a = 2;}
        }//FIM TELCA ENTER
    }//FIM WHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}
#endif
