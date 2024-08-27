#include <stdio.h>
#include <stdlib.h>

// NOME: LUCAS BERTOLINO SANTOS COSTA 
// TURMA: CC6M 
// MATÉRIA: Estrutua de dados II

//Atividade a ser feita =>
/*• Crie em C a estrutura de uma árvore binária cuja 
* informação seja um inteiro.
*Escreva funções que recebam um ponteiro para a raiz da 
* árvore AVL e façam:
• Função de balanceamento;
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
  }    
  else // caso existe mais uma altura a função percorre o caminho da esquerda
  {
    tamanho_esquerda = verificar_arvore_altura(arvore->esquerda);
    
  }

  if (arvore->direita == NULL) {
    // para de buscar altura
  }    
  else // caso existe mais uma altura a função percorre o caminho da direita
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
arvore  *criar_arvore(int informacao) {
  // Aqui teremos o ponteiro para a raiz da árvore, ou
  // seja, o primeiro elemento da árvore
  arvore *novo_no = (arvore *)malloc(sizeof(struct Arvore));
  // caso já exista um elemento na árvore, ele é
  // descartado esta função
  if (novo_no == NULL) 
  {
    printf("Erro: Falha ao alocar memória para o novo nó.\n");
    // peguei do professor que é uma função para sair 
    // do programa
    // (se funciona não tem pq mexer nele)
    exit(-1);
  }

  //aqui iria criar a arvore e suas ramificações 
  novo_no->informacao = informacao;
  novo_no->esquerda = NULL;
  novo_no->direita = NULL;
  return novo_no;
}

arvore *inserir_arvore(arvore *arvore, int valor) {
  // caso não exista uma arvore este valor se torna a 
  // raiz
  if (arvore == NULL)
    criar_arvore(valor);
  else {
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
  if (arvore->informacao == valor)
  {
    printf("Valor encontrado: %d\n", valor);
    return 1; 
  }

  // caso contrario vamos ver se o valor é menor ou 
  // maior levando ela para a esquerda(menor) ou 
  // direita(maior)
  if (arvore->informacao < valor)
  {
  return busca_binaria(arvore->esquerda, valor);
  }
    else
    {
      return busca_binaria(arvore->direita, valor);
    }
  
}

// função auxiliar para a função principal 
// retirar arvore 
int maior_valor(arvore *arvore)
{
  // tem como ação encontrar o maior valor da arvore
  // no meu caso é a direita
  while (arvore->direita != NULL)
      arvore = arvore->direita;
  return arvore;
}


// função principal para retirar um nó 
int retirar_arvore(arvore *arvore, int valor)
{
  // caso não exista a arvore
  if (arvore == NULL)
    return 0;

  // aqui faremos iqual a função binária para achar um 
  // valor
  if (valor < arvore->informacao)
    return retirar_arvore(arvore->esquerda, valor);
  else
  {
    if (valor > arvore->informacao)
      return retirar_arvore(arvore->direita, valor);
    else
    {
      // caso o valor seja encontrado
      // vamos verificar se ele tem filhos
      // caso não tenha filhos
      if (arvore->esquerda == NULL && arvore->direita == NULL)
      {
        // liberamos a memória
        free(arvore);
        // e retornamos 0
        return 0;
        
      }
      else
      {
        // caso tenha filhos
        // vamos verificar se ele tem filho a direita
        // ou a esquerda
        // caso tenha filho a direita
        if (arvore->esquerda == NULL)
        {
          // vamos pegar o filho a direita
          arvore *aux = arvore->direita;
          // e liberamos a memória
          free(arvore);
          // e retornamos o filho a direita
          return aux;
        }
        else
        {
          // caso tenha filho a esquerda
          if (arvore->direita == NULL)
          {
            // vamos pegar o filho a esquerda
            arvore *aux = arvore->esquerda;
            // e liberamos a memória
            free(arvore);
            // e retornamos o filho a esquerda
            return aux;
            
          }
          else
          {
            // caso tenha dois filhos
            // vamos pegar o maior valor da esquerda
            // e substituir o valor da arvore
            arvore->informacao = maior_valor(arvore->esquerda);
            // e retornamos o valor da arvore
            return arvore;
          }
          
        }
        
      }
      
    }
    
  } 
}

int mostrar_arvore(arvore *arvore)
{
  // caso não exista a arvore
  if (arvore == NULL)
    return 0;
  // aqui vamos mostrar a arvore em ordem crescente
  // primeiro a esquerda
  
  
}


int main(void) {
  struct Arvore *arvore = NULL;

  arvore = inserir_arvore(arvore, 5);
  arvore = inserir_arvore(arvore, 1);
  arvore = inserir_arvore(arvore, 2);
  arvore = inserir_arvore(arvore, 3);
  arvore = inserir_arvore(arvore, 4);
  arvore = inserir_arvore(arvore, 6);
  arvore = inserir_arvore(arvore, 7);
  arvore = inserir_arvore(arvore, 8);
  arvore = inserir_arvore(arvore, 9);

  printf("Hello World\n");
  return 0;
}
