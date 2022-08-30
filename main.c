#include <stdio.h>
#include <locale.h>

#define TAM 100

int valores_moedas[TAM];
int valor_limite[TAM];
int quant_moedas[TAM];
int quant_lim[TAM];

/* ================================================= Ordenacao */
int ordem(int tamanho) { // crescente
    int x, y, troca;
    for (x = tamanho; x >= 1; x--) /* define a posicao de teto */ {
        for (y = 1; y < x; y++) {
            if (valores_moedas[y] > valores_moedas[y + 1]) {
                troca = valores_moedas[y];
                valores_moedas[y] = valores_moedas[y + 1];
                valores_moedas[y + 1] = troca;
            }
        }
    }
}

int ordem2(int tamanho) { // decrescente
    int x, y, troca;
    for (x = tamanho; x >= 1; x--) /* define a posicao de teto */ {
        for (y = 1; y < x; y++) {
            if (valor_limite[y] < valor_limite[y + 1]) { // esta linha é alterada, sinal > vira <
                troca = valor_limite[y];
                valor_limite[y] = valor_limite[y + 1];
                valor_limite[y + 1] = troca;
            }
        }
    }
}
/* ================================================================ */

Inicializar(int m) {
    int i;
    for (i = 1; i <= m; i++)
        quant_moedas[i] = 0;
}

Inicializar2(int m) {
    int i;
    for (i = 1; i <= m; i++)
        quant_lim[i] = 0;
}

void main() {
    setlocale(LC_ALL, "portuguese");

    int v_desejado, m, resto, i, moeda_selecionada,
    l, valor_selecionado;

    printf("Valor de troco: ");
    scanf("%d", &v_desejado);

    printf("Quantidade de tipos de moedas: ");
    scanf("%d", &m);

    Inicializar(m);
    for (i = 1; i <= m; i++) {
        printf("Valor de moeda: ");
        scanf("%d", & valores_moedas[i]);
    }

    /* Ordenação crescente para os valores dos tipos de moedas */
    ordem(m);

    l = m;
    printf("\n");

    Inicializar2(l);
    for (i = 1; i <= l; i++) {
        printf("Valor limite da %dª moeda: ", i);
        scanf("%d", & valor_limite[i]);
    }

    /* Ordenação decrescente para os valores LIMITES dos tipos de moedas */
    ordem2(l);

    resto = v_desejado;

    printf("\n");
    // Imprimindo, respectivamente, as moedas e os limites da moedas
    for (i = 1; i <= m; i++) {
        printf("Moedas: %d\n", valores_moedas[i]);
    }

    for (i = 1; i <= l; i++) {
        printf("Limites cada moeda: %d\n", valor_limite[i]);
    }

    moeda_selecionada = m; /* começa pela moeda de maior valor */
    valor_selecionado = l;

    while ((resto != 0) && (moeda_selecionada != 0) && (valor_selecionado != 0)) { // se resto, moeda_selec. e valor_selec. tiverem conteúdo
        if (resto >= valores_moedas[moeda_selecionada] && valor_limite[moeda_selecionada] != 0) { // se 467 for maior ou igual a 100 e moeda de 100 não ter limite atingido
            quant_moedas[moeda_selecionada]++; // quantidade de uso da moeda 100 aumenta 1
            resto = resto - valores_moedas[moeda_selecionada]; // tira 100 de 467, resultando 367
            valor_limite[moeda_selecionada] -= 1; // limite de uso da moeda 100 diminiu 1 e
                                                  // repete ciclo até ser < q 100 e o limite acabar
        } else
            moeda_selecionada--; // como 67 é menor q 100, o tipo da moeda abaixa,
                                 // ou seja, agr é 50 e ciclo repete
    }

    /* mostrar resultado */
    if (resto != 0)
        printf("\n\nTroco nao possivel\n");
    else {
        printf("\nTipos de moedas -----------\n");
        for (i = 1; i <= m; i++) {
            printf("%d ", valores_moedas[i]);
        }

        printf("\nTroco realizado -----------\n");
        for (i = 1; i <= m; i++) {
            printf("%d ", quant_moedas[i]);
        }
    }
}
