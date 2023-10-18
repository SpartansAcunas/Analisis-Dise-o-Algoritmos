#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;


//LISTA ENLAZADA DOBLE

typedef struct TArticulo // Creacion de nuevo tipo de dato con forma de estructura
{
	int Codigo; // Codigo del articulo
	char Nombre[20]; // Contiene el nombre
	int Disponible; // Contiene la cantidad disponible
	double Precio; // Contiene el precio
	TArticulo*Anterior; // Puntero para almacenar la direccion del articulo anterior
	TArticulo*Siguiente; // Puntero para almacenar la direccion del articulo siguiente
}X;
typedef TArticulo * PtrTArticulo; // Redefine el tipo de dato TArticulo com puntero


// Funcion para iniciar un nuevo inventario
void InicializarInventario(PtrTArticulo &Lista)
{
	Lista = NULL; // Asigna a Lista la direccion de NULL
}


PtrTArticulo CrearArticulo(int NCodigo, int NDisponible, double NPrecio) {
	PtrTArticulo Nuevo = new(TArticulo);
	char buffer[5];


	Nuevo->Codigo = NCodigo;
	Nuevo->Disponible = NDisponible;
	Nuevo->Precio = NPrecio;


	strcpy_s(Nuevo->Nombre, "Pieza");
	_itoa_s(NCodigo, buffer, 10);
	strcat_s(Nuevo->Nombre, buffer);

	Nuevo->Anterior = NULL;
	Nuevo->Siguiente = NULL;
	return Nuevo;
}

void AgregarFinalInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo) {
	PtrTArticulo Aux;
	Aux = Lista;
	if (Aux == NULL) {
		Lista = Nuevo;
	}
	else {
		while (Aux->Siguiente != NULL) {
			Aux = Aux->Siguiente;
		}
		Aux->Siguiente = Nuevo;
		Nuevo->Anterior = Aux;
	}
}


void AgregarInicioInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo) {


	if (Lista == NULL) {
		Lista = Nuevo;
	}
	else
	{
		Nuevo->Siguiente = Lista;
		Lista->Anterior = Nuevo;
		Lista = Nuevo;
	}
}
void Listar_Inicio_a_Final(PtrTArticulo &Lista) {
	PtrTArticulo Aux;
	Aux = Lista;
	while (Aux != NULL) {
		cout << "[";
		cout << Aux->Codigo << ",";
		cout << Aux->Nombre << ",";
		cout << Aux->Precio << "] - ";
		Aux = Aux->Siguiente;
	}
	system("pause");
}

void Listar_Final_a_Inicio(PtrTArticulo &Lista) {
	PtrTArticulo Aux;
	Aux = Lista;
	while (Aux->Siguiente != NULL)  Aux = Aux->Siguiente;

	while (Aux != NULL) {
		cout << "[";
		cout << Aux->Codigo << ",";
		cout << Aux->Nombre << ",";
		cout << Aux->Precio << "] - ";
		Aux = Aux->Anterior;
	}
	system("pause");
}



void DestruirInventario(PtrTArticulo &Lista)
{
	PtrTArticulo Aux;
	Aux = Lista;
	while (Aux != NULL)
	{
		Lista = Lista->Siguiente;
		delete(Aux);
		Aux = Lista;
	}
}


