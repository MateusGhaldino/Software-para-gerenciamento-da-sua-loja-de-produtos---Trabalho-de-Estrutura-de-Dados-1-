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
int incrementoIDProdutos(FILE *a){
    produto pr;
    unsigned long maiorid, id;
    id=1;
    maiorid=1;
    fseek(a,0,SEEK_SET);
    while(fread(&pr,sizeof(produto),1,a)==1){
          if(pr.id>=maiorid){
             id++;
             maiorid=id;
          }
          else
            return id;
       };
    return id;
}

int consultaProduto(FILE *arq, unsigned long id){
    produto pr;
    int posicao=0;

    fseek(arq,0,SEEK_SET);
    while(fread(&pr,sizeof(produto),1,arq)==1){
        if(pr.id==id){
            return posicao;
        }
        else{
            posicao++;
        };
       };

    return -1;
}

int consultaPreco(FILE *arq,unsigned long id){
    produto pr;
    int posicao=0;
    fseek(arq,0,SEEK_SET);
    while(fread(&pr,sizeof(produto),1,arq)==1){
        if(pr.id==id){
            return pr.precoUnitario;
        }
        else
            posicao++;
    }
    return -1;
}
int consultaEstoqueProduto(FILE *arq,int posicao,unsigned int estoque){
    produto pr;
    fseek(arq,posicao*sizeof(produto),SEEK_SET);
    fread(&pr,sizeof(produto),1,arq);

        if(estoque<=pr.quantidadeEstoque){
            //Retorna 1 quando a quantidade é suficiente para a venda;
            return 1;
        }
        else{
            //Retorna -1 quando a quantidade é insuficiente para a venda;
            return -1;
        };
}

void cadastroProdutos(FILE *arq){
    int sair;
    unsigned long iden;
    produto pe;
    float preco;
    do{
        printf("\nGerando ID...");

        iden =incrementoIDProdutos(arq);
        pe.id=iden;
        printf("\nID gerada com sucesso!!");
        printf("\nID: %lu",pe.id);
        printf("\nPronto para seguir com o cadastro do produto!!");

        printf("\nForneça o nome do produto:");
        lestring(pe.nome);

        //Atribuindo 0 a quantidade em estoque
        pe.quantidadeEstoque=0;
        do{
            printf("\nForneça agora o preço unitário desse produto:");
            scanf("%f",&preco);
            if(preco==0){
                printf("\nPreço Unitário inválido!!");
                sair=0;
            }
            else{
                pe.precoUnitario = preco;
                sair=1;
            };
        }while(sair!=1);

        printf("\nProduto salvo com sucesso!!");
        printf("\nID:%lu",pe.id);
        printf("\nNome do Produto:%s",pe.nome);
        printf("\nQuantidade em estoque = %u",pe.quantidadeEstoque);
        printf("\nPreço Unitário desse produto:%f",pe.precoUnitario);
        fseek(arq,0,SEEK_END);
        fwrite(&pe,sizeof(produto),1,arq);
        printf("\nDeseja Sair? \n1 - Sim \n2 - Não: ");
        scanf("%d",&sair);
    }while(sair!=1);
}
