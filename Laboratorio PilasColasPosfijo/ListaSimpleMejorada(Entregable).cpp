#include "pch.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

using namespace std;


typedef struct TArticulo 
{
	int Codigo;
	char Nombre[20]; 
	int Disponible; 
	float Precio; 
	TArticulo *Siguiente; 
}*PtrTArticulo; 


//******************************************

int i;  //parametro global


void InicializarInventario(PtrTArticulo &Lista)
{
	Lista = NULL;
}

// Función que me limpia el Parametro lsita , este es  por referencia
void DestruirInventario(PtrTArticulo &Lista)
{
	PtrTArticulo Aux; // Puntero que apuntara al primer dato de la lista
	Aux = Lista; // Aux toma el valor de lista
	while (Aux != NULL) // Mientras Aux no termine de leer toda la lista.
	{
		Lista = Lista->Siguiente; // Lista apuntara al siguiente valor de la lista
		delete(Aux); // Borra el valor de Aux
		Aux = Lista; // Aux toma el valor de lista el cual apuntara  al siguiente valor para que continue su recorrido
	}
}

// Funcion para agregar nuevo articulo 
PtrTArticulo CrearArticulo(int NCodigo, int NDisponible, float NPrecio)
{
	PtrTArticulo Pieza = new(TArticulo); // Solicita un Nuevo espacio  en Memoria para ser asignado a un nuevo articulo
	char buffer[5];

	Pieza->Codigo = NCodigo; //Asignacion del codigo solicitado por Usuario al Tipo Codigo dentro del struct
	Pieza->Disponible = NDisponible; // Asignacion de la disponiblidad solicitada por Usuario al Tipo Disponible dentro del struct
	Pieza->Precio = NPrecio; // Asignacion del precio solicitado por Usuario al Tipo Precio dentro del struct

	strcpy_s(Pieza->Nombre, "Pieza"); // Agrega el Nombre al  string Pieza
	_itoa_s(NCodigo, buffer, 10); // Convierte el codigo a string, y lo almacena como un float 
	strcat_s(Pieza->Nombre, buffer); // Concatena strings, al nombre se le agrega  el codigo almacenado

	Pieza->Siguiente = NULL; //Al puntero se le asigna el valor NULL
	return Pieza; // Regresa los datos de la Pieza añadida
}

// Funcionque agrega cada articulo nuevo al inicio de lista
void AgregarInicioInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo)
{
	Nuevo->Siguiente = Lista; // Al puntero siguiente del nuevo articulo, se  le asigna la direccion al inicio de la lista
	Lista = Nuevo; // La direccion de la lista se enlaza al nuevo articulo
}




// Funcion para agregar los articulos al final de la lista 
void AgregarFinalInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo)
{
	PtrTArticulo Aux; // Declaracion del puntero Aux a PtrTArticulo
	Aux = Lista; // Aux almacena la direccion del primer miembro de la lista
	if (Aux != NULL) //Condicional que se cumple si Aux aun no Termina la lista
	{
		while (Aux->Siguiente != NULL) // Mientras el puntero almacenado en Siguiente no sea NULL
		{
			Aux = Aux->Siguiente; // Aux toma la direccion  del siguiente miembro de la lista
		}

		Aux->Siguiente = Nuevo;
	}
	else // Si se llega al final de la lista
	{
		Lista = Nuevo;
	}
}



// Funcion para imprimir lista en pantalla
void ListarInventario(PtrTArticulo &Lista)
{
	int Contador = 1; // Inicio de contador
	PtrTArticulo Aux; // Se declara Aux  a PtrTArticulo
	Aux = Lista; // Aux almacena la direccion  de la lista
	while (Aux != NULL) // Mientras no se llegue al final de la lista
	{
		printf(" %d ", Contador); // Imprime el contador
		printf("%d ", Aux->Codigo); // Imprime el codigo
		printf("%s ", Aux->Nombre); // Imprime el nombre
		printf(" %d ", Aux->Disponible); // Imprime la cantidad disponible
		printf(" %f\n ", Aux->Precio); // Imprime el precio del producto
		Aux = Aux->Siguiente; // Aux almacena la direccion en memoria del siguiente articulo
		Contador++; // Incremento del contador
	}
}

// Funcion para buscar articulos en la lista

