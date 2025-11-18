#include <stdio.h>
#include <string.h>

#define TAM 100

struct Categoria {
    int codigo;
    char name[50];
};

struct Produto {
    int codigo;
    char titulo[100];
    char descricao[256];
    int categoria; 
    int preco; 
};

/*========================================================
    QUESTÃO 1 – CADASTRAR CATEGORIA
========================================================*/
void cadastrarCategoria(struct Categoria v[], int *qtd) {
    if (*qtd >= TAM) {
        printf("Nao e possivel cadastrar: vetor cheio.\n");
        return;
    }

    int codigo;
    printf("Digite o codigo da nova categoria: ");
    scanf("%d", &codigo);

    // Verificar se já existe
    for (int i = 0; i < *qtd; i++) {
        if (v[i].codigo == codigo) {
            printf("Codigo ja existente! Cadastro cancelado.\n");
            return;
        }
    }

    v[*qtd].codigo = codigo;

    printf("Digite o nome da categoria: ");
    getchar();
    fgets(v[*qtd].name, 50, stdin);
    v[*qtd].name[strcspn(v[*qtd].name, "\n")] = '\0';

    (*qtd)++;
}

/*========================================================
    QUESTÃO 2 – IMPRIMIR CATEGORIAS
========================================================*/
void imprimirCategorias(struct Categoria v[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("Codigo: %d | Nome: %s\n", v[i].codigo, v[i].name);
    }
}

/*========================================================
    QUESTÃO 3 – IMPRIMIR PRODUTOS
========================================================*/
void imprimirProdutos(struct Produto vp[], int qtdProdutos,
                      struct Categoria vc[], int qtdCategorias) {

    for (int i = 0; i < qtdProdutos; i++) {

        char nomeCategoria[50] = "Categoria nao encontrada";

        // Buscar nome da categoria
        for (int j = 0; j < qtdCategorias; j++) {
            if (vc[j].codigo == vp[i].categoria) {
                strcpy(nomeCategoria, vc[j].name);
                break;
            }
        }

        double precoCorrigido = vp[i].preco / 100.0;

        printf("\n--- PRODUTO %d ---\n", i+1);
        printf("Codigo: %d\n", vp[i].codigo);
        printf("Titulo: %s\n", vp[i].titulo);
        printf("Descricao: %s\n", vp[i].descricao);
        printf("Categoria: %s\n", nomeCategoria);
        printf("Preco: R$ %.2f\n", precoCorrigido);
    }
}

/*========================================================
    QUESTÃO 4 – SELECTION SORT POR DESCRIÇÃO
========================================================*/
void selectionSortPorDescricao(struct Produto v[], int qtd) {
    int menor;
    struct Produto aux;

    for (int i = 0; i < qtd - 1; i++) {
        menor = i;

        for (int j = i + 1; j < qtd; j++) {
            if (strcmp(v[j].descricao, v[menor].descricao) < 0) {
                menor = j;
            }
        }

        if (menor != i) {
            aux = v[i];
            v[i] = v[menor];
            v[menor] = aux;
        }
    }
}

/*========================================================
    QUESTÃO 5 – BUSCA BINÁRIA POR DESCRIÇÃO
========================================================*/
int buscaBinariaPorDescricao(struct Produto v[], int qtd, char *x) {
    int inicio = 0, fim = qtd - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        int cmp = strcmp(v[meio].descricao, x);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1; 
}

/*========================================================
    MAIN PARA TESTES
========================================================*/
int main() {
    struct Categoria categorias[TAM];
    struct Produto produtos[TAM];

    int qtdCategorias = 0;
    int qtdProdutos = 0;

    int opc;
    char busca[256];

    while (1) {
        printf("\n=========== MENU ===========\n");
        printf("1 - Cadastrar Categoria\n");
        printf("2 - Listar Categorias\n");
        printf("3 - Cadastrar Produto\n");
        printf("4 - Listar Produtos\n");
        printf("5 - Ordenar Produtos por Descricao\n");
        printf("6 - Buscar Produto por Descricao (Binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        if (opc == 0) break;

        switch (opc) {
            case 1:
                cadastrarCategoria(categorias, &qtdCategorias);
                break;

            case 2:
                imprimirCategorias(categorias, qtdCategorias);
                break;

            case 3:
                if (qtdProdutos >= TAM) {
                    printf("Limite de produtos atingido.\n");
                } else {
                    printf("Codigo do produto: ");
                    scanf("%d", &produtos[qtdProdutos].codigo);

                    printf("Titulo: ");
                    getchar();
                    fgets(produtos[qtdProdutos].titulo, 100, stdin);
                    produtos[qtdProdutos].titulo[strcspn(produtos[qtdProdutos].titulo, "\n")] = '\0';

                    printf("Descricao: ");
                    fgets(produtos[qtdProdutos].descricao, 256, stdin);
                    produtos[qtdProdutos].descricao[strcspn(produtos[qtdProdutos].descricao, "\n")] = '\0';

                    printf("Codigo da categoria: ");
                    scanf("%d", &produtos[qtdProdutos].categoria);

                    printf("Preco (em centavos): ");
                    scanf("%d", &produtos[qtdProdutos].preco);

                    qtdProdutos++;
                }
                break;

            case 4:
                imprimirProdutos(produtos, qtdProdutos, categorias, qtdCategorias);
                break;

            case 5:
                selectionSortPorDescricao(produtos, qtdProdutos);
                printf("Ordenado!\n");
                break;

            case 6:
                printf("Digite a descricao para buscar: ");
                getchar();
                fgets(busca, 256, stdin);
                busca[strcspn(busca, "\n")] = '\0';

                selectionSortPorDescricao(produtos, qtdProdutos); // necessário
                int pos = buscaBinariaPorDescricao(produtos, qtdProdutos, busca);

                if (pos == -1)
                    printf("Nao encontrado.\n");
                else
                    printf("Produto encontrado na posicao %d.\n", pos);

                break;

            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}
