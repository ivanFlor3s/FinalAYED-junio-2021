// Final-junio-2021.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

struct InfoLista
{
    int c1;
    char c2;
    float c3;
    int c4;

};
struct NodoLista {
    InfoLista infoLista;
    NodoLista* sig;

};

struct InfoSubLista
{
    float campo3;
    int campo4;


};

struct NodoSubLista
{
    InfoSubLista infSub;
    NodoSubLista* sig;

};

struct InfoResult {
    int c1;
    char c2;
    NodoSubLista* subLista;
};

struct NodoListaResult
{
    InfoResult info;
    NodoListaResult* sig;
};


InfoLista Pop(NodoLista* &lista) {
    //Guardo valor que voy a devolver
    InfoLista res = lista->infoLista;

    //Guardo Lista en auxiliar
    NodoLista* aux = lista;

    //Lista ahora empieza en el siguiente
    lista = aux->sig;

    //Borro el que ya saque
    delete aux;

    return res;
}

void InsertarSubNodo(NodoSubLista* lista, NodoSubLista* insert ) {
    NodoSubLista* aux = lista;
    while (aux->sig != NULL) {
        aux = aux->sig;
    }
    aux->sig = insert;
}

NodoListaResult* CargarListaDeListas(NodoLista* &lista) {
    NodoListaResult* nr = new NodoListaResult();
    NodoListaResult* nraux = new NodoListaResult();
    bool primerNodo = true;
    while (lista->sig != NULL) {
        InfoLista il = Pop(lista);
        if (primerNodo) {
            nr->info.c1 = il.c1;
            nr->info.c2 = il.c2;
            NodoSubLista* nsl = new NodoSubLista();
            nsl->infSub.campo3 = il.c3;
            nsl->infSub.campo4 = il.c4;
            nr->info.subLista = nsl;
            NodoListaResult* nraux = nr;
        }
        else {
            while ( il.c1 == nraux->info.c1 && il.c2 == nraux->info.c2) {
                NodoSubLista* ns = new NodoSubLista();
                InfoSubLista subInfo;
                subInfo.campo3 = il.c3;
                subInfo.campo4 = il.c4;
                ns->infSub = subInfo;
                ns->sig = NULL;

                InsertarSubNodo(nr->info.subLista, ns);
                nraux = nraux->sig;
            }
        }
        
    }


    return nr;
}


int main()
{
    NodoLista* nl = new NodoLista();
    InfoLista* il = new InfoLista();
    il->c1 = 2;
    il->c2 = 'C';
    il->c3 = 2;
    il->c4 = 32;

    nl->infoLista = *il;

    

    return 0;
};