PtrTArticulo BuscarArticulo(PtrTArticulo &Lista, int cual)
{
	bool encontro = false; // Declaracion de variable tipo booleana
	PtrTArticulo Aux; // Declaracion de puntero Aux a PtrTArticulo
	Aux = Lista; // Se le asigna a Aux la direccion de Lista

	while ((!encontro == true) && (Aux != NULL)) // Mientras que encontro sea falso
	{
		if (Aux->Codigo == cual) // Si el codigo del producto es igual al buscado
		{
			encontro = true; // Se asigna encontro como verdadero
		}
		else // Si el codigo no es igual al buscado
		{
			Aux = Aux->Siguiente; // Aux apunta al siguiente producto en la lista
		}
	}
	return Aux; // Se regresa la direccion en memoria del producto encontrado
}

// Funcion para guardar la lista en memoria secundaria como archivo de texto
void GuardarInventario(PtrTArticulo Lista)
{
	FILE *archivo; // Puntero a archivo que almacena la direccion en memoria donde se guarda el archivo
	fopen_s(&archivo, "ARCHIVO.txt", "w+"); // Copia la informacion del archivo y lo almacena en la memoria como archivo logico
	if (NULL == archivo) // Si la direccion en memoria es igual a NULL, el archivo no fue encontrado
	{
		printf("No se pudo abrir el archivo."); // Imprime un mensaje de error
	}
	else // Si encontro el archivo
	{
		PtrTArticulo AUX = Lista; // Aux almacena la direccion del comienzo de la lista
		while (AUX != NULL) // Mientras no se llega al final de la lista
		{
			fprintf(archivo, "%i\n", AUX->Codigo); // Escribe en el archivo logico el codigo de cada producto del arreglo
			fprintf(archivo, "%s\n", AUX->Nombre); // Escribe en el archivo logico el nombre de cada producto del arreglo
			fprintf(archivo, "%i\n", AUX->Disponible); // Escribe en el archivo logico la cantidad disponible de cada producto del arreglo
			fprintf(archivo, "%f\n", AUX->Precio); // Escribe en el archivo logico el precio de cada producto del arreglo
			AUX = AUX->Siguiente; // Aux apunta al siguiente miembro de la lista
		}
	}
	fclose(archivo); // Como el archivo se cargo en modo de escritura, entonces sobreescribe la informacion al archivo de texto
}

// Funcion para cargar la informacion almacenada del almacenamiento a archivo logico
void CargarInventario(PtrTArticulo &Lista)
{
	PtrTArticulo Nuevo; // Se declara un puntero a PtrTArticulo
	FILE *archivo; // Se almacena la direccion del archivo de texto
	fopen_s(&archivo, "ARCHIVO.txt", "r"); // Se carga la informacion del archivo de texto en la memoria RAM
	if (NULL == archivo) // Si no encuentra el archivo en la memoria 
	{
		printf("No se pudo abrir el archivo"); // imprime un mensaje de error
	}
	else // Si lo encuentra
	{
		while (!feof(archivo)) // Mientras no se llegue al final del archivo en la memoria
		{
			Nuevo = new(TArticulo); // Nuevo solicita un nuevo espacio en la memoria
			char Cadena[20]; // Declaracion de variable tipo caracter
			fscanf_s(archivo, "%i\n", &Nuevo->Codigo); // Lee el codigo del producto y lo almacena en la memoria
			fscanf_s(archivo, "%s\n", Cadena, 20); // Añade el string cadena a la memoria
			fscanf_s(archivo, "%i\n", &Nuevo->Disponible); // Lee la cantidad disponible del producto y lo almacena en la memoria
			fscanf_s(archivo, "%f\n", &Nuevo->Precio); // Lee el precio del producto y lo almacena en la memoria
			strcpy_s(Nuevo->Nombre, Cadena); // Al Nombre del producto le añade el string Cadena
			Nuevo->Siguiente = NULL; // Al puntero Siguiente en Nuevo, lo define como NULL
			AgregarFinalInventario(Lista, Nuevo); // Llama esta funcion para agregar cada articulo al final de la lista
		}
	}
	fclose(archivo); // Como el archivo se cargo en modo de lectura, la informacion de la memoria se borra y no escribe en el archivo
}

