#include "lista.h"

nodo * inicLista()
{
    return NULL;
}

nodo * crearNodo(stProducto dato)
{
    nodo * aux = (nodo*)malloc(sizeof(nodo));
    aux->dato = dato;
    aux->siguiente = NULL;

    return aux;
}

nodo * buscarUltimo(nodo * lista)
{
    nodo * seg = lista;
    if(seg != NULL)
        while(seg->siguiente != NULL)
        {
            seg = seg->siguiente;
        }
    return seg;
}

nodo * agregarFinal(nodo * lista, nodo * nuevoNodo)
{

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodo * ultimo = buscarUltimo(lista);

        ultimo->siguiente = nuevoNodo;
    }
    return lista;
}

void mostrarNodo(nodo * aux)
{
    printf("Nombre: %s \n",aux->dato.nombreProducto);
    printf("ID: %d \n",aux->dato.idProducto);
    printf("Expira el %s \n",aux->dato.fechaExpiracion);
    printf("El stock es: %d \n",aux->dato.cantidadStock);
}

void recorrerYmostrar(nodo * lista)
{
    nodo * aux=lista;
    while(aux!=NULL)
    {
        mostrarNodo(aux);
        aux=aux->siguiente;
    }
}
