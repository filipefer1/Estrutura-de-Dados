#include <stdio.h>
#include <malloc.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
} REGISTRO;

typedef struct aux {
  REGISTRO reg;
  struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
  PONT topo;
} PILHA;

void inicializarPilha(PILHA* p) {
  p->topo = NULL;
}

int tamanho(PILHA* p) {
  PONT end = p->topo;
  int tam = 0;

  while(end != NULL) {
    tam++;
    end = end->prox;
  }
  return tam;
}

bool estaVazia(PILHA* p) {
  if (p->topo == NULL) return true;
  return false;
}

void exibirPilha(PILHA* p) {
  PONT end = p->topo;

  printf("Pilha: \" ");
  while(end != NULL) {
    printf("%i ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
}

bool inserirElemPilha(PILHA* p, REGISTRO reg) {
  PONT novo = (PONT) malloc(sizeof(ELEMENTO));
  novo->reg = reg;
  novo->prox = p->topo;
  p->topo = novo;
  return true;
}

bool excluirElemPilha(PILHA* p, REGISTRO* reg) {
  if (p->topo == NULL) return false;
  *reg = p->topo->reg;
  PONT apagar = p->topo;
  p->topo = p->topo->prox;
  free(apagar);
  return true;
}

void reinicializarPilha(PILHA* p) {
  PONT apagar;
  PONT posicao = p->topo;

  while(posicao != NULL) {
    apagar = posicao;
    posicao = posicao->prox;
    free(apagar);
  }
  p->topo = NULL;
}

int main() {
  PILHA pilha;
  bool vazia;
  inicializarPilha(&pilha);
  exibirPilha(&pilha);
  printf("Numero de elementos na pilha: %i.\n",tamanho(&pilha));
  vazia = estaVazia(&pilha);
  printf("A pilha está vazia? %d \n", vazia);
  REGISTRO reg;
  reg.chave = 9;
  inserirElemPilha(&pilha,reg);
  exibirPilha(&pilha);
  reg.chave = 4;
  inserirElemPilha(&pilha,reg);
  exibirPilha(&pilha);
  reg.chave = 12;
  inserirElemPilha(&pilha,reg);
  exibirPilha(&pilha);
  reg.chave = 8;
  inserirElemPilha(&pilha,reg);
  exibirPilha(&pilha);
  printf("Numero de elementos na pilha: %i.\n",tamanho(&pilha));
  REGISTRO chaveExcluida;
  excluirElemPilha(&pilha, &chaveExcluida);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirPilha(&pilha);
  printf("Numero de elementos na pilha: %i.\n",tamanho(&pilha));
  vazia = estaVazia(&pilha);
  printf("A pilha está vazia? %d \n", vazia);
  printf("----Reinicialização da pilha----\n");
  reinicializarPilha(&pilha);
  printf("Numero de elementos na pilha: %i.\n",tamanho(&pilha));
  return 0;
}