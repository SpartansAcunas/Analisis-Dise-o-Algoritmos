#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cctype> 
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h> 
#include <math.h>
#include <sstream>
#include <random>
using namespace std;

typedef struct T_Votante { //Se define la estructura para los votantes
	char cedula[10];
	char codelec[7];
	char sexo;
	char fecha[9];
	char numjun[6];
	char nombre[31];
	char papellido[27];
	char sapellido[27];
	T_Votante* PtrSiguiente;
}*PtrT_Votante;

//Funcion para agregar un votante, recibe como parametro la lista de votantes y la LINEA DE TEXTO del padron electoral
//extrae cada uno de los atributos de la linea y los almacena en un nodo de la lista de votantes
void agregarvotante(PtrT_Votante& ListaV, char agregado[118]) {
	PtrT_Votante Aux = new (T_Votante);
	Aux->PtrSiguiente = ListaV;
	ListaV = Aux;

	for (int ce = 0; ce < 9; ce++) {
		ListaV->cedula[ce] = agregado[ce];
	}
	ListaV->cedula[9] = '\0';

	for (int co = 10; co < 16; co++) {
		ListaV->codelec[co - 10] = agregado[co];
	}
	ListaV->codelec[6] = '\0';

	ListaV->sexo = agregado[17];


	for (int fe = 19; fe < 27; fe++) {
		ListaV->fecha[fe - 19] = agregado[fe];
	}
	ListaV->fecha[8] = '\0';

	for (int nu = 28; nu < 33; nu++) {
		ListaV->numjun[nu - 28] = agregado[nu];
	}
	ListaV->numjun[5] = '\0';

	for (int nom = 34; nom < 64; nom++) {
		ListaV->nombre[nom - 34] = agregado[nom];
	}
	ListaV->nombre[30] = '\0';

	for (int pa = 65; pa < 91; pa++) {
		ListaV->papellido[pa - 65] = agregado[pa];
	}
	ListaV->papellido[26] = '\0';

	for (int sa = 92; sa < 118; sa++) {
		ListaV->sapellido[sa - 92] = agregado[sa];
	}
	ListaV->sapellido[26] = '\0';

}
typedef struct T_Preguntas {
	char cedula[10];
	int Preg1;
	int Preg2;
	int Preg3;
	int Preg4;
	int Preg5;
	T_Preguntas* PtrSiguiente;
}*PtrT_Preguntas;

void inicializarpreguntas(PtrT_Preguntas& ListaP) {
	ListaP = NULL;
}


int random()
{
	int nram;

	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	nram = rand() % 4 + 1;

	return nram;
}
void RealizarEncuesta(PtrT_Votante ListaV, PtrT_Preguntas& ListaP) {
	PtrT_Votante Aux;
	Aux = ListaV;
	while (Aux != NULL) {
		for (int a = 0; a < 9; a++) {
			Aux->cedula[a] = ListaP->cedula[a];
		}
		ListaP->Preg1 = random();
		ListaP->Preg2 = random();
		ListaP->Preg3 = random();
		ListaP->Preg4 = random();
		ListaP->Preg5 = random();
		Aux = Aux->PtrSiguiente;

	}

}

void CargarVotantes(PtrT_Votante& ListaV) {
	int cont = 1;
	time_t inicio, fin;
	inicio = time(NULL);
	FILE* archivo;
	fopen_s(&archivo, "PADRON_COMPLETO.txt", "r");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo");
	}
	else {
		char agregado[118];
		while (fgets(agregado, 118, archivo) != NULL) {
			if (cont % 2 != 0) {
				agregarvotante(ListaV, agregado);
			}
			cont++;
		}
		fclose(archivo);
	}

	fin = time(NULL);
	cout << "----------------------------Padron cargado--------------------------------" << endl;
	printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Padron cargado--------------------------------" << endl;
	system("pause");
}


//Funcion para liberar los votantes en estructuras de memoria dinamica de la lista enlazada hasta dejar la lista en NULL

