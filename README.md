# 📟 Terminal Command History -

Este projeto é uma simulação simples de um **histórico de comandos de terminal**, implementado usando a estrutura de dados **Pilha (Stack)**.  
Faz parte do trabalho final da disciplina de **Estrutura de Dados e Algoritmos**.

---

## 📌 Sobre o projeto

A aplicação permite que o usuário:

- Execute comandos (simulados)
- Guarde cada comando na pilha
- Veja o último comando executado
- Reexecute comandos recentes
- Liste todo o histórico armazenado
- Remova o último comando (pop)

A ideia é demonstrar, na prática, como a estrutura de pilha segue o princípio **LIFO (Last In, First Out)** e como ela pode ser usada para representar funções reais — como o histórico de comandos de um terminal.

---

## 📂 Estrutura de diretórios

/src
main.c # Arquivo principal com o menu da aplicação
pilha.c # Implementação das funções da pilha

/include

pilha.h # Definições, structs e assinaturas das funções

README.md # Documentação do projeto

---

## ▶️ Como rodar o projeto

Dentro do Codespaces ou qualquer ambiente com compilador C:

1. Compile o projeto:
   ```bash
   gcc src/main.c src/pilha.c -o terminal

2. Execute:
    ./terminal

---

## Objetivo acadêmico 🎓

Este projeto foi desenvolvido para o trabalho final da disciplina de Estruturas de Dados e Algoritmos, com o intuito de:

1. Aplicar a estrutura Pilha em um problema real

2. Demonstrar uso prático do modelo LIFO

3. Implementar operações fundamentais (push, pop, peek)

4. Estruturar o código em módulos (.c e .h)

5. Criar uma aplicação simples com menu interativo

---
