#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia
{
  int vertice;
  TIPOPESO peso;
  struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
  ADJACENCIA *cab;
} VERTICE;

typedef struct grafo
{
  int vertices;
  int arestas;
  VERTICE *adj;
} GRAFO;

typedef int TIPOCHAVE;

typedef struct
{
  TIPOCHAVE chave;
} REGISTRO;

typedef struct aux
{
  REGISTRO reg;
  struct aux *prox;
} ELEMENTO, *PONT;

typedef struct
{
  PONT inicio;
  PONT fim;
} FILA;

void inicializarFila(FILA *f)
{
  f->inicio = NULL;
  f->fim = NULL;
}

int tamanhoFila(FILA *f)
{
  PONT end = f->inicio;
  int tam = 0;

  while (end != NULL)
  {
    tam++;
    end = end->prox;
  }
  return tam;
}

void exibirFila(FILA *f)
{
  PONT end = f->inicio;
  printf("Lista: \" ");
  while (end != NULL)
  {
    printf("%i ", end->reg.chave);
    end = end->prox;
  }
  printf("\"\n");
}

bool inserirNaFila(FILA *f, REGISTRO reg)
{
  PONT novo = (PONT)malloc(sizeof(ELEMENTO));
  novo->reg = reg;
  novo->prox = NULL;
  if (f->inicio == NULL)
    f->inicio = novo;
  else
    f->fim->prox = novo;
  f->fim = novo;
  return true;
}

bool excluirDaFila(FILA *f, REGISTRO *reg)
{
  if (f->inicio == NULL)
    return false;
  *reg = f->inicio->reg;
  PONT apagar = f->inicio;
  f->inicio = f->inicio->prox;
  free(apagar);
  return true;
}

void reinicializarFila(FILA *f)
{
  PONT end = f->inicio;
  while (end != NULL)
  {
    PONT apagar = end;
    end = end->prox;
    free(apagar);
  }
  f->inicio = NULL;
  f->fim = NULL;
}

void visitaL(GRAFO *g, int s, bool *expl)
{
  FILA f;
  inicializarFila(&f);

  expl[s] = true;
  REGISTRO *u = (REGISTRO *)malloc(sizeof(REGISTRO));
  u->chave = s;
  inserirNaFila(&f, *u);
  exibirFila(&f);

  while (f.inicio)
  {
    excluirDaFila(&f, u);
    exibirFila(&f);
    ADJACENCIA *v = g->adj[u->chave].cab;

    while (v)
    {
      if (!expl[v->vertice])
      {
        expl[v->vertice] = true;
        u->chave = v->vertice;
        inserirNaFila(&f, *u);
        exibirFila(&f);
      }
      v = v->prox;
    }
  }
  free(u);
}

void largura(GRAFO *g)
{
  bool expl[g->vertices];

  int u;
  for (u = 0; u < g->vertices; u++)
  {
    expl[u] = false;
  }

  for (u = 0; u < g->vertices; u++)
  {
    if (!expl[u])
      visitaL(g, u, expl);
  }
}

GRAFO *criaGrafo(int v)
{
  GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
  g->vertices = v;
  g->arestas = 0;
  g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));

  int i;
  for (i = 0; i < v; i++)
  {
    g->adj[i].cab = NULL;
  }
  return g;
}

ADJACENCIA *criaAdj(int v, int peso)
{
  ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
  temp->vertice = v;
  temp->peso = peso;
  temp->prox = NULL;
  return temp;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p)
{
  if (!gr)
    return false;
  if ((vf < 0) || (vf >= gr->vertices))
    return false;
  if ((vi < 0) || (vi >= gr->vertices))
    return false;

  ADJACENCIA *novo = criaAdj(vf, p);
  novo->prox = gr->adj[vi].cab;
  gr->adj[vi].cab = novo;
  gr->arestas++;
  return true;
}

void imprime(GRAFO *gr)
{
  printf("Vértices: %d. Arestas: %d. \n", gr->vertices, gr->arestas);
  int i;
  for (i = 0; i < gr->vertices; i++)
  {
    printf("v%d: ", i);
    ADJACENCIA *ad = gr->adj[i].cab;
    while (ad)
    {
      printf("v%d(%d) ", ad->vertice, ad->peso);
      ad = ad->prox;
    }
    printf("\n");
  }
}

int main()
{
  GRAFO *gr = criaGrafo(5);

  criaAresta(gr, 0, 1, 2);
  criaAresta(gr, 1, 2, 4);
  criaAresta(gr, 2, 0, 12);
  criaAresta(gr, 2, 4, 40);
  criaAresta(gr, 3, 1, 3);
  criaAresta(gr, 4, 3, 8);

  largura(gr);

  imprime(gr);
  return 0;
}