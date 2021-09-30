#ifndef NOTACOMPRA_H_INCLUDED
#define NOTACOMPRA_H_INCLUDED
typedef struct{
    unsigned long id,idFornecedor;
    char dataCompra[11];
    float valorTotal;
}NotaCompra;

int incrementoIDNotaCompra(FILE *);
int consultaIdNotaCompra(FILE *,unsigned long);
void gerarNotaCompra(FILE *,unsigned long,unsigned long*,float);



#endif // NOTACOMPRA_H_INCLUDED
