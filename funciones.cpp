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
    std::ifstream archivo("planes.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el fichero de planes.\n";
        return false;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        if (linea.find(nombrePlan) != std::string::npos) {
            // Verifica si el nombre del plan coincide exactamente
            return true;
        }
    }
    return false;
}

std::string obtenerFechaActual() {
    std::time_t t = std::time(nullptr);
    char fecha[20];
    std::strftime(fecha, sizeof(fecha), "%Y-%m-%d", std::localtime(&t));
    return std::string(fecha);
}

void inscribirAlumno() {
    Alumno nuevoAlumno;
    std::string dni, nombrePlan, universidad, carrera;

    // 1. Ingresar el DNI y verificar si está en alumnos.txt
    std::cout << "Ingrese el DNI del alumno: ";
    std::getline(std::cin, dni);
    if (!existeEnFichero(dni, "alumnos.txt")) {
        std::cout << "El alumno no cumple los requisitos para cursar el programa SICUE.\n";
        return;
    }

    // 2. Ingresar el nombre
    std::cout << "Ingrese el nombre: ";
    std::getline(std::cin, nuevoAlumno.nombre);

    // 3. Ingresar los apellidos
    std::cout << "Ingrese los apellidos: ";
    std::getline(std::cin, nuevoAlumno.apellidos);

    // 4. Ingresar el correo
    std::cout << "Ingrese el correo electrónico: ";
    std::getline(std::cin, nuevoAlumno.correo);

    // 5. Ingresar el nombre del plan y verificar que exista
    std::cout << "Ingrese el nombre del plan: ";
    std::getline(std::cin, nombrePlan);
    if (!existePlan(nombrePlan)) {
        std::cout << "El plan no existe.\n";
        return;  // Termina la ejecución de la función si el plan no existe
    }

    // 6. Ingresar cuatrimestre (1 o 2) y validar
    int cuatrimestre;
    std::cout << "Ingrese la duración del plan (1 para 1 cuatrimestre, 2 para 2 cuatrimestres): ";
    std::cin >> cuatrimestre;
    std::cin.ignore();  // Limpiar el buffer del cin
    if (cuatrimestre != 1 && cuatrimestre != 2) {
        std::cout << "Opción no válida. Debe seleccionar 1 o 2.\n";
        return;
    }

    // 7. Confirmar inscripción
    char confirmacion;
    std::cout << "¿Desea confirmar la inscripción? (S/N): ";
    std::cin >> confirmacion;
    std::cin.ignore();  // Limpiar el buffer del cin
    if (confirmacion == 'S' || confirmacion == 's') {
        // Guardar en inscritos.txt
        nuevoAlumno.dni = dni;  // Añadir el DNI a la estructura
        nuevoAlumno.estadoInscripcion = "Confirmado";
        nuevoAlumno.fechaInscripcion = obtenerFechaActual();
        std::ofstream archivoInscritos("inscritos.txt", std::ios::app);
        if (!archivoInscritos) {
            std::cerr << "Error al abrir el fichero de inscritos.\n";
            return;
        }
        archivoInscritos << nuevoAlumno.dni << ", "  // DNI
                         << nuevoAlumno.nombre << " " << nuevoAlumno.apellidos << ", "  // Nombre y Apellidos
                         << nuevoAlumno.correo << ", "  // Correo electrónico
                         << nombrePlan << ", "  // Nombre del plan
                         << cuatrimestre << " cuatrimestre(s)\n";  // Duración del plan
        std::cout << "Inscripción confirmada correctamente.\n";
    } else {
        std::cout << "Inscripción cancelada.\n";
    }
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
<<<<<<< HEAD

    // Leemos cada línea del archivo
    while (getline(archivo, linea)) {
        // Verificamos si la línea contiene el DNI del alumno
        if (linea.find(dni) != std::string::npos) {
            encontrado = true;

            // Extraemos la información relevante
            std::string nombre, apellidos, correo, plan, cuatrimestres, estado, fechaInscripcion;
            size_t pos = 0;
            
            // Obtenemos el DNI (es lo primero en la línea)
            pos = linea.find(", ");
            std::string dniAlumno = linea.substr(0, pos);
            linea = linea.substr(pos + 2);

            // Obtenemos el nombre completo
            pos = linea.find(", ");
            nombre = linea.substr(0, pos);
            linea = linea.substr(pos + 2);

            // Obtenemos el correo
            pos = linea.find(", ");
            correo = linea.substr(0, pos);
            linea = linea.substr(pos + 2);

            // Obtenemos el plan
            pos = linea.find(", ");
            plan = linea.substr(0, pos);
            linea = linea.substr(pos + 2);

            // Obtenemos los cuatrimestres
            pos = linea.find(", ");
            cuatrimestres = linea.substr(0, pos);
            linea = linea.substr(pos + 2);

            // Mostramos la información detallada
            std::cout << "Inscripción de: " << nombre << ", con DNI: " << dniAlumno << "\n";
            std::cout << "Plan seleccionado: " << plan << "\n";
            std::cout << "Duración: " << cuatrimestres << "\n";

            // Fecha de inscripción (si está en el archivo, la agregas aquí)
            fechaInscripcion = obtenerFechaActual();  // Aquí puedes poner la fecha real si está en el archivo
            std::cout << "Fecha de inscripción: " << fechaInscripcion << "\n";

            // Estado de la inscripción (puedes definir su valor o buscarlo en el archivo si es necesario)
            estado = "En trámite";  // Ajusta esto si el estado está en el archivo
            std::cout << "Estado de la inscripción: " << estado << "\n";

            break;
        }
    }

    if (!encontrado) {
        std::cout << "Alumno con DNI " << dni << " no encontrado. Aún no está inscrito.\n";
    }
=======
    while (getline(archivo, linea)) {
        if (linea.find(dni) != std::string::npos) {
            std::cout << "Información del alumno: " << linea << "\n";
            encontrado = true;
            break;
        }
    }
    if (!encontrado) std::cout << "Alumno no encontrado.\n";
>>>>>>> e63a7618487bf3ef99c076fe214f28da6bd2abd9
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


