#include <stdio.h>
#include <malloc.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct {
  TIPOCHAVE chave;
} REGISTRO;

typedef struct auxElem {
  REGISTRO reg;
  struct auxElem* ant;
  struct auxElem* prox;
}ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
  PONT cabeca;
} DEQUE;

void inicializarDeque(DEQUE* d) {
  d->cabeca = (PONT) malloc(sizeof(ELEMENTO));
  d->cabeca->ant = d->cabeca;
  d->cabeca->prox = d->cabeca;
}

int tamanho(DEQUE* d) {
  PONT end = d->cabeca->prox;
  int tam = 0;

  while (end != d->cabeca) {
    tam++;
    end = end->prox;
  }
  return tam;
}

void exibirDequeFim(DEQUE* d) {
  PONT end = d->cabeca->ant;

  printf("Deque partindo do fim: \" ");
  while(end != d->cabeca) {
    printf("%i ", end->reg.chave);
    end = end->ant;
  }

  printf("\"\n");
}

bool inserirDequeFim(DEQUE* d, REGISTRO reg) {
  PONT i = (PONT) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  i->prox = d->cabeca;
  i->ant = d->cabeca->ant;
  d->cabeca->ant = i;
  i->ant->prox = i;
  return true;
}

bool inserirDequeInicio(DEQUE* d, REGISTRO reg) {
  PONT i = (PONT) malloc(sizeof(ELEMENTO));
  i->reg = reg;
  i->ant = d->cabeca;
  i->prox = d->cabeca->prox;
  d->cabeca->prox = i;
  i->prox->ant = i;
  return true;
}

bool excluirElemDequeInicio(DEQUE* d, REGISTRO* reg) {
  if (d->cabeca->prox == d->cabeca) return false;
  PONT apagar = d->cabeca->prox;
  *reg = apagar->reg;
  d->cabeca->prox = apagar->prox;
  apagar->prox->ant = d->cabeca;
  free(apagar);
  return true;
}

bool excluirElemDequeFim(DEQUE* d, REGISTRO* reg) {
  if (d->cabeca->prox == d->cabeca) return false;
  PONT apagar = d->cabeca->ant;
  *reg = apagar->reg;
  d->cabeca->ant = apagar->ant;
  apagar->ant->prox = d->cabeca;
  free(apagar);
  return true;
} 

void reinicializarDeque(DEQUE* d) {
  PONT end = d->cabeca->prox;

  while (end != d->cabeca) {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  d->cabeca->prox = d->cabeca;
  d->cabeca->ant = d->cabeca;
  
}

int main() {
  DEQUE deque;
  inicializarDeque(&deque);
  exibirDequeFim(&deque);
  printf("Numero de elementos no deque: %i.\n",tamanho(&deque));
  REGISTRO reg;
  reg.chave = 9;
  inserirDequeInicio(&deque,reg);
  exibirDequeFim(&deque);
  reg.chave = 4;
  inserirDequeFim(&deque,reg);
  exibirDequeFim(&deque);
  reg.chave = 12;
  inserirDequeFim(&deque,reg);
  exibirDequeFim(&deque);
  reg.chave = 8;
  inserirDequeFim(&deque,reg);
  exibirDequeFim(&deque);
  printf("Numero de elementos no deque: %i.\n",tamanho(&deque));
  REGISTRO chaveExcluida;
  excluirElemDequeFim(&deque, &chaveExcluida);
  printf("Item excluído: %i \n", chaveExcluida.chave);
  exibirDequeFim(&deque);
  printf("Numero de elementos no deque: %i.\n",tamanho(&deque));
  printf("----Reinicialização da pilha----\n");
  reinicializarDeque(&deque);
  printf("Numero de elementos no deque: %i.\n",tamanho(&deque));
  return 0;
}