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

void altaProducto();
void modificacionProducto();
void bajaProducto();

void printProductos();
void printEmpleados();
void printMesas(unsigned int mesa);

void numProductosRegistrados();
void numEmpleadosRegistrados();

bool buscarEmp(unsigned int buscarempleado);
bool buscarProd(unsigned int numProd);
bool buscarCuenta(unsigned int numCuenta);

void clean();


//Enums---------------------------------------------------------------
enum turno{ // Turnos que se pueden asignar
	Matutino = 1,
	Vespertino = 2,
	Nocturno = 3
};

enum puesto{ // Puestos que se pueden asignar
	Mesero = 1,
	Cocinero = 2,
	Gerente = 3,
	Bartender = 4
};


//Structs-------------------------------------------------------------
typedef struct producto{
	bool alta;
	unsigned int id;
	char nombre[30];
	float precio;
} producto;

typedef struct empleado{
	bool alta;
	unsigned int id;
	char nombre[25];
	unsigned int edad;
	enum turno turno;
	enum puesto puesto;
} empleado;

typedef struct cuenta{
	unsigned int id;
	producto cuentaProductos[100];
} cuenta;

typedef struct mesa{
	unsigned int numMesa;
	empleado mesaMesero;
	cuenta mesaCuenta;
} mesa;


//Variables Globales--------------------------------------------------
unsigned int numEmpleadosAlta = 0;
unsigned int numEmpleadosIdUsados = 0;

unsigned int numProductosAlta = 0;
unsigned int numProductosIdUsados = 0;

empleado empleados[20] = { //Array con todos los empleados
	{true, 1, "Juan", 25, Nocturno, Mesero},
	{true, 2, "Marta", 23, Nocturno, Mesero},
	{true, 3, "Yolanda", 21, Nocturno, Mesero},
	{true, 4, "Pedro", 30, Nocturno, Mesero},
	{true, 5, "Javier", 35, Nocturno, Gerente},
	{true, 6, "Jimena", 26, Nocturno, Bartender},
	{true, 7, "Alma", 24, Nocturno, Cocinero},
	{true, 8, "Ivan", 26, Nocturno, Cocinero},
	{true, 9, "Michel", 28, Nocturno, Bartender}
};

producto productos[50] = { // Array con los productos vendidos
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
};

cuenta cuentas[100]; // Array con las cuentas del bar

mesa mesas[30]; // Array con las mesas del bar


