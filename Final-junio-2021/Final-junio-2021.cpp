// Final-junio-2021.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
using namespace std;

template <typename T>
struct Nodo {
    T info;
    Nodo<T>* sig;
};

template <typename T>
Nodo<T>* buscarNodo(int id, bool *criterio, Nodo<T>* lista) {
    Nodo<T>* aux = lista;
    while (aux != NULL) {
        if (criterio(aux, id)) {
            return aux;
        }
        aux = aux->sig;
    }
}

template <typename T>
Nodo<T>* AgregarNodo(T info, Nodo<T>* &lista) {
    
    if (lista == NULL) {
        lista = new Nodo<T>;
        lista->info = info;
        lista->sig = NULL;
        return lista;
    }
    else {
        Nodo<T>* aux = lista;
        while (aux->sig != NULL) {

            aux = aux->sig;
        }
        Nodo<T>* nuevo = new Nodo<T>;
        nuevo->info = info;
        nuevo->sig = NULL;

        aux->sig = nuevo;
        return nuevo;
    }

}


struct Inscripcion{
    int idAlumno;
    int idCurso;

    Inscripcion(int ia, int ic) {
        idAlumno = ia;
        idCurso = ic;
    }
    Inscripcion(){}
    
};
struct Curso
{
    int idCurso;
    char turno;
    int capacidad;
    string materia;

    Curso(int id, char t, int c, string m) {
        idCurso = id;
        turno = t;
        capacidad = c;
        materia = m;
    }

    Curso(){}
    
};
struct CupoCurso {
    int idCurso;
    int inscriptos;
    CupoCurso(int id) {
        idCurso = id;
        inscriptos = 0;
    }
};

struct Materia {
    Nodo<Curso>* listaCursos = NULL;
    
    string cMateria;
    int Inscriptos = 0;

    Curso getCurso(int idCurso) {
        Nodo<Curso>* aux = listaCursos;
        while (aux != NULL) {
            if (aux->info.idCurso == idCurso) {
                return aux->info;
            }
            aux = aux->sig;
        }
    }
};

struct TadMaterias {
    Nodo<Materia>* listaMaterias = NULL;
    Nodo<CupoCurso>* listaCupos = NULL;

    Nodo<CupoCurso>* buscarCupoCurso(int idCurso) {
        Nodo<CupoCurso>* aux = listaCupos;

        while (aux != NULL) {
            if (aux->info.idCurso == idCurso) {
                return aux;
            }

            aux = aux->sig;
        }
    }
    void AgregarCursoAMateria(Curso curso) {
        AgregarNodo<CupoCurso>(*new CupoCurso(curso.idCurso), listaCupos);
        Nodo<Materia>* aux = listaMaterias;
       
       
            while (aux != NULL) {
                if (aux->info.cMateria == curso.materia) {
                    AgregarNodo<Curso>(curso, aux->info.listaCursos);
                    
                    return;
                }

                aux = aux->sig;

            }
            //No encontre la materia -> Creo la materia
            Materia* materia = new Materia();
            materia->cMateria = curso.materia;
            AgregarNodo<Curso>(curso, materia->listaCursos);
            
            AgregarNodo<Materia>(*materia, listaMaterias);
            return;
        
        
    }
    Nodo<Materia>* buscarMateriaConIdCurso(int idCurso) {
        Nodo<Materia>* aux = listaMaterias;
        while (aux != NULL) {
            Nodo<Curso>* auxCurso = aux->info.listaCursos;
            while (auxCurso != NULL) {
                if (auxCurso->info.idCurso == idCurso)
                {
                    return aux;
                }
                auxCurso = auxCurso->sig;
            }
            
            aux = aux->sig;

        }
    }

    void CargarCursosEnMaterias(Nodo<Curso>* lista) {
        Nodo<Curso>* aux = lista;
        while (aux != NULL) {
            AgregarCursoAMateria(aux->info);
            aux = aux->sig;
        }

    }

    void ImprimirPunto2() {
        Nodo<Materia>* aux = listaMaterias;

        
        
        while (aux != NULL) {
            Nodo<Curso>* auxCurso = aux->info.listaCursos;
            cout << "Materia libre " << aux->info.cMateria << endl;
            while (auxCurso != NULL) {
                Nodo<CupoCurso>* ncc = buscarCupoCurso(auxCurso->info.idCurso);
                if (auxCurso->info.capacidad >= ncc->info.inscriptos) {
                    cout << "Curso con cupos: " << ncc->info.idCurso << endl;
                }
                auxCurso = auxCurso->sig;
            }
            
            aux = aux->sig;
        }
    }
};

