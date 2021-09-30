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
        printf("\nComo desejar atualizar o pre�o:");
        printf("\n1 - Atualizar de apenas um item");
        printf("\n2 - Atualizar de todos os itens cadastrados");
        printf("\n3 - Sair");
        printf("\nO que deseja fazer?:");
        scanf("%d",&comando);
        switch(comando){

        case 1:
            printf("\nForne�a o ID do produto que voc� deseja atualizar o pre�o:");
            scanf("%lu",&id);
            DatadoSistemaOperacional(dete);

            posicao = consultaProduto(arqprodutos,id);

            if(posicao!=-1){
                Resulta = consultaHistorico(arqHistoricoPreco,dete,posicao);
                if(Resulta==-1){
                printf("\nSeguindo com a atualiza��o do Pre�o do Produto.");
                fseek(arqprodutos,posicao*sizeof(produto),SEEK_SET);
                fread(&pr,sizeof(produto),1,arqprodutos);
                printf("\nO Produto %s \nPre�o:%f",pr.nome,pr.precoUnitario);
                pe = pr.precoUnitario;
                printf("\nForne�a aqui a porcentagem que aumentar no produto:");
                scanf("%f",&porcentagem);
                porcentagem = porcentagem / 100;
                total = (pe * porcentagem) + pe;
                pr.precoUnitario = total;
                /*Atualizando o Pre�o do Produto no arquivo*/
                fseek(arqprodutos,posicao*sizeof(produto),SEEK_SET);
                fwrite(&pr,sizeof(produto),1,arqprodutos);

                printf("\nProduto atualizado com sucesso");
                printf("\nPre�o atualizado %f",total);

                DatadoSistemaOperacional(data);
                strcpy(Hp.dataAlteracao,data);
                Hp.idProduto = id;
                Hp.Valor = total;

                printf("\nData da altera��o:%s",Hp.dataAlteracao);
                do{
                    printf("\nDeseja alterar a data da Compra?? \n1 - Sim \n2 - N�o");
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
                                        printf("Data inv�lida\n");
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
                printf("\nHist�rico gerado com sucesso!!");
                }
                else{
                    printf("\nN�o � poss�vel atualizar o Pre�o de um produto mais de uma vez por dia!!");
                };
            }
            else{
              printf("\nID do produto n�o encontrado!!!");
            };
            break;
        case 2:
            printf("\nForne�a a porcentagem:");
            scanf("%f",&porcentagem);
            porcentagem = porcentagem / 100;

            DatadoSistemaOperacional(date);
            strcpy(Hp.dataAlteracao,date);

            idsize = incrementoIDProdutos(arqprodutos);
            printf("N�mero de Produtos que sofreram a altera��o: %d",idsize - 1);

            fseek(arqprodutos,0,SEEK_SET);
            fread(&pr,sizeof(produto),1,arqprodutos);

            for( i = 0 ; i < idsize; i++){
                posicao = consultaProduto(arqprodutos,i);

                Hp.idProduto = i;

                fseek(arqprodutos,posicao*sizeof(produto),SEEK_SET);
                fread(&pr,sizeof(produto),1,arqprodutos);

                printf("\nID do produto sendo alterado: %lu",pr.id);
                printf("\nID Pre�o antes da altera��o: %f",pr.precoUnitario);
                pe = pr.precoUnitario;
                total = (pe * porcentagem) + pe;
                pr.precoUnitario = total;

                printf("\n--------Altera��o----------");
                printf("\nNovo Pre�o:%f",pr.precoUnitario);
                /*Alterando no arquivo do Produto*/
                fseek(arqprodutos,posicao*sizeof(produto),SEEK_SET);
                fwrite(&pr,sizeof(produto),1,arqprodutos);

                /*Gerando um registro no arquivo HistoricoPreco*/

                Hp.Valor = total;
                strcpy(Hp.dataAlteracao,date);
                printf("\nData: %s",Hp.dataAlteracao);
                fseek(arqHistoricoPreco,0,SEEK_END);
                fwrite(&Hp,sizeof(HistoricoPreco),1,arqHistoricoPreco);
                printf("\nHist�rico gerado com sucesso!!");
                printf("\nProduto de ID %d",i);
            }
            break;
        };
    }while(comando!=3);
}


