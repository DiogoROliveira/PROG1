#ifndef _CLIENTE
#define _CLIENTE

#include "libs.h"
#include "datatypes.h"

int addClient(ELEM_CLIENT **inicio_listaC, ELEM_CLIENT **fim_listaC, CLIENTE newInfo); // done
int getDataClient(ELEM_CLIENT **inicio_listaC, ELEM_CLIENT **fim_listaC);              // done
void listarClientAlf(ELEM_CLIENT *fim_listaC);                                         // done
void listarNIF(ELEM_CLIENT *inicio_listaC);                                            // done
void alterarClient(ELEM_CLIENT *inicio_listaC);                                        // done
void loadClients(ELEM_CLIENT **inicio_listaC, ELEM_CLIENT **fim_listaC);               // done
int saveClients(ELEM_CLIENT *inicio_listaC);                                           // done
void limparClients(ELEM_CLIENT **inicio_listaC, ELEM_CLIENT **fim_listaC);             // done

#endif