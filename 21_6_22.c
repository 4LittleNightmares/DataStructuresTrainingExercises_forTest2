// Ex 1

// Ex 2
#include <stdio.h>
#include <stdlib.h>
#include "iterador.h"
#include "noSimples.h"
#include "dicionario.h"
#include "fila.h"
#include "atleta.h"
#include "sala.h"
#include "prova.h"

struct _prova{
    dicionario atletas; // todos os atletas alguma vez inscritos na prova
    // (chave: número atleta; elemento: atleta), implementado em tabela de dispersão aberta
    fila atletasEmEspera; // atletas em espera de ser atribuído às salas
    // fila implementada em vetor
    sala *salas; // salas existentes na prova
    // vetor dinâmico de salas
    int numeroSalas; // número de salas existentes
    int indiceVetorSalas; // indice no vetor salas da 1ª sala com lugares vagos ou -1 caso
    // não haja salas com lugares vazios
} Prova;

// cria uma prova
prova criaProva (int numeroSalas, int capacidade, int prevAtletas){
    prova p = (prova) malloc (sizeof (struct _prova)); // aloca memória para a prova
    p->atletas = criaDicionario(prevAtletas);
    p->atletasEmEspera = criaFila(prevAtletas);
    p->salas = (sala*) malloc (numeroSalas * sizeof(sala)); // vetor dinâmico de salas
    p->numeroSalas = numeroSalas;
    p->indiceVetorSalas = 0;
}

// destroi uma prova
void destroiAtletasSalaEProva (prova p){
    destroiDicionario(p->atletas);
    destroiFila(p->atletasEmEspera);
    for (int i = 0; i < p->numeroSalas; i++){
        destroiSala(p->salas[i]);
    }
    free(p->salas);
    free(p);
}

// indica se o atleta com o número dado está ou esteve na prova
int eAtletaProva(prova p, int numeroAtleta){
    return existeElemDicionario(p->atletas, numeroAtleta);
}

// inscreve um atleta na prova
int inscreveAtletaProva(prova p, atleta a){
    int indice = p->indiceVetorSalas; // indice da 1ª sala com lugares vagos
    if (existeElemDicionario(p->atletas, daNumAtleta(a))){
        return 0;
    } else {
        adicionaElemDicionario(p->atletas, daNumAtleta(a), a);
        if (indice != -1 && vaziaFila(p->atletasEmEspera)){ // se há salas com lugares vagos e não há atletas em espera
            atribuiSalaAtleta(p->salas[indice], a); //salas[indice] é a 1ª sala com lugares vagos
            atribuiAtletaSala(a, p->salas[indice +1]);
        } else { // se não há salas com lugares vagos ou há atletas em espera
            adicionaElemFila(p->atletasEmEspera, a); // p->atletasEmEspera é uma fila; a é um atleta
        } // adiciona o atleta à fila de espera
        return 1;    
}

// iterador de salas vazias
iterador salasVaziasProva (prova p){
    int indice = p->indiceVetorSalas; // indice da 1ª sala com lugares vagos
    int num = p->numeroSalas; // número de salas existentes
    if (indice == -1){ // se não há salas com lugares vagos
        return NULL;
    } else {
        return criaIterador(p->salas + indice, num - indice); // p->salas é um vetor dinâmico de salas
    }
}


// Grupo 2
// Ex 1

typedef struct _lista *lista;

typedef struct _lista{
    noSimples cabeça;
} Lista;

/****************************************************************************
tamanhoLista: indica o número de elementos na lista
parametros: l - lista de elementos
retorno: o número de elementos na lista
pré-condição: l != NULL
****************************************************************************/
// no não tem função de tamanhoNoSimples
int tamanhoLista (lista l){
    int i = 0;
    noSimples n = L->cabeça;
    while (n != NULL){ // enquanto não chegar ao fim da lista
        i++;
        n = segNoSimples(n);
    }
    return i;
}

/****************************************************************************
adicionaElementoLista: adiciona elemento à cabeça da lista
parametros: l - lista de elementos
elem - elemento a adicionar
pré-condição: l != NULL && elem != NULL
****************************************************************************/
void adicionaElementoLista (lista l, void *elem){
    noSimples n = criaNoSimples(elem, l->cabeça); // cria um novo nó com o elemento a adicionar e o nó seguinte
    l->cabeça = n; // o novo nó passa a ser a cabeça da lista
}

/****************************************************************************
ocorrenciasMaximoLista: calcula o número de ocorrências do valor máximo na
lista
parametros: l - lista de elementos
retorno: o número de ocorrências do valor máximo
pré-condição: l != NULL
****************************************************************************/
int ocorrenciasMaximoLista (lista l){
    int max = 0;
    int ocorrencias = 0;
    noSimples n = l->cabeça;
    if (n == NULL){
        return 0;
    } else {
        max = *(int*) elemNoSimples(n); // max é o valor do 1º elemento da lista
        while (n != NULL){ // enquanto não chegar ao fim da lista
            if (*(int*) elemNoSimples(n) > max){ // se o valor do elemento for maior que o valor máximo
                max = *(int*) elemNoSimples(n); // o valor máximo passa a ser o valor do elemento
            }
            n = segNoSimples(n);
        }
        n = l->cabeça;
        while (n != NULL){ // enquanto não chegar ao fim da lista
            if (*(int*) elemNoSimples(n) == max){ // se o valor do elemento for igual ao valor máximo
                ocorrencias++; // incrementa o número de ocorrências
            }
            n = segNoSimples(n);
        }
        return ocorrencias;
    }
}