//// Pila_Cola.cpp: define el punto de entrada de la aplicación de consola.
//
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>


using namespace std;

typedef struct TArticulo
{
	int Codigo;
	char Nombre[20];
	int Disponible;
	float Precio;
	TArticulo *Siguiente;
}*PtrTArticulo;


int i; 

void InicializarInventario(PtrTArticulo &Lista)
{
	Lista = NULL;
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
PtrTArticulo CrearArticulo(int NCodigo, int NDisponible, float NPrecio)
{
	PtrTArticulo Pieza = new(TArticulo);
	char buffer[5];

	Pieza->Codigo = NCodigo;
	Pieza->Disponible = NDisponible;
	Pieza->Precio = NPrecio;

	strcpy_s(Pieza->Nombre, "Pieza");
	_itoa_s(NCodigo, buffer, 10);
	strcat_s(Pieza->Nombre, buffer);

	Pieza->Siguiente = NULL;
	return Pieza;
}
void AgregarInicioInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo)
{
	Nuevo->Siguiente = Lista;
	Lista = Nuevo;
}
void AgregarFinalInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo)
{
	PtrTArticulo Aux;
	Aux = Lista;
	if (Aux != NULL)
	{
		while (Aux->Siguiente != NULL)
		{
			Aux = Aux->Siguiente;
		}

		Aux->Siguiente = Nuevo;
	}
	else
	{
		Lista = Nuevo;
	}


}
void ListarInventario(PtrTArticulo &Lista)
{
	int Contador = 1;
	PtrTArticulo Aux;
	Aux = Lista;
	while (Aux != NULL)
	{
		printf(" %d ", Contador);
		printf("%d ", Aux->Codigo);
		printf("%s ", Aux->Nombre);
		printf(" %d ", Aux->Disponible);
		printf(" %f\n ", Aux->Precio);
		Aux = Aux->Siguiente;
		Contador++;
	}
}
PtrTArticulo BuscarArticulo(PtrTArticulo &Lista, int cual)
{
	return Lista;
}


void GuardarInventario(PtrTArticulo Lista) {
	FILE *archivo;
	fopen_s(&archivo, "ARCHIVO.txt", "w+");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo.");
	}
	else {
		PtrTArticulo AUX = Lista;
		while (AUX != NULL) {
			fprintf(archivo, "%i\n", AUX->Codigo);
			fprintf(archivo, "%s\n", AUX->Nombre);
			fprintf(archivo, "%i\n", AUX->Disponible);
			fprintf(archivo, "%f\n", AUX->Precio);
			AUX = AUX->Siguiente;
		}


	}
	fclose(archivo);
}
void CargarInventario(PtrTArticulo &Lista) {
	PtrTArticulo Nuevo;
	FILE *archivo;
	fopen_s(&archivo, "ARCHIVO.txt", "r");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo");
	}
	else {


		while (!feof(archivo)) {
			Nuevo = new(TArticulo);
			char Cadena[20];
			fscanf_s(archivo, "%i\n", &Nuevo->Codigo);
			fscanf_s(archivo, "%s\n", Cadena, 20);
			fscanf_s(archivo, "%i\n", &Nuevo->Disponible);
			fscanf_s(archivo, "%f\n", &Nuevo->Precio);
			strcpy_s(Nuevo->Nombre, Cadena);
			Nuevo->Siguiente = NULL;
			AgregarFinalInventario(Lista, Nuevo);

		}
	}
	fclose(archivo);
}

void Push(PtrTArticulo &Lista, PtrTArticulo Nuevo) {
	AgregarInicioInventario(Lista, Nuevo);
}
PtrTArticulo Top(PtrTArticulo &Lista) {
	return Lista;
}
PtrTArticulo Pop(PtrTArticulo &Lista) {
	PtrTArticulo Aux = Lista;
	Lista = Lista->Siguiente;
	Aux->Siguiente = NULL;
	return Aux;
}
void Encolar(PtrTArticulo &Lista, PtrTArticulo Nuevo) {
	AgregarFinalInventario(Lista, Nuevo);
}

PtrTArticulo Primero(PtrTArticulo &Lista) {
	return Lista;
}
PtrTArticulo Descolar(PtrTArticulo &Lista) {
	PtrTArticulo Aux = Lista;
	Lista = Lista->Siguiente;
	Aux->Siguiente = NULL;
	return Aux;
}







void main(int argc, char* argv[])
{
	
	PtrTArticulo Pila_Llantas;
	PtrTArticulo Cola_Pasajeros; 
	PtrTArticulo Nuevo;
	int i;

		


	InicializarInventario(Pila_Llantas);
	InicializarInventario(Cola_Pasajeros);
	int opc;
	bool menu = true;
	while (menu) {
		system("CLS");
		cout << " ********* Menu de pila *********" << endl << endl;
		cout << "  1. Usar Pila" << endl;
		cout << "  2. Usar cola" << endl;
		cout << "  3. Salir" << endl;
		cout << endl << "	Digite la opcion: ";
		cin >> opc;
		switch (opc) {
		case 1: {
			int opc;
			bool menu = true;
			while (menu) {
				system("CLS");
				cout << " ********* Submenu de pila *********" << endl << endl;
				cout << "  1. Push de 100 elementos" << endl;
				cout << "  2. Top" << endl;
				cout << "  3. Pop" << endl;
				cout << "  4. Salir" << endl;
				cout << endl << "	Digite la opcion: ";
				cin >> opc;
				switch (opc) {
				case 1: {// Insercion con Push
					system("CLS");
					cout << "Haciendo Push de 100 elementos" << endl;

					for (i = 1; i <= 100; i++)
					{
						Nuevo = CrearArticulo(i, i, i);
						Push(Pila_Llantas, Nuevo);
						cout << "Se acaba de hacer PUSH, el Top de la Pila ahora es: " << endl << Top(Pila_Llantas)->Codigo << endl;
					}
					system("pause");
					break;
				}
				case 2: {// Pregunto con TOP
					system("CLS");
					if (Top(Pila_Llantas) != NULL)
						cout << "El Top de la Pila es: " << endl << Top(Pila_Llantas)->Codigo << endl;
					else
						cout << "El Top de la Pila es: NULO " << endl;

					system("pause");
					break;
				}
				case 3: { //Elimino con Top
					system("CLS");
					PtrTArticulo Aux = Pop(Pila_Llantas);
					if (Top(Pila_Llantas) != NULL)
						cout << "Se acaba de hacer POP, el Top de la Pila ahora es: " << endl << Top(Pila_Llantas)->Codigo << endl;
					else
						cout << "Se acaba de hacer POP, el Top de la Pila ahora es:  NULO " << endl;

					system("pause");
					break;
				}
				case 4: {//Saliendo Y Limpiando Memoria
					system("CLS");
					menu = false;
					system("CLS");
					cout << "Liberando memoria ... " << endl << endl << endl;
					DestruirInventario(Pila_Llantas);
					system("Pause");
					break;
				}
				}
			}
			system("pause");
			break;
		}
		case 2: {
			int opc;
			bool menu = true;
			while (menu) {
				system("CLS");
				cout << " ********* Submenu de cola *********" << endl << endl;
				cout << "  1. Encolar" << endl;
				cout << "  2. Primer Elemento" << endl;
				cout << "  3. Descolar" << endl;
				cout << "  4. Salir" << endl;
				cout << endl << "	Digite la opcion: ";
				cin >> opc;
				switch (opc) {
				case 1: {// ENCOLAR
					system("CLS");
					cout << "Haciendo Encolar de 50 elementos" << endl;

					for (i = 1; i <= 50; i++)
					{
						Nuevo = CrearArticulo(i, i, i);
						Encolar(Cola_Pasajeros, Nuevo);
						cout << "Se acaba de hacer ENCOLAR al final de la Cola de : " << Nuevo->Codigo << endl;
					}

					system("pause");
					break;
				}
				case 2: {// Preguntar Por el Primer valor en Lista
					system("CLS");
					cout << "El primero que va a ser atendido de la cola es : " << Primero(Cola_Pasajeros)->Codigo << endl;
					system("pause");
					break;
				}
				case 3: {// Descolar o eliminar  valor Solicitado
					system("CLS");

					PtrTArticulo Aux = Descolar(Cola_Pasajeros);

					if (Primero(Cola_Pasajeros) != NULL)
						cout << "Se hizo Descolar, el  primero  en la Cola ahora es: " << endl << Primero(Cola_Pasajeros)->Codigo << endl;
					else
						cout << "Se hizo Descolar, el  primero  en la Cola ahora es:  NULO " << endl;

					system("pause");
					break;
				}
				case 4: {//Saliendo Y Limpiando Memoria
					menu = false;
					system("CLS");
					cout << "Liberando memoria ... " << endl << endl << endl;
					DestruirInventario(Cola_Pasajeros);
					system("Pause");
					break;
				}
				}
			}
			system("pause");
			break;
		}
		case 3: {
			menu = false;
			system("CLS");
			cout << "Opcion 5: saliendo . . ." << endl << endl << endl;
			cout << "ADIOS!!!" << endl;
			system("Pause");
			break;
		}
		}
	}
}  
/*Haciendo Push de 100 elementos
Se acaba de hacer PUSH, el Top de la Pila ahora es :
1
Se acaba de hacer PUSH, el Top de la Pila ahora es :
2
Se acaba de hacer PUSH, el Top de la Pila ahora es :
3
Se acaba de hacer PUSH, el Top de la Pila ahora es :
4
Se acaba de hacer PUSH, el Top de la Pila ahora es :
5
Se acaba de hacer PUSH, el Top de la Pila ahora es :
6
Se acaba de hacer PUSH, el Top de la Pila ahora es :
7
Se acaba de hacer PUSH, el Top de la Pila ahora es :
8
Se acaba de hacer PUSH, el Top de la Pila ahora es :
9
Se acaba de hacer PUSH, el Top de la Pila ahora es :
10
Se acaba de hacer PUSH, el Top de la Pila ahora es :
11
Se acaba de hacer PUSH, el Top de la Pila ahora es :
12
Se acaba de hacer PUSH, el Top de la Pila ahora es :
13
Se acaba de hacer PUSH, el Top de la Pila ahora es :
14
Se acaba de hacer PUSH, el Top de la Pila ahora es :
15
Se acaba de hacer PUSH, el Top de la Pila ahora es :
16
Se acaba de hacer PUSH, el Top de la Pila ahora es :
17
Se acaba de hacer PUSH, el Top de la Pila ahora es :
18
Se acaba de hacer PUSH, el Top de la Pila ahora es :
19
Se acaba de hacer PUSH, el Top de la Pila ahora es :
20
Se acaba de hacer PUSH, el Top de la Pila ahora es :
21
Se acaba de hacer PUSH, el Top de la Pila ahora es :
22
Se acaba de hacer PUSH, el Top de la Pila ahora es :
23
Se acaba de hacer PUSH, el Top de la Pila ahora es :
24
Se acaba de hacer PUSH, el Top de la Pila ahora es :
25
Se acaba de hacer PUSH, el Top de la Pila ahora es :
26
Se acaba de hacer PUSH, el Top de la Pila ahora es :
27
Se acaba de hacer PUSH, el Top de la Pila ahora es :
28
Se acaba de hacer PUSH, el Top de la Pila ahora es :
29
Se acaba de hacer PUSH, el Top de la Pila ahora es :
30
Se acaba de hacer PUSH, el Top de la Pila ahora es :
31
Se acaba de hacer PUSH, el Top de la Pila ahora es :
32
Se acaba de hacer PUSH, el Top de la Pila ahora es :
33
Se acaba de hacer PUSH, el Top de la Pila ahora es :
34
Se acaba de hacer PUSH, el Top de la Pila ahora es :
35
Se acaba de hacer PUSH, el Top de la Pila ahora es :
36
Se acaba de hacer PUSH, el Top de la Pila ahora es :
37
Se acaba de hacer PUSH, el Top de la Pila ahora es :
38
Se acaba de hacer PUSH, el Top de la Pila ahora es :
39
Se acaba de hacer PUSH, el Top de la Pila ahora es :
40
Se acaba de hacer PUSH, el Top de la Pila ahora es :
41
Se acaba de hacer PUSH, el Top de la Pila ahora es :
42
Se acaba de hacer PUSH, el Top de la Pila ahora es :
43
Se acaba de hacer PUSH, el Top de la Pila ahora es :
44
Se acaba de hacer PUSH, el Top de la Pila ahora es :
45
Se acaba de hacer PUSH, el Top de la Pila ahora es :
46
Se acaba de hacer PUSH, el Top de la Pila ahora es :
47
Se acaba de hacer PUSH, el Top de la Pila ahora es :
48
Se acaba de hacer PUSH, el Top de la Pila ahora es :
49
Se acaba de hacer PUSH, el Top de la Pila ahora es :
50
Se acaba de hacer PUSH, el Top de la Pila ahora es :
51
Se acaba de hacer PUSH, el Top de la Pila ahora es :
52
Se acaba de hacer PUSH, el Top de la Pila ahora es :
53
Se acaba de hacer PUSH, el Top de la Pila ahora es :
54
Se acaba de hacer PUSH, el Top de la Pila ahora es :
55
Se acaba de hacer PUSH, el Top de la Pila ahora es :
56
Se acaba de hacer PUSH, el Top de la Pila ahora es :
57
Se acaba de hacer PUSH, el Top de la Pila ahora es :
58
Se acaba de hacer PUSH, el Top de la Pila ahora es :
59
Se acaba de hacer PUSH, el Top de la Pila ahora es :
60
Se acaba de hacer PUSH, el Top de la Pila ahora es :
61
Se acaba de hacer PUSH, el Top de la Pila ahora es :
62
Se acaba de hacer PUSH, el Top de la Pila ahora es :
63
Se acaba de hacer PUSH, el Top de la Pila ahora es :
64
Se acaba de hacer PUSH, el Top de la Pila ahora es :
65
Se acaba de hacer PUSH, el Top de la Pila ahora es :
66
Se acaba de hacer PUSH, el Top de la Pila ahora es :
67
Se acaba de hacer PUSH, el Top de la Pila ahora es :
68
Se acaba de hacer PUSH, el Top de la Pila ahora es :
69
Se acaba de hacer PUSH, el Top de la Pila ahora es :
70
Se acaba de hacer PUSH, el Top de la Pila ahora es :
71
Se acaba de hacer PUSH, el Top de la Pila ahora es :
72
Se acaba de hacer PUSH, el Top de la Pila ahora es :
73
Se acaba de hacer PUSH, el Top de la Pila ahora es :
74
Se acaba de hacer PUSH, el Top de la Pila ahora es :
75
Se acaba de hacer PUSH, el Top de la Pila ahora es :
76
Se acaba de hacer PUSH, el Top de la Pila ahora es :
77
Se acaba de hacer PUSH, el Top de la Pila ahora es :
78
Se acaba de hacer PUSH, el Top de la Pila ahora es :
79
Se acaba de hacer PUSH, el Top de la Pila ahora es :
80
Se acaba de hacer PUSH, el Top de la Pila ahora es :
81
Se acaba de hacer PUSH, el Top de la Pila ahora es :
82
Se acaba de hacer PUSH, el Top de la Pila ahora es :
83
Se acaba de hacer PUSH, el Top de la Pila ahora es :
84
Se acaba de hacer PUSH, el Top de la Pila ahora es :
85
Se acaba de hacer PUSH, el Top de la Pila ahora es :
86
Se acaba de hacer PUSH, el Top de la Pila ahora es :
87
Se acaba de hacer PUSH, el Top de la Pila ahora es :
88
Se acaba de hacer PUSH, el Top de la Pila ahora es :
89
Se acaba de hacer PUSH, el Top de la Pila ahora es :
90
Se acaba de hacer PUSH, el Top de la Pila ahora es :
91
Se acaba de hacer PUSH, el Top de la Pila ahora es :
92
Se acaba de hacer PUSH, el Top de la Pila ahora es :
93
Se acaba de hacer PUSH, el Top de la Pila ahora es :
94
Se acaba de hacer PUSH, el Top de la Pila ahora es :
95
Se acaba de hacer PUSH, el Top de la Pila ahora es :
96
Se acaba de hacer PUSH, el Top de la Pila ahora es :
97
Se acaba de hacer PUSH, el Top de la Pila ahora es :
98
Se acaba de hacer PUSH, el Top de la Pila ahora es :
99
Se acaba de hacer PUSH, el Top de la Pila ahora es :
100
Presione una tecla para continuar . . .

El Top de la Pila es:
100
Presione una tecla para continuar . . .

Se acaba de hacer POP, el Top de la Pila ahora es:
99
Presione una tecla para continuar . . .


Haciendo Encolar de 50 elementos
Se acaba de hacer ENCOLAR al final de la Cola de : 1
Se acaba de hacer ENCOLAR al final de la Cola de : 2
Se acaba de hacer ENCOLAR al final de la Cola de : 3
Se acaba de hacer ENCOLAR al final de la Cola de : 4
Se acaba de hacer ENCOLAR al final de la Cola de : 5
Se acaba de hacer ENCOLAR al final de la Cola de : 6
Se acaba de hacer ENCOLAR al final de la Cola de : 7
Se acaba de hacer ENCOLAR al final de la Cola de : 8
Se acaba de hacer ENCOLAR al final de la Cola de : 9
Se acaba de hacer ENCOLAR al final de la Cola de : 10
Se acaba de hacer ENCOLAR al final de la Cola de : 11
Se acaba de hacer ENCOLAR al final de la Cola de : 12
Se acaba de hacer ENCOLAR al final de la Cola de : 13
Se acaba de hacer ENCOLAR al final de la Cola de : 14
Se acaba de hacer ENCOLAR al final de la Cola de : 15
Se acaba de hacer ENCOLAR al final de la Cola de : 16
Se acaba de hacer ENCOLAR al final de la Cola de : 17
Se acaba de hacer ENCOLAR al final de la Cola de : 18
Se acaba de hacer ENCOLAR al final de la Cola de : 19
Se acaba de hacer ENCOLAR al final de la Cola de : 20
Se acaba de hacer ENCOLAR al final de la Cola de : 21
Se acaba de hacer ENCOLAR al final de la Cola de : 22
Se acaba de hacer ENCOLAR al final de la Cola de : 23
Se acaba de hacer ENCOLAR al final de la Cola de : 24
Se acaba de hacer ENCOLAR al final de la Cola de : 25
Se acaba de hacer ENCOLAR al final de la Cola de : 26
Se acaba de hacer ENCOLAR al final de la Cola de : 27
Se acaba de hacer ENCOLAR al final de la Cola de : 28
Se acaba de hacer ENCOLAR al final de la Cola de : 29
Se acaba de hacer ENCOLAR al final de la Cola de : 30
Se acaba de hacer ENCOLAR al final de la Cola de : 31
Se acaba de hacer ENCOLAR al final de la Cola de : 32
Se acaba de hacer ENCOLAR al final de la Cola de : 33
Se acaba de hacer ENCOLAR al final de la Cola de : 34
Se acaba de hacer ENCOLAR al final de la Cola de : 35
Se acaba de hacer ENCOLAR al final de la Cola de : 36
Se acaba de hacer ENCOLAR al final de la Cola de : 37
Se acaba de hacer ENCOLAR al final de la Cola de : 38
Se acaba de hacer ENCOLAR al final de la Cola de : 39
Se acaba de hacer ENCOLAR al final de la Cola de : 40
Se acaba de hacer ENCOLAR al final de la Cola de : 41
Se acaba de hacer ENCOLAR al final de la Cola de : 42
Se acaba de hacer ENCOLAR al final de la Cola de : 43
Se acaba de hacer ENCOLAR al final de la Cola de : 44
Se acaba de hacer ENCOLAR al final de la Cola de : 45
Se acaba de hacer ENCOLAR al final de la Cola de : 46
Se acaba de hacer ENCOLAR al final de la Cola de : 47
Se acaba de hacer ENCOLAR al final de la Cola de : 48
Se acaba de hacer ENCOLAR al final de la Cola de : 49
Se acaba de hacer ENCOLAR al final de la Cola de : 50
Presione una tecla para continuar . . .

El primero que va a ser atendido de la cola es : 1
Presione una tecla para continuar . . .

Se hizo Descolar, el  primero  en la Cola ahora es:
2
Presione una tecla para continuar . . .

*/




