#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

void inicilizaD(GRAFO *g, int *d, int *p, int s)
{
  int v;
  for (v = 0; v < g->vertices; v++)
  {
    d[v] = INT_MAX / 2;
    p[v] = -1;
  }
  d[s] = 0;
}

void relaxa(GRAFO *g, int *d, int *p, int u, int v)
{
  ADJACENCIA *ad = g->adj[u].cab;
  while (ad && ad->vertice != v)
    ad = ad->prox;

  if (ad)
  {
    if (d[v] > d[u] + ad->peso)
    {
      d[v] = d[u] + ad->peso;
      p[v] = u;
    }
  }
}

bool existeAberto(GRAFO *g, int *aberto)
{
  int i;
  for (i = 0; i < g->vertices; i++)
    if (aberto[i])
      return true;
  return false;
}

int menorDist(GRAFO *g, int *aberto, int *d)
{
  int i;
  for (i = 0; i < g->vertices; i++)
  {
    if (aberto[i])
      break;
  }
  if (i == g->vertices)
    return -1;
  int menor = i;

  for (i = menor + 1; i < g->vertices; i++)
  {
    if (aberto[i] && (d[menor] > d[i]))
      menor = i;
  }
  return menor;
}

int *dijkstra(GRAFO *g, int s)
{

  int *d = (int *)malloc(sizeof(int));
  int p[g->vertices];
  bool aberto[g->vertices];
  inicilizaD(g, d, p, s);

  int i;
  for (i = 0; i < g->vertices; i++)
  {
    aberto[i] = true;
  }

  while (existeAberto(g, aberto))
  {
    int u = menorDist(g, aberto, d);
    aberto[u] = false;
    ADJACENCIA *ad = g->adj[u].cab;
    while (ad)
    {
      relaxa(g, d, p, u, ad->vertice);
      ad = ad->prox;
    }
  }
  return d;
}

int main()
{
  GRAFO *gr = criaGrafo(6);

  criaAresta(gr, 0, 1, 10);
  criaAresta(gr, 0, 2, 5);
  criaAresta(gr, 2, 1, 3);
  criaAresta(gr, 1, 3, 1);
  criaAresta(gr, 2, 3, 8);
  criaAresta(gr, 2, 4, 2);
  criaAresta(gr, 4, 5, 6);
  criaAresta(gr, 3, 5, 4);
  criaAresta(gr, 3, 4, 4);

  int *r = dijkstra(gr, 0);

  int i;

  for (i = 0; i < gr->vertices; i++)
  {
    printf("D(v0 -> v%d) = %d\n", i, r[i]);
  }

  return 0;
}