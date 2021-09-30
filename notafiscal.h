#ifndef NOTAFISCAL_H_INCLUDED
#define NOTAFISCAL_H_INCLUDED
typedef struct{
    unsigned long id,idCliente,idVendedor;
    char dataCompra[11];
    float ValorTotal;
}NotaFiscal;

int incrementoIDNotaFiscal(FILE *);
int ConsultaIDNotaFiscal(FILE *,unsigned long);
int Consultadatacompra(FILE *,char*);
void gerarNotaFiscal(FILE *,unsigned long, unsigned long,unsigned long*,float);




#endif // NOTAFISCAL_H_INCLUDED
