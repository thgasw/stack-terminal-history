#ifndef GRAFO_H
#define GRAFO_H

#include "pilha.h"   // para usar MAX_TAM_COMANDO

#define MAX_NOS 100  // quantidade máxima de comandos diferentes no grafo

typedef struct {
    int destino;    // índice do nó de destino
    int peso;       // quantas vezes essa transição aconteceu
} Aresta;

typedef struct {
    char comando[MAX_TAM_COMANDO]; // texto do comando (vértice)
    Aresta adj[MAX_NOS];           // lista de adjacência (arestas saindo)
    int grau;                      // quantas arestas saem deste nó
} NoGrafo;

typedef struct {
    NoGrafo nos[MAX_NOS];
    int qtd_nos;                   // quantidade de nós no grafo
} GrafoComandos;

// Inicializa o grafo, definindo qtd_nos = 0.
void inicializarGrafo(GrafoComandos *g);

// Busca o índice de um comando no grafo. Retorna o índice (0..qtd_nos-1) se encontrar, ou -1 se não existir.

int buscarNo(const GrafoComandos *g, const char *comando);

// Adiciona um novo nó para o comando informado. Retorna o índice do nó criado, ou -1 se o grafo estiver cheio. Se o comando já existir, apenas retorna o índice existente.
int adicionarNo(GrafoComandos *g, const char *comando);

// Adiciona uma aresta origem -> destino, ou incrementa o peso.se essa aresta já existir.

void adicionarOuIncrementarAresta(GrafoComandos *g, int origem, int destino);

// Função de conveniência: garante que os comandos de origem e destino.existam no grafo e registra a transição entre eles.
void registrarTransicao(GrafoComandos *g,
                        const char *comandoOrigem,
                        const char *comandoDestino);

// Mostra as transições de um comando específico (recomendações).

void sugerirComandosPosteriores(const GrafoComandos *g,
                                const char *comandoBase);

// Mostra todas as transições registradas no grafo.
void mostrarTodasTransicoes(const GrafoComandos *g);

#endif // GRAFO_H
