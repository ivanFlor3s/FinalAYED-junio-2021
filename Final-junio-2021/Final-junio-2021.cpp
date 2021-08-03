// Final-junio-2021.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

template<typename T>
struct Nodo {
    T info;
    Nodo<T> sig;
};

struct Ilicito {
    string patente;
    string delito;
    int horaIlicito;
};

struct Recorrido {
    int idZona;
    int horaRegistro;
    bool vale;

    Recorrido(int id, int h, bool v) {
        idZona = id;
        horaRegistro = h;
        vale = v;
    }
};

struct VehiculoSospechoso {
    string patente;
    string delito;
    Nodo<Recorrido>* listaRecorrido;
};

struct BusquedaPatenteDelito {
    string patente;
    string delito;
    BusquedaPatenteDelito(string p, string d) {
        patente = p;
        delito = d;
    }
};

struct TadZona
{
    Nodo<Recorrido>* listaRecorridos;
    int nroZona;

    //Armar los recorridos del auto buscado en la zona. Se devuelve la lista de recorrido
    void BuscarRecorridoIlicito(string patente, string delito, Nodo<Recorrido>* &lista, int horaIlicito) {
        Nodo<Recorrido>* aux = listaRecorridos;
        
         aux = buscar(listaRecorridos, *new BusquedaPatenteDelito(patente, delito));
        while (aux != NULL) {
            Recorrido* rec = new Recorrido(nroZona, aux->info.horaRegistro, true);
            if (rec->horaRegistro > horaIlicito) {

                insertarOrdenado<Recorrido>(lista, *rec);
            }
            else
            {
                //El valor de vale, es verdadero cuando el registro es posterior al ilicito
                rec->vale = false;
                inserterOrdenado<Recorrido>(lista, *rec);
            }
            aux = buscar(aux, *new BusquedaPatenteDelito(patente, delito));
        }
    }

};

Nodo<Recorrido>* Reordenar(Nodo<Recorrido>* listaRec) {
    Nodo<Recorrido>* nuevaLista = NULL;
    Nodo<Recorrido>* aux = listaRec;
    while (aux != NULL) {
        insertarOrdenado<Recorrido>(listaRec, aux->info);
        aux = aux->sig;
    }

    return nuevaLista;
}

VehiculoSospechoso recorrido(TadZona zonas[10], string patenteBusq, string delito,int  horaIlicito) {
    VehiculoSospechoso* resp = new VehiculoSospechoso();

    resp->delito = delito;
    resp->patente = patenteBusq;
    Nodo<Recorrido>* listRecorrido;
    for (int i = 0; i < 10; i++) {
        zonas[i].BuscarRecorridoIlicito(patenteBusq, delito, listRecorrido, horaIlicito);
    }
    resp->listaRecorrido = Reordenar(listRecorrido);

    return *resp;
}

int main()
{
    TadZona zonas[10];

    //Invocacion de la funcion
    VehiculoSospechoso resp = recorrido(zonas, "DSA89321", "Ir a 120 en avenida",390213);
   


    return 0;
};

