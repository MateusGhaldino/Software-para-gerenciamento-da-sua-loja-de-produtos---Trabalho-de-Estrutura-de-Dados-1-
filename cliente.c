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

int pesquisaid(FILE *arq,unsigned long mat){
   int posicao=0;
   cliente rf;

       /*posicionando no início do arquivo*/
       fseek(arq,0,SEEK_SET);

       while(fread(&rf,sizeof(cliente),1,arq)==1){
          if(rf.id==mat)
             return posicao;

          else
             posicao++;
       }
       return -1;
}


int pesquisaCpf(FILE *arq, char *cpf){
    cliente ci;
    int posicao=0;

    fseek(arq,0,SEEK_SET);
    while(fread(&ci,sizeof(cliente),1,arq)==1){
        if(strcmp(ci.cpf,cpf)==0){
            return posicao;
        }else
            posicao++;
    }
    return -1;
}


int pesquisaPrefixoCliente(FILE *arq,char *prefix){
    cliente cl;
    int posicao=0;

    fseek(arq,0,SEEK_SET);

    while(fread(&cl,sizeof(cliente),1,arq)==1){
        if(strncmp(cl.nome,prefix,strlen(prefix))==0){
            return posicao;
        }else
            posicao++;
    }
    return -1;

}
int incrementoID(FILE *a){
    unsigned long maiorid, id;
    cliente cl;
    id =1;
    maiorid=1;
    fseek(a,0,SEEK_SET);
    while(fread(&cl,sizeof(cliente),1,a)==1){

          if(cl.id>=maiorid){
             id++;
             maiorid=id;
          }
          else
            return id;
       }
    return id;
}
void cadastro(FILE *arq){
    int sair;
    unsigned long iden;
    cliente cl;
    char cpf[12],email[50];

        do{
            printf("\nGerando ID...");
            iden =incrementoID(arq);
            cl.id=iden;
            setbuf(stdin,NULL);
            printf("\nID gerada com sucesso");
            printf("\nID %lu",cl.id);
            printf("\nPronto para seguir com o cadastro do cliente!!");
            printf("\nForneça o nome do cliente:");
            lestring(cl.nome);
            //Transformando o testo para maiúsculo;
            strupr(cl.nome);
                do{
                    printf("\nForneça o cpf do cliente:");
                    lestring(cpf);
                    if(validarCPF(cpf)==0){
                        printf("\nCPF inválido\n\nPor favor digite o CPF novamente");
                        sair=2;
                    }
                    else{
                        if(pesquisaCpf(arq,cpf)==-1){
                            strcpy(cl.cpf,cpf);
                            sair=1;
                            printf("\nCPF Válido e cadastrado com sucesso!!");
                        }
                        else{
                            printf("\nCPF já Cadastrado!!!");
                            sair=0;
                        };
                        }
                    }while(sair!=1);

                    do{
                        printf("\nForneça o email do cliente:");
                        lestring(email);

                        if(validaemail(email)==1){
                            strcpy(cl.email,email);
                            //strupr(cl.email);
                            printf("\nÉ Válido!!!!");
                            sair=1;
                        }
                        else{
                            sair=0;
                            printf("\nNão è valido!!");
                        }
                    }while(sair!=1);
                    printf("\nExemplo:11-40028922");
                    printf("\nForneça o número de telefone do cliente:");
                    lestring(cl.telefone);

                    printf("\nid:%lu",cl.id);
                    printf("\nNome:%s",cl.nome);
                    printf("\nCPF:%s",cl.cpf);
                    printf("\nE-mail:%s",cl.email);
                    printf("\nNúmero de telefone: %s",cl.telefone);
                    fseek(arq,0,SEEK_END);
                    fwrite(&cl,sizeof(cliente),1,arq);

            printf("\nDeseja Sair? \n1 - Sim \n2 - Não: ");
            scanf("%d",&sair);

        }while(sair!=1);

}