// Funcion para borrar un articulo de la lista
bool BorrarArticulo(PtrTArticulo &Lista, int cual) {
	PtrTArticulo Aux; // Puntero Auxiliar
	PtrTArticulo kill; // Puntero encargado de eliminar el articulo
	bool encontrado = false; // Booleano que indica si se encuentra el articulo
	Aux = Lista;
	kill = Lista;

	if (Lista == NULL) { // Lista Vacia
		cout << "La lista esta vacia" << endl;

	}
	else if (Aux->Siguiente == NULL) { // Si la lista solo tiene un articulo
		if (Aux->Codigo == cual) { // Si el articulo es el que se va a borrar
			Aux = NULL; // Aux apunta a NULL, por lo tanto la lista queda en NULL
			delete(kill); // Se elimina el articulo
			cout << "El articulo " << cual << " fue borrado" << endl;
			cout << "La lista ahora esta vacia" << endl;
			encontrado = true; // Se define encontrado como true

		}
		else { // Si el articulo no es el que se busca
			cout << "El articulo no esta en la lista de un solo elemento" << endl;
			encontrado = false; // No se encontro el articulo
		}
	}
	else { // Lista con varios articulos
		while (!encontrado == true) {
			if (kill->Codigo == cual) { // Si se encuentra el articulo
				encontrado = true; // encontrado se le asigna a true para finalizar el ciclo
				Aux->Siguiente = kill->Siguiente; // El puntero siguiente en Aux apunta al puntero siguiente en kill para eliminar el puntero kill de la lista
				delete(kill); // Se elimina el articulo
				cout << "Articulo Borrado!!!!!!!" << endl;

			}
			else if (kill->Siguiente == NULL) { // Si no econtro el articulo
				cout << "El articulo no se encuentra en la lista" << endl;
				encontrado = false; // encontrado sigue siendo falso
			}
			else { // Mientras no encuentre el articulo en la lista
				Aux = kill;
				kill = kill->Siguiente; // kill apunta al siguiente articulo
			}
		}
	}
	return encontrado;
}

// Funcion para invertir lista usando 2 listas
PtrTArticulo Invertir2Listas(PtrTArticulo &Lista) {
	PtrTArticulo Nuevo; // Puntero para crear un nuevo articulo con los datos de Aux
	PtrTArticulo Aux = Lista; // Aux se inicia en Lista
	PtrTArticulo Lista2; // Puntero para una segunda lista
	InicializarInventario(Lista2); // Se inicia la segunda lista

	if (Aux == NULL) { // Si la lista esta vacia
		printf("0 articulos en lista\n");
		Lista2 = Lista;
	}

	else if (Aux->Siguiente == NULL) { // Si solamente hay un articulo en la lista
		cout << "La lista 1 solamente tiene un elemento" << endl;
		Lista2 = Lista;
	}

	else {
		while (Aux != NULL) { // Si en la lista hay minimo 2 articulos
			Nuevo = CrearArticulo(Aux->Codigo, Aux->Disponible, Aux->Precio); // Se crea un nuevo articulo con los datos de Aux
			AgregarInicioInventario(Lista2, Nuevo); // Se agrega el articulo al inicio de la segunda lista
			Aux = Aux->Siguiente; // Aux apunta al siguiente articulo
		}
	}
	return Lista2;
}//en general lo que hace es que aux recorre la lista y la guarda en una segunda  invertiendola

// Funcion para invertir una lista usando una lista
PtrTArticulo Invertir1Lista(PtrTArticulo &Lista) {
	PtrTArticulo Aux; // Aux se uutiliza para crear articulos y despues  se borra
	PtrTArticulo Siguiente; // Siguiente se usa para poder sacar Aux de la lista
	PtrTArticulo Primero; // Primero siempre mantiene la direccion del primer articulo de la lista
	PtrTArticulo Nuevo; // Crea un articulo con los datos de Aux

	Primero = Lista; // Primero se iguala al comienzo de la lista, que sera el mismo hasta el ultimo articulo

	if (Primero == NULL) { // Lista vacia
		cout << "La lista esta vacia" << endl;
	}
	else if (Primero->Siguiente == NULL) { // Lista con un articulo
		cout << "La lista solo tiene un elemento" << endl;
	}
	else { // Lista con dos articulos o mas
		Aux = Primero->Siguiente; // Aux toma el valor del segundo en la lista
		Siguiente = Aux->Siguiente;// Siguiente toma el valor del tercero en la lista
		while (Siguiente != NULL) { // Mientras haya tres articulos como minimo
			Primero->Siguiente = Siguiente; // El puntero siguiente en primero apunta al tercer articulo para eliminar Aux de la lista
			Nuevo = CrearArticulo(Aux->Codigo, Aux->Disponible, Aux->Precio); // Se crea el articulo con los datos de Aux
			delete(Aux); // Se elimina Aux
			AgregarInicioInventario(Lista, Nuevo); // Se añade Nuevo al inicio de la lista
			Aux = Primero->Siguiente;
			Siguiente = Aux->Siguiente;
		}
		// Cuando el ciclo deja al final de la lista al primer elemento y el ultimo de la lista inicial solamente
		Siguiente = Primero->Siguiente; // Siguiente toma el valor del ultimo de la lista
		Nuevo = CrearArticulo(Siguiente->Codigo, Siguiente->Disponible, Siguiente->Precio); // Se crea el articulo con los datos de siguiente
		Primero->Siguiente = NULL; // El puntero siguiente en primero apunta a NULL
		AgregarInicioInventario(Lista, Nuevo); // Se agrega el articulo creado al inicio
		// En este Momento el ultimo en la lista original  es el primero
		Lista = Nuevo; // Lista apunta a Nuevo
	}
	return Lista; // Retorna la lista
}//en General lo que hace es tomar todos los valores  de nuevo y agregarlos de nuvo  y borrar los datos viejos par asi Inertir la lista

