#include <stdio.h>
#include <string.h>
#include "../include/pilha.h"

void inicializarPilha(PilhaComandos *p) {
    p->topo = -1;
}

int pilhaVazia(const PilhaComandos *p) {
    return (p->topo == -1);
}

int pilhaCheia(const PilhaComandos *p) {
    return (p->topo == MAX_COMANDOS - 1);
}

int pushComando(PilhaComandos *p, const char *comando) {
    if (pilhaCheia(p)) {
        return 0; // falha: pilha cheia
    }

    p->topo++;
    // copia o comando para a posição do topo
    strncpy(p->comandos[p->topo], comando, MAX_TAM_COMANDO - 1);
    p->comandos[p->topo][MAX_TAM_COMANDO - 1] = '\0'; // garante terminação

    return 1; // sucesso
}

int popComando(PilhaComandos *p, char *dest) {
    if (pilhaVazia(p)) {
        return 0; // falha: pilha vazia
    }

    // copia o comando do topo para dest
    strncpy(dest, p->comandos[p->topo], MAX_TAM_COMANDO);
    dest[MAX_TAM_COMANDO - 1] = '\0'; // garante terminação

    p->topo--; // "remove" o elemento do topo
    return 1; // sucesso
}

int peekComando(const PilhaComandos *p, char *dest) {
    if (pilhaVazia(p)) {
        return 0; // falha: pilha vazia
    }

    strncpy(dest, p->comandos[p->topo], MAX_TAM_COMANDO);
    dest[MAX_TAM_COMANDO - 1] = '\0';

    return 1; // sucesso
}

void listarHistorico(const PilhaComandos *p) {
    if (pilhaVazia(p)) {
        printf("\nNenhum comando no historico ainda.\n");
        return;
    }

    printf("\nHistorico de comandos (do mais recente para o mais antigo):\n");

    for (int i = p->topo; i >= 0; i--) {
        printf("%2d) %s\n", p->topo - i + 1, p->comandos[i]);
    }
}

void limparPilha(PilhaComandos *p) {
    p->topo = -1;
}