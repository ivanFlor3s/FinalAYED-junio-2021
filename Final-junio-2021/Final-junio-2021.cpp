// Final-junio-2021.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

template<typename T>
struct Nodo
{
    T info;
    Nodo<T>* sig;
};

template<typename T>
struct TadStack
{
    Nodo<T>* pila = NULL;
    
    void push(T nuevaInfo) {
        if (pila == NULL) {
            pila = new Nodo<T>();
            pila->info = nuevaInfo;
            pila->sig = NULL;
            return;
        }
        else {
            Nodo<T>* aux = pila;

            pila = new Nodo<T>();
            pila->info = nuevaInfo;
            pila->sig = aux;
        }
    }

    T pop() {
        if (pila != NULL)
        {
            T content = pila->info;
            Nodo<T>* aux = pila;
            pila = pila->sig;
            delete(aux);
            return content;

        }
        return NULL;
        
    }

};

template<typename T >
struct TadCola
{
    Nodo<T>* cola = NULL;

    void encolar(T nuevo) {
        if (cola == NULL) {
            cola = new Nodo<T>();
            cola->info = nuevo;
            cola->sig = NULL;
            return;
        }
        else {
            Nodo<T>* aux = cola;
            while (aux->sig != NULL) {
                aux = aux->sig;
            }
            aux->sig = new Nodo<T>();
            aux->sig->info = nuevo;
            aux->sig->sig = NULL;
            return;

        }
    }

    T desencolar() {
        if (cola != NULL) {
            T content = cola->info;
            Nodo<T>* aux = cola;
            cola = cola->sig;
            delete(aux);

            return content;
        }
        return NULL;
    }
};

int main()
{
    
    TadStack<int> stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    int primerPop = stack.pop();

    TadCola<string> queue;
    queue.encolar("Hola");
    queue.encolar("Como");
    queue.encolar("Estas");

    string s = queue.desencolar();
    string s2 = queue.desencolar();
    string s3 = queue.desencolar();
    return 0;
};

