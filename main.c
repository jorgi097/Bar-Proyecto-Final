#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Prototipos----------------------------------------------------------
void adminMesas();
void adminCuenta();
void adminCobro();
void adminInventario();
void adminEmpleados();


void altaEmpleado();
void modificacionEmpleado();
void bajaEmpleado();
void numEmpleadosRegistrados();


void altaProducto();
void modificacionProducto();
void bajaProducto();
void numProductosRegistrados();

bool buscar(int buscarempleado);
void clean();


//Enums---------------------------------------------------------------
enum turno{
    Matutino = 1,
    Vespertino = 2,
    Nocturno = 3
};


enum puesto{
    Mesero = 1,
    Cocinero = 2,
    Gerente = 3,
    Bartender = 4
};


//Structs-------------------------------------------------------------
typedef struct producto{
    bool alta;
    int id;
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


//Variables Globales--------------------------------------------------
int mainOpc = 500;

mesa mesas[15]; //Array con las mesas del bar

empleado empleados[20] = { //Array con todos los empleados
    {false, 0, " ", 0, 0, 0},
    {true, 1, "Juan", 25, 3, Mesero},
    {true, 2, "Marta", 23, 3, Mesero},
    {true, 3, "Yolanda", 21, 3, Mesero},
};

int numEmpleadosUsados = 0;
int numProductosUsados = 0;
int numIdUsados = 0;

producto productos[50] = {
    {false, 0, "", 0},
    {true, 1, "Papas", 30},
    {true, 2, "Hotdog", 35},
    {true, 3, "Hamburguesa", 65},
    {true, 4, "Taco Asada", 25},
    {true, 5, "Taco Chorizo", 25},
    {true, 6, "Indio", 25},
    {true, 7, "Corona", 25},
    {true, 8, "Modelo", 25},
    {true, 9, "Victoria", 25},
    {true, 10, "Michelada", 25},
    {true, 11, "Tequila", 30},
    {true, 12, "Mezcal", 30},
    {true, 13, "Whisky", 30},
    {true, 14, "Perla Negra", 35},
    {true, 15, "Mojito", 35},
    {true, 16, "Limonada", 20},
}; // Array con los productos vendidos


int main(){ //--------------------------------------------------------

    while(mainOpc != 0){ //Imprimir menu principal
        printf("Que deseas administrar?\n\n");
        printf("1) Mesas\n");
        printf("2) Cuentas\n");
        printf("3) Cobro\n");
        printf("4) Inventario\n");
        printf("5) Empleados\n");
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


//Funciones Principales-----------------------------------------------
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
    int adminInventarioOpc;

    while(adminInventarioOpc != 0){
        numProductosRegistrados();
        system("cls");

        printf("El numero de productos regisrados es: %d\n\n", numProductosUsados);

        printf(" ID |          NOMBRE |  PRECIO |\n");
        for(unsigned int i = 1; i < sizeof(productos) / sizeof(productos[0]); i++){
            if(productos[i].alta){
                printf("%3d |%16s | %7.2f |\n", productos[i].id, productos[i].nombre, productos[i].precio);
            }
        }

        printf("\nQue deseas hacer?\n\n");
        printf("1) Alta producto\n");
        printf("2) Modificar producto\n");
        printf("3) Dar de baja producto\n");
        printf("0) Regresar\n");

        scanf("%d", &adminInventarioOpc);

        switch(adminInventarioOpc){
        case  1: altaProducto();
            break;
        case  2: modificacionProducto();
            break;
        case  3: bajaProducto();
            break;
        default:
            break;
        }
    }




}

void adminEmpleados(){ // Menu administración de empleados
    int adminEmpleadosOpc;

    while(adminEmpleadosOpc != 0){

        numEmpleadosRegistrados();
        system("cls");

        printf("Hay %d empleados dados de alta en este momento\n\n", numEmpleadosUsados);

        printf("TURNO: Matutino = 1 | Vespertino = 2 | Nocturno = 3\n\nPUESTO: Mesero = 1 | Cocinero = 2 | Gerente = 3 | Bartender = 4\n\n");

        printf(" NUMERO DE EMPLEADO |         NOMBRE |     EDAD |     TURNO |     PUESTO |\n");
        for(unsigned int i = 1; i < sizeof(empleados) / sizeof(empleados[0]); i++){
            if(empleados[i].alta){
                printf("%19d | %14s |%9d |%10d |%11d |\n", empleados[i].numEmpleado, empleados[i].nombre, empleados[i].edad, empleados[i].turno, empleados[i].puesto);
            }
        }

        printf("\nQue deseas hacer?\n\n");
        printf("1) Alta empleado\n");
        printf("2) Modificar empleado\n");
        printf("3) Dar de baja empleado\n");
        printf("0) Regresar\n");

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


//Funciones secundarias-----------------------------------------------
void altaEmpleado(){ // AGREGAR DAR DE ALTA EMPLEADOS PREVIAMENTE DADOS DE BAJA
    printf("Ingresa el nombre del empleado a dar de alta: ");
    scanf("%s", empleados[numEmpleadosUsados + 1].nombre);

    printf("Ingresa la edad del empleado a dar de alta: ");
    scanf("%d", &empleados[numEmpleadosUsados + 1].edad);

    printf("Ingresa el turno del empleado a dar de alta (1: Matutino, 2: Vespertino, 3: Nocturno): ");
    scanf("%d", (int*)&empleados[numEmpleadosUsados + 1].turno);

    printf("Ingresa el puesto del empleado a dar de alta (1: Mesero, 2: Cocinero, 3: Gerente, 4: Bartender): ");
    scanf("%d", (int*)&empleados[numEmpleadosUsados + 1].puesto);

    empleados[numEmpleadosUsados + 1].alta = true;
    empleados[numEmpleadosUsados + 1].numEmpleado = numEmpleadosUsados + 1;
}

void modificacionEmpleado(){ // AGREGAR NO MODIFICAR EMPLEADOS DADOS DE BAJA
    int numeroEmpleadoOpc, modificarOpc;

    system("cls");

    printf("Ingresa el numero de empleado del empleado a modificar: \n");
    scanf("%d", &numeroEmpleadoOpc);

    while(modificarOpc != 0){
        printf("Que deseas modificar de %s?\n", empleados[numeroEmpleadoOpc].nombre);
        printf("1) Nombre\n");
        printf("2) Edad\n");
        printf("3) Turno\n");
        printf("4) Puesto\n");
        printf("0) Regresar\n");

        scanf("%d", &modificarOpc);

        switch(modificarOpc){
        case 1:
            printf("\nIngresa el nombre del empleado: \n");
            scanf("%s", empleados[numeroEmpleadoOpc].nombre);
            printf("Cambio ralizado\n\n");
            break;
        case 2:
            printf("\nIngresa la edad del empleado: ");
            scanf("%d", &empleados[numeroEmpleadoOpc].edad);
            printf("Cambio ralizado\n\n");
            break;
        case 3:
            printf("\nIngresa el turno del empleado (1: Matutino, 2: Vespertino, 3: Nocturno): \n");
            scanf("%d", (int*)&empleados[numeroEmpleadoOpc].turno);
            printf("Cambio ralizado\n\n");
            break;
        case 4:
            printf("\nIngresa el puesto del empleado(1: Mesero, 2: Cocinero, 3: Gerente, 4: Bartender): \n");
            scanf("%d", (int*)&empleados[numeroEmpleadoOpc].puesto);
            printf("Cambio ralizado\n\n");
            break;

        default:
            break;
        }
    }
}

void bajaEmpleado(){ //Da de baja logica a empleados
    int numeroEmpleadoOpc;

    system("cls");

    printf("Ingresa el numero de empleado a dar de baja: \n");
    scanf("%d", &numeroEmpleadoOpc);

    empleados[numeroEmpleadoOpc].alta = false;
}


void altaProducto(){
    printf("Ingresa el nombre del producto a dar de alta: ");
    scanf("%s", productos[numProductosUsados + 1].nombre);

    printf("Ingresa el precio del producto a dar de alta: ");
    scanf("%f", &productos[numProductosUsados + 1].precio);

    productos[numProductosUsados + 1].alta = true;
    productos[numProductosUsados + 1].id = numProductosUsados + 1;
}


void modificacionProducto(){
    int numeroProductoOpc, modificarOpc;

    system("cls");

    printf("Ingresa el numero de producto a modificar: \n");
    scanf("%d", &numeroProductoOpc);

    while(modificarOpc != 0){
        printf("Que deseas modificar de %s?\n", productos[numeroProductoOpc].nombre);
        printf("1) Nombre\n");
        printf("2) Precio\n");
        printf("0) Regresar\n");

        scanf("%d", &modificarOpc);

        switch(modificarOpc){
        case 1:
            printf("\nIngresa el nombre del producto: \n");
            scanf("%s", productos[numeroProductoOpc].nombre);
            printf("Cambio ralizado\n\n");
            break;
        case 2:
            printf("\nIngresa la edad del empleado: ");
            scanf("%f", &productos[numeroProductoOpc].precio);
            printf("Cambio ralizado\n\n");
            break;

        default:
            break;
        }
    }
}


void bajaProducto(){
    int numeroProductoOpc;

    system("cls");

    printf("Ingresa el numero de producto a dar de baja: \n");
    scanf("%d", &numeroProductoOpc);

    productos[numeroProductoOpc].alta = false;
}





// FUnciones terciarias-----------------------------------------------
void numEmpleadosRegistrados(){
    numEmpleadosUsados = 0;

    for(unsigned int i = 1; i < sizeof(empleados) / sizeof(empleados[0]); i++){
        if(empleados[i].numEmpleado != 0){
            numEmpleadosUsados++;
        }
    }
}


void numProductosRegistrados(){
    numProductosUsados = 0;
    numIdUsados = 0;

    for(unsigned int i = 1; i < sizeof(productos) / sizeof(productos[0]); i++){
        if(productos[i].id != 0){
            if(productos[i].alta){
                numProductosUsados++;
            }
        }
    }

    for(unsigned int i = 1; i < sizeof(productos) / sizeof(productos[0]); i++){
        if(productos[i].id != 0){
            if(productos[i].alta){
                numProductosUsados++;
            }
        }
    }
    
    
}



bool buscar(int numEmpleado){ // Busca si un empleado esta dado de alta segun su numero de empleado
    int numEmpleados = sizeof(empleados) / sizeof(empleados[0]);

    for(int i = 1; i < numEmpleados; i++){
        if(empleados[i].numEmpleado == numEmpleado && empleados[i].alta){
            return true;
        }
    }
    return false;
}


void clean(){ //Limpia el buffer de la entrada estandar (teclado)
    int c;
    int contador = 0;
    int limite_intentos = 100;

    while((c = getchar()) != '\n' && c != EOF && contador < limite_intentos){
        contador++;
    }
}
