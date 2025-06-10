#include <iostream>
using namespace std;

//Funciones prototipo


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
