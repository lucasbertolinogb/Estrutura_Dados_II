#include <stdio.h>
#include <stdlib.h>

/*• Crie em C a estrutura de uma árvore binária cuja
* informação seja um inteiro.
*Escreva funções que recebam um ponteiro para a raiz da
* árvore AVL e façam:
• Inserção de um elemento na árvore;
• Pesquisa de um elemento na árvore;
• Exclusão de um elemento na árvore.
  */

// Criação da estrutura da árvore
typedef struct Arvore {
  struct Arvore *esquerda;
  struct Arvore *direita;
  int informacao;
} arvore;

// Verifica a altura da árvore
int verificar_arvore_altura(arvore *arvore) {
  // Se a árvore estiver vazia, retorna -1
  int tamanho_esquerda = -1, tamanho_direita = -1;
  if (arvore == NULL) // nao existe arvore
    return printf("Arvore nula");

  if (arvore->esquerda == NULL) {
    // para de buscar altura
  } else // caso existe mais uma altura a função percorre o caminho da esquerda
  {
    tamanho_esquerda = verificar_arvore_altura(arvore->esquerda);
  }

  if (arvore->direita == NULL) {
    // para de buscar altura
  } else // caso existe mais uma altura a função percorre o caminho da direita
  {
    tamanho_direita = verificar_arvore_altura(arvore->direita);
  }

  // se temos um tamanho arvore direita e esquerda
  // retornamos o maior valor, no caso, o
  // tamanho da arvore
  if (tamanho_esquerda > tamanho_direita)
    return tamanho_esquerda++;
  else
    return tamanho_direita++;

  // no final disso tudo deve retornar o tamanho da
  // arvore
}

// Criação da árvore
arvore *criar_arvore(int informacao) {
  // Aqui teremos o ponteiro para a raiz da árvore, ou
  // seja, o primeiro elemento da árvore
  arvore *novo_no = (arvore *)malloc(sizeof(struct Arvore));
  // caso já exista um elemento na árvore, ele é
  // descartado esta função
  if (novo_no == NULL) {
    printf("Erro: Falha ao alocar memória para o novo nó.\n");
    // peguei do professor que é uma função para sair
    // do programa
    // (se funciona não tem pq mexer nele)
    exit(-1);
  }

  // aqui iria criar a arvore e suas ramificações
  novo_no->informacao = informacao;
  novo_no->esquerda = NULL;
  novo_no->direita = NULL;
  return novo_no;
}

arvore *inserir_arvore(arvore *arvore, int valor) {
  // caso não exista uma arvore este valor se torna a
  // raiz
  if (arvore == NULL) {
    return criar_arvore(valor);
    exit(-1);
  } else {
    // agora vem de comparar o valor com o valor da raiz
    // separando ela por lado esquerdo ou direito
    // neste caso esquerda para valor menores que a raiz
    // e direita para valores maiores que a raiz
    if (valor < arvore->informacao)
      arvore->esquerda = inserir_arvore(arvore->esquerda, valor);
    else
      arvore->direita = inserir_arvore(arvore->direita, valor);
  }
  // finalizando com uma arvore retornada
  return arvore;
}

int busca_binaria(arvore *arvore, int valor) {
  // aqui seria quando o valor não exista na arvore
  if (arvore == NULL)
    return 0;

  // aqui encontramos o valor (facil de mais)
  if (arvore->informacao == valor) {
    printf("Valor encontrado: %d\n", valor);
    return 1;
  }

  // caso contrario vamos ver se o valor é menor ou
  // maior levando ela para a esquerda(menor) ou
  // direita(maior)
  if (arvore->informacao < valor) {
    return busca_binaria(arvore->esquerda, valor);
  } else {
    return busca_binaria(arvore->direita, valor);
  }
}

// função auxiliar para a função principal
// retirar arvore
int maior_valor(arvore *arvore) {
  // tem como ação encontrar o maior valor da arvore
  // no meu caso é a direita
  while (arvore->direita != NULL) {
    arvore = arvore->direita;
  }
  // retornamos o valor
  return arvore->informacao;
}

