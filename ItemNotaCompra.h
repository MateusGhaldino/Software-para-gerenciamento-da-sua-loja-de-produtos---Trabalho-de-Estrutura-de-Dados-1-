#ifndef ITEMNOTACOMPRA_H_INCLUDED
#define ITEMNOTACOMPRA_H_INCLUDED
typedef struct{
    unsigned long id,idProduto,idNotaCompra;
    unsigned int quantidade;
    float valorUnitario;
}ItemNotaCompra;


int incrementoIDItemNotaCompra(FILE *);



#endif // ITEMNOTACOMPRA_H_INCLUDED
