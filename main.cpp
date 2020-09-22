#include <iostream>
#include <vector>

using namespace std;

struct node
{
    int id;
    int data;
    vector<int> arr;
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
        //cout << "AQUI ESTA EL ERROR " << aux->data << "\n";
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

    //PROBANDING
    int tam = size(aux2);
    int tam_lista = size(lista1);
    int count = 0;
    if (lista1)
    //cout << "max data: " << max_data << " max_id: " << max_id << " procesos: " << lista1->id << " memoria: " << aux2->id << "\n";
    //for (int i = 0; i < tam_lista; i++)
    //while (count < tam_lista)
    {
        for (int j = 0; j < tam; j++)
        {
            if (max_id == aux2->id && max_data > lista1->data)
            {
                //Necesidad de antigua en struct !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                aux2->arr.push_back(lista1->id);
                lista1->arr.push_back(1);
                // if (lista2->arr.at(0) == lista1->id)
                // {
                //     /* code */
                // }
                aux2->data = aux2->data - lista1->data;
                cout << "El proceso " << lista1->id << " se almaceno en la memoria " << aux2->id << ". El espacio en " << aux2->id << " es: " << aux2->data << "\n";
                max_data = retro_DATA(lista2);
                max_id = retro_ID(max_id, lista2);
                //cout << "Among " << max_data << "\n";
                //cout << "Us " << max_id << "\n";
                break;
            }
            if (max_id == aux2->id && max_data < lista1->data)
            {
                cout << "El proceso " << lista1->id << " NO se almaceno en la memoria."
                     << "\n";
            }

            aux2 = aux2->next;
        }
        //count++;
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
    //Lista2 sera de memoria
    //Lista1 sera de procesos
    node *aux2 = lista2;

    //PROBANDING
    if (lista1)
    {
        if (aux2->arr.size() == 0)
        {
            des_asignacion(find, lista1, lista2->next);
        }
        else
        {
            for (int j = 0; j < aux2->arr.size(); j++)
            {
                if (aux2->arr.at(j) == lista1->id)
                {
                    cout << "El valor del arr.data de memoria en: " << j << " ERA: " << aux2->data << "\n";
                    cout << "El valor del arr de memoria en: " << j << " ERA: " << aux2->arr.at(j) << "\n";
                    cout << "El valor del arr de proceso en: " << 0 << " ERA: " << lista1->arr.at(0) << "\n";
                    aux2->data += lista1->data;
                    cout << "El valor del arr.data de memoria en: " << j << " ERA: " << aux2->data << "\n";
                    aux2->arr.at(j) = 0;
                    cout << "El valor del arr de memoria en: " << j << " es: " << aux2->arr.at(j) << "\n";
                    lista1->arr.at(0) = 0;
                    cout << "El valor del arr de proceso en: " << 0 << " es: " << lista1->arr.at(0) << "\n";
                    break;
                }
                aux2 = aux2->next;
            }
            des_asignacion(find, lista1->next, lista2);
        }
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

void estados(node *memoria)
{
    node *aux = memoria;

    for (int i = 0; i < size(memoria); i++)
    {
        if (aux->arr.size() != 0)
        {
            for (int j = 0; j < aux->arr.size(); j++)
            {
                if (aux->arr.at(j) != 0)
                {
                    cout << "El proceso " << aux->arr.at(j) << " esta en la memoria " << aux->id << ".\n";
                }
            }
        }
        aux = aux->next;
    }
}
//Funciones
void menu();

//Variables globales
node *procesos = NULL,
     *bloque_memoria = NULL;

int main(int argc, char const *argv[])
{
    menu();
    return 0;
}

void menu()
{
    int option;

    do
    {
        cout << "\n";
        cout << "1. Proceso de asignacion de memoria. \n";
        cout << "2. Proceso de des-asignacion de memoria. \n";
        cout << "3. Ver estado de procesos. \n";
        cout << "4. Salir \n";
        cin >> option;

        switch (option)
        {
        case 1:
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

            pre_asignacion(procesos, bloque_memoria);
            break;
        case 2:
            pre_des_asignacion(procesos, bloque_memoria);
            break;
        case 3:
            estados(bloque_memoria);
            break;

        default:
            break;
        }
    } while (option != 4);
}
