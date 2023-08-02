#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Prototipos----------------------------------------------------------
void adminMesas();
void adminInventario();
void adminEmpleados();

void adminCuenta(unsigned int mesaOpc);

void altaEmpleado();
void modificacionEmpleado();
void bajaEmpleado();

void altaProducto();
void modificacionProducto();
void bajaProducto();

void printProductos(int productosParametro);
void printEmpleados(int empleadosParametro);
void printMesas(int mesaParametro);
void printProductosCuenta(int productosCuentaParametro, int productosCuentaParametro2);

void numProductosRegistrados();
void numEmpleadosRegistrados();

bool buscarEmpleado(unsigned int numEmpleado);
bool buscarProducto(unsigned int numProd);
bool buscarCuenta(unsigned int numCuenta);
int buscarCuentaLibre();

void cuentaAutomatica(unsigned int modificar);
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
	bool used;
} cuenta;

typedef struct mesa{
	unsigned int numMesa;
	empleado mesaMesero;
	cuenta* mesaCuenta;
} mesa;


//Variables Globales--------------------------------------------------
unsigned int numEmpleadosAlta = 0; // Se usa en la funcion numEmpleadosRegistrados
unsigned int numEmpleadosIdUsados = 0; // Se usa en la funcion numEmpleadosRegistrados

unsigned int numProductosAlta = 0; // Se usa en la funcion numProductosRegistrados
unsigned int numProductosIdUsados = 0; // Se usa en la funcion numProductosRegistrados

int defaultParameter = 500; // Argumento por default para varias funciones

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
	{true, 17, "Irvingchelada", 40}
};

cuenta cuentas[100]; // Array con las cuentas del bar

mesa mesas[20]; // Array con las mesas del bar


