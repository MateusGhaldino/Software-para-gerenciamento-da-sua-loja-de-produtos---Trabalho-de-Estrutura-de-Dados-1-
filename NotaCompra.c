#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
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

int incrementoIDNotaCompra(FILE *arq){
    unsigned long maiorid, id;
    NotaCompra ne;
    id =1;
    maiorid=1;
    fseek(arq,0,SEEK_SET);
    while(fread(&ne,sizeof(NotaCompra),1,arq)==1){

          if(ne.id>=maiorid){
             id++;
             maiorid=id;
          }
          else
            return id;
       }
    return id;

}

int consultaIdNotaCompra(FILE *arq,unsigned long id){
    int posicao=0;
    NotaCompra Nc;

    /*posicionando no início do arquivo*/
    fseek(arq,0,SEEK_SET);

    while(fread(&Nc,sizeof(NotaCompra),1,arq)==1){
        if(Nc.id==id)
            return posicao;
        else
            posicao++;
       }
       return -1;

}

void gerarNotaCompra(FILE *arq,unsigned long idFornecedor,unsigned long*idnotacompra,float total){
    NotaCompra nf;
    unsigned long id;
    int sair,dia,mes,ano,op;
    char data[11],date[11],datacompra[11];

    printf("\nGerando Nota Compra");
    id=incrementoIDNotaCompra(arq);
    nf.id = id;
    *idnotacompra=id;
    printf("\nID da nota: %lu",nf.id);
    nf.idFornecedor = idFornecedor;
    printf("\nId Fornecedor:%lu",nf.idFornecedor);
    DatadoSistemaOperacional(data);
    strcpy(nf.dataCompra,data);
    nf.valorTotal = total;
    printf("\nData da Venda:%s",data);
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
                            strcpy(nf.dataCompra,datacompra);
                            printf("\nA Data digitada foi:%s",nf.dataCompra);
                        };
            }while(op!=1);
            break;
        };
    }while(sair!=2);
    fseek(arq,0,SEEK_END);
    fwrite(&nf,sizeof(NotaCompra),1,arq);
    printf("\nNota Compra Gerada com sucesso!!");

}
