#ifndef FORNECEDOR_H_INCLUDED
#define FORNECEDOR_H_INCLUDED
typedef struct{
    unsigned long id;
    char CNPJ[15],nome[100],email[50],telefone[15];
}fornecedor;
int pesquisaidFornecedor(FILE *,unsigned long);
//int pesquisaCNPJFornecedor(FILE *,char *);
int pesquisaPrefixoFornecedor(FILE *,char *);

int pesquisaNomeFornecedor(FILE *,char *);
int incrementoIDFornecedor(FILE *);
void cadastroFornecedor(FILE *);
void alterarFornecedor(FILE *);
void consultaFornecedor(FILE *);
void listarFornecedor(FILE *);

#endif // FORNECEDOR_H_INCLUDED