int main(){ //--------------------------------------------------------
	unsigned int mainOpc = 500;

	for(unsigned int i = 0; i < sizeof(cuentas) / sizeof(cuentas[0]); i++){ // Asigna un id a cada cuenta
		cuentas[i].id = i + 1;
	}

	for(unsigned int i = 0; i < sizeof(mesas) / sizeof(mesas[0]); i++){ // Asigna un id a cada mesa
		mesas[i].numMesa = i + 1;
	}

	while(mainOpc != 0){ // Imprimir menu principal
		system("cls");

		printf("Que deseas administrar?\n\n");
		printf("1) Mesas\n");
		printf("2) Cuentas\n");
		printf("3) Cobro\n");
		printf("4) Inventario\n");
		printf("5) Empleados\n");
		printf("0) Salir\n");

		scanf("%u", &mainOpc);

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
void adminMesas(){ // Asigna meseros y cuentas a las mesas
	unsigned int mesaOpc, modificarOpc, meseroOpc, cuentaOpc;
	unsigned int defaultPar = 0;

	system("cls");

	printMesas(defaultPar);

	printf("\nIndique la mesa a administrar\n");
	scanf("%u", &mesaOpc);

	if(mesaOpc > 0 && mesaOpc <= sizeof(mesas) / sizeof(mesas[0])){ // Si la mesa existe
		for(unsigned int i = 0; i < sizeof(mesas) / sizeof(mesas[0]); i++){
			if(mesas[i].numMesa == mesaOpc){
				while(modificarOpc != 0){
					printf("\nQue deseas modificar de la mesa %u?\n", mesas[i].numMesa);
					printf("1) Mesero\n");
					printf("2) Cuenta\n");
					printf("0) Regresar\n");

					scanf("%u", &modificarOpc);

					switch(modificarOpc){
					case 1:
						printf("\nIngresa el mesero a cargo de la mesa: %u\n\n", mesas[i].numMesa);
						printEmpleados();

						scanf("%u", &meseroOpc);
						if(buscarEmp(meseroOpc)){ // Verificar si el ID del mesero existe
							for(unsigned int j = 0; j < sizeof(empleados) / sizeof(empleados[1]); j++){
								if(empleados[j].id == meseroOpc){
									mesas[i].mesaMesero = empleados[j];
								}
							}
						} else{
							printf("-----Ingrese un mesero registrado-----\n\nPresione una tecla para continuar\n");
							clean();
							getchar();
						}
						system("cls");
						break;
					case 2:
						printf("\nIngresa el numero de cuenta de la mesa: %u\n", mesas[i].numMesa);
						scanf("%u", &cuentaOpc);
						if(buscarCuenta(cuentaOpc)){ // Verificar si el ID de la mesa existe
							for(unsigned int k = 0; k < sizeof(cuentas) / sizeof(cuentas[0]); k++){
								if(cuentas[k].id == cuentaOpc){
									mesas[i].mesaCuenta = cuentas[k];
								}
							}
						} else{
							printf("-----Ingrese una cuenta disponible-----\n\nPresione una tecla para continuar\n");
							clean();
							getchar();
						}
						system("cls");
						break;

					default:
						break;
					}
				}
			}
		}
	} else{
		printf("-----Ingrese una mesa registrada-----\n\nPresione una tecla para continuar\n");
		clean();
		getchar();
	}
}

void adminCuenta(){ // Menu administración de cuentas

}

void adminCobro(){ // Menu para realizar cobros

}

void adminInventario(){ // Menu administración de inventario
	unsigned int adminInventarioOpc;

	while(adminInventarioOpc != 0){
		numProductosRegistrados();

		system("cls");

		printProductos();

		printf("\nQue deseas hacer?\n\n");
		printf("1) Alta producto\n");
		printf("2) Modificar producto\n");
		printf("3) Dar de baja producto\n");
		printf("0) Regresar\n");

		scanf("%u", &adminInventarioOpc);

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
	unsigned int adminEmpleadosOpc;

	while(adminEmpleadosOpc != 0){
		numEmpleadosRegistrados();

		system("cls");

		printEmpleados();

		printf("\nQue deseas hacer?\n\n");
		printf("1) Alta empleado\n");
		printf("2) Modificar empleado\n");
		printf("3) Dar de baja empleado\n");
		printf("0) Regresar\n");

		scanf("%u", &adminEmpleadosOpc);

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
void altaProducto(){ // Da de alta un nuevo produto
	system("cls");

	printProductos();

	printf("\nIngresa el nombre del producto a dar de alta: ");
	scanf("%s", productos[numProductosIdUsados + 1].nombre);

	printf("Ingresa el precio del producto a dar de alta: ");
	scanf("%f", &productos[numProductosIdUsados + 1].precio);

	productos[numProductosIdUsados + 1].alta = true;
	productos[numProductosIdUsados + 1].id = numProductosIdUsados + 1;
}

void modificacionProducto(){ // Modifica las propiedades de los productos
	unsigned int numeroProductoOpc, modificarOpc;

	system("cls");

	printProductos();

	printf("\nIngresa el numero de producto a modificar: \n");
	scanf("%u", &numeroProductoOpc);

	if(buscarProd(numeroProductoOpc)){ // Si el producto esta dado de alta
		for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[0]); i++){
			if(productos[i].id == numeroProductoOpc){
				while(modificarOpc != 0){
					printf("\nQue deseas modificar de %s?\n", productos[i].nombre);
					printf("1) Nombre\n");
					printf("2) Precio\n");
					printf("0) Regresar\n");

					scanf("%u", &modificarOpc);

					switch(modificarOpc){
					case 1:
						printf("\nIngresa el nuevo nombre del producto: %s\n", productos[i].nombre);
						scanf("%s", productos[i].nombre);
						system("cls");
						printProductos();
						break;
					case 2:
						printf("\nIngresa el nuevo precio de: %s\n", productos[i].nombre);
						scanf("%f", &productos[i].precio);
						system("cls");
						printProductos();
						break;

					default:
						break;
					}
				}
			}
		}
	} else{
		printf("-----Ingrese un producto registrado-----\n\nPresione una tecla para continuar\n");
		clean();
		getchar();
	}
}

void bajaProducto(){ // Da de baja logica a productos
	unsigned int numeroProductoOpc;

	system("cls");

	printProductos();

	printf("\nIngresa el numero de producto a dar de baja: \n");
	scanf("%u", &numeroProductoOpc);

	if(buscarProd(numeroProductoOpc)){
		for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[0]); i++){
			if(productos[i].id == numeroProductoOpc){
				productos[i].alta = false;
			}
		}
	}
}

//--------------------------------------------------------------------

void altaEmpleado(){ // Da de alta un nuevo empleado
	system("cls");

	printEmpleados();

	printf("\nIngresa el nombre del empleado a dar de alta: \n");
	scanf("%s", empleados[numEmpleadosIdUsados + 1].nombre);

	printf("Ingresa la edad del empleado a dar de alta: \n");
	scanf("%u", &empleados[numEmpleadosIdUsados + 1].edad);

	do{
		printf("Ingresa el turno del empleado a dar de alta (1: Matutino, 2: Vespertino, 3: Nocturno): \n");
		scanf("%u", (int*)&empleados[numEmpleadosIdUsados + 1].turno);
		if(empleados[numEmpleadosIdUsados + 1].turno < 1 || empleados[numEmpleadosIdUsados + 1].turno > 3){
			printf("\n-----Ingrese un turno valido-----\n\n");
		}
	} while(empleados[numEmpleadosIdUsados + 1].turno < 1 || empleados[numEmpleadosIdUsados + 1].turno > 3); // Verifica que sea un turno valido

	do{
		printf("Ingresa el puesto del empleado a dar de alta (1: Mesero, 2: Cocinero, 3: Gerente, 4: Bartender): \n");
		scanf("%u", (int*)&empleados[numEmpleadosIdUsados + 1].puesto);
		if(empleados[numEmpleadosIdUsados + 1].puesto < 1 || empleados[numEmpleadosIdUsados + 1].puesto > 4){
			printf("\n-----Ingrese un puesto valido-----\n\n");
		}
	} while(empleados[numEmpleadosIdUsados + 1].puesto < 1 || empleados[numEmpleadosIdUsados + 1].puesto > 4); // Verifica que sea un puesto valido

	empleados[numEmpleadosIdUsados + 1].alta = true;
	empleados[numEmpleadosIdUsados + 1].id = numEmpleadosIdUsados + 1;
}

void modificacionEmpleado(){ // Modifica las propiedades de los empleados
	unsigned int numeroEmpleadoOpc, modificarOpc;

	system("cls");

	printEmpleados();

	printf("\nIngresa el numero de empleado del empleado a modificar: \n");
	scanf("%u", &numeroEmpleadoOpc);


	if(buscarEmp(numeroEmpleadoOpc)){ // Si el empleado esta dado de alta
		for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){
			if(empleados[i].id == numeroEmpleadoOpc){
				while(modificarOpc != 0){
					printf("\nQue deseas modificar de %s?\n", empleados[i].nombre);
					printf("1) Nombre\n");
					printf("2) Edad\n");
					printf("3) Turno\n");
					printf("4) Puesto\n");
					printf("0) Regresar\n");

					scanf("%u", &modificarOpc);

					switch(modificarOpc){
					case 1:
						printf("\nIngresa el nuevo nombre del empleado: %s\n", empleados[i].nombre);
						scanf("%s", empleados[i].nombre);
						system("cls");
						printEmpleados();
						break;
					case 2:
						printf("\nIngresa la nueva edad del empleado: %s\n", empleados[i].nombre);
						scanf("%u", &empleados[i].edad);
						system("cls");
						printEmpleados();
						break;
					case 3:
						do{
							printf("\nIngresa el nuevo turno del empleado: %s\n", empleados[i].nombre);
							scanf("%u", (int*)&empleados[i].turno);
							if(empleados[i].turno < Matutino || empleados[i].turno > Nocturno){
								printf("-----Ingrese un turno valido-----\n\n");
							}
						} while(empleados[i].turno < Matutino || empleados[i].turno > Nocturno); // Verifica que sea un turno valido
						system("cls");
						printEmpleados();
						break;
					case 4:
						do{
							printf("\nIngresa el nuevo puesto del empleado: %s\n", empleados[i].nombre);
							scanf("%u", (int*)&empleados[i].puesto);
							if(empleados[i].puesto < 1 || empleados[i].puesto > 4){
								printf("------Ingrese un puesto valido------\n\n");
							}
						} while(empleados[i].puesto < 1 || empleados[i].puesto > 4); // Verifica que sea un puesto valido
						system("cls");
						printEmpleados();
						break;

					default:
						break;
					}
				}
			}
		}
	} else{
		printf("-----Ingrese un empleado registrado-----\n\nPresione una tecla para continuar\n");
		clean();
		getchar();
	}
}

