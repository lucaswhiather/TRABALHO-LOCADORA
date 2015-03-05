#ifndef _CLIENTE_H_

void exibirExtratoTXT(struct reg_cliente cliente){
     struct data data;
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
     char nome_arquivo[35];
     char string[200];
     char abrir_arquivo[50];

     int aux = 0;
     int aux_loca = 0;
     int aux_filme = 0;

     strcpy(nome_arquivo,"extrato\\");
     strcat(nome_arquivo,cliente.nome);
     strcat(nome_arquivo,".txt");

     fplocadev = fopen(arquivoLocadev,"rb");
         while (fread(&locadev,sizeof(locadev),1,fplocadev)==1)
             if(cliente.codigo==locadev.cliente)
                aux_loca++;

     fclose(fplocadev);

     int lista_filme[aux_loca];

    fplocadev = fopen(arquivoLocadev,"rb");
         while (fread(&locadev,sizeof(locadev),1,fplocadev)==1)
             if(cliente.codigo==locadev.cliente){
                 lista_filme[aux_filme];
                 aux_filme++;
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
     for(int x = 0; x<aux_loca; x++){
         fpfilme = fopen(arquivoFilme,"rb");
         while (fread(&filme,sizeof(filme),1,fpfilme)==1)
            if(lista_filme[x]==filme.codigo)
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

         sprintf(string,"\n\nCódigo: %i \nTitulo: %s \nGênero: %s \nCategoria: %s \nPreço: %5.2f",filme.codigo,filme.titulo,genero.genero,categoria.categoria,categoria.preco);
         fputs(string,fpextrato);
     }

     fclose(fpextrato);
     strcpy(abrir_arquivo,"start ");
     strcat(abrir_arquivo,nome_arquivo);
     system(abrir_arquivo);


}

void mostrarExtratoCliente(struct reg_cliente cliente){
    OPC = 1;
    int a = 1;
    while(a==1){
        textoDoMenu(7,20,1,"Mostar extrato",COR_MENU);
        textoDoMenu(7,22,2,"Voltar",COR_MENU);
        andarMenu(2);
        if (TECLA==13){
            if(OPC==1)exibirExtratoTXT(cliente);
            else if(OPC==2){OPC = 1; a = 2;}
        }
    }
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");

}

void apresentarDadosCliente(int posX, int posY,struct reg_cliente cliente){//APRESENTAR DADOS DO CLIENTE
    campo(posX,posY,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    texto(7,8,3,"C\242digo: ");
    printf("%i",cliente.codigo);
    texto(7,10,3,"Nome:");
    printf(" %s",cliente.nome);
    texto(7,12,3,"Rua:");
    printf(" %s",cliente.end_rua);
    texto(7,14,3,"N\247:");
    printf(" %i",cliente.end_numero);
    texto(7,16,3,"Telefone:");
    printf(" %i",cliente.telefone);
    texto(7,18,3,"Email:");
    printf(" %s",cliente.email);
}//FIM APRESENTAR DADOS DO CLIENTE

struct reg_cliente procurarClienteCodigo(){//PROCURAR CLIENTE PELO CÓDIGO
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    struct reg_cliente cliente;
    FILE *fpcliente;
    int cod;
    int achou = 0;

    texto(7,8,COR_LETRA,"Digite o c\242digo do cliente:");
    campoDeInt(35,8,4,COR_LETRA,BLACK,&cod);

    fpcliente = fopen(arquivoCliente,"rb");
    while ((!achou)&&(fread(&cliente,sizeof(cliente),1,fpcliente)==1))
            if(cod==cliente.codigo)
                achou = 1;
    fclose(fpcliente);

    if(achou==0){
        texto(7,10,RED,"C\242digo nao encontrado");
        OPC = 1;
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        cliente.codigo = -1;
        getch();
    }
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return cliente;
}//FIM PROCURAR CLIENTE PELO CÓDIGO

struct reg_cliente procurarClienteNomeInteiro(){//PROCURAR CLIENTE PELO NOME INTEIRO
    struct reg_cliente cliente;
    FILE *fpcliente;
    char nome[30];
    int achou = 0;

    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    texto(7,8,COR_LETRA,"Digite o nome inteiro:");
    campoDeString(30,8,sizeof(nome),COR_LETRA,BLACK,&nome[0]);

    fpcliente = fopen(arquivoCliente,"rb");
    while ((!achou)&&(fread(&cliente,sizeof(cliente),1,fpcliente)==1))
            if(strcmp(cliente.nome,nome)==0)
                achou = 1;
    fclose(fpcliente);

    if(achou==0){
        texto(7,10,RED,"Nome nao encontrado");
        OPC = 1;
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        cliente.codigo = 0;
        getch();
    }
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return cliente;
}//FIM PROCURAR CLIENTE PELO NOME INTEIRO

struct reg_cliente procurarClientePalavraChave(){//PROCURAR CLIENTE POR PALAVRA CHAVE NO NOME
    struct reg_cliente cliente;
    FILE *fpcliente;
    char nome[30];
    int achou = 0;

    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    texto(7,8,COR_LETRA,"Digite uma palavra:");
    campoDeString(28,8,sizeof(nome),COR_LETRA,BLACK,&nome[0]);

    fpcliente = fopen(arquivoCliente,"rb");
    while ((!achou)&&(fread(&cliente,sizeof(cliente),1,fpcliente)==1))
            if(strstr(cliente.nome,nome)!=NULL)
                achou = 1;
    fclose(fpcliente);

    if(achou==0){
        texto(7,10,RED,"Palavara n\306o encontrada");
        OPC = 1;
        textoDoMenu(7,12,1,"Voltar",COR_MENU);
        cliente.codigo = 0;
        getch();
    }
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return cliente;
}//FIM PROCURAR CLIENTE POR PALAVRA CHAVE NO NOME

struct reg_cliente selecionarClienteManualmente(){//SELECIONAR CLIENTE MANUALMENTE
     system("cd func&start selecionarCliente.exe");
     FILE *fpcliente;
     struct reg_cliente cliente;
     int cod = 0;

     while((fpcliente = fopen("func\\selecionarCliente.dat","rb"))==NULL)
         _sleep(2000);

     fread(&cod,sizeof(cod),1,fpcliente);
     fclose(fpcliente);

     _sleep(2000);
     system("Del func\\selecionarCliente.dat");

     fpcliente = fopen(arquivoCliente,"rb");
     while (fread(&cliente,sizeof(cliente),1,fpcliente)==1)
         if(cod==cliente.codigo)
             break;
     fclose(fpcliente);

     return cliente;
}//FIM SELECIONAR CLIENTE MANUALMENTE

struct reg_cliente menuSelecionarCliente(){//MENU SELECIONAR CLIENTE
    campo(7,8,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    struct reg_cliente cliente;
    int a = 1;
    cliente.codigo = 0;
    OPC = 1;
    if(quantidadeDeRegistro(arquivoCliente)==0){
        campo(7,8,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");;
        texto(7,8,RED,"Nenhum cliente cadastrado");
        OPC = 1;
        textoDoMenu(7,10,1,"Voltar",COR_MENU);
        getch();
        campo(7,8,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
        a = 2;
    }

    while(a==1){
        texto(7,8,CYAN,"SELECIONAR CLIENTE");
        textoDoMenu(7,10,1,"Procurar pelo c\242digo",COR_MENU);
        textoDoMenu(7,12,2,"Procurar pelo nome inteiro",COR_MENU);
        textoDoMenu(7,14,3,"Procurar por palavra chave no nome",COR_MENU);
        textoDoMenu(7,16,4,"Selecionar manualmente",COR_MENU);
        textoDoMenu(7,18,5,"Voltar",COR_MENU);
        andarMenu(5);
        if(TECLA==27){OPC = 1; a = 2;} //tecla esc
        if (TECLA==13){
            if(OPC==1){OPC = 1; cliente = procurarClienteCodigo();}
            else if(OPC==2){OPC = 1; cliente = procurarClienteNomeInteiro();}
            else if(OPC==3){OPC = 1; cliente = procurarClientePalavraChave();}
            else if(OPC==4){OPC = 1; cliente = selecionarClienteManualmente();}
            else if(OPC==5){OPC = 1; a = 2;}
        }
        if(cliente.codigo>0)
            return cliente;

    }//FIM WHILE a
    campo(7,8,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    return cliente;
};//FIM MENU SELECIONAR CLIENTE

void listarClienteParteIniciarNome(){//LISTAR CLIENTES PELA PARTE INICIAR DO NOME
     FILE *fpcliente;
     struct reg_cliente cliente;
     int quantidade = 0;
     int aux = 0;
     OPC = 1;
     char nome_cliente[30];

    if(quantidadeDeRegistro(arquivoCliente)==0){
        campo(7,8,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");;
        texto(7,8,RED,"Nenhum cliente cadastrado");
        OPC = 1;
        textoDoMenu(7,10,1,"Voltar",COR_MENU);
        getch();
        campo(7,8,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
        return;
    }

     campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
     texto(7,8,3,"Parte inicial do nome: ");
     campoDeString(30,8,sizeof(nome_cliente),COR_LETRA,BLACK,&nome_cliente[0]);
//----------------------------------------------------------------------
    fpcliente = fopen(arquivoCliente,"rb");
    while (fread(&cliente,sizeof(cliente),1,fpcliente)==1)
            if(strncmp(cliente.nome,nome_cliente,strlen(nome_cliente))==0)
                quantidade++;
    fclose(fpcliente);

    char nome_parte[quantidade][30];

    fpcliente = fopen(arquivoCliente,"rb");
    while (fread(&cliente,sizeof(cliente),1,fpcliente)==1)
            if(strncmp(cliente.nome,nome_cliente,strlen(nome_cliente))==0){
                strcpy(nome_parte[aux],cliente.nome);
                aux++;
            }
    fclose(fpcliente);

    int pagina = 1;
    int paginas = 0;
    paginas = (quantidade/8);
    if(quantidade%8!=0)
    paginas++;
    texto(7,10,COR_LETRA,"Clientes encontrados: ");printf("%i",quantidade);
    int a = 1;
    while(a==1){
        int auxY = 12;
        if(quantidade>0){
            for(int x = 0; x<8; x++)
                if(((pagina-1)*8)+x<quantidade){
                    texto(7,auxY,COR_LETRA,nome_parte[((pagina-1)*8)+x]);
                    auxY++;
                }
        }
        else
            texto(7,20,RED,"Nenhum cliente foi encontrado");

        textoDoMenu(8,22,1,"<<<<",COR_MENU);
        textoDoMenu(15,22,2,"Voltar",COR_MENU);
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

}//FIM LISTAR CLIENTES PELA PARTE INICIAR DO NOME

void editarCliente(struct reg_cliente cliente){//EDITAR CLIENTE
    FILE *fpcliente;
    int a = 1;
    int achou = 0;
    struct reg_cliente cliente2;
    while(a==1){
        textoDoMenu(7,10,1,"Nome:",3);
        textoDoMenu(7,12,2,"Rua:",3);
        textoDoMenu(7,14,3,"N\247:",3);
        textoDoMenu(7,16,4,"Telefone:",3);
        textoDoMenu(7,18,5,"Email:",3);
        textoDoMenu(7,20,6,"Gravar e sair",COR_MENU);
        textoDoMenu(7,22,7,"Voltar",COR_MENU);
        andarMenu(7);
        if(TECLA==27) {OPC = 1; a = 2;} //tecla esc
        if (TECLA==13){
            if(OPC==1) campoDeString(13,10,sizeof(cliente.nome),COR_LETRA,BLACK,&cliente.nome[0]);
            if(OPC==2) campoDeString(12,12,sizeof(cliente.end_rua),COR_LETRA,BLACK,&cliente.end_rua[0]);
            if(OPC==3) campoDeInt(11,14,5,COR_LETRA,BLACK,&cliente.end_numero);
            if(OPC==4) campoDeInt(17,16,10,COR_LETRA,BLACK,&cliente.telefone);
            if(OPC==5) campoDeString(14,18,sizeof(cliente.email),COR_LETRA,BLACK,&cliente.email[0]);
            if(OPC==6) {
                fpcliente = fopen(arquivoCliente,"rb+");
                while ((!achou)&&(fread(&cliente2,sizeof(cliente2),1,fpcliente)==1))
                    if(cliente.codigo==cliente2.codigo)
                        achou = 1;

                fseek(fpcliente,-1*sizeof(cliente),1);
                fwrite(&cliente,sizeof(cliente),1,fpcliente);
                fclose(fpcliente);
                texto(7,24,GREEN,"Os dados foram alterados com sucesso");
                _sleep(3500);
                OPC = 1;
                a = 2;
            }
            if(OPC==7) {OPC = 1; a = 2;}
        }//TECLA ENTER
    }  //FIM EHILE a
    campo(7,8,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}//FIM EDITAR CLIENTE

void excluirCliente(struct reg_cliente cliente){//EXCLUIR CLIENTE
    char arquivoClienteBack[25] = {"save\\clienteBack.dat"};
    FILE *fpcliente;
    FILE *fpclienteBack;
    FILE *fplocadev;
    struct reg_locadev locadev;
    int achou = 0;

    fplocadev = fopen(arquivoLocadev,"rb");
    while ((!achou)&&(fread(&locadev,sizeof(locadev),1,fplocadev)==1))
        if((cliente.codigo==locadev.cliente)&&(locadev.devolucao.dia==0))
            achou = 1;
    fclose(fplocadev);

    if(achou==1){
        texto(7,20,RED,"O cliente est\240 com loca\207\344s aberta");
        texto(7,21,RED,"por isso n\306o pode ser excluido");
        OPC = 1;
        textoDoMenu(7,23,1,"Voltar",COR_MENU);
        getch();
        campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
        return;
    }

    int a = 1;
    while(a==1){
        textoDoMenu(7,20,1,"Deletar",COR_MENU);
        textoDoMenu(7,22,2,"Voltar",COR_MENU);
        andarMenu(2);
        if(TECLA==27) {OPC = 1; a = 2;} //tecla esc
        if (TECLA==13){
            if(OPC==1){
                int codigo = cliente.codigo;
                fpcliente = fopen(arquivoCliente,"rb");
                fpclienteBack = fopen(arquivoClienteBack,"wb");
                    while(fread(&cliente,sizeof(cliente),1,fpcliente)==1)
                        if(codigo!=cliente.codigo)
                            fwrite(&cliente,sizeof(cliente),1,fpclienteBack);
                fclose(fpcliente);
                fclose(fpclienteBack);
                int auxDel = 0;
                if(quantidadeDeRegistro(arquivoCliente)==1)
                    auxDel = 1;

                system("del save\\cliente.dat");
                if(auxDel==0)
                    system("rename save\\clienteBack.dat cliente.dat");

                texto(7,24,RED,"Cliente deletado");
                _sleep(3500);
                OPC = 1;
                a = 2;
            }
            else if(OPC==2) {OPC = 1; a = 2;}
        }//TECLA ENTER
    }  //FIM EHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}//FIM EXCLUIR CLIENTE

void consultarCliente(struct reg_cliente cliente){//CONSULTAR CLIENTE
    FILE *fpcliente;
    FILE *fplocadev;
    FILE *fpfilme;
    int quantidade = 0;
    int a = 1;
    int aux = 0;
    struct reg_locadev locadev;
    struct reg_filme filme;

    fplocadev = fopen(arquivoLocadev,"rb");
    while (fread(&locadev,sizeof(locadev),1,fplocadev)==1)
            if(cliente.codigo==locadev.cliente)
                quantidade++;
    fclose(fplocadev);

    struct locacoes locacoes[quantidade];

    fplocadev = fopen(arquivoLocadev,"rb");
    while (fread(&locadev,sizeof(locadev),1,fplocadev)==1)
            if(cliente.codigo==locadev.cliente){
                strcpy(locacoes[aux].dataLocacao,dataFormatada(locadev.locacao,1,FALSE));
                if(locadev.devolucao.dia==0)locacoes[aux].status = 0;
                else locacoes[aux].status = 1;
                fpfilme = fopen(arquivoFilme,"rb");
                while(fread(&filme,sizeof(filme),1,fpfilme)==1)
                    if(locadev.filme==filme.codigo)
                        break;
                fclose(fpfilme);
                strcpy(locacoes[aux].tituloFilme,filme.titulo);
                aux++;
            }
    fclose(fplocadev);

    int pagina = 1;
    int paginas = 0;
    paginas = (quantidade/5);
    if(quantidade%5!=0)
    paginas++;

    while(a==1){
        int auxY = 20;
        texto(7,19,COR_LETRA,"Locacoes feitas: ");
        printf("%i",quantidade);
        if(quantidade>0){
            for(int x = 0; x<5; x++)
                if(((pagina-1)*5)+x<quantidade){
                    texto(7,auxY,COR_LETRA,locacoes[((pagina-1)*5)+x].dataLocacao);
                    texto(20,auxY,COR_LETRA,locacoes[((pagina-1)*5)+x].tituloFilme);
                    if(locacoes[((pagina-1)*5)+x].status==1)
                        texto(52,auxY,GREEN,"Encerrada");
                    else
                        texto(52,auxY,RED,"Aberta");
                    auxY++;
                }
        }
        else
            texto(7,20,RED,"Nenhuma locacao feita");

        textoDoMenu(12,25,1,"<<<<",COR_MENU);
        textoDoMenu(20,25,2,"Voltar",COR_MENU);
        textoDoMenu(40,25,3,">>>>",COR_MENU);

        andarMenu(3);

        if(TECLA==27) {OPC = 1; a = 2;} //tecla esc
        if (TECLA==13){
            if(OPC==1){pagina--; if(pagina<1) pagina = paginas; campo(7,20,tamanhoProgramaX,24,BLACK," ");}
            else if(OPC==2){OPC = 1; a = 2;}
            else if(OPC==3){ pagina++; if(pagina>paginas) pagina = 1; campo(7,20,tamanhoProgramaX,24,BLACK," ");}
        }//FIM TECLA ENTER
    }  //FIM EHILE a
    campo(5,7,tamanhoProgramaX-1,tamanhoProgramaY,BLACK," ");
}//FIM CONSULTAR CLIENTE

void menuPrincipalCliente(){//MENU CLIENTE PRINCIPAL
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    struct reg_cliente cliente;
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
    int a = 1;
    while(a==1){
        texto(7,8,CYAN,"MENU PRINCIPAL CLIENTE");
        textoDoMenu(7,10,1,"Cadastrar cliente",COR_MENU);
        textoDoMenu(7,12,2,"Editar cliente",COR_MENU);
        textoDoMenu(7,14,3,"Excluir cliente ",COR_MENU);
        textoDoMenu(7,16,4,"Listar clientes",COR_MENU);
        textoDoMenu(7,18,5,"Listar clientes pela parte inicial do nome",COR_MENU);
        textoDoMenu(7,20,6,"Consultar cliente",COR_MENU);
        textoDoMenu(7,22,7,"Mostrar extrato de um cliente",COR_MENU);
        textoDoMenu(7,24,8,"Voltar",COR_MENU);
        andarMenu(8);
        if(TECLA==27) a = 2; //tecla esc
        if (TECLA==13){ //AO PRESSIONAR A TECLA "ENTER"
            if(OPC==1) system("cd func&start cadastrarCliente.exe");
            else if(OPC==2){
                    cliente = menuSelecionarCliente();
                    if(cliente.codigo>0){
                        apresentarDadosCliente(5,7,cliente);
                        editarCliente(cliente);
                    }
            }
            else if(OPC==3){
                    cliente = menuSelecionarCliente();
                    if(cliente.codigo>0){
                        apresentarDadosCliente(5,7,cliente);
                        excluirCliente(cliente);
                    }
            }
            else if(OPC==4) system("cd func&start listarCliente.exe");
            else if(OPC==5) listarClienteParteIniciarNome();
            else if(OPC==6){
                    cliente = menuSelecionarCliente();
                    if(cliente.codigo>0){
                        apresentarDadosCliente(5,7,cliente);
                        consultarCliente(cliente);
                    }
            }
            else if(OPC==7){
                    cliente = menuSelecionarCliente();
                    if(cliente.codigo>0){
                        apresentarDadosCliente(5,7,cliente);
                        mostrarExtratoCliente(cliente);
                    }
            }
            else if(OPC==8) {OPC = 1; a = 2;}                   //voltar
        }
    }//FIM WHILE a
    campo(5,7,tamanhoProgramaX,tamanhoProgramaY-1,BLACK," ");
}//FIM MENU CLIENTE PRINCIPAL
#endif
