#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototipos
void mesas();
void reservas();
void cobro();
void inventario();
void empleados();

//Structs
struct mesa{
    int numMesa;
    char mesero[25];
};

//Variables Globales
int mainOpc = 500;


char meseros[10][20] = { //Meseros del bar
    "Juan",
    "Maria",
    "Roberto",
    "Miguel",
    "Alejandra"
};


int mesa[30]; //Mesas del bar





int main(){
    for(int i = 0; i < 30; i++){ //Llena el array "mesa"
        mesa[i] = i + 1;
    }


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
        case 1: mesas();
            break;

        case 2: reservas();
            break;

        case 3: cobro();

        case 4: inventario();

        case 5: empleados();

        default:
            break;
        }

    }

    return 0;
}


//Funciones Principales

void mesas(){
    int mesaOpc;
    char meseroOpc;
    printf("Selecciona una mesa: ");
    scanf("%d", &mesaOpc);
    printf("Asigna un mesero: ");
    scanf("%c", &meseroOpc);
    if(mesaOpc >= 0 && mesaOpc <= 30){
        
    }
}

void reservas(){

}

void cobro(){

}

void inventario(){

}

void empleados(){

}