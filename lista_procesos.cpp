#include <iostream>
#include <string>

using namespace std;

struct Proceso {
    int id;
    std::string nombre;
    int prioridad;
    Proceso* siguiente;
};

class GestorProcesos {
private:
    Proceso* cabeza;
    int contador;

public:
    GestorProcesos() {
        cabeza = NULL;
        contador = 0;
    }

    void insertarProceso(const string& nombre, int prioridad) {
        Proceso* nuevo = new Proceso;
        nuevo->id = ++contador;
        nuevo->nombre = nombre;
        nuevo->prioridad = prioridad;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cout << "Proceso insertado: " << nombre << " (ID: " << nuevo->id << ", Prioridad: " << prioridad << ")\n";
    }

    void eliminarProceso(int id) {
        Proceso* actual = cabeza;
        Proceso* anterior = NULL;

        while (actual != NULL && actual->id != id) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (actual == NULL) {
            cout << "Proceso no encontrado.\n";
            return;
        }

        if (anterior == NULL)
            cabeza = actual->siguiente;
        else
            anterior->siguiente = actual->siguiente;

        delete actual;
        cout << "Proceso eliminado.\n";
    }

    Proceso* buscarPorID(int id) {
        Proceso* actual = cabeza;
        while (actual != NULL) {
            if (actual->id == id)
                return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }

    Proceso* buscarPorNombre(const string& nombre) {
        Proceso* actual = cabeza;
        while (actual != NULL) {
            if (actual->nombre == nombre)
                return actual;
            actual = actual->siguiente;
        }
        return NULL;
    }

    void modificarPrioridad(int id, int nuevaPrioridad) {
        Proceso* p = buscarPorID(id);
        if (p) {
            p->prioridad = nuevaPrioridad;
            cout << "Prioridad modificada.\n";
        } else {
            cout << "Proceso no encontrado.\n";
        }
    }

    void listarProcesos() {
        Proceso* actual = cabeza;
        while (actual != NULL) {
            cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << ", Prioridad: " << actual->prioridad << "\n";
            actual = actual->siguiente;
        }
    }
};

int main() {
    GestorProcesos gestor;
    int opcion;

    do {
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
                cin.ignore(); // Limpiar buffer
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
                cin.ignore(); // Limpiar buffer
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