int main(){ //--------------------------------------------------------
	unsigned int mainOpc = 500;

	for(unsigned int i = 0; i < sizeof(cuentas) / sizeof(cuentas[0]); i++){
		cuentas[i].id = i + 1; // Asigna un id a cada cuenta
		cuentas[i].used = false; // Indica que la cuenta nunca ha sido utilizada
	}

	for(unsigned int i = 0; i < sizeof(mesas) / sizeof(mesas[0]); i++){
		mesas[i].numMesa = i + 1; // Asigna un id a cada mesa
		mesas[i].mesaCuenta = NULL; // Inicializa el puntero como NULL
	}

	printf("WELCOME TO IRVING´S BAR ULTIMATE MANAGEMENT SYSTEM");

	while(mainOpc != 0){ // Imprimir menu principal
		system("cls");

		printf("Que deseas administrar?\n\n");
		printf("1) Mesas\n");
		printf("2) Inventario\n");
		printf("3) Empleados\n");
		printf("0) Salir\n");

		scanf("%u", &mainOpc);

		switch(mainOpc){
		case 1:
			system("cls");
			adminMesas();
			break;
		case 2:
			system("cls");
			adminInventario();
			break;
		case 3:
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
	unsigned int mesaOpc, meseroOpc;
	unsigned int modificarOpc = 500;

	system("cls");

	printMesas(defaultParameter);

	printf("\nIndique la mesa a administrar\n");
	scanf("%u", &mesaOpc);

	if(mesaOpc > 0 && mesaOpc <= sizeof(mesas) / sizeof(mesas[0])){ // Si la mesa existe
		for(unsigned int i = 0; i < sizeof(mesas) / sizeof(mesas[0]); i++){
			if(mesas[i].numMesa == mesaOpc){ // Solo si el numero de mesa es igual a mesaOpc;
				while(modificarOpc != 0){
					system("cls");

					printf("Que deseas modificar de la mesa %u?\n\n", mesas[i].numMesa + 1);

					printMesas(mesaOpc - 1);

					printf("\n1) Abrir cuenta\n");
					printf("2) Cambiar Mesero\n");
					printf("3) Modificar la cuenta\n");
					printf("0) Regresar\n");

					scanf("%u", &modificarOpc);

					switch(modificarOpc){
					case 1:
						if(mesas[mesaOpc - 1].mesaCuenta == NULL){ // Verifica que no tenga asignada una mesa
							system("cls");

							printEmpleados(1);

							printf("\nIngresa el mesero a cargo de la mesa: %u\n", mesas[i].numMesa);
							scanf("%u", &meseroOpc);

							if(buscarEmpleado(meseroOpc)){ // Verificar si el ID del mesero existe
								for(unsigned int j = 0; j < sizeof(empleados) / sizeof(empleados[1]); j++){
									if(empleados[j].id == meseroOpc){
										mesas[i].mesaMesero = empleados[j];
									}
								}
								cuentaAutomatica(mesaOpc - 1);
							} else{
								printf("-----Ingrese un mesero registrado-----\n\nPresione enter para continuar\n");
								clean();
								getchar();
							}

							system("cls");
						} else{
							printf("-----Esta mesa ya tiene una cuenta abierta-----\n\nPresione enter para continuar\n");
							clean();
							getchar();
						}
						break;

					case 2:
						if(mesas[i].mesaCuenta != NULL){
							system("cls");

							printEmpleados(1);

							printf("\nIngresa el mesero a cargo de la mesa: %u\n", mesas[i].numMesa);
							scanf("%u", &meseroOpc);

							if(buscarEmpleado(meseroOpc)){ // Verificar si el ID del mesero existe
								for(unsigned int j = 0; j < sizeof(empleados) / sizeof(empleados[1]); j++){
									if(empleados[j].id == meseroOpc){
										mesas[i].mesaMesero = empleados[j];
									}
								}
							} else{
								printf("-----Ingrese un mesero registrado-----\n\nPresione enter para continuar\n");
								clean();
								getchar();
							}
						} else{
							printf("-----Primero debe abrir una cuenta-----\n\nPresione enter para continuar\n");
							clean();
							getchar();
						}

						system("cls");
						break;

					case 3:
						if(mesas[i].mesaCuenta != NULL){ // Verifica que ya se haya asignado una cuenta a la mesa
							adminCuenta(mesaOpc - 1);

						} else{
							printf("-----Primero debe abrir una cuenta-----\n\nPresione enter para continuar\n");
							clean();
							getchar();
						}
						break;

					default:
						break;
					}
				}
			}
		}
	} else{
		printf("-----Ingrese una mesa registrada-----\n\nPresione enter para continuar\n");
		clean();
		getchar();
	}
}

void adminInventario(){ // Menu administración de inventario
	unsigned int adminInventarioOpc;

	while(adminInventarioOpc != 0){
		system("cls");

		printProductos(defaultParameter);

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
		system("cls");

		printEmpleados(defaultParameter);

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

void adminCuenta(unsigned int mesaOpc){ // Menu administración de cuentas
	unsigned int productoCuentaOpc, modificarCuentaOpc = 500;
	int countCuentaProductos = 0, respuesta;
	float totalCuenta = 0.0;

	for(int i = 0; i < 100; i++){
		if(mesas[mesaOpc].mesaCuenta->cuentaProductos[i].alta){
			countCuentaProductos++; // Almacena cuantos productos tiene la cuenta de la mesa
		}
	}

	while(modificarCuentaOpc != 0){
		system("cls");

		printf("Que deseas modificar a la cuenta de la mesa %u?\n\n", mesaOpc + 1);
		printf("1) Agregar producto\n");
		printf("2) Cobrar la cuenta\n");
		printf("0) Regresar\n");

		scanf("%u", &modificarCuentaOpc);

		switch(modificarCuentaOpc){
		case 1:
			system("cls");

			printProductos(1);

			printf("\nQue producto desea agregar a la cuenta de la mesa %d?\n", mesas[mesaOpc].numMesa);
			scanf("%d", &productoCuentaOpc);

			if(buscarProducto(productoCuentaOpc)){ // Si el producto existe
				printf("%s", productos[productoCuentaOpc - 1].nombre);
				mesas[mesaOpc].mesaCuenta->cuentaProductos[countCuentaProductos + 1] = productos[productoCuentaOpc - 1];

				//system("cls");

				printf("%s fue agregado a la cuenta\n\n", mesas[mesaOpc].mesaCuenta->cuentaProductos[countCuentaProductos + 1].nombre);

				countCuentaProductos++;

				printProductosCuenta(mesaOpc, defaultParameter);

				printf("\nPresione enter para continuar\n");
				clean();
				getchar();
			} else{
				printf("-----Ingrese una producto registrado-----\n\nPresione enter para continuar\n");
				clean();
				getchar();
			}
			break;

		case 2:
			system("cls");

			printf("El total de los productos de la cuenta de la mesa %d es:\n\n", mesaOpc + 1);

			printProductosCuenta(mesaOpc, 1);

			for(int j = 0; j < 100; j++){
				if(mesas[mesaOpc].mesaCuenta->cuentaProductos[j].alta){
					totalCuenta = totalCuenta + mesas[mesaOpc].mesaCuenta->cuentaProductos[j].precio;
				}
			}

			printf("\nTOTAL: %.2f\n\n", totalCuenta);

			while(respuesta != 1){
				printf("Haz recibido el pago? (1=Si 2=No)\n");
				scanf("%d", &respuesta);

				if(respuesta == 1){
					strcpy(mesas[mesaOpc].mesaMesero.nombre, "N/A");

					mesas[mesaOpc].mesaCuenta = NULL;

					printf("\nLa cuenta ha sido cerrada\n");
				} else{
					printf("\nCobra al cliente la cantidad de: %.2f para cerrar la cuenta\n\n", totalCuenta);
				}
			}
			printf("\nPresiona enter para continuar\n");
			clean();
			getchar();
			return;
		}
	}
}

//--------------------------------------------------------------------

void altaProducto(){ // Da de alta un nuevo produto
	system("cls");

	printProductos(defaultParameter);

	printf("\nIngresa el nombre del producto a dar de alta: ");
	scanf("%s", productos[numProductosIdUsados].nombre);

	printf("Ingresa el precio del producto a dar de alta: ");
	scanf("%f", &productos[numProductosIdUsados].precio);

	productos[numProductosIdUsados].alta = true;
	productos[numProductosIdUsados].id = numProductosIdUsados + 1;
}

void modificacionProducto(){ // Modifica las propiedades de los productos
	unsigned int numeroProductoOpc, modificarOpc;

	system("cls");

	printProductos(defaultParameter);

	printf("\nIngresa el numero de producto a modificar: \n");
	scanf("%u", &numeroProductoOpc);

	if(buscarProducto(numeroProductoOpc)){ // Si el producto esta dado de alta
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

						printProductos(defaultParameter);
						break;

					case 2:
						printf("\nIngresa el nuevo precio de: %s\n", productos[i].nombre);
						scanf("%f", &productos[i].precio);

						system("cls");

						printProductos(defaultParameter);
						break;

					default:
						break;
					}
				}
			}
		}
	} else{
		printf("\n-----Ingrese un producto registrado-----\n\nPresione enter para continuar\n");
		clean();
		getchar();
	}
}

