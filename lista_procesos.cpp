#include <iostream>
#include <windows.h> 
using namespace std;

//Funciones prototipo
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

//Coloquen las funciones en orden , yo ordenares en el menu
//Yoset la parte de Gestor de procesos
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


// Prototipos de funciones del Planificador de CPU
void inicializarPlanificador(PlanificadorCPU* pc);
void encolarProceso(PlanificadorCPU* pc, Proceso p);
Proceso desencolarProceso(PlanificadorCPU* pc);
void mostrarCola(PlanificadorCPU* pc);
bool estaVacia(PlanificadorCPU* pc);
//Gestor de Memoria Anderson 


int main(){
  system("color F0"); 
  SetConsoleTitle("Administrador de Procesos");
  setlocale(LC_CTYPE,"Spanish");
return 0;
};

//Colocar a aqui las funciones

void mostrarMenu() {
    cout << "\n=== Sistema de Gestión de Procesos ===\n";
    cout << "1. Gestor de Procesos\n";
    cout << "2. Planificador de CPU\n";
    cout << "3. Gestor de Memoria\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opción: ";
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
