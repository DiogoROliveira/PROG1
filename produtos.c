#include "libs.h"
#include "datatypes.h"

int getDataProd(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP)
{
    PRODUTO produto;
    int res = 0;
    printf("Inserir produto:\n\n");

    printf("Codigo do produto: ");
    fflush(stdin);
    scanf("%d", &produto.codigoProduto);

    printf("Nome do produto: ");
    fflush(stdin);
    gets(produto.nomeProduto);

    printf("Categoria do produto: ");
    fflush(stdin);
    gets(produto.categoria);

    printf("Data de validade: \n");

    printf("Dia: ");
    fflush(stdin);
    scanf("%d", &produto.dt_validade.dia);

    printf("Mes: ");
    fflush(stdin);
    scanf("%d", &produto.dt_validade.mes);

    printf("Ano: ");
    fflush(stdin);
    scanf("%d", &produto.dt_validade.ano);

    printf("Quantidade: ");
    fflush(stdin);
    scanf("%d", &produto.qtdProduto);

    if (produto.qtdProduto < 0)
    {
        printf("Quantidade invalida!\n");
        system("pause");
        return -1;
    }

    printf("Quantidade minima aceitavel: ");
    fflush(stdin);
    scanf("%d", &produto.qtdMin);

    if (produto.qtdMin < 0)
    {
        printf("Quantidade invalida!\n");
        system("pause");
        return -1;
    }

    printf("Preco de compra(euros): ");
    fflush(stdin);
    scanf("%f", &produto.precoCompra);

    if (produto.precoCompra < 0)
    {
        printf("Valor invalido!\n");
        system("pause");
        return -1;
    }

    printf("Preco de venda(euros): ");
    fflush(stdin);
    scanf("%f", &produto.precoVenda);

    if (produto.precoVenda < 0)
    {
        printf("Valor invalido!\n");
        system("pause");
        return -1;
    }

    res = addProduto(inicio_listaP, fim_listaP, produto);

    return res;
}

int addProduto(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP, PRODUTO produto)
{
    ELEM_PRODUTO *novo = NULL;
    ELEM_PRODUTO *aux;
    novo = (ELEM_PRODUTO *)calloc(1, sizeof(ELEM_PRODUTO));
    novo->infoP = produto;
    novo->seguinte = NULL;
    novo->anterior = NULL;

    for (aux = *inicio_listaP; aux != NULL; aux = aux->seguinte)
    {
        if (aux->infoP.codigoProduto == novo->infoP.codigoProduto)
        {
            printf("O codigo que introduziu pertence a outro produto!\n");
            return 1;
        }
    }

    if (*fim_listaP == NULL)
    {
        *inicio_listaP = novo;
        *fim_listaP = novo;
        return 0;
    }
    else
    {
        novo->anterior = *fim_listaP;
        (*fim_listaP)->seguinte = novo;
        *fim_listaP = novo;
        return 0;
    }
    return 1;
}

void listarAlf(ELEM_PRODUTO *fim_listaP)
{
    ELEM_PRODUTO *aux = NULL;
    int tam = 0, i = 0;

    if (fim_listaP == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }

    for (aux = fim_listaP; aux != NULL; aux = aux->anterior)
    {
        tam++;
    }

    PRODUTO info[tam], info_aux;
    for (aux = fim_listaP; aux != NULL; aux = aux->anterior)
    {
        info[i] = aux->infoP;
        i++;
    }

    for (int j = 0; j < tam - 1; j++)
    {
        for (int k = 0; k < tam - 1 - j; k++)
        {
            if (strcasecmp(info[k].nomeProduto, info[k + 1].nomeProduto) > 0)
            {
                info_aux = info[k];
                info[k] = info[k + 1];
                info[k + 1] = info_aux;
            }
        }
    }

    printf("%-10s%-16s%-16s%-15s%-15s%-15s%-15s\n", "Codigo", "Nome", "Categoria", "Validade", "Quantidade", "Pr. Compra", "Pr. Venda");
    printf("--------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < tam; i++)
    {
        printf("%-10d%-16s%-16s%2d%s%2d%s%-10d%-15d%-15.2f%-15.2f\n", info[i].codigoProduto, info[i].nomeProduto, info[i].categoria, info[i].dt_validade.dia, "-",
               info[i].dt_validade.mes, "-", info[i].dt_validade.ano, info[i].qtdProduto, info[i].precoCompra, info[i].precoVenda);
    }
    printf("\n");
    system("pause");
    system("cls");
    return;
}

void listarCat(ELEM_PRODUTO *inicio_listaP)
{
    ELEM_PRODUTO *aux;
    char categoria[50];
    int encontrado = 0;

    if (inicio_listaP == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }

    printf("Categoria: ");
    fflush(stdin);
    gets(categoria);

    printf("\n%-10s%-16s%-16s%-15s%-15s%-15s%-15s\n", "Codigo", "Nome", "Categoria", "Validade", "Quantidade", "Pr. Compra", "Pr. Venda");
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (aux = inicio_listaP; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->infoP.categoria, categoria) == 0)
        {
            encontrado = 1;
            printf("%-10d%-16s%-16s%2d%s%2d%s%-10d%-15d%-15.2f%-15.2f\n", aux->infoP.codigoProduto, aux->infoP.nomeProduto, aux->infoP.categoria,
                   aux->infoP.dt_validade.dia, "-", aux->infoP.dt_validade.mes, "-", aux->infoP.dt_validade.ano, aux->infoP.qtdProduto, aux->infoP.precoCompra, aux->infoP.precoVenda);
        }
    }

    if (!encontrado)
    {
        printf("Nao ha produtos da categoria %s\n", categoria);
        system("pause");
        system("cls");

        return;
    }

    printf("\n");
    system("pause");
    system("cls");
    return;
}