void bajaProducto(){ // Da de baja logica a productos
	unsigned int numeroProductoOpc;

	system("cls");

	printProductos(defaultParameter);

	printf("\nIngresa el numero de producto a dar de baja: \n");
	scanf("%u", &numeroProductoOpc);

	if(buscarProducto(numeroProductoOpc)){
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

	printEmpleados(defaultParameter);

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

	printEmpleados(defaultParameter);

	printf("\nIngresa el numero de empleado del empleado a modificar: \n");
	scanf("%u", &numeroEmpleadoOpc);


	if(buscarEmpleado(numeroEmpleadoOpc)){ // Si el empleado esta dado de alta
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
						printEmpleados(defaultParameter);
						break;

					case 2:
						printf("\nIngresa la nueva edad del empleado: %s\n", empleados[i].nombre);
						scanf("%u", &empleados[i].edad);
						system("cls");
						printEmpleados(defaultParameter);
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
						printEmpleados(defaultParameter);
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
						printEmpleados(defaultParameter);
						break;

					default:
						break;
					}
				}
			}
		}
	} else{
		printf("-----Ingrese un empleado registrado-----\n\nPresione enter para continuar\n");
		clean();
		getchar();
	}
}

void bajaEmpleado(){ // Da de baja logica a empleados
	unsigned int numeroEmpleadoOpc;

	system("cls");

	printEmpleados(defaultParameter);

	printf("\nIngresa el numero de empleado a dar de baja: \n");
	scanf("%u", &numeroEmpleadoOpc);

	if(buscarEmpleado(numeroEmpleadoOpc)){ // Solo si esta dado de alta
		for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){
			if(empleados[i].id == numeroEmpleadoOpc){
				empleados[i].alta = false;
			}
		}
	}
}

// Funciones terciarias-----------------------------------------------

void printMesas(int mesaParametro){ // Imprime las mesas activas
	printf(" # MESA |     MESERO | CUENTA |\n");

	if(mesaParametro == 500){

		for(unsigned int i = 0; i < sizeof(mesas) / sizeof(mesas[0]); i++){

			if(mesas[i].numMesa != 0){
				printf("%7u |%11s |", mesas[i].numMesa, mesas[i].mesaMesero.nombre);

				if(mesas[i].mesaCuenta != NULL){
					printf("%7u |\n", mesas[i].mesaCuenta->id);
				} else{
					printf("    N/A |\n");
				}
			}
		}
	} else{
		if(mesas[mesaParametro].numMesa != 0){
			printf("%7u |%11s |", mesas[mesaParametro].numMesa, mesas[mesaParametro].mesaMesero.nombre);

			if(mesas[mesaParametro].mesaCuenta != NULL){
				printf("%7u |\n", mesas[mesaParametro].mesaCuenta->id);
			} else{
				printf("    N/A |\n");
			}
		}
	}
}

