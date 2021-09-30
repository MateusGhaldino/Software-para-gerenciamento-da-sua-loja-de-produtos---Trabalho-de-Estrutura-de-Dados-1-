#ifndef ITEMNOTAFISCAL_H_INCLUDED
#define ITEMNOTAFISCAL_H_INCLUDED
typedef struct{
    unsigned long id,idNotaFiscal,idProduto;
    float valorVenda;
    unsigned int quantidade;
}ItemNotaFiscal;

int incrementoIDItemNotaFiscal(FILE *);




#endif // ITEMNOTAFISCAL_H_INCLUDED
