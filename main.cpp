// main.cpp
#include "datos.h"
#include "funciones.h"
#include <cstring>
#include <iostream>
using namespace std;

int main() {
  inicializarDatos();
  int opcion, userID;
  char password[30];
  Usuario *usuarioActual = nullptr;

  do {
    mostrarMenu();
    cin >> opcion;

    switch (opcion) {
    case 1:
      cout << "Ingrese ID de usuario: ";
      cin >> userID;
      usuarioActual = buscarUsuario(arbolUsuarios, userID);

      if (usuarioActual) {
        cout << "Ingrese contraseña: ";
        cin >> password;

        if (strcmp(usuarioActual->password, password) == 0) {
          if (usuarioActual->rol == ADMIN) {
            menuAdmin(usuarioActual);
          } else {
            menuUsuario(usuarioActual);
          }
        } else {
          cout << "Contraseña incorrecta!\n";
        }
      } else {
        cout << "Usuario no encontrado!\n";
      }
      break;

    case 2:
      menuCatalogo();
      break;
    }
  } while (opcion != 3);

  cout << "Saliendo del sistema...\n";
  return 0;
}