#include "hashing.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % HASH_TABLE_SIZE;
}

// Função para criar o hash
Entrada* CriarEntrada(const char *key, void *valor) {
    Entrada *novaEntrada = (Entrada *)malloc(sizeof(Entrada));
    if (!novaEntrada) return NULL;
    novaEntrada->key = strdup(key);
    novaEntrada->valor = valor;
    novaEntrada->prox = NULL;
    return novaEntrada;
}

// Função para inserir a nova entrada no hash
void InserirEntrada(Entrada **hash_table, const char *key, void *valor) {
    unsigned int indice = hash(key);
    printf("Inserting key: %s, at index: %u\n", key, indice);
    Entrada *novaEntrada = CriarEntrada(key, valor);
    if (!novaEntrada) return;
    if (!hash_table[indice]) {
        hash_table[indice] = novaEntrada;
    } else {
        Entrada *atual = hash_table[indice];
        while (atual->prox) {
            atual = atual->prox;
        }
        atual->prox = novaEntrada;
    }
}

void* ObterValor(Entrada **hash_table, const char *key) {
    printf("key: %s\n", key);
    unsigned int indice = hash(key);
    printf("hash index: %u\n", indice);

    Entrada *atual = hash_table[indice];
    while (atual) {
        printf("Checking key: %s\n", atual->key);
        if (strcmp(atual->key, key) == 0) {
            return atual->valor;
        }
        atual = atual->prox;
    }
    return NULL;
}

void DestruirHashing(Entrada **hash_table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Entrada *atual = hash_table[i];
        while (atual) {
            Entrada *prox = atual->prox;
            free(atual->key);
            free(atual);
            atual = prox;
        }
    }
}
