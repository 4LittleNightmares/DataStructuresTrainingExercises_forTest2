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
cliente criaCliente (char* email, char* nome, char* nif);

void destroiCliente (cliente c);

float precoCompraCliente (cliente c);

void addCompraCliente (cliente c, produto p, int num);

int remCompraCliente (cliente c, char* cod);

int existeProdutoCliente (cliente c; char* cod);

iterador comprasCliente (cliente c);

// funções feitas
// complexidade caso médio: O(1) (o nif tem tamanho fixo)
cliente criaCliente (char* email, char* nome, char* nif){
    cliente c = (cliente) malloc (sizeof (struct _cliente));
    // colocar o nif no cliente
    strcpy(c->nif, nif);
    
    c->email = (char*) malloc (strlen(email) + 1);
    strcpy(c->email, email);
    
    c->nome = (char*) malloc (strlen(nome) + 1);
    strcpy/c->nome, nome);

    c->compras = criaSequencia();

    c->total = 0;
    return c;
}

// complexidade caso médio: O(n) onde n é o número de compras do cliente
// complexidade caso pior: O(n) onde n é o número de compras do cliente
void destroiCliente (cliente c){
    for (int i = 0); i < comprimentoSequencia(c->compras); i++){
        destroiNoSimples(dameElemSequencia(c->compras, i));
    }
    free(c->email);
    free(c->nome);
    free(c);
}

// complexidade caso médio: O(1)
// complexidade caso pior: O(1)
float precoCompraCliente (cliente c){
    return c->total;
}

// complexidade caso médio: O(n) n é o numero de produtos comprados pelo cliente
void addCompraCliente (cliente c, produto p, int num){
    compra comp = criaCompra(num, p);
    adicionaPosSequencia(c->compras, comp, (tamanhoSequencia(c->compras)+1));
    c->total += valorCompra(comp);
}

// 
int remCompraCliente (cliente c, char* cod){
    int num = 0; // numero de unidades removidas
    for (int i = 0; i < tamanhoSequencia(c->compras); i++){
        compra comp = elemPosSequencia(c->compras, i);
        if (strcmp(cod, codigoProduto(produtoCompra(comp))) == 0){ // se o codigo do produto for igual ao codigo do produto da compra
            num = unidadesCompra(comp);
            c->total -= valorCompra(comp);
            destroiCompra(comp);
            removePosSequencia(c->compras, i);
            break;
        }
    }
    return num;
}

int existeProdutoCliente (cliente c; char* cod){
    int num = 0;
    for (int i = 0; i < tamanhoSequencia(c->compras); i++){
        compra comp = elemPosSequencia(c->compras, i);
        if (strcmp(cod, codigoProduto(produtoCompra(comp))) == 0){ // se o codigo do produto for igual ao codigo do produto da compra
            num = unidadesCompra(comp);
            break;
        }
    }
    return num;
}

iterador comprasCliente (cliente c){
    int num = 0;
    void* vetor = malloc (tamanhoSequencia(c->compras) * sizeof (compra));
    for (int i = 0; i < tamanhoSequencia(c->compras); i++){ 
        compra comp = elemPosSequencia(c->compras, i); 
        vetor[num] = comp;
        num++;
    }
    iterador it = criaIterador(vetor, num);
    return it;
}


// Pergunta 2
// adicionamos ao cliente o campo noSimples comprados, que é uma sequencia de compras já efetuadas

void confirmarEncomendaCliente(cliente c);

void confirmarEncomendaCliente(cliente c){
    for (int i = 0; i < tamanhoSequencia(c->compras); i++){ // percorrer o carrinho de compras
        compra comp = elemPosSequencia(c->compras, i);
        // adicionar ao noSimples comprados
        noSimples n = criaNoSimples(comp, NULL); // cria o noSimples para guardar a compra
        if(c->comprados == NULL) { // se a lista estiver vazia
            c->comprados = n; // o primeiro elemento da lista é o noSimples criado
        } else {
            noSimples aux = c->comprados; // auxiliar para percorrer a lista
            while (segNoSimples(aux) != NULL) {
                aux = segNoSimples(aux); 
            }
            atribuiSegNoSimples(aux, n);
        }

        // remover do carrinho de compras
        for (int j = 0; j < tamanhoSequencia(c->compras); j++){
            compra comp2 = elemPosSequencia(c->compras, j);
            if (comp == comp2){
                destroiCompra(comp2);
                removePosSequencia(c->compras, j);
                break;
            }
        }
}

// Pergunta 3

typedef struct _loja * loja;

// opção B, os clientes são identificados por mail, logo o dicionario é implementado com uma tabela de dispersão aberta
//            os produtos são identificados por código, logo o dicionario é implementado com uma tabela de dispersão aberta
// comparativamente com uma sequencia, em complexidade, a tabela de dispersão aberta é mais eficiente, pois a procura é feita em O(1)
struct _loja{
    dicionrio clientes; //  implementado com dicionario em tabela de dispersão aberta
    dicionario produtos; // implementado com dicionario em tabela de dispersão aberta
};



loja criaLoja(int numC, int numP){
    loja l = (loja) malloc(sizeof(struct _loja));
    l->clientes = criaDicionario(numC);
    l->produtos = criaDicionario(numP);~
    return l;
}

int vendaProdutoLoja(loja l, char* cod, char* email, int uni){
    cliente c = elementoDicionario(l->clientes, email);
    produto p = elementoDicionario(l->produtos, cod);
    if (c == NULL || p == NULL) return 0;
    int vendas = vendaProduto(p, uni);
    if (vendas == 0) return 0;
    compra comp = criaCompra(p, vendas);
    insereSequencia(c->compras, comp);
    return vendas;
}

iterador stockProdutosLoja(loja l, int n){
    iterador it = iteradorDicionario(l->produtos);
    iterador it2 = criaIterador();
    while (temSeguinteIterador(it)){
        produto p = seguinteIterador(it);
        if (unidadesProduto(p) > n){
            insereIterador(it2, p);
        }
    }
    destroiIterador(it);
    return it2;
}



