#include "libs.h"
#include "datatypes.h"

void submenuListarProd(ELEM_PRODUTO *inicio_listaP, ELEM_PRODUTO *fim_listaP)
{
    int opcao = -1;
    do
    {
        printf("\n SUB-MENU LISTAGEM\n\n");
        printf("\t1 - Listar todos os produtos\n");
        printf("\t2 - Listar por categoria\n");
        printf("\t3 - Listar produtos expirados\n");
        printf("\t4 - Pesquisar por codigo\n");
        printf("\t0 - Sair\n");
        printf("\t:");
        fflush(stdin);
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            system("cls");
            listarAlf(fim_listaP);
            break;
        case 2:
            system("cls");
            listarCat(inicio_listaP);
            break;
        case 3:
            system("cls");
            listarExp(inicio_listaP);
            break;
        case 4:
            system("cls");
            listarCod(inicio_listaP);
            break;
        case 0:
            printf("A sair...");
            system("cls");
            return;
            break;
        default:
            printf("Opcao Invalida!\n");
            break;
        }
    } while (opcao != 0);
}

int menuProdutos(ELEM_PRODUTO *inicio_listaP, ELEM_PRODUTO *fim_listaP)
{

    int opcao = -1, res = 0, Saved = 0;
    float res2 = 0;

    do
    {
        printf("\n<<<<<<<<<<<<<<< MENU PRODUTOS >>>>>>>>>>>>>>>\n\n");
        printf("\t1 - Adicionar produto ao stock\n");
        printf("\t2 - Alterar dados de produtos\n");
        printf("\t3 - Remover produto do stock\n");
        printf("\t4 - Opcoes de listagem de produtos\n");
        printf("\t5 - Calcular valor total do stock\n");
        printf("\t6 - Ver relatorio de stock\n");
        printf("\t0 - Voltar\n");
        fflush(stdin);
        printf("\t:");
        scanf("%d", &opcao);
        {
            switch (opcao)
            {
            case 1:
                system("cls");
                res = getDataProd(&inicio_listaP, &fim_listaP);
                if (res == 0)
                {
                    printf("Produto adicionado com sucesso!\n");
                    system("pause");
                    system("cls");
                    break;
                }
                else
                {
                    printf("ERRO ao adicionar o produto!\n");
                    system("pause");
                    system("cls");
                    break;
                }
            case 2:
                system("cls");
                alterarProd(inicio_listaP);
                break;
            case 3:
                system("cls");
                removeProduto(&inicio_listaP, &fim_listaP);
                break;
            case 4:
                system("cls");
                submenuListarProd(inicio_listaP, fim_listaP);
                break;
            case 5:
                system("cls");
                res2 = valorStock(inicio_listaP);
                printf("Valor total de stock: %.2f\n", res2);
                system("pause");
                system("cls");
                break;
            case 6:
                system("cls");
                criarRelatorio(inicio_listaP);
                break;
            case 0:
                printf("A sair...");
                Saved = saveProdutos(inicio_listaP);
                system("cls");
                return Saved;
                break;
            default:
                printf("Opcao Invalida!\n");
                break;
            }
        }

    } while (opcao != 0);

    return Saved;
}

int menuClientes(ELEM_CLIENT *inicio_listaC, ELEM_CLIENT *fim_listaC)
{
    int opcao = -1, res = 0, Saved = 0;

    do
    {
        printf("\n<<<<<<<<<<<<<<< MENU CLIENTES >>>>>>>>>>>>>>>\n\n");
        printf("\t1 - Adicionar cliente\n");
        printf("\t2 - Alterar dados de um cliente\n");
        printf("\t3 - Listar clientes\n");
        printf("\t4 - Procurar cliente por NIF\n");
        printf("\t0 - Voltar\n");
        fflush(stdin);
        printf("\t:");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            system("cls");
            res = getDataClient(&inicio_listaC, &fim_listaC);
            if (res == 0)
            {
                printf("Cliente adicionado com sucesso!\n");
                system("pause");
                system("cls");
                break;
            }
            else
            {
                printf("Erro ao adicionar o cliente!\n");
                system("pause");
                system("cls");
                break;
            }
            break;
        case 2:
            system("cls");
            alterarClient(inicio_listaC);
            break;
        case 3:
            system("cls");
            listarClientAlf(fim_listaC);
            break;
        case 4:
            system("cls");
            listarNIF(inicio_listaC);
            break;
        case 0:
            printf("A sair...");
            Saved = saveClients(inicio_listaC);
            system("cls");
            return Saved;
            break;
        default:
            printf("Opcao Invalida!\n");
            break;
        }
    } while (opcao != 0);

    return Saved;
}

