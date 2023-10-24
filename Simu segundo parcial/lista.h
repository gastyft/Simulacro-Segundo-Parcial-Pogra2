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

typedef struct nodo
{
    stProducto dato;
    struct nodo* siguiente;
} nodo;

typedef struct {
stRegistroProductos registro1;
 nodo *siguiente;
}Arreglo;


nodo * inicLista();
nodo * crearNodo(stProducto dato);
nodo * agregarFinal(nodo * lista, nodo * nuevoNodo);
void mostrarNodo(nodo * aux);
void recorrerYmostrar(nodo * lista);
nodo * buscarUltimo(nodo * lista);
Arreglo *agregar_desde_archivo(char archivo[], int *validos);
void mostrar_cabecera_arreglo(Arreglo *arr,int validos);
Arreglo *cargar_manualmente(Arreglo *arr,int *validos);
int posicion(Arreglo *arr,int validos,char cate[30],int i);
Arreglo *inicArreglo();
void cargar_archivo_categoria(Arreglo *arr,char archivo[],int validos);
Arreglo* cargar_lista_productos(Arreglo *arr,int validos,char archivo[]);
stProducto cargar_producto();
int contar_productos(char archivo[]);


#endif // LISTA_H_INCLUDED
