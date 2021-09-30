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
#include "compra.h"
#include "notafiscal.h"
#include "ItemNotaFiscal.h"
#include "CompraFornecedor.h"
#include "NotaCompra.h"
#include "ItemNotaCompra.h"
#include "HistoricoPreco.h"
#include "relatorios.h"


void alterarItem_Fornecedor(FILE *arq,Fornecedor_carrinho c[],int *ultimapos){
    unsigned int quantidade;
    unsigned long id;
    int posicaovetor,sair;
    if(*ultimapos>=0){
        printf("\nForneça o id do produto que você deseja alterar:");
        scanf("%lu",&id);
        posicaovetor = Consultacarrinho_Fornecedor(c,id,*ultimapos);
        if(posicaovetor!=-1){
             do{
                printf("\nForneça a quantidade que você deseja colocar no carrinho:");
                scanf("%u",&quantidade);

                printf("\nAlterado com sucesso");
                c[posicaovetor].quantidade=quantidade;
                sair=1;
             }while(sair!=1);
            }
        else{
            printf("\nId do produto foi não encontrado!!!\n");
        };
    }
    else
        printf("\nO carrinho está vazio!!");
}
void excluirItem_Fornecedor(Fornecedor_carrinho c[],int *ultimapos){
    unsigned long id;
    int posicao,i = *ultimapos;
    if(*ultimapos>0){
        printf("\nForneça o id do produto que você deseja cancelar:");
        scanf("%lu",&id);
        posicao = Consultacarrinho_Fornecedor(c,id,i);
        if(posicao!=-1){
                c[posicao]=c[*ultimapos];
                (*ultimapos)--;
                printf("\nItem excluído do carrinho com Sucesso!!");
            }
            else
                printf("\nId não encontrado!!!\n");
    }
    else
        printf("\nO carrinho está vazio!!");
}
int Consultacarrinho_Fornecedor(Fornecedor_carrinho ca[],unsigned long id,int pos){
    int j=0;
    for (int i=0;i<=pos;i++){
        if(ca[i].idProduto==id){
            return j;
        }
        else
            j++;
    }
    return -1;
}

void compras_Fornecedor(FILE *arqfornecedores,FILE *arqprodutos,FILE *arqnotacompra,FILE *arqItemcompra){
    fornecedor fe;
    int sair,achou,posicaoFor,posicaoPro,comando,op,i,c;
    unsigned long idproduto,idFornecedor,idnotafiscalCompra;
    unsigned int quantidade;
    char CNPJ[15];
    float total;
    Fornecedor_carrinho *ca;
    i=0;
    printf("\nBem vindo(a) ao carrinho de compras do Fornecedor");

    do{
        //Autenticação do Fornecedor
        do{
            printf("\nPrimeiro vamos fazer a autenticação para a venda");
            printf("\nPrezado Fornecedor,\nForneça seu CNPJ:");
            lestring(CNPJ);

            posicaoFor = pesquisaCNPJFornecedor(arqfornecedores,CNPJ);
            if(posicaoFor!=-1){
                printf("\nAutenticado com sucesso!!!!");
            }
            else{
            printf("\nCNPJ não cadastrado!!");
            sair=0;
            };


            do{
                ca = (Fornecedor_carrinho *) malloc(sizeof(Fornecedor_carrinho));
                if(ca == NULL) printf("\nErro ao alocar memória");

                if(posicaoPro!=-1){
                  /*Printando os dados do vendendor na tela*/
                  fseek(arqfornecedores,posicaoPro*sizeof(fornecedor),SEEK_SET);
                  fread(&fe,sizeof(fornecedor),1,arqfornecedores);
                  printf("\nEssa Compra está sendo realizada pelo(a) fornecedor(a):%s.ID:%li\n",fe.nome,fe.id);
                  idFornecedor = fe.id;
                  /*Entrando no carrinho de venda*/
                  do{
                    printf("\nBem vindo ao carrinho de compras");
                    printf("\n------------------\n");
                    printf("\n1 -Adicionar um item ao carrinho \n2-Listar itens do Carrinho \n3-Cancelar item do carrinho \n4 -Alterar quantidade de algum item do carrinho \n5 -Sair do carrinho e finalizar compra \nO que desejar fazer?:");
                    scanf("%d",&comando);
                    switch(comando){
                    case 1:
                            do{
                                do{
                                    printf("\nItens no carrinho:%d",i);
                                    printf("\nForneça o codigo do produto:");
                                    scanf("%lu",&idproduto);

                                    if(consultaProduto(arqprodutos,idproduto)!=-1){
                                    //    Verificando se o produto existe no carrinho compras
                                        if(Consultacarrinho(ca,idproduto,i)==-1){
                                            posicaoPro=consultaProduto(arqprodutos,idproduto);
                                            ca[i].idProduto=idproduto;
                                            sair=1;
                                        }
                                        else{
                                            printf("\nO Produto ja se encontra no carrinho!!");
                                            sair=0;
                                            };
                                    }
                                    else{
                                        sair=0;
                                        printf("\nProduto não Cadastrado");
                                        }

                                }while(sair!=1);

                                do{
                                    printf("\nForneça a quantidade a ser Comprada:");
                                    scanf("%u",&ca[i].quantidade);
                                    quantidade=ca[i].quantidade;
                                    if(quantidade==0){
                                        printf("\nA quantidade não pode ser 0");
                                        sair=0;
                                    }
                                    else
                                        printf("\nQuantidade adiciona com Sucesso no carrinho");
                                }while(sair!=1);
                                /*Passando o preço do produto para struct*/
                                do{
                                    printf("\nForneça o Preço Unitário desse Produto:");
                                    scanf("%f",&ca[i].valorUnitario);
                                    if(ca[i].valorUnitario==0){
                                        printf("\nPreço Inválido");
                                        sair=0;
                                    }
                                    else{
                                        printf("\nValor válido");
                                        sair=1;
                                    }
                                }while(sair!=1);
                                c=i;
                                i++;
                                ca = (Fornecedor_carrinho *) realloc(ca,(i+1)* sizeof(Fornecedor_carrinho));
                                if(ca == NULL) printf("\nErro ao alocar memória");

                                printf("\nDeseja adicionar mais algum item no carrinho? \n1 -Sim \n2-Não \nO que desejar fazer:");
                                scanf("%d",&op);
                            }while(op!=2);
                        break;
                    case 2:

                        for (int j=0;j<=c;j++){
                            printf("\nCódigo do produto:%lu",ca[j].idProduto);
                            printf("\nQuantidade vendida:%u",ca[j].quantidade);
                            printf("\nValor:%f",ca[j].valorUnitario);
                        }
                        break;
                    case 3:
                        excluirItem_Fornecedor(ca,&c);
                        break;
                    case 4:
                        alterarItem_Fornecedor(arqprodutos,ca,&c);
                        break;
                    case 5:
                        if(ca[0].idProduto!=0){
                            /*Somando os preços de cada carrinho*/
                            for(int j=0;j<=i;j++){
                                total = (ca[j].valorUnitario * ca[j].quantidade) + total;
                            }
                            printf("\nTotal do carrinho:%f",total);

                            gerarNotaCompra(arqnotacompra,idFornecedor,&idnotafiscalCompra,total);
                            /**/
                            gerar_ItemNota_fiscal(arqItemcompra,ca,i,idnotafiscalCompra);
                            /**/
                            alteraestoqueForne(arqprodutos,ca,c);

                            i=0;c=0;total=0;comando=6;
                            for(int j=0;j<=c;j++){
                                ca[j].idProduto=0;
                                ca[j].quantidade=0;
                                ca[j].valorUnitario=0;
                            };
                            free(ca);
                            break;
                        }
                        else{
                            printf("\nO carrinho está vazio!!!");
                            comando=6;
                        break;
                        };
                    };
                  }while(comando!=6);
                }
                else{
                    printf("\nFornecedor não encontrado");
                };

                printf("\nFornecedor, deseja Sair? \n1-Se sim, você será deslogado. \n2-Se não, você poderá continuar realizando compras com esse mesmo login.\nO que você deseja fazer?:");
                 scanf("%d",&achou);
            }while(achou!=1);
            sair=1;
        }while(sair!=1);
        sair=1;
    }while(sair!=1);
}

