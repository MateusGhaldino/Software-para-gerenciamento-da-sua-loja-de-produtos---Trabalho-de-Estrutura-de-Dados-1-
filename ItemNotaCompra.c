#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include "cliente.h"
#include "menu.h"
#include "utilitarios.h"
#include "vendedor.h"
#include "Fornecedor.h"
#include "produto.h"
#include "compra.h"
#include "notafiscal.h"
#include "ItemNotaFiscal.h"
#include "CompraFornecedor.h"
#include "NotaCompra.h"
#include "ItemNotaCompra.h"
#include "HistoricoPreco.h"
#include "relatorios.h"
int incrementoIDItemNotaCompra(FILE *a){
    NotaCompra Nc;
    unsigned long maiorid, id;
    id=1;
    maiorid=1;
    fseek(a,0,SEEK_SET);
    while(fread(&Nc,sizeof(NotaCompra),1,a)==1){
          if(Nc.id>=maiorid){
             id++;
             maiorid=id;
          }
          else
            return id;
       }
    return id;
}
