#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct BookingNode
{
    int reservationNumber;
    char namePassanger[50];
    char destinationPassanger[50];
    struct BookingNode *left;
    struct BookingNode *right;
};

typedef struct BookingNode Node;

// Prototipos Node
Node *createNode(int reservationNumber, char namePassanger[], char destinationPassanger[]);
Node *insertNode(Node *root, int reservationNumber, char namePassanger[], char destinationPassanger[]);

// Prototipos Void
void inOrder(Node *root);
void treeFree(Node *root);

// Prototipos Void
bool SearchAndPrintDestiny(Node *Node, const char *destiny);

// Prototipos Int
int binarySearch(Node *root, int reservationNumber);
int menu();

Node *createNode(int reservationNumber, char namePassanger[], char destinationPassanger[])
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->reservationNumber = reservationNumber;
    strcpy(newNode->namePassanger, namePassanger);
    strcpy(newNode->destinationPassanger, destinationPassanger);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *insertNode(Node *root, int reservationNumber, char namePassanger[], char destinationPassanger[])
{
    if (root == NULL)
    {
        return createNode(reservationNumber, namePassanger, destinationPassanger);
    }

    if (reservationNumber < root->reservationNumber)
    {
        root->left = insertNode(root->left, reservationNumber, namePassanger, destinationPassanger);
    }
    else if (reservationNumber > root->reservationNumber)
    {
        root->right = insertNode(root->right, reservationNumber, namePassanger, destinationPassanger);
    }
    else
    {
        printf("El numero de reserva ingresado ya existe. \n");
    }

    return root;
}

void inOrder(Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("\nNúmero de reserva: %d \n", root->reservationNumber);
        printf("Pasajero: %s \n", root->namePassanger);
        printf("Destino Vuelo: %s \n\n", root->destinationPassanger);
        inOrder(root->right);
    }
}

Node *minValue(Node *root)
{
    Node *actual = root;

    while (actual->left != NULL)
    {
        actual = actual->left;
    }

    return actual;
}

Node *deleteNode(Node *root, int reservationNumber)
{
    if (root == NULL)
    {
        return root;
    }

    if (reservationNumber < root->reservationNumber)
    {
        root->left = deleteNode(root->left, reservationNumber);
    }
    else if (reservationNumber > root->reservationNumber)
    {
        root->right = deleteNode(root->right, reservationNumber);
    }
    else
    {
        // El Node actual es el que se desea eliminar

        // Caso 1: El Node es una hoja
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // Caso 2: a) El Node tiene un hijo a la right
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        // Caso 2: b) El Node tiene un hijo a la left
        if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        // Caso 3: El Node tiene dos hijos
        Node *temp = minValue(root->right);
        // Se copian los valores del Node mínimo al Node actual
        root->reservationNumber = temp->reservationNumber;
        strcpy(root->namePassanger, temp->namePassanger);
        strcpy(root->destinationPassanger, temp->destinationPassanger);
        // Se elimina el Node mínimo del subárbol derecho
        root->right = deleteNode(root->right, temp->reservationNumber);
    }

    return root;
}

int binarySearch(Node *root, int reservationNumber)
{
    if (root == NULL)
    {
        return -1;
    }
    else if (root->reservationNumber == reservationNumber)
    {
        return 0;
    }
    else if (reservationNumber < root->reservationNumber)
    {
        return binarySearch(root->left, reservationNumber);
    }
    else
    {
        return binarySearch(root->right, reservationNumber);
    }
}

void treeFree(Node *root)
{
    if (root != NULL)
    {
        treeFree(root->left);
        treeFree(root->right);
        free(root);
    }
}

bool SearchAndPrintDestiny(Node *Node, const char *destiny)
{
    if (Node == NULL)
    {
        return false;
    }
    bool found = false;
    if (strcmp(Node->destinationPassanger, destiny) == 0)
    {
        printf("Se encontro una reserva con el destino %s:\n", destiny);
        printf("Numero de reserva: %d\n", Node->reservationNumber);
        printf("Pasajero: %s\n", Node->namePassanger);
        printf("Destino del vuelo: %s\n\n", Node->destinationPassanger);
        found = true;
    }
    bool foundInLeft = SearchAndPrintDestiny(Node->left, destiny);
    bool foundInRight = SearchAndPrintDestiny(Node->right, destiny);
    return found || foundInLeft || foundInRight;
}

int menu()
{
    int option;
    printf("1. Ingresar nueva reserva\n");
    printf("2. Cancelar una reserva\n");
    printf("3. Buscar datos de una reserva segun su numero de reserva\n");
    printf("4. Buscar una reserva segun su destino\n");
    printf("5. Mostrar todas las reservas\n");
    printf("6. Cerrar el programa\n");
    scanf("%d", &option);
    if (option > 6 || option < 1)
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
            scanf("%d", &option);
        } while (option > 6 || option < 1);
    }
    system("cls");
    return option;
}

int main()
{
    Node *root = NULL;
    int option, reservationNumber;
    char namePassanger[50], destinationPassanger[50];
    do
    {
        option = menu();
        switch (option)
        {
        case 1:
            printf("Ingrese su nombre: \n");
            scanf("%s", namePassanger);
            printf("Ingrese su destino: \n");
            scanf("%s", destinationPassanger);
            printf("Ingrese su numero de reserva\n");
            scanf("%d", &reservationNumber);
            root = insertNode(root, reservationNumber, namePassanger, destinationPassanger);
            break;
        case 2:
            printf("Ingrese el numero de reserva a cancelar\n");
            scanf("%d", &reservationNumber);
            root = deleteNode(root, reservationNumber);
            break;
        case 3:
            printf("Ingrese el numero de reserva a buscar\n");
            int targetReservation;
            scanf("%d", &targetReservation);
            int result = binarySearch(root, targetReservation);
            if (result == -1)
            {
                printf("No se encontró ninguna reserva con el numero %d\n", targetReservation);
            }
            else
            {
                printf("El numero de reserva si existe!\n");
            }
            break;
        case 4:
            printf("Ingrese el destino a buscar:\n");
            scanf("%s", destinationPassanger);
            bool found = SearchAndPrintDestiny(root, destinationPassanger);
            if (!found)
            {
                printf("No se encontró ninguna reserva con el destino %s\n", destinationPassanger);
            }
            break;
        case 5:
            printf("A continuacion se muestran todas las reservas:\n");
            inOrder(root);
            break;
        case 6:
            printf("Cerrando el programa...\n");
            break;
        default:
            printf("option invalida, intente nuevamente...\n");
            break;
        }
    } while (option != 6);
    treeFree(root);
    return 0;
}