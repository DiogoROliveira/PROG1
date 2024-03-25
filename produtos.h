#ifndef _PRODUTO
#define _PRODUTO

#include "libs.h"
#include "datatypes.h"

int addProduto(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP, PRODUTO NewInfo); // done
int getDataProd(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP);                 // done
void listarAlf(ELEM_PRODUTO *fim_listaP);                                                 // done
void listarCat(ELEM_PRODUTO *inicio_listaP);                                              // done
void listarCod(ELEM_PRODUTO *inicio_listaP);                                              // done
void removeProduto(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP);              // done
void loadProdutos(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP);               // done
int saveProdutos(ELEM_PRODUTO *inicio_listaP);                                            // done
void alterarProd(ELEM_PRODUTO *inicio_listaP);                                            // done
float valorStock(ELEM_PRODUTO *inicio_listaP);                                            // done
void listarExp(ELEM_PRODUTO *inicio_listaP);                                              // done
void criarRelatorio(ELEM_PRODUTO *inicio_listaP);                                         // done
void limparProdutos(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP);

#endif