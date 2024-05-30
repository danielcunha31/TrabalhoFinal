#include "requisicao.h"
#include "lista.h"
#include "hashing.h"
#include <stdio.h>
#include <stdlib.h>

No *Requisicoes = NULL;

void RequisitarLivro(Requisicao requisicao) {
    Requisicao *novaRequisicao = (Requisicao *)malloc(sizeof(Requisicao));
    if (!novaRequisicao) return;
    *novaRequisicao = requisicao;
    AddNo(&Requisicoes, novaRequisicao);
}

void ListarAtuaisRequisicoes() {
    No *atual = Requisicoes;
    while (atual) {
        Requisicao *req = (Requisicao *)atual->dados;
        printf("Requisitante ID: %s, ISBN: %s, data: %s\n",
               req->id_requisitante, req->isbn, req->data);
        atual = atual->prox;
    }
}