void LiberarVotantes(PtrT_Votante& ListaV) {
	PtrT_Votante Aux = ListaV;
	time_t inicio, fin;

	inicio = time(NULL);

	while (Aux != NULL) {
		ListaV = ListaV->PtrSiguiente;
		delete(Aux);
		//Globalfree(Aux);
		Aux = ListaV;
	}

	fin = time(NULL);

	cout << "----------------------------Padron liberado--------------------------------" << endl;
	printf("\nLa liberacion del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Padron liberado--------------------------------" << endl;
	system("pause");
}


//Funci�n para inicializar la lista de votantes
void inicializarvotantes(PtrT_Votante& ListaV) {
	ListaV = NULL;
}

void ListarPregunta1(PtrT_Preguntas& Lista)
{
	int O1 = 0, O2 =0, O3 =0, O4= 0;
	PtrT_Preguntas Aux;
	Aux = Lista;
	while (Aux != NULL) {
		if (Aux->Preg1 == 1) {
			Aux = Aux->PtrSiguiente;
			O1 = O1++;
		}
		if (Aux->Preg1 == 2) {
			Aux = Aux->PtrSiguiente;
		}
		if (Aux->Preg1 == 3) {
			Aux = Aux->PtrSiguiente;
		}
		else
			O4 = O4++;
	}
	cout << "Los resultados de la pregunta 1 son"<<endl;
	cout << "Opcion 1" << O1 << endl;
	cout << "Opcion 2" << O2 << endl;
	cout << "Opcion 3" << O3 << endl;
	cout << "Opcion 4" << O4 << endl;
}
void ListarPregunta2(PtrT_Preguntas& Lista)
{
	int O1 = 0, O2 = 0, O3 = 0, O4 = 0;
	PtrT_Preguntas Aux;
	Aux = Lista;
	while (Aux != NULL) {
		if (Aux->Preg2 == 1) {
			Aux = Aux->PtrSiguiente;
			O1 = O1++;
		}
		if (Aux->Preg2 == 2) {
			Aux = Aux->PtrSiguiente;
		}
		if (Aux->Preg2 == 3) {
			Aux = Aux->PtrSiguiente;
		}
		else
			O4 = O4++;
	}
	cout << "Los resultados de la pregunta 2 son"<<endl;
	cout << "Opcion 1" << O1 << endl;
	cout << "Opcion 2" << O2 << endl;
	cout << "Opcion 3" << O3 << endl;
	cout << "Opcion 4" << O4 << endl;
}
void ListarPregunta3(PtrT_Preguntas& Lista)
{
	int O1 = 0, O2 = 0, O3 = 0, O4 = 0;
	PtrT_Preguntas Aux;
	Aux = Lista;
	while (Aux != NULL) {
		if (Aux->Preg3 == 1) {
			Aux = Aux->PtrSiguiente;
			O1 = O1++;
		}
		if (Aux->Preg3 == 2) {
			Aux = Aux->PtrSiguiente;
		}
		if (Aux->Preg3 == 3) {
			Aux = Aux->PtrSiguiente;
		}
		else
			O4 = O4++;
	}
	cout << "Los resultados de la pregunta 3 son" <<endl;
	cout << "Opcion 1" << O1 << endl;
	cout << "Opcion 2" << O2 << endl;
	cout << "Opcion 3" << O3 << endl;
	cout << "Opcion 4" << O4 << endl;
}
void ListarPregunta4(PtrT_Preguntas& Lista)
{
	int O1 = 0, O2 = 0, O3 = 0, O4 = 0;
	PtrT_Preguntas Aux;
	Aux = Lista;
	while (Aux != NULL) {
		if (Aux->Preg4 == 1) {
			Aux = Aux->PtrSiguiente;
			O1 = O1++;
		}
		if (Aux->Preg4 == 2) {
			Aux = Aux->PtrSiguiente;
		}
		if (Aux->Preg4 == 3) {
			Aux = Aux->PtrSiguiente;
		}
		else
			O4 = O4++;
	}
	cout << "Los resultados de la pregunta 4 son"<<endl;
	cout << "Opcion 1" << O1 << endl;
	cout << "Opcion 2" << O2 << endl;
	cout << "Opcion 3" << O3 << endl;
	cout << "Opcion 4" << O4 << endl;
}
void ListarPregunta5(PtrT_Preguntas& Lista)
{
	int O1 = 0, O2 = 0, O3 = 0, O4 = 0;
	PtrT_Preguntas Aux;
	Aux = Lista;
	while (Aux != NULL) {
		if (Aux->Preg5 == 1) {
			Aux = Aux->PtrSiguiente;
			O1 = O1++;
		}
		if (Aux->Preg5 == 2) {
			Aux = Aux->PtrSiguiente;
		}
		if (Aux->Preg5 == 3) {
			Aux = Aux->PtrSiguiente;
		}
		else
			O4 = O4++;
	}
	cout << "Los resultados de la pregunta 5 son" << endl;
	cout << "Opcion 1" << O1 << endl;
	cout << "Opcion 2" << O2 << endl;
	cout << "Opcion 3" << O3 << endl;
	cout << "Opcion 4" << O4 << endl;
}

void LiberarEncuesta(PtrT_Preguntas& ListaP) {
	PtrT_Preguntas Aux = ListaP;
	time_t inicio, fin;

	inicio = time(NULL);

	while (Aux != NULL) {
		ListaP = ListaP->PtrSiguiente;
		delete(Aux);
		Aux = ListaP;
	}
}
typedef struct T_Codigo{ //Se define la estructura para los votantes
	char codelec[7];
	char lugar[111];
	T_Codigo* PtrSiguiente;
}*PtrT_Codigo;


void agregarlugar(PtrT_Codigo& ListaL, char agregado[118]) {
	PtrT_Codigo Aux = new (T_Codigo);
	Aux->PtrSiguiente = ListaL;
	ListaL = Aux;

	for (int ce = 0; ce < 6; ce++) {
		ListaL->codelec[ce] = agregado[ce];
	}
	ListaL->codelec[9] = '\0';

	for (int co = 7; co < 111; co++) {
		ListaL->lugar[co - 7] = agregado[co];
	}
}
void CargarDistelec(PtrT_Codigo& ListaL) {
	int cont = 1;
	time_t inicio, fin;
	inicio = time(NULL);
	FILE* archivo;
	fopen_s(&archivo, "Distelec.txt", "r");
	if (NULL == archivo) {
		printf("No se pudo abrir el archivo");
	}
	else {
		char agregado[118];
		while (fgets(agregado, 118, archivo) != NULL) {
			if (cont % 2 != 0) {
				agregarlugar(ListaL, agregado);
			}
			cont++;
		}
		fclose(archivo);
	}

	fin = time(NULL);
}
void LiberarDistelec(PtrT_Codigo& ListaL) {
	PtrT_Codigo Aux = ListaL;
	time_t inicio, fin;

	inicio = time(NULL);

	while (Aux != NULL) {
		ListaL = ListaL->PtrSiguiente;
		delete(Aux);
		//Globalfree(Aux);
		Aux = ListaL;
	}

	fin = time(NULL);
}
void inicializarlugares(PtrT_Codigo& ListaL) {
	ListaL = NULL;
}
typedef struct TPregunta {
	int preg;
	TPregunta* Anterior;
	TPregunta* Siguiente;
}X;
typedef TPregunta* PtrTPregunta;

void InicializarInventario(PtrTPregunta& Lista) {
	Lista = NULL;
}

PtrTPregunta CrearArticulo(int npregunta) {
	PtrTPregunta Nuevo = new(TPregunta);
	char buffer[5];

	Nuevo->preg = npregunta;
	Nuevo->Anterior = NULL;
	Nuevo->Siguiente = NULL;
	return Nuevo;
}


void AgregarInicioEncuesta(PtrTPregunta& Lista, PtrTPregunta& Nuevo) {


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
void Listar_Inicio_a_Final(PtrTPregunta& Lista) {
	PtrTPregunta Aux;
	Aux = Lista;
	while (Aux != NULL) {
		cout << Aux->preg << endl;
		Aux = Aux->Siguiente;
	}
	system("pause");
}


void DestruirInventario(PtrTPregunta& Lista)
{
	PtrTPregunta Aux;
	Aux = Lista;
	while (Aux != NULL)
	{
		Lista = Lista->Siguiente;
		delete(Aux);
		Aux = Lista;
	}
}
void borrarPregunta(PtrTPregunta& Lista, int cual) {
	PtrTPregunta Aux = Lista;
	PtrTPregunta kill;
	bool a = true;
	int i = 0;
	while (a) {
		if (i < cual, i++) {
			Aux = Aux->Siguiente;
		}

		else {
			kill = Aux->Siguiente;
			kill->Siguiente = NULL; delete(kill);
			break;
		}
	}
}


void Cuestionario() {

	PtrTPregunta Nuevo;
	PtrTPregunta Preguntas;


	InicializarInventario(Preguntas);


	bool menu = true; // Booleano utilizado para el menu
	int m;
	while (menu) {
		system("CLS");
		cout << "MENU DE ENCUESTAS" << endl << endl; // Imprime el menu

		cout << "1. Mostrar encuesta" << endl;
		cout << "2. Agregar pregunta" << endl;
		cout << "3. Borrar encuesta" << endl;
		cout << "4. Salir" << endl;
		cin >> m; // Solicita una opcion

		switch (m) {
		case '1': {
			system("CLS");
			cout << "Estas son todas las preguntas ingresadas" << endl << endl;
			Listar_Inicio_a_Final(Preguntas);;
			system("pause");
			break;
		}

		case '2': {
			system("CLS");
			cout << "Ingrese la nueva pregunta que desea agregar" << endl;
			int a;
			cin >> a;
			Nuevo = CrearArticulo(a);
			AgregarInicioEncuesta(Preguntas, Nuevo);
			cout << endl << "Pregunta agregada a la encuesta" << endl;
			system("pause");
			break;
		}

		case '3': {
			system("CLS");
			int c;
			cout << "¿Cual pregunta desea borrar?" << endl;
			cin >> c;
			borrarPregunta(Preguntas, c);
			cout << endl << "La pregunta fue borrada" << endl;
			system("pause");
			break;
		}

		case '4': {
			menu = false;
			DestruirInventario(Preguntas);
			break;
		}
		}
	}
}
	
void main() {
	bool realizado = false;
	bool ciclo = true;
	int opcion = 0;
	PtrT_Votante ListaV;
	PtrT_Preguntas ListaP;
	PtrT_Codigo ListaL;
	inicializarpreguntas(ListaP);
	inicializarvotantes(ListaV);
	inicializarlugares(ListaL);
	CargarDistelec(ListaL);
	cout << "Por favor espere mientras se carga el Padron" << endl;
	CargarVotantes(ListaV);
	RealizarEncuesta(ListaV, ListaP);
	ListarPregunta1(ListaP);
	ListarPregunta2(ListaP);
	ListarPregunta3(ListaP);
	ListarPregunta4(ListaP);
	ListarPregunta5(ListaP);
	Cuestionario();
	LiberarVotantes(ListaV);
	LiberarEncuesta(ListaP);
	LiberarDistelec(ListaL);

	cout << "Finalizado" << endl;

	system("pause");

}