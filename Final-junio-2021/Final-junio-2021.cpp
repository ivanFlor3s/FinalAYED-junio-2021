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
        return -1;
        
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
    return 0;
};

