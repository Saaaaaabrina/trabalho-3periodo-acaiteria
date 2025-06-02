#include <stdio.h>
#include <string.h>
#include <locale.h>

#define MAX_SUGESTOES 100
#define TAM_FILA 100

typedef struct {
    char descricao[100];
    float preco;
    int quantidade;
} Pedido;

typedef struct {
    Pedido pedidos[TAM_FILA];
    int inicio;
    int fim;
} Fila;

typedef struct {
    char nome[30];
    float preco;
} Copo;

typedef struct {
    char nome[30];
} Acai;

typedef struct {
    char nome[30];
    float preco;
} Frutas;

typedef struct {
    char nome[30];
    float preco;
} Cobertura;

void inicializarFila(Fila* f) {
    f->inicio = 0;
    f->fim = 0;
}

int filaVazia(Fila* f) {
    return f->inicio == f->fim;
}

int filaCheia(Fila* f) {
    return f->fim == TAM_FILA;
}

void enfileirar(Fila* f, Pedido pedido) {
    if (!filaCheia(f)) {
        f->pedidos[f->fim] = pedido;
        f->fim++;
    } else {
        printf("Total atingido, impossível adicionar mais pedidos.\n");
    }
}

void desenfileirar(Fila* f) {
    if (!filaVazia(f)) {
        printf(">> Pedido sendo preparado: %s\n", f->pedidos[f->inicio].descricao);
        f->inicio++;
    } else {
        printf("Nenhum pedido em espera.\n");
    }
}

void mostrarFila(Fila* f) {
    if (filaVazia(f)) {
        printf("Nenhum pedido em espera.\n");
    } else {
        printf("\n--- Pedidos em Espera ---\n");
        for (int i = f->inicio; i < f->fim; i++) {
            printf("- %s (Qtd: %d) - R$ %.2f\n", f->pedidos[i].descricao, f->pedidos[i].quantidade, f->pedidos[i].preco);
        }
    }
}

int main() {
    Fila filaPedidos;
    inicializarFila(&filaPedidos);

    setlocale(LC_ALL, "Portuguese");

    Copo copos[] = {
        {"500ml", 10.0},
        {"750ml", 15.0},
        {"900ml", 20.0}
    };

    Acai acais[] = {
        {"Tradicional"},
        {"Açaí com guaraná"},
        {"Açaí sem açúcar"},
        {"Açaí com banana"}
    };

    Frutas frutas[] = {
        {"Banana", 2.0},
        {"Morango", 3.0},
        {"Kiwi", 3.0},
        {"Uva-Passa", 1.5}
    };

    Cobertura coberturas[] = {
        {"Chocolate", 2.5},
        {"Morango", 2.0},
        {"Caramelo", 2.5},
        {"Limão", 1.5}
    };

    int rodando = 1, escolha, i;

    while (rodando) {
        printf("\n+-------------------------------------------------------+\n");
        printf("¦        >> Bem-vindo à Açaiteria Del Livery <<          ¦\n");
        printf("¦--------------------------------------------------------¦\n");
        printf("¦  [1]. Montar açaí personalizado                        ¦\n");
        printf("¦  [2]. Ver fila de pedidos em espera                    ¦\n");
        printf("¦  [3]. Preparar próximo pedido                          ¦\n");
        printf("¦  [4]. Sair                                             ¦\n");
        printf("+-------------------------------------------------------+\n");
        printf(">>> ");
        scanf("%d", &escolha);
        getchar();

        if (escolha == 1) {
            char descricao[200] = "";
            float precoTotal = 0.0;

            printf("\n>> Escolha o tamanho do copo:\n");
            for (i = 0; i < 3; i++) {
                printf("%d. %s - R$ %.2f\n", i + 1, copos[i].nome, copos[i].preco);
            }
            scanf("%d", &escolha);
            getchar();
            strcat(descricao, copos[escolha - 1].nome);
            precoTotal += copos[escolha - 1].preco;

            printf("\n>> Escolha o tipo de açaí:\n");
            for (i = 0; i < 4; i++) {
                printf("%d. %s\n", i + 1, acais[i].nome);
            }
            scanf("%d", &escolha);
            getchar();
            strcat(descricao, " + ");
            strcat(descricao, acais[escolha - 1].nome);

            printf("\n>> Escolha até 2 frutas (0 para nenhuma):\n");
            for (i = 0; i < 4; i++) {
                printf("%d. %s - R$ %.2f\n", i + 1, frutas[i].nome, frutas[i].preco);
            }

            int fruta;
            for (int f = 0; f < 2; f++) {
                printf("Fruta %d: ", f + 1);
                scanf("%d", &fruta);
                getchar();
                if (fruta > 0) {
                    strcat(descricao, " + ");
                    strcat(descricao, frutas[fruta - 1].nome);
                    precoTotal += frutas[fruta - 1].preco;
                }
            }

            printf("\n>> Escolha até 2 coberturas (0 para nenhuma):\n");
            for (i = 0; i < 4; i++) {
                printf("%d. %s - R$ %.2f\n", i + 1, coberturas[i].nome, coberturas[i].preco);
            }

            int cob;
            for (int c = 0; c < 2; c++) {
                printf("Cobertura %d: ", c + 1);
                scanf("%d", &cob);
                getchar();
                if (cob > 0) {
                    strcat(descricao, " + ");
                    strcat(descricao, coberturas[cob - 1].nome);
                    precoTotal += coberturas[cob - 1].preco;
                }
            }

            int qtd;
            printf("\nInforme a quantidade do pedido: ");
            scanf("%d", &qtd);
            getchar();

            precoTotal *= qtd;

            // Método de pagamento
            int metodo;
            printf("\nEscolha o método de pagamento:\n");
            printf("1. Dinheiro\n");
            printf("2. Cartão\n");
            printf(">>> ");
            scanf("%d", &metodo);
            getchar();

			const char* metodoStr;
			if (metodo == 1) {
			    metodoStr = "Dinheiro";
			} else {
			    metodoStr = "Cartão";
			}
            // Montar pedido
            Pedido p;
            strcpy(p.descricao, descricao);
            p.preco = precoTotal;
            p.quantidade = qtd;

            enfileirar(&filaPedidos, p);

            // Mostrar resumo do pedido
            printf("\n+-------------------------------------------+\n");
            printf("¦             >> PEDIDO FINAL <<             ¦\n");
            printf("+-------------------------------------------+\n");
            printf("¦ %s                                  		 ¦\n", descricao);
            printf("¦ Quantidade: %d                             ¦\n", qtd);
            printf("¦ Total a pagar: R$ %.2f                     ¦\n", precoTotal);
            printf("¦ Método de pagamento: %s                    ¦\n", metodoStr);
            printf("+-------------------------------------------+\n");
            printf("¦ Um MotoBoy está a caminho do seu endereço! ¦\n");
            printf("¦ Obrigado e volte sempre à Açaiteria Del Livery!  ¦\n");
            printf("+-------------------------------------------+\n");

        } else if (escolha == 2) {
            mostrarFila(&filaPedidos);
        } else if (escolha == 3) {
            desenfileirar(&filaPedidos);
        } else if (escolha == 4) {
            printf("Encerrando expediente...\n");
            rodando = 0;
        } else {
            printf("Opção inválida.\n");
        }
    }

    return 0;
}

