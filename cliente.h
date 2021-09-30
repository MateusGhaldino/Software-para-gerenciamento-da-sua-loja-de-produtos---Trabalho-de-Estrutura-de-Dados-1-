#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct{
    unsigned long  id;
    char nome[100],cpf[12],email[50],telefone[15];
}cliente;

int pesquisaid(FILE *,unsigned long);
int pesquisaPrefixoCliente(FILE *,char *);
int pesquisaCpf(FILE *, char *);
int incrementoID(FILE *);
void cadastro(FILE *);
void alterar(FILE *);
void consulta(FILE *);
void listar(FILE *);



#endif // CLIENTE_H_INCLUDED
