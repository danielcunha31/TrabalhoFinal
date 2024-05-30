#include "hashing.h"
#include <stdlib.h>
#include <string.h>

unsigned int hash(const char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % HASH_TABLE_SIZE;
}

Entrada* CriarEntrada(const char *key, void *valor) {
    Entrada *novaEntrada = (Entrada *)malloc(sizeof(Entrada));
    if (!novaEntrada) return NULL;
    novaEntrada->key = strdup(key);
    novaEntrada->valor = valor;
    novaEntrada->prox = NULL;
    return novaEntrada;
}

void InserirEntrada(Entrada **hash_table, const char *key, void *valor) {
    unsigned int indice = hash(key);
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

void* BuscarValor(Entrada **hash_table, const char *key) {
    unsigned int indice = hash(key);
    Entrada *atual = hash_table[indice];
    while (atual) {
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
