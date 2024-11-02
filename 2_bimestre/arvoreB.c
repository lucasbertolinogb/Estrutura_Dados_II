#include <stdio.h>
#include <stdlib.h>

#define T 2  // Ordem mínima da árvore. Cada nó tem no mínimo T-1 chaves e no máximo 2*T-1 chaves.

struct arvoreB {
    int *chave;
    int grau;
    struct arvoreB **C;
    int n;
    int folha;
};

// Função para criar um novo nó da Árvore B
struct arvoreB *criarNo(int grau, int folha) {
    struct arvoreB *no = (struct arvoreB *)malloc(sizeof(struct arvoreB));
    
    no->grau = grau;
    no->folha = folha;
    no->chave = (int *)malloc((2 * grau - 1) * sizeof(int));
    
    no->C = (struct arvoreB **)malloc((2 * grau) * sizeof(struct arvoreB *));
    no->n = 0;
    return no;
}

// Função para dividir o filho `y` de um nó `no`
void dividir(struct arvoreB *no, int i, struct arvoreB *y) {
    struct arvoreB *z = criarNo(y->grau, y->folha);
    z->n = y->grau - 1;

    for (int j = 0; j < y->grau - 1; j++)
        {
        z->chave[j] = y->chave[j + y->grau];
        }

    if (!y->folha) 
    {
        for (int j = 0; j < y->grau; j++)
            {
            z->C[j] = y->C[j + y->grau];
            }
    }

    y->n = y->grau - 1;
    
    for (int j = no->n; j >= i + 1; j--)
        {
        no->C[j + 1] = no->C[j];
        }
    
    no->C[i + 1] = z;
    
    for (int j = no->n - 1; j >= i; j--)
        {
        no->chave[j + 1] = no->chave[j];
        }

    no->chave[i] = y->chave[y->grau - 1];
    no->n += 1;
}

// Função para inserir uma nova chave em um nó não cheio
void inserirNaoCheio(struct arvoreB *no, int k) {
    int i = no->n - 1;

    if (no->folha) 
    {
        while (i >= 0 && no->chave[i] > k) 
        {
            no->chave[i + 1] = no->chave[i];
            i--;
        }
        no->chave[i + 1] = k;
        no->n++;
    } else {
        while (i >= 0 && no->chave[i] > k)
            {
            i--;        
            }

        i++;
        if (no->C[i]->n == 2 * no->grau - 1) 
        {
            dividir(no, i, no->C[i]);
            if (no->chave[i] < k)
                i++;
        }
        inserirNaoCheio(no->C[i], k);
    }
}

// Função de inserção para a Árvore B
struct arvoreB *inserir(struct arvoreB *raiz, int k) {
    if (raiz->n == 2 * T - 1) 
    {
        struct arvoreB *s = criarNo(T, 0);
        s->C[0] = raiz;
        dividir(s, 0, raiz);
        inserirNaoCheio(s, k);
        return s;
    } else {
        inserirNaoCheio(raiz, k);
        return raiz;
           }
}

// Função para percorrer a árvore B
void percorrer(struct arvoreB *no) {
    for (int i = 0; i < no->n; i++) 
    {
        if (!no->folha)
            percorrer(no->C[i]);
        printf("%d ", no->chave[i]);
    }
    if (!no->folha)
        percorrer(no->C[no->n]);
}

// Função para liberar a memória da árvore B
void liberarArvore(struct arvoreB *no) {
    if (no) 
    {
        if (!no->folha) 
        {
            for (int i = 0; i <= no->n; i++)
                {
                liberarArvore(no->C[i]);
                }
        }
        free(no->chave);
        free(no->C);
        free(no);
    }
}

int main() {
    struct arvoreB *raiz = criarNo(T, 1);

    int valores[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        {
        raiz = inserir(raiz, valores[i]);
        }

    printf("Traversal da árvore B: ");
    percorrer(raiz);
    printf("\n");

    liberarArvore(raiz);  // Libera a memória alocada para a árvore
    return 0;
}
