#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int idRegistro;
    int idProducto;
    char nombreProducto[30];
    char categoria[30];
    int cantidadStock;
    char fechaExpiracion [11];
} stRegistroProductos;

typedef struct
{
    int idProducto;
    char nombreProducto[30];
    int cantidadStock;
    char fechaExpiracion [11];
} stProducto;

typedef struct
{
    stProducto dato;
    struct nodo* siguiente;
} nodo;

nodo * inicLista();
nodo * crearNodo(stProducto dato);
nodo * agregarFinal(nodo * lista, nodo * nuevoNodo);
void mostrarNodo(nodo * aux);
void recorrerYmostrar(nodo * lista);
nodo * buscarUltimo(nodo * lista);

#endif // LISTA_H_INCLUDED
