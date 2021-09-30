#ifndef COMPRAFORNECEDOR_H_INCLUDED
#define COMPRAFORNECEDOR_H_INCLUDED
typedef struct{
    unsigned long idProduto;
    unsigned int quantidade;
    float valorUnitario;
}Fornecedor_carrinho;

void alterarItem_Fornecedor(FILE *,Fornecedor_carrinho [],int *);
void excluirItem_Fornecedor(Fornecedor_carrinho [],int *);
int Consultacarrinho_Fornecedor(Fornecedor_carrinho [],unsigned long,int);
void compras_Fornecedor(FILE *,FILE *,FILE *,FILE *);
void gerar_ItemNota_fiscal_Compra_Fornecedor(FILE *,Fornecedor_carrinho[],int ,unsigned long);
void alteraestoqueForne(FILE *,Fornecedor_carrinho[],int);


#endif // COMPRAFORNECEDOR_H_INCLUDED
