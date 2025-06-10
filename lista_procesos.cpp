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
