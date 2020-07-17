#include <stdio.h>
#include <malloc.h>

#define false 0;
#define true 1;

typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
} REGISTRO;

typedef struct tempRegistro {
  REGISTRO reg;
  struct tempRegistro* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
  PONT cabeca;
} LISTA;

void inicializarLista(LISTA* l) {
  l->cabeca = (PONT) malloc(sizeof(ELEMENTO));
  l->cabeca->prox = l->cabeca;
}

int tamanho(LISTA* l) {
  PONT end = l->cabeca->prox;
  int tam = 0;

  while(end != l->cabeca) {
    tam++;
    end = end->prox;
  }
  return tam;
}

void exibirLista(LISTA* l) {
  PONT end = l->cabeca->prox;

  printf("Lista: \" ");
  while(end != l->cabeca) {
    printf("%d ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
}

PONT buscaSentinela(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->cabeca->prox;
  l->cabeca->reg.chave = ch;

  while(pos->reg.chave != ch) pos = pos->prox;
  if(pos != l->cabeca) return pos;
  return NULL;
}

PONT buscaSentinelaOrd(LISTA* l, TIPOCHAVE ch) {
  PONT pos = l->cabeca->prox;
  l->cabeca->reg.chave = ch;

  while(pos->reg.chave < ch) pos = pos->prox;
  if(pos != l->cabeca && pos->reg.chave == ch) return pos;
  return NULL;
}

PONT buscaSeqExc(LISTA* l, TIPOCHAVE ch, PONT* ant) {
  *ant = l->cabeca;
  PONT atual = l->cabeca->prox;

  l->cabeca->reg.chave = ch;

  while(atual->reg.chave < ch) {
    *ant = atual;
    atual = atual->prox;
  }

  if(atual != l->cabeca && atual->reg.chave == ch) return atual;
  return NULL;
}

bool inserirElemListaOrd(LISTA* l, REGISTRO reg) {
  PONT ant, i;
  i = buscaSeqExc(l, reg.chave, &ant);

  if (i != NULL) return false;

  i = (PONT) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  i->prox = ant->prox;
  ant->prox = i;
  return true;
}

bool excluirElemLista(LISTA* l, TIPOCHAVE ch) {
  PONT ant, i;
  i = buscaSeqExc(l, ch, &ant);

  if (i == NULL) return false;

  ant->prox = i->prox;
  free(i);
  return true;
}

void reinicializarLista(LISTA* l) {
  PONT end = l->cabeca->prox;
  while(end != l->cabeca) {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  l->cabeca->prox = l->cabeca;
}

int main() {
  LISTA lista;
  inicializarLista(&lista);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  REGISTRO reg;
  reg.chave = 9;
  inserirElemListaOrd(&lista,reg);
  reg.chave = 4;
  inserirElemListaOrd(&lista,reg);
  reg.chave = 12;
  inserirElemListaOrd(&lista,reg);
  reg.chave = 8;
  inserirElemListaOrd(&lista,reg);
  exibirLista(&lista);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));

  printf("Chave 8 encontrada no endereço: %p .\n",buscaSentinelaOrd(&lista,8));
  excluirElemLista(&lista, 8);
  printf("Numero de elementos na lista: %i.\n",tamanho(&lista));
  printf("Chave 8 encontrada no endereço: %p .\n",buscaSentinelaOrd(&lista,8));
  return 0;
}