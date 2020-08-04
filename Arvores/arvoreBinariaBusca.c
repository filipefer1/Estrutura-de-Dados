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

PONT contem(TIPOCHAVE ch, PONT raiz) {
  if (raiz == NULL) return NULL;
  if (raiz->chave == ch) return raiz;
  if (raiz->chave > ch) 
    return contem(ch, raiz->esq);
  return contem(ch, raiz->dir);
}

int numeroNos(PONT raiz) {
  // busca do tipo esquerda-raiz-direita, também conhecida como varredura central
  if (!raiz) return 0;
  return numeroNos(raiz->esq) + 1 + numeroNos(raiz->dir);
}

void exibirArvore(PONT raiz) {
  if (raiz != NULL) {
    printf("%i", raiz->chave);
    printf("(");
    exibirArvore(raiz->esq);
    exibirArvore(raiz->dir);
    printf(")");
  }
} 

int main() {
  PONT r = inicializa();
  PONT no = criaNovoNo(23);
  r = adiciona(r, no);
  no = criaNovoNo(12);
  r = adiciona(r, no);
  no = criaNovoNo(8);
  r = adiciona(r, no);
  no = criaNovoNo(14);
  r = adiciona(r, no);
  no = criaNovoNo(25);
  r = adiciona(r, no);
  no = criaNovoNo(32);
  r = adiciona(r, no);
  no = criaNovoNo(41);
  r = adiciona(r, no);
  no = criaNovoNo(5);
  r = adiciona(r, no);
  no = criaNovoNo(21);
  r = adiciona(r, no);

  PONT c = contem(5, r);
  printf("%i\n", c->chave);
  printf("%d\n", numeroNos(r));
  exibirArvore(r);
};