void printEmpleados(int empleadosParametro){ // Imprime los empleados dados de alta como tabla
	numEmpleadosRegistrados();
	if(empleadosParametro == 500){
		printf("Hay %u empleados dados de alta en este momento\n\n", numEmpleadosAlta);

		printf("TURNO: Matutino = 1 / Vespertino = 2 / Nocturno = 3\n\nPUESTO: Mesero = 1 / Cocinero = 2 / Gerente = 3 / Bartender = 4\n\n");

		printf(" ID |     NOMBRE |     EDAD |     TURNO |     PUESTO |\n");
		for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){

			if(empleados[i].alta){
				printf("%3u | %10s |%9u |%10u |%11u |\n", empleados[i].id, empleados[i].nombre, empleados[i].edad, empleados[i].turno, empleados[i].puesto);
			}
		}
	} else{
		printf(" ID |     NOMBRE |\n");

		for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){

			if(empleados[i].alta){
				printf("%3u | %10s |\n", empleados[i].id, empleados[i].nombre);
			}
		}
	}
}

void printProductos(int productosParametro){ // Imprime los productos dados de alta como tabla
	numProductosRegistrados();
	if(productosParametro == 500){
		printf("El numero de productos registrados es: %u\n\n", numProductosAlta);

		printf(" ID |      NOMBRE |  PRECIO |\n");
		for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[0]); i++){

			if(productos[i].alta){
				printf("%3u |%12s | %7.2f |\n", productos[i].id, productos[i].nombre, productos[i].precio);
			}
		}
	} else{
		printf(" ID |      NOMBRE |  PRECIO |\n");
		for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[0]); i++){
			if(productos[i].alta){
				printf("%3u |%12s | %7.2f |\n", productos[i].id, productos[i].nombre, productos[i].precio);
			}
		}
	}
}

void printProductosCuenta(int productosCuentaParametro, int productosCuentaParametro2){ // Imprime los productos que ya fueron asignados a una cuenta de una mesa
	if(productosCuentaParametro2 == 500){
		printf(" ID |            Nombre |\n");

		for(unsigned int i = 0; i < 100; i++){

			if(mesas[productosCuentaParametro].mesaCuenta->cuentaProductos[i].alta){
				printf("%3d |%18s |\n", i, mesas[productosCuentaParametro].mesaCuenta->cuentaProductos[i].nombre);
			}
		}
	} else{
		printf(" ID |            Nombre |     PRECIO |\n");

		for(unsigned int i = 0; i < 100; i++){

			if(mesas[productosCuentaParametro].mesaCuenta->cuentaProductos[i].alta){
				printf("%3d |%18s |%11.2f |\n", i, mesas[productosCuentaParametro].mesaCuenta->cuentaProductos[i].nombre, mesas[productosCuentaParametro].mesaCuenta->cuentaProductos[i].precio);
			}
		}
	}
}

//--------------------------------------------------------------------

bool buscarCuenta(unsigned int numCuenta){ // Busca si el numero de cuenta existe
	for(unsigned int i = 0; i < sizeof(cuentas) / sizeof(cuentas[0]); i++){

		if(cuentas[i].id == numCuenta){
			return true;
		}
	}
	return false;
}

int buscarCuentaLibre(){ // Busca una cuenta que no haya sido utilizada
	for(unsigned int j = 0; j < sizeof(cuentas) / sizeof(cuentas[0]); j++){

		if(!cuentas[j].used){
			return j;
		}
	}
	return -1;
}

bool buscarEmpleado(unsigned int numEmpleado){ // Busca si un empleado esta dado de alta segun su numero de empleado
	for(unsigned int i = 0; i < sizeof(empleados) / sizeof(empleados[0]); i++){

		if(empleados[i].id == numEmpleado && empleados[i].alta){
			return true;
		}
	}
	return false;
}

bool buscarProducto(unsigned int numProd){ // Busca si un producto esta dado de alta segun su numero de empleado
	for(unsigned int i = 0; i < sizeof(productos) / sizeof(productos[0]); i++){

		if(productos[i].id == numProd && productos[i].alta){
			return true;
		}
	}
	return false;
}

//--------------------------------------------------------------------

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

//--------------------------------------------------------------------

void cuentaAutomatica(unsigned int modificar){ //Asigna automaticamente una cuenta no utilizada anteriormente a la mesa
	int cuentaLibre;
	cuentaLibre = buscarCuentaLibre();

	if(cuentaLibre != -1){
		mesas[modificar].mesaCuenta = &cuentas[cuentaLibre];

		cuentas[cuentaLibre].used = true;
	}
}

void clean(){ // Limpia el buffer de la entrada estandar (teclado)
	while(getchar() != '\n'); // Cada getchar elimina un caracter del buffer
}