void gerar_ItemNota_fiscal_Compra_Fornecedor(FILE * arqItemcompra,Fornecedor_carrinho ca[],int i,unsigned long idnotafiscalCompra){
    ItemNotaCompra It;
    unsigned long id;
    int cont;
    printf("\nGerando de a nota fiscal de cada item");

    for(cont=0;cont<i;cont++){
        id=incrementoIDItemNotaCompra(arqItemcompra);
        It.id = id;
        It.idNotaCompra = idnotafiscalCompra;
        It.idProduto = ca[cont].idProduto;
        It.quantidade = ca[cont].quantidade;
        It.valorUnitario = ca[cont].valorUnitario;
        printf("\nId da Nota Item:%lu",It.id);
        printf("\nId do Produto:%lu",It.idProduto);
        printf("\nId da Nota Fiscal:%lu",It.idNotaCompra);
        printf("\nId Quantidade:%u",It.quantidade);
        printf("\nValor de unitário:%f",It.valorUnitario);
        fseek(arqItemcompra,0,SEEK_END);
        fwrite(&It,sizeof(ItemNotaCompra),1,arqItemcompra);
    };

}
void alteraestoqueForne(FILE *arq,Fornecedor_carrinho ca[],int i){
    int cont,posicaoPro;
    unsigned long id;
    unsigned int quantidade,quantidade_2,resultado;
    produto pr;
    for(cont=0;cont<=i;cont++){

        id = ca[cont].idProduto;

        posicaoPro = consultaProduto(arq,id);

        if(posicaoPro!=-1){
            quantidade=ca[cont].quantidade;
            fseek(arq,posicaoPro*sizeof(produto),SEEK_SET);
            fread(&pr,sizeof(produto),1,arq);
            quantidade_2 = pr.quantidadeEstoque;
            resultado = quantidade_2 + quantidade;
            pr.quantidadeEstoque = resultado;

            fseek(arq,posicaoPro*sizeof(produto),SEEK_SET);
            fwrite(&pr,sizeof(produto),1,arq);
            printf("\nProduto Alterado com Sucesso no estoque! Produto de posição %d no carrinho",cont + 1);

        }
        else
            printf("\nErro ao procurar o id do produto");

    };

}
