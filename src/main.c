#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/pilha.h"
#include "../include/grafo.h"


// Função auxiliar para remover o '\n' que o fgets coloca no final
void removerQuebraDeLinha(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Função auxiliar para limpar o buffer do teclado após um scanf
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // descarta caracteres até o fim da linha
    }
}

void exibirMenu(void) {
    printf("\n================ HISTORICO DE COMANDOS (PILHA) ================\n");
    printf("1 - Executar novo comando\n");
    printf("2 - Ver ultimo comando executado\n");
    printf("3 - Reexecutar ultimo comando\n");
    printf("4 - Listar historico completo\n");
    printf("5 - Remover ultimo comando do historico\n");
    printf("0 - Sair\n");
    printf("===============================================================\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    PilhaComandos historico;
    inicializarPilha(&historico);


    GrafoComandos grafo;           
    inicializarGrafo(&grafo);      

    char ultimoComando[MAX_TAM_COMANDO] = "";   
    int temUltimoComando = 0;                   

    int opcao;
    char comando[MAX_TAM_COMANDO];
    char bufferComando[MAX_TAM_COMANDO];

    do {
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada(); // limpa o '\n' que ficou no buffer

        switch (opcao) {
            case 1:
                 printf("\nDigite o comando que deseja executar: ");
                 if (fgets(comando, sizeof(comando), stdin) == NULL) {
                 printf("Erro na leitura do comando.\n");
                 break;
                 }
                 removerQuebraDeLinha(comando);

                if (strlen(comando) == 0) {
                printf("Comando vazio. Nada foi executado.\n");
                break;
                }

                // REGISTRAR TRANSIÇÃO NO GRAFO (se houver comando anterior)
                if (temUltimoComando) {
                registrarTransicao(&grafo, ultimoComando, comando);
                 }

                // ATUALIZAR ÚLTIMO COMANDO EXECUTADO
                strncpy(ultimoComando, comando, MAX_TAM_COMANDO - 1);
                ultimoComando[MAX_TAM_COMANDO - 1] = '\0';
                temUltimoComando = 1;

                if (!pushComando(&historico, comando)) {
                 printf("Historico cheio! Nao foi possivel armazenar o comando.\n");
                } else {
                printf("Executando comando: %s\n", comando);
                }

                system(comando);
                break;

            case 2:
                if (!peekComando(&historico, bufferComando)) {
                    printf("\nNao ha comandos no historico.\n");
                } else {
                    printf("\nUltimo comando executado: %s\n", bufferComando);
                }
                break;

            case 3:
                if (!peekComando(&historico, bufferComando)) {
                printf("\nNao ha comandos para reexecutar.\n");
                } else {
                // REGISTRAR TRANSIÇÃO NO GRAFO
                if (temUltimoComando) {
                registrarTransicao(&grafo, ultimoComando, bufferComando);
                }

                // ATUALIZAR ÚLTIMO COMANDO
                strncpy(ultimoComando, bufferComando, MAX_TAM_COMANDO - 1);
                ultimoComando[MAX_TAM_COMANDO - 1] = '\0';
                temUltimoComando = 1;

                // Empilhar novamente
                if (!pushComando(&historico, bufferComando)) {
                printf("\nHistorico cheio! Nao foi possivel registrar a reexecucao.\n");
                } else {
                printf("\nReexecutando comando: %s\n", bufferComando);
                }

                system(bufferComando);
                }
                break;

            case 4:
                listarHistorico(&historico);
                break;

            case 5:
                if (!popComando(&historico, bufferComando)) {
                    printf("\nNao ha comandos para remover.\n");
                } else {
                    printf("\nComando removido do historico: %s\n", bufferComando);
                }
                break;

            case 0:
                printf("\nSaindo do programa. Ate mais!\n");
                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}