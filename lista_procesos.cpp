#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

// Prototipos de funciones generales
void limpiarConsola();
int validarPrioridad();
int validarMemoria();
string obtenerNombrePrioridad(int prioridad);
void pausar();

// Estructuras de datos
struct Proceso {
    int id;
    string nombre;
    int prioridad; // 0=Baja, 1=Media, 2=Alta
    int memoria;
};

struct NodoLista {
    Proceso proceso;
    NodoLista* siguiente;
};

struct GestorProcesos {
    NodoLista* cabeza;
    int contador_id;
};

struct NodoCola {
    Proceso proceso;
    NodoCola* siguiente;
};

struct PlanificadorCPU {
    NodoCola* frente;
};

struct NodoPila {
    int tamano;
    int id_proceso;
    NodoPila* siguiente;
};

struct GestorMemoria {
    NodoPila* tope;
    int memoria_total;
    int memoria_disponible;
};

// Prototipos de funciones del Gestor de Procesos
void inicializarGestor(GestorProcesos* gp);
void insertarProceso(GestorProcesos* gp, string nombre, int prioridad, int memoria);
bool eliminarProceso(GestorProcesos* gp, int id);
Proceso* buscarPorId(GestorProcesos* gp, int id);
Proceso* buscarPorNombre(GestorProcesos* gp, string nombre);
bool modificarPrioridad(GestorProcesos* gp, int id, int nuevaPrioridad);
void mostrarProcesos(GestorProcesos* gp);

// Prototipos de funciones del Planificador de CPU
void inicializarPlanificador(PlanificadorCPU* pc);
void encolarProceso(PlanificadorCPU* pc, Proceso p);
Proceso desencolarProceso(PlanificadorCPU* pc);
void mostrarCola(PlanificadorCPU* pc);
bool estaVacia(PlanificadorCPU* pc);

// Prototipos de funciones del Gestor de Memoria
void inicializarGestorMemoria(GestorMemoria* gm, int total);
bool asignarMemoria(GestorMemoria* gm, int tamano, int id_proceso);
bool liberarMemoria(GestorMemoria* gm);
void mostrarEstadoMemoria(GestorMemoria* gm);

// Prototipos de funciones de menú
void mostrarMenu();
void menuGestorProcesos(GestorProcesos* gp);
void menuPlanificadorCPU(PlanificadorCPU* pc, GestorProcesos* gp);
void menuGestorMemoria(GestorMemoria* gm, GestorProcesos* gp);

// Función principal
int main() {
    system("color F0");
    SetConsoleTitle("Administrador de Procesos");
    setlocale(LC_CTYPE,"Spanish");
    
    GestorProcesos gp;
    inicializarGestor(&gp);
    
    PlanificadorCPU pc;
    inicializarPlanificador(&pc);
    
    GestorMemoria gm;
    inicializarGestorMemoria(&gm, 16384); // 16GB de memoria total
    
    int opcion;
    do {
        limpiarConsola();
        mostrarMenu();
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                menuGestorProcesos(&gp);
                break;
            case 2:
                menuPlanificadorCPU(&pc, &gp);
                break;
            case 3:
                menuGestorMemoria(&gm, &gp);
                break;
            case 4:
                cout << "\nSaliendo del sistema...\n";
                break;
            default:
                cout << "\nOpción no válida. Intente de nuevo.\n";
                pausar();
        }
    } while (opcion != 4);
    
    return 0;
}

// Implementación de funciones generales
void limpiarConsola() {
    system("cls");
}

int validarPrioridad() {
    int prioridad;
    cin >> prioridad;
    while (prioridad < 0 || prioridad > 2) {
        cout << "Dato no válido (0=Baja, 1=Media, 2=Alta). Intente de nuevo: ";
        cin >> prioridad;
    }
    return prioridad;
}

int validarMemoria() {
    int memoria;
    cin >> memoria;
    while (memoria < 0) {
        cout << "No se puede ingresar memoria negativa. Intente de nuevo: ";
        cin >> memoria;
    }
    return memoria;
}