void listarCod(ELEM_PRODUTO *inicio_listaP)
{
    ELEM_PRODUTO *aux;
    int codigo = 0, encontrado = 0;

    printf("Codigo: ");
    fflush(stdin);
    scanf("%d", &codigo);

    if (inicio_listaP == NULL)
    {
        printf("Lista Vazia!\n");
        system("pause");
        return;
    }

    printf("\n%-10s%-16s%-16s%-15s%-15s%-15s%-15s\n", "Codigo", "Nome", "Categoria", "Validade", "Quantidade", "Pr. Compra", "Pr. Venda");
    printf("----------------------------------------------------------------------------------------------------\n");
    for (aux = inicio_listaP; aux != NULL; aux = aux->seguinte)
    {
        if (codigo == aux->infoP.codigoProduto)
        {
            encontrado = 1;
            printf("%-10d%-16s%-16s%2d%s%2d%s%-10d%-15d%-15.2f%-15.2f\n", aux->infoP.codigoProduto, aux->infoP.nomeProduto, aux->infoP.categoria,
                   aux->infoP.dt_validade.dia, "-", aux->infoP.dt_validade.mes, "-", aux->infoP.dt_validade.ano, aux->infoP.qtdProduto, aux->infoP.precoCompra, aux->infoP.precoVenda);
        }
    }

    if (!encontrado)
    {
        printf("Nao ha nenhum produto de codigo %d\n", codigo);
        system("pause");
        system("cls");
        return;
    }

    printf("\n");
    system("pause");
    system("cls");
    return;
}

void listarExp(ELEM_PRODUTO *inicio_listaP)
{
    ELEM_PRODUTO *aux;
    time_t t = time(NULL);
    struct tm *data_atual = localtime(&t);
    int encontrado = 0;

    if (inicio_listaP == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }

    printf("Produtos com data de validade expirada: \n\n");
    printf("\n%-10s%-16s%-16s%-15s%-15s%-15s%-15s\n", "Codigo", "Nome", "Categoria", "Validade", "Quantidade", "Pr. Compra", "Pr. Venda");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (aux = inicio_listaP; aux != NULL; aux = aux->seguinte)
    {
        if (aux->infoP.dt_validade.ano < (data_atual->tm_year + 1900) ||
            (aux->infoP.dt_validade.ano == (data_atual->tm_year + 1900) && aux->infoP.dt_validade.mes < (data_atual->tm_mon + 1)) ||
            (aux->infoP.dt_validade.ano == (data_atual->tm_year + 1900) && aux->infoP.dt_validade.mes == (data_atual->tm_mon + 1) && aux->infoP.dt_validade.dia < data_atual->tm_mday))
        {
            encontrado = 1;
            printf("%-10d%-16s%-16s%2d%s%2d%s%-10d%-15d%-15.2f%-15.2f\n", aux->infoP.codigoProduto, aux->infoP.nomeProduto, aux->infoP.categoria,
                   aux->infoP.dt_validade.dia, "-", aux->infoP.dt_validade.mes, "-", aux->infoP.dt_validade.ano, aux->infoP.qtdProduto, aux->infoP.precoCompra, aux->infoP.precoVenda);
        }
    }

    if (!encontrado)
    {
        printf("Nao ha nenhum produto expirado!\n");
        system("pause");
        system("cls");
        return;
    }

    printf("\n");
    system("pause");
    system("cls");
    return;
}

