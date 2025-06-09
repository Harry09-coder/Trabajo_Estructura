#include <iostream>
#include <string>


struct Proceso {
    int id;
    std::string nombre;
    int prioridad;
    Proceso* siguiente;
};


