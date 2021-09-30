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

int incrementoIDNotaFiscal(FILE *a){
    NotaFiscal pr;
    unsigned long maiorid, id;
    id=1;
    maiorid=1;
    fseek(a,0,SEEK_SET);
    while(fread(&pr,sizeof(NotaFiscal),1,a)==1){
          if(pr.id>=maiorid){
             id++;
             maiorid=id;
          }
          else
            return id;
       }
    return id;
}
int ConsultaIDNotaFiscal(FILE *arq,unsigned long id){
    int posicao=0;
    NotaFiscal Nf;

    /*posicionando no início do arquivo*/
    fseek(arq,0,SEEK_SET);

    while(fread(&Nf,sizeof(NotaFiscal),1,arq)==1){
        if(Nf.id==id)
            return posicao;
        else
            posicao++;
       }
       return -1;
}

int Consultadatacompra(FILE *arq,char *data){
    NotaFiscal Nf;
    int posicao=0;
    fseek(arq,0,SEEK_SET);
    while(fread(&Nf,sizeof(NotaFiscal),1,arq)==1){
        if(strcmp(Nf.dataCompra,data)==0){
            return posicao;
        }else
            posicao++;
    }
    return -1;
}
int ConsultacompraVendedor(FILE *arq,unsigned long id){
    NotaFiscal Nf;
    int posicao=0;
    fseek(arq,0,SEEK_SET);
    while(fread(&Nf,sizeof(NotaFiscal),1,arq)==1){
        if(Nf.idVendedor==id){
            return posicao;
        }
        else
            posicao++;
    }
    return -1;
}
void gerarNotaFiscal(FILE *arqnotafiscal,unsigned long idcliente, unsigned long idvendedor,unsigned long *idnotafiscal,float valor){
    NotaFiscal nf;
    unsigned long id;
    int sair,dia,mes,ano,op;
    char data[11],date[11],datacompra[11];

    printf("\nGerando Nota fiscal");
    id=incrementoIDNotaFiscal(arqnotafiscal);
    nf.id=id;
    *idnotafiscal=id;
    printf("\nID da nota: %lu",nf.id);
    nf.ValorTotal=valor;
    nf.idCliente = idcliente;
    printf("\nId cliente:%lu",nf.idCliente);
    nf.idVendedor = idvendedor;
    printf("\nId Vendendor:%lu",nf.idVendedor);
    DatadoSistemaOperacional(data);
    strcpy(nf.dataCompra,data);
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
                            printf("\nData alterado  com sucesso!!");
                            strcpy(nf.dataCompra,datacompra);
                            printf("\nA Data digitada foi:%s",nf.dataCompra);
                        };
            }while(op!=1);
            break;
        };
    }while(sair!=2);
    fseek(arqnotafiscal,0,SEEK_END);
    fwrite(&nf,sizeof(NotaFiscal),1,arqnotafiscal);
    printf("\nNota Fiscal Gerada com sucesso!!");


}
