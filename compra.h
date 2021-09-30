#ifndef COMPRA_H_INCLUDED
#define COMPRA_H_INCLUDED
typedef struct{
    unsigned long idProduto;
    unsigned int quantidadeVendida;
    float valorVenda;
}carrinho;

void alterarItem(FILE *,carrinho [],int *);
void excluirItem(carrinho [],int *);
int Consultacarrinho(carrinho [],unsigned long,int);
int ConsultasenhaVendedor(FILE *,char *);
void compras(FILE *,FILE *,FILE *,FILE *, FILE *);
void gerar_ItemNota_fiscal(FILE *,carrinho[],int ,unsigned long);
void alteraestoque(FILE *,carrinho[],int);

#endif // COMPRA_H_INCLUDED
