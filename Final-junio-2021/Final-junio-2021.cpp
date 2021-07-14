#include <iostream>
#include <stdio.h>
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
};

struct JugoEn {
    int idJugador;
    char pais[50];
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





int main()
{
    Jugador* jugador1 = new Jugador(1,"messo", 12081996,"ARG",10);
    Jugador* jugador2 = new Jugador(2, "JAVI", 12081996, "AFR", 5);
    Jugador* jugador3 = new Jugador(3, "refus", 12081996, "ENG", 3);
    Jugador* jugador4 = new Jugador(4, "tom", 12081996, "URU", 3);
    Jugador* jugador5 = new Jugador(5, "chadgi", 12081996, "BOL", 15);

    Jugador jugadores[5] = {
        *jugador1,*jugador2, *jugador3, *jugador4, *jugador5
    };
    char nombreFile[20] = "jugadores.dat";
    writeInFile<Jugador>(jugadores, nombreFile);

    FILE* f = fopen("jugadores.dat", "r+b");
    Jugador* jugLeido = new Jugador(5, "s", 1, "s", 15);

    fseek(f, sizeof(Jugador) * 3, SEEK_SET);

    fread(jugLeido, sizeof(Jugador), 1, f);
    fclose(f);
    cout<< jugLeido->nombre <<endl;
    return 0;
};

