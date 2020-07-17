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
  REGISTRO A[MAX + 1];
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

int tamanhoEmBytes(LISTA* l) {
  return sizeof(LISTA);
}

void exibirLista(LISTA *l)
{
  int i;
  printf("Lista: \" ");
  for (i = 0; i < l->nroElem; i++)
  {
    printf("%i ", l->A[i].chave);
  }
  printf("\"\n");
}

int buscaSequencial(LISTA *l, TIPOCHAVE ch)
{
  int i = 0;
  while (i < l->nroElem)
  {
    if (ch == l->A[i].chave)
      return i;
    else
      i++;
  }
  return -1;
}

int buscaSentinela(LISTA *l, TIPOCHAVE ch)
{
  int i = 0;
  l->A[l->nroElem].chave = ch;
  while (l->A[i].chave != ch)
    i++;
  if (i == l->nroElem)
    return -1;
  else
    return i;
}

int buscaBinaria(LISTA* l, TIPOCHAVE ch) {
  int dir, esq, meio;
  esq = 0;
  dir = l->nroElem - 1;

  while (esq <= dir) {
    meio = (esq + dir) / 2;
    printf("%i\n", meio);
    if (l->A[meio].chave == ch) return meio;
    else {
      if (l->A[meio].chave < ch) esq = meio + 1;
      else dir = meio - 1;
    }
  }
  return -1;
}

bool inserirElemLista(LISTA *l, REGISTRO reg, int i)
{
  int j;
  if ((l->nroElem == MAX) || (i < 0) || (i > l->nroElem))
  {
    return false;
  }
  for (j = l->nroElem; j > i; j--)
    l->A[j] = l->A[j - 1];
  l->A[i] = reg;
  l->nroElem++;
  return true;
}

bool inserirElemListaOrd(LISTA *l, REGISTRO reg)
{
  if (l->nroElem >= MAX)
    return false;
  int pos = l->nroElem;
  while (pos > 0 && l->A[pos - 1].chave > reg.chave)
  {
    l->A[pos] = l->A[pos - 1];
    pos--;
  }
  l->A[pos] = reg;
  l->nroElem++;
}

bool excluirElemLista(LISTA *l, TIPOCHAVE ch)
{
  int j, pos;
  /*pos = buscaSequencial(l, ch); */
  pos = buscaBinaria(l, ch);

  if (pos == -1)
    return false;

  for (j = pos; j < l->nroElem - 1; j++)
  {
    l->A[j] = l->A[j + 1];
  }
  l->nroElem--;
  return true;
}

void reinicializarLista(LISTA *l)
{
  l->nroElem = 0;
}

int main(){
    LISTA lista;
  inicializarLista(&lista);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i.\n",tamanhoEmBytes(&lista));
  REGISTRO reg;
  reg.chave = 9;
  inserirElemListaOrd(&lista,reg);
  exibirLista(&lista);
  reg.chave=3;
  inserirElemListaOrd(&lista,reg);
  reg.chave=4;
  inserirElemListaOrd(&lista,reg);
  reg.chave=1;
  inserirElemListaOrd(&lista,reg);
  reg.chave=12;
  inserirElemListaOrd(&lista,reg);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i.\n",tamanhoEmBytes(&lista));
  printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",buscaSequencial(&lista,4));
  printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",buscaBinaria(&lista,4));
  printf("Chave 4 encontrada na posicao: %i do arranjo A.\n",buscaSentinela(&lista,4));
  if (excluirElemLista(&lista,4)) printf("Exclusao bem sucedida: 4.\n");
  if (excluirElemLista(&lista,8)) printf("Exclusao bem sucedida: 8.\n");
  if (excluirElemLista(&lista,9)) printf("Exclusao bem sucedida: 9.\n");
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i.\n",tamanhoEmBytes(&lista));
  reinicializarLista(&lista);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  printf("Tamanho da lista (em bytes): %i.\n",tamanhoEmBytes(&lista));
  return 0;
}