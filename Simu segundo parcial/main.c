#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#define color system("COLOR B")
#include <string.h>
#include <conio.h>
#define ESC 27

int main()
{
    color;

    char archivo[] = "registros.bin";

    Arreglo *arr =  inicArreglo(); // Inicializar el arreglo
    int validos = 0;

    arr= agregar_desde_archivo(archivo,&validos);
    mostrar_cabecera_arreglo(arr, validos);

    arr= cargar_manualmente(arr,&validos);
    mostrar_cabecera_arreglo(arr,validos);
    int i=0;
    printf("INgrese categoria a buscar \n");
    char catee[30];
    fflush(stdin);
    gets(catee);
    if(posicion(arr,validos,catee,i)==-1)
        printf("LA CATEGORIA BUSCADA NO EXISTEEE \n");
    else
        printf("LA POSICION ES: %d",posicion(arr,validos,catee,i));


    arr= cargar_lista_productos( arr, validos,archivo);

    mostrar_cabecera_arreglo(arr,validos);

    cargar_archivo_categoria(arr,archivo,validos);

    arr= agregar_desde_archivo(archivo,&validos);

    mostrar_cabecera_arreglo(arr, validos);

    return 0;
}

Arreglo *inicArreglo()
{
    return NULL;
}


Arreglo *agregar_desde_archivo(char archivo[], int *validos)
{
    FILE *archi = fopen(archivo, "r+b");
    stRegistroProductos regis;
    int i = 0;
    Arreglo *arr = NULL;
    long numElementos = 0;

    if (archi)
    {

        arr = (Arreglo *)malloc(sizeof(Arreglo));
        numElementos = 0;

        while (fread(&regis, sizeof(stRegistroProductos), 1, archi) > 0)
        {
            char cate[30];
            strcpy(cate, regis.categoria);


            int categoriaExistente = 0;
            for (int j = 0; j < numElementos; j++)
            {
                if (strcmpi(cate, arr[j].registro1.categoria) == 0)
                {
                    categoriaExistente = 1;
                    break;
                }
            }

            if (!categoriaExistente)
            {

                numElementos++;
                arr = (Arreglo *)realloc(arr, numElementos *  sizeof(Arreglo));
                strcpy(arr[i].registro1.categoria, regis.categoria);
                i++;
            }
        }

        fseek(archi, 0, SEEK_SET);


        while (fread(&regis, sizeof(stRegistroProductos), 1, archi) > 0)
        {
            stProducto product;

            for (int j = 0; j < numElementos; j++)
            {
                if (strcmpi(arr[j].registro1.categoria, regis.categoria) == 0)
                {
                    strcpy(product.fechaExpiracion, regis.fechaExpiracion);
                    strcpy(product.nombreProducto, regis.nombreProducto);
                    product.cantidadStock = regis.cantidadStock;
                    product.idProducto = regis.idProducto;


                    if (arr[j].siguiente == NULL)
                    {

                        arr[j].siguiente = crearNodo(product);
                    }
                    else
                    {

                        arr[j].siguiente = agregarFinal(arr[j].siguiente, crearNodo(product));
                    }
                }
            }
        }

    }
    else
    {
        printf("No se pudo abrir el archivo. Verifica la ruta.\n");
    }

    *validos = numElementos;
    fclose(archi);
    return arr;
}

void mostrar_cabecera_arreglo(Arreglo *arr, int validos)
{
    int i = 0;

    while (i < validos)
    {
        nodo* aux= arr[i].siguiente;
        printf("CATEGORIA: %s\n", arr[i].registro1.categoria);
        recorrerYmostrar(aux);
        i++;
        printf("--------------------------------------------------------------------\n");
    }
}

Arreglo *cargar_manualmente(Arreglo *arr,int *validos)
{

    int i=*validos;
    char o=0;

    while(o!=ESC)
    {
        arr = (Arreglo *)realloc(arr, (i + 1) * sizeof(Arreglo));
        printf("Ingrese una categoria nueva\n");
        fflush(stdin);
        gets(arr[i].registro1.categoria);
        arr[i].siguiente=inicLista();
        arr[i].registro1.idRegistro=i;
        i++;

        printf("PRESS ESC TO EXIT OR ANY KEY TO CONTINUE LOADING \n");
        fflush(stdin);
        o=getch();
    }
    *validos=i;

    return arr;
}


