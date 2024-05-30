#ifndef LISTA_H
#define LISTA_H

// No structure for linked lists
typedef struct No {
    void *dados;
    struct No *prox;
} No;

// Function prototypes
No* CriarNo(void *data);
void AddNo(No **head, void *data);
void DestruirLista(No *head, void (*LiberarDados)(void *));

#endif // LISTA_H
