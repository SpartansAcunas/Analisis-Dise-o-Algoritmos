//Pila_Cola.cpp: define el punto de entrada de la aplicación de consola.
//
#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
using namespace std;



typedef struct TEntero {
	int Entero;
	TEntero *Siguiente;
}*PtrTEntero;

typedef struct TCaracter {
	char Caracter;
	TCaracter *Siguiente;
}*PtrTCaracter;

int i; 
int n;

const int MAX = 10000;




// Funciones para generar caracteres ASCII aleatorios
long g_seed = 1;
inline int fastrand() {
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}
char GenerarRandom()
{
	char c = 32 + fastrand() % (127 - 32);
	return c;
}

// Funciones de  Caracteres ASCII

// Inicia pila de caracterres
void InicializarPila(PtrTCaracter &Pila) {
	Pila = NULL;
}

// Elimina la pila de caracteres
void DestruirPila(PtrTCaracter &Char) {
	PtrTCaracter Aux;
	Aux = Char;
	while (Char != NULL) {
		Char = Char->Siguiente;
		delete(Aux);
		Aux = Char;
	}
}

PtrTCaracter CrearCaracter(char c) {
	PtrTCaracter Nuevo = new(TCaracter);
	Nuevo->Caracter = c;
	Nuevo->Siguiente = NULL;
	return Nuevo;
}

void AgregarFinalPila(PtrTCaracter &Pila, PtrTCaracter &Nuevo) {
	PtrTCaracter Char;
	Char = Pila;

	if (Char != NULL) {
		while (Char->Siguiente != NULL) {
			Char = Char->Siguiente;
		}
		Char->Siguiente = Nuevo;
	}
	else {
		Pila = Nuevo;
	}
}

bool Muere_SigueVivo(PtrTCaracter &Char) {
	bool Muerto;
	PtrTCaracter Aux;
	PtrTCaracter Siguiente;
	PtrTCaracter Nuevo;

	Aux = Char;
	Siguiente = Aux->Siguiente;
	Char = Siguiente;

	Muerto = rand() % 2;
	cout << Muerto << endl;
	if (Muerto == true) {
		delete(Aux);
	}
	else {
		Nuevo = CrearCaracter(Aux->Caracter);
		AgregarFinalPila(Char, Nuevo);
		delete(Aux);
	}
	return Muerto;
}

// Lista la pila
void ListarPila(PtrTCaracter &Pila)
{
	int Contador = 1;
	PtrTCaracter Char;
	Char = Pila;
	while (Char != NULL)
	{
		cout << Contador << " " << Char->Caracter << "  " << &Char << endl;
		Char = Char->Siguiente;
		Contador++;
	}
}


// Inicializa lista enlazada
void InicializarLista(PtrTEntero &Lista) {
	Lista = NULL;
}

// Destruye la lista
void DestruirLista(PtrTEntero &Lista) {
	PtrTEntero Aux;
	Aux = Lista;
	while (Lista != NULL) {
		Lista = Lista->Siguiente;
		delete(Aux);
		Aux = Lista;

	}
}



// Genera enteros enlazados
PtrTEntero generarEntero(int k) {
	PtrTEntero Nuevo = new(TEntero);
	Nuevo->Entero = k;
	Nuevo->Siguiente = NULL;
	return Nuevo;
}

// Agrega entero al final de la lista
void AgregarFinalLista(PtrTEntero &Lista, PtrTEntero &Nuevo) {
	PtrTEntero Ent;
	Ent = Lista;

	if (Ent != NULL) {
		while (Ent->Siguiente != NULL) {
			Ent = Ent->Siguiente;
		}
		Ent->Siguiente = Nuevo;
	}
	else {
		Lista = Nuevo;
	}
}

void ImprimirLista(PtrTEntero &Lista) {
	PtrTEntero Aux = Lista;

	while (Aux != NULL) {
		int cont = 0;
		while (cont < 10) {
			cout << Aux->Entero << endl;
			cont++;
		}
		Aux = Aux->Siguiente;
	}
}


