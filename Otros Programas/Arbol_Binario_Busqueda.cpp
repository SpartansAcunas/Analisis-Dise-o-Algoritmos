// Raizbb.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include "iostream"
#include <stdio.h>

// Nuevo tipo de dato para arboles
typedef struct NodoBB
{
	int llave; // Contiene la llave
	NodoBB * HijoIzquierdo; // Puntero para hijo izquierdo
	NodoBB * HijoDerecho; // Puntero para hijo derecho
}X;

// Funcion para insertar un nuevo nodo
bool Insertar(NodoBB * &Raiz, int cualllave)
{
	if (Raiz == NULL) // Si el puntero es NULL
	{
		Raiz = new(NodoBB); // Solicita un nuevo lugar en memoria
		Raiz->llave = cualllave; // Almacena la llave
		Raiz->HijoIzquierdo = NULL; // Los hijos se inician en NULL
		Raiz->HijoDerecho = NULL;
		return true; // Devuelve true
	}
	else
	{
		// Si el nodo ya existe
		if (cualllave == Raiz->llave) return false; // Regresa falso
		// Si no existe
		else
			// Si la llave es menor a la llave de la raiz
			if (cualllave < Raiz->llave) return Insertar(Raiz->HijoIzquierdo, cualllave); // Llama a la funcion hijo izquierdo
			// Si la llave es mayor
			else return Insertar(Raiz->HijoDerecho, cualllave); // Llama a la funcion hijo derecho
	}
}


// Funcion para eliminar un ArbolBB
void PodarHojas(NodoBB * &Raiz)
{
	if (Raiz != NULL) // Si la raiz es distinta de NULL
	{
		PodarHojas(Raiz->HijoIzquierdo); // Llama a la funcion con hijo izquierdo y derecho
		PodarHojas(Raiz->HijoDerecho);
		printf("Borro : %i \n", Raiz->llave); // Imprime a pantalla que borra el nodo
		delete(Raiz); Raiz = NULL; // Borra la raiz y la asigna en NULL
	}
}

// Funcion para buscar un nodo en un ArbolBB
NodoBB * Buscar(NodoBB * Raiz, int cualllave)
{
	if (Raiz == NULL) // Si raiz es NULL, o el arbol esta vacio o no lo encontro
	{
		return NULL; // Regresa NULL
	}
	else
	{	// Si encuentra la llave
		if (cualllave == Raiz->llave) return Raiz; // Devuelve el nodo solicitado
		else
			// Si la llave es menor a la de la raiz
			if (cualllave < Raiz->llave) return Buscar(Raiz->HijoIzquierdo, cualllave); // Llama a la funcion  hijo izquierdo y lo devuelve
			// Si la llave es menor
			else return Buscar(Raiz->HijoDerecho, cualllave); // Llama a la funcion  hijo derecho y lo devuelve
	}
}

// Funcion para imprimir los nodos de un arbol en PreOrden
void PreOrdenRID(NodoBB * Raiz)
{	// Si la raiz no es NULL
	if (Raiz != NULL)
	{
		printf("%i  ", Raiz->llave); // Imprime la llave
		PreOrdenRID(Raiz->HijoIzquierdo); // Llama a la funcion  hijo izquierdo y lo devuelve
		PreOrdenRID(Raiz->HijoDerecho); // Llama a la funcion  hijo derecho  y lo devuelve
	}
}

// Funcion para imprimir los nodos de un arbol EnOrden
void EnOrdenIRD(NodoBB * Raiz)
{	// Si la raiz no es NULL
	if (Raiz != NULL)
	{
		EnOrdenIRD(Raiz->HijoIzquierdo); // Llamaa la funcion  hijo izquierdo y lo devuelve
		printf("%i  ", Raiz->llave); // Imprime la llave
		EnOrdenIRD(Raiz->HijoDerecho); // Llama a la funcion hijo derecho y lo devuelve
	}
}

// Funcion para imprimir los nodos de un arbol en PosOrden
void PosOrdenIDR(NodoBB * Raiz)
{	// Si la raiz no es NULL
	if (Raiz != NULL)
	{
		PosOrdenIDR(Raiz->HijoIzquierdo); // Llama a la funcion  hijo izquierdo y lo devuelve
		PosOrdenIDR(Raiz->HijoDerecho); // Llama a la funcion  hijo derechoy lo devuelve
		printf("%i  ", Raiz->llave); // Imprime la llave
	}
}

