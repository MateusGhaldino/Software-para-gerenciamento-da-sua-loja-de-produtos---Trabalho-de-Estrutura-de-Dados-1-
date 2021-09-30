#ifndef VENDEDOR_H_INCLUDED
#define VENDEDOR_H_INCLUDED
typedef struct{
    unsigned long id;
    char Nome[100],cpf[12],email[50],telefone[15],password[20];
}vendedor;
int pesquisaidVendedores(FILE *,unsigned long);
int pesquisaCpfVendedores(FILE *,char *);
int pesquisaPrefixoVendedor(FILE *,char *);
int pesquisaEmailvendedores(FILE *,char *);
int incrementoIDVendedores(FILE *);
void cadastroVendedores(FILE *);
void alterarVendedores(FILE *);
void consultaVendedores(FILE *);
void listarVendedores(FILE *);

#endif // VENDEDOR_H_INCLUDED
