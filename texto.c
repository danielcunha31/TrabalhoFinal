#include "requisitante.h"
#include "lista.h"
#include "hashing.h"
#include <stdio.h>
#include <stdlib.h>
#include "texto.h"
#include <ctype.h>
#include <string.h>

extern No *Livros;
extern Entrada *Livro_hash_table[HASH_TABLE_SIZE];
extern No *requisitantes;
extern Entrada *requisitante_hash_table[HASH_TABLE_SIZE];
Distrito* lista_distritos = NULL;


void CarregarRequisitantes(const char *filenome) {
    FILE *file = fopen(filenome, "r");
    if (!file) {
        perror("Erro ao abrir ficheiro");
        return;
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        Requisitante req;
        if (sscanf(linha, "%s\t%s\t%s\t%s", req.id, req.nome, req.dataNascimento, req.id_freguesia) != 4) {
            fprintf(stderr, "Formato inválido: %s", linha); // Mensagem de erro
            continue;
        }
        if (!ValidarIDRequisitante(req.id) || !ValidarIDFreguesia(req.id_freguesia)) {
            fprintf(stderr, "Falha na validação: %s", linha); // Mensagem de erro
            continue;
        }
        AddRequisitante(req);
    }
    fclose(file);
}

void CarregarDistritos(const char *filenome) {
    FILE *file = fopen(filenome, "r");
    if (!file) {
        perror("Erro ao abrir ficheiro");
        return;
    }
    int id;
    char nome[100];
    while(fscanf(file, "%2d %99[^\n]", &id, nome) == 2) {
        Distrito* novo = (Distrito*)malloc(sizeof(Distrito));
        novo->id = id;
        strcpy(novo->nome, nome);
        novo->concelhos = NULL;
        novo->prox = lista_distritos;
        lista_distritos = novo;
    }
    
    fclose(file);
}

void CarregarConcelhos(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir arquivo de concelhos");
        return;
    }
    
    int id;
    char nome[100];
    while (fscanf(file, "%4d %99[^\n]", &id, nome) == 2) {
        int distrito_id = id / 100;
        Distrito* atual = lista_distritos;
        while (atual != NULL) {
            if (atual->id == distrito_id) {
                Concelho* novo = (Concelho*)malloc(sizeof(Concelho));
                novo->id = id;
                strcpy(novo->nome, nome);
                novo->prox = atual->concelhos;
                atual->concelhos = novo;
                break;
            }
            atual = atual->prox;
        }
    }
    fclose(file);
}

 void CarregarLivros(const char *filename){
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Não foi possível abrir o ficheiro de livros");
        return;
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), file)) {
        Livro livro;
        if (sscanf(linha, "%s\t%s\t%s\t%s", livro.isbn, livro.titulo, livro.autor, livro.ano, livro.area) != 5) {
            log_error("Formato Invalido", linha);
            continue;
        }
        
    AddLivro(livro);
    }
    fclose(file);
}

void SalvarLivros(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Não foi possível abrir o ficheiro de livros para escrita");
        return;
    }
    No *atual = Livros;
    while (atual) {
        Livro *livro = (Livro *)atual->dados;
        fprintf(file, "%s,%s,%s,%d,%s\n",
                livro->isbn, livro->titulo, livro->autor, livro->ano, livro->area);
        atual = atual->prox;
    }
    fclose(file);
}

void SalvarRequisitantes(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Não foi possível abrir o ficheiro de requisitantes");
        return;
    }
    No *atual = requisitantes;
    while (atual) {
        Requisitante *req = (Requisitante *)atual->dados;
        fprintf(file, "%s\t%s\t%s\t%s\n",
                req->id, req->nome, req->dataNascimento, req->id_freguesia);
        atual = atual->prox;
    }
    fclose(file);
}

void log_error(const char *erro_message, const char *linha) {
    FILE *log = fopen("logs.txt", "a");
    if (!log) return;
    fprintf(log, "Error: %s\nlinha: %s\n", erro_message, linha);
    fclose(log);
}