// Funcion para contar
int contar(NodoBB *Raiz) {

	if (Raiz == NULL) // Si el arbol esta vacio o llega a los hijos de una hoja
		return 0; // Devuleve 0

	else // Si hay una raiz
		return (1 + contar(Raiz->HijoIzquierdo) + contar(Raiz->HijoDerecho)); // Suma 1 cada vez que el resultado de la funcion evaluada en los hijos izquierdo y derechocumple el condicional
}

// Función para comparar dos raices
bool compararArboles(NodoBB *Raiz1, NodoBB *Raiz2) {

	// Si la raiz principal de alguno de los arboles es NULL
	if (Raiz1 == NULL || Raiz2 == NULL) { // Si una de las raices es NULL
		if (Raiz1 == NULL && Raiz2 == NULL) return true; // Si las dos raices son NULL, los arboles estan vacios y devuelve true
		else return false; // Si una raiz es NULL y la otra no, devuelve false
	}

	// Si ambos arboles tienen al menos un elemento
	else if (Raiz1->llave != Raiz2->llave) return false; // Si la llave de las raices es distinta, devuelve false

	else /* Si ambas llaves son iguales  retorna verdadero por ser iguales y hace el llamado recursivo con ambos hijos de las 2 raices,
		para que ambos arboles sean iguales, todos los llamados deben devolver true*/
		return (true && compararArboles(Raiz1->HijoIzquierdo, Raiz2->HijoIzquierdo) && compararArboles(Raiz1->HijoDerecho, Raiz2->HijoDerecho));
}

// Funcion para clonar un arbol
NodoBB *clonarArbol(NodoBB *Raiz1, NodoBB *&Raiz2) { // Toma las raices del Raiz1 y las clona en Raiz2
	Raiz2 = NULL; // Inicializa el Arbol 2
	NodoBB *Aux = Raiz1; // Se declara un puntero Auxiliar que sera la raiz durante la recursion

	if (Aux == NULL) { // Si el Arbol esta vacio o se llega a una hoja
		return NULL; // Devuelve NULL para agregar al arbol en el mismo sitio
	}
	else {
		Raiz2 = new(NodoBB); // Se declara la Raiz del segundo arbol como NodoBB
		Raiz2->llave = Aux->llave; // La llave toma el valor del auxiliar

		// Hace un llamado recursivo con los hijos de las raices de ambos arboles
		clonarArbol(Aux->HijoIzquierdo, Raiz2->HijoIzquierdo);
		clonarArbol(Aux->HijoDerecho, Raiz2->HijoDerecho);
		return Raiz2; // Regresa el puntero a Raiz2
	}
}

//Funcion para determinar si un arbol es completo
bool esCompleto(NodoBB *Raiz) {
	// Si la raiz existe
	if (Raiz != NULL) {
		// Si los dos hijos son iguales a NULL o los dos hijos son distintos de NULL
		if (((Raiz->HijoIzquierdo == NULL) && (Raiz->HijoDerecho == NULL)) || ((Raiz->HijoIzquierdo != NULL) && (Raiz->HijoDerecho != NULL))) {
			// Devuelve verdadero y la funcion con hijo izquierdo y con hijo derecho
			// Si algun llamado devuelve false, el resultado es false
			return (true && esCompleto(Raiz->HijoIzquierdo) && esCompleto(Raiz->HijoDerecho));
		}
		// Si existe un nodo con un solo hijo
		else return false; // Devuelve false
	}
}

// Funcion para visualizar las hojas
void visualizarHojas(NodoBB *Raiz) {

	// Si ni la raiz ni los hijos son NULL
	if ((Raiz != NULL) && (Raiz->HijoIzquierdo != NULL) && (Raiz->HijoDerecho != NULL)) {
		visualizarHojas(Raiz->HijoIzquierdo); // Llama la funcion con los hijos izquierdo y derecho
		visualizarHojas(Raiz->HijoDerecho);
	}
	// Si la raiz y el hijo derecho no son NULL pero el izquierdo si
	else if ((Raiz != NULL) && (Raiz->HijoIzquierdo == NULL) && (Raiz->HijoDerecho != NULL)) {
		visualizarHojas(Raiz->HijoDerecho); // Llama a la funcion con el hijo derecho
	}
	// Si la raiz y el hijo izquierdo no son NULL pero el derecho si
	else if ((Raiz != NULL) && (Raiz->HijoDerecho == NULL) && (Raiz->HijoIzquierdo != NULL)) {
		visualizarHojas(Raiz->HijoIzquierdo);// Llama a la funcion con el hijo izquierdo
	}
	else {
		// Si la raiz no es NULL y los hijos si
		if ((Raiz->HijoIzquierdo == NULL) && (Raiz->HijoDerecho == NULL)) {
			printf("%i ", Raiz->llave); // Imprime la llave de la raiz
		}
	}

}