string obtenerNombrePrioridad(int prioridad) {
    switch(prioridad) {
        case 0: return "Baja";
        case 1: return "Media";
        case 2: return "Alta";
        default: return "Desconocida";
    }
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Implementación de funciones del Gestor de Procesos
void inicializarGestor(GestorProcesos* gp) {
    gp->cabeza = NULL;
    gp->contador_id = 1;
}

void insertarProceso(GestorProcesos* gp, string nombre, int prioridad, int memoria) {
    Proceso nuevo;
    nuevo.id = gp->contador_id++;
    nuevo.nombre = nombre;
    nuevo.prioridad = prioridad;
    nuevo.memoria = memoria;
    
    NodoLista* nuevoNodo = new NodoLista;
    nuevoNodo->proceso = nuevo;
    nuevoNodo->siguiente = NULL;
    
    if (!gp->cabeza) {
        gp->cabeza = nuevoNodo;
    } else {
        NodoLista* actual = gp->cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

bool eliminarProceso(GestorProcesos* gp, int id) {
    if (!gp->cabeza) return false;
    
    if (gp->cabeza->proceso.id == id) {
        NodoLista* temp = gp->cabeza;
        gp->cabeza = gp->cabeza->siguiente;
        delete temp;
        return true;
    }
    
    NodoLista* actual = gp->cabeza;
    while (actual->siguiente && actual->siguiente->proceso.id != id) {
        actual = actual->siguiente;
    }
    
    if (actual->siguiente) {
        NodoLista* temp = actual->siguiente;
        actual->siguiente = actual->siguiente->siguiente;
        delete temp;
        return true;
    }
    
    return false;
}

Proceso* buscarPorId(GestorProcesos* gp, int id) {
    NodoLista* actual = gp->cabeza;
    while (actual) {
        if (actual->proceso.id == id) {
            return &(actual->proceso);
        }
        actual = actual->siguiente;
    }
    return NULL;
}

Proceso* buscarPorNombre(GestorProcesos* gp, string nombre) {
    NodoLista* actual = gp->cabeza;
    while (actual) {
        if (actual->proceso.nombre == nombre) {
            return &(actual->proceso);
        }
        actual = actual->siguiente;
    }
    return NULL;
}

bool modificarPrioridad(GestorProcesos* gp, int id, int nuevaPrioridad) {
    Proceso* proc = buscarPorId(gp, id);
    if (proc) {
        proc->prioridad = nuevaPrioridad;
        return true;
    }
    return false;
}

void mostrarProcesos(GestorProcesos* gp) {
    limpiarConsola();
    NodoLista* actual = gp->cabeza;
    cout << "\n--- Lista de Procesos ---\n";
    while (actual) {
        cout << "ID: " << actual->proceso.id 
             << ", Nombre: " << actual->proceso.nombre 
             << ", Prioridad: " << obtenerNombrePrioridad(actual->proceso.prioridad)
             << ", Memoria: " << actual->proceso.memoria << "MB\n";
        actual = actual->siguiente;
    }
    cout << "-------------------------\n";
}

// Implementación de funciones del Planificador de CPU
void inicializarPlanificador(PlanificadorCPU* pc) {
    pc->frente = NULL;
}

void encolarProceso(PlanificadorCPU* pc, Proceso p) {
    NodoCola* nuevoNodo = new NodoCola;
    nuevoNodo->proceso = p;
    nuevoNodo->siguiente = NULL;
    
    if (!pc->frente || p.prioridad > pc->frente->proceso.prioridad) {
        nuevoNodo->siguiente = pc->frente;
        pc->frente = nuevoNodo;
    } else {
        NodoCola* actual = pc->frente;
        while (actual->siguiente && actual->siguiente->proceso.prioridad >= p.prioridad) {
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }
}

Proceso desencolarProceso(PlanificadorCPU* pc) {
    Proceso resultado;
    resultado.id = -1;
    
    if (pc->frente) {
        NodoCola* temp = pc->frente;
        resultado = pc->frente->proceso;
        pc->frente = pc->frente->siguiente;
        delete temp;
    }
    
    return resultado;
}

void mostrarCola(PlanificadorCPU* pc) {
    limpiarConsola();
    NodoCola* actual = pc->frente;
    cout << "\n--- Cola de Procesos (Prioridad) ---\n";
    while (actual) {
        cout << "ID: " << actual->proceso.id 
             << ", Nombre: " << actual->proceso.nombre 
             << ", Prioridad: " << obtenerNombrePrioridad(actual->proceso.prioridad)
             << ", Memoria: " << actual->proceso.memoria << "MB\n";
        actual = actual->siguiente;
    }
    cout << "-----------------------------------\n";
}

bool estaVacia(PlanificadorCPU* pc) {
    return pc->frente == NULL;
}

// Implementación de funciones del Gestor de Memoria
void inicializarGestorMemoria(GestorMemoria* gm, int total) {
    gm->tope = NULL;
    gm->memoria_total = total;
    gm->memoria_disponible = total;
}

bool asignarMemoria(GestorMemoria* gm, int tamano, int id_proceso) {
    if (tamano > gm->memoria_disponible) {
        return false;
    }
    
    NodoPila* nuevoBloque = new NodoPila;
    nuevoBloque->tamano = tamano;
    nuevoBloque->id_proceso = id_proceso;
    nuevoBloque->siguiente = gm->tope;
    gm->tope = nuevoBloque;
    gm->memoria_disponible -= tamano;
    return true;
}

bool liberarMemoria(GestorMemoria* gm) {
    if (!gm->tope) {
        return false;
    }
    
    NodoPila* temp = gm->tope;
    gm->memoria_disponible += gm->tope->tamano;
    gm->tope = gm->tope->siguiente;
    delete temp;
    return true;
}

void mostrarEstadoMemoria(GestorMemoria* gm) {
    limpiarConsola();
    cout << "\n--- Estado de Memoria ---\n";
    cout << "Memoria total: " << gm->memoria_total << "MB\n";
    cout << "Memoria disponible: " << gm->memoria_disponible << "MB\n";
    cout << "Memoria en uso: " << (gm->memoria_total - gm->memoria_disponible) << "MB\n";
    
    cout << "Bloques asignados:\n";
    NodoPila* actual = gm->tope;
    while (actual) {
        cout << "Proceso ID: " << actual->id_proceso 
             << ", Bloque: " << actual->tamano << "MB\n";
        actual = actual->siguiente;
    }
    cout << "-------------------------\n";
}

// Implementación de funciones de menú
void mostrarMenu() {
    cout << "\n=== Sistema de Gestión de Procesos ===\n";
    cout << "1. Gestor de Procesos\n";
    cout << "2. Planificador de CPU\n";
    cout << "3. Gestor de Memoria\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opción: ";
}

void menuGestorProcesos(GestorProcesos* gp) {
    int opcion;
    do {
        limpiarConsola();
        cout << "\n--- Gestor de Procesos ---\n";
        cout << "1. Insertar nuevo proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Buscar proceso por ID\n";
        cout << "4. Buscar proceso por nombre\n";
        cout << "5. Modificar prioridad\n";
        cout << "6. Mostrar todos los procesos\n";
        cout << "7. Regresar\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                string nombre;
                int prioridad, memoria;
                cout << "Nombre del proceso: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Prioridad (0=Baja, 1=Media, 2=Alta): ";
                prioridad = validarPrioridad();
                cout << "Memoria requerida (MB): ";
                memoria = validarMemoria();
                
                insertarProceso(gp, nombre, prioridad, memoria);
                cout << "\nProceso agregado exitosamente.\n";
                pausar();
                break;
            }
            case 2: {
                int id;
                cout << "ID del proceso a eliminar: ";
                cin >> id;
                if (eliminarProceso(gp, id)) {
                    cout << "\nProceso eliminado exitosamente.\n";
                } else {
                    cout << "\nNo se encontró el proceso con ID " << id << ".\n";
                }
                pausar();
                break;
            }
            case 3: {
                int id;
                cout << "ID del proceso a buscar: ";
                cin >> id;
                Proceso* proc = buscarPorId(gp, id);
                if (proc) {
                    cout << "\nProceso encontrado:\n";
                    cout << "ID: " << proc->id << ", Nombre: " << proc->nombre 
                         << ", Prioridad: " << obtenerNombrePrioridad(proc->prioridad)
                         << ", Memoria: " << proc->memoria << "MB\n";
                } else {
                    cout << "\nProceso no encontrado.\n";
                }
                pausar();
                break;
            }
            case 4: {
                string nombre;
                cout << "Nombre del proceso a buscar: ";
                cin.ignore();
                getline(cin, nombre);
                Proceso* proc = buscarPorNombre(gp, nombre);
                if (proc) {
                    cout << "\nProceso encontrado:\n";
                    cout << "ID: " << proc->id << ", Nombre: " << proc->nombre 
                         << ", Prioridad: " << obtenerNombrePrioridad(proc->prioridad)
                         << ", Memoria: " << proc->memoria << "MB\n";
                } else {
                    cout << "\nProceso no encontrado.\n";
                }
                pausar();
                break;
            }
            case 5: {
                int id, nuevaPrioridad;
                cout << "ID del proceso a modificar: ";
                cin >> id;
                cout << "Nueva prioridad (0=Baja, 1=Media, 2=Alta): ";
                nuevaPrioridad = validarPrioridad();
                if (modificarPrioridad(gp, id, nuevaPrioridad)) {
                    cout << "\nPrioridad actualizada exitosamente.\n";
                } else {
                    cout << "\nNo se encontró el proceso con ID " << id << ".\n";
                }
                pausar();
                break;
            }
            case 6:
                mostrarProcesos(gp);
                pausar();
                break;
            case 7:
                return;
            default:
                cout << "\nOpción no válida.\n";
                pausar();
        }
    } while (opcion != 7);
}

void menuPlanificadorCPU(PlanificadorCPU* pc, GestorProcesos* gp) {
    int opcion;
    do {
        limpiarConsola();
        cout << "\n--- Planificador de CPU ---\n";
        cout << "1. Encolar proceso\n";
        cout << "2. Desencolar y ejecutar proceso\n";
        cout << "3. Mostrar cola de procesos\n";
        cout << "4. Regresar\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                int id;
                cout << "ID del proceso a encolar: ";
                cin >> id;
                Proceso* proc = buscarPorId(gp, id);
                if (proc) {
                    encolarProceso(pc, *proc);
                    cout << "\nProceso encolado exitosamente.\n";
                } else {
                    cout << "\nNo se encontró el proceso con ID " << id << ".\n";
                }
                pausar();
                break;
            }
            case 2: {
                Proceso proc = desencolarProceso(pc);
                if (proc.id != -1) {
                    cout << "\nEjecutando proceso:\n";
                    cout << "ID: " << proc.id << ", Nombre: " << proc.nombre 
                         << ", Prioridad: " << obtenerNombrePrioridad(proc.prioridad)
                         << ", Memoria: " << proc.memoria << "MB\n";
                } else {
                    cout << "\nNo hay procesos en la cola.\n";
                }
                pausar();
                break;
            }
            case 3:
                mostrarCola(pc);
                pausar();
                break;
            case 4:
                return;
            default:
                cout << "\nOpción no válida.\n";
                pausar();
        }
    } while (opcion != 4);
}