void main(int argc, char* argv[]) {

	PtrTCaracter Char;
	PtrTCaracter Nuevo;
	InicializarPila(Char);
	PtrTEntero Ent;
	PtrTEntero New;
	InicializarLista(Ent);

	// ********* Menu para Pila ********

	int opc;
	bool menu = true;
	while (menu) {

		char c;
		bool Muerto;

		system("CLS");
		cout << " ********* Menu de Pila *********" << endl << endl;
		cout << "  1. Push de 300 caracteres ASCII" << endl;
		cout << "  2. Listar Pila" << endl;
		cout << "  3. Ciclo de actuacion" << endl;
		cout << "  4. Salir" << endl;
		cout << endl << "	Digite la opcion: ";
		cin >> opc;
		switch (opc) {
		case 1: {
			InicializarPila(Char);
			for (i = 0; i < 300; i++) {
				c = GenerarRandom();
				Nuevo = CrearCaracter(c);
				AgregarFinalPila(Char, Nuevo);
			}
			cout << "Se acaba de crear la Pila de caracteres" << endl;
			system("pause");
			break;
		}
		case 2: {
			system("CLS");
			ListarPila(Char);
			system("pause");
			break;
		}
		case 3: {
			while (Char != NULL) {
				for (i = 0; i <= 100; i++) {
					cout << Char->Caracter << endl;
					system("CLS");
					Sleep(25);
				}
				Muerto = Muere_SigueVivo(Char);
				if (Muerto == true) {
					cout << "Murio" << endl;
				}
				else {
					cout << "Sigue vivo" << endl;
				}
			}
			break;
		}
		case 4: {
			system("CLS");
			menu = false;
			system("CLS");
			cout << "Liberando memoria ... " << endl << endl << endl;
			DestruirPila(Char);
			system("Pause");
			break;
		}
		}
	}

	/*
	// ****************** Arreglo de Max Enteros ***********************
	int Arreglo[MAX]; // Arreglo de enteros para prueba

	// Generar el arreglo
	time_t inicio, fin; // Definicion de variables de tiempo
	inicio = time(NULL); // Se toma el tiempo inicial
	system("CLS");
	for (n = 0; n < MAX; n++) { // Se inicia un ciclo de 0 hasta MAX
		Arreglo[n] = n; // Se añaden los numeros del ciclo al arreglo
		int cont = 0;
		while (cont < 10) {
			cout << n << endl;
			cont++;
		}
	}
	fin = time(NULL); // Se toma el tiempo final

	// Se imprimen los tiempos obtenidos
	cout << endl << "El tiempo inicial fue: " << inicio << endl;
	cout << endl << "El tiempo final fue: " << fin << endl;
	cout << endl << "El tiempo transcurrido fue: " << (fin - inicio) << endl;
	system("pause");
	*/

	// ***************** Enlazada de Max Enteros ******************

	// Se inicia la lista
	InicializarLista(Ent);
	time_t inicio, fin; // Se inicializan las variables de tiempo

	inicio = time(NULL); // Inicio toma el valor de tiempo inicial
	for (n = 0; n < MAX; n++) {
		int cont = 0;
		New = generarEntero(n); // Se añaden los elementos
		AgregarFinalLista(Ent, New);
		while (cont < 10) {
			cout << New->Entero << endl;
			cont++;
		}
	}
	fin = time(NULL); // fin toma el valor de tiempo final
	cout << "Se acaba de crear la Lista de enteros" << endl;
	system("pause");


	// Se imprimen los tiempos obtenidos
	cout << endl << "El tiempo inicial fue: " << inicio << endl;
	cout << endl << "El tiempo final fue: " << fin << endl;
	cout << endl << "El tiempo transcurrido fue: " << (fin - inicio) << endl;
	system("pause");

}

/* ******** Con el arreglo y MAX = 10000
El tiempo inicial fue: 1567662182

El tiempo final fue: 1567662227

El tiempo transcurrido fue: 45
*/

/* ******** Con la lista y MAX = 10000

El tiempo inicial fue: 1567662300

El tiempo final fue: 1567662334

El tiempo transcurrido fue: 34

*/