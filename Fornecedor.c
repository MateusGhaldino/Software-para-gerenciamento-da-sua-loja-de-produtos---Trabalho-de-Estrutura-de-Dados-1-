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

int pesquisaidFornecedor(FILE *arq,unsigned long id){
    int posicao=0;
    fornecedor fe;

       /*posicionando no início do arquivo*/
       fseek(arq,0,SEEK_SET);

       while(fread(&fe,sizeof(fornecedor),1,arq)==1){
          if(fe.id==id)
             return posicao;

          else
             posicao++;
       }
       return -1;

}
int pesquisaCNPJFornecedor(FILE *arq,char *cnpj){
    fornecedor fe;
    int posicao=0;

    fseek(arq,0,SEEK_SET);
    while(fread(&fe,sizeof(fornecedor),1,arq)==1){
        if(strcmp(fe.CNPJ,cnpj)==0){
            return posicao;
        }else
            posicao++;
    }
    return -1;
}

int pesquisaPrefixoFornecedor(FILE *arq,char *prefix){
    fornecedor fe;
    int posicao=0;

    fseek(arq,0,SEEK_SET);

    while(fread(&fe,sizeof(fornecedor),1,arq)==1){
        if(strncmp(fe.nome,prefix,strlen(prefix))==0){
            return posicao;
        }else
            posicao++;
    }
    return -1;

}

int pesquisaNomeFornecedor(FILE *arq,char *nome){
    fornecedor fe;
    int posicao=0;

    fseek(arq,0,SEEK_SET);
    while(fread(&fe,sizeof(fornecedor),1,arq)==1){
        if(strcmp(fe.nome,nome)==0){
            return posicao;
        }else
            posicao++;
    }
    return -1;
}

