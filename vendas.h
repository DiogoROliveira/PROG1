#ifndef _VENDA
#define _VENDA

#include "libs.h"
#include "datatypes.h"

int getDataVenda(ELEM_VENDAS **inicio_listaV, ELEM_VENDAS **fim_listaV, ELEM_CLIENT *inicio_listaC, ELEM_PRODUTO *inicio_listaP); // done
int addVenda(ELEM_VENDAS **inicio_listaV, ELEM_VENDAS **fim_listaV, VENDA temp);                                                  // done
int saveVendas(ELEM_VENDAS *inicio_listaV);                                                                                       // done
void loadVendas(ELEM_VENDAS **inicio_listaV, ELEM_VENDAS **fim_listaP);                                                           // done
void limparVendas(ELEM_VENDAS **inicio_listaV, ELEM_VENDAS **fim_listaV);                                                         // done
void relatorioDiario(ELEM_VENDAS *inicio_listaV, ELEM_PRODUTO *inicio_listaP);                                                    // done
void relatorioMensal(ELEM_VENDAS *inicio_listaV, ELEM_PRODUTO *inicio_listaP);                                                    // done
void relatorioAnual(ELEM_VENDAS *inicio_listaV, ELEM_PRODUTO *inicio_listaP);                                                     // done
#endif