// Funcion para borrar un nodo de un Arbol Binario de Busqueda
void borrarNodo(NodoBB *&Raiz, int cualllave) {

	NodoBB *AuxHI = Raiz->HijoIzquierdo;
	NodoBB *AuxHD = Raiz->HijoDerecho;

	if (Raiz == NULL) { // Si el arbol esta vacio o no encontro la llave
		printf("\nEl arbol no tiene nodos o la llave no esta\n");
	}

	else if ((Raiz->llave == cualllave) && ((Raiz->HijoIzquierdo != NULL) || (Raiz->HijoDerecho != NULL))) {

	}

	else {

		if (cualllave < Raiz->llave) { // Si la llave por borrar es menor a la llave de Raiz
			borrarNodo(Raiz->HijoIzquierdo, cualllave); // Hace el llamado con el Hijo Izquierdo
		}
		else if (cualllave > Raiz->llave) { // Si la llave es mayor
			borrarNodo(Raiz->HijoDerecho, cualllave); // Hace el llamado con el Hijo Derecho
		}
		else {
			if ((Raiz->HijoIzquierdo == NULL) && (Raiz->HijoDerecho == NULL) && (cualllave == Raiz->llave)) { // Si la llave busada es igual a Raiz llave y la raiz no tiene hijos
				delete(Raiz); Raiz = NULL; // Borra el puntero y lo deja en NULL para que sea hoja del anterior
				printf("\nEl nodo de llave %i fue borrado\n", cualllave);
			}
		}
	}
}



// Funcion principal
void main(int argc, char* argv[])
{
	NodoBB * ArbolEnteros = NULL;

	printf("\nINSERTANDO la secuencia de Elementos : 9, 6, 16, 3, 13, 8, 18 ");
	Insertar(ArbolEnteros, 9);
	Insertar(ArbolEnteros, 6);
	Insertar(ArbolEnteros, 16);
	Insertar(ArbolEnteros, 3);
	Insertar(ArbolEnteros, 13);
	Insertar(ArbolEnteros, 8);
	Insertar(ArbolEnteros, 18);

	printf("\n\nRECORIENDO: ");
	printf("\nElementos en recorrido PreOrden : ");
	PreOrdenRID(ArbolEnteros);

	printf("\nElementos en recorrido EnOrden : ");
	EnOrdenIRD(ArbolEnteros);

	printf("\nElementos en recorrido PosOrden : ");
	PosOrdenIDR(ArbolEnteros);

	printf("\n\nBUSCANDO 1 x 1 : ");
	NodoBB * Aux;
	if ((Aux = Buscar(ArbolEnteros, 18)) != NULL) printf("\nBusco %i y encontro %i ", 18, Aux->llave);
	if ((Aux = Buscar(ArbolEnteros, 8)) != NULL) printf("\nBusco %i y encontro %i ", 8, Aux->llave);
	if ((Aux = Buscar(ArbolEnteros, 13)) != NULL) printf("\nBusco %i y encontro %i ", 13, Aux->llave);
	if ((Aux = Buscar(ArbolEnteros, 3)) != NULL) printf("\nBusco %i y encontro %i ", 3, Aux->llave);
	if ((Aux = Buscar(ArbolEnteros, 16)) != NULL) printf("\nBusco %i y encontro %i ", 16, Aux->llave);
	if ((Aux = Buscar(ArbolEnteros, 6)) != NULL) printf("\nBusco %i y encontro %i ", 6, Aux->llave);
	if ((Aux = Buscar(ArbolEnteros, 9)) != NULL) printf("\nBusco %i y encontro %i ", 9, Aux->llave);

	printf("\n\nTotal de raices: %i", contar(ArbolEnteros));

	printf("\n\nBORRANDO TODO ... de las hojas a la Raiz:\n");
	PodarHojas(ArbolEnteros);
	//system("pause");

	// ****************************** Comparar 2 arboles *************************
	NodoBB *Arbol1 = NULL;
	NodoBB *Arbol2 = NULL;

	// Insertar en 1 : 9, 6, 16, 3, 13, 8, 18 
	Insertar(Arbol1, 9); Insertar(Arbol1, 6); Insertar(Arbol1, 16); Insertar(Arbol1, 3); Insertar(Arbol1, 8); Insertar(Arbol1, 13); Insertar(Arbol1, 18);
	// Isertar en 2: 9, 6, 16, 3, 13, 8
	Insertar(Arbol2, 65); Insertar(Arbol2, 50); Insertar(Arbol2, 23); Insertar(Arbol2, 70); Insertar(Arbol2, 82); Insertar(Arbol2, 68); Insertar(Arbol2, 39);
	printf("Arbol1: ");
	PosOrdenIDR(Arbol1);
	printf("\nArbol2: ");
	PosOrdenIDR(Arbol2);

	printf("\n\nComparacion de arboles\n");
	if (compararArboles(Arbol1, Arbol2)) printf("Los arboles son iguales\n");
	else printf("Los arboles no son iguales\n");

	// *************************** Clonar Arboles *****************************
	// Clonacion de Arbol1 en Arbol3
	printf("\nClonado de Arbol1 en Arbol3\n");
	NodoBB *Arbol3 = clonarArbol(Arbol1, Arbol3);
	printf("\nArbol1: "); PosOrdenIDR(Arbol1);
	printf("\nArbol3: "); PosOrdenIDR(Arbol3);

	// ************************** Arbol Completo ******************************
	if (esCompleto(Arbol2)) printf("\n\nEl arbol es completo\n");
	else printf("\n\nEl arbol no es completo\n");

	// ************************** Visualizar Hojas ***************************
	visualizarHojas(Arbol1);
	system("pause");

	// ************************* Borrar un nodo *****************************
	printf("\n\nBorrar el 3 de Arbol2\n");
	printf("Arbol 2 completo: "); PosOrdenIDR(Arbol2);
	borrarNodo(Arbol2, 3);
	printf("\nArbol 2 sin la llave 3: "); PosOrdenIDR(Arbol2);
	system("pause");

}