struct Alumno {
    int idAlumno;
    Nodo<string>* materiasRechazadas;

    Alumno(int id) {
        idAlumno = id;
        materiasRechazadas = NULL;
    }
    
};

struct TadAlumnos
{
    Nodo<Alumno>* listaAlumnos;

    Nodo<Alumno>* buscarAlumno(int idAlumno) {
        Nodo<Alumno>* aux = listaAlumnos;
        while (aux != NULL) {
            if (aux->info.idAlumno == idAlumno) {
                return aux;
            }
            aux = aux->sig;
        }
        return NULL;
    }

    int procesarInscripcion(Inscripcion inscripcion, TadMaterias tadMaterias ) {
        Nodo<Materia>* nodoMateria = tadMaterias.buscarMateriaConIdCurso(inscripcion.idCurso);
        Curso c = nodoMateria->info.getCurso(inscripcion.idCurso);
        Nodo<CupoCurso>* ncc = tadMaterias.buscarCupoCurso(inscripcion.idCurso);
        if (c.capacidad == ncc->info.inscriptos) {
            //Se rechaza por falta de capacidad
            Nodo<Alumno>* na = buscarAlumno(inscripcion.idAlumno);
            if (na == NULL) {
                na = AgregarNodo<Alumno>(*new Alumno(inscripcion.idAlumno), listaAlumnos);
                
            }
            AgregarNodo<string>(c.materia, na->info.materiasRechazadas);
        }
        else {
            ncc->info.inscriptos += 1;
            nodoMateria->info.Inscriptos += 1;
        }
    }

    void inprimirPunto1() {
        Nodo<Alumno>* aux = listaAlumnos;
        while (aux != NULL) {
            cout << "El alumno: " << aux->info.idAlumno << " - Tiene materias rechazadas" << endl;
            if (aux->info.materiasRechazadas != NULL) {
                Nodo<string> *auxRechazadas = aux->info.materiasRechazadas;
                while (auxRechazadas != NULL) {
                    cout << auxRechazadas->info << endl;
                    auxRechazadas = auxRechazadas->sig;
                }
            }
            aux = aux->sig;
        }
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

struct TadCursos {

    Nodo<Curso>* listaCursos = NULL;

    void escribirArhivoCursos() {
        FILE* f = fopen("cursos.dat", "w+b");
        Curso* c1 = new Curso(1, 'T', 4, "Algebra");
        Curso* c2 = new Curso(2, 'T', 4, "Ingles");
        Curso* c3 = new Curso(3, 'M', 5, "Ingles");
        Curso* c4 = new Curso(4, 'M', 6, "Algebra");
        Curso* c5 = new Curso(5, 'N', 2, "Algebra");
        Curso* c6 = new Curso(6, 'M', 5, "Analisis");
        Curso cursos[6] = { *c1,*c2,*c3,*c4,*c5,*c6 };

        fwrite(cursos, sizeof(Curso), 6, f);
        fclose(f);
    }

    //Leer y guardar cursos en listaCursos
    void leerArchivoCursos() {
        FILE* f = fopen("cursos.dat", "r+b");
        Curso* curso = new Curso();

        fread(curso, sizeof(Curso), 1, f);
        

        while (!feof(f)) {
            AgregarNodo<Curso>(*curso, listaCursos);
            fread(curso, sizeof(Curso), 1, f);
        }
    }
};




int main()
{
    //escribirArhivoCursos();
    //escribirArhivoInscripcion();
    TadCursos tadCursos;
    TadMaterias tadMaterias;
    TadAlumnos tadAlumnos;
    
    tadCursos.leerArchivoCursos();
    
    tadMaterias.CargarCursosEnMaterias(tadCursos.listaCursos);

    FILE* f = fopen("inscripcion.dat", "r+b");
    Inscripcion* inscripcion = new Inscripcion();
    fread(inscripcion, sizeof(Inscripcion), 1, f);

    while (!feof(f)) {
        tadAlumnos.procesarInscripcion(*inscripcion, tadMaterias);

        fread(inscripcion, sizeof(Inscripcion), 1, f);
    }


    tadAlumnos.inprimirPunto1();
    tadMaterias.ImprimirPunto2();

    return 0;
};

