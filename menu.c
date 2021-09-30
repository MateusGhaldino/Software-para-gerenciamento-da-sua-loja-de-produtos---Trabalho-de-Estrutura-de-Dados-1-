#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "cliente.h"
#include "menu.h"
#include "utilitarios.h"
#include "vendedor.h"
#include "Fornecedor.h"
#include "produto.h"
#include "notafiscal.h"
#include "ItemNotaFiscal.h"
#include "CompraFornecedor.h"
#include "NotaCompra.h"
#include "ItemNotaCompra.h"
#include "HistoricoPreco.h"
#include "relatorios.h"

void menuinicial(){

    int inicial, menu;

    FILE *arqclientes;

    arqclientes = fopen("Clientes.dat","rb+");

    if(arqclientes==NULL){
        arqclientes = fopen("Clientes.dat","wb+");
    };

    FILE *arqvendedores;
    arqvendedores = fopen("Vendedor.dat","rb+");

    if(arqvendedores==NULL){
        arqvendedores = fopen("Vendedor.dat","wb+");
    };

    FILE *arqfornecedores;
    arqfornecedores = fopen("Fornecedor.dat","rb+");

    if(arqfornecedores==NULL){
        arqfornecedores = fopen("Fornecedor.dat","wb+");
    };

    FILE *arqProdutos;
    arqProdutos = fopen("Produto.dat","rb+");

    if(arqProdutos==NULL){
      arqProdutos = fopen("Produto.dat","wb+");
    };

    FILE *arqnotafiscal;
    arqnotafiscal = fopen("NotaFiscal.dat","rb+");

    if(arqnotafiscal==NULL){
      arqnotafiscal = fopen("NotaFiscal.dat","wb+");
    };

    FILE *arqItemnotafiscal;
    arqItemnotafiscal = fopen("ItemNotaFiscal.dat","rb+");

    if(arqItemnotafiscal==NULL){
      arqItemnotafiscal = fopen("ItemNotaFiscal.dat","wb+");
    };

    FILE *arqnotacompra;
    arqnotacompra = fopen("NotaCompra.dat","rb+");

    if(arqnotacompra==NULL){
        arqnotacompra = fopen("NotaCompra.dat","wb+");
    };

    FILE *Item_arqnotacompra;
    Item_arqnotacompra = fopen("ItemNotaCompra.dat","rb+");

    if(Item_arqnotacompra==NULL){
        Item_arqnotacompra = fopen("ItemNotaCompra.dat","wb+");
    };

    FILE *arqHistoricoPreco;
    arqHistoricoPreco = fopen("HistoricoPreco.dat","rb+");

    if(arqHistoricoPreco==NULL){
        arqHistoricoPreco = fopen("HistoricoPreco.dat","wb+");
    };

    FILE *relatorio_a;
    relatorio_a = fopen("relatorio_a.txt","r+");

    if(relatorio_a==NULL){
        relatorio_a = fopen("relatorio_a.txt","w+");
    };


    FILE *relatorio_b;
    relatorio_b = fopen("relatorio_b.txt","r+");

    if(relatorio_b==NULL){
        relatorio_b = fopen("relatorio_b.txt","w+");
    };


    FILE *relatorio_c;
    relatorio_c = fopen("relatorio_c.txt","r+");

    if(relatorio_c==NULL){
        relatorio_c = fopen("relatorio_c.txt","w+");
    };

    FILE *relatorio_d;
    relatorio_d = fopen("relatorio_d.txt","r+");

    if(relatorio_d==NULL){
        relatorio_d = fopen("relatorio_d.txt","w+");
    };

    FILE *relatorio_e;
    relatorio_e = fopen("relatorio_e.txt","r+");

    if(relatorio_e==NULL){
        relatorio_e = fopen("relatorio_e.txt","w+");
    };

    FILE *relatorio_f;
    relatorio_f = fopen("relatorio_f.txt","r+");

    if(relatorio_f==NULL){
        relatorio_f = fopen("relatorio_f.txt","w+");
    };

    FILE *relatorio_g;
    relatorio_g= fopen("relatorio_g.txt","r+");

    if(relatorio_g==NULL){
        relatorio_g = fopen("relatorio_g.txt","w+");
    };

    FILE *relatorio_h;
    relatorio_h= fopen("relatorio_h.txt","r+");

    if(relatorio_h==NULL){
        relatorio_h = fopen("relatorio_h.txt","w+");
    };

    do{
        printf("\nSistema da Farmácia do Senhor Louco das Pedras");
        printf("\n1 - Manutenção das tabelas Cliente\n2 - Manutenção da tabela Vendedor \n3 - Manutenção da tabela Fornecedor \n4 - Cadastro de Produto  \n5 - Efetuar uma venda \n6 - Efetuar uma compra \n7 - Atualizar Preço \n8 - relátorios \n9 - Sair \nO que deseja fazer?:");
        scanf("%d",&inicial);
        switch(inicial){

        case 1:
            do{
                printf("\nBem vindo ao menu do cliente");
                printf("\n1 - Cadastro\n2 - Alteração\n3 - Consulta\n4 - Listagem\n5- Sair do menu clientes\nO que deseja fazer?:");
                scanf("%d",&menu);
                switch(menu){
                case 1:
                    cadastro(arqclientes);
                    break;
                case 2:
                    alterar(arqclientes);
                    break;
                case 3:
                    consulta(arqclientes);
                    break;
                case 4:
                    listar(arqclientes);
                    break;
                };
            }while(menu!=5);
            break;
        case 2:

            do{
                printf("\nBem vindo ao menu do vendedor");
                printf("\n1 - Cadastro\n2 - Alteração\n3 - Consulta\n4 - Listagem\n5- Sair do menu vendedor\nO que deseja fazer?:");
                scanf("%d",&menu);
                switch(menu){
                case 1:
                    cadastroVendedores(arqvendedores);
                    break;
                case 2:
                    alterarVendedores(arqvendedores);
                    break;
                case 3:
                    consultaVendedores(arqvendedores);
                    break;
                case 4:
                    listarVendedores(arqvendedores);
                    break;
                };
            }while(menu!=5);
            break;
        case 3:
            do{
                printf("\nBem vindo ao menu do Fornecedor");
                printf("\n1 - Cadastro\n2 - Alteração\n3 - Consulta\n4 - Listagem\n5- Sair do menu Fornecedor\nO que deseja fazer?:");
                scanf("%d",&menu);
                switch(menu){
                case 1:
                    cadastroFornecedor(arqfornecedores);
                    break;
                case 2:
                    alterarFornecedor(arqfornecedores);
                    break;
                case 3:
                    consultaFornecedor(arqfornecedores);
                    break;
                case 4:
                    listarFornecedor(arqfornecedores);
                    break;
                };
            }while(menu!=5);
            break;
        case 4:
            cadastroProdutos(arqProdutos);
            break;
        case 5:
            comprasvendedor(arqItemnotafiscal,arqnotafiscal,arqclientes,arqvendedores,arqProdutos);
            break;
        case 6:
            compras_Fornecedor(arqfornecedores,arqProdutos,arqnotacompra,Item_arqnotacompra);
            break;
        case 7:
            AtualizarPreco(arqProdutos,arqHistoricoPreco);
            break;
        case 8:
            do{
                printf("\nBem Vindo ao menu de Relatórios!\n1 - Dados de uma nota Fiscal e os itens associados a ela");
                printf("\n2 - Dados de uma compra e os itens associados a ela");
                printf("\n3 - Compras efetuadas por um cliente em uma data específica, bem como em um intervalo de datas");
                printf("\n4 - Vendas efetuadas por um vendedor em um dia específico");
                printf("\n5 - Vendas realizadas por um vendedor em um determinado mês");
                printf("\n6 - Dados de uma determinada notaFiscal a partir do seu número.");
                printf("\n7 - Dados de uma determinada notaCompra a partir do seu número.");
                printf("\n8 - Histórico de valor de venda de um determinado produto");
                printf("\n9 - Sair\nO que deseja fazer?:");
                scanf("%d",&menu);
                switch(menu){
                case 1:
                    ConsultaNotaFiscal_Itens(relatorio_a,arqnotafiscal,arqItemnotafiscal);
                    break;
                case 2:
                    ConsultaCompra_Itens(relatorio_b,arqnotacompra,Item_arqnotacompra);
                    break;
                case 3:
                    Consulta_Compras_Efetuadas_clientedata(relatorio_c,arqclientes,arqnotafiscal,arqItemnotafiscal);
                    break;
                case 4:
                    Consulta_Compras_Efetuadas_vendedordata(relatorio_d,arqvendedores,arqnotafiscal);
                    break;
                case 5:
                    Consulta_Compra_Efetuadas_vendedor_mes(relatorio_e,arqvendedores,arqnotafiscal);
                    break;
                case 6:
                    Consulta_Nota_Fiscal(relatorio_f,arqnotafiscal);
                    break;
                case 7:
                    Consulta_Nota_Compra(relatorio_g,arqnotacompra);
                    break;
                case 8:
                    consultaHistorico_relatorio(relatorio_h,arqHistoricoPreco);
                    break;
                }
            }while(menu!=9);
            break;
        };

    }while(inicial!=9);
    fclose(arqclientes);
    fclose(arqvendedores);
    fclose(arqfornecedores);
    fclose(arqProdutos);
    fclose(arqnotafiscal);
    fclose(arqItemnotafiscal);
    fclose(arqnotacompra);
    fclose(Item_arqnotacompra);
    fclose(arqHistoricoPreco);
    fclose(relatorio_a);
    fclose(relatorio_b);
    fclose(relatorio_c);
    fclose(relatorio_d);
    fclose(relatorio_e);
    fclose(relatorio_f);
    fclose(relatorio_g);
    fclose(relatorio_h);
}
