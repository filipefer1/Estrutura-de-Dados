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
} ELEMENTO, * PONT;

typedef struct {
  PONT inicio;
  PONT fim;
} FILA;

void inicializarFila(FILA* f) {
  f->inicio = NULL;
  f->fim = NULL;
}

int tamanhoFila(FILA* f) {
  PONT end = f->inicio;
  int tam = 0;

  while(end != NULL) {
    tam++;
    end = end->prox;
  }
  return tam;
}

void exibirFila(FILA* f) {
  PONT end = f->inicio;
  printf("Lista: \" ");
  while(end != NULL) {
    printf("%i ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
}

bool inserirNaFila(FILA* f, REGISTRO reg){
  PONT novo = (PONT) malloc(sizeof(ELEMENTO));
  novo->reg = reg;
  novo->prox = NULL;
  if (f->inicio == NULL) f->inicio = novo;
  else f->fim->prox = novo;
  f->fim = novo;
  return true;
}

bool excluirDaFila(FILA* f, REGISTRO* reg) {
  if (f->inicio == NULL) return false;
  *reg = f->inicio->reg;
  PONT apagar = f->inicio;
  f->inicio = f->inicio->prox;
  free(apagar);
  return true;
}

void reinicializarFila(FILA* f) {
  PONT end = f->inicio;
  while(end != NULL) {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  f->inicio = NULL;
  f->fim = NULL;
}

int main() {
  FILA fila;
  inicializarFila(&fila);
  exibirFila(&fila);
  printf("Numero de elementos na fila: %i.\n",tamanhoFila(&fila));
  REGISTRO reg;
  reg.chave = 9;
  inserirNaFila(&fila,reg);
  exibirFila(&fila);
  reg.chave = 4;
  inserirNaFila(&fila,reg);
  exibirFila(&fila);
  reg.chave = 12;
  inserirNaFila(&fila,reg);
  exibirFila(&fila);
  reg.chave = 8;
  inserirNaFila(&fila,reg);
  exibirFila(&fila);
  printf("Numero de elementos na fila: %i.\n",tamanhoFila(&fila));
  REGISTRO chaveExcluida;
  excluirDaFila(&fila, &chaveExcluida);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirFila(&fila);
  excluirDaFila(&fila, &chaveExcluida);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirFila(&fila);
  excluirDaFila(&fila, &chaveExcluida);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  printf("Numero de elementos na fila: %i.\n",tamanhoFila(&fila));
  printf("----Reinicialização da pilha----\n");
  reinicializarFila(&fila);
  printf("Numero de elementos na fila: %i.\n",tamanhoFila(&fila));
  return 0;
}