void removeProduto(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP)
{
    int codigo;
    int encontrado = 0;
    ELEM_PRODUTO *aux = *inicio_listaP;
    printf("Indique o codigo do produto que quer remover: ");
    fflush(stdin);
    scanf("%d", &codigo);

    while (aux != NULL)
    {
        if (aux->infoP.codigoProduto == codigo)
        {
            encontrado = 1;
            break;
        }
        aux = aux->seguinte;
    }

    if (encontrado)
    {
        if (aux == *inicio_listaP && aux == *fim_listaP)
        {
            *inicio_listaP = NULL;
            *fim_listaP = NULL;
        }
        else if (aux == *inicio_listaP)
        {
            aux->seguinte->anterior = NULL;
            *inicio_listaP = aux->seguinte;
        }
        else if (aux == *fim_listaP)
        {
            aux->anterior->seguinte = NULL;
            *fim_listaP = aux->anterior;
        }
        else
        {
            aux->anterior->seguinte = aux->seguinte;
            aux->seguinte->anterior = aux->anterior;
        }
        printf("O produto de codigo %d foi removido da lista.\n\n", codigo);

        system("pause");
        system("cls");
        return;
    }
    else
    {
        printf("Nao foi encontrado o produto de codigo %d\n\n", codigo);
        system("pause");
        system("cls");
        return;
    }
}

void alterarProd(ELEM_PRODUTO *inicio_listaP)
{
    ELEM_PRODUTO *aux, *aux2;
    VALIDADE novaDT;
    int opcao = -1, codigo = 0, encontrado = 0;
    int nvCodigo, nvQtd;
    char nvNome[50], nvCat[50];
    float nvPrC, nvPrV;

    printf("Indique o codigo do produto que quer alterar: ");
    fflush(stdin);
    scanf("%d", &codigo);

    if (inicio_listaP == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }

    for (aux = inicio_listaP; aux != NULL; aux = aux->seguinte)
    {
        if (aux->infoP.codigoProduto == codigo)
        {
            encontrado = 1;
            printf("Produto encontrado!\n");
            printf("\n%-10s%-16s%-16s%-15s%-15s%-15s%-15s\n", "Codigo", "Nome", "Categoria", "Validade", "Quantidade", "Pr. Compra", "Pr. Venda");
            printf("----------------------------------------------------------------------------------------------------\n");
            printf("%-10d%-16s%-16s%2d%s%2d%s%-10d%-15d%-15.2f%-15.2f\n\n", aux->infoP.codigoProduto, aux->infoP.nomeProduto, aux->infoP.categoria,
                   aux->infoP.dt_validade.dia, "-", aux->infoP.dt_validade.mes, "-", aux->infoP.dt_validade.ano, aux->infoP.qtdProduto, aux->infoP.precoCompra, aux->infoP.precoVenda);
            printf("Indique que informacao que alterar:\n");
            printf("1 - Codigo\n");
            printf("2 - Nome\n");
            printf("3 - Categoria\n");
            printf("4 - Validade\n");
            printf("5 - Quantidade\n");
            printf("6 - Pr. Compra\n");
            printf("7 - Pr. Venda\n");
            printf(":");
            fflush(stdin);
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                printf("Novo codigo: ");
                fflush(stdin);
                scanf("%d", &nvCodigo);
                for (aux2 = inicio_listaP; aux2 != NULL; aux2 = aux2->seguinte)
                {
                    if (nvCodigo == aux2->infoP.codigoProduto)
                    {
                        printf("Ja existe um produto com o codigo que introduziu!\n");
                        system("pause");
                        system("cls");
                        return;
                    }
                }

                aux->infoP.codigoProduto = nvCodigo;
                break;
            case 2:
                printf("Novo nome: ");
                fflush(stdin);
                gets(nvNome);
                strcpy(aux->infoP.nomeProduto, nvNome);
                break;
            case 3:
                printf("Nova categoria: ");
                fflush(stdin);
                gets(nvCat);
                strcpy(aux->infoP.categoria, nvCat);
                break;
            case 4:
                printf("Nova data de validade: \n");
                printf("Dia: ");
                fflush(stdin);
                scanf("%d", novaDT.dia);
                printf("Mes: ");
                fflush(stdin);
                scanf("%d", &novaDT.mes);
                printf("Ano: ");
                fflush(stdin);
                scanf("%d", &novaDT.ano);
                aux->infoP.dt_validade = novaDT;
                break;
            case 5:
                printf("Nova quantidade: ");
                fflush(stdin);
                scanf("%d", &nvQtd);
                aux->infoP.qtdProduto = nvQtd;
                break;
            case 6:
                printf("Novo preco compra: ");
                fflush(stdin);
                scanf("%f", &nvPrC);
                aux->infoP.precoCompra = nvPrC;
                break;
            case 7:
                printf("Nova preco venda: ");
                fflush(stdin);
                scanf("%d", &nvPrV);
                aux->infoP.precoVenda = nvPrV;
                break;
            default:
                printf("Opcao Invalida!\n");
                return;
                break;
            }
        }
    }

    if (encontrado)
    {
        printf("Valor/es alterado com sucesso!\n");
        system("pause");
        system("cls");
        return;
    }
    else
    {
        printf("Nao existe o produto com codigo '%d'\n", codigo);
        system("pause");
        system("cls");
        return;
    }
}

