#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct no {
  TIPOCHAVE chave;
  struct no *primFilho;
  struct no *proxIrmao;
} NO;

typedef NO* PONT;

PONT criaNovoNo(TIPOCHAVE ch) {
  PONT novo = (PONT) malloc(sizeof(NO));
  novo->chave = ch;
  novo->primFilho = NULL;
  novo->proxIrmao = NULL;
  return novo;
};

PONT inicializa(TIPOCHAVE ch) {
  return criaNovoNo(ch);
}

PONT buscaChave(TIPOCHAVE ch, PONT raiz) {
  if (raiz == NULL) return NULL;
  if (raiz->chave == ch) return raiz;
  PONT p = raiz->primFilho;
  while (p) {
    PONT resp = buscaChave(ch, p);
    if (resp) return resp;
    p = p->proxIrmao;
  }
  return NULL;
}

bool insere(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai) {
  PONT pai = buscaChave(chavePai, raiz);
  if (!pai) return false;
  PONT filho = criaNovoNo(novaChave);
  PONT p = pai->primFilho;
  if (!p) pai->primFilho = filho;
  else {
    while(p->proxIrmao)
      p = p->proxIrmao;
    p->proxIrmao = filho;
  }
  return true;
}

void exibirArvore(PONT raiz) {
  if (raiz == NULL) return;

  printf("%d(", raiz->chave);
  PONT p = raiz->primFilho;
  while(p) {
    exibirArvore(p);
    p = p->proxIrmao;
  }
  printf(")");
}

int main() {
  PONT r = inicializa(8);
  insere(r, 15, 8);
  insere(r, 23, 8);
  insere(r, 2, 8);
  insere(r, 20, 15);
  insere(r, 10, 15);
  insere(r, 28, 15);
  insere(r, 36, 2);
  insere(r, 7, 2);
  exibirArvore(r);
  return 0;
}