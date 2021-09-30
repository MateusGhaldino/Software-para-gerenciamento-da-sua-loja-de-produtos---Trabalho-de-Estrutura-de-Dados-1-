#ifndef HISTORICOPRECO_H_INCLUDED
#define HISTORICOPRECO_H_INCLUDED
typedef struct{
    unsigned long idProduto;
    char dataAlteracao[11];
    float Valor;
}HistoricoPreco;

void AtualizarPreco(FILE *,FILE*);


#endif // HISTORICOPRECO_H_INCLUDED
