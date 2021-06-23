// Final-junio-2021.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

struct InfoLista
{
    int c1;
    string c2;
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

    InfoSubLista(float dato1, int dato2) {
        campo3 = dato1;
        campo4 = dato2;
    }
};

struct NodoSubLista
{
    InfoSubLista infSub;
    NodoSubLista* sig;
};

struct InfoResult {
    int c1;
    string c2;
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


int main()
{
    NodoLista* nl = new NodoLista();
    InfoLista* il = new InfoLista();
    il->c1 = 2;
    il->c2 = "string";
    il->c3 = 2;
    il->c4 = 32;

    nl->infoLista = *il;

    

    return 0;
};