void main()
{
	// creacion  de variables
	PtrTArticulo Nuevo;
	PtrTArticulo Abarrotes;

	// Carga en la lista codigos del 1 al 100, luego los lista del inicio al final y luego del final al inicio.  Finalmente destruye la lista.
	//INICIO PILOTO AGREGANDO AL INICIO EN LISTA DOBLE
	InicializarInventario(Abarrotes);

	for (int i = 1; i <= 100; i++)
	{
		Nuevo = CrearArticulo(i, i, i);
		AgregarInicioInventario(Abarrotes, Nuevo);
	}

	system("pause");
	system("cls");
	cout << "Listando elementos del Inicio al Final de una lista creada con insercion al inicio" << endl;
	Listar_Inicio_a_Final(Abarrotes);
	cout << "Listando elementos del Final al Inicio de una lista creada con insercion al inicio" << endl;
	Listar_Final_a_Inicio(Abarrotes);
	DestruirInventario(Abarrotes);
	//FIN PILOTO AGREGANDO AL INICIO EN LISTA DOBLE

	//INICIO PILOTO AGREGANDO AL FINAL EN LISTA DOBLE
	InicializarInventario(Abarrotes);

	for (int i = 500; i <= 600; i++)
	{
		Nuevo = CrearArticulo(i, i, i);
		AgregarFinalInventario(Abarrotes, Nuevo);
	}

	system("pause");
	system("cls");
	cout << "Listando elementos del Inicio al Final de una lista creada con insercion al final" << endl;
	Listar_Inicio_a_Final(Abarrotes);
	cout << "Listando elementos del Final al Inicio de una lista creada con insercion al final" << endl;
	Listar_Final_a_Inicio(Abarrotes);
	DestruirInventario(Abarrotes);
	//FIN PILOTO AGREGANDO AL FINAL EN LISTA DOBLE
}
	/*Listando elementos del Inicio al Final de una lista creada con insercion al inicio
[100,Pieza100,100] - [99,Pieza99,99] - [98,Pieza98,98] - [97,Pieza97,97] - [96,Pieza96,96] - [95,Pieza95,95] - [94,Pieza94,94] - [93,Pieza93,93] - [92,Pieza92,92] - [91,Pieza91,91] - [90,Pieza90,90] - [89,Pieza89,89] - [88,Pieza88,88] - [87,Pieza87,87] - [86,Pieza86,86] - [85,Pieza85,85] - [84,Pieza84,84] - [83,Pieza83,83] - [82,Pieza82,82] - [81,Pieza81,81] - [80,Pieza80,80] - [79,Pieza79,79] - [78,Pieza78,78] - [77,Pieza77,77] - [76,Pieza76,76] - [75,Pieza75,75] - [74,Pieza74,74] - [73,Pieza73,73] - [72,Pieza72,72] - [71,Pieza71,71] - [70,Pieza70,70] - [69,Pieza69,69] - [68,Pieza68,68] - [67,Pieza67,67] - [66,Pieza66,66] - [65,Pieza65,65] - [64,Pieza64,64] - [63,Pieza63,63] - [62,Pieza62,62] - [61,Pieza61,61] - [60,Pieza60,60] - [59,Pieza59,59] - [58,Pieza58,58] - [57,Pieza57,57] - [56,Pieza56,56] - [55,Pieza55,55] - [54,Pieza54,54] - [53,Pieza53,53] - [52,Pieza52,52] - [51,Pieza51,51] - [50,Pieza50,50] - [49,Pieza49,49] - [48,Pieza48,48] - [47,Pieza47,47] - [46,Pieza46,46] - [45,Pieza45,45] - [44,Pieza44,44] - [43,Pieza43,43] - [42,Pieza42,42] - [41,Pieza41,41] - [40,Pieza40,40] - [39,Pieza39,39] - [38,Pieza38,38] - [37,Pieza37,37] - [36,Pieza36,36] - [35,Pieza35,35] - [34,Pieza34,34] - [33,Pieza33,33] - [32,Pieza32,32] - [31,Pieza31,31] - [30,Pieza30,30] - [29,Pieza29,29] - [28,Pieza28,28] - [27,Pieza27,27] - [26,Pieza26,26] - [25,Pieza25,25] - [24,Pieza24,24] - [23,Pieza23,23] - [22,Pieza22,22] - [21,Pieza21,21] - [20,Pieza20,20] - [19,Pieza19,19] - [18,Pieza18,18] - [17,Pieza17,17] - [16,Pieza16,16] - [15,Pieza15,15] - [14,Pieza14,14] - [13,Pieza13,13] - [12,Pieza12,12] - [11,Pieza11,11] - [10,Pieza10,10] - [9,Pieza9,9] - [8,Pieza8,8] - [7,Pieza7,7] - [6,Pieza6,6] - [5,Pieza5,5] - [4,Pieza4,4] - [3,Pieza3,3] - [2,Pieza2,2] - [1,Pieza1,1] - Presione una tecla para continuar . . .
	*/