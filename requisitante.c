#include "requisitante.h"
#include "lista.h"
#include "hashing.h"
#include <stdio.h>
#include <stdlib.h>
#include "texto.h"
#include <ctype.h>
#include <string.h>

No *requisitantes = NULL;
Entrada *requisitante_hash_table[HASH_TABLE_SIZE] = {0};

void AddRequisitante(Requisitante requisitante) {
    Requisitante *novoRequisitante = (Requisitante *)malloc(sizeof(Requisitante));
    if (!novoRequisitante) return;
    *novoRequisitante = requisitante;
    AddNo(&requisitantes, novoRequisitante);
    InserirEntrada(requisitante_hash_table, requisitante.id, novoRequisitante);
}

void ListarRequisitantes() {
    No *atual = requisitantes;
    while (atual) {
        Requisitante *req = (Requisitante *)atual->dados;
        printf("ID: %s, nome: %s, Data de nascimento: %s, Freguesia ID: %s\n",
               req->id, req->nome, req->dataNascimento, req->id_freguesia);
        atual = atual->prox;
    }
}

void ListarRequisitantePorNome(const char *nome){
    extern Entrada *requisitante_hash_table[HASH_TABLE_SIZE];
    Requisitante *req = ObterValor(requisitante_hash_table, nome);
    if (req) {
        printf("Encontrar requisitante:\n Nome: %s, ID: %s, Data de Nascimento: %s, ID Freguesia: %s\n",
               req->nome, req->id, req->dataNascimento, req->id_freguesia);
    } else {
        printf("Requisitante nao encontrado.\n");
    }
}

int ValidarIDRequisitante(const char id[]) {
   if (strlen(id) != 9) {
        return 0; // O ID deve ter exatamente 9 caracteres
    }
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        if (id[i] < '0' || id[i] > '9') {
            return 0; // Todos os caracteres devem ser dígitos
        }
        soma += id[i] - '0'; // Converte o caractere para o valor inteiro correspondente
    }
    return soma % 10 == 0; // Verifica se a soma é múltiplo de 10
}


int ValidarIDFreguesia(const char id[]) {
   if (strlen(id) != 6) {
        return 0; // O ID deve ter 6 caracteres
    }
    for (int i = 0; i < 4; i++) {
        if (!isdigit((unsigned char)id[i])) {
            return 0; // Os primeiros 4 caracteres devem ser dígitos
        }
    }
    // Os últimos 2 caracteres podem ser dígitos ou letras
    for (int i = 4; i < 6; i++) {
        if (!isalnum((unsigned char)id[i])) {
            return 0; // Verifica se é um carácter alfanumérico
        }
    }
    return 1;
}