void bajaEmpleado(){ // Da de baja logica a empleados
	unsigned int numeroEmpleadoOpc;

	system("cls");

	printEmpleados();

	printf("\nIngresa el numero de empleado a dar de baja: \n");
	scanf("%u", &numeroEmpleadoOpc);

	if(buscarEmp(numeroEmpleadoOpc)){ // Solo si esta dado de alta
		for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){
			if(empleados[i].id == numeroEmpleadoOpc){
				empleados[i].alta = false;
			}
		}
	}
}

	// FUnciones terciarias-----------------------------------------------
void numEmpleadosRegistrados(){ // Guarda en las variables cuantos empleados estan actualmente dados de alta y los IDs usados hasta el momento
	numEmpleadosAlta = 0;
	numEmpleadosIdUsados = 0;

	for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){ // Empleados dados de alta actualmente
		if(empleados[i].alta){
			numEmpleadosAlta++;
		}
	}

	for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){ // Ids usados al momento
		if(empleados[i].id != 0){
			numEmpleadosIdUsados++;
		}
	}
}

void numProductosRegistrados(){ // Guarda en las variables cuantos productos estan actualmente dados de alta y los IDs usados hasta el momento
	numProductosAlta = 0;
	numProductosIdUsados = 0;

	for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[0]); i++){ // Productos dados de alta actualmente
		if(productos[i].alta){
			numProductosAlta++;
		}
	}

	for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[0]); i++){ // IDs usados al momento
		if(productos[i].id != 0){
			numProductosIdUsados++;
		}
	}
}

