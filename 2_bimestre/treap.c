#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct treap
{
    int dado, prioridade;
    struct treap *pai, *esq, *dir;
}Treap;


Treap* novoNo(int dado, int prioridade)
{
    Treap* novo = (Treap*)malloc(sizeof(Treap));
    novo->dado = dado;
    novo->prioridade = prioridade;
    novo->pai = novo->dir = novo->esq = NULL;
    return novo;
}

// Função para rotacionar à direita
Treap* rotacionarDireita(Treap* y) {
    Treap* x = y->esq;
    y->esq = x->dir;
    if (x->dir != NULL) {
        x->dir->pai = y;
    }
    x->pai = y->pai;
    x->dir = y;
    y->pai = x;
    return x;
}

// Função para rotacionar à esquerda
Treap* rotacionarEsquerda(Treap* x) {
    Treap* y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULL) {
        y->esq->pai = x;
    }
    y->pai = x->pai;
    y->esq = x;
    x->pai = y;
    return y;
}

// Função de inserção
Treap* inserir(Treap* raiz, int dado, int prioridade) {
    if (raiz == NULL) {
        return novoNo(dado, prioridade);
    }

    if (dado < raiz->dado) {
        raiz->esq = inserir(raiz->esq, dado, prioridade);
        raiz->esq->pai = raiz;
        
        if (raiz->esq->prioridade > raiz->prioridade) {
            raiz = rotacionarDireita(raiz);
        }
    } else {
        raiz->dir = inserir(raiz->dir, dado, prioridade);
        raiz->dir->pai = raiz;
        
        if (raiz->dir->prioridade > raiz->prioridade) {
            raiz = rotacionarEsquerda(raiz);
        }
    }
    
    return raiz;
}

// Função para imprimir a treap em ordem
void imprimirTreap(Treap* raiz) {
    if (raiz != NULL) {
        imprimirTreap(raiz->esq);
        printf("Dado: %d, Prioridade: %d\n", raiz->dado, raiz->prioridade);
        imprimirTreap(raiz->dir);
    }
}

void pre_ordem(Treap* raiz) { //RED
    if (raiz != NULL) {
        printf("Dado: %d, Prioridade: %d\n", raiz->dado, raiz->prioridade);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }
}


// Função principal
int main() {
    srand(time(NULL)); // Para gerar prioridades aleatórias
    Treap* raiz = NULL;
    
    // Inserindo elementos na treap
    raiz = inserir(raiz, 30, rand() % 100);
    raiz = inserir(raiz, 20, rand() % 100);
    raiz = inserir(raiz, 40, rand() % 100);
    raiz = inserir(raiz, 10, rand() % 100);
    raiz = inserir(raiz, 25, rand() % 100);
    
    // Imprimindo a treap
    printf("Treap em ordem:\n");
    imprimirTreap(raiz);

    printf("\n");
    
    printf("Treap em pre ordem:\n");
    pre_ordem(raiz);
    
    // Liberar memória (implementação de liberação de memória não incluída)
    
    return 0;
}
