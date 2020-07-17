#include <stdio.h>

#define MAX 50
#define INVALIDO -1

#define true 1;
#define false 0;

typedef int bool;

typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE ch;
} REGISTRO;

typedef struct{
  REGISTRO reg;
  int prox;
} ELEMENTO;

typedef struct {
  ELEMENTO A[MAX];
  int inicio;
  int dispo;
} LISTA;

void inicializarLista(LISTA* l) {
  int i;
  for (i=0; i<MAX-1; i++) {
    l->A[i].prox = i + 1;
  }
  l->A[MAX-1].prox = INVALIDO;
  l->inicio = INVALIDO;
  l->dispo = 0;
}

int tamanho(LISTA* l) {
  int i = l->inicio;
  int tam = 0;

  while(i != INVALIDO) {
    tam++;
    i = l->A[i].prox;
  }
  return tam;
}

void exibirLista(LISTA* l) {
  int i = l->inicio;
  printf("Lista: \" ");
  while(i != INVALIDO) {
    printf("%d ", l->A[i].reg.ch);
    i = l->A[i].prox;
  }
  printf("\"\n");
}

int buscaSequencialOrd(LISTA* l, TIPOCHAVE ch) {
  int i = l->inicio;
  while(i != INVALIDO && l->A[i].reg.ch < ch) {
    i = l->A[i].prox;
  }
  if (i != INVALIDO && l->A[i].reg.ch == ch) return i;
  else return INVALIDO;
}

int obterNo(LISTA* l) {
  int resultado = l->dispo;
  if (l->dispo != INVALIDO) {
    l->dispo = l->A[l->dispo].prox;
  }
  return resultado;
}

bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
  if (l->dispo == INVALIDO) return false;
  int ant = INVALIDO;
  int i = l->inicio;
  TIPOCHAVE ch = reg.ch;

  while((i != INVALIDO) && (l->A[i].reg.ch < ch)) {
    ant = i;
    i = l->A[i].prox;
  }
  
  if(i != INVALIDO && l->A[i].reg.ch == ch) return false;

  i = obterNo(l);
  l->A[i].reg = reg;

  if(ant == INVALIDO) {
    l->A[i].prox = l->inicio;
    l->inicio = i;
  } else {
    l->A[i].prox = l->A[ant].prox;
    l->A[ant].prox = i;
  }
  return true;
}

void devolverNo(LISTA* l, int j) {
  l->A[j].prox = l->dispo;
  l->dispo = j;
}

bool excluirElemLista(LISTA* l, TIPOCHAVE ch) {
  int ant = INVALIDO;
  int i = l->inicio;

  while((i != INVALIDO) && (l->A[i].reg.ch < ch)) {
    ant = 1;
    i = l->A[i].prox;
  }

  if ((i == INVALIDO) || (l->A[i].reg.ch != ch)) return false;
  if (ant == INVALIDO) l->inicio = l->A[i].prox;
  else l->A[ant].prox = l->A[i].prox;
  devolverNo(l, i);
  return true;
}

void reinicializarLista(LISTA* l) {
  inicializarLista(l);
}

int main() {
  LISTA lista;
  inicializarLista(&lista);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  REGISTRO reg;
  reg.ch = 9;
  inserirElemListaOrd(&lista,reg);
  reg.ch = 4;
  inserirElemListaOrd(&lista,reg);
  reg.ch = 12;
  inserirElemListaOrd(&lista,reg);
  reg.ch = 8;
  inserirElemListaOrd(&lista,reg);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));

  excluirElemLista(&lista, 8);
  printf("Chave 8 encontrada na posicao: %i do arranjo A.\n",buscaSequencialOrd(&lista,8));
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  return 0;
}