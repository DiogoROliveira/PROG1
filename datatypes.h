#ifndef _DATATYPES
#define _DATATYPES

typedef struct
{
    int ano;
    int mes;
    int dia;

} VALIDADE;

typedef struct produto
{
    int codigoProduto;
    char nomeProduto[64];
    char categoria[64];
    VALIDADE dt_validade;
    int qtdProduto;
    int qtdMin;
    float precoCompra;
    float precoVenda;
} PRODUTO;

typedef struct elem_Produto
{
    PRODUTO infoP;
    struct elem_Produto *seguinte;
    struct elem_Produto *anterior;
} ELEM_PRODUTO;

typedef struct vendas
{
    float precoVenda;
    char nomeProd[50];
    int idCliente;
    int idProduto;
    int qtdVendida;
    VALIDADE dtVenda;
    float receitaVenda;
} VENDA;

typedef struct elem_Vendas
{
    VENDA infoV;
    struct elem_Vendas *anterior;
    struct elem_Vendas *seguinte;
} ELEM_VENDAS;

typedef struct client
{
    int codigoClient;
    char nome[50];
    char morada[200];
    long int NIF;
    long int telefone;
    char email[50];
} CLIENTE;

typedef struct elem_client
{
    CLIENTE infoC;
    struct elem_client *anterior;
    struct elem_client *seguinte;
} ELEM_CLIENT;

#endif