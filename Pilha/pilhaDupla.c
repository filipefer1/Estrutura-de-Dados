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
  int topo1;
  int topo2;
} PILHADUPLA;

void inicializarPilhaDupla(PILHADUPLA* p) {
  p->topo1 = -1;
  p->topo2 = MAX;
}

int tamanhoPilhaDupla(PILHADUPLA* p) {
  return p->topo1+1 - MAX-p->topo2;
}

bool exibirUmaPilha(PILHADUPLA* p, int pilha) {
  if (pilha < 1 || pilha > 2) return false;
  printf("Pilha%i: \" ", pilha);
  int i;
  if (pilha == 1) for (i = p->topo1; i >= 0; i--) printf("%i ", p->A[i].chave);
  else for (i = p->topo2; i < MAX; i++) printf("%i ", p->A[i].chave);
  printf("\"\n");
  return true;
}

bool inserirElementoPilha(PILHADUPLA* p, REGISTRO reg, int pilha) {
  if (pilha < 1 || pilha > 2) return false;
  if (p->topo1 + 1 == p->topo2) return false;

  if (pilha == 1) {
    p->topo1 = p->topo1 + 1;
    p->A[p->topo1] = reg;
  } else {
    p->topo2 = p->topo2 - 1;
    p->A[p->topo2] = reg;
  }
  return true;
}

bool excluirElementoPilha(PILHADUPLA* p, REGISTRO* reg, int pilha) {
  if (pilha < 1 || pilha > 2) return false;
  if (pilha == 1) {
    if (p->topo1 == -1) return false;
    *reg = p->A[p->topo1];
    p->topo1 = p->topo1 - 1;
  } else {
    if (p->topo2 == MAX) return false;
    *reg = p->A[p->topo2];
    p->topo2 = p->topo2 + 1;
  }
  return true;
}

void reinicializarPilha(PILHADUPLA* p) {
  inicializarPilhaDupla(p);
}

int main() {
  PILHADUPLA pilha;
  inicializarPilhaDupla(&pilha);
  exibirUmaPilha(&pilha, 1);
  exibirUmaPilha(&pilha, 2);
  REGISTRO reg;
  reg.chave = 4;
  inserirElementoPilha(&pilha, reg, 1);
  exibirUmaPilha(&pilha, 1);
  reg.chave = 2;
  inserirElementoPilha(&pilha, reg, 2);
  exibirUmaPilha(&pilha, 2);
  reg.chave = 1;
  inserirElementoPilha(&pilha, reg, 1);
  exibirUmaPilha(&pilha, 1);
  reg.chave = 6;
  inserirElementoPilha(&pilha, reg, 1);
  exibirUmaPilha(&pilha, 1);
  reg.chave = 3;
  inserirElementoPilha(&pilha, reg, 2);
  exibirUmaPilha(&pilha, 2);
  reg.chave = 5;
  inserirElementoPilha(&pilha, reg, 2);
  exibirUmaPilha(&pilha, 2);
  REGISTRO chaveExcluida;
  excluirElementoPilha(&pilha, &chaveExcluida, 1);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirUmaPilha(&pilha, 1);
  excluirElementoPilha(&pilha, &chaveExcluida, 2);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirUmaPilha(&pilha, 2);
  excluirElementoPilha(&pilha, &chaveExcluida, 1);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirUmaPilha(&pilha, 1);
  printf("----Reinicialização da pilha----\n");
  reinicializarPilha(&pilha);
  exibirUmaPilha(&pilha, 1);
  exibirUmaPilha(&pilha, 2);
  
  return 0;
}