/**
 * Nombre completo: Diego Edgardo Vega Herrera.
 */

#include <iostream>
#include <vector>

using namespace std;

//Estructura base para la lista de memoria post-compactacion
struct node2
{
    int id;
    int data;
    int proceso;
    node2 *next;
};

//Funcion que retorna el tamaño de la lista
int size(node2 *lista)
{
    return lista == NULL ? 0 : 1 + size(lista->next);
}

/**
 * Funcion especificamente pensada para llenar la lista de memoria compactada
 * 
 * lista: Se refiere a la lista de memoria compactada que inicialmente apunta a NULL
 * info: Se refiere al tamaño que tendra este espacio en memoria
 * id: Se refiere al id del bloque, el de memoria
 * proceso: Se refiere al id del proceso que contiene
 */
void insertarFinal_compac(node2 **lista, int info, int id, int proceso)
{
    if (id != 0)
    {
        node2 *n = new node2;
        n->id = id;
        n->data = info;
        n->proceso = proceso;
        n->next = NULL;

        if (!*lista)
        {
            *lista = n;
        }
        else
        {
            node2 *aux = *lista;

            while (aux->next)
                aux = aux->next;

            aux->next = n;
        }
    }
}

/**
 * Funcion que recibe como parametro la lista de memoria compactada e imprime su contenido
 */
void mostrar_compactacion(node2 *lista)
{
    if (lista)
    {
        //Si lista->prpoceso es igual a 0 significa que ese proceso no fue asiganado segun el algoritmo
        if (lista->proceso != 0)
        {
            cout << "En memoria " << lista->id << " esta el proceso " << lista->proceso << " con tamanio: " << lista->data << "\n";
        }
        else
        {
            cout << "En memoria " << lista->id << " esta libre con tamanio: " << lista->data << "\n";
        }
        mostrar_compactacion(lista->next);
    }
}

/**
 * Estructura base para listas de procesos y memoria
 * 
 * id: Se refiere al id del elemento en la lista
 * data: Se refiere al tamaño que tiene este elemento en la lista
 * pos_other_list: Se refiere a la posicion del elemento en la otra lista |
 * si hablamos de una lista de memoria, esta variable contendra que proceso tiene almacenado y por el contrario almacenara en que memoria esta el proceso
 * pos_compac: Posicion una vez compactada la lista | Especifico para memoria
 */
struct node
{
    int id;
    int data;
    int pos_other_list;
    int pos_compac;
    node *next;
};

//Funcion que retorna el tamaño de la lista
int size(node *lista)
{
    return lista == NULL ? 0 : 1 + size(lista->next);
}

/**
 * Funcion especificamente pensada para llenar la lista de procesos y memoria
 * 
 * lista: Se refiere a la lista de memoria compactada que inicialmente apunta a NULL
 * info: Se refiere al tamaño que tendra este espacio en memoria
 * id: Se refiere al id del bloque, el de memoria
 */
void insertarFinal(node **lista, int info, int id)
{
    node *n = new node;
    n->id = id;
    n->data = info;
    n->next = NULL;

    if (!*lista)
    {
        *lista = n;
    }
    else
    {
        node *aux = *lista;

        while (aux->next)
            aux = aux->next;

        aux->next = n;
    }
}

//Funcion que imprime en consola el nombre del proceso y su tamaño
void mostrar_process(node *lista)
{
    if (lista)
    {
        cout << "Proceso " << lista->id << " - " << lista->data << "\n";
        mostrar_process(lista->next);
    }
}

//Funcion que imprime en consola el nombre de la memoria y su tamaño
void mostrar_memory(node *lista)
{
    if (lista)
    {
        cout << "Bloque de memoria " << lista->id << " - " << lista->data << "\n";
        mostrar_memory(lista->next);
    }
}

//Funcion especifica para encontrar la data/tamaño mayor de una memoria
int retro_DATA(node *lista)
{
    node *aux = lista;
    int max = 0;

    for (int i = 0; i < size(lista); i++)
    {
        if (max < aux->data)
        {
            max = aux->data;
        }
        aux = aux->next;
    }
    return max;
}

//Funcion especifica para encontrar la id mayor de una memoria
int retro_ID(int max_id, node *lista)
{
    node *aux = lista;
    int data = 0;
    int max = 0;

    for (int i = 0; i < size(lista); i++)
    {
        if (data < aux->data)
        {
            data = aux->data;
            max = aux->id;
        }
        aux = aux->next;
    }
    return max;
}

