#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Prototipos
void adminMesas();
void adminCuenta();
void adminCobro();
void adminInventario();
void adminEmpleados();

void altaEmpleado();
void modificacionEmpleado();
void bajaEmpleado();
bool buscar(char buscarmesero []);

//Enum
enum turno{
    Manana = 1,
    Tarde = 2,
    Noche = 3
};

enum puesto{
    Mesero,
    Cocinero,
    Gerente,
    Bartender
};


//Structs
typedef struct producto{
    char nombre[30];
    float precio;
} producto;


typedef struct cuenta{
    producto producto[100];
} cuenta;

typedef struct mesa{
    int numMesa;
    char mesero[25];
    cuenta cuenta;
} mesa;



typedef struct empleado{
    int numEmpleado;
    char nombre[50];
    int edad;
    enum turno turno;
    enum puesto puesto;
} empleado;


//Variables Globales
int mainOpc = 500;

mesa mesas[30]; //Array con las mesas del bar

empleado empleados[50] = { //Array con todos los empleados
    {1, "Juan", 25, Noche, Mesero},
    {2, "Martha", 23, Noche, Mesero},
    {3, "Yolanda", 21, Noche, Mesero},
};

producto productos[100]; // Array con los productos vendidos



int main(){

    while(mainOpc != 0){ //Imprimir menu principal
        printf("Que desea hacer?\n\n");
        printf("1)Asignar Mesas\n");
        printf("2)Administrar Cuenta\n");
        printf("3)Realizar Cobro\n");
        printf("4)Actualizar Inventario\n");
        printf("5)Administrar Empleados\n");
        printf("0)Salir\n");

        scanf("%d", &mainOpc);

        switch(mainOpc){
        case 1: adminMesas();
            break;
        case 2: adminCuenta();
            break;
        case 3: adminCobro();
            break;
        case 4: adminInventario();
            break;
        case 5: adminEmpleados();
            break;
        default:
            break;
        }

    }

    return 0;
}


//Funciones Principales

void adminMesas(){ //Asigna mesas a meseros
    int mesaOpc = 500;
    char meseroOpc[25];
    while(true){
        printf("Selecciona una mesa (1-%d): ", sizeof(mesas) / sizeof(mesas[0]));
        scanf("%d", &mesaOpc);
        if(mesaOpc == 0){
            break;;
        }
        printf("Asigna un mesero: ");
        scanf(" %s", meseroOpc);
        if(strcmp(meseroOpc, "0") == 0){
            break;;
        }
        if(mesaOpc > 0 && mesaOpc <= 30){
            if(buscar(meseroOpc)){ //Revisa si el mesero esta registrado
                mesas[mesaOpc].numMesa = mesaOpc;
                strcpy(mesas[mesaOpc].mesero, meseroOpc);
            } else{
                printf("El mesero no esta registrado intentalo nuevamente\n\n");
            }
        } else{
            printf("Ingresa una mesa del 1 al 30 unicamente\n\n");
        }
    }

}

void adminCuenta(){

}

void adminCobro(){

}

void adminInventario(){

}

void adminEmpleados(){
    int adminEmpleadosOpc;
    printf("Que deseas hacer?\n\n");
    printf("1)Alta empleado\n");
    printf("2)Modificar empleado\n");
    printf("3)Dar de baja empleado\n");

    scanf("%d", &adminEmpleadosOpc);

    switch(adminEmpleadosOpc){
    case  1: altaEmpleado();
        break;
    case  2: modificacionEmpleado();
        break;
    case  3: bajaEmpleado();
        break;
    default:
        break;
    }
}


//Funciones secundarias

bool buscar(char buscarmesero []){
    int num_meseros = sizeof(empleados) / sizeof(empleados[0]);
    for(int i = 1; i < num_meseros; i++){
        if(strcmp(buscarmesero, empleados[i].nombre) == 0){
            return true;
        }
    }
    return false;
}


void altaEmpleado(){
    
}

void modificacionEmpleado(){

}

void bajaEmpleado(){

}