void loadProdutos(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP)
{
    FILE *ficheiroProdutos = NULL;
    ficheiroProdutos = fopen("DadosProdutos.dat", "rb");
    if (ficheiroProdutos == NULL)
    {
        printf("ERRO ao iniciar o programa!\n");
        return;
    }

    PRODUTO info;
    while (fread(&info, sizeof(PRODUTO), 1, ficheiroProdutos))
    {
        addProduto(inicio_listaP, fim_listaP, info);
    }

    fclose(ficheiroProdutos);
    return;
}

int saveProdutos(ELEM_PRODUTO *inicio_listaP)
{
    FILE *ficheiroProdutos = NULL;
    ficheiroProdutos = fopen("DadosProdutos.dat", "wb");
    if (ficheiroProdutos == NULL)
    {
        printf("ERRO ao abrir o ficheiro de produtos!\n");
        return -1;
    }

    ELEM_PRODUTO *aux;
    int res = 0;

    if (inicio_listaP == NULL)
    {
        printf("Lista Vazia!\n");
        return -1;
    }

    aux = inicio_listaP;
    while (aux != NULL)
    {
        fwrite(&aux->infoP, sizeof(PRODUTO), 1, ficheiroProdutos);
        aux = aux->seguinte;
        res++;
    }

    fclose(ficheiroProdutos);
    return res;
}

float valorStock(ELEM_PRODUTO *inicio_listaP)
{
    ELEM_PRODUTO *aux;

    if (inicio_listaP == NULL)
    {
        return 0;
    }

    float soma = 0;

    for (aux = inicio_listaP; aux != NULL; aux = aux->seguinte)
    {
        soma += aux->infoP.qtdProduto * aux->infoP.precoCompra;
    }

    return soma;
}

void criarRelatorio(ELEM_PRODUTO *inicio_listaP)
{
    FILE *fp = NULL;
    fp = fopen("RelatorioStock.txt", "w");
    if (fp == NULL)
    {
        printf("ERRO ao abrir o ficheiro!\n");
        return;
    }

    ELEM_PRODUTO *aux;

    fprintf(fp, "Relatorio de Stock\n\n");
    for (aux = inicio_listaP; aux != NULL; aux = aux->seguinte)
    {
        if (aux->infoP.qtdProduto < aux->infoP.qtdMin)
        {
            fprintf(fp, "Codigo: %d, Nome: '%s' - Abaixo do nivel minimo (%d) -- Atual %d\n", aux->infoP.codigoProduto, aux->infoP.nomeProduto, aux->infoP.qtdMin, aux->infoP.qtdProduto);
        }
    }

    printf("Relatorio salvo em RelatorioStock.txt\n");
    system("pause");
    system("cls");
    fclose(fp);
    return;
}

void limparProdutos(ELEM_PRODUTO **inicio_listaP, ELEM_PRODUTO **fim_listaP)
{
    ELEM_PRODUTO *aux = NULL, *proximo = NULL;

    aux = *inicio_listaP;
    *inicio_listaP = NULL;
    *fim_listaP = NULL;
    while (aux != NULL)
    {
        proximo = aux->seguinte;
        free(aux);
        aux = proximo;
    }

    return;
}