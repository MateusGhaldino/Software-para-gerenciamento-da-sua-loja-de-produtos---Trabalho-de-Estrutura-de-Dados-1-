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

void alterarItem(FILE *arq,carrinho c[],int *ultimapos){
    unsigned int quantidade;
    unsigned long id;
    int posicao,posicaovetor,sair;
    if(*ultimapos>=0){
        printf("\nForneça o id do produto que você deseja alterar:");
        scanf("%lu",&id);
        posicaovetor = Consultacarrinho(c,id,*ultimapos);
        posicao = consultaProduto(arq,id);
        if(posicaovetor!=-1){
             do{
                printf("\nForneça a quantidade que você deseja colocar no carrinho:");
                scanf("%u",&quantidade);

                if(consultaEstoqueProduto(arq,posicao,quantidade)==1){
                    printf("\nAlterado com sucesso");
                    c[posicaovetor].quantidadeVendida=quantidade;
                    sair=1;
                }
                else{
                    printf("\nNão foi possível alterar a quantidade desse item porque não disponibilidade no estoque");
                    sair=0;
                };
             }while(sair!=1);
            }
            else
                printf("\nId do produto foi não encontrado!!!\n");
    }
    else
        printf("\nO carrinho está vazio!!");
}
void excluirItem(carrinho c[],int *ultimapos){
    unsigned long id;
    int posicao,i = *ultimapos;
    if(*ultimapos>0){
        printf("\nForneça o id do produto que você deseja cancelar:");
        scanf("%lu",&id);
        posicao = Consultacarrinho(c,id,i);
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
int Consultacarrinho(carrinho c[],unsigned long id,int pos){
    int j=0;
    for (int i=0;i<pos;i++){
        if(c[i].idProduto==id){
            return j;
        }
        else
            j++;
    }
    return -1;
}
int ConsultasenhaVendedor(FILE *arq,char *senha){
    vendedor ve;
    int posicao=0;

    fseek(arq,0,SEEK_SET);
    while(fread(&ve,sizeof(vendedor),1,arq)==1){
        if(strcmp(ve.password,senha)==0){
            return posicao;
        }else
            posicao++;
    }
    return -1;
}

void comprasvendedor(FILE *arqitemnotafiscal,FILE *arqnotafiscal,FILE *arqclientes,FILE *arqvendedores, FILE *arqprodutos){
    int sair,achou,posicaoCli,posicaoVen,posicaoPro,comando,op,i,c;
    unsigned long idcliente,idproduto,idvendedor,idnotafiscal;
    unsigned int quantidade;
    char CPF[12],senha[20];
    float total;
    vendedor ve;
    cliente ce;
    carrinho *ca;
    produto pr;
    i=0;
    printf("\nBem vindo(a) ao carrinho de compras");

    do{
        //Autenticação do vendedor
        do{
            printf("\nPrimeiro vamos fazer a autenticação para a venda");
            printf("\nPrezado Vendedor,\nForneça seu cpf:");
            lestring(CPF);
            if(validarCPF(CPF)==0){
                printf("\nCPF Inválido!!!");
                sair=0;
            }
            else{
                //Validando o CPF do vendendor;
                posicaoVen = pesquisaCpfVendedores(arqvendedores,CPF);
              if(posicaoVen!=-1){

                do{
                    printf("\nForneça a sua senha:");
                    lestring(senha);

                    //Validando a senha do Vendendor;
                    if(ConsultasenhaVendedor(arqvendedores,senha)!=-1){
                        printf("\nSenha Validada com sucesso!");
                        achou=1;
                        sair =1;

                    }
                    else{
                        printf("\nSenha Inválida!!");
                        achou=0;
                    };

                }while(achou!=1);
              }

              else{
                printf("\nCPF não cadastrado!!");
                sair=0;
            };

            }while(sair!=1);

            do{
                printf("\nEstamos quase lá, agora vamos para a parte do cliente");

                printf("\nPor favor, informe o ID do cliente :");
                scanf("%lu",&idcliente);

                //Validando o ID do cliente;
                /*Alocando memória para o carrinho*/
                ca = (carrinho *) malloc(sizeof(carrinho));
                if(ca == NULL) printf("\nErro ao alocar memória");

                posicaoCli = pesquisaid(arqclientes,idcliente);

                if(posicaoCli!=-1){
                  printf("\nProntinho \nVendedor e Cliente autenticados com sucessos!!\n");

                  /*Printando os dados do vendendor na tela*/
                  fseek(arqvendedores,posicaoVen*sizeof(vendedor),SEEK_SET);
                  fread(&ve,sizeof(vendedor),1,arqvendedores);
                  printf("\nEssa venda está sendo realizada pelo(a) vendendor(a):%s.ID:%li\n",ve.Nome,ve.id);
                  idvendedor = ve.id;
                  /*Printando os dados do cliente na tela*/
                  fseek(arqclientes,posicaoCli*sizeof(cliente),SEEK_SET);
                  fread(&ce,sizeof(cliente),1,arqclientes);
                  idcliente = ce.id;
                  printf("\nEssa venda está sendo realizada ao(a) cliente:%s.ID:%li\n",ce.nome,ce.id);

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
                                        /*Verificando se o produto existe no carrinho compras*/
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
                                        printf("\nProduto não encontrado");
                                        }

                                }while(sair!=1);

                                do{
                                    printf("\nForneça a quantidade a ser vendida:");
                                    scanf("%u",&ca[i].quantidadeVendida);
                                    quantidade=ca[i].quantidadeVendida;

                                    if(consultaEstoqueProduto(arqprodutos,posicaoPro,quantidade)==1){
                                            printf("\nQuantidade disponivel e adicionada no carrinho");
                                            sair=1;
                                    }
                                    else{
                                        sair=0;
                                        printf("\nQuantidade insuficiente no estoque!!");
                                        fseek(arqprodutos,posicaoPro*sizeof(produto),SEEK_SET);
                                        fread(&pr,sizeof(produto),1,arqprodutos);
                                        printf("\nQuantidade disponível = %u",pr.quantidadeEstoque);
                                    };
                                }while(sair!=1);
                                /*Passando o preço do produto para struct*/
                                ca[i].valorVenda=consultaPreco(arqprodutos,idproduto);

                                i++;
                                c=i;
                                ca = (carrinho *) realloc(ca,(i+1)* sizeof(carrinho));
                                if(ca == NULL) printf("\nErro ao alocar memória");

                                printf("\nDeseja adicionar mais algum item no carrinho? \n1 -Sim \n2-Não \nO que desejar fazer:");
                                scanf("%d",&op);
                            }while(op!=2);
                        break;
                    case 2:

                        for (int j=0;j<=c;j++){
                            printf("\nCódigo do produto:%lu",ca[j].idProduto);
                            printf("\nQuantidade vendida:%u",ca[j].quantidadeVendida);
                            printf("\nValor:%f",ca[j].valorVenda);
                        }
                        break;
                    case 3:
                        excluirItem(ca,&c);
                        break;
                    case 4:
                        alterarItem(arqprodutos,ca,&c);
                        break;
                    case 5:
                        /*Somando os preços de cada carrinho*/
                    if(ca[0].idProduto!=0){

                        for(int j=0;j<=i;j++){
                            total = (ca[j].valorVenda * ca[j].quantidadeVendida) + total;
                        }
                        printf("\nTotal do carrinho:%f",total);

                        gerarNotaFiscal(arqnotafiscal,idcliente,idvendedor,&idnotafiscal,total);
                        gerar_ItemNota_fiscal(arqitemnotafiscal,ca,c,idnotafiscal);
                        alteraestoque(arqprodutos,ca,c);
                        i=0;c=0;total=0;comando=6;
                        for(int j=0;j<=c;j++){
                            ca[j].idProduto=0;
                            ca[j].quantidadeVendida=0;
                            ca[j].valorVenda=0;
                        };
                        free(ca);
                        break;
                    }
                    else{
                        printf("\nO carrinho está vazio!!!");
                        i=0;c=0;total=0;comando=6;
                        for(int j=0;j<=c;j++){
                            ca[j].idProduto=0;
                            ca[j].quantidadeVendida=0;
                            ca[j].valorVenda=0;
                        };
                        free(ca);
                        break;}
                    };
                  }while(comando!=6);
                }
                else{
                    printf("\nCliente não encontrado");
                };

                printf("\nVendedor, deseja Sair? \n1-Se sim, você será deslogado. \n2-Se não, você poderá continuar realizando compras com esse mesmo login.\nO que você deseja fazer?:");
                scanf("%d",&achou);
            }while(achou!=1);
            sair=1;
        }while(sair!=1);
        sair=1;
    }while(sair!=1);
}
void gerar_ItemNota_fiscal(FILE *arqitemnotafiscal,carrinho c[],int i,unsigned long idnotafiscal){
    ItemNotaFiscal In;
    unsigned long id;
    int cont;
    printf("\nGerando de a nota fiscal de cada item");

    for(cont=0;cont<i;cont++){
        id=incrementoIDItemNotaFiscal(arqitemnotafiscal);
        In.id = id;
        In.idProduto = c[cont].idProduto;
        In.idNotaFiscal = idnotafiscal;
        In.quantidade = c[cont].quantidadeVendida;
        In.valorVenda = (c[cont].valorVenda * c[cont].quantidadeVendida);
        printf("\nId da Nota Item:%lu",In.id);
        printf("\nId do Produto:%lu",In.idProduto);
        printf("\nId da Nota Fiscal:%lu",In.idNotaFiscal);
        printf("\nId Quantidade:%u",In.quantidade);
        printf("\nValor de Venda:%f",In.valorVenda);
        fseek(arqitemnotafiscal,0,SEEK_END);
        fwrite(&In,sizeof(ItemNotaFiscal),1,arqitemnotafiscal);
    };

}
void alteraestoque(FILE *arq,carrinho ca[],int i){
    int cont,posicaoPro;
    unsigned long id;
    unsigned int quantidade,quantidade_2,resultado;
    produto pr;
    for(cont=0;cont<i;cont++){

        id = ca[cont].idProduto;
        posicaoPro = consultaProduto(arq,id);

        if(posicaoPro!=-1){
            quantidade=ca[cont].quantidadeVendida;
            fseek(arq,posicaoPro*sizeof(produto),SEEK_SET);
            fread(&pr,sizeof(produto),1,arq);
            quantidade_2 = pr.quantidadeEstoque;
            resultado = quantidade_2 - quantidade;
            pr.quantidadeEstoque = resultado;
            fseek(arq,posicaoPro*sizeof(produto),SEEK_SET);
            fwrite(&pr,sizeof(produto),1,arq);
            printf("\nProduto Alterado com Sucesso no estoque! Produto de posição %d no carrinho",cont + 1);
        }
        else
            printf("\nErro ao procurar o id do produto");

    };

}
