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

int consultaHistorico(FILE *arq,char *date,int posicao){

    HistoricoPreco Hp;
    fseek(arq,posicao*sizeof(HistoricoPreco),SEEK_SET);
    fread(&Hp,sizeof(HistoricoPreco),1,arq);

    if(strcmp(Hp.dataAlteracao,date)==0){
            return posicao;
    }
    else{
        return -1;
    };

}

int ConsultaHistorioPreco(FILE *arq,char *data, unsigned long IdProduto){
    HistoricoPreco Hp;
    int posicao = 0,cont;
    fseek(arq,0,SEEK_SET);
    while(fread(&Hp,sizeof(HistoricoPreco),1,arq)==1){
        if(Hp.idProduto==IdProduto){
            if(strcmp(Hp.dataAlteracao,data)==0){
                return posicao;
            }
            else
                cont++;
        }
        else
            posicao++;

    }
    return -1;
}

void AtualizarPreco(FILE *arqprodutos,FILE *arqHistoricoPreco){
    unsigned long id;
    int posicao,Resulta,sair,op,dia,mes,ano,comando,idsize,i;
    float porcentagem,pe,total;
    char data[11],date[11],dete[11],datacompra[11];
    HistoricoPreco Hp;
    produto pr;
    do{
        printf("\nComo desejar atualizar o preço:");
        printf("\n1 - Atualizar de apenas um item");
        printf("\n2 - Atualizar de todos os itens cadastrados");
        printf("\n3 - Sair");
        printf("\nO que deseja fazer?:");
        scanf("%d",&comando);
        switch(comando){

        case 1:
            printf("\nForneça o ID do produto que você deseja atualizar o preço:");
            scanf("%lu",&id);
            DatadoSistemaOperacional(dete);

            posicao = consultaProduto(arqprodutos,id);

            if(posicao!=-1){
                Resulta = consultaHistorico(arqHistoricoPreco,dete,posicao);
                if(Resulta==-1){
                printf("\nSeguindo com a atualização do Preço do Produto.");
                fseek(arqprodutos,posicao*sizeof(produto),SEEK_SET);
                fread(&pr,sizeof(produto),1,arqprodutos);
                printf("\nO Produto %s \nPreço:%f",pr.nome,pr.precoUnitario);
                pe = pr.precoUnitario;
                printf("\nForneça aqui a porcentagem que aumentar no produto:");
                scanf("%f",&porcentagem);
                porcentagem = porcentagem / 100;
                total = (pe * porcentagem) + pe;
                pr.precoUnitario = total;
                /*Atualizando o Preço do Produto no arquivo*/
                fseek(arqprodutos,posicao*sizeof(produto),SEEK_SET);
                fwrite(&pr,sizeof(produto),1,arqprodutos);

                printf("\nProduto atualizado com sucesso");
                printf("\nPreço atualizado %f",total);

                DatadoSistemaOperacional(data);
                strcpy(Hp.dataAlteracao,data);
                Hp.idProduto = id;
                Hp.Valor = total;

                printf("\nData da alteração:%s",Hp.dataAlteracao);
                do{
                    printf("\nDeseja alterar a data da Compra?? \n1 - Sim \n2 - Não");
                    scanf("%d",&sair);
                    switch(sair){
                    case 1:
                        do{
                            printf("\nInforme a data que deseja colocar na compra(ex: 05/02/2021):");
                                    lestring(datacompra);
                                    date[0] = datacompra[0];
                                    date[1] = datacompra[1];
                                    date[2] = '\0';
                                    dia = atoi(date);
                                    date[0] = datacompra[3];
                                    date[1] = datacompra[4];
                                    date[2] = '\0';
                                    mes = atoi(date);
                                    date[0] = datacompra[6];
                                    date[1] = datacompra[7];
                                    date[2] = datacompra[8];
                                    date[3] = datacompra[9];
                                    date[4] = '\0';
                                    ano = atoi(date);
                                    if(valida_data(dia,mes,ano)==0){
                                        op=0;
                                        printf("Data inválida\n");
                                    }
                                    else{
                                        op=1;
                                        sair=2;
                                        printf("\nData alterado com sucesso!!");
                                        strcpy(Hp.dataAlteracao,datacompra);
                                        printf("\nA Data digitada foi:%s",Hp.dataAlteracao);
                                        };
                        }while(op!=1);
                        break;
                        };
                    }while(sair!=2);

                fseek(arqHistoricoPreco,0,SEEK_END);
                fwrite(&Hp,sizeof(HistoricoPreco),1,arqHistoricoPreco);
                printf("\nHistórico gerado com sucesso!!");
                }
                else{
                    printf("\nNão é possível atualizar o Preço de um produto mais de uma vez por dia!!");
                };
            }
            else{
              printf("\nID do produto não encontrado!!!");
            };
            break;
        case 2:
            printf("\nForneça a porcentagem:");
            scanf("%f",&porcentagem);
            porcentagem = porcentagem / 100;

            DatadoSistemaOperacional(date);
            strcpy(Hp.dataAlteracao,date);

            idsize = incrementoIDProdutos(arqprodutos);
            printf("Número de Produtos que sofreram a alteração: %d",idsize - 1);

            fseek(arqprodutos,0,SEEK_SET);
            fread(&pr,sizeof(produto),1,arqprodutos);

            for( i = 0 ; i < idsize; i++){
                posicao = consultaProduto(arqprodutos,i);

                Hp.idProduto = i;

                fseek(arqprodutos,posicao*sizeof(produto),SEEK_SET);
                fread(&pr,sizeof(produto),1,arqprodutos);

                printf("\nID do produto sendo alterado: %lu",pr.id);
                printf("\nID Preço antes da alteração: %f",pr.precoUnitario);
                pe = pr.precoUnitario;
                total = (pe * porcentagem) + pe;
                pr.precoUnitario = total;

                printf("\n--------Alteração----------");
                printf("\nNovo Preço:%f",pr.precoUnitario);
                /*Alterando no arquivo do Produto*/
                fseek(arqprodutos,posicao*sizeof(produto),SEEK_SET);
                fwrite(&pr,sizeof(produto),1,arqprodutos);

                /*Gerando um registro no arquivo HistoricoPreco*/

                Hp.Valor = total;
                strcpy(Hp.dataAlteracao,date);
                printf("\nData: %s",Hp.dataAlteracao);
                fseek(arqHistoricoPreco,0,SEEK_END);
                fwrite(&Hp,sizeof(HistoricoPreco),1,arqHistoricoPreco);
                printf("\nHistórico gerado com sucesso!!");
                printf("\nProduto de ID %d",i);
            }
            break;
        };
    }while(comando!=3);
}


