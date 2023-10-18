#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cctype>  // Se necesita para clasificar y transformar caracteres individuales
#include <cstdlib> // Libreria que permite el manejo de memoria dinamica,funciones de numeros aleatorios ,etc
#include <string.h> // Uso de funciones para manipular strings y arreglos en C
#include <stdlib.h> // Archivo de cabecera para la libreria cstdlib
#include <time.h> // Para el uso de funciones  que utilizan el reloj interno del OS
#include <windows.h> // Archivo para la creacion y manejo de ventanas
#include <math.h> // Paquete para operaciones matematicas comunes
#include <sstream> //Operaciones con strings
#include <random> // Uso de numeros aleatorios
using namespace std;

// Se define un nuevo tipo de dato en forma de estructura
typedef struct T_Votante {
	char cedula[10]; // Numero de cedula
	char codelec[7]; // Codigo electoral
	char sexo; // Sexo del votante
	char fecha[9]; // Fecha de vencimiento de la cedula de identidad
	char numjun[6]; // Numero de junta
	char nombre[31]; // Nombre de la persona
	char papellido[27]; // Primer apellido
	char sapellido[27]; // Segundo apellido
	T_Votante * PtrSiguiente; // Puntero para apuntar a la direccion del votante siguiente y enlazarlo
}*PtrT_Votante;

//Funcion para agregar un votante, recibe como parametro la lista de votantes y la LINEA DE TEXTO del padron electoral
//extrae cada uno de los atributos de la linea y los almacena en un nodo de la lista de votantes
void agregarvotante(PtrT_Votante &ListaV, char agregado[118]) {
	PtrT_Votante Aux = new (T_Votante); // Se solicita un nuevo espacio en memoria y se almacena en Aux
	Aux->PtrSiguiente = ListaV; // El dato PtrSiguiente dentro de Aux almacena la direccion en memoria del inicio de la ListaV
	ListaV = Aux; //Aux  toma la direccion de la ListaV

	for (int ce = 0; ce < 9; ce++) { //  Recorre la cedula de los votantes, digito por digito

		ListaV->cedula[ce] = agregado[ce]; // Los digitos de la cedula copiados, se agregan al dato cedula del votante
	}
	ListaV->cedula[9] = '\0'; // Añade un final de string

	for (int co = 10; co < 16; co++) { // Reecorre el codigo electoral del votante

		ListaV->codelec[co - 10] = agregado[co]; // El codigo electoral del votante se añade a codelec, digito por digito
	}
	ListaV->codelec[6] = '\0'; // Añade un final de string

	ListaV->sexo = agregado[17]; // Añade el sexo del votante al dato sexo en la estructura


	for (int fe = 19; fe < 27; fe++) { // Recorre la fecha de vencimiento de la cedula de los votantes

		ListaV->fecha[fe - 19] = agregado[fe]; // Añade a fecha la fecha copiada del archivo, digito por digito
	}
	ListaV->fecha[8] = '\0'; // Añade un final de string

	for (int nu = 28; nu < 33; nu++) { // Recorre el numero de junta del votante

		ListaV->numjun[nu - 28] = agregado[nu]; // Añade el numero de junta copiado del archivo
	}
	ListaV->numjun[5] = '\0';// Añade un final de string

	for (int nom = 34; nom < 64; nom++) // Recorrer el nombre del votante
	{
		ListaV->nombre[nom - 34] = agregado[nom]; // Añade el nombre copiado del archivo al dato nombre de la estrucutra
	}
	ListaV->nombre[30] = '\0';// Añade un final de string

	for (int pa = 65; pa < 91; pa++) // Recorre el primer apellido del votante
	{
		ListaV->papellido[pa - 65] = agregado[pa]; // Añade el primer apellido a la estructura
	}
	ListaV->papellido[26] = '\0';// Añade un final de string

	for (int sa = 92; sa < 118; sa++) // Recorre el segundo apellido del votante
	{
		ListaV->sapellido[sa - 92] = agregado[sa]; // Añade el segundo apellido a la estructura
	}
	ListaV->sapellido[26] = '\0'; // Añade un final de string

}



