// Pergunta 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iterador.h"
#include "noSimples.h"
#include "dicionario.h"
#include "fila.h"

typedef struct _cliente *cliente;

struct _cliente {
    char nif[NIF_TAMANHO]; // identificação fiscal do cliente
    char* email; // email do cliente
    char* nome; // nome do cliente
    sequencia compras; // carrinho de compras do cliente
    float total; // preço total do conteudo do carrinho de compras
};

// protótipos das funções
cliente criaCliente (char* email, char* nome, char* nig);

void destroiCliente (cliente c);

void addCompraCliente (cliente c, produto p, int num);

int remCompraCliente (cliente c, char* cod);

int existeProdutoCliente (cliente c; char* cod);

iterador comprasCliente (cliente c);

// funções feitas
cliente criaCliente (char* email, char* nome, char* nig){
    
}