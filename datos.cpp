#include "datos.h"
#include "estructuras.h"
#include "funciones.h"
#include <cstring>

// Definir las variables globales
NodoProducto *catalogoPorCategoria[MAX_CATEGORIAS] = {nullptr};
NodoUsuario *arbolUsuarios = nullptr;

void inicializarDatos() {
  // Crear productos de ejemplo
  Producto *p1 = new Producto{1, "Smartphone X", "TechMax", 499.99f, 4, 0};
  Producto *p2 = new Producto{2, "Laptop Pro", "TechMax", 899.99f, 5, 0};
  Producto *p3 =
      new Producto{3, "Cafetera Premium", "HomeGoods", 129.99f, 4, 1};
  Producto *p4 =
      new Producto{4, "Zapatillas Running", "SportLife", 89.99f, 3, 3};
  Producto *p5 =
      new Producto{5, "Crema Hidratante", "BeautyCare", 24.99f, 4, 4};

  agregarProductoACategoria(p1);
  agregarProductoACategoria(p2);
  agregarProductoACategoria(p3);
  agregarProductoACategoria(p4);
  agregarProductoACategoria(p5);

  // Crear usuarios
  Usuario *u1 = new Usuario();
  strcpy(u1->nombre, "Ana");
  strcpy(u1->apellido, "García");
  u1->id = 1001;
  strcpy(u1->username, "ana_user");
  strcpy(u1->password, "pass123");
  inicializarHistorial(u1->historial);
  agregarPreferencia(u1->preferenciasMarcas, "TechMax");
  agregarPreferencia(u1->preferenciasMarcas, "HomeGoods");
  agregarAlHistorial(u1->historial, p1);
  agregarAlHistorial(u1->historial, p3);

  Usuario *u2 = new Usuario();
  strcpy(u2->nombre, "Carlos");
  strcpy(u2->apellido, "Martínez");
  u2->id = 1002;
  strcpy(u2->username, "carlos_m");
  strcpy(u2->password, "pass456");
  inicializarHistorial(u2->historial);
  agregarPreferencia(u2->preferenciasMarcas, "SportLife");
  agregarAlHistorial(u2->historial, p4);

  Usuario *u3 = new Usuario();
  strcpy(u3->nombre, "Daniel");
  strcpy(u3->apellido, "Nuñez");
  u3->id = 1003;
  strcpy(u3->username, "daniel");
  strcpy(u3->password, "daniel");
  inicializarHistorial(u3->historial);
  agregarPreferencia(u3->preferenciasMarcas, "SportLife");

  // Insertar usuarios en el árbol
  insertarUsuario(arbolUsuarios, u1);
  insertarUsuario(arbolUsuarios, u2);
  insertarUsuario(arbolUsuarios, u3);
}
