#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "estructuras.h"

// Declaraciones de funciones
void inicializarHistorial(Historial &h);
void agregarAlHistorial(Historial &h, Producto *p);
void agregarPreferencia(NodoLista *&lista, const char *marca);
bool buscarPreferencia(NodoLista *lista, const char *marca);
void insertarUsuario(NodoUsuario *&raiz, Usuario *usuario);
Usuario *buscarUsuario(NodoUsuario *raiz, int id);
void agregarProductoACategoria(Producto *p);
void generarRecomendaciones(Usuario *usuario, Producto *recomendados[]);
void mostrarProducto(Producto *p);
void mostrarMenu();
void menuUsuario(Usuario *usuario);
// Nuevas funciones para filtrado
void menuCatalogo();
void mostrarCatalogoCompleto();
void filtrarPorRangoPrecios();
void filtrarPorCategoria();
void filtrarPorMarca();
void filtrarPorDescripcion();
#endif