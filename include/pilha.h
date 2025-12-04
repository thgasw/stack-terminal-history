#ifndef PILHA_H
#define PILHA_H

#define MAX_COMANDOS 100        // Quantidade máxima de comandos no histórico
#define MAX_TAM_COMANDO 128     // Tamanho máximo de cada comando (caracteres)

typedef struct {
    char comandos[MAX_COMANDOS][MAX_TAM_COMANDO];
    int topo; // índice do topo da pilha (-1 significa vazia)
} PilhaComandos;

/**
 * Inicializa a pilha, definindo topo = -1.
 */
void inicializarPilha(PilhaComandos *p);

/**
 * Retorna 1 se a pilha estiver vazia, 0 caso contrário.
 */
int pilhaVazia(const PilhaComandos *p);

/**
 * Retorna 1 se a pilha estiver cheia, 0 caso contrário.
 */
int pilhaCheia(const PilhaComandos *p);

/**
 * Empilha um novo comando.
 * Retorna 1 em caso de sucesso, 0 se a pilha estiver cheia.
 */
int pushComando(PilhaComandos *p, const char *comando);

/**
 * Desempilha o comando do topo.
 * Retorna 1 em caso de sucesso, 0 se a pilha estiver vazia.
 * O comando removido é copiado para o buffer dest.
 */
int popComando(PilhaComandos *p, char *dest);

/**
 * Copia o comando do topo sem removê-lo.
 * Retorna 1 em caso de sucesso, 0 se a pilha estiver vazia.
 */
int peekComando(const PilhaComandos *p, char *dest);

/**
 * Imprime todos os comandos da pilha,
 * do mais recente (topo) até o mais antigo (base).
 */
void listarHistorico(const PilhaComandos *p);

/**
 * Esvazia a pilha, definindo topo = -1.
 */
void limparPilha(PilhaComandos *p);

#endif // PILHA_H