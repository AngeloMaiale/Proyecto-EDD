#include "class.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


void menu() {
    cout << "\nMENÚ DEL HECHIZO \n";
    cout << "1. Mostrar linea de sucesion\n";
    cout << "2. Buscar mago\n";
    cout << "3. Actualizar mago\n";
    cout << "4. Insertar mago\n";
    cout << "5. Eliminar mago\n";
    cout << "6. Ver hechizos de un mago\n";
    cout << "0. Salir\n";
    cout << "Elige una opcion: ";
}

int main() {
    MagicTree arbol;
    Mago magos[100];
    int count = 0;

    ifstream file("bin/magos.csv");
    if (!file.is_open()) {
        cout << "No se pudo abrir magos.csv\n";
        return 1;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Mago w;

    getline(ss, token, ','); w.id = convertirSeguro(token);
    getline(ss, token, ','); w.name = token;
    getline(ss, token, ','); w.last_name = token;
    getline(ss, token, ','); w.gender = token[0];
    getline(ss, token, ','); w.age = convertirSeguro(token);
    getline(ss, token, ','); w.id_father = convertirSeguro(token, true); 
    getline(ss, token, ','); w.is_dead = (token == "1");
    getline(ss, token, ','); w.type_magic = token;
    getline(ss, token, ','); w.is_owner = (token == "1");

        magos[count++] = w;
    }

    file.close();

    arbol.buildTree(magos, count);
    int option;
    do {
        menu();
        cin >> option;
        switch (option) {
            case 1:
                cout << "Mostrando sucesion...\n";
                arbol.displayTree();
                break;
            case 2:
                cout << "Linea de sucesion actual: ";
                mostrarSucesionViva(arbol.getRoot());
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
                cout << "Opcion no valida\n";
                break;
        }
    } while (option != 0);

    return 0;
}
