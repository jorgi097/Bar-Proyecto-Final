#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
void printProductos();

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
    int id;
    char nombre[25];
    int edad;
    enum turno turno;
    enum puesto puesto;
} empleado;

typedef struct cuenta{
    producto cuentaProductos[100];
} cuenta;

typedef struct mesa{
    int numMesa;
    empleado mesaMesero[1];
    cuenta mesaCuenta[1];
} mesa;


//Variables Globales--------------------------------------------------
int mainOpc = 500;

empleado empleados[20] = { //Array con todos los empleados
    {true, 1, "Juan", 25, Nocturno, Mesero},
    {true, 2, "Marta", 23, 3, Mesero},
    {true, 3, "Yolanda", 21, 3, Mesero},
};

int numEmpleadosAlta = 0;
int numEmpleadosIdUsados = 0;
int numProductosAlta = 0;
int numIdUsados = 0;

producto productos[50] = {
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

mesa mesas[30]; //Array con las mesas del bar

int main(){ //--------------------------------------------------------
    while(mainOpc != 0){ //Imprimir menu principal
        system("cls");
        
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

}

void adminCuenta(){ // Menu administración de cuentas

}

void adminCobro(){ // Menu para realizar cobros

}

void adminInventario(){ // Menu administración de inventario
    int adminInventarioOpc;

    while(adminInventarioOpc != 0){
        numProductosRegistrados();

        system("cls");

        printProductos();

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

        printf("Hay %d empleados dados de alta en este momento\n\n", numEmpleadosAlta);

        printf("TURNO: Matutino = 1 | Vespertino = 2 | Nocturno = 3\n\nPUESTO: Mesero = 1 | Cocinero = 2 | Gerente = 3 | Bartender = 4\n\n");

        printf(" NUMERO DE EMPLEADO |         NOMBRE |     EDAD |     TURNO |     PUESTO |\n");
        for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[1]); i++){
            if(empleados[i].alta){
                printf("%19d | %14s |%9d |%10d |%11d |\n", empleados[i].id, empleados[i].nombre, empleados[i].edad, empleados[i].turno, empleados[i].puesto);
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
void altaProducto(){ //AGREGAR DAR DE ALTA PRODUCTOS DADOS DE BAJA ANTERIORMENTE
    system("cls");

    printProductos();

    printf("\nIngresa el nombre del producto a dar de alta: ");
    scanf("%s", productos[numIdUsados + 1].nombre);

    printf("Ingresa el precio del producto a dar de alta: ");
    scanf("%f", &productos[numIdUsados + 1].precio);

    productos[numIdUsados + 1].alta = true;
    productos[numIdUsados + 1].id = numIdUsados + 1;
}

void modificacionProducto(){ //AGREGAR NO PERMITIR MODIFICAR PRODUCTOS DADOS DE BAJA
    int numeroProductoOpc, modificarOpc;

    system("cls");

    printProductos();

    printf("\nIngresa el numero de producto a modificar: \n");
    scanf("%d", &numeroProductoOpc);

    while(modificarOpc != 0){
        printf("Que deseas modificar de %s?\n", productos[numeroProductoOpc-1].nombre);
        printf("1) Nombre\n");
        printf("2) Precio\n");
        printf("0) Regresar\n");

        scanf("%d", &modificarOpc);

        switch(modificarOpc){
        case 1:
            printf("\nIngresa el nombre del producto: \n");
            scanf("%s", productos[numeroProductoOpc-1].nombre);
            printf("Cambio ralizado\n\n");
            break;
        case 2:
            printf("\nIngresa la edad del empleado: ");
            scanf("%f", &productos[numeroProductoOpc-1].precio);
            printf("Cambio ralizado\n\n");
            break;

        default:
            break;
        }
    }
}

void bajaProducto(){ //AGREGAR NO DAR DE BAJA PRODUCTOS DADOS DE BAJA
    int numeroProductoOpc;

    system("cls");

    printProductos();

    printf("\nIngresa el numero de producto a dar de baja: \n");
    scanf("%d", &numeroProductoOpc);

    productos[numeroProductoOpc-1].alta = false;
}

//--------------------------------------------------------------------

void altaEmpleado(){ // AGREGAR DAR DE ALTA EMPLEADOS PREVIAMENTE DADOS DE BAJA
    printf("Ingresa el nombre del empleado a dar de alta: ");
    scanf("%s", empleados[numEmpleadosIdUsados + 1].nombre);

    printf("Ingresa la edad del empleado a dar de alta: ");
    scanf("%d", &empleados[numEmpleadosIdUsados + 1].edad);

    printf("Ingresa el turno del empleado a dar de alta (1: Matutino, 2: Vespertino, 3: Nocturno): ");
    scanf("%d", (int*)&empleados[numEmpleadosIdUsados + 1].turno);

    printf("Ingresa el puesto del empleado a dar de alta (1: Mesero, 2: Cocinero, 3: Gerente, 4: Bartender): ");
    scanf("%d", (int*)&empleados[numEmpleadosIdUsados + 1].puesto);

    empleados[numEmpleadosIdUsados + 1].alta = true;
    empleados[numEmpleadosIdUsados + 1].id = numEmpleadosIdUsados + 1;
}

void modificacionEmpleado(){ // AGREGAR NO MODIFICAR EMPLEADOS DADOS DE BAJA
    int numeroEmpleadoOpc, modificarOpc;

    system("cls");

    printf("Ingresa el numero de empleado del empleado a modificar: \n");
    scanf("%d", &numeroEmpleadoOpc);

    while(modificarOpc != 0){
        printf("Que deseas modificar de %s?\n", empleados[numeroEmpleadoOpc-1].nombre);
        printf("1) Nombre\n");
        printf("2) Edad\n");
        printf("3) Turno\n");
        printf("4) Puesto\n");
        printf("0) Regresar\n");

        scanf("%d", &modificarOpc);

        switch(modificarOpc){
        case 1:
            printf("\nIngresa el nombre del empleado: \n");
            scanf("%s", empleados[numeroEmpleadoOpc-1].nombre);
            printf("Cambio ralizado\n\n");
            break;
        case 2:
            printf("\nIngresa la edad del empleado: ");
            scanf("%d", &empleados[numeroEmpleadoOpc-1].edad);
            printf("Cambio ralizado\n\n");
            break;
        case 3:
            printf("\nIngresa el turno del empleado (1: Matutino, 2: Vespertino, 3: Nocturno): \n");
            scanf("%d", (int*)&empleados[numeroEmpleadoOpc-1].turno);
            printf("Cambio ralizado\n\n");
            break;
        case 4:
            printf("\nIngresa el puesto del empleado(1: Mesero, 2: Cocinero, 3: Gerente, 4: Bartender): \n");
            scanf("%d", (int*)&empleados[numeroEmpleadoOpc-1].puesto);
            printf("Cambio ralizado\n\n");
            break;

        default:
            break;
        }
    }
}

void bajaEmpleado(){ //Da de baja logica a empleados
//AGREGAR NO DAR DE BAJA A EMPLEADOS DADOS DE BAJA
    int numeroEmpleadoOpc;

    system("cls");

    printf("Ingresa el numero de empleado a dar de baja: \n");
    scanf("%d", &numeroEmpleadoOpc);

    empleados[numeroEmpleadoOpc-1].alta = false;
}


// FUnciones terciarias-----------------------------------------------
void numEmpleadosRegistrados(){
    numEmpleadosAlta = 0;
    numEmpleadosIdUsados = 0;

    for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[1]); i++){
        if(empleados[i].alta){
            numEmpleadosAlta++;
        }
    }

    for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[1]); i++){
        if(empleados[i].id != 0){
            numEmpleadosIdUsados++;
        }
    }
}

void numProductosRegistrados(){
    numProductosAlta = 0; // Resetea a 0
    numIdUsados = 0; // Resetea a 0

    for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[1]); i++){ // Guarda cuantos productos estan dados de alta
        if(productos[i].alta){
            numProductosAlta++;
        }
    }

    for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[1]); i++){ // Guarda cuantos ID estan usados
        if(productos[i].id != 0){
            numIdUsados++;
        }
    }
}

void printProductos(){
    printf("El numero de productos registrados es: %d\n\n", numProductosAlta);

    printf(" ID |          NOMBRE |  PRECIO |\n");
    for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[1]); i++){
        if(productos[i].alta){
            printf("%3d |%16s | %7.2f |\n", productos[i].id, productos[i].nombre, productos[i].precio);
        }
    }
}

bool buscar(int numEmpleado){ // Busca si un empleado esta dado de alta segun su numero de empleado
    int numEmpleados = sizeof(empleados) / sizeof(empleados[1]);

    for(int i = 0; i < numEmpleados; i++){
        if(empleados[i].id == numEmpleado && empleados[i].alta){
            return true;
        }
    }
    return false;
}

void clean(){ //Limpia el buffer de la entrada estandar (teclado)
    while(getchar() != '\n');
}
