#include <stdio.h>

#define MAX 50
#define true 1;
#define false 0;

typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
} REGISTRO;

typedef struct {
  REGISTRO A[MAX];
  int topo;
} PILHA;

void inicializarPilha(PILHA* p) {
  p->topo = -1;
}

int tamanhoPilha(PILHA* p) {
  return p->topo + 1;
}

void exibirPilha(PILHA* p) {
  printf("Pilha: \" ");
  int i;
  for (i = p->topo; i >= 0; i--) {
    printf("%i ", p->A[i].chave);
  }
  printf("\"\n");
}

bool inserirElementoPilha(PILHA* p, REGISTRO reg) {
  if (p->topo >= MAX-1) return false;
  p->topo = p->topo + 1;
  p->A[p->topo] = reg;
  return true;
}

bool excluirElementoPilha(PILHA* p, REGISTRO* reg) {
  if (p->topo == -1) return false;
  *reg = p->A[p->topo];
  p->topo = p->topo - 1;
  return true;
}

void reinicializarPilha(PILHA* p) {
  p->topo = -1;
}

int main() {
  PILHA pilha;
  inicializarPilha(&pilha);
  exibirPilha(&pilha);
  printf("Numero de elementos na pilha: %i.\n",tamanhoPilha(&pilha));
  REGISTRO reg;
  reg.chave = 9;
  inserirElementoPilha(&pilha,reg);
  exibirPilha(&pilha);
  reg.chave = 4;
  inserirElementoPilha(&pilha,reg);
  exibirPilha(&pilha);
  reg.chave = 12;
  inserirElementoPilha(&pilha,reg);
  exibirPilha(&pilha);
  reg.chave = 8;
  inserirElementoPilha(&pilha,reg);
  exibirPilha(&pilha);
  printf("Numero de elementos na pilha: %i.\n",tamanhoPilha(&pilha));
  REGISTRO chaveExcluida;
  excluirElementoPilha(&pilha, &chaveExcluida);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirPilha(&pilha);
  printf("Numero de elementos na pilha: %i.\n",tamanhoPilha(&pilha));
  return 0;
}