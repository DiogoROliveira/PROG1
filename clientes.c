#include "libs.h"
#include "datatypes.h"

// Variável Global estática
static int proximoCodigoCliente = 1;

int getDataClient(ELEM_CLIENT **inicio_listaC, ELEM_CLIENT **fim_listaC)
{
    CLIENTE client;

    int res = 0;
    printf("Inserir Cliente:\n\n");

    printf("Nome do cliente: ");
    fflush(stdin);
    gets(client.nome);

    printf("Morada do cliente: ");
    fflush(stdin);
    gets(client.morada);

    printf("Insira o NIF do cliente: ");
    fflush(stdin);
    scanf("%ld", &client.NIF);

    printf("Insira o numero de telefone: ");
    fflush(stdin);
    scanf("%ld", &client.telefone);

    printf("Insira o email: ");
    fflush(stdin);
    gets(client.email);

    res = addClient(inicio_listaC, fim_listaC, client);
    return res;
}

// Passar para a lista
int addClient(ELEM_CLIENT **inicio_listaC, ELEM_CLIENT **fim_listaC, CLIENTE client)
{
    ELEM_CLIENT *novo = NULL;
    ELEM_CLIENT *aux;

    novo = (ELEM_CLIENT *)calloc(1, sizeof(ELEM_CLIENT));
    if (novo == NULL)
    {
        printf("Out of Memory!");
        return -1;
    }
    novo->infoC = client;
    novo->seguinte = NULL;
    novo->anterior = NULL;

    for (aux = *inicio_listaC; aux != NULL; aux = aux->seguinte)
    {
        if (aux->infoC.NIF == novo->infoC.NIF)
        {
            printf("O NIF que introduziu pertence a outro cliente!\n");
            return 1;
        }
    }

    if (*fim_listaC == NULL)
    {
        novo->infoC.codigoClient = proximoCodigoCliente;
        *inicio_listaC = novo;
        *fim_listaC = novo;
        // Atualizar o próximo código disponível
        proximoCodigoCliente++;
        return 0;
    }
    else
    {
        novo->infoC.codigoClient = proximoCodigoCliente;
        novo->anterior = *fim_listaC;
        (*fim_listaC)->seguinte = novo;
        *fim_listaC = novo;
        // Atualizar o próximo código disponível
        proximoCodigoCliente++;
        return 0;
    }

    return 1;
}

