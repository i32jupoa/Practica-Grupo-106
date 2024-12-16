#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cassert>
#include <sstream>
#include <cctype>
#include <algorithm>

struct Alumno {
    std::string nombre;
    std::string apellidos;
    std::string dni;
    std::string correo;
    std::string estadoInscripcion;
    std::string fechaInscripcion;
};

struct Plan {
    std::string nombre;
    std::string universidad;
    std::vector<std::string> asignaturas;
};

bool existeEnFichero(const std::string &dato, const std::string &fichero);
bool perteneceAUniversidad(const std::string &universidad);
bool existeCarrera(const std::string &carrera);
bool existePlan(const std::string &nombrePlan);
void inscribirAlumno();
void agregarPlan();
void consultarInscripcion();
void mostrarInscritos();
void pruebasErrores();
std::string obtenerFechaActual();
void pruebaPerteneceAUniversidad();
void pruebaExisteCarrera();
void pruebaObtenerFechaActual();
void pruebaGenerarFichero();

#endif