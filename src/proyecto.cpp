#include "class.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Mago {
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_father;
    bool is_dead;
    string type_magic;
    bool is_owner;
};

void menu() {
    cout << "\nMENÚ DEL HECHIZO \n";
    cout << "1. Mostrar línea de sucesión\n";
    cout << "2. Buscar mago\n";
    cout << "3. Actualizar mago\n";
    cout << "4. Insertar mago\n";
    cout << "5. Eliminar mago\n";
    cout << "6. Ver hechizos de un mago\n";
    cout << "0. Salir\n";
    cout << "Elige una opción: ";
}

int main() {
    Trees<Mago> school;
    int option;
    do {
        menu();
        cin >> option;
        switch (option) {
            case 1:
                cout << "Mostrando sucesión...\n";
                break;
            case 2:
                cout << "Ingresa el nombre del mago a buscar: ";
                break;
            case 3:
                cout << "Actualizar mago\n";
                break;
            case 4:
                cout << "Insertar nuevo mago\n";
                break;
            case 5:
                cout << "Eliminar mago\n";
                break;
            case 6:
                cout << "Ver hechizos heredados\n";
                break;
            case 0:
                cout << "Cerrando el grimorio... Hasta luego, hechicero.\n";
                break;
            default:
                cout << "Opción no valida\n";
                break;
        }
    } while (option != 0);

    return 0;
}
