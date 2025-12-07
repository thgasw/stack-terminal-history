#include <stdio.h>
#include <string.h>
#include "../include/grafo.h"

void inicializarGrafo(GrafoComandos *g) {
    g->qtd_nos = 0;
}

int buscarNo(const GrafoComandos *g, const char *comando) {
    for (int i = 0; i < g->qtd_nos; i++) {
        if (strcmp(g->nos[i].comando, comando) == 0) {
            return i;
        }
    }
    return -1;
}

int adicionarNo(GrafoComandos *g, const char *comando) {
    int idx = buscarNo(g, comando);
    if (idx != -1) {
        return idx; // já existe
    }

    if (g->qtd_nos == MAX_NOS) {
        return -1; // grafo cheio
    }

    idx = g->qtd_nos;
    strncpy(g->nos[idx].comando, comando, MAX_TAM_COMANDO - 1);
    g->nos[idx].comando[MAX_TAM_COMANDO - 1] = '\0';
    g->nos[idx].grau = 0;
    g->qtd_nos++;

    return idx;
}

void adicionarOuIncrementarAresta(GrafoComandos *g, int origem, int destino) {
    if (origem < 0 || destino < 0) return;

    NoGrafo *noOrigem = &g->nos[origem];

    // Verifica se já existe uma aresta origem -> destino
    for (int i = 0; i < noOrigem->grau; i++) {
        if (noOrigem->adj[i].destino == destino) {
            noOrigem->adj[i].peso++;
            return;
        }
    }

    // Se não existir, cria uma nova
    if (noOrigem->grau < MAX_NOS) {
        noOrigem->adj[noOrigem->grau].destino = destino;
        noOrigem->adj[noOrigem->grau].peso = 1;
        noOrigem->grau++;
    }
}

void registrarTransicao(GrafoComandos *g,
                        const char *comandoOrigem,
                        const char *comandoDestino) {
    if (comandoOrigem == NULL || comandoDestino == NULL) return;
    if (strlen(comandoOrigem) == 0 || strlen(comandoDestino) == 0) return;

    int idxOrigem = adicionarNo(g, comandoOrigem);
    int idxDestino = adicionarNo(g, comandoDestino);

    if (idxOrigem == -1 || idxDestino == -1) {
        printf("Nao foi possivel registrar transicao (grafo cheio).\n");
        return;
    }

    adicionarOuIncrementarAresta(g, idxOrigem, idxDestino);
}

void sugerirComandosPosteriores(const GrafoComandos *g,
                                const char *comandoBase) {
    int idx = buscarNo(g, comandoBase);
    if (idx == -1) {
        printf("\nO comando \"%s\" ainda nao possui transicoes registradas.\n",
               comandoBase);
        return;
    }

    NoGrafo no = g->nos[idx];

    if (no.grau == 0) {
        printf("\nO comando \"%s\" nao possui comandos posteriores registrados.\n",
               comandoBase);
        return;
    }

    printf("\nComandos mais provaveis apos \"%s\":\n", comandoBase);
    for (int i = 0; i < no.grau; i++) {
        int destIdx = no.adj[i].destino;
        int peso    = no.adj[i].peso;
        printf("- %s (ocorreu %d vez(es))\n",
               g->nos[destIdx].comando,
               peso);
    }
}

void mostrarTodasTransicoes(const GrafoComandos *g) {
    if (g->qtd_nos == 0) {
        printf("\nNenhum comando registrado no grafo ainda.\n");
        return;
    }

    printf("\nGrafo de transicoes entre comandos:\n");

    for (int i = 0; i < g->qtd_nos; i++) {
        NoGrafo no = g->nos[i];
        if (no.grau == 0) continue;

        printf("\nA partir do comando \"%s\":\n", no.comando);
        for (int j = 0; j < no.grau; j++) {
            int destIdx = no.adj[j].destino;
            int peso    = no.adj[j].peso;
            printf("  -> %s (ocorreu %d vez(es))\n",
                   g->nos[destIdx].comando,
                   peso);
        }
    }
}
