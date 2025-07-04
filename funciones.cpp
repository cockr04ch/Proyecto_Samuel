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

// Helper struct for sorting recommendations
struct ProductoPuntuado {
  Producto *producto;
  float puntuacion;
};

// Bubble sort for the array of structs
void ordenarCandidatos(ProductoPuntuado arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j].puntuacion < arr[j + 1].puntuacion) {
        ProductoPuntuado temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void generarRecomendaciones(Usuario *usuario, Producto *recomendados[]) {
  const int MAX_CANDIDATOS = 200;
  ProductoPuntuado candidatos[MAX_CANDIDATOS];
  int num_candidatos = 0;

  // Step 1: Iterate through all products and calculate a score for each.
  for (int cat = 0; cat < MAX_CATEGORIAS; cat++) {
    NodoProducto *actual = catalogoPorCategoria[cat];
    while (actual) {
      Producto *p = actual->producto;

      // Skip products already in the user's purchase history
      bool enHistorial = false;
      for (int i = 0; i < usuario->historial.contador; i++) {
        int idx = (usuario->historial.frente + i) % MAX_HISTORIAL;
        if (usuario->historial.items[idx]->id == p->id) {
          enHistorial = true;
          break;
        }
      }
      if (enHistorial) {
        actual = actual->siguiente;
        continue;
      }

      float puntuacion = 0.0f;
      // Score based on brand preference
      if (buscarPreferencia(usuario->preferenciasMarcas, p->marca)) {
        puntuacion += 0.5f;
      }

      // Score based on similarity to purchase history
      for (int i = 0; i < usuario->historial.contador; i++) {
        int idx = (usuario->historial.frente + i) % MAX_HISTORIAL;
        Producto *h = usuario->historial.items[idx];
        if (strcmp(h->marca, p->marca) == 0) {
          puntuacion += 0.3f;
        }
        if (h->categoria == p->categoria) {
          puntuacion += 0.2f;
        }
      }

      // Score based on quality
      puntuacion += (1.0f - abs(p->calidad - 3) / 5.0f) * 0.2f;

      // Add product to candidates list if it has a positive score
      if (puntuacion > 0 && num_candidatos < MAX_CANDIDATOS) {
        candidatos[num_candidatos].producto = p;
        candidatos[num_candidatos].puntuacion = puntuacion;
        num_candidatos++;
      }

      actual = actual->siguiente;
    }
  }

  // Step 2: Sort candidates in descending order of score (Bubble Sort)
  ordenarCandidatos(candidatos, num_candidatos);

  // Step 3: Fill the recommendations array with the top products
  int contador = 0;
  for (int i = 0; i < num_candidatos && contador < MAX_RECOMENDACIONES; ++i) {
    recomendados[contador++] = candidatos[i].producto;
  }

  // Step 4: Fill the rest of the array with nullptrs
  for (int i = contador; i < MAX_RECOMENDACIONES; i++) {
    recomendados[i] = nullptr;
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
    cout << "4. Marcar producto de interés\n";
    cout << "5. Cerrar sesión\n";
    cout << "Seleccione: ";
    cin >> opcion;

    switch (opcion) {
    case 1: {
      generarRecomendaciones(usuario, recomendados);
      cout << "\nRECOMENDACIONES PARA TI:\n";
      for (int i = 0; i < MAX_RECOMENDACIONES && recomendados[i]; i++) {
        mostrarProducto(recomendados[i]);
      }
      break;
    }
    case 2: {
      cout << "\nTU HISTORIAL:\n";
      for (int i = 0; i < usuario->historial.contador; i++) {
        int idx = (usuario->historial.frente + i) % MAX_HISTORIAL;
        mostrarProducto(usuario->historial.items[idx]);
      }
      break;
    }
    case 3: {
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
    case 4: {
      marcarProductoDeInteres(usuario);
      break;
    }
    }
  } while (opcion != 5);
}

Producto *buscarProductoPorId(int id) {
  for (int i = 0; i < MAX_CATEGORIAS; i++) {
    NodoProducto *actual = catalogoPorCategoria[i];
    while (actual) {
      if (actual->producto->id == id) {
        return actual->producto;
      }
      actual = actual->siguiente;
    }
  }
  return nullptr;
}

void marcarProductoDeInteres(Usuario *usuario) {
  int categoria, idProducto;
  const char *categorias[] = {"Electrónica", "Hogar y cocina",
                              "Moda y Accesorios", "Deportes y Aire Libre",
                              "Cuidado personal"};

  cout << "\n--- MARCAR PRODUCTO DE INTERÉS ---\n";
  cout << "Seleccione una categoría:\n";
  for (int i = 0; i < 5; i++) {
    cout << i << ". " << categorias[i] << "\n";
  }
  cout << "Seleccione: ";
  cin >> categoria;

  if (categoria < 0 || categoria >= 5) {
    cout << "Categoría inválida.\n";
    return;
  }

  cout << "\n--- PRODUCTOS EN " << categorias[categoria] << " ---\n";
  NodoProducto *actual = catalogoPorCategoria[categoria];
  while (actual) {
    mostrarProducto(actual->producto);
    actual = actual->siguiente;
  }

  cout << "\nIngrese el ID del producto que le interesa: ";
  cin >> idProducto;

  Producto *productoSeleccionado = buscarProductoPorId(idProducto);
  if (productoSeleccionado) {
    agregarAlHistorial(usuario->historial, productoSeleccionado);
    cout << "Producto agregado a su historial.\n";
  } else {
    cout << "Producto no encontrado.\n";
  }
}

// Función para mostrar el submenú de catálogo
void menuCatalogo() {
  int opcion;
  do {
    cout << "\n=== MENÚ CATÁLOGO ===\n";
    cout << "1. Mostrar todo el catálogo\n";
    cout << "2. Filtrar por rango de precios\n";
    cout << "3. Filtrar por categoría\n";
    cout << "4. Filtrar por marca\n";
    cout << "5. Filtrar por descripción\n";
    cout << "6. Volver al menú principal\n";
    cout << "Seleccione: ";
    cin >> opcion;

    switch (opcion) {
    case 1: {
      mostrarCatalogoCompleto();
      break;
    }
    case 2: {
      filtrarPorRangoPrecios();
      break;
    }
    case 3: {
      filtrarPorCategoria();
      break;
    }
    case 4: {
      filtrarPorMarca();
      break;
    }
    case 5: {
      filtrarPorDescripcion();
      break;
    }
    }
  } while (opcion != 6);
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

// Función para filtrar por marca
void filtrarPorMarca() {
  char marca[50];
  cout << "\nFILTRAR POR MARCA\n";
  cout << "Ingrese la marca: ";
  cin >> marca;

  cout << "\nPRODUCTOS DE LA MARCA " << marca << ":\n";
  for (int i = 0; i < MAX_CATEGORIAS; i++) {
    NodoProducto *actual = catalogoPorCategoria[i];
    while (actual) {
      Producto *p = actual->producto;
      if (strcmp(p->marca, marca) == 0) {
        mostrarProducto(p);
      }
      actual = actual->siguiente;
    }
  }
}

// Función para filtrar por descripción
void filtrarPorDescripcion() {
  char descripcion[100];
  cout << "\nFILTRAR POR DESCRIPCIÓN\n";
  cout << "Ingrese una palabra de la descripción: ";
  cin >> descripcion;
  cout << "\nPRODUCTOS CON LA DESCRIPCIÓN QUE CONTIENE '" << descripcion
       << "':\n";
  for (int i = 0; i < MAX_CATEGORIAS; i++) {
    NodoProducto *actual = catalogoPorCategoria[i];
    while (actual) {
      Producto *p = actual->producto;
      if (strstr(p->descripcion, descripcion) != nullptr) {
        mostrarProducto(p);
      }
      actual = actual->siguiente;
    }
  }
}

void agregarNuevoUsuario() {
  Usuario *nuevoUsuario = new Usuario();
  cout << "\n--- AGREGAR NUEVO USUARIO ---\n";
  cout << "ID: ";
  cin >> nuevoUsuario->id;
  if (buscarUsuario(arbolUsuarios, nuevoUsuario->id)) {
    cout << "Error: El ID de usuario ya existe.\n";
    delete nuevoUsuario;
    return;
  }
  cout << "Nombre: ";
  cin >> nuevoUsuario->nombre;
  cout << "Apellido: ";
  cin >> nuevoUsuario->apellido;
  cout << "Username: ";
  cin >> nuevoUsuario->username;
  cout << "Password: ";
  cin >> nuevoUsuario->password;
  nuevoUsuario->rol = CLIENTE;
  inicializarHistorial(nuevoUsuario->historial);
  insertarUsuario(arbolUsuarios, nuevoUsuario);
  cout << "Usuario agregado exitosamente!\n";
}

void agregarNuevoProducto() {
  Producto *nuevoProducto = new Producto();
  cout << "\n--- AGREGAR NUEVO PRODUCTO ---\n";
  cout << "ID: ";
  cin >> nuevoProducto->id;
  cout << "Descripción: ";
  cin.ignore();
  cin.getline(nuevoProducto->descripcion, 100);
  cout << "Marca: ";
  cin >> nuevoProducto->marca;
  cout << "Precio: ";
  cin >> nuevoProducto->precio;
  cout << "Calidad (1-5): ";
  cin >> nuevoProducto->calidad;
  cout << "Categoría (0-4): ";
  cin >> nuevoProducto->categoria;
  agregarProductoACategoria(nuevoProducto);
  cout << "Producto agregado exitosamente!\n";
}

void menuAdmin(Usuario *usuario) {
  int opcion;
  do {
    cout << "\n=== MENÚ ADMIN ===\n";
    cout << "1. Agregar nuevo usuario\n";
    cout << "2. Agregar nuevo producto\n";
    cout << "3. Cerrar sesión\n";
    cout << "Seleccione: ";
    cin >> opcion;
    switch (opcion) {
    case 1: {
      agregarNuevoUsuario();
      break;
    }
    case 2: {
      agregarNuevoProducto();
      break;
    }
    }
  } while (opcion != 3);
}