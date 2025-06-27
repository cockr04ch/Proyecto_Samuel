#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

const int MAX_CATEGORIAS = 5;
const int MAX_HISTORIAL = 5;
const int MAX_RECOMENDACIONES = 5;

struct Producto {
  int id;
  char descripcion[100];
  char marca[50];
  float precio;
  int calidad;
  int categoria;
};

struct NodoLista {
  char dato[50];
  NodoLista *siguiente;
};

struct Historial {
  Producto *items[MAX_HISTORIAL];
  int frente;
  int final;
  int contador;
};

struct Usuario {
  char nombre[50];
  char apellido[50];
  int id;
  char username[30];
  char password[30];
  NodoLista *preferenciasMarcas;
  Historial historial;
};

struct NodoUsuario {
  Usuario *usuario;
  NodoUsuario *izquierda;
  NodoUsuario *derecha;
};

struct NodoProducto {
  Producto *producto;
  NodoProducto *siguiente;
};

// Declaraciones externas para las variables globales
extern NodoProducto *catalogoPorCategoria[MAX_CATEGORIAS];
extern NodoUsuario *arbolUsuarios;

#endif