// Funcion para imprimir solo los articulos impares de la lista
PtrTArticulo ImprimirImpares(PtrTArticulo &Lista) {
	PtrTArticulo Aux = Lista; // Puntero Auxiliar
	PtrTArticulo ListaImpares; // Puntero para almacenar la nueva lista
	PtrTArticulo Nuevo; // Puntero para nuevo articulo
	InicializarInventario(ListaImpares); // Se inicializa la lista

	while (Aux != NULL) { // Mientras no llegue al final de la lista
		if ((Aux->Codigo % 2) != 0) { // Si el residuo del codigo dividido entre dos es distinto de 0 (Es impar)
			Nuevo = CrearArticulo(Aux->Codigo, Aux->Disponible, Aux->Precio); // Se copian los datos de Aux en Nuevo
			AgregarFinalInventario(ListaImpares, Nuevo); // Se agrega Nuevo al final
			Aux = Aux->Siguiente; // Aux apunta a siguiente
		}
		else { // Si es par
			Aux = Aux->Siguiente; // Aux apunta al siguiente
		}
	}
	return ListaImpares;
}


// Funcion principal
void main(int argc, char* argv[])
{
	//************************************************************************
	// Declaracion de punteros a PtrTArticulo
	PtrTArticulo Llantas;
	PtrTArticulo Abarrotes;
	PtrTArticulo Nuevo;
	PtrTArticulo AbarrotesInvertida;
	bool borrar;

	// ************************* Borrar Articulos ******************************

	system("CLS");
	printf("*************** Uso de la funcion BorrarArticulo ******************* \n\n");
	// Busqueda con lista vacia
	printf("---Borrar articulo de codigo 4 de la lista llantas vacia---\n");
	InicializarInventario(Llantas);
	borrar = BorrarArticulo(Llantas, 4);
	if (borrar == true) {
		cout << "El articulo fue borrado" << endl;
	}
	else {
		cout << "El articulo no fue borrado" << endl;
	}

	// Busqueda con lista con un solo articulo
	printf("---Borrar articulo de codigo 4 de la lista llantas con un articulo---\n");
	Nuevo = CrearArticulo(1, 1, 1);
	AgregarFinalInventario(Llantas, Nuevo);
	borrar = BorrarArticulo(Llantas, 4);
	if (borrar == true) {
		cout << "El articulo fue borrado" << endl;
	}
	else {
		cout << "El articulo no fue borrado" << endl;
	}

	printf("---Borrar articulo de codigo 1 de la lista llantas con un articulo---\n");
	BorrarArticulo(Llantas, 1);

	// Busqueda con lista con varios articulos
	InicializarInventario(Llantas);
	printf("---Borrar articulo de codigo 3 de la lista---\n");
	for (i = 1; i < 11; i++) {
		Nuevo = CrearArticulo(i, i, i);
		AgregarFinalInventario(Llantas, Nuevo);
	}
	ListarInventario(Llantas);
	borrar = BorrarArticulo(Llantas, 3);
	if (borrar == true) {
		cout << "El articulo fue borrado" << endl;
	}
	else {
		cout << "El articulo no fue borrado" << endl;
	}
	ListarInventario(Llantas);
	system("pause");

	// ******************* Inversion con dos listas *************************

	system("CLS");
	InicializarInventario(Abarrotes);
	printf("*************** Uso de la funcion Invertir2Listas *****************\n\n");

	printf("---Invertir una lista sin articulos---\n");
	AbarrotesInvertida = Invertir2Listas(Abarrotes);
	ListarInventario(AbarrotesInvertida);
	DestruirInventario(AbarrotesInvertida);
	// *****************************************************************************
	printf("---Invertir una lista con un solo articulo---\n");
	Nuevo = CrearArticulo(1, 1, 1);
	AgregarFinalInventario(Abarrotes, Nuevo);
	ListarInventario(Abarrotes);
	AbarrotesInvertida = Invertir2Listas(Abarrotes);
	// ******************************************************************************
	cout << "---Invertir lista con varios articulos---" << endl << endl;
	for (i = 2; i < 11; i++) {
		Nuevo = CrearArticulo(i, i, i);
		AgregarFinalInventario(Abarrotes, Nuevo);
	}
	cout << "Lista sin invertir" << endl;
	ListarInventario(Abarrotes);
	cout << endl << "Lista invertida" << endl;
	AbarrotesInvertida = Invertir2Listas(Abarrotes);
	ListarInventario(AbarrotesInvertida);
	DestruirInventario(Abarrotes);
	DestruirInventario(AbarrotesInvertida);


	// ******************* Inversion con una lista ************************
	system("CLS");
	printf("*************** Uso de la funcion Invertir1Lista ***************** \n\n");
	InicializarInventario(Abarrotes);

	printf("---Invertir lista vacia ---\n");
	AbarrotesInvertida = Invertir1Lista(Abarrotes);
	/**/
	printf("\n---Invertir lista con un elemento ---\n");
	Nuevo = CrearArticulo(1, 1, 1);
	AgregarFinalInventario(Abarrotes, Nuevo);
	AbarrotesInvertida = Invertir1Lista(Abarrotes);
	/**/
	printf("\n---Invertir lista con dos elementos---\n");
	Nuevo = CrearArticulo(2, 2, 2);
	AgregarFinalInventario(Abarrotes, Nuevo);
	printf("Lista sin invertir\n");
	ListarInventario(Abarrotes);
	AbarrotesInvertida = Invertir1Lista(Abarrotes);
	printf("Lista invertida\n");
	ListarInventario(AbarrotesInvertida);
	DestruirInventario(Abarrotes);
	/**/
	printf("\---Uso de la funcion con varios elementos en la lista---\n");
	InicializarInventario(Abarrotes);
	InicializarInventario(AbarrotesInvertida);
	for (i = 1; i < 11; i++) {
		Nuevo = CrearArticulo(i, i, i);
		AgregarFinalInventario(Abarrotes, Nuevo);
	}
	printf("\nLista sin invertir\n");
	ListarInventario(Abarrotes);
	AbarrotesInvertida = Invertir1Lista(Abarrotes);
	printf("\nLista Invertida\n");
	ListarInventario(AbarrotesInvertida);
	system("pause");
	DestruirInventario(Abarrotes);

	// ********************** Impresion de Impares ************************
	system("CLS");
	printf("\---Uso de la funcion imprimir lista de impares---\n\n");
	PtrTArticulo ListaImpares;
	InicializarInventario(Abarrotes);
	for (i = 1; i < 20; i++) {
		Nuevo = CrearArticulo(i, i, i);
		AgregarFinalInventario(Abarrotes, Nuevo);
	}
	printf("---Lista Abarrotes completa---\n");
	ListarInventario(Abarrotes);
	printf("\n---Lista de impares---\n");
	ListaImpares = ImprimirImpares(Abarrotes);
	ListarInventario(ListaImpares);
	system("pause");

}