void menuGestorMemoria(GestorMemoria* gm, GestorProcesos* gp) {
    int opcion;
    do {
        limpiarConsola();
        cout << "\n--- Gestor de Memoria ---\n";
        cout << "1. Asignar memoria a proceso\n";
        cout << "2. Liberar memoria\n";
        cout << "3. Mostrar estado de memoria\n";
        cout << "4. Regresar\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
                int id, memoria;
                cout << "ID del proceso: ";
                cin >> id;
                Proceso* proc = buscarPorId(gp, id);
                if (proc) {
                    cout << "Memoria a asignar (MB): ";
                    memoria = validarMemoria();
                    if (asignarMemoria(gm, memoria, id)) {
                        cout << "\nMemoria asignada exitosamente.\n";
                    } else {
                        cout << "\nNo hay suficiente memoria disponible.\n";
                    }
                } else {
                    cout << "\nNo se encontró el proceso con ID " << id << ".\n";
                }
                pausar();
                break;
            }
            case 2:
                if (liberarMemoria(gm)) {
                    cout << "\nMemoria liberada exitosamente.\n";
                } else {
                    cout << "\nNo hay bloques de memoria asignados.\n";
                }
                pausar();
                break;
            case 3:
                mostrarEstadoMemoria(gm);
                pausar();
                break;
            case 4:
                return;
            default:
                cout << "\nOpción no válida.\n";
                pausar();
        }
    } while (opcion != 4);
}