int menuVendas(ELEM_VENDAS *inicio_listaV, ELEM_VENDAS *fim_listaV, ELEM_CLIENT *inicio_listaC, ELEM_PRODUTO *inicio_listaP)
{
    int opcao = -1;
    int res = 0, Saved = 0;

    do
    {
        printf("\n<<<<<<<<<<<<<<< MENU VENDAS >>>>>>>>>>>>>>>\n\n");
        printf("\t1 - Registar nova venda\n");
        printf("\t2 - Criar relatorio de vendas diario\n");
        printf("\t3 - Criar relatorio de vendas mensal\n");
        printf("\t4 - Criar relatorio de vendas anual\n");
        printf("\t0 - Voltar\n");
        printf("\t:");
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            system("cls");
            res = getDataVenda(&inicio_listaV, &fim_listaV, inicio_listaC, inicio_listaP);
            if (res == 0)
            {
                printf("Venda registada com sucesso!\n");
                system("pause");
                system("cls");
                break;
            }
            else
            {
                printf("Erro ao registar a venda!\n");
                system("pause");
                system("cls");
                break;
            }
            break;
        case 2:
            system("cls");
            relatorioDiario(inicio_listaV, inicio_listaP);
            printf("Relatorio guardado no ficheiro 'VendasDiarias.txt'!\n");
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            relatorioMensal(inicio_listaV, inicio_listaP);
            printf("Relatorio guardado no ficheiro 'VendasMensais.txt'\n");
            system("pause");
            system("cls");
            break;
        case 4:
            system("cls");
            relatorioAnual(inicio_listaV, inicio_listaP);
            printf("Relatorio guardado no ficheiro 'VendasAnuais.txt'\n");
            system("pause");
            system("cls");
            break;
        case 0:
            printf("A sair...");
            Saved = saveVendas(inicio_listaV);
            system("cls");
            return Saved;
            break;
        default:
            printf("Opcao Invalida!\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}

int main()
{
    ELEM_PRODUTO *inicio_listaP = NULL;
    ELEM_PRODUTO *fim_listaP = NULL;
    ELEM_CLIENT *inicio_listaC = NULL;
    ELEM_CLIENT *fim_listaC = NULL;
    ELEM_VENDAS *inicio_listaV = NULL;
    ELEM_VENDAS *fim_listaV = NULL;
    static int SaveProd = 0, SaveSales = 0, SaveClient = 0;

    loadVendas(&inicio_listaV, &fim_listaV);
    loadClients(&inicio_listaC, &fim_listaC);
    loadProdutos(&inicio_listaP, &fim_listaP);

    int opcao = -1;
    do
    {
        printf("\n<<<<<<<<<<<<<<< GESTOR STOCK >>>>>>>>>>>>>>>\n\n");
        printf("\t1 - Gerir Produtos\n");
        printf("\t2 - Gerir clientes\n");
        printf("\t3 - Gerir Vendas\n");
        printf("\t0 - Sair e guardar dados\n");
        printf("\t:");
        fflush(stdin);
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            system("cls");
            SaveProd = menuProdutos(inicio_listaP, fim_listaP);
            break;

        case 2:
            system("cls");
            SaveClient = menuClientes(inicio_listaC, fim_listaC);
            break;

        case 3:
            system("cls");
            SaveSales = menuVendas(inicio_listaV, fim_listaV, inicio_listaC, inicio_listaP);
            break;
        case 0:
            printf("A sair...\n");
            printf("%d clientes salvos\n", SaveClient);
            printf("%d produtos salvos\n", SaveProd);
            printf("%d vendas salvas", SaveSales);
            limparClients(&inicio_listaC, &fim_listaC);
            limparProdutos(&inicio_listaP, &fim_listaP);
            limparVendas(&inicio_listaV, &fim_listaV);
            return 0;
        default:
            printf("Opcao Invalida!\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}
