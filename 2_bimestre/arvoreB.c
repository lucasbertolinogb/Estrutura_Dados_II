#include <stdio.h>
#include <stdlib.h>

#define T 2  // Ordem mínima da árvore. Cada nó tem no mínimo T-1 chaves e no máximo 2*T-1 chaves.

// Estrutura de um nó da Árvore B
struct arvoreB {
    int *chave;  // Array de chaves
    int grau;  // Grau mínimo da árvore
    struct arvoreB **C;  // Array de ponteiros para os filhos
    int n;  // Número atual de chaves no nó
    int folha;  // Se é folha (1) ou não (0)
};

// Função para criar um novo nó da Árvore B
struct arvoreB *criarNo(int y, int folha) {
    struct arvoreB *no = (struct arvoreB *)malloc(sizeof(struct arvoreB));
    no->grau = y;
    no->folha = folha;
    no->chave = (int *)malloc((2 * y - 1) * sizeof(int));
    no->C = (struct arvoreB **)malloc((2 * y) * sizeof(struct arvoreB *));
    no->n = 0;
    return no;
}

void dividir(struct arvoreB *no, int i, struct arvoreB *y) {
    // Cria um novo nó que armazenará (t-1) chaves do nó `y`
    struct arvoreB *z = criarNo(y->grau, y->folha);
    z->n = y->grau - 1;

    // Copia as chaves do meio para o novo nó `z`
    for (int j = 0; j < y->grau - 1; j++) {
        z->chave[j] = y->chave[j + y->grau];
    }

    // Se `y` não é uma folha, copia os filhos para `z`
    if (!y->folha) {
        for (int j = 0; j < y->grau; j++) {
            z->C[j] = y->C[j + y->grau];
        }
    }

    // Reduz o número de chaves em `y`
    y->n = y->grau - 1;

    // Move os filhos de `no` para abrir espaço para `z`
    for (int j = no->n; j >= i + 1; j--) {
        no->C[j + 1] = no->C[j];
    }

    // Liga o novo nó `z` ao nó `no`
    no->C[i + 1] = z;

    // Move as chaves de `no` para abrir espaço para a nova chave
    for (int j = no->n - 1; j >= i; j--) {
        no->chave[j + 1] = no->chave[j];
    }

    // Copia a chave do meio de `y` para `no`
    no->chave[i] = y->chave[y->grau - 1];

    // Incrementa o número de chaves em `no`
    no->n = no->n + 1;
}

// Função para inserir uma nova chave em um nó não cheio
void insNoNNUll(struct arvoreB *no, int k) {
    int i = no->n - 1;

    if (no->folha) {
        // Insere a nova chave no nó folha
        while (i >= 0 && no->chave[i] > k) {
            no->chave[i + 1] = no->chave[i];
            i--;
        }
        no->chave[i + 1] = k;
        no->n = no->n + 1;
    } else {
        // Encontra o filho que receberá a nova chave
        while (i >= 0 && no->chave[i] > k) {
            i--;
        }
        i++;

        // Se o filho está cheio, divide-o
        if (no->C[i]->n == 2 * no->grau - 1) {
            dividir(no, i, no->C[i]);

            // Depois de dividir, a chave do meio sobe para o nó atual
            if (no->chave[i] < k) {
                i++;
            }
        }
      insNoNNUll(no->C[i], k);
    }
}

// Função para inserir uma chave na Árvore B
struct arvoreB *insert(struct arvoreB *raiz, int k) {
    if (raiz->n == 2 * T - 1) {
        struct arvoreB *s = criarNo(T, 0);
        s->C[0] = raiz;
        dividir(s, 0, raiz);
        insNoNNUll(s, k);
        return s;
    } else {
        insNoNNUll(raiz, k);
        return raiz;
    }
}

// Função para imprimir a árvore (para fins de teste)
void traverse(struct arvoreB *no) {
    int i;
    for (i = 0; i < no->n; i++) {
        if (!no->folha) {
            traverse(no->C[i]);
        }
        printf("%d ", no->chave[i]);
    }
    if (!no->folha) {
        traverse(no->C[i]);
    }
}

int main() {
    struct arvoreB *raiz = criarNo(T, 1);

    // Inserindo chaves
    raiz = insert(raiz, 10);
    raiz = insert(raiz, 20);
    raiz = insert(raiz, 5);
    raiz = insert(raiz, 6);
    raiz = insert(raiz, 12);
    raiz = insert(raiz, 30);
    raiz = insert(raiz, 7);
    raiz = insert(raiz, 17);

    printf("Traversal da árvore B: ");
    traverse(raiz);
    printf("\n");

    return 0;
}
