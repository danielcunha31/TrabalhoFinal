#ifndef Requisicao_H
#define Requisicao_H

typedef struct {
    char id_requisitante[10];
    char isbn[14];
    char data[11];
} Requisicao;

// Function prototypes
void RequisitarLivro(Requisicao requisicao);
void ListarAtuaisRequisicoes();

#endif // Requisicao_H
