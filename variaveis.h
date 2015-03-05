#ifndef _FUNCOES_H_
//--------------------variavevis globais-----------------------
int OPC = 1;
int TECLA;
int COR_LETRA = 7;
int COR_SELECAO = 4;
int COR_FUNDO = BLACK;
int COR_MENU = WHITE;
int ITENS_PAGINA = 10;

struct reg_cliente{
    int codigo;
    char nome[30];
    char end_rua[30];
    int end_numero;
    int telefone;
    char email[30];
};

struct reg_filme{
    int codigo;
    char titulo[30];
    int genero;
    int categoria;
    int situacao;
};

struct reg_genero{
    int codigo;
    char genero[30];
};

struct reg_categoria{
    int codigo;
    char categoria[30];
    float preco;
};

struct data{
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;
};

struct reg_locadev{
    int codigo;
    struct data locacao;
    struct data devolucao;
    int cliente; //codigo do cliente
    int filme;   //codigo do filme
};

typedef struct reg_opcoes{
    int cor_letra;
    int cor_menu;
    int cor_fundo;
    int cor_selecao;
}opcao;
opcao opcoes;

struct locacoes{
    char dataLocacao[10];
    int status;
    char tituloFilme[30];
};

#endif
