// Final-junio-2021.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
using namespace std;



struct Inscripcion{
    int idAlumno;
    int idCurso;

    Inscripcion(int ia, int ic) {
        idAlumno = ia;
        idCurso = ic;
    }
};
struct Curso
{
    int idCurso;
    char turno;
    int capacidad;
    string materia;
    Curso() {
    }
    Curso(int id, char t, int c, string m) {
        idCurso = id;
        turno = t;
        capacidad = c;
        materia = m;
    }
    
};


void escribirArhivoCursos() {
    FILE* f = fopen("cursos.dat", "w+b");
    Curso* c1 = new Curso(1, 'T', 4, "Algebra");
    Curso* c2 = new Curso(2, 'T', 4, "Ingles");
    Curso* c3 = new Curso(3, 'M', 5, "Ingles");
    Curso* c4 = new Curso(4, 'M', 6, "Algebra");
    Curso* c5 = new Curso(5, 'N', 2, "Algebra");
    Curso* c6 = new Curso(6, 'M', 5, "Analisis");
    Curso cursos[6] = {*c1,*c2,*c3,*c4,*c5,*c6};

    fwrite(cursos, sizeof(Curso), 6, f);
    fclose(f);
}

void escribirArhivoInscripcion() {
    FILE* f = fopen("inscripcion.dat", "w+b");

    Inscripcion* i1 = new Inscripcion(1, 6);
    Inscripcion* i2 = new Inscripcion(2, 1);
    Inscripcion* i3 = new Inscripcion(3, 5);
    Inscripcion* i4 = new Inscripcion(4, 1);
    Inscripcion* i5 = new Inscripcion(5, 4);
    Inscripcion* i6 = new Inscripcion(6, 1);
    Inscripcion* i7 = new Inscripcion(7, 1);
    Inscripcion* i8 = new Inscripcion(8, 1);
    Inscripcion* i11 = new Inscripcion(6, 2);
    Inscripcion* i12 = new Inscripcion(7, 2);
    Inscripcion* i13 = new Inscripcion(8, 2);
    Inscripcion* i9 = new Inscripcion(9, 1);
    Inscripcion* i10 = new Inscripcion(10, 1);
    Inscripcion* i14 = new Inscripcion(6, 3);
    Inscripcion* i15 = new Inscripcion(7, 3);
    Inscripcion* i16 = new Inscripcion(8, 3);
    Inscripcion* i17 = new Inscripcion(9, 3);
    Inscripcion* i18 = new Inscripcion(10,2);

    Inscripcion inscripciones[18] = { 
        *i1,*i2,*i3,
        *i4,*i5,*i6,*i7,*i8,*i9,*i10, 
        *i11, *i12, *i13, *i14, *i15 , 
        *i16, *i17, *i18 };

    fwrite(inscripciones, sizeof(Inscripcion), 10, f);
    fclose(f);
}

int main()
{
    escribirArhivoCursos();
    escribirArhivoInscripcion();


    

    return 0;
};