int incrementoIDFornecedor(FILE *a){

    unsigned long maiorid, id;
    fornecedor fe;
    id =1;
    maiorid=1;
    fseek(a,0,SEEK_SET);
    while(fread(&fe,sizeof(fornecedor),1,a)==1){

          if(fe.id>=maiorid){
             id++;
             maiorid=id;
          }
          else
            return id;
       }
    return id;
}
void cadastroFornecedor(FILE *arq){
    int sair,posicao;
    unsigned long iden;
    fornecedor fe;
    char cnpj[15],email[50],nome[100];

        do{
            printf("\nGerando ID...");
            iden =incrementoIDFornecedor(arq);
            fe.id=iden;
            setbuf(stdin,NULL);
            printf("\nID gerada com sucesso!!");
            printf("\nID: %lu",fe.id);
            printf("\nPronto para seguir com o cadastro do Fornecedor!!");
            do{
                printf("\nForneça o nome do Fornecedor:");
                lestring(nome);
                posicao = pesquisaNomeFornecedor(arq,nome);
                if(posicao==-1){
                    strcpy(fe.nome,nome);
                    sair=1;
                }
                else{
                    printf("\nNome digitado já está cadastrado!!");
                    sair=0;
                };
            }while(sair!=1);

            //Transformando o testo para maiúsculo;

                do{
                    printf("\nForneça o CNPJ do Fornecedor:");
                    lestring(cnpj);
                     if(pesquisaCNPJFornecedor(arq,cnpj)==-1){
                        strcpy(fe.CNPJ,cnpj);
                        sair=1;
                        printf("\nCNPJ Válido e cadastrado com sucesso!!");
                    }
                    else{
                        printf("\nCNPJ já Cadastrado!!!");
                        sair=0;
                    };

                    }while(sair!=1);

                    do{
                        printf("\nForneça o email do fornecedor:");
                        lestring(email);

                        if(validaemail(email)==1){

                                strcpy(fe.email,email);
                                printf("\nEmail válido e cadastrado com sucesso!!!!");
                                sair=1;
                        }
                        else{
                            sair=0;
                            printf("\nE-mail inválido!!");
                        }
                    }while(sair!=1);
                    printf("\nExemplo:11-40028922");
                    printf("\nForneça o número de telefone do fornecedor:");
                    lestring(fe.telefone);

                    printf("\nid:%lu",fe.id);
                    printf("\nNome:%s",fe.nome);
                    printf("\nCNPJ:%s",fe.CNPJ);
                    printf("\nE-mail:%s",fe.email);
                    printf("\nNúmero de telefone: %s",fe.telefone);
                    fseek(arq,0,SEEK_END);
                    fwrite(&fe,sizeof(fornecedor),1,arq);

            printf("\nDeseja Sair? \n1 - Sim \n2 - Não: ");
            scanf("%d",&sair);

        }while(sair!=1);

}
void alterarFornecedor(FILE *arq){
    int sair,posicao,pos;
    unsigned long id;
    fornecedor fe;
    char CNPJ[12],email[50],nome[100];

    do{
        printf("\nForneça o ID do Fornecedor:");
        scanf("%lu",&id);
        posicao = pesquisaidFornecedor(arq,id);
        if(posicao!=-1){
            printf("\nProsseguindo com a alteração!!!");
            fe.id=id;
            do{
                printf("\nForneça o nome do Fornecedor:");
                lestring(nome);
                pos = pesquisaNomeFornecedor(arq,nome);
                if(pos==posicao||pos==-1){
                    strcpy(fe.nome,nome);
                    sair=1;
                }
                else{
                    printf("\nNome já cadastrado");
                    sair=0;
                };
            }while(sair!=1);
                do{
                    printf("\nForneça o CNPJ do Fornecedor:");
                    lestring(CNPJ);
                     if(pesquisaCNPJFornecedor(arq,CNPJ)==-1){
                        strcpy(fe.CNPJ,CNPJ);
                        sair=1;
                        printf("\nCNPJ Válido e cadastrado com sucesso!!");
                    }
                    else{
                        printf("\nCNPJ já Cadastrado!!!");
                        sair=0;
                    };

                }while(sair!=1);
            do{
                printf("\nForneça o email do fornecedor:");
                lestring(email);

                    if(validaemail(email)==1){
                            strcpy(fe.email,email);
                            //strupr(ve.email);
                            printf("\nÉ Válido!!!!");
                            sair=1;
                        }
                        else{
                            sair=0;
                            printf("\nNão è valido!!");
                        }
                    }while(sair!=1);

                    printf("\nForneça o número de telefone do vendedor:");
                    printf("\nExemplo:11-40028922");
                    lestring(fe.telefone);

                    fseek(arq,posicao*sizeof(fornecedor),SEEK_SET);
                    fwrite(&fe,sizeof(fornecedor),1,arq);
                    printf("\nAlterado com Sucesso");
        }
        else{
            printf("\nID não encontrada!!");
        };

        printf("\nDeseja Sair? \n1 - Sim \n2 - Não: ");
        scanf("%d",&sair);
    }while(sair!=1);

}
void consultaFornecedor(FILE *arq){
    unsigned long id;
    int sair,posicao,comando;
    fornecedor fe;
    char CNPJ[15],prefixo[100];

    //Posicionando o ponteiro no final do arquivo;
    fseek(arq,0,SEEK_END);
    if(ftell(arq)>0){
        do{
            printf("\nComo desejar fazer a sua consulta: \n1- Pelo ID \n2 - Pelo CPF \n3- Por um prefixo do nome do Fornecedor:");
            scanf("%d",&comando);
            setbuf(stdin,NULL);
            switch(comando){
            case 1:
                printf("\nForneça o ID do Fornecedor:");
                scanf("%lu",&id);
                posicao = pesquisaidFornecedor(arq,id);
                setbuf(stdin,NULL);
                if(posicao!=-1){
                    //posicionando o ponteiro no registro
                    fseek(arq,posicao*sizeof(fornecedor),SEEK_SET);
                    fread(&fe,sizeof(fornecedor),1,arq);
                    printf("\nDados do Cliente");
                    printf("\nNome:%s",fe.nome);
                    printf("\nID:%lu",fe.id);
                    printf("\nCNPJ:%s",fe.CNPJ);
                    printf("\nE-mail:%s",fe.email);
                    printf("\nTelefone:%s",fe.telefone);
                }
                else
                    printf("\n ID não cadastrado!");
                break;
            case 2:
                printf("\nForneça o CNPJ do Fornecedor:");
                fgets(CNPJ,12,stdin);
                posicao = pesquisaCNPJFornecedor(arq,CNPJ);

                if(posicao!=1){
                    //posicionando o ponteiro no registro
                    fseek(arq,posicao*sizeof(fornecedor),SEEK_SET);
                    fread(&fe,sizeof(fornecedor),1,arq);
                    printf("\nDados do Cliente");
                    printf("\nNome:%s",fe.nome);
                    printf("\nID:%lu",fe.id);
                    printf("\nCNPJ:%s",fe.CNPJ);
                    printf("\nE-mail:%s",fe.email);
                    printf("\nTelefone:%s",fe.email);
                }
                else
                    printf("\n CNPJ não cadastrado");
                break;
            case 3:
                printf("\nForneça o prefixo do nome do Fornecedor:");
                lestring(prefixo);
                posicao = pesquisaPrefixoFornecedor(arq,prefixo);
                if(posicao!= 1){

                    fseek(arq,posicao*sizeof(fornecedor),SEEK_SET);
                    fread(&fe,sizeof(vendedor),1,arq);
                    printf("\nDados do Cliente");
                    printf("\nNome:%s",fe.nome);
                    printf("\nID:%lu",fe.id);
                    printf("\nCNPJ:%s",fe.CNPJ);
                    printf("\nE-mail:%s",fe.email);
                    printf("\nTelefone:%s",fe.telefone);

                }
                else
                    printf("\nNenhum registro foi encontrado com esses caracteres!!");
                break;
            }

            printf("\nDeseja Sair? \n1 - Sim \n2 - Não: ");
            scanf("%d",&sair);
        }while(sair!=1);

    }
    else{
        printf("\nNão há fornecedores registrados!!");
    }
}
void listarFornecedor(FILE *arq){
    fornecedor fe;
    fseek(arq,0,SEEK_SET);
    printf("\nDados dos vendedores");
    while(fread(&fe,sizeof(fornecedor),1,arq)){
        printf("\n--------------------");
        printf("\nNome:%s",fe.nome);
        printf("\nID:%lu",fe.id);
        printf("\nCNPJ:%s",fe.CNPJ);
        printf("\nE-mail:%s",fe.email);
        printf("\nTelefone:%s",fe.telefone);
    }
}