// *******************Borrando Articulo ******************************
/*
*************** Uso de la funcion BorrarArticulo *******************

---Borrar articulo de codigo 4 de la lista llantas vacia---
La lista esta vacia
El articulo no fue borrado

---Borrar articulo de codigo 4 de la lista llantas con un articulo---
El articulo no esta en la lista de un solo elemento
El articulo no fue borrado

---Borrar articulo de codigo 1 de la lista llantas con un articulo---
El articulo 1 fue borrado
La lista ahora esta vacia

---Borrar articulo de codigo 3 de la lista---
1 1 Pieza1  1  1.000000
2 2 Pieza2  2  2.000000
3 3 Pieza3  3  3.000000
4 4 Pieza4  4  4.000000
5 5 Pieza5  5  5.000000
6 6 Pieza6  6  6.000000
7 7 Pieza7  7  7.000000
8 8 Pieza8  8  8.000000
9 9 Pieza9  9  9.000000
10 10 Pieza10  10  10.000000
Articulo Borrado!!!!!!!
El articulo fue borrado
1 1 Pieza1  1  1.000000
2 2 Pieza2  2  2.000000
3 4 Pieza4  4  4.000000
4 5 Pieza5  5  5.000000
5 6 Pieza6  6  6.000000
6 7 Pieza7  7  7.000000
7 8 Pieza8  8  8.000000
8 9 Pieza9  9  9.000000
9 10 Pieza10  10  10.000000
*/

