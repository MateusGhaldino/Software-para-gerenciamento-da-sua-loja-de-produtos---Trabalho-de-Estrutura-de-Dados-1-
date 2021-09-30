#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include "cliente.h"
#include "menu.h"
#include "abrearquivo.h"
#include "utilitarios.h"
#include "vendedor.h"
#include "Fornecedor.h"
#include "produto.h"
#include "notafiscal.h"
#include "ItemNotaFiscal.h"
#include "CompraFornecedor.h"
#include "NotaCompra.h"
#include "ItemNotaCompra.h"
#include "HistoricoPreco.h"
#include "relatorios.h"

int main(){
    setlocale(LC_ALL,"Portuguese");
    menuinicial();
    return 0;
}
