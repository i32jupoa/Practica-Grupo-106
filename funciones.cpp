#include "funciones.h"

// Función genérica para buscar si un dato existe en un fichero
bool existeEnFichero(const std::string &dato, const std::string &fichero) {
    std::ifstream archivo(fichero);
    std::string linea;
    while (getline(archivo, linea)) {
        if (linea.find(dato) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool perteneceAUniversidad(const std::string &universidad) {
    std::ifstream archivo("universidad.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el fichero de universidades.\n";
        return false;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        if (linea == universidad) {  // Compara si la línea es exactamente la universidad
            return true;
        }
    }
    return false;
}

bool existeCarrera(const std::string &carrera) {
    std::ifstream archivo("carrera.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el fichero de carreras.\n";
        return false;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        if (linea == carrera) {  // Compara si la línea es exactamente la carrera
            return true;
        }
    }
    return false;
}

bool existePlan(const std::string &nombrePlan) {
    return existeEnFichero(nombrePlan, "planes.txt");
}

std::string obtenerFechaActual() {
    std::time_t t = std::time(nullptr);
    char fecha[20];
    std::strftime(fecha, sizeof(fecha), "%Y-%m-%d", std::localtime(&t));
    return std::string(fecha);
}

void inscribirAlumno() {
    Alumno nuevoAlumno;
    std::string universidad, carrera;

    // Datos del alumno
    std::cout << "Ingrese el nombre: ";
    std::getline(std::cin, nuevoAlumno.nombre);
    std::cout << "Ingrese los apellidos: ";
    std::getline(std::cin, nuevoAlumno.apellidos);
    std::cout << "Ingrese el DNI: ";
    std::getline(std::cin, nuevoAlumno.dni);

    // Universidad
    std::cout << "Ingrese la universidad: ";
    std::getline(std::cin, universidad);
    if (!perteneceAUniversidad(universidad)) {
        std::cout << "La universidad no admite el plan SICUE.\n";
        return;
    }

    // Carrera
    std::cout << "Ingrese la carrera: ";
    std::getline(std::cin, carrera);
    if (!existeCarrera(carrera)) {
        std::cout << "La carrera no existe en el sistema.\n";
        return;
    }

    // Asignaturas
    std::vector<std::string> asignaturas;
    std::string asignatura;
    std::cout << "Ingrese las asignaturas a cursar (escriba 'fin' para terminar): \n";
    while (true) {
        std::getline(std::cin, asignatura);
        if (asignatura == "fin") break;
        asignaturas.push_back(asignatura);
    }

    // Guardar en planes.txt
    std::ofstream archivoPlanes("planes.txt", std::ios::app);
    if (!archivoPlanes) {
        std::cerr << "Error al abrir el fichero de planes.\n";
        return;
    }
    archivoPlanes << "Plan: " << carrera << ", Universidad: " << universidad << ", Asignaturas: ";
    for (const auto &asig : asignaturas) archivoPlanes << asig << " ";
    archivoPlanes << "\n";

    // Guardar en inscritos.txt
    nuevoAlumno.estadoInscripcion = "En trámite";
    nuevoAlumno.fechaInscripcion = obtenerFechaActual();
    std::ofstream archivoInscritos("inscritos.txt", std::ios::app);
    archivoInscritos << nuevoAlumno.nombre << ", " << nuevoAlumno.apellidos << ", "
                     << nuevoAlumno.dni << ", " << nuevoAlumno.estadoInscripcion << ", Fecha: "
                     << nuevoAlumno.fechaInscripcion << "\n";

    std::cout << "Alumno inscrito correctamente.\n";
}

void agregarPlan() {
    std::string nombrePlan, universidadOrigen, universidadDestino, carrera;

    // 1. Ingresar el nombre del plan
    std::cout << "Ingrese el nombre del plan: ";
    std::getline(std::cin, nombrePlan);

    // 2. Universidad de origen
    std::cout << "Ingrese la universidad de origen: ";
    std::getline(std::cin, universidadOrigen);
    if (!perteneceAUniversidad(universidadOrigen)) {
        std::cout << "La universidad de origen no se encuentra en el programa SICUE.\n";
        return;
    }

    // 3. Universidad de destino
    std::cout << "Ingrese la universidad de destino: ";
    std::getline(std::cin, universidadDestino);
    if (!perteneceAUniversidad(universidadDestino)) {
        std::cout << "La universidad de destino no se encuentra en el programa SICUE.\n";
        return;
    }

    // 4. Carrera asociada al plan
    std::cout << "Ingrese la carrera asociada al plan: ";
    std::getline(std::cin, carrera);
    if (!existeCarrera(carrera)) {
        std::cout << "La carrera no existe en el sistema.\n";
        return;
    }

    // 5. Guardar el plan en el fichero planes.txt
    std::ofstream archivo("planes.txt", std::ios::app);
    if (!archivo) {
        std::cerr << "Error al abrir el fichero de planes.\n";
        return;
    }
    archivo << nombrePlan << ": " << universidadOrigen << " --> " << universidadDestino  << ", Carrera: " << carrera << "\n";

    std::cout << "Plan de convalidación agregado correctamente.\n";
}

void consultarInscripcion() {
    std::string dni;
    std::cout << "Ingrese el DNI del alumno: ";
    std::getline(std::cin, dni);

    std::ifstream archivo("inscritos.txt");
    std::string linea;
    bool encontrado = false;
    while (getline(archivo, linea)) {
        if (linea.find(dni) != std::string::npos) {
            std::cout << "Información del alumno: " << linea << "\n";
            encontrado = true;
            break;
        }
    }
    if (!encontrado) std::cout << "Alumno no encontrado.\n";
}

void mostrarInscritos() {
    std::ifstream archivo("inscritos.txt");
    std::string linea;
    std::cout << "--- Lista de inscritos ---\n";
    while (getline(archivo, linea)) {
        std::cout << linea << "\n";
    }
}

void pruebasErrores() {
    std::cout << "\n--- Pruebas de errores ---\n";

    std::cout << "1. Intentar agregar un plan con universidad inexistente.\n";
    agregarPlan();

    std::cout << "2. Intentar inscribir un alumno en una carrera inválida.\n";
    inscribirAlumno();

    std::cout << "3. Consultar un alumno inexistente.\n";
    consultarInscripcion();
}