/**
 * Funcion que realiza el algoritmo de peor ajuste de memoria
 * 
 * max_data: La cantidad de memoria mayor de la lista de memorias
 * max_id: Contiene el id de la memoria con mayor tamaño en la lista de memorias
 * lista1: Se refiere a la lista de procesos
 * lista2: Se refiere a la lista de memorias
 */
void asignacion(int max_data, int max_id, node *lista1, node *lista2)
{
    node *aux2 = lista2;

    int tam = size(aux2);
    int tam_lista = size(lista1);
    if (lista1)
    {
        for (int j = 0; j < tam; j++)
        {
            if (max_id == aux2->id && max_data > lista1->data)
            {
                lista1->pos_other_list = aux2->id;
                aux2->data = aux2->data - lista1->data;
                cout << "El proceso " << lista1->id << " se almaceno en la memoria " << aux2->id << ". El espacio en " << lista1->pos_other_list << " es: " << aux2->data << "\n";
                max_data = retro_DATA(lista2);
                max_id = retro_ID(max_id, lista2);
                break;
            }
            if (max_id == aux2->id && max_data < lista1->data)
            {
                cout << "El proceso " << lista1->id << " NO se almaceno en la memoria."
                     << "\n";
                lista1->pos_other_list = 0;
            }

            aux2 = aux2->next;
        }
        asignacion(max_data, max_id, lista1->next, lista2);
    }
}

/**
 * Funcion de preparacion para el algoritmo de peor ajuste
 * 
 * lista1: Se refiere a la lista de procesos
 * lista2: Se refiere a la lista de memorias
 */
void pre_asignacion(node *lista1, node *lista2)
{
    int max_data = 0;
    int max_id = 0;
    max_data = retro_DATA(lista2);
    max_id = retro_ID(max_id, lista2);

    asignacion(max_data, max_id, lista1, lista2);
}

/**
 * Funcion que realiza lo inverso a la funcion de aignacion
 * 
 * find: Se refiere al numero ingresado como nombre del proceso a des-asignar
 * lista1: Se refiere a la lista de procesos
 * lista2: Se refiere a la lista de memorias
 */
void des_asignacion(int find, node *lista1, node *lista2)
{
    node *aux2 = lista2;
    int tam = size(aux2);
    int tam_lista = size(lista1);
    if (lista1)
    {
        for (int j = 0; j < tam; j++)
        {
            if (aux2->id == lista1->pos_other_list)
            {
                if (lista1->id == find)
                {
                    aux2->data += lista1->data;
                    lista1->pos_other_list = 0;
                    break;
                }
            }
            aux2 = aux2->next;
        }
        des_asignacion(find, lista1->next, lista2);
    }
}

/**
 * Funcion de preparacion des-asignar un proceso
 * 
 * lista1: Se refiere a la lista de procesos
 * lista2: Se refiere a la lista de memorias
 */
void pre_des_asignacion(node *lista1, node *lista2)
{
    //Lista2 sera de memoria
    //Lista1 sera de procesos
    int find;
    cout << "Inserte numero del proceso: "
         << "\n";
    cin >> find;

    des_asignacion(find, lista1, lista2);
}

/**
 * Funcion para mostrar el estado actual de los procesos | informa en que memoria esta asignado el proceso
 */
void estados(node *proceso)
{
    node *aux = proceso;

    for (int i = 0; i < size(proceso); i++)
    {
        if (aux->pos_other_list != 0)
        {
            cout << "El proceso " << aux->id << " esta en la memoria " << aux->pos_other_list << ".\n";
        }
        aux = aux->next;
    }
}

/**
 * Funcion para mostrar el estado actual de la memoria | informa en que cuanta memoria libre tiene cada bloque de memoria
 */
void estados_memoria(node *memoria)
{
    node *aux = memoria;

    for (int i = 0; i < size(memoria); i++)
    {
        cout << "La memoria " << aux->id << " tiene una cantidad de " << aux->data << " disponible"
             << ".\n";
        aux = aux->next;
    }
}

/**
 * Funcion para calcular el total me memoria disponible de toda la memoria
 * 
 * memoria: Se refiere a la lista de memoria
 * tam: Se refiere a la cantidad de bloques de memoria que se tienen
 * disponibles: Se refiere a la variable que retornara la funcion - contendra el total de memoria disponible
 */
int fun_disponible(node *memoria, int tam, int disponibles)
{
    node *aux = memoria;
    for (int i = 0; i < tam; i++)
    {
        disponibles += aux->data;
        aux = aux->next;
    }
    return disponibles;
}

//Funcion que maneja el flujo de opciones que podra seleccionar el usuario al correr el programa
void menu();

/**Variables globales
 * 
 * procesos: Es la estructura de lista simple para procesos
 * bloque_memoria: Es la estructura de lista simple para la memoria
 * 
 * compresion: Es la estructura de lista simple para la memoria una vez compactada
 * aux: Es la estructura de lista simple que se utiliza como auxiliar apuntando a la lista de procesos
 * 
 * disponibles: Contendra la cantidad total de memoria que se encunetra disponible
 * no_disponible: Contiene la cantidad total de memoria que esta siendo utilizada por un proceso
 * 
 * data:
 * nombre_memoria: Contiene los id de la memoria, siendo la forma en la que se nombran
 * nombre_proceso: Contiene los id de los procesos, siendo la forma en la que se nombran
 */

node *procesos = NULL,
     *bloque_memoria = NULL;
node2 *compresion = NULL;
node *aux;

int disponibles = 0;
int no_disponible = 0;

int data;
int nombre_memoria;
int nombre_proceso;

//main class
int main(int argc, char const *argv[])
{
    menu();
    return 0;
}

void menu()
{
    int option;

    /**
     * cantidad_procesos: Cantidad de procesos que usara el usuatio
     * process_size: tamaño del proceso
     * 
     * cantidad_bloque_m: Cantidad de bloques de memoria
     * bloque_m_size: tamaño de la memoria
    */

    int cantidad_process, process_size,
        cantidad_bloque_m, bloque_m_size;

    cout << "Ingrese cantidad de procesos: ";
    cin >> cantidad_process;
    cout << "Ingrese cantidad de bloques de memoria: ";
    cin >> cantidad_bloque_m;
    cout << "########## PROCESOS ##########\n";
    for (int i = 0; i < cantidad_process; i++)
    {
        cout << "Tamanio del proceso " << i + 1 << ": ";
        cin >> process_size; //El tamaño del proceso
        insertarFinal(&procesos, process_size, i + 1);
    }
    cout << "########## MEMORIA ##########\n";
    for (int i = 0; i < cantidad_bloque_m; i++)
    {
        cout << "Tamanio del de la memoria " << i + 1 << ": ";
        cin >> bloque_m_size; //El tamaño de memoria del bloque
        insertarFinal(&bloque_memoria, bloque_m_size, i + 1);
    }

    mostrar_process(procesos);
    mostrar_memory(bloque_memoria);
    cout << "\n";

    do
    {
        cout << "\n";
        cout << "1. Proceso de asignacion de memoria. \n";
        cout << "2. Proceso de des-asignacion de memoria. \n";
        cout << "3. Ver estado de procesos. \n";
        cout << "4. Ver estado de memoria. \n";
        cout << "5. Realizar compresion. \n";
        cout << "6. Salir \n";
        cin >> option;

        switch (option)
        {
        case 1:
            pre_asignacion(procesos, bloque_memoria);
            break;
        case 2:
            pre_des_asignacion(procesos, bloque_memoria);
            break;
        case 3:
            estados(procesos);
            break;
        case 4:
            estados_memoria(bloque_memoria);
            break;
        case 5:
            disponibles = 0;
            no_disponible = 0;
            disponibles = fun_disponible(bloque_memoria, cantidad_bloque_m, disponibles);
            aux = procesos;

            data = procesos->data;
            nombre_memoria = procesos->pos_other_list;
            nombre_proceso = procesos->id;
            compresion = NULL;
            for (int i = 0; i < cantidad_process; i++)
            {
                data = aux->data;
                nombre_memoria = aux->pos_other_list;
                nombre_proceso = aux->id;
                cout << "\n";
                insertarFinal_compac(&compresion, data, nombre_memoria, nombre_proceso);
                aux = aux->next;
            }
            insertarFinal_compac(&compresion, disponibles, size(bloque_memoria), 0);
            mostrar_compactacion(compresion);
            break;
        }
    } while (option != 6);
}