void alterar(FILE *arq){
    int sair,posicao;
    unsigned long id;
    cliente cl;
    char cpf[12],email[50];

    do{
        printf("\nForneça o ID do cliente:");
        scanf("%lu",&id);
        posicao = pesquisaid(arq,id);
        if(posicao!=-1){
            printf("\nProsseguindo com a alteração!!!");
            cl.id=id;
            printf("\nForneça o nome do cliente:");
            lestring(cl.nome);

            do{
                printf("\nForneça o cpf do cliente:");
                lestring(cpf);
                if(validarCPF(cpf)==0){
                    printf("\nCPF inválido\n\nPor favor digite o CPF novamente");
                    sair=2;
                }
                else{
                    strcpy(cl.cpf,cpf);
                    sair=1;
                    printf("\nCPF Válido e alterado com sucesso!");
                };
            }while(sair!=1);

            do{
                printf("\nForneça o email do cliente:");
                lestring(email);

                    if(validaemail(email)==1){
                            strcpy(cl.email,email);
                            //strupr(cl.email);
                            printf("\nÉ Válido!!!!");
                            sair=1;
                        }
                        else{
                            sair=0;
                            printf("\nNão è valido!!");
                        }
                    }while(sair!=1);

                    printf("\nForneça o número de telefone do cliente:");
                    printf("\nExemplo:11-40028922");
                    lestring(cl.telefone);
                    fseek(arq,posicao*sizeof(cliente),SEEK_SET);
                    fwrite(&cl,sizeof(cliente),1,arq);
                    printf("\nAlterado com Sucesso");
        }
        else{
            printf("\nID não encontrada!!");
        };

        printf("\nDeseja Sair? \n1 - Sim \n2 - Não: ");
        scanf("%d",&sair);
    }while(sair!=1);
}
void consulta(FILE *arq){
    unsigned long id;
    int sair,posicao,comando;
    cliente cl;
    char cpf[12],prefixo[100];
    //Posicionando o ponteiro no final do arquivo;
    fseek(arq,0,SEEK_END);
    if(ftell(arq)>0){
        do{
            printf("\nComo desejar fazer a sua consulta: \n1- Pelo ID \n2 - Pelo CPF \n3- Por um prefixo do nome do cliente:");
            scanf("%d",&comando);
            setbuf(stdin,NULL);
            switch(comando){
            case 1:
                printf("\nForneça o ID do cliente:");
                scanf("%lu",&id);
                posicao = pesquisaid(arq,id);
                setbuf(stdin,NULL);
                if(posicao!=-1){
                    //posicionando o ponteiro no registro
                    fseek(arq,posicao*sizeof(cliente),SEEK_SET);
                    fread(&cl,sizeof(cliente),1,arq);
                    printf("\nDados do Cliente");
                    printf("\nNome:%s",cl.nome);
                    printf("\nID:%lu",cl.id);
                    printf("\nCPF:%s",cl.cpf);
                    printf("\nE-mail:%s",cl.email);
                    printf("\nTelefone:%s",cl.telefone);
                }
                else
                    printf("\n ID não cadastrado!");
                break;
            case 2:
                printf("\nForneça o CPF do cliente:");
                fgets(cpf,12,stdin);
                posicao = pesquisaCpf(arq,cpf);

                if(posicao!=1){

                    //posicionando o ponteiro no registro
                    fseek(arq,posicao*sizeof(cliente),SEEK_SET);
                    fread(&cl,sizeof(cliente),1,arq);
                    printf("\nDados do Cliente");
                    printf("\nNome:%s",cl.nome);
                    printf("\nID:%lu",cl.id);
                    printf("\nCPF:%s",cl.cpf);
                    printf("\nE-mail:%s",cl.email);
                    printf("\nTelefone:%s",cl.telefone);
                }
                else
                    printf("\n CPF não cadastrado");
                break;

            case 3:
                printf("Forneça o prefixo do Cliente que você deseja consultar:");
                lestring(prefixo);
                pesquisaPrefixoCliente(arq,prefixo);
                posicao = pesquisaPrefixoCliente(arq,prefixo);

                if(posicao!=-1){

                    fseek(arq,posicao*sizeof(cliente),SEEK_SET);
                    fread(&cl,sizeof(cliente),1,arq);
                    printf("\nDados do Cliente");
                    printf("\nNome:%s",cl.nome);
                    printf("\nID:%lu",cl.id);
                    printf("\nCPF:%s",cl.cpf);
                    printf("\nE-mail:%s",cl.email);
                    printf("\nTelefone:%s",cl.telefone);

                }
                else{
                    printf("\nNenhum registro foi encontrado com esses caracteres!!");
                }
                break;
            }

            printf("\nDeseja Sair? \n1 - Sim \n2 - Não: ");
            scanf("%d",&sair);
        }while(sair!=1);

    }
    else{
        printf("\nNão há clientes registrados!!");
    }

}
void listar(FILE *a){
    cliente cl;

    fseek(a,0,SEEK_SET);
    printf("\nDados dos clientes");
    while(fread(&cl,sizeof(cliente),1,a)){
        printf("\n--------------------");
        printf("\nNome:%s",cl.nome);
        printf("\nID:%lu",cl.id);
        printf("\nCPF:%s",cl.cpf);
        printf("\nE-mail:%s",cl.email);
        printf("\nTelefone:%s",cl.telefone);
    }
}