//Funcion para cargar los votantes, se encarga de tomar cada una de las lineas
//directo del archivo de texto y enviarlo a la funcion encargada de extraer cada uno
// de los datos e incorporarlos en un nodo de la lista.
void CargarVotantes(PtrT_Votante &ListaV) {
	int cont = 1; // Se inicia un contador
	time_t inicio, fin; //Tipo de funcion aritmetica capaz de representar tiempos
	inicio = time(NULL); // Se toma como tiempo inicial la hora actual del sistema
	FILE *archivo; // Puntero que almacena la direccion del archivo en la memoria secundaria
	fopen_s(&archivo, "PADRON_COMPLETO.txt", "r"); // Abre el archivo Padron_completo en modo de lectura
	if (NULL == archivo) // Si no encuentra el archivo
	{
		printf("No se pudo abrir el archivo"); // Imprime un mensaje de error
	}
	else // Si encuentra el archivo
	{
		char agregado[119]; // Se define una variable tipo caracter
		while (fgets(agregado, 119, archivo) != NULL) // Mientras no termina de recorrer la linea completa con los datos del votante
		{
			if (cont % 2 != 0) // 
			{
				agregarvotante(ListaV, agregado); // Usa la funcion para agregar el votante al archivo logico
			}
			cont++; // Incrementa el contador
		}
		fclose(archivo); // Cierra el archivo si sobreescribir datos
	}

	fin = time(NULL); // Se toma la hora del sistema como tiempo final de carga
	cout << "----------------------------Padron cargado--------------------------------" << endl;
	printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio)); // Imprime el timpo que tardo en cargar el padron como la diferencia entre fin e inicio
	cout << "----------------------------Padron cargado--------------------------------" << endl;
	system("pause"); // Pausa el sistema
}


//Funcion para liberar los votantes en estructuras de memoria dinamica de la lista enlazada hasta dejar la lista en NULL

void LiberarVotantes(PtrT_Votante &ListaV)
{
	PtrT_Votante Aux = ListaV; // Puntero para almacenar la direccion en memoria del primer votante en la lista
	time_t inicio, fin; // Funcion para medir el tiempo que tarda en borrar

	inicio = time(NULL); // Tiempo inicial, igual a la hora que inicia el programa

	while (Aux != NULL) // Mientras la direccion almacenada en Aux no sea nula
	{
		ListaV = ListaV->PtrSiguiente; // La nueva direccion de lista es la que se almacena en PtrSiguiente del conjunto
		delete(Aux); // Borra de la memoria el votante contenido en la direccion a la que apunta Aux
					 //Globalfree(Aux);//otra forma de borrar
		Aux = ListaV; // Aux almacena la direccion del siguiente votante
	}

	fin = time(NULL); // Tiempo final, igual a la hora en que finaliza la ejecucion del programa

	cout << "----------------------------Padron liberado--------------------------------" << endl;
	printf("\nLa liberacion del padron ha tardado : %f segundos.\n", difftime(fin, inicio)); // Imprime el tiempo que tardo en borrar el padron como la diferencia de los tiempos final e inicial
	cout << "----------------------------Padron liberado--------------------------------" << endl;
	system("pause");
}


//Funcion para inicializar la lista de votantes
void inicializarvotantes(PtrT_Votante &ListaV)
{
	ListaV = NULL; // Asigna la direccion de NULL a la lista
}

// Puntero a funcion para buscar un votante por medio de la cedula
PtrT_Votante BuscarVotante(PtrT_Votante &Lista, char cual[9])
{
	bool encontro = false; // Declaracion de variable tipo bool
	PtrT_Votante Aux; // Puntero a T_Votante para almacenar la direccion en memoria del comienzo del arreglo
	Aux = Lista; // Aux toma el valor de direccion donde comienza el arreglo

	while ((!encontro == true) && (Aux != NULL)) // Mientras no encuentre al votante y la direccion almacenada en Aux no sea -1:-1
	{
		// strncmp compara los caracteres del primer parametro con los del segundo parametro. El tercero es el maximo numero de caracteres a comparar
		if (strncmp(Aux->cedula, cual, 9) == 0) // Si todos los caracteres en ambas cedulas son identicos 
			encontro = true; // Define encontro como true
		else // Si no lo ha encontrado
			Aux = Aux->PtrSiguiente; // Aux apunta a la direccion del siguiente votante
	}
	return Aux; // Regesa los datos  encontrado
}

// Funcion para buscar votante por nombre, recibe como parametros el nombre, y los apellidos
PtrT_Votante BuscarNombre(PtrT_Votante &Lista, char Nombre[], char pa[], char sa[])
{
	bool encontro = false; // Declaracion de variable booleana
	PtrT_Votante Aux; // Declaracion de puntero
	Aux = Lista; // Aux almacena la direccion de la lista
	while ((!encontro == true) && (Aux != NULL)) // Mientras encontro sea falso y Aux no apunte a NULL
	{
		// Se compara el nombre del votante almacenado en el arreglo con el nombre que se quiere buscar
		// Si el nombre y los apellidos almacenados son iguales al menos hasta la longitud de lo buscado, se cumple la condicion
		if ((strncmp(Aux->nombre, Nombre, strlen(Nombre)) == 0) && (strncmp(Aux->papellido, pa, strlen(pa)) == 0) && (strncmp(Aux->sapellido, sa, strlen(sa)) == 0))
		{
			encontro = true; // Se asigna true a encontro
		}
		else // Si no lo encuentra
			Aux = Aux->PtrSiguiente; // Apunta al siguiente votante
	}
	return Aux; // Retorna la direccion obtenida
}