void printProductos(){ // Imprime los productos dados de alta como tabla
	printf("El numero de productos registrados es: %u\n\n", numProductosAlta);

	printf(" ID |          NOMBRE |  PRECIO |\n");
	for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[0]); i++){
		if(productos[i].alta){
			printf("%3u |%16s | %7.2f |\n", productos[i].id, productos[i].nombre, productos[i].precio);
		}
	}
}

void printEmpleados(){ // Imprime los empleados dados de alta como tabla
	printf("Hay %u empleados dados de alta en este momento\n\n", numEmpleadosAlta);

	printf("TURNO: Matutino = 1 / Vespertino = 2 / Nocturno = 3\n\nPUESTO: Mesero = 1 / Cocinero = 2 / Gerente = 3 / Bartender = 4\n\n");

	printf(" NUMERO DE EMPLEADO |         NOMBRE |     EDAD |     TURNO |     PUESTO |\n");
	for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){
		if(empleados[i].alta){
			printf("%19u | %14s |%9u |%10u |%11u |\n", empleados[i].id, empleados[i].nombre, empleados[i].edad, empleados[i].turno, empleados[i].puesto);
		}
	}
}

void printMesas(unsigned int mesaPar){ // Imprime las mesas activas
	printf(" # MESA |          EMPLEADO | CUENTA |\n");
	if(mesaPar != 0){

	}
	for(unsigned int i = 0; i < sizeof(mesas) / sizeof(mesas[0]); i++){
		if(mesas[i].numMesa != 0){
			printf("%7u |%18s |%7u |\n", mesas[i].numMesa, mesas[i].mesaMesero.nombre, mesas[i].mesaCuenta.id);
		}
	}
}

bool buscarCuenta(unsigned int numCuenta){ // Busca si el numero de cuenta existe
	for(unsigned int i = 0; i < sizeof(cuentas) / sizeof(cuentas[0]); i++){
		if(cuentas[i].id == numCuenta){
			printf("true");
			return true;
		}
	}
	printf("false");
	return false;
}

bool buscarEmp(unsigned int numEmpleado){ // Busca si un empleado esta dado de alta segun su numero de empleado
	for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){
		if(empleados[i].id == numEmpleado && empleados[i].alta){
			return true;
		}
	}
	return false;
}

bool buscarProd(unsigned int numProd){ // Busca si un producto esta dado de alta segun su numero de empleado
	for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[0]); i++){
		if(productos[i].id == numProd && productos[i].alta){
			return true;
		}
	}
	return false;
}

void clean(){ // Limpia el buffer de la entrada estandar (teclado)
	while(getchar() != '\n');
}
