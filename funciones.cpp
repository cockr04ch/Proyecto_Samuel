// funciones.cpp
#include "funciones.h"
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

// Implementaciones de las funciones

void inicializarHistorial(Historial &h) {
  h.frente = 0;
  h.final = -1;
  h.contador = 0;
}

void agregarAlHistorial(Historial &h, Producto *p) {
  if (h.contador < MAX_HISTORIAL) {
    h.final = (h.final + 1) % MAX_HISTORIAL;
    h.items[h.final] = p;
    h.contador++;
  } else {
    h.frente = (h.frente + 1) % MAX_HISTORIAL;
    h.final = (h.final + 1) % MAX_HISTORIAL;
    h.items[h.final] = p;
  }
}

void agregarPreferencia(NodoLista *&lista, const char *marca) {
  NodoLista *nuevo = new NodoLista;
  strcpy(nuevo->dato, marca);
  nuevo->siguiente = lista;
  lista = nuevo;
}

bool buscarPreferencia(NodoLista *lista, const char *marca) {
  while (lista) {
    if (strcmp(lista->dato, marca) == 0)
      return true;
    lista = lista->siguiente;
  }
  return false;
}

void insertarUsuario(NodoUsuario *&raiz, Usuario *usuario) {
  if (!raiz) {
    raiz = new NodoUsuario;
    raiz->usuario = usuario;
    raiz->izquierda = raiz->derecha = nullptr;
  } else {
    if (usuario->id < raiz->usuario->id)
      insertarUsuario(raiz->izquierda, usuario);
    else
      insertarUsuario(raiz->derecha, usuario);
  }
}

Usuario *buscarUsuario(NodoUsuario *raiz, int id) {
  if (!raiz)
    return nullptr;
  if (id == raiz->usuario->id)
    return raiz->usuario;
  if (id < raiz->usuario->id)
    return buscarUsuario(raiz->izquierda, id);
  return buscarUsuario(raiz->derecha, id);
}

void agregarProductoACategoria(Producto *p) {
  NodoProducto *nuevo = new NodoProducto;
  nuevo->producto = p;
  nuevo->siguiente = catalogoPorCategoria[p->categoria];
  catalogoPorCategoria[p->categoria] = nuevo;
}

void generarRecomendaciones(Usuario *usuario, Producto *recomendados[]) {
  int contador = 0;
  float puntuacionMax = 0;
  Producto *mejorProducto = nullptr;

  for (int cat = 0; cat < MAX_CATEGORIAS; cat++) {
    NodoProducto *actual = catalogoPorCategoria[cat];
    while (actual && contador < MAX_RECOMENDACIONES) {
      Producto *p = actual->producto;
      float puntuacion = 0;

      if (buscarPreferencia(usuario->preferenciasMarcas, p->marca))
        puntuacion += 0.5;

      for (int i = 0; i < usuario->historial.contador; i++) {
        int idx = (usuario->historial.frente + i) % MAX_HISTORIAL;
        Producto *h = usuario->historial.items[idx];
        if (strcmp(h->marca, p->marca) == 0)
          puntuacion += 0.3;
        if (h->categoria == p->categoria)
          puntuacion += 0.2;
      }

      puntuacion += (1 - abs(p->calidad - 3) / 5.0) * 0.2;

      if (puntuacion > puntuacionMax) {
        puntuacionMax = puntuacion;
        mejorProducto = p;
      }

      actual = actual->siguiente;
    }

    if (mejorProducto) {
      recomendados[contador++] = mejorProducto;
      puntuacionMax = 0;
    }
  }
}

void mostrarProducto(Producto *p) {
  const char *categorias[] = {"Electrónica", "Hogar y cocina",
                              "Moda y Accesorios", "Deportes y Aire Libre",
                              "Cuidado personal"};

  cout << "ID: " << p->id << "\n";
  cout << "Descripción: " << p->descripcion << "\n";
  cout << "Marca: " << p->marca << " | Precio: $" << p->precio << "\n";
  cout << "Calidad: " << p->calidad
       << "/5 | Categoría: " << categorias[p->categoria] << "\n";
  cout << "--------------------------------\n";
}

void mostrarMenu() {
  cout << "\n=== SISTEMA DE RECOMENDACIÓN ===\n";
  cout << "1. Iniciar sesión\n";
  cout << "2. Explorar Catalogo\n";
  cout << "3. Salir\n";
  cout << "Seleccione: ";
}

