#include <stdio.h>
#define MAX 50
#define true 1;
#define false 0;

typedef int bool;
typedef int TIPOCHAVE;

typedef struct
{
  TIPOCHAVE chave;
} REGISTRO;

typedef struct
{
  REGISTRO A[MAX];
  int nroElem;
} LISTA;

void inicializarLista(LISTA *l)
{
  l->nroElem = 0;
}

int tamanho(LISTA *l)
{
  return l->nroElem;
}

void exibirLista(LISTA *l)
{
  int i;
  printf("Lista: \" ");
  for (i = 0; i < l->nroElem; i++) {
    printf("%i ", l->A[i].chave);
  }
  printf("\"\n");
}

int buscaSequencial(LISTA* l, TIPOCHAVE ch) {
  int i = 0;
  while (i < l->nroElem) {
    if (ch == l->A[i].chave) return i;
    else i++;
  }
  return -1;
}

bool inserirElemLista(LISTA* l, REGISTRO reg, int i) {
  int j;
  if ((l->nroElem == MAX) || (i < 0) || (i > l->nroElem)) {
    return false;
  }
  for (j=l->nroElem; j > i; j--) l->A[j] = l->A[j-1];
  l->A[i] = reg;
  l->nroElem++;
  return true;
}

bool excluirElemLista(LISTA* l, TIPOCHAVE ch) {
  int j, pos;
  pos = buscaSequencial(l, ch);

  if (pos == -1) return false;

  for (j = pos; j < l->nroElem - 1; j++) {
    l->A[j] = l->A[j+1];
  }
  l->nroElem--;
  return true;
}

void reinicializarLista(LISTA* l) {
  l->nroElem = 0;
}