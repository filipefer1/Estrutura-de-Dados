#include <stdio.h>

#define true 1
#define false 0
#define MAX 50

typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
} REGISTRO;

typedef struct {
  REGISTRO A[MAX];
  int inicio;
  int nroElem;
} FILA;

void inicializarFila(FILA* f) {
  f->inicio = 0;
  f->nroElem = 0;
}

int tamanhoFila(FILA* f) {
  return f->nroElem;
}

void exibirFila(FILA* f) {
  printf("Fila: \" ");
  int i = f->inicio;
  int temp;
  for (temp=0; temp < f->nroElem; temp++) {
    printf("%i ", f->A[i].chave);
    i = (i+1) % MAX;
  }

  printf("\"\n");
}

bool inserirElementoFila(FILA* f, REGISTRO reg) {
  if (f->nroElem >= MAX) return false;
  int posicao = (f->inicio + f->nroElem) % MAX;
  f->A[posicao] = reg;
  f->nroElem++;
  return true;
}

bool excluirElementoFila(FILA* f, REGISTRO* reg) {
  if (f->nroElem == 0) return false;
  *reg = f->A[f->inicio];
  f->inicio = (f->inicio + 1) % MAX;
  f->nroElem--;
  return true;
}

void reinicializarFila(FILA* f) {
  inicializarFila(f);
}

int main() {
  FILA fila;
  inicializarFila(&fila);
  exibirFila(&fila);
  printf("Numero de elementos na fila: %i.\n",tamanhoFila(&fila));
  REGISTRO reg;
  reg.chave = 9;
  inserirElementoFila(&fila,reg);
  exibirFila(&fila);
  reg.chave = 4;
  inserirElementoFila(&fila,reg);
  exibirFila(&fila);
  reg.chave = 12;
  inserirElementoFila(&fila,reg);
  exibirFila(&fila);
  reg.chave = 8;
  inserirElementoFila(&fila,reg);
  exibirFila(&fila);
  printf("Numero de elementos na fila: %i.\n",tamanhoFila(&fila));
  REGISTRO chaveExcluida;
  excluirElementoFila(&fila, &chaveExcluida);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirFila(&fila);
  excluirElementoFila(&fila, &chaveExcluida);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirFila(&fila);
  excluirElementoFila(&fila, &chaveExcluida);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  printf("Numero de elementos na fila: %i.\n",tamanhoFila(&fila));
  printf("----Reinicialização da pilha----\n");
  reinicializarFila(&fila);
  printf("Numero de elementos na fila: %i.\n",tamanhoFila(&fila));
  return 0;
}