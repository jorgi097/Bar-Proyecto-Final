#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Prototipos
void adminMesas();
void adminCuenta();
void adminCobro();
void adminInventario();
void adminEmpleados();


void altaEmpleado();
void modificacionEmpleado();
void bajaEmpleado();
void numEmpleadosRegistrados();

bool buscar(int buscarempleado);
void clean();


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

typedef struct empleado{
    bool alta;
    int numEmpleado;
    char nombre[25];
    int edad;
    enum turno turno;
    enum puesto puesto;
} empleado;

typedef struct cuenta{
    producto producto[100];
} cuenta;


typedef struct mesa{
    int numMesa;
    empleado empleado;
    cuenta cuenta;
} mesa;


//Variables Globales
int mainOpc = 500;

mesa mesas[15]; //Array con las mesas del bar

empleado empleados[20] = { //Array con todos los empleados
    {false, 0, "Jon Doe", 0, Noche, Mesero},
    {true, 1, "Juan", 25, Noche, Cocinero},
    {true, 2, "Martha", 23, Noche, Mesero},
    {true, 3, "Yolanda", 21, Noche, Mesero},
};

int numEmpleadosUsados = 0;

producto productos[100]; // Array con los productos vendidos


int main(){

    while(mainOpc != 0){ //Imprimir menu principal
        printf("Que desea hacer?\n\n");
        printf("1) Asignar Mesas\n");
        printf("2) Administrar Cuenta\n");
        printf("3) Realizar Cobro\n");
        printf("4) Actualizar Inventario\n");
        printf("5) Administrar Empleados\n");
        printf("0) Salir\n");

        scanf("%d", &mainOpc);

        switch(mainOpc){
        case 1:
            system("cls");
            adminMesas();
            break;
        case 2:
            system("cls");
            adminCuenta();
            break;
        case 3:
            system("cls");
            adminCobro();
            break;
        case 4:
            system("cls");
            adminInventario();
            break;
        case 5:
            system("cls");
            adminEmpleados();
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
    int meseroOpc = 500;

    while(true){
        for(unsigned int i = 1; i < sizeof(mesas) / sizeof(mesas[0]); i++){
            if(mesas[i].empleado.nombre[0] != '\0' && mesas[i].empleado.puesto == Mesero){
                printf("La mesa %d tiene asignado al mesero: %s\n", i, mesas[i].empleado.nombre);
            }
        }
        if(mesas[1].empleado.nombre[0] != '\0'){
            printf("\n");
        }

        printf("Selecciona una mesa (1-%d): ", sizeof(mesas) / sizeof(mesas[0]));

        scanf("%d", &mesaOpc);
        if(mesaOpc == 0){
            break;;
        }

        printf("Asigna un mesero: ");

        scanf("%d", &meseroOpc);
        if(meseroOpc == 0){
            break;;
        }

        if(mesaOpc > 0 && mesaOpc <= 30){
            if(buscar(meseroOpc)){ //Revisa si el mesero esta registrado
                mesas[mesaOpc].numMesa = mesaOpc;
                mesas[mesaOpc].empleado.numEmpleado = meseroOpc;
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

void adminEmpleados(){ // Menu administración de empleados
    int adminEmpleadosOpc;

    while(adminEmpleadosOpc != 0){
        numEmpleadosRegistrados();

        printf("Hay %d empleados dados de alta en este momento\n\n", numEmpleadosUsados);

        printf(" Numero de Empleado |         Nombre |     edad |     turno |     puesto |\n");
        for(unsigned int i = 1; i < sizeof(empleados) / sizeof(empleados[0]); i++){
            if(empleados[i].alta){
                printf("%19d | %14s |%9d |\n", empleados[i].numEmpleado, empleados[i].nombre, empleados[i].edad);
            }
        }


        printf("\nQue deseas hacer?\n\n");
        printf("1) Alta empleado\n");
        printf("2) Modificar empleado\n");
        printf("3) Dar de baja empleado\n");

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

}


//Funciones secundarias

void altaEmpleado(){
    int empleadoOpc;
    printf("Ingresa un numero de empleado a dar de alta: ");
    scanf("%d", &empleadoOpc);
}

void modificacionEmpleado(){

}

void bajaEmpleado(){

}


// FUnciones terciarias
void numEmpleadosRegistrados(){
    for(unsigned int i = 1; i < sizeof(empleados) / sizeof(empleados[0]); i++){
        if(empleados[i].numEmpleado != '\0'){
            numEmpleadosUsados++;
        }
    }
}


bool buscar(int numEmpleado){ // Busca si un empleado esta dado de alta segun su numero de empleado
    int numEmpleados = sizeof(empleados) / sizeof(empleados[0]);

    for(int i = 1; i < numEmpleados; i++){
        if(empleados[i].numEmpleado == numEmpleado && empleados[i].alta){
            return true;
        } else{
            return false;
        }
    }
}


void clean(){ //Limpia el buffer de la entrada estandar (teclado)
    int c;

    while(c != '\n'){
        c = getchar();
    }
}
