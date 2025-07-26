#include "class.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void limpiarBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}

void menu() {
    cout << "\nMENU DEL HECHIZO \n";
    cout << "1. Mostrar arbol completo\n";
    cout << "2. Mostrar linea de sucesion(solo vivos):\n";
    cout << "3. Buscar mago por ID\n";
    cout << "4. Actualizar informacion de un mago\n";
    cout << "5. Insertar nuevo mago\n";
    cout << "6. Eliminar mago (sin hijos)\n";
    cout << "7. Ver hechizos heredados de un mago\n";
    cout << "8. Asignar nuevo dueño automaticamente\n";
    cout << "9. Guardar cambios\n";
    cout << "0. Salir\n";
    cout << "Elige una opcion: ";
}

void buscarMago(MagicTree& arbol) {
    int id;
    cout << "Ingrese ID del mago a buscar: ";
    cin >> id;
    limpiarBuffer();
    
    TreeNode* encontrado = arbol.findByID(id);
    if (encontrado) {
        cout << "\nInformacion del mago:\n";
        cout << "ID: " << encontrado->content.id << "\n";
        cout << "Nombre: " << encontrado->content.name << " " << encontrado->content.last_name << "\n";
        cout << "Género: " << encontrado->content.gender << "\n";
        cout << "Edad: " << encontrado->content.age << "\n";
        cout << "ID Padre: " << encontrado->content.id_father << "\n";
        cout << "Estado: " << (encontrado->content.is_dead ? "Muerto" : "Vivo") << "\n";
        cout << "Tipo de magia: " << encontrado->content.type_magic << "\n";
        cout << "Dueño del hechizo: " << (encontrado->content.is_owner ? "Si" : "No") << "\n";
    } else {
        cout << "Mago no encontrado.\n";
    }
}

void actualizarMago(MagicTree& arbol) {
    int id;
    cout << "Ingrese ID del mago a actualizar: ";
    cin >> id;
    limpiarBuffer();
    
    TreeNode* existente = arbol.findByID(id);
    if (!existente) {
        cout << "Mago no encontrado.\n";
        return;
    }
    
    cout << "\nIngrese los nuevos datos (deje en blanco para mantener el valor actual):\n";
    
    Mago actualizado = existente->content;
    string input;
    
    cout << "Nombre (" << existente->content.name << "): ";
    getline(cin, input);
    if (!input.empty()) actualizado.name = input;
    
    cout << "Apellido (" << existente->content.last_name << "): ";
    getline(cin, input);
    if (!input.empty()) actualizado.last_name = input;
    
    cout << "Género (" << existente->content.gender << "): ";
    getline(cin, input);
    if (!input.empty()) actualizado.gender = input[0];
    
    cout << "Edad (" << existente->content.age << "): ";
    getline(cin, input);
    if (!input.empty()) actualizado.age = stoi(input);
    
    cout << "¿Está muerto? (" << (existente->content.is_dead ? "Si" : "No") << "), 1=Si 0=No: ";
    getline(cin, input);
    if (!input.empty()) actualizado.is_dead = (input == "1");
    
    cout << "Tipo de magia (" << existente->content.type_magic << "): ";
    getline(cin, input);
    if (!input.empty()) actualizado.type_magic = input;
    
    cout << "¿Es dueño? (" << (existente->content.is_owner ? "Si" : "No") << "), 1=Si 0=No: ";
    getline(cin, input);
    if (!input.empty()) actualizado.is_owner = (input == "1");
    
    if (arbol.updateMago(actualizado)) {
        cout << "Mago actualizado.\n";
    } else {
        cout << "Error al actualizar el mago.\n";
    }
}

void insertarMago(MagicTree& arbol) {
    Mago nuevo;
    cout << "Ingrese ID: ";
    cin >> nuevo.id;
    limpiarBuffer();
    
    cout << "Ingrese nombre: ";
    getline(cin, nuevo.name);
    
    cout << "Ingrese apellido: ";
    getline(cin, nuevo.last_name);
    
    cout << "Ingrese genero (M/F): ";
    cin >> nuevo.gender;
    
    cout << "Ingrese edad: ";
    cin >> nuevo.age;
    
    cout << "Ingrese ID del padre (0 si no tiene): ";
    cin >> nuevo.id_father;
    
    cout << "Esta muerto? (1=Sí, 0=No): ";
    cin >> nuevo.is_dead;
    
    limpiarBuffer();
    cout << "Ingrese tipo de magia (elemental, unique, mixed, no_magic): ";
    getline(cin, nuevo.type_magic);
    
    cout << "Es dueño? (1=Si, 0=No): ";
    cin >> nuevo.is_owner;
    
    if (arbol.insertMago(nuevo)) {
        cout << "Mago insertado.\n";
    } else {
        cout << "Error al insertar el mago(ID duplicado o limite alcanzado).\n";
    }
}

void eliminarMago(MagicTree& arbol) {
    int id;
    cout << "Ingrese ID del mago a eliminar: ";
    cin >> id;
    
    if (arbol.deleteMago(id)) {
        cout << "Mago eliminado.\n";
    } else {
        cout << "Error al eliminar (mago no encontrado, tiene hijos o es la raiz).\n";
    }
}

void mostrarHechizosHeredados(MagicTree& arbol) {
    int id;
    cout << "Ingrese ID del mago: ";
    cin >> id;
    limpiarBuffer();
    
    string hechizos[100];
    int cantidadHechizos = 0;
    
    arbol.getInheritedSpells(id, hechizos, cantidadHechizos);
    
    if (cantidadHechizos == 0) {
        cout << "No se encontraron hechizos heredados o el mago no existe.\n";
        return;
    }
    
    cout << "\nHechizos heredados por el mago:\n";
    for (int i = 0; i < cantidadHechizos; ++i) {
        cout << "- " << hechizos[i] << "\n";
    }
}

void guardarCambios(MagicTree& arbol) {
    arbol.saveToCSV("bin/magos.csv");
    cout << "Cambios guardados en magos.csv\n";
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
        limpiarBuffer();

        switch (option) {
            case 1:
                cout << "\nArbol magico completo:\n";
                arbol.displayTree();
                break;
            case 2:
                cout << "\nLinea de sucesion (solo magos vivos):\n";
                mostrarSucesionViva(arbol.getRoot());
                break;
            case 3:
                buscarMago(arbol);
                break;
            case 4:
                actualizarMago(arbol);
                break;
            case 5:
                insertarMago(arbol);
                break;
            case 6:
                eliminarMago(arbol);
                break;
            case 7:
                mostrarHechizosHeredados(arbol);
                break;
            case 8:
                arbol.autoAssignOwner();
                cout << "Dueño del hechizo actualizado automaticamente.\n";
                break;
            case 9:
                guardarCambios(arbol);
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