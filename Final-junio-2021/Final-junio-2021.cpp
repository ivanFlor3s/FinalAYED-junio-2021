#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


struct Producto
{
    string name;
    int price;

};


struct Nodo
{
    int info;
    Nodo* sig;
};


void agregarNodoAlFinal(Nodo* lista, int infor) {
    Nodo* nuevo = new Nodo();
    nuevo->info = infor;
    nuevo->sig = NULL;

    Nodo* aux = lista;

    while (aux->sig != NULL) {

        aux = aux->sig;
    }
    aux->sig = nuevo;
}

int main()
{


    int a = 30;
    //OPERADOR DE DIRECCION : anteponer & a una variable me da la direccion de memoria donde esta esa variable
    cout << "Direccion de a: " << &a << endl;

    //Direccion de a
    int* p = &a;
    cout << "Valor puntero: " << p << endl;

    //OPERADOR DE CONTENIDO: Si a una variable de tipo puntero antepongo * me da el CONTENIDO que se aloja en esa direccion que indica la variable
    cout << "Valor de a por direccion: " << *p << endl;

    //Direccion de la direccion de a
    int** q = &p;
    cout << "Valor de la direccion de la direccion del entero a: " << q <<endl;


    //GESTION DINAMICA DE MEMORIA ------------------------------------------

    //Inicializo el entero ESTATICA
    int* puntero = NULL;

    //Pedir memoria al OS en tiempo de ejecucion de mi programa DINAMICA
    puntero = new int();

    //Libero la memoria que pedi dinamicamente. Ya no tengo acceso a PUNTERO
    delete(puntero);

    
   //PUNTEROS A ESTRUCTURAS

    Producto* prod = new Producto();
    //Son analogos (es mas facil usar la flecha)
    prod->name = "Lapiz";
    (*prod).price = 50;

    cout << "Producto, precio: " << (*prod).price << " - " << prod->name << endl;

    // ESTRUCTURA DINAMICA, ejemplo Nodo
    


    return 0;
};

