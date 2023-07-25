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
bool buscar(char buscarempleado []);


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
    {0, "Jon Doe", 0, Noche, Mesero},
    {1, "Juan", 25, Noche, Cocinero},
    {2, "Martha", 23, Noche, Mesero},
    {3, "Yolanda", 21, Noche, Mesero},
};

int empleadosInicializados = 0;

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
    char meseroOpc[25];

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

        scanf("%s", meseroOpc);
        if(strcmp(meseroOpc, "0") == 0){
            break;;
        }

        if(mesaOpc > 0 && mesaOpc <= 30){
            if(buscar(meseroOpc)){ //Revisa si el mesero esta registrado
                mesas[mesaOpc].numMesa = mesaOpc;
                strcpy(mesas[mesaOpc].empleado.nombre, meseroOpc);
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
        empleadosRegistrados();

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

}


//Funciones secundarias




void altaEmpleado(){
    char empleadoOpc[25];
do{
    system("cls");
    printf("Ingresa el nombre del empleado a dar de alta: ");
    scanf("%s", &empleadoOpc);

    if(buscar(empleadoOpc)){
        printf("El empleado ya esta registrado");
    }else{
        empleados[empleadosInicializados + 1].nombre = empleadoOpc;
    }
}while()
    

    printf("Ingresa la edad del empleado: ");
    scanf("%s", empleados[empleadosInicializados + 1].edad);
    printf("Ingresa el puesto del empleado: (Mesero | Cocinero | Gerente | Bartender)");
    scanf("%s", empleados[empleadosInicializados + 1].puesto);
    printf("Ingresa el turno del empleado: (Manana | Tarde | Noche)");
    scanf("%s", empleados[empleadosInicializados + 1].turno);
    empleados[empleadosInicializados + 1].numEmpleado = empleadosInicializados + 1;
}

void modificacionEmpleado(){

}

void bajaEmpleado(){

}


// FUnciones terciarias
int empleadosRegistrados(){
    for(unsigned int i = 1; i < sizeof(empleados) / sizeof(empleados[0]); i++){
        if(empleados[i].nombre[0] != '\0'){
            empleadosInicializados++;
            return empleadosInicializados;
        }
    }
}


bool buscar(char buscarempleado []){ // Busca si un empleado existe
    int num_meseros = sizeof(empleados) / sizeof(empleados[0]);

    for(int i = 1; i < num_meseros; i++){
        if(strcmp(buscarempleado, empleados[i].nombre) == 0){
            return true;
        }
    }

    return false;
}


void clean(){ //Limpia el buffer de la entrada estandar (teclado)
    int c;

    while(c != '\n'){
        c = getchar();
    }
}
