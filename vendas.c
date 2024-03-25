#include "libs.h"
#include "datatypes.h"

int getDataVenda(ELEM_VENDAS **inicio_listaV, ELEM_VENDAS **fim_listaV, ELEM_CLIENT *inicio_listaC, ELEM_PRODUTO *inicio_listaP)
{

    VENDA temp;
    int res;
    ELEM_CLIENT *auxC = NULL;
    ELEM_PRODUTO *auxP = NULL;
    int encontrado = 0;
    time_t t = time(NULL);
    struct tm *data_atual = localtime(&t);

    printf("Codigo de cliente: ");
    fflush(stdin);
    scanf("%d", &temp.idCliente);

    for (auxC = inicio_listaC; auxC != NULL; auxC = auxC->seguinte)
    {
        if (temp.idCliente == auxC->infoC.codigoClient)
        {
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("Nao existe um cliente com o codigo %d!\n", temp.idCliente);
        system("pause");
        system("cls");
        return -1;
    }

    encontrado = 0;

    printf("Codigo de produto: ");
    fflush(stdin);
    scanf("%d", &temp.idProduto);

    for (auxP = inicio_listaP; auxP != NULL; auxP = auxP->seguinte)
    {
        if (temp.idProduto == auxP->infoP.codigoProduto)
        {
            temp.precoVenda = auxP->infoP.precoVenda;
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("Nao existe um produto com o codigo %d!\n", temp.idProduto);
        system("pause");
        system("cls");
        return -1;
    }

    printf("Quantidade vendida: ");
    fflush(stdin);
    scanf("%d", &temp.qtdVendida);

    for (auxP = inicio_listaP; auxP != NULL; auxP = auxP->seguinte)
    {
        if (temp.idProduto == auxP->infoP.codigoProduto)
        {
            if (temp.qtdVendida > auxP->infoP.qtdProduto)
            {
                printf("Quantidade introduzida inválida!\n");
                system("pause");
                system("cls");
                return -1;
            }

            auxP->infoP.qtdProduto = auxP->infoP.qtdProduto - temp.qtdVendida;
        }
    }

    printf("Data da venda:\n");
    printf("Dia: ");
    fflush(stdin);
    scanf("%d", &temp.dtVenda.dia);

    printf("Mes: ");
    fflush(stdin);
    scanf("%d", &temp.dtVenda.mes);

    printf("Ano: ");
    fflush(stdin);
    scanf("%d", &temp.dtVenda.ano);

    if (temp.dtVenda.ano > (data_atual->tm_year + 1900) || temp.dtVenda.ano == (data_atual->tm_year + 1900) && temp.dtVenda.mes > (data_atual->tm_mon + 1) || temp.dtVenda.ano == (data_atual->tm_year + 1900) && temp.dtVenda.mes == (data_atual->tm_mon + 1) && temp.dtVenda.dia > (data_atual->tm_mday))
    {
        printf("Data Inválida!\n");
        system("pause");
        system("cls");
        return -1;
    }

    temp.receitaVenda = temp.qtdVendida * temp.precoVenda;

    res = addVenda(inicio_listaV, fim_listaV, temp);
    return res;
}

int addVenda(ELEM_VENDAS **inicio_listaV, ELEM_VENDAS **fim_listaV, VENDA temp)
{

    ELEM_VENDAS *novo = NULL;
    novo = (ELEM_VENDAS *)calloc(1, sizeof(ELEM_VENDAS));
    if (novo == NULL)
    {
        printf("Out Of Memory!\n");
        system("pause");
        return 1;
    }
    novo->infoV = temp;
    novo->seguinte = NULL;
    novo->anterior = NULL;

    if (*inicio_listaV == NULL)
    {
        *inicio_listaV = novo;
        *fim_listaV = novo;
        return 0;
    }
    else
    {
        novo->seguinte = *inicio_listaV;
        (*inicio_listaV)->anterior = novo;
        *inicio_listaV = novo;
        return 0;
    }
    return 1;
}

int saveVendas(ELEM_VENDAS *inicio_listaV)
{
    FILE *ficheiroVendas = NULL;
    ficheiroVendas = fopen("DadosVendas.dat", "wb");
    if (ficheiroVendas == NULL)
    {
        printf("Erro ao abrir o ficheiro!\n");
        return -1;
    }

    ELEM_VENDAS *aux;
    int res = 0;

    if (inicio_listaV == NULL)
    {
        printf("Lista Vazia!\n");
        return -1;
    }

    aux = inicio_listaV;
    while (aux != NULL)
    {
        fwrite(&aux->infoV, sizeof(VENDA), 1, ficheiroVendas);
        aux = aux->seguinte;
        res++;
    }

    fclose(ficheiroVendas);
    return res;
}

void loadVendas(ELEM_VENDAS **inicio_listaV, ELEM_VENDAS **fim_listaP)
{
    FILE *ficheiroVendas = NULL;
    ficheiroVendas = fopen("DadosVendas.dat", "rb");
    if (ficheiroVendas == NULL)
    {
        printf("ERRO ao iniciar o programa!\n");
        return;
    }

    VENDA info;
    while (fread(&info, sizeof(VENDA), 1, ficheiroVendas))
    {
        addVenda(inicio_listaV, fim_listaP, info);
    }

    fclose(ficheiroVendas);
}

void limparVendas(ELEM_VENDAS **inicio_listaV, ELEM_VENDAS **fim_listaV)
{
    ELEM_VENDAS *proximo = NULL, *aux = NULL;

    aux = *inicio_listaV;
    *inicio_listaV = NULL;
    *fim_listaV = NULL;

    while (aux != NULL)
    {
        proximo = aux->seguinte;
        free(aux);
        aux = proximo;
    }
}

void relatorioDiario(ELEM_VENDAS *inicio_listaV, ELEM_PRODUTO *inicio_listaP)
{
    FILE *fp = NULL;
    time_t t = time(NULL);
    struct tm *data_atual = localtime(&t);
    fp = fopen("VendasDiarias.txt", "w");
    if (fp == NULL)
    {
        printf("ERRO ao abrir o ficheiro!\n");
        system("pause");
        return;
    }

    ELEM_PRODUTO *temp = NULL;
    float receita = 0;
    ELEM_VENDAS *aux = NULL;

    fprintf(fp, "Relatorio diario de vendas - %d/%d/%d\n\n", data_atual->tm_mday, (data_atual->tm_mon + 1), (data_atual->tm_year + 1900));

    for (temp = inicio_listaP; temp != NULL; temp = temp->seguinte)
    {
        for (aux = inicio_listaV; aux != NULL; aux = aux->seguinte)
        {
            if (temp->infoP.codigoProduto == aux->infoV.idProduto)
            {
                if (aux->infoV.dtVenda.dia == data_atual->tm_mday && aux->infoV.dtVenda.mes == (data_atual->tm_mon + 1) && aux->infoV.dtVenda.ano == (data_atual->tm_year + 1900))
                {
                    receita += aux->infoV.receitaVenda;
                    fprintf(fp, "Data: %d/%d/%d\n", aux->infoV.dtVenda.dia, aux->infoV.dtVenda.mes, aux->infoV.dtVenda.ano);
                    fprintf(fp, "Produto: %s, codigo %d\n", temp->infoP.nomeProduto, aux->infoV.idProduto);
                    fprintf(fp, "Quantidade vendida: %d\n\n", aux->infoV.qtdVendida);
                }
            }
        }
    }

    if (receita == 0)
    {
        fprintf(fp, "Ainda nao foram efetuadas vendas!\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "Receita Total: %.2f euros\n\n", receita);
    fclose(fp);
    return;
}

void relatorioMensal(ELEM_VENDAS *inicio_listaV, ELEM_PRODUTO *inicio_listaP)
{
    time_t t = time(NULL);
    struct tm *data_atual = localtime(&t);
    FILE *fp = NULL;
    fp = fopen("VendasMensais.txt", "w");
    if (fp == NULL)
    {
        printf("ERRO ao abrir o ficheiro!\n");
        system("pause");
        return;
    }

    ELEM_PRODUTO *temp = NULL;
    ELEM_VENDAS *temp2 = NULL;
    float receita = 0;
    char meses[12][20] = {"Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

    fprintf(fp, "Relatorio mensal de vendas -  %s de %d\n\n", meses[data_atual->tm_mon], data_atual->tm_year + 1900);

    for (temp = inicio_listaP; temp != NULL; temp = temp->seguinte)
    {
        for (temp2 = inicio_listaV; temp2 != NULL; temp2 = temp2->seguinte)
        {
            if (temp->infoP.codigoProduto == temp2->infoV.idProduto)
            {
                if (temp2->infoV.dtVenda.mes == (data_atual->tm_mon + 1) && temp2->infoV.dtVenda.ano == (data_atual->tm_year + 1900))
                {
                    receita += temp2->infoV.receitaVenda;
                    fprintf(fp, "Data: %d/%d/%d\n", temp2->infoV.dtVenda.dia, temp2->infoV.dtVenda.mes, temp2->infoV.dtVenda.ano);
                    fprintf(fp, "Produto: %s, codigo %d\n", temp->infoP.nomeProduto, temp2->infoV.idProduto);
                    fprintf(fp, "Quantidade vendida: %d\n\n", temp2->infoV.qtdVendida);
                }
            }
        }
    }

    if (receita == 0)
    {
        fprintf(fp, "Ainda nao foram efetuadas vendas!\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "Receita Total: %.2f euros\n\n", receita);
    fclose(fp);
    return;
}

void relatorioAnual(ELEM_VENDAS *inicio_listaV, ELEM_PRODUTO *inicio_listaP)
{
    FILE *fp = NULL;
    time_t t = time(NULL);
    struct tm *data_atual = localtime(&t);
    fp = fopen("VendasAnuais.txt", "w");
    if (fp == NULL)
    {
        printf("ERRO ao abrir o ficheiro!\n");
        system("pause");
        return;
    }

    ELEM_PRODUTO *temp = NULL;
    ELEM_VENDAS *temp2 = NULL;
    float receita = 0;

    fprintf(fp, "Relatorio anual de vendas - %d\n\n", data_atual->tm_year + 1900);

    for (temp = inicio_listaP; temp != NULL; temp = temp->seguinte)
    {
        for (temp2 = inicio_listaV; temp2 != NULL; temp2 = temp2->seguinte)
        {
            if (temp->infoP.codigoProduto == temp2->infoV.idProduto)
            {
                if (temp2->infoV.dtVenda.ano == (data_atual->tm_year + 1900))
                {
                    receita += temp2->infoV.receitaVenda;
                    fprintf(fp, "Data: %d/%d/%d\n", temp2->infoV.dtVenda.dia, temp2->infoV.dtVenda.mes, temp2->infoV.dtVenda.ano);
                    fprintf(fp, "Produto: %s, codigo %d\n", temp->infoP.nomeProduto, temp2->infoV.idProduto);
                    fprintf(fp, "Quantidade vendida: %d\n\n", temp2->infoV.qtdVendida);
                }
            }
        }
    }

    if (receita == 0)
    {
        fprintf(fp, "Ainda nao foram efetuadas vendas!\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "Receita Total: %.2f euros\n\n", receita);
    fclose(fp);
    return;
}