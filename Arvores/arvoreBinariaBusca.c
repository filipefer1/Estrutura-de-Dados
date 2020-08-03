#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct aux {
  TIPOCHAVE chave;
  struct aux *esq, *dir;
} NO;

typedef NO* PONT;

PONT inicializa() {
  return NULL;
};


PONT adiciona(PONT raiz, PONT no) {
  if (raiz == NULL) return no;
  if(no->chave < raiz->chave) {
    raiz->esq = adiciona(raiz->esq, no);
  } else {
    raiz->dir = adiciona(raiz->dir, no);
  }
  return raiz;
}

PONT criaNovoNo(TIPOCHAVE ch) {
  PONT novoNo = (PONT) malloc(sizeof(NO));
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  novoNo->chave = ch;
  return novoNo;
}

int main() {
  PONT r = inicializa();
  PONT no = criaNovoNo(23);
  r = adiciona(r, no);
  no = criaNovoNo(12);
  r = adiciona(r, no);
};
