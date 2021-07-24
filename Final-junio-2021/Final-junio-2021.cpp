#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Link del video https://www.youtube.com/watch?v=DXxMNCOZf3Q&list=PLfvyG2RxJZsaiWvkM_Cat0obF3VSmo4UQ&index=26

template <class T>
struct Nodo {
	T info;
	Nodo<T>* sig;
};

struct Ciudad {
	int idCiudad;
	string descripcion;
	int millas;
};

struct InfoCiudad {
	Ciudad ciudad;
	int cantFamiliasComoDestino = 0;
};

struct TadListaCiudades {
	Nodo<InfoCiudad>* lista;
	void inicializar() {
		//Llenar con datos la lista
	}

	void imprimirResultados() {
		Nodo<InfoCiudad>* aux = lista;

		while (aux != NULL) {
			cout << "Ciudad " << aux->info.ciudad.descripcion << 
				" - Grupos que la eligen como destino: " << 
				aux->info.cantFamiliasComoDestino << endl;
			aux = aux->sig;
		}
	}

	Nodo<InfoCiudad>* buscarCiudad(int idCiudad) {
		Nodo<InfoCiudad>* aux = lista;

		while (aux != NULL) {
			if (aux->info.ciudad.idCiudad == idCiudad) {
				return aux;
			}
			aux = aux->sig;
		}
	}
};



struct Vuelo {
	int idVuelo;
	int capacidad;
	int idOrigen; //id ciudad origen
	int idDestino; //id ciudad destino
};
struct InfoVuelo
{
	Vuelo vuelo;
	int reservados = 0;
	int rechazadas = 0;
	bool esCompleto = false;
};
struct NodoVuelo
{
	InfoVuelo info;
	NodoVuelo* sig;
};

struct TadVuelos {
	NodoVuelo* lista;
	
	void inicializarLista() {
		//Completar lista con Vuelos
	}

	void imprimirResultados() {
		NodoVuelo* aux = lista;
		while (aux != NULL) {
			cout << "IdVuelo: " << aux->info.vuelo.idVuelo <<
				" - Rechazados" << aux->info.rechazadas <<
				"Completo? " << (aux->info.esCompleto ? "SI" : "NO") << endl;
			aux = aux->sig;
		}
	}

	NodoVuelo* buscarVuelo(int idVuelo) {
		NodoVuelo* aux = lista;

		while (aux != NULL) {
			if (aux->info.vuelo.idVuelo == idVuelo) {
				return aux;
			}
			aux = aux->sig;
		}
	}

	bool puedeReservar(int cant, NodoVuelo* vuelo) {
		if (vuelo->info.esCompleto) {
			return false;
		}
		return vuelo->info.reservados + cant <= vuelo->info.vuelo.capacidad;
	}

	bool reservarVuelo(int cant, NodoVuelo* vuelo) {
		if (puedeReservar(cant, vuelo)) {

			vuelo->info.reservados += cant;
			vuelo->info.esCompleto = vuelo->info.reservados == vuelo->info.vuelo.capacidad;
			return true;
		}
		else {
			vuelo->info.rechazadas += 1;
			return false;
		}
	}
};



struct Reserva {
	int idCliente;
	int idVuelo;
	int cantidad;
};

struct NodoCliente
{
	InfoCliente info;
	NodoCliente* sig;
};

struct InfoCliente
{
	int idCliente;
	int millasAcumuladas = 0;
};

struct TadListaClientes {
	NodoCliente* lista;

	void informarMillas() {
		NodoCliente* aux = lista;
		while (aux != NULL) {

			cout <<"CLIENTE: " <<aux->info.idCliente <<" - MILLAS: " <<aux->info.millasAcumuladas<< endl;

			aux = aux->sig;
		}
	}

	//Busca y devuelve un puntero al nodoCliente
	NodoCliente* buscarAgregarCliente(int id) {
		NodoCliente* aux = lista;
		while (aux != NULL) {

			if (aux->info.idCliente == id) {
				return aux;
			}

			aux = aux->sig;
		}
		
		aux = lista;
		while (aux->sig == NULL) {
			aux = aux->sig;
		}

		InfoCliente* nuevoCliente = new InfoCliente();
		nuevoCliente->idCliente = id;
		nuevoCliente->millasAcumuladas = 0;

		NodoCliente* nodo = new NodoCliente();
		nodo->info = *nuevoCliente;
		nodo->sig = NULL;
		aux = nodo;

		return aux;
		
	}
};





Reserva leerReserva() {
	Reserva res;
	cout << "Ingrese los datos de la reserva: IDCLIENTE - IDVUELO - CANTIDAD" << endl;
	cin >> res.idCliente >> res.idVuelo >> res.cantidad;
	return res;
}



int main()
{

	//Inicializo TADS
	TadListaClientes listaClientes;

	TadListaCiudades ciudades;
	TadVuelos vuelos ;


	Reserva reserva = leerReserva();
	while (reserva.idCliente > 0) {

		NodoCliente * nCliente = listaClientes.buscarAgregarCliente(reserva.idCliente);
		
		NodoVuelo* v = vuelos.buscarVuelo(reserva.idVuelo);

		if (vuelos.reservarVuelo(reserva.cantidad, v)) {
			Nodo<InfoCiudad>* ciudadOrigen = ciudades.buscarCiudad(v->info.vuelo.idOrigen);
			Nodo<InfoCiudad>* ciudadDestino = ciudades.buscarCiudad(v->info.vuelo.idDestino);
			//Considero que si se reservan mas de 2 es una familia
			if (reserva.cantidad > 2) {
				ciudadDestino->info.cantFamiliasComoDestino += 1;
			}
			nCliente->info.millasAcumuladas += abs(ciudadOrigen->info.ciudad.millas - ciudadDestino->info.ciudad.millas);
		}

		reserva = leerReserva();
	}


	//Punto 1
	listaClientes.informarMillas();

	//Punto 2
	ciudades.imprimirResultados();

	//Punto 3
	vuelos.imprimirResultados();

};

