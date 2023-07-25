#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Prototipos
void adminMesas();
void adminReservas();
void adminCobro();
void adminInventario();
void adminEmpleados();

bool buscar(char buscarmesero []);

//Structs
typedef struct mesa{
    int numMesa;
    char mesero[25];
} mesa;

//Variables Globales
int mainOpc = 500;

mesa mesas[30]; //Mesas del bar

char meseros[15][20] = { //Meseros del bar
    "Juan",
    "Maria",
    "Roberto",
    "Miguel",
    "Alejandra"
};



int main(){

    while(mainOpc != 0){ //Imprimir menu principal
        printf("Que desea hacer?\n\n");
        printf("1)Asignar Mesas\n");
        printf("2)Administrar Reservas\n");
        printf("3)Realizar Cobro\n");
        printf("4)Actualizar Inventario\n");
        printf("5)Administrar Empleados\n");
        printf("0)Salir\n");

        scanf("%d", &mainOpc);

        switch(mainOpc){
        case 1: adminMesas();
            break;
        case 2: adminReservas();
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

void adminMesas(){
    int mesaOpc = 500;
    char meseroOpc[25];
    while(mesaOpc != 0 && meseroOpc != "0"){
        int mesaOpc;
        char meseroOpc[25];
        printf("Selecciona una mesa: ");
        scanf("%d", &mesaOpc);
        printf("Asigna un mesero: ");
        scanf(" %s", meseroOpc);
        if(mesaOpc > 0 && mesaOpc <= 30){
            if(buscar(meseroOpc)){
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

void adminReservas(){
    
}

void adminCobro(){

}

void adminInventario(){

}

void adminEmpleados(){

}


//Funciones secundarias

bool buscar(char buscarmesero []){
    int num_meseros = sizeof(meseros) / sizeof(meseros[0]);
    for(int i = 0; i < num_meseros; i++){
        if(strcmp(buscarmesero, meseros[i]) == 0){
            return true;
        }
    }
    return false;
}