void menuUsuario(Usuario *usuario) {
  Producto *recomendados[MAX_RECOMENDACIONES] = {nullptr};
  int opcion;

  do {
    cout << "\n=== BIENVENIDO " << usuario->nombre << " ===\n";
    cout << "1. Ver recomendaciones\n";
    cout << "2. Ver historial\n";
    cout << "3. Ver perfil\n";
    cout << "4. Cerrar sesión\n";
    cout << "Seleccione: ";
    cin >> opcion;

    switch (opcion) {
    case 1:
      generarRecomendaciones(usuario, recomendados);
      cout << "\nRECOMENDACIONES PARA TI:\n";
      for (int i = 0; i < MAX_RECOMENDACIONES && recomendados[i]; i++) {
        mostrarProducto(recomendados[i]);
      }
      break;
    case 2:
      cout << "\nTU HISTORIAL:\n";
      for (int i = 0; i < usuario->historial.contador; i++) {
        int idx = (usuario->historial.frente + i) % MAX_HISTORIAL;
        mostrarProducto(usuario->historial.items[idx]);
      }
      break;
    case 3:
      cout << "\nTU PERFIL:\n";
      cout << "Nombre: " << usuario->nombre << " " << usuario->apellido << "\n";
      cout << "Usuario: " << usuario->username << "\n";
      cout << "Marcas preferidas: ";
      NodoLista *temp = usuario->preferenciasMarcas;
      while (temp) {
        cout << temp->dato << ", ";
        temp = temp->siguiente;
      }
      cout << "\n";
      break;
    }
  } while (opcion != 4);
}

// Función para mostrar el submenú de catálogo
void menuCatalogo() {
  int opcion;
  do {
    cout << "\n=== MENÚ CATÁLOGO ===\n";
    cout << "1. Mostrar todo el catálogo\n";
    cout << "2. Filtrar por rango de precios\n";
    cout << "3. Filtrar por categoría\n";
    cout << "4. Volver al menú principal\n";
    cout << "Seleccione: ";
    cin >> opcion;

    switch (opcion) {
    case 1:
      mostrarCatalogoCompleto();
      break;
    case 2:
      filtrarPorRangoPrecios();
      break;
    case 3:
      filtrarPorCategoria();
      break;
    }
  } while (opcion != 4);
}

// Función para mostrar todo el catálogo
void mostrarCatalogoCompleto() {
  cout << "\nCATÁLOGO COMPLETO:\n";
  for (int i = 0; i < MAX_CATEGORIAS; i++) {
    NodoProducto *actual = catalogoPorCategoria[i];
    while (actual) {
      mostrarProducto(actual->producto);
      actual = actual->siguiente;
    }
  }
}

// Función para filtrar por rango de precios
void filtrarPorRangoPrecios() {
  float min, max;
  cout << "\nFILTRAR POR RANGO DE PRECIOS\n";
  cout << "Ingrese precio mínimo: ";
  cin >> min;
  cout << "Ingrese precio máximo: ";
  cin >> max;

  cout << "\nPRODUCTOS ENTRE $" << min << " Y $" << max << ":\n";
  for (int i = 0; i < MAX_CATEGORIAS; i++) {
    NodoProducto *actual = catalogoPorCategoria[i];
    while (actual) {
      Producto *p = actual->producto;
      if (p->precio >= min && p->precio <= max) {
        mostrarProducto(p);
      }
      actual = actual->siguiente;
    }
  }
}

// Función para filtrar por categoría
void filtrarPorCategoria() {
  const char *categorias[] = {"Electrónica", "Hogar y cocina",
                              "Moda y Accesorios", "Deportes y Aire Libre",
                              "Cuidado personal"};

  cout << "\nFILTRAR POR CATEGORÍA\n";
  cout << "0. Electrónica\n";
  cout << "1. Hogar y cocina\n";
  cout << "2. Moda y Accesorios\n";
  cout << "3. Deportes y Aire Libre\n";
  cout << "4. Cuidado personal\n";

  int cat;
  cout << "Seleccione categoría (0-4): ";
  cin >> cat;

  if (cat < 0 || cat >= MAX_CATEGORIAS) {
    cout << "Categoría inválida!\n";
    return;
  }

  cout << "\nPRODUCTOS EN " << categorias[cat] << ":\n";
  NodoProducto *actual = catalogoPorCategoria[cat];
  while (actual) {
    mostrarProducto(actual->producto);
    actual = actual->siguiente;
  }
}