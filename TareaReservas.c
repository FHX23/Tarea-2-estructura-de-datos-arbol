#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Nodoreservas
{
    int reservationNumber;
    char namePassanger[50];
    char destinationPassanger[50];
    struct Nodoreservas *izquierda;
    struct Nodoreservas *derecha;
};

typedef struct Nodoreservas NODO;

// Prototipos Nodo
NODO *inicializar(int reservationNumber, char namePassanger[], char destinationPassanger[]);
NODO *insertar(NODO *raiz, int reservationNumber, char namePassanger[], char destinationPassanger[]);

// Prototipos Void
void inOrden(NODO *rarbol);
void treeFree(NODO *rarbol);

//prototipos void 
bool SearchAndPrintDestiny(NODO* nodo, const char* destino);

// Prototipos Int
int binarySearch(NODO *rarbol, int reservationNumber);
int menu();

NODO *inicializar(int reservationNumber, char namePassanger[], char destinationPassanger[])
{
    NODO *nuevoNodo = (NODO *)malloc(sizeof(NODO));
    nuevoNodo->reservationNumber = reservationNumber;
    strcpy(nuevoNodo->namePassanger, namePassanger);
    strcpy(nuevoNodo->destinationPassanger, destinationPassanger);
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

NODO *insertar(NODO *raiz, int reservationNumber, char namePassanger[], char destinationPassanger[])
{
    if (raiz == NULL)
    {
        return inicializar(reservationNumber, namePassanger, destinationPassanger);
    }

    if (reservationNumber < raiz->reservationNumber)
    {
        raiz->izquierda = insertar(raiz->izquierda, reservationNumber, namePassanger, destinationPassanger);
    }
    else if (reservationNumber > raiz->reservationNumber)
    {
        raiz->derecha = insertar(raiz->derecha, reservationNumber, namePassanger, destinationPassanger);
    }
    else
    {
        printf("El numero de reserva ingresado ya existe. \n");
    }

    return raiz;
}

void inOrden(NODO *rarbol)
{
    if (rarbol != NULL)
    {
        inOrden(rarbol->izquierda);
        printf("Número de reserva: %d \n", rarbol->reservationNumber);
        printf("Pasajero: %s \n", rarbol->namePassanger);
        printf("Destino Vuelo: %s \n\n", rarbol->destinationPassanger);
        inOrden(rarbol->derecha);
    }
}

NODO *minimoValor(NODO *raiz)
{
    NODO *actual = raiz;

    while (actual->izquierda != NULL)
    {
        actual = actual->izquierda;
    }

    return actual;
}

NODO *eliminar(NODO *raiz, int reservationNumber)
{
    if (raiz == NULL)
    {
        return raiz;
    }

    if (reservationNumber < raiz->reservationNumber)
    {
        raiz->izquierda = eliminar(raiz->izquierda, reservationNumber);
    }
    else if (reservationNumber > raiz->reservationNumber)
    {
        raiz->derecha = eliminar(raiz->derecha, reservationNumber);
    }
    else
    {
        // El nodo actual es el que se desea eliminar

        // Caso 1: El nodo es una hoja
        if (raiz->izquierda == NULL && raiz->derecha == NULL)
        {
            free(raiz);
            return NULL;
        }

        // Caso 2: a) El nodo tiene un hijo a la derecha
        if (raiz->izquierda == NULL)
        {
            NODO *temp = raiz->derecha;
            free(raiz);
            return temp;
        }
        // Caso 2: b) El nodo tiene un hijo a la izquierda
        if (raiz->derecha == NULL)
        {
            NODO *temp = raiz->izquierda;
            free(raiz);
            return temp;
        }

        // Caso 3: El nodo tiene dos hijos
        NODO *temp = minimoValor(raiz->derecha);

        // Se copian los valores del nodo mínimo al nodo actual
        raiz->reservationNumber = temp->reservationNumber;
        strcpy(raiz->namePassanger, temp->namePassanger);
        strcpy(raiz->destinationPassanger, temp->destinationPassanger);

        // Se elimina el nodo mínimo del subárbol derecho
        raiz->derecha = eliminar(raiz->derecha, temp->reservationNumber);
    }

    return raiz;
}



int binarySearch(NODO *rarbol, int reservationNumber)
{
    if (rarbol == NULL)
    {
        return -1;
    }
    else if (rarbol->reservationNumber == reservationNumber)
    {
        return 0;
    }
    else if (reservationNumber < rarbol->reservationNumber)
    {
        return binarySearch(rarbol->izquierda, reservationNumber);
    }
    else
    {
        return binarySearch(rarbol->derecha, reservationNumber);
    }
}

void treefree(NODO *rarbol)
{
    if (rarbol != NULL)
    {
        treefree(rarbol->izquierda);
        treefree(rarbol->derecha);
        free(rarbol);
    }
}

bool SearchAndPrintDestiny(NODO* nodo, const char* destino) {
    if (nodo == NULL) {
        return false;
    }

    bool found = false;

    if (strcmp(nodo->destinationPassanger, destino) == 0) {
        printf("Se encontro una reserva con el destino %s:\n", destino);
        printf("Numero de reserva: %d\n", nodo->reservationNumber);
        printf("Pasajero: %s\n", nodo->namePassanger);
        printf("Destino del vuelo: %s\n\n", nodo->destinationPassanger);
        found = true;
    }

    bool foundInLeft = SearchAndPrintDestiny(nodo->izquierda, destino);
    bool foundInRight = SearchAndPrintDestiny(nodo->derecha, destino);

    return found || foundInLeft || foundInRight;
}

int menu()
{
    int opcion;

    printf("1. Ingresar nueva reserva\n");
    printf("2. Cancelar una reserva\n");
    printf("3. Buscar datos de una reserva segun su numero de reserva\n");
    printf("4. Buscar una reserva segun su destino\n");
    printf("5. Mostrar todas las reservas\n");
    printf("6. Cerrar el programa\n");
    scanf("%d", &opcion);
    if (opcion > 6 || opcion < 1)
    {
        do
        {
            system("clear");
            printf("Dato erróneo, ingrese nuevamente\n");
            printf("1. Ingresar nueva reserva\n");
            printf("2. Cancelar una reserva\n");
            printf("3. Buscar datos de una reserva segun su numero de reserva\n");
            printf("4. Buscar una reserva segun su destino\n");
            printf("5. Mostrar todas las reservas\n");
            printf("6. Cerrar el programa\n");
            scanf("%d", &opcion);
        } while (opcion > 6 || opcion < 1);
    }
    system("cls");
    return opcion;
}




int main()
{
    NODO *raiz = NULL;

    int opcion, reservationNumber;
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
            scanf("%d", &reservationNumber);
            raiz = insertar(raiz, reservationNumber, namePassanger, destinationPassanger);
            break;

        case 2:
            printf("Ingrese el numero de reserva a cancelar\n");
            scanf("%d", &reservationNumber);
            raiz = eliminar(raiz, reservationNumber);
            break;

        case 3: // Saul: Agregue la busqueda por numero de reserva. Es medio basica la implementacion en el case pero funciona.
            printf("Ingrese el numero de reserva a buscar\n");
            int targetReservation;
            scanf("%d", &targetReservation);
            int resultado = binarySearch(raiz, targetReservation);
            if (resultado == -1)
            {
                printf("No encontrado!\n");
            }
            else
            {
                printf("Encontrado!\n");
            }
            break;

        case 4: // Saul: Agregue la Busqueda por destino, mientras tanto esta limitada a solo la primer persona encontrada.
        	// la hize denuevo para que recorra el arbol y me muestre todos los que coincide  altiro
        	// y si no encontro a nadie muestre el mensaje 
			printf("Ingrese el destino a buscar:\n");
			scanf("%s", destinationPassanger);
			bool found = SearchAndPrintDestiny(raiz, destinationPassanger);
					
			if (!found){
    			printf("No se encontró ninguna reserva con el destino %s\n", destinationPassanger);
			}
			break;

        case 5:
            printf("A continuacion se muestran todas las reservas:\n");
            inOrden(raiz);
            break;

        case 6:
            printf("Cerrando el programa...\n");
            break;

        default:
            printf("Opcion invalida, intente nuevamente...\n");
            break;
        }

    } while (opcion != 6);

    treefree(raiz);

    return 0;
}
