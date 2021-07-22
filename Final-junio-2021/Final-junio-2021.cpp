#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//Link del ejercicio: https://www.youtube.com/watch?v=F_ikRFhRTv0&list=PLfvyG2RxJZsaiWvkM_Cat0obF3VSmo4UQ&index=24

struct TipoInfraccion {
	int id;
	string descripcion;
	int importe;
	int diasPp;
	int dtoPp;
};

struct Infraccion {
	string patente;
	int fecha;
	int idTipoInfraccion;
};

struct Estadistica {
	int dia;
	int cantidad = 0;
	int Total = 0;
	bool acceso = false;
};


void cargarTiposInfraccion(TipoInfraccion colTipos[50]) {
	
 }



Infraccion leerInfraccion() {
	Infraccion i;
	cout << "Ingrese infraccion" << endl <<"Patente - Fecha - Id"<<endl;
	cin >> i.patente >> i.fecha >> i.idTipoInfraccion;
	return i;

}

TipoInfraccion buscarTipo(int idTipo, TipoInfraccion colTipos[50]) {
	int i = 0;
	for (i ; i < 50; i++) {
		if (colTipos[i].id == idTipo) {
			return colTipos[i];
		}		
	}
}



void agregarEstadistica(int dia, int importe, Estadistica estadisticas[31]) {
	estadisticas[dia].acceso = true;
	estadisticas[dia].cantidad += 1;
	estadisticas[dia].Total += importe;
}

int main()
{

	Infraccion colInfracciones[50];
	TipoInfraccion colTipos[50];
	cargarTiposInfraccion(colTipos);

	int fechaHoy = 30;

	Estadistica estadisticas[31];
	
	Infraccion infraccion = leerInfraccion();

	//Corto cuando se ingrese una patente con Id Negativo o igual a 0
	while (infraccion.idTipoInfraccion > 0) {

		string patenteAnterior = infraccion.patente;
		cout << "Patente: " << infraccion.patente << endl;
		double TotalImportes = 0;
		double TotalDescuentos = 0;
		//Itero mientras este leyendo infraciones con la misma patente
		while (patenteAnterior == infraccion.patente) {

			TipoInfraccion t =  buscarTipo(infraccion.idTipoInfraccion, colTipos);
			int descuento = ((fechaHoy - infraccion.fecha) > t.diasPp) ? t.dtoPp * t.importe : 0;
			int total = t.importe - descuento;

			//Imprimir los resultados por cada lectura
			cout << "Fecha: " << infraccion.fecha << " - Valor" << t.importe << 
				" - Descuento " << descuento << " - Total" << total << endl;
			TotalImportes += total;
			infraccion = leerInfraccion();

			agregarEstadistica(infraccion.fecha, t.importe, estadisticas);
			
		}

		cout << "TOTAL IMPORTES: " << TotalImportes << endl;
		cout << "TOTAL DESCUENTOS: " << TotalDescuentos << endl;
		cout << "TOTAL TOTALES: " << TotalImportes - TotalDescuentos << endl;
		cout<< "----------------------" << endl;


	}

	cout << endl << endl << "punto 2";
	cout << "Dia - Cantidad - Total" << endl;

	double acumTotales = 0;
	int acumCant = 0;
	for (int j = 0; j < 50; j++) {
		if (estadisticas[j].acceso) {
			acumCant += estadisticas[j].cantidad;
			acumTotales += estadisticas[j].Total;
			cout << estadisticas[j].dia << "-" << estadisticas[j].cantidad << " - " << estadisticas[j].Total << endl;
		}
	}

	cout << "FIN------------------------------------------------------------------------";


};