/*
INSERTANDO la secuencia de Elementos : 9, 6, 16, 3, 13, 8, 18

RECORIENDO:
Elementos en recorrido PreOrden : 9  6  3  8  16  13  18
Elementos en recorrido EnOrden : 3  6  8  9  13  16  18
Elementos en recorrido PosOrden : 3  8  6  13  18  16  9

BUSCANDO 1 x 1 :
Busco 18 y encontro 18
Busco 8 y encontro 8
Busco 13 y encontro 13
Busco 3 y encontro 3
Busco 16 y encontro 16
Busco 6 y encontro 6
Busco 9 y encontro 9

Total de raices: 7

BORRANDO TODO ... de las hojas a la Raiz:
Borro : 3
Borro : 8
Borro : 6
Borro : 13
Borro : 18
Borro : 16
Borro : 9

Arbol1: 3  8  6  13  18  16  9
Arbol2: 39  23  50  68  82  70  65

Comparacion de arboles
Los arboles no son iguales

Clonado de Arbol1 en Arbol3

Arbol1: 3  8  6  13  18  16  9
Arbol3: 3  8  6  13  18  16  9

El arbol no es completo

 Presione una tecla para continuar . . .


*****Punto 6 del Laboratorio******************

INSERTANDO la secuencia de Elementos : 9,6,16,3,13,8,18
INSERTANDO la secuencia de Elementos : 65,50,23,70,82,68,39
INSERTANDO la secuencia de Elementos : 65,50,23,70,82,68,39

RECORIENDO:
Elementos en recorrido PreOrden : 65  50  23  39  70  68  82
Elementos en recorrido EnOrden : 23  39  50  65  68  70  82
Elementos en recorrido PosOrden : 39  23  50  68  82  70  65

RECORIENDO:
Elementos en recorrido PreOrden : 43  25  10  58  47  75  65  62  60  70  67  66  69  68  73  86  93
Elementos en recorrido EnOrden : 10  25  43  47  58  60  62  65  66  67  68  69  70  73  75  86  93
Elementos en recorrido PosOrden : 10  25  47  60  62  66  68  69  67  73  70  65  93  86  75  58  43

RECORIENDO:
Elementos en recorrido PreOrden : 10  27  17  15  13  25  21  20  19  24  29  31  51  48  35  60  66
Elementos en recorrido EnOrden : 10  13  15  17  19  20  21  24  25  27  29  31  35  48  51  60  66
Elementos en recorrido PosOrden : 13  15  19  20  24  21  25  17  35  48  66  60  51  31  29  27  10

RECORIENDO:
Elementos en recorrido PreOrden : 10  68  27  21  15  53  43  37  41  39  58  63  80  77  72  70  95
Elementos en recorrido EnOrden : 10  15  21  27  37  39  41  43  53  58  63  68  70  72  77  80  95
Elementos en recorrido PosOrden : 15  21  39  41  37  43  63  58  53  27  70  72  77  95  80  68  10


*/