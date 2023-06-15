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
    
}