int posicion(Arreglo *arr,int validos,char cate[30],int i)
{
    int pos=-1;

    if(i<validos)
    {
        if(strcmpi(cate,arr[i].registro1.categoria)!=0)
        {
            i++;
            pos=posicion(arr,validos,cate,i);

        }
        else
            pos=i;

    }
    return pos;
}

stProducto cargar_producto()
{
    stProducto prod;
    printf("Ingrese nombre del producto \n");
    fflush(stdin);
    gets(prod.nombreProducto);
    printf("Ingrese cantidad en stock \n");
    scanf("%d",&prod.cantidadStock);
    printf("Ingrese Fecha de expiracion \n");
    fflush(stdin);
    gets(prod.fechaExpiracion);
    return prod;
}

Arreglo* cargar_lista_productos(Arreglo *arr,int validos,char archivo[])
{


    char o=0;
    char cat[30];
    printf("Ingrese la categoria del producto a cargar \n");
    fflush(stdin);
    gets(cat);
    int i=0;
    i=posicion(arr,validos,cat,i);
    int final_id=contar_productos(archivo);
    printf("ID DEL ARCH %d ",contar_productos(archivo));
    while(o!=27)
    {
        final_id++;
        stProducto prod=cargar_producto();
        if(arr[i].siguiente==NULL)
        {
            arr[i].siguiente=crearNodo(prod);
            arr[i].siguiente->dato.idProducto=final_id;

        }
        else
        {
            arr[i].siguiente->siguiente=agregarFinal( arr[i].siguiente->siguiente,crearNodo(prod));
            nodo *aux=buscarUltimo( arr[i].siguiente->siguiente);
            aux->dato.idProducto=final_id;

        }
        printf("Si desea seguir cargando productos en esta categoria presione cualquier tecla o ESC para finalizar con la carga \n");
        fflush(stdin);
        o=getch();



    }

    return arr;
}

int contar_productos(char archivo[])
{

    FILE *archi=fopen(archivo,"r+b");

    fseek(archi,0,SEEK_END);
    int cont= ftell(archi)/sizeof(stRegistroProductos);


    fclose(archi);
    return cont;
}

void cargar_archivo_categoria(Arreglo *arr,char archivo[],int validos)
{

    FILE *archi=fopen(archivo,"r+b");
    stRegistroProductos reg;
    stRegistroProductos cate;
    int i=0;
    if(archi)
    {
        printf("Ingrese Categoria a agregar \n");
        fflush(stdin);
        gets(cate.categoria);
        while(i<validos)
        {

            if(strcmpi(cate.categoria,arr[i].registro1.categoria)==0)
            {
                /// fseek(archi,ftell(archi),SEEK_SET);


                nodo*aux=arr[i].siguiente;
                while(aux)
                {
                    int flag=0;
                    while(fread(&reg,sizeof(stRegistroProductos),1,archi)>0)
                    {

                        if(aux->dato.idProducto==reg.idProducto)
                        {

                            flag=1;

                        }

                    }
                    if(!flag)
                    {
                        fseek(archi,0,SEEK_END);
                        strcpy(reg.nombreProducto,aux->dato.nombreProducto);
                        strcpy(reg.categoria,cate.categoria);

                        strcpy(reg.fechaExpiracion,aux->dato.fechaExpiracion);
                            reg.idRegistro=arr[i].registro1.idRegistro;
                        reg.cantidadStock=aux->dato.cantidadStock;
                    reg.idProducto=aux->dato.idProducto;
                        fwrite(&reg,sizeof(stRegistroProductos),1,archi);
                    }
                    fseek(archi,0,SEEK_SET);
                    aux=aux->siguiente;

                }
            }

            i++;
        }
    }

    else
        printf("ERROR EN EL ARCHIVO FUNCION AGREGAR \n");

    fclose(archi);
}

