#include <iostream>
#include <string>

using namespace std;

// Estructura que representa un proceso en la lista enlazada
struct Proceso {
    int id;                // Identificador único del proceso
    std::string nombre;    // Nombre del proceso
    int prioridad;         // Prioridad del proceso
    Proceso* siguiente;    // Puntero al siguiente proceso en la lista
};

// Clase para gestionar una lista enlazada de procesos
class GestorProcesos {
private:
    Proceso* cabeza;   // Puntero al primer proceso de la lista
    int contador;      // Contador para asignar IDs únicos

public:
    // Constructor: inicializa lista vacía y contador en 0
    GestorProcesos() {
        cabeza = NULL;
        contador = 0;
    }

    // Inserta un nuevo proceso al inicio de la lista
    void insertarProceso(const string& nombre, int prioridad) {
        Proceso* nuevo = new Proceso;
        nuevo->id = ++contador;          // Asigna ID único
        nuevo->nombre = nombre;
        nuevo->prioridad = prioridad;
        nuevo->siguiente = cabeza;       // Inserta al inicio
        cabeza = nuevo;

        cout << "Proceso insertado: " << nombre << " (ID: " << nuevo->id << ", Prioridad: " << prioridad << ")\n";
    }

    // Elimina un proceso por su ID
    void eliminarProceso(int id) {
        Proceso* actual = cabeza;
        Proceso* anterior = NULL;

        // Recorre la lista buscando el proceso por ID
        while (actual != NULL && actual->id != id) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (actual == NULL) {
            cout << "Proceso no encontrado.\n";
            return;
        }

        // Reenlaza los nodos para eliminar el proceso
        if (anterior == NULL)
            cabeza = actual->siguiente;
        else
            anterior->siguiente = actual->siguiente;

        delete actual;
        cout << "Proceso eliminado.\n";
    }

    // Busca un proceso por su ID
    Proceso* buscarPorID(int id) {
        Proceso* actual = cabeza;
        while (actual != NULL) {
            if (actual->id == id)
                return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }

    // Busca un proceso por su nombre
    Proceso* buscarPorNombre(const string& nombre) {
        Proceso* actual = cabeza;
        while (actual != NULL) {
            if (actual->nombre == nombre)
                return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }

    // Modifica la prioridad de un proceso dado su ID
    void modificarPrioridad(int id, int nuevaPrioridad) {
        Proceso* p = buscarPorID(id);
        if (p) {
            p->prioridad = nuevaPrioridad;
            cout << "Prioridad modificada.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }

    // Muestra todos los procesos en la lista
    void listarProcesos() {
        Proceso* actual = cabeza;
        if (actual == NULL) {
            cout << "No hay procesos registrados.\n";
            return;
        }
        while (actual != NULL) {
            cout << "ID: " << actual->id 
                 << ", Nombre: " << actual->nombre 
                 << ", Prioridad: " << actual->prioridad << "\n";
            actual = actual->siguiente;
        }
    }
};

// Función principal con menú de usuario
int main() {
    GestorProcesos gestor;
    int opcion;

    do {
        // Menú de opciones
        cout << "\n===== MENU DE GESTION DE PROCESOS =====\n";
        cout << "1. Insertar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Buscar proceso por ID\n";
        cout << "4. Buscar proceso por nombre\n";
        cout << "5. Modificar prioridad de proceso\n";
        cout << "6. Listar todos los procesos\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nombre;
                int prioridad;
                cout << "Ingrese nombre del proceso: ";
                cin.ignore(); // Limpia el buffer de entrada
                getline(cin, nombre);
                cout << "Ingrese prioridad del proceso: ";
                cin >> prioridad;
                gestor.insertarProceso(nombre, prioridad);
                break;
            }
            case 2: {
                int id;
                cout << "Ingrese ID del proceso a eliminar: ";
                cin >> id;
                gestor.eliminarProceso(id);
                break;
            }
            case 3: {
                int id;
                cout << "Ingrese ID del proceso a buscar: ";
                cin >> id;
                Proceso* p = gestor.buscarPorID(id);
                if (p) {
                    cout << "Proceso encontrado: ID: " << p->id << ", Nombre: " << p->nombre << ", Prioridad: " << p->prioridad << "\n";
                } else {
                    cout << "Proceso no encontrado.\n";
                }
                break;
            }
            case 4: {
                string nombre;
                cout << "Ingrese nombre del proceso a buscar: ";
                cin.ignore(); // Limpia el buffer
                getline(cin, nombre);
                Proceso* p = gestor.buscarPorNombre(nombre);
                if (p) {
                    cout << "Proceso encontrado: ID: " << p->id << ", Nombre: " << p->nombre << ", Prioridad: " << p->prioridad << "\n";
                } else {
                    cout << "Proceso no encontrado.\n";
                }
                break;
            }
            case 5: {
                int id, nuevaPrioridad;
                cout << "Ingrese ID del proceso: ";
                cin >> id;
                cout << "Ingrese nueva prioridad: ";
                cin >> nuevaPrioridad;
                gestor.modificarPrioridad(id, nuevaPrioridad);
                break;
            }
            case 6:
                gestor.listarProcesos();
                break;
            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}

