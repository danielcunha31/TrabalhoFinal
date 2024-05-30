#ifndef HASHING_H
#define HASHING_H

#define HASH_TABLE_SIZE 100

// Hash table Entrada structure
typedef struct Entrada {
    char *key;
    void *valor;
    struct Entrada *prox;
} Entrada;

// Function prototypes
unsigned int hash(const char *key);
Entrada* CriarEntrada(const char *key, void *valor);
void InserirEntrada(Entrada **hash_table, const char *key, void *valor);
void* BuscarValor(Entrada **hash_table, const char *key);
void DestruirHashing(Entrada **hash_table);

#endif // HASHING_H