// Funcion principal
void main()
{
	// Declaracion de variables
	bool realizado = false;
	bool ciclo = true;
	int opcion = 0;

	PtrT_Votante ListaV; // Puntero a T_Votante para almacenar la direccion del primer miembro del arreglo
	inicializarvotantes(ListaV); // Llama la funcion para solicitar un espacio en la memoria
	cout << "Por favor espere mientras se carga el Padron" << endl;
	CargarVotantes(ListaV); // Comienza a cargar el padron en el arreglo
	char buscado[] = "207550813"; // Variable tipo char para buscar el numero de cedula introducido
	PtrT_Votante Encontrado = NULL; // Definicion de un puntero para almacenar la direccion del votante buscado
	Encontrado = BuscarVotante(ListaV, buscado); // Busca el votante y almacena su direccion
	if (Encontrado != NULL) // Si encuentra al votante en la memoria 
	{
		cout << endl << "Encontre al Votante!! " << endl << endl; // Imprime el mensaje de que lo encontro

		cout << "Cedula: " << Encontrado->cedula << endl; // Imprime el numero de cedula
		cout << "Nombre: " << Encontrado->nombre << endl; // Imprime el nombre
		cout << "Primer Apellido: " << Encontrado->papellido << endl; // Imprime el primer apellido
		cout << "Segundo Apellido: " << Encontrado->sapellido << endl; // Imprime el segundo apellido
		cout << "Sexo: " << Encontrado->sexo << endl; // Imprime el sexo, 1 para hombre, 2 para mujer
		cout << "Fecha: " << Encontrado->fecha << endl; // Imprime la fecha
		cout << "Codigo Electoral:  " << Encontrado->codelec << endl; // Imprime el codigo electoral
		cout << "Numero Junta: " << Encontrado->numjun << endl << endl; // Imprime el numero de junta
	}
	else // Si la direccion de Encontrado sigue siendo la de NULL
		cout << " No se encontro al votante !!! " << endl; // Imprime el mensaje de no encontrado

	//********** Buscar por nombre *****************
	char nombre[] = "VICTOR MANUEL"; // Nombre que se quiere buscar
	char primer[] = "GARRO"; // Primer apellido
	char segundo[] = "ABARCA"; // Segundo apellido
	PtrT_Votante Encontrado_2 = NULL; // Se declara un puntero
	Encontrado_2 = BuscarNombre(ListaV, nombre, primer, segundo); // Se llama a la funcion para buscar por nombre
	if (Encontrado_2 != NULL) // Si obtiene una direccion distinta de NULL
	{
		cout << endl << "****** Busqueda de votante por nombre *******" << endl;
		cout << endl << "Encontre el nombre del Votante!! " << endl << endl; // Imprime el mensaje de que lo encontro
		cout << "Cedula: " << Encontrado_2->cedula << endl; // Imprime el numero de cedula
		cout << "Nombre: " << Encontrado_2->nombre << endl; // Imprime el nombre
		cout << "Primer Apellido: " << Encontrado_2->papellido << endl; // Imprime el primer apellido
		cout << "Segundo Apellido: " << Encontrado_2->sapellido << endl; // Imprime el segundo apellido
		cout << "Sexo: " << Encontrado_2->sexo << endl; // Imprime el sexo, 1 para hombre, 2 para mujer
		cout << "Fecha: " << Encontrado_2->fecha << endl; // Imprime la fecha
		cout << "Codigo Electoral:  " << Encontrado_2->codelec << endl; // Imprime el codigo electoral
		cout << "Numero Junta: " << Encontrado_2->numjun << endl; // Imprime el numero de junta
	}
	else // Si la direccion de Encontrado sigue siendo la de NULL
		cout << endl << "No se encontro el nombre !!! " << endl; // Imprime el mensaje de no encontrado


	LiberarVotantes(ListaV); // Libera los datos de la memoria

	cout << "Finalizado" << endl;

	system("pause"); // Pausa el sistema
}

/*Por favor espere mientras se carga el Padron
----------------------------Padron cargado--------------------------------

El cargado del padron ha tardado : 18.000000 segundos.
----------------------------Padron cargado--------------------------------
Presione una tecla para continuar . . .

Encontre al Votante!!

Cedula: 207550813
Nombre: ALFREDO
Primer Apellido: ACUÐA
Segundo Apellido: CHACON
Sexo: 1
Fecha: 20240703
Codigo Electoral:  206004
Numero Junta: 02390


****** Busqueda de votante por nombre *******

Encontre el nombre del Votante!!

Cedula: 107490737
Nombre: VICTOR MANUEL
Primer Apellido: GARRO
Segundo Apellido: ABARCA
Sexo: 1
Fecha: 20300204
Codigo Electoral:  101016
Numero Junta: 00022
----------------------------Padron liberado--------------------------------

La liberacion del padron ha tardado : 1.000000 segundos.
----------------------------Padron liberado--------------------------------
Presione una tecla para continuar . . .*/