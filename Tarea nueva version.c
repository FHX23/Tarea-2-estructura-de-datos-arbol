#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Nodoreservas
{
    int reservationNumber;
    char namePassanger[50];
    char destinationPassanger[50];
    struct Nodoreservas *izquierda;
    struct Nodoreservas *Derecha;
};

typedef struct Nodoreservas NODO;

int menu();
NODO *inicializar(int reservationNumber, char namePassanger[], char destinationPassanger[]);
NODO *insertar(NODO *raiz, int reservationNumber, char namePassanger[], char destinationPassanger[]);

void inorden(NODO *rarbol);
void treefree(NODO *rarbol);

int main()
{
    NODO *raiz = NULL; // Inicializa raiz en NULL

    int opcion , reservationNumber;
    char namePassanger[50], destinationPassanger[50];

    do
    {
        opcion = menu();
        switch (opcion)
        {
        case 1:
        
            printf("Ingrese su nombre: \n");
            scanf("%s", namePassanger);

            printf("Ingrese su destino: \n");
            scanf("%s", destinationPassanger);

            printf("Ingrese su numero de reserva\n");
            scanf("%d",&reservationNumber);
            if (raiz==NULL)
            {
                raiz=inicializar(reservationNumber, namePassanger, destinationPassanger);
            }else{
                insertar(raiz,reservationNumber,namePassanger,destinationPassanger);
            }
            
            
            break;

        case 2:

            break;

        case 3:

            break;

        case 4:

            break;

        case 5:
            printf("Ahora vera los numeros de reserva \n");
            inorden(raiz);
            break;

        case 6:

            break;

        default:
            break;
        }

    } while (opcion != 6);


    treefree(raiz);
    raiz = NULL;
    
    return 0;
}

int menu()
{

    int opcion;

    printf("Ingrese 1 para ingresar nueva reserva\n");
    printf("Ingrese 2 para cancelar una reserva\n");
    printf("Ingrese 3 para buscar datos de una reserva segun su numero de reserva\n");
    printf("Ingrese 4 para buscar una reserva segun su destino\n");
    printf("Ingrese 5 para mostrar todas las reservas\n");
    printf("Ingrese 6 para cerrar el progama\n");
    scanf("%d", &opcion);
    if (opcion > 6 || opcion < 1)
    {

        do
        {
            system("clear");
            printf("Dato erroneo Ingrese nuevamente\n");
            printf("Ingrese 1 para ingresar nueva reserva\n");
            printf("Ingrese 2 para cancelar una reserva\n");
            printf("Ingrese 3 para buscar datos de una reserva segun su numero de reserva\n");
            printf("Ingrese 4 para buscar una reserva segun su destino\n");
            printf("Ingrese 5 para mostrar todas las reservas\n");
            printf("Ingrese 6 para cerrar el progama\n");
            
        } while (opcion > 6 || opcion < 1);
    }
    system("cls");
    return opcion;
}

NODO *inicializar(int reservationNumber, char namePassanger[], char destinationPassanger[])
{

    NODO *nuevoNodo = (NODO *)malloc(sizeof(NODO));
    nuevoNodo->reservationNumber = reservationNumber;

    nuevoNodo->izquierda = NULL;
    nuevoNodo->Derecha = NULL;
    return nuevoNodo;
}

NODO *insertar(NODO *raiz, int reservationNumber, char namePassanger[], char destinationPassanger[])
{

    if (raiz == NULL)
    {
        return inicializar(reservationNumber,namePassanger,destinationPassanger);
    }

    if (reservationNumber < raiz->reservationNumber)
    {
        raiz->izquierda = insertar(raiz->izquierda,reservationNumber,namePassanger,destinationPassanger);
    }
    else if (reservationNumber > raiz->reservationNumber)
    {
        raiz->Derecha = insertar(raiz->Derecha, reservationNumber,namePassanger,destinationPassanger);
    }

    return raiz;
}

void inorden(NODO *rarbol)
{
    if (rarbol != NULL)
    {
        inorden(rarbol->izquierda);
        printf("numero de reserva: %d \n", rarbol->reservationNumber);
        inorden(rarbol->Derecha);
    }
}

void treefree(NODO *rarbol)
{
    if (rarbol != NULL)
    {
        treefree(rarbol->izquierda);
        treefree(rarbol->Derecha);
        free(rarbol); // Usa free en lugar de delete
    }
}