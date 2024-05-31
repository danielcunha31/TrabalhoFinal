#ifndef Livro_H
#define Livro_H

typedef struct {
    char isbn[14];
    char titulo[100];
    char autor[50];
    char area[30];
    int ano;
} Livro;


// Function prototypes
void AddLivro(Livro Livro);
void ListarLivrosPorArea();
void ListarLivroPorISBN(const char *isbn);
void DevolverLivro(const char *isbn, const char *id_requisitante);

#endif // Livro_H