// Listar os clientes alfabéticamente
void listarClientAlf(ELEM_CLIENT *fim_listaC)
{
    ELEM_CLIENT *aux = NULL;
    int tam = 0, i = 0;

    if (fim_listaC == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }

    for (aux = fim_listaC; aux != NULL; aux = aux->anterior)
    {
        tam++;
    }

    CLIENTE info[tam], info_aux;
    for (aux = fim_listaC; aux != NULL; aux = aux->anterior)
    {
        info[i] = aux->infoC;
        i++;
    }

    // Ordenar Alfabéticamente
    for (int j = 0; j < tam - 1; j++)
    {
        for (int k = 0; k < tam - 1 - j; k++)
        {
            if (strcasecmp(info[k].nome, info[k + 1].nome) > 0)
            {
                info_aux = info[k];
                info[k] = info[k + 1];
                info[k + 1] = info_aux;
            }
        }
    }

    printf("%-10s%-22s%-25s%-12s%-12s%-24s\n", "Codigo", "Nome", "Morada", "NIF", "Telefone", "Email");
    printf("--------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < tam; i++)
    {
        printf("%-10d%-22s%-25s%-12ld%-12ld%-24s\n", info[i].codigoClient, info[i].nome, info[i].morada, info[i].NIF, info[i].telefone, info[i].email);
    }

    printf("\n");
    system("pause");
    system("cls");
    return;
}

// Listar por NIF
void listarNIF(ELEM_CLIENT *inicio_listaC)
{
    ELEM_CLIENT *aux;
    int nif = 0, encontrado = 0;

    printf("NIF: ");
    fflush(stdin);
    scanf("%d", &nif);

    if (inicio_listaC == NULL)
    {
        printf("Lista Vazia!\n");
        system("pause");
        return;
    }

    printf("%-10s%-22s%-25s%-12s%-12s%-24s\n", "Codigo", "Nome", "Morada", "NIF", "Telefone", "Email");
    printf("--------------------------------------------------------------------------------------------------------\n");
    for (aux = inicio_listaC; aux != NULL; aux = aux->seguinte)
    {
        if (nif == aux->infoC.NIF)
        {
            encontrado = 1;
            printf("%-10d%-22s%-25s%-12ld%-12ld%-24s\n", aux->infoC.codigoClient, aux->infoC.nome, aux->infoC.morada, aux->infoC.NIF, aux->infoC.telefone, aux->infoC.email);
        }
    }

    if (!encontrado)
    {
        printf("Nao ha nenhum cliente de NIF: %d\n", nif);
        system("pause");
        system("cls");
        return;
    }

    printf("\n");
    system("pause");
    system("cls");
    return;
}

// Alterar Cliente
void alterarClient(ELEM_CLIENT *inicio_listaC)
{
    ELEM_CLIENT *aux;

    int opcao = -1, codigo = 0, encontrado = 0;
    long int nvTelefone;
    char nvMorada[200], nvEmail[50];

    printf("Indique o codigo do cliente que pretende alterar: ");
    fflush(stdin);
    scanf("%d", &codigo);

    if (inicio_listaC == NULL)
    {
        printf("Lista Vazia!\n");
        return;
    }

    for (aux = inicio_listaC; aux != NULL; aux = aux->seguinte)
    {
        if (aux->infoC.codigoClient == codigo)
        {
            encontrado = 1;
            printf("Cliente encontrado!\n\n");
            printf("%-10s%-22s%-25s%-12s%-12s%-24s\n", "Codigo", "Nome", "Morada", "NIF", "Telefone", "Email");
            printf("--------------------------------------------------------------------------------------------------------\n");
            printf("%-10d%-22s%-25s%-12ld%-12ld%-24s\n\n", aux->infoC.codigoClient, aux->infoC.nome, aux->infoC.morada, aux->infoC.NIF, aux->infoC.telefone, aux->infoC.email);
            printf("Indique que informacao que alterar:\n");
            printf("1 - Morada\n");
            printf("2 - Telefone\n");
            printf("3 - Email\n");
            printf(":");
            fflush(stdin);
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
                printf("Nova morada: ");
                fflush(stdin);
                gets(nvMorada);
                strcpy(aux->infoC.morada, nvMorada);
                break;
            case 2:
                printf("Novo telefone: ");
                fflush(stdin);
                scanf("%ld", &nvTelefone);
                aux->infoC.telefone = nvTelefone;
                break;
            case 3:
                printf("Novo email: ");
                fflush(stdin);
                gets(nvEmail);
                strcpy(aux->infoC.email, nvEmail);
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
        printf("Nao existe o cliente com codigo '%d'\n", codigo);
        system("pause");
        system("cls");
        return;
    }
}

void loadClients(ELEM_CLIENT **inicio_listaC, ELEM_CLIENT **fim_listaC)
{
    FILE *ficheiroClientes = NULL;
    ficheiroClientes = fopen("DadosClientes.dat", "rb");
    if (ficheiroClientes == NULL)
    {
        printf("Erro ao iniciar o programa!\n");
        return;
    }

    CLIENTE info;
    while (fread(&info, sizeof(CLIENTE), 1, ficheiroClientes))
    {
        addClient(inicio_listaC, fim_listaC, info);
    }

    fclose(ficheiroClientes);
    return;
}

int saveClients(ELEM_CLIENT *inicio_listaC)
{
    FILE *ficheiroClientes = NULL;
    ficheiroClientes = fopen("DadosClientes.dat", "wb");
    if (ficheiroClientes == NULL)
    {
        printf("Erro ao abrir o ficheiro de clientes!\n");
        return -1;
    }

    ELEM_CLIENT *aux;
    int res = 0;

    if (inicio_listaC == NULL)
    {
        printf("Lista Vazia!\n");
        return -1;
    }

    aux = inicio_listaC;
    while (aux != NULL)
    {
        fwrite(&aux->infoC, sizeof(CLIENTE), 1, ficheiroClientes);
        aux = aux->seguinte;
        res++;
    }

    fclose(ficheiroClientes);
    return res;
}

void limparClients(ELEM_CLIENT **inicio_listaC, ELEM_CLIENT **fim_listaC)
{
    ELEM_CLIENT *aux = NULL, *proximo = NULL;
    aux = *inicio_listaC;
    *inicio_listaC = NULL;
    *fim_listaC = NULL;

    while (aux != NULL)
    {
        proximo = aux->seguinte;
        free(aux);
        aux = proximo;
    }

    return;
}