// *****************Invertiendo con 2 listas ******************

/*
*************** Uso de la funcion Invertir2Listas *****************

---Invertir una lista sin articulos---
0 articulos en lista
La lista esta vacia

---Invertir una lista con un solo articulo---
1 1 Pieza1  1  1.000000
La lista 1 solamente tiene un elemento

---Invertir lista con varios articulos---

Lista sin invertir
1 1 Pieza1  1  1.000000
2 2 Pieza2  2  2.000000
3 3 Pieza3  3  3.000000
4 4 Pieza4  4  4.000000
5 5 Pieza5  5  5.000000
6 6 Pieza6  6  6.000000
7 7 Pieza7  7  7.000000
8 8 Pieza8  8  8.000000
9 9 Pieza9  9  9.000000
10 10 Pieza10  10  10.000000
Lista invertida
1 10 Pieza10  10  10.000000
2 9 Pieza9  9  9.000000
3 8 Pieza8  8  8.000000
4 7 Pieza7  7  7.000000
5 6 Pieza6  6  6.000000
6 5 Pieza5  5  5.000000
7 4 Pieza4  4  4.000000
8 3 Pieza3  3  3.000000
9 2 Pieza2  2  2.000000
10 1 Pieza1  1  1.000000
*/

// ***************** Invirtendo con una lista ******************
/*
*************** Uso de la funcion Invertir1Lista *****************

---Invertir lista vacia ---
La lista esta vacia

---Invertir lista con un elemento ---
La lista solo tiene un elemento

---Invertir lista con dos elementos---
Lista sin invertir
1 1 Pieza1  1  1.000000
2 2 Pieza2  2  2.000000
Lista invertida
1 2 Pieza2  2  2.000000
2 1 Pieza1  1  1.000000

---Uso de la funcion con varios elementos en la lista---
Lista sin invertir
1 1 Pieza1  1  1.000000
2 2 Pieza2  2  2.000000
3 3 Pieza3  3  3.000000
4 4 Pieza4  4  4.000000
5 5 Pieza5  5  5.000000
6 6 Pieza6  6  6.000000
7 7 Pieza7  7  7.000000
8 8 Pieza8  8  8.000000
9 9 Pieza9  9  9.000000
10 10 Pieza10  10  10.000000
Lista Invertida
1 10 Pieza10  10  10.000000
2 9 Pieza9  9  9.000000
3 8 Pieza8  8  8.000000
4 7 Pieza7  7  7.000000
5 6 Pieza6  6  6.000000
6 5 Pieza5  5  5.000000
7 4 Pieza4  4  4.000000
8 3 Pieza3  3  3.000000
9 2 Pieza2  2  2.000000
10 1 Pieza1  1  1.000000
*/

// ***************** Impares ******************
/*---Uso de la funcion imprimir lista de impares---

---Lista Abarrotes completa---
 1 1 Pieza1  1  1.000000
  2 2 Pieza2  2  2.000000
  3 3 Pieza3  3  3.000000
  4 4 Pieza4  4  4.000000
  5 5 Pieza5  5  5.000000
  6 6 Pieza6  6  6.000000
  7 7 Pieza7  7  7.000000
  8 8 Pieza8  8  8.000000
  9 9 Pieza9  9  9.000000
  10 10 Pieza10  10  10.000000
  11 11 Pieza11  11  11.000000
  12 12 Pieza12  12  12.000000
  13 13 Pieza13  13  13.000000
  14 14 Pieza14  14  14.000000
  15 15 Pieza15  15  15.000000
  16 16 Pieza16  16  16.000000
  17 17 Pieza17  17  17.000000
  18 18 Pieza18  18  18.000000
  19 19 Pieza19  19  19.000000

---Lista de impares---
 1 1 Pieza1  1  1.000000
  2 3 Pieza3  3  3.000000
  3 5 Pieza5  5  5.000000
  4 7 Pieza7  7  7.000000
  5 9 Pieza9  9  9.000000
  6 11 Pieza11  11  11.000000
  7 13 Pieza13  13  13.000000
  8 15 Pieza15  15  15.000000
  9 17 Pieza17  17  17.000000
  10 19 Pieza19  19  19.000000
  */