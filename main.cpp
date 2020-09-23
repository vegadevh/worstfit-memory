#include <iostream>
#include <vector>

using namespace std;

struct node_
{
    int id;
    int data;

    node *next;
};

struct node
{
    int id;
    int data;
    int pos_other_list;
    int pos_compac;
    node *next;
};

int size(node *lista)
{
    return lista == NULL ? 0 : 1 + size(lista->next);
}

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

void mostrar_process(node *lista)
{
    if (lista)
    {
        cout << "Proceso " << lista->id << " - " << lista->data << "\n";
        mostrar_process(lista->next);
    }
}

void mostrar_memory(node *lista)
{
    if (lista)
    {
        cout << "Bloque de memoria " << lista->id << " - " << lista->data << "\n";
        mostrar_memory(lista->next);
    }
}

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

void pre_asignacion(node *lista1, node *lista2)
{
    //Lista2 sera de memoria
    //Lista1 sera de procesos

    int max_data = 0;
    int max_id = 0;
    max_data = retro_DATA(lista2);
    max_id = retro_ID(max_id, lista2);

    asignacion(max_data, max_id, lista1, lista2);
}

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

int fun_no_disponible(node *procesos, int tam, int no_disponible)
{
    for (int i = 0; i < tam; i++)
    {
        if (procesos->pos_other_list != 0)
        {
            no_disponible += procesos->data;
        }
        procesos = procesos->next;
    }
    return no_disponible;
}

//Metdos de asignacion de memoria por compactacion.

//Funciones
void menu();

//Variables globales
node *procesos = NULL,
     *bloque_memoria = NULL;
node_ *compresion = NULL;

int disponibles = 0;
int no_disponible = 0;

int main(int argc, char const *argv[])
{
    menu();
    return 0;
}

void menu()
{
    int option;

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
            no_disponible = fun_no_disponible(procesos, cantidad_process, no_disponible);
            break;
        }
    } while (option != 6);
}
