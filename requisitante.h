#ifndef REQUISITANTE_H
#define REQUISITANTE_H

typedef struct {
    char id[10];
    char nome[50];
    char dataNascimento[11];
    char id_freguesia[7];
} Requisitante;

// Function prototypes
void AddRequisitante(Requisitante requisitante);
void ListarRequisitantes();
void ListarRequisitantePorNome(const char *nome);
int ValidarIDRequisitante(const char id[]);
int ValidarIDFreguesia(const char id[]);

#endif // REQUISITANTE_H