// Aqui é minha arvore auxiliar para retornar a arvore sem
// o nó desejado , ou seja, que já tenha a função de remover
// feita nela
arvore *aux;

// função principal para retirar um nó
arvore *retirar_arvore(arvore *arvore, int valor) {
  // caso não exista a arvore
  if (arvore == NULL) {
    printf("Arvore nula ou ausencia de valor");
    return NULL;
    // diferente dos outros casos que eu uso return
    // aqui usarei return NULL para indicar a ausência
    // de arvore ou sua retirada
  }

  // aqui faremos iqual a função binária para achar um
  // valor
  if (valor < arvore->informacao)
    arvore->esquerda = retirar_arvore(arvore->esquerda, valor);
  else if (valor > arvore->informacao)
    arvore->direita = retirar_arvore(arvore->direita, valor);
  else {
    // caso o valor seja encontrado
    // vamos verificar se ele tem filhos
    // caso não tenha filhos
    if (arvore->esquerda == NULL && arvore->direita == NULL) {
      // liberamos a memória
      free(arvore);
      // e retornamos a nó vazio
      return NULL;

    } else if (arvore->esquerda == NULL) {
      // caso tenha filhos
      // vamos verificar se ele tem filho a direita
      // ou a esquerda
      // caso tenha filho a direita
       
        // vamos pegar o filho a direita
        aux = arvore->direita;
        // e liberamos a memória
        free(arvore);
        // e retornamos o filho a direita
        return aux;
      } else if (arvore->direita == NULL){
        // caso tenha filho a esquerda
         
          // vamos pegar o filho a esquerda
          aux = arvore->esquerda;
          // e liberamos a memória
          free(arvore);
          // e retornamos o filho a esquerda
          return aux;

        } else {
          // caso tenha dois filhos
          // vamos pegar o maior valor da esquerda
          // e substituir o valor da arvore
          arvore->informacao = maior_valor(arvore->esquerda);
          // e com arvore->informação sendo o mairo valor
          // agora podemos retirar este nó

          arvore->esquerda =
              retirar_arvore(arvore->esquerda, arvore->informacao);
        }
      }
        return arvore;
}

void mostrar_arvore(arvore *arvore) {
  // caso não exista a arvore
  if (arvore == NULL)
    return;

  // obrigo a não retornar algo estranho da arvore
  if (arvore != NULL) {
    // peguei do professor que é uma função de retorno
    // em pré-ordem
    // explicação dela : pega a raiz , depois a esquerda e
    // finaliza com a direita (RED)
    printf("%d ", arvore->informacao);
    mostrar_arvore(arvore->esquerda);
    mostrar_arvore(arvore->direita);
  }
}

void pre_ordem(arvore *arvore) {
  // caso não exista a arvore
  if (arvore == NULL)
    return;

  if (arvore != NULL) {
    // peguei do professor que é uma função de retorno
    // em pré-ordem
    // explicação dela : pega a raiz , depois a esquerda e
    // finaliza com a direita (RED)
    printf("%d ", arvore->informacao);
    mostrar_arvore(arvore->esquerda);
    mostrar_arvore(arvore->direita);
  }
}
void em_ordem(arvore *arvore) {
  // caso não exista a arvore
  if (arvore == NULL)
    return;

  if (arvore != NULL) {
    // peguei do professor que é uma função de retorno
    // em pré-ordem
    // explicação dela : pega o mais a esquerda, raiz e depois
    // direita (ERD)
    mostrar_arvore(arvore->esquerda);
    printf("%d ", arvore->informacao);
    mostrar_arvore(arvore->direita);
  }
}

void pos_ordem(arvore *arvore) {
  // caso não exista a arvore
  if (arvore == NULL)
    return;

  if (arvore != NULL) {
    // peguei do professor que é uma função de retorno
    // em pré-ordem
    // explicação dela : pega esquerda , direita e raiz (EDR)
    mostrar_arvore(arvore->esquerda);
    mostrar_arvore(arvore->direita);
    printf("%d ", arvore->informacao);
  }
}

