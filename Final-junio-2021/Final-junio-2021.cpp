#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//Final 13-02-2015
//Sistema para el Seguimiento de Jugadores de Fútbol


struct Jugador {
    int idJugador;
    string nombre;
    int fechaNacimiento;
    string pais;
    int cantGoles;

    Jugador(int id, string n, int fn, string p, int cg) {
        idJugador = id;
        nombre = n;
        fechaNacimiento = fn;
        pais = p;
        cantGoles = cg;
    }

    Jugador() {};
};

struct JugoEn {
    int idJugador;
    string pais;
    JugoEn(int id, string p) {
        idJugador = id;
        pais = p;
    }
    JugoEn() {};
};

struct NodoListaJugadores {
    Jugador info;
    NodoListaJugadores* sig;
};

struct NodoListaJugoEn {
    JugoEn info;
    NodoListaJugoEn* sig;
};

//Escribir en Archivo
template <typename T> void writeInFile(T lista[5], char nombreFile[20])
{
    FILE* f = fopen( nombreFile, "w+b");
    fwrite(lista, sizeof(T), 5, f);
    fclose(f);
}

void escribirJugadoresFile() {
    Jugador* jugador1 = new Jugador(1, "Messi", 18, "ARG", 10);
    Jugador* jugador2 = new Jugador(2, "Neymar", 21, "BRA", 5);
    Jugador* jugador3 = new Jugador(3, "Dibu", 20, "ARG", 3);
    Jugador* jugador4 = new Jugador(4, "Higuain", 31, "ARG", 3);
    Jugador* jugador5 = new Jugador(5, "Pique", 44, "ESP", 15);

    Jugador jugadores[5] = {
        *jugador1,*jugador2, *jugador3, *jugador4, *jugador5
    };
    char nombreFile[20] = "jugadores.dat";
    writeInFile<Jugador>(jugadores, nombreFile);
}

void escribirJugoEnFile() {

    JugoEn* jugo1 = new JugoEn(1, "ARG");
    JugoEn* jugo2 = new JugoEn(2, "BRA");
    JugoEn* jugo3 = new JugoEn(3, "BOL");
    JugoEn* jugo4 = new JugoEn(4, "ARG");
    JugoEn* jugo5 = new JugoEn(5, "ESP");

    JugoEn lista[5] = {
        *jugo1,*jugo2,*jugo3, *jugo4, *jugo5
    };
    char nombreFile[20] = "jugoEn.dat";
    writeInFile<JugoEn>(lista, nombreFile);


}

template <typename T > T read(FILE* f) {
    T aux;
    fread(&aux, sizeof(T), 1, f);
    return aux ;
}

//Codificar o diagramar cargarDatosEnMemoria que reciba dos flujos binarios y que retorne o devuelva punteros 
//a estructuras enlazadas con los datos validos de esos flujos a los efectos de facilitar las búsquedas. NodoListaJugadores*& jugadoresLista, NodoListaJugoEn*& jugoEnLista


void insertarNodoJugador(Jugador jugador, NodoListaJugadores* &lista) {


    NodoListaJugadores* njug = new NodoListaJugadores();
    njug->info = jugador;
    njug->sig = lista;

    lista = njug;

}

void insertarNodoJugoEn(JugoEn jugo, NodoListaJugoEn*& lista) {


    NodoListaJugoEn* nodo = new NodoListaJugoEn();
    nodo->info = jugo;
    nodo->sig = lista;

    lista = nodo;

}

void insertarPrimerNodo(JugoEn jugo, NodoListaJugoEn*& lista) {
    NodoListaJugoEn* nodo = new NodoListaJugoEn();
    nodo->info = jugo;
    nodo->sig = NULL;

    lista = nodo;

}

void insertarPrimerNodo(Jugador jugador, NodoListaJugadores*& lista) {
    NodoListaJugadores* njug = new NodoListaJugadores();
    njug->info = jugador;
    njug->sig = NULL;

    lista = njug;
}

void cargarDatosEnMemoria(NodoListaJugadores* &lista, NodoListaJugoEn* &listaJugoEn ) {

    //CARGAR JUGADORES
    FILE* f = fopen("jugadores.dat", "r+b");
 
    Jugador* j = new Jugador();

    fread(j, sizeof(Jugador), 1, f);

    insertarPrimerNodo(*j,lista);

    cout <<"Se cargo el jugador: "<< j->nombre << endl;


    while (!feof(f)) {
        Jugador* j = new Jugador();
        fread(j, sizeof(Jugador), 1, f);
        if (j->nombre != "") {

            insertarNodoJugador(*j, lista);
            cout << "Se cargo el jugador: " << j->nombre << endl;
        }
    }

    fclose(f);

    //CARGAR JUGO EN
    FILE* fe = fopen("jugoEn.dat", "r+b");

    JugoEn* je = new JugoEn();

    fread(je, sizeof(JugoEn), 1, fe);

    insertarPrimerNodo(*je, listaJugoEn);
    cout << "Se cargo el jugo de: " << je->pais << endl;

    while (!feof(fe)) {

        JugoEn* je = new JugoEn();
        fread(je, sizeof(JugoEn), 1, fe);

        if (je->pais != "") {

            insertarNodoJugoEn(*je, listaJugoEn);
            cout << "Se cargo el jugo de: " << je->pais << endl;
        }
    }
    fclose(fe);
}

bool JugoEnOtraSeleccion(Jugador jugador, NodoListaJugoEn* lista ) {
    bool jugoEnOtra = false;
    NodoListaJugoEn* aux = lista;

    while (!jugoEnOtra && aux->sig != NULL) {
        
        if (jugador.idJugador == aux->info.idJugador) {
            jugoEnOtra = aux->info.pais != jugador.pais;
        }
        aux = aux->sig;
    }
    return jugoEnOtra;
}

bool puedeSerCitado(Jugador jugador, NodoListaJugoEn* lista) {
    return jugador.fechaNacimiento < 30 && !JugoEnOtraSeleccion(jugador, lista);
}



int main()
{

   /*
   CREACION DE ARCHIVOS
    escribirJugadoresFile();
    escribirJugoEnFile();
    */

    /*NodoListaJugadores* listaJugadores = new NodoListaJugadores();
    NodoListaJugoEn* listaJugoEn = new NodoListaJugoEn();
    cargarDatosEnMemoria(listaJugadores, listaJugoEn);

    NodoListaJugadores* aux = listaJugadores;

    

    aux = listaJugadores;
    while (aux->sig != NULL) {
        if (JugoEnOtraSeleccion(aux->info, listaJugoEn)) {
            cout << "Alto vendido este " << aux->info.nombre << endl;
        }
        aux = aux->sig;
    }

    aux = listaJugadores;

    while (aux->sig != NULL) {
        if (puedeSerCitado(aux->info, listaJugoEn)) {
            cout << "Mete a este scaloniiiii: " << aux->info.nombre << endl;
        }
        aux = aux->sig;

    }*/

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




    
   
   
    return 0;
};

