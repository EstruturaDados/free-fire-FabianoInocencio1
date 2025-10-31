#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Estrutura do item da mochila:
 * Cada item possui nome, tipo, prioridade e ponteiro para o próximo item.
 * Utiliza-se lista ligada para facilitar inserções e remoções dinâmicas.
 */
typedef struct item {
    char nome[50];
    char tipo[50];
    int prioridade;
    struct item* prox;
} item;

/* Função para criar uma mochila vazia */
item* criarMochila() {
    return NULL;
}

/*
 * Função para adicionar item à mochila
 * Recebe a mochila atual, nome, tipo e prioridade.
 * O item é adicionado no início da lista (push front).
 */
item* adicionarItem(item* mochila, const char* nome, const char* tipo, int prioridade) {
    item* novo = (item*)malloc(sizeof(item));
    if (novo == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    strcpy(novo->nome, nome);
    strcpy(novo->tipo, tipo);
    novo->prioridade = prioridade;
    novo->prox = mochila; // insere no início da lista

    printf("Item '%s' adicionado à mochila.\n", nome);
    return novo;
}

/*
 * Função para remover item da mochila
 * Percorre a lista ligada procurando pelo nome do item.
 * Ajusta ponteiros e libera memória do item removido.
 */
item* removerItem(item* mochila, const char* nome) {
    item* anterior = NULL;
    item* atual = mochila;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Item '%s' não encontrado na mochila.\n", nome);
        return mochila;
    }

    if (anterior == NULL) {
        mochila = atual->prox; // remover o primeiro item
    } else {
        anterior->prox = atual->prox;
    }

    printf("Item '%s' removido da mochila!\n", nome);
    free(atual);
    return mochila;
}

/*
 * Função para listar todos os itens da mochila
 * Percorre a lista ligada imprimindo cada item.
 */
void listarMochila(item* mochila) {
    if (mochila == NULL) {
        printf("Mochila de sobrevivência vazia.\n");
        return;
    }

    printf("Itens na mochila:\n");
    item* atual = mochila;
    while (atual != NULL) {
        printf("- %s (%s) prioridade: %d\n", atual->nome, atual->tipo, atual->prioridade);
        atual = atual->prox;
    }
}

/*
 * Função para ordenar a mochila por nome em ordem alfabética
 * Utiliza Bubble Sort adaptado para lista ligada.
 */
void ordenarPorNome(item* mochila) {
    if (mochila == NULL) return;

    int trocou;
    do {
        trocou = 0;
        item* atual = mochila;
        while (atual->prox != NULL) {
            if (strcmp(atual->nome, atual->prox->nome) > 0) {
                char tempNome[50], tempTipo[50];
                int tempPrioridade;

                // Troca os campos de nome, tipo e prioridade para manter consistência do item
                strcpy(tempNome, atual->nome);
                strcpy(tempTipo, atual->tipo);
                tempPrioridade = atual->prioridade;

                strcpy(atual->nome, atual->prox->nome);
                strcpy(atual->tipo, atual->prox->tipo);
                atual->prioridade = atual->prox->prioridade;

                strcpy(atual->prox->nome, tempNome);
                strcpy(atual->prox->tipo, tempTipo);
                atual->prox->prioridade = tempPrioridade;

                trocou = 1;
            }
            atual = atual->prox;
        }
    } while (trocou);
}

/*
 * Função para ordenar a mochila por prioridade crescente
 * Utiliza Bubble Sort apenas no campo 'prioridade'.
 */
void ordenarPorPrioridade(item* mochila) {
    if (mochila == NULL) return;

    int trocou;
    do {
        trocou = 0;
        item* atual = mochila;
        while (atual->prox != NULL) {
            if (atual->prioridade > atual->prox->prioridade) {
                int temp = atual->prioridade;
                atual->prioridade = atual->prox->prioridade;
                atual->prox->prioridade = temp;
                trocou = 1;
            }
            atual = atual->prox;
        }
    } while (trocou);
}

/*
 * Função para validar nomes
 * Aceita apenas letras e espaços, retorna 1 se válido.
 */
int nomeValido(const char *str) {
    if (str[0] == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != ' ')
            return 0;
    }
    return 1;
}

/* Função principal */
int main() {
    item* mochila = criarMochila();
    int opcao;
    char nome[50];
    char tipo[50];
    int prioridade;

    do {
        printf("\n============== Plano de Fuga ===================\n");
        printf("=========== Mochila de Sobrevivência ===========\n");
        printf("1 - Adicionar Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens da Mochila\n");
        printf("4 - Organizar Mochila (Ordenar componentes)\n");
        printf("5 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Nome do item: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Tipo do item: ");
                fgets(tipo, sizeof(tipo), stdin);
                tipo[strcspn(tipo, "\n")] = '\0';

                printf("Defina a prioridade: ");
                scanf("%d", &prioridade);
                getchar();

                mochila = adicionarItem(mochila, nome, tipo, prioridade);
                break;

            case 2:
                printf("Nome do item a remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                mochila = removerItem(mochila, nome);
                break;

            case 3:
                listarMochila(mochila);
                break;

            case 4: {
                int opcaoOrdenar;
                printf("Como deseja ordenar?\n");
                printf("1 - Por nome (Alfabética)\n");
                printf("2 - Por prioridade\n");
                printf("3 - Cancelar\n");
                printf("Escolha: ");
                scanf("%d", &opcaoOrdenar);
                getchar();

                switch (opcaoOrdenar) {
                    case 1:
                        ordenarPorNome(mochila);
                        printf("Mochila organizada por nome (alfabética).\n");
                        listarMochila(mochila);
                        break;
                    case 2:
                        ordenarPorPrioridade(mochila);
                        printf("Mochila organizada por prioridade.\n");
                        listarMochila(mochila);
                        break;
                    case 3:
                        printf("Cancelando ordenação...\n");
                        break;
                    default:
                        printf("Opção inválida!\n");
                }
                break;
            }

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 5);

    /* Libera toda a memória alocada */
    item* atual = mochila;
    while (atual != NULL) {
        item* temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
}