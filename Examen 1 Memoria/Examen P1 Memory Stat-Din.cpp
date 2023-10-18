// Examen P1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//Dinamico:

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cctype> 
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
using namespace std;

typedef struct TVotante
{
	int Cedula;
	char Nombre[20];
	char Direccion[20];
	int Edad;
	TVotante *Siguiente;
}*PtrTVotante;

int i;


PtrTVotante CrearVotante(int NCedula, string NNombre, string NDireccion, int NEdad)
{
	PtrTVotante Persona = new(TVotante);

	Persona->Cedula = NCedula;
	strcpy(Persona->Nombre, NNombre.c_str());
	strcpy(Persona->Direccion, NDireccion.c_str());
	Persona->Edad = NEdad;

	Persona->Siguiente = NULL;
	return Persona;
}
void InicializarVotantes(PtrTVotante &Lista)
{
	Lista = NULL;
}

void AgregarInicioVotantes(PtrTVotante &Lista, PtrTVotante &Nuevo)
{
	Nuevo->Siguiente = Lista;
	Lista = Nuevo;
}



void ListarVotantes(PtrTVotante &Lista)
{
	int Contador = 1;
	PtrTVotante Aux;
	Aux = Lista;

	while (Aux != NULL)
	{
		printf(" %d ", Contador);
		printf("%d ", Aux->Cedula);
		printf("%s ", Aux->Nombre);
		printf(" %s ", Aux->Direccion);
		printf(" %d\n ", Aux->Edad);
		Aux = Aux->Siguiente;
		Contador++;
	}
}


void BuscarMasViejo(PtrTVotante &Lista, PtrTVotante &Mayor)
{
	PtrTVotante Aux;
	Aux = Lista;

	while (Aux != NULL) {
		if (Aux->Edad > Mayor->Edad) {
			Mayor = Aux;
		}
		Aux = Aux->Siguiente;
	}
	printf("%d ", Mayor->Cedula);
	printf("%s ", Mayor->Nombre);
	printf(" %s ", Mayor->Direccion);
	printf("edad: %d\n ", Mayor->Edad);
}


void ImprimirImpares(PtrTVotante &Lista) {
	PtrTVotante Aux;
	Aux = Lista;

	while (Aux != NULL)
	{
		if (Aux->Edad % 2 != 0) {
			printf("%d ", Aux->Cedula);
			printf("%s ", Aux->Nombre);
			printf(" %s ", Aux->Direccion);
			printf(" %d\n ", Aux->Edad);
		}
		Aux = Aux->Siguiente;
	}
}


int main(int argc, char* argv[])
{

	PtrTVotante Persona;
	int opcion = 0;

	while (opcion < 5) {
		cout << "1. agregar votantes" << '\n';
		cout << "2. listar votantes" << '\n';
		cout << "3. buscar mas viejo" << '\n';
		cout << "4. listar con edad impar" << '\n';
		cout << "5. salir" << '\n';
		cout << "ingrese una opcion: ";
		cin >> opcion;

		switch (opcion) {
		case 1:
			InicializarVotantes(Persona);
			for (int i = 1; i <= 825; i++)
			{
				PtrTVotante Nuevo;
				Nuevo = CrearVotante(i, "nombre-" + to_string(i), "direccion-" + to_string(i), i);
				AgregarInicioVotantes(Persona, Nuevo);
			}
			break;
		case 2:
			ListarVotantes(Persona);
			break;
		case 3:
			PtrTVotante Mayor;
			Mayor->Edad = 0;
			BuscarMasViejo(Persona, Mayor);
			break;
		case 4:
			ImprimirImpares(Persona);
			break;
		}
	}

	return 0;
}

/*Estatico

typedef struct TVotante
{
	int Cedula;
	char Nombre[20];
	char Direccion[20];
	int Edad;
	bool Activo;
};

void ListarVotantes(TVotante Personas[826]) {
  for (int i = 1; i <= 825; i++)
  {
	printf("%d ", Personas[i].Cedula);
	printf("%s ", Personas[i].Nombre);
	printf("%s ", Personas[i].Direccion);
	printf("%d ", Personas[i].Edad);
	printf("%d\n", Personas[i].Activo);
  }
}

void ListarImpares(TVotante Personas[826]) {
  for (int i = 1; i <= 825; i++)
  {
	if (Personas[i].Edad%2 != 0) {
	  printf("%d ", Personas[i].Cedula);
	  printf("%s ", Personas[i].Nombre);
	  printf("%s ", Personas[i].Direccion);
	  printf("%d ", Personas[i].Edad);
	  printf("%d\n", Personas[i].Activo);
	}
  }
}

void BuscarViejo(TVotante Personas[826]) {
  int indexViejo = 1;
  for (int i = 1; i <= 825; i++)
  {
	if (Personas[i].Edad > Personas[indexViejo].Edad ) {
	  indexViejo = i;
	}
  }
  printf("%d ", Personas[indexViejo].Cedula);
  printf("%s ", Personas[indexViejo].Nombre);
  printf("%s ", Personas[indexViejo].Direccion);
  printf("edad: %d ", Personas[indexViejo].Edad);
  printf("%d\n", Personas[indexViejo].Activo);
}

int main(int argc, char* argv[])
{

	TVotante Personas[826];
  int opcion = 0;

  while (opcion<5) {
	std::cout << "1. agregar votantes" << '\n';
	std::cout << "2. listar votantes" << '\n';
	std::cout << "3. buscar mas viejo" << '\n';
	std::cout << "4. listar con edad impar" << '\n';
	std::cout << "5. salir" << '\n';
	std::cout << "ingrese una opcion: ";
	cin >> opcion;

	switch (opcion) {
	  case 1 :
		for (int i = 1; i <= 825; i++)
		{
		  Personas[i].Cedula = i;
		  strcpy(Personas[i].Nombre, "nombre");
		  strcpy(Personas[i].Direccion, "direccion");
		  Personas[i].Edad = i;
		  Personas[i].Activo = true;
		}
		break;
	  case 2 :
		ListarVotantes(Personas);
		break;
	  case 3 :
		BuscarViejo(Personas);
		break;
	  case 4 :
		ListarImpares(Personas);
		break;
	}
  }

  return 0;
}*/