int main(void) {
  struct Arvore *arvore = NULL;

  // testando uma arvore simples
  printf("Teste 1:\n");
  arvore = inserir_arvore(arvore, 10);
  mostrar_arvore(arvore); // esperado 10
  printf("\n\n");

  // limpeza da arvore (mister clean clode :P)
  arvore = NULL;

  // testando um arvore com multiplos valores crescentes
  printf("Teste 2:\n");
  arvore = inserir_arvore(arvore, 7);
  arvore = inserir_arvore(arvore, 8);
  arvore = inserir_arvore(arvore, 9);
  arvore = inserir_arvore(arvore, 10);
  mostrar_arvore(arvore); // esperado 7 8 9 10
  printf("\n\n");

  // limpeza da arvore
  arvore = NULL;

  // Inserção de nos na arvore de modo aleatório
  printf("Teste 3:\n");

  /*
          9
        8     12
      7     10   13
              11
      resultado: 9, 8, 7, 12, 10, 11, 13
    */
  arvore = inserir_arvore(arvore, 9);
  arvore = inserir_arvore(arvore, 12);
  arvore = inserir_arvore(arvore, 8);
  arvore = inserir_arvore(arvore, 13);
  arvore = inserir_arvore(arvore, 7);
  arvore = inserir_arvore(arvore, 10);
  arvore = inserir_arvore(arvore, 11);
  mostrar_arvore(arvore);
  printf("\n\n");

  // usando a mesma arvore de antes
  // testando valor duplicado
  printf("Teste 4:\n");
  arvore = inserir_arvore(arvore, 9);
  mostrar_arvore(arvore); // esperado: 9, 8, 7, 12, 10, 9 , 11, 13
  /*
      9
    8     12
  7     10   13
       9  11

  */
  printf("\n\n");

  // Daqui em diante sera um caso de teste para remover_arvore
  // removendo nenhum filho existente
  printf("Teste 5:\n");
  retirar_arvore(arvore, 5);
  printf("\nArvore atual:\n");
  mostrar_arvore(arvore); // esperado  o mesmo do teste 4
  printf("\n\n");


  // removendo um filho
  printf("Teste 6:\n");
  retirar_arvore(arvore, 7);
  mostrar_arvore(arvore); // esperado: 9, 8, 12, 10,11, 13
  printf("\n\n");

  arvore = NULL;
  
  // teste para retirar nó com dois filhos
  printf("Teste 7:\n");

  arvore = inserir_arvore(arvore, 9);
  arvore = inserir_arvore(arvore, 12);
  arvore = inserir_arvore(arvore, 8);
  arvore = inserir_arvore(arvore, 13);
  arvore = inserir_arvore(arvore, 7);
  arvore = inserir_arvore(arvore, 10);
  /*
      9
    8     12
  7     10   13
  */
  retirar_arvore(arvore, 12);
  mostrar_arvore(arvore); // esperado: 9, 8, 7, 10, 13
  printf("\n\n");

  

  arvore = NULL;


  arvore = inserir_arvore(arvore, 9);
  arvore = inserir_arvore(arvore, 12);
  arvore = inserir_arvore(arvore, 8);
  arvore = inserir_arvore(arvore, 13);
  arvore = inserir_arvore(arvore, 7);
  arvore = inserir_arvore(arvore, 10);
  arvore = inserir_arvore(arvore, 11);

  /*
      9
    8     12
  7     10   13
          11
  */
  
  printf("Pre ordem: \n");
  pre_ordem(arvore); // 9,8,7,12,10,11,13
  printf("\n\n");

  printf("Em ordem: \n");
  em_ordem(arvore); // 7,8,9,12,10,11,13
  printf("\n\n");
  printf("Pos ordem: \n");
  pos_ordem(arvore);
  printf("\n\n");

  return 0;
}
