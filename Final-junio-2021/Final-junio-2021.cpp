// Final-junio-2021.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#define _CRT_SECURE_NO_WARNINGS 1 
#include <iostream>
using namespace std;

template<typename T>
struct Nodo {
    T info;
    Nodo<T>* sig;
};

template<typename T>
void AgregarNodo(T nuevo, Nodo<T>* cola) {
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

struct Ticket {
    int nroTicket;
    int codigoTipoIncidente;
    string solicitante;
    string interno;
    string descripcion;
    string responsable = "Empty";
    bool resuelto;

    void resolverTicket() {
        resuelto = true;
    }
};

struct Incidente {
    int codigoTipoIncidente;
    string nombreIncidente;
};


struct TadTiposIncidentes {
    Nodo<Incidente>* listaIncidentes = NULL;
    void leerTiposIncidentes() {
        //leer file incidentes y agregar en ListaIncidentes
    }

    Incidente* buscar(int idIncidente) {
        Nodo<Incidente>* aux = listaIncidentes;
        while (aux != NULL ) {
            if (aux->info.codigoTipoIncidente == idIncidente) {
                return &aux->info;
            }
            aux = aux->sig;
        }
        return NULL;
    }

};

struct TadTickets {

    int lastNumeroTicket = 0;
    Nodo<Ticket>* listaTickets = NULL;
    TadTiposIncidentes tadInc;

    void setUltimoNumeroTicket() {
        FILE* f = fopen("NUMERADOR.DAT", "r+b");
        fread(&lastNumeroTicket, sizeof(int), 1, f);
        fclose(f);
    }
    void asignarNumeroTicket(Ticket* pt) {
        pt->nroTicket = lastNumeroTicket;
        lastNumeroTicket += 1;
    }

    
    void cargarTickets() {
        cout << "Cargando ticket" << endl;
        Ticket* t = new Ticket();
        cin >> t->codigoTipoIncidente >> t->solicitante >> t->interno >> t->descripcion;
        while (t->codigoTipoIncidente != 666) {
            Incidente* i = tadInc.buscar(t->codigoTipoIncidente);
            if (i !=NULL) {
                asignarNumeroTicket(t);
                AgregarNodo<Ticket>(*t, listaTickets);
            }
            else {
                cout << "Ingrese un tipo de incidente valido" << endl;
            }
            cin >> t->codigoTipoIncidente >> t->solicitante >> t->interno >> t->descripcion;
        }

        saveTickets();
        cout << "Fin de carga" << endl;
    }
    void saveTickets() {
        //recorro la lista haciendo fwrites de llos tickets a lo loco 
    }

    void asignarTickets() {
        Nodo<Ticket>* aux = listaTickets;
        while (aux != NULL) {
            if (aux->info.responsable == "Empty") {
                cout << "Ingrese un responsable para el ticket " << aux->info.nroTicket << aux->info.descripcion << endl;
                cin >> aux->info.responsable;
            }
            aux = aux->sig;
        }
    }

    Nodo<Ticket>* filtrarTickets(string resp) {
        //Devuelve una lista filtrada por responsable de tickets
        return new Nodo<Ticket>();
    }
    Nodo<Ticket>* buscarTicket(int id) {
        Nodo<Ticket>* aux = listaTickets;
        while (aux != NULL)
        {
            if (aux->info.nroTicket == id) {
                return aux;
            }
            aux = aux->sig;
        }
        return NULL;
    }
    void mostrarTickets(Nodo<Ticket>* tickets) {
        Nodo<Ticket>* aux = tickets;
        while (aux != NULL) {
            cout << "Ticket nro" << aux->info.nroTicket << endl;
            cout << "Solicitante" << aux->info.nroTicket << endl;
            cout << "Nombre TipoIncidente" << tadInc.buscar(aux->info.codigoTipoIncidente)->nombreIncidente << endl;
            cout << "Descripcion" << aux->info.descripcion << endl;
            cout << "------------------------"<< endl;
            aux = aux->sig;
        }
        cout << "se mostraron todos los tickets" << endl;
    }
    void saveTicketsNoResueltos() {
        int contador = 1;
        Nodo<Ticket>* aux = listaTickets;
        Nodo<Ticket>* auxLista = NULL;
        FILE* f = fopen("PENDIENTES.DAT", "w+b");

        while (aux != NULL) {
            if (!aux->info.resuelto) {
                contador++;
                AgregarNodo<Ticket>(aux->info, auxLista);
                fwrite(&aux->info, sizeof(Ticket), 1, f);
                fseek(f, contador * sizeof(Ticket), SEEK_SET);
            }
            aux = aux->sig;
        }
        cout << "Guardado en archivo tickets pendientes" << endl;
        mostrarTickets(auxLista);

        
        
    }

    void mostrarMenu() {
        int opcion;
        string responsable;
        int ticktTarget;
        cout << "1-Resolver Ticket" << endl;
        cout << "2-Salir" << endl;
        cin >> opcion;
        cout << "Responsable" << endl;
        cin >> responsable;
        while (opcion != 2) {
            if (opcion == 1) {
                Nodo<Ticket>* misTickets = filtrarTickets(responsable);
                mostrarTickets(misTickets);

                cout << "Ingresar num ticket a resolver: " << endl;
                cin >> ticktTarget;
                Nodo<Ticket>* pt = buscarTicket(ticktTarget);
                if (pt != NULL) {

                    pt->info.resolverTicket();
                }
                else{
                    cout << "No se encontro el ticket" << endl;
                }
            }
            cout << "No ingresaste una opcion valida" << endl;
        }

        saveTicketsNoResueltos();
    }
};

int main()
{
    TadTiposIncidentes tadIncidentes;
    TadTickets tadTickets;
    tadTickets.tadInc = tadIncidentes;
    tadTickets.cargarTickets();
    
    
    tadTickets.asignarTickets();
   
    tadTickets.mostrarMenu();

    return 0;
};


