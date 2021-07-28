#include <iostream>
using namespace std;

template<typename T>
struct Nodo {
	T info;
	Nodo<T>* sig;
};

struct Resultado {
	int idEquipo1;
	int idEquipo2;
	int idCR; //Codigo resultado
	string estadio;
};

struct InfoEstadio {
	string estadio;
	int partidosJugados;
	int partidosEmpatados;
};

struct Equipo
{
	int idEquipo;
	string nombre;
	int puntos;
};

struct TadListados {
	Nodo<Equipo>* listaEquipos;
	Nodo<InfoEstadio>* listaEstadios;

	int resultadosJuego(Resultado r) {
		//idCR positivo => gano eq2
		//idCR negativo => gano eq1
		//idCR 0 => Empate 
		return r.idCR > 0 ? r.idEquipo2 : (r.idCR < 0 ? r.idEquipo1 : -1);
	}

	Nodo<Equipo>* buscarEquipo(int idEquipoB) {
		Nodo<Equipo>* aux = listaEquipos;
		while (aux != NULL) {
			if (aux->info.idEquipo == idEquipoB) {
				return aux;
			}
			aux = aux->sig;
		}
		return NULL;
	}
	Nodo<InfoEstadio>* buscarEstadio(string nombre) {
		Nodo<InfoEstadio>* aux = listaEstadios;
		while (aux != NULL) {
			if (aux->info.estadio == nombre) {
				return aux;
			}
			aux = aux->sig;
		}
		return NULL;
	}

	void procesarResultado(Resultado resultado) {

		Nodo<InfoEstadio>* estadio = buscarEstadio(resultado.estadio);
		estadio->info.partidosJugados += 1;
		if (resultadosJuego(resultado) > 0) {
			//Alguien gano
			int idGanador = resultadosJuego(resultado);
			Nodo<Equipo>* equipoGanador = buscarEquipo(idGanador);
			equipoGanador->info.puntos += 3;
		}
		else {
			//empataron
			Nodo<Equipo>* eq1 = buscarEquipo(resultado.idEquipo1);
			eq1->info.puntos += 1;

			Nodo<Equipo>* eq2 = buscarEquipo(resultado.idEquipo2);
			eq2->info.puntos += 1;

			
			estadio->info.partidosEmpatados += 1;
		}

	}

	void ordenarEquipos() {

	}
};

void cargarArchivoResultados() {
	//Crea un binario archivo resultados.dat con los resultados 
}

int main()
{
	TadListados listados;

	FILE* f = fopen("resultados.dat", "r+b");
	Resultado r;
	fread(&r, sizeof(Resultado), 1, f);

	while (!feof(f)) {
		listados.procesarResultado(r);
		fread(&r, sizeof(Resultado), 1, f);
	}




	
	return 0;
}

