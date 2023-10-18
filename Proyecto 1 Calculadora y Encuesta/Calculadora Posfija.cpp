// Calculadora Posfija.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.


// Este programa convierte expresiones de infija o posfija
// Ademas calcula expresiones ingresadas en posfijo
//

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <math.h>
#define MAX 100 // Maximo numero de caracteres en el string ingresado
using namespace std;

// Estructura de datos donde se almacena cada caracter para introducirlo en una lista 
typedef struct Operador {
	char caracter; // Almacena el caracter
	int prioridad; // Almacena el valor de prioridad de operacion. Es 0 para Operandos
	float valor; // Almacena el valor que se les da a los Operandos
	bool existe; // Si ya se le dio valor al Operando, no lo vuelve a solicitar
	Operador *Siguiente; // Puntero al siguiente en la lista
}*PtrOperador;

// ************************* FUNCIONES DE LISTAS *****************************

// Funcion para eliminar la pila de caracteres
void DestruirLista(PtrOperador &Lista) {
	PtrOperador Aux; // Puntero Auxiliar
	Aux = Lista; // Aux se iguala a pila para recorrerla
	while (Lista != NULL) { // Mientras pila tenga algun dato
		Lista = Lista->Siguiente; // Pila se iguala al siguiente
		delete(Aux); // Se borra el auxiliar
		Aux = Lista; // Aux se iguala al primero de la lista
	}
}

// Funcion para crear un nuevo caracter de tipo puntero a Operador
PtrOperador CrearCaracter(char c, int p) {
	PtrOperador Nuevo = new(Operador); // Solicita espacio en memoria
	Nuevo->caracter = c; // Caracter se iguala al caracter ingresado
	Nuevo->prioridad = p; // Prioridad se iguala a la del caracter ingresado
	Nuevo->existe = false; // Se define existe como falso
	Nuevo->Siguiente = NULL; // Siguiente apunta a NULL

	return Nuevo; // Se returna el nuevo dato
}

// Funcion para agregar un nuevo dato al inicio de un lista de Operadores
void AgregarInicioLista(PtrOperador &Lista, PtrOperador &Nuevo) {
	Nuevo->Siguiente = Lista; // El puntero siguiente en Nuevo se iguala al primero de Lista
	Lista = Nuevo; // Lista comienza en Nuevo
}

// Funcion para agregar un nuevo dato al final de un lista de Operadores
void AgregarFinalLista(PtrOperador &Lista, PtrOperador Nuevo) {
	PtrOperador Char; // Se declara el puntero a Operador Char
	Char = Lista; // Char se iguala a Lista

	if (Char != NULL) { // Si Char es distinto de NULL
		while (Char->Siguiente != NULL) { // Mientras el puntero Siguiente de Char no apunte a NULL
			Char = Char->Siguiente; // Char se iguala a Siguiente
		}
		Char->Siguiente = Nuevo; // Al terminar, el puntero Siguiente de Char se igula a Nuevo
	}
	else { // Si Char es NULL
		Lista = Nuevo; // La lista se iguala a Nuevo
	}
}

// Funcion para listar la pila
void MostrarLista(PtrOperador Lista) {
	PtrOperador Char; // Se declara el puntero Char
	Char = Lista; // Char se iguala a la Lista

	while (Char != NULL) { // Mientras Char sea distinto de NULL
		printf("%c", Char->caracter); // Imprime el caracter de Char
		Char = Char->Siguiente; // Char apunta a Siguiente
	}
	printf("\n");// Imprime Fin de Linea
}

// ********************** FUNCIONES DE PILAS *****************************

// Funcion para introducir un nuevo miembro en la pila
void Push(PtrOperador &pila, PtrOperador Nuevo) {
	AgregarInicioLista(pila, Nuevo); // Llama la funcion para agregar al inicio de la pila
}
// Funcion para ver quien es el miembro del inicio de la pila
PtrOperador Top(PtrOperador &pila) {
	return pila; // Regresa el primer miembro de la pila
}
// Funcion para sacar de la pila el primer miembro
PtrOperador Pop(PtrOperador &pila) {
	PtrOperador Aux = pila; // Declara el puntero auxiliar y lo iguala al primero de la pila
	if (Aux == NULL) { // Si la pila esta vacia
		return NULL; // Devuelve NULL
	}
	else if (pila->Siguiente != NULL) { // Si la pila tiene mas de un dato
		pila = pila->Siguiente; // Se iguala el puntero de pila al puntero siguiente del primero
		Aux->Siguiente = NULL; // El auxiliar siguiente se igula a NULL, separandolo de la pila
	}
	else { // Si pila solo tiene un dato
		pila = NULL; // Se inicia la pila en NULL, dejandola vacia
		Aux->Siguiente = NULL; // El auxiliar siguiente se igula a NULL, separandolo de la pila
	}
	return Aux; // Se regresa el Auxiliar
}

// Funcion que evalua cada caracter en la lista y le da orden de prioridad
void anadirPrioridad(PtrOperador &Nuevo) {

	if ((Nuevo->caracter >= 'A' && Nuevo->caracter <= 'Z') || (Nuevo->caracter >= 'a' && Nuevo->caracter <= 'z')) { // Si es un letra
		Nuevo->prioridad = 0; // La prioridad es 0
	}
	else if (Nuevo->caracter == ')') { // Si es el cierre de un parentesis, la priridad es 1
		Nuevo->prioridad = 1;
	}
	else if (Nuevo->caracter == '^') { // Si es un exponente, la prioridad es 2
		Nuevo->prioridad = 2;
	}
	else if ((Nuevo->caracter == '*') || (Nuevo->caracter == '/')) { // Si es un producto o una division, la prioridad es 3
		Nuevo->prioridad = 3;
	}
	else if ((Nuevo->caracter == '+') || (Nuevo->caracter == '-')) { // Si es una suma o resta, la prioridad es 4
		Nuevo->prioridad = 4;
	}
	else if (Nuevo->caracter == '(') { // Si la apertura de un parentesis, la prioridad es 5
		Nuevo->prioridad = 5;
	}
	else if ((Nuevo->caracter >= '0' && Nuevo->caracter <= '9')) { // Si es un numero, la prioridad es 6
		Nuevo->prioridad = 6;
	}
	else { // Si es un espacio
		Nuevo->prioridad = 7;
	}
}

// Funcion que toma el string ingresado y lo transforma en una lista enlazada del tipo Operador
void CrearListaEnlazada(PtrOperador &pila, char Entrada[MAX]) { // Entrada es el string donde se ingresa la expresion desde el teclado
	pila = NULL; // Inicializa la pila
	PtrOperador Nuevo; // Puntero Auxiliar

	for (int i = 0; i < MAX; i++) { // Ciclo desde 0 hasta MAX

		if (Entrada[i] == '\0') { // Si llega al final de la cadena
			break; // Finaliza el ciclo
		}

		else {
			Nuevo = CrearCaracter(Entrada[i], 0); // Se añade 0 para crear el caracter pero se cambia en la siguiente linea
			anadirPrioridad(Nuevo); // Añade la prioridad a los caracteres
			AgregarFinalLista(pila, Nuevo); // Lo agrega al final de la lista
		}
	}
}

// Funcion para convertir la lista de infija a una lista en posfija
void conversion(PtrOperador Infija, PtrOperador &Posfija) {
	PtrOperador Aux, Aux2, PilaOperadores, Nuevo; // Se definen dos auxiliares, un puntero para crear nuevos datos y una pila de operadores
	PilaOperadores = NULL; // Se inicia la pila en NULL
	Aux = Infija; // Aux se iguala a la lista de infija

	while (Aux != NULL) { // Mientras Aux sea distinto de NULL
		Nuevo = CrearCaracter(Aux->caracter, Aux->prioridad); // Se crea un nuevo caracter con los datos de Aux
		if (Aux->prioridad == 0) { // Si es una letra
			AgregarFinalLista(Posfija, Nuevo); // Se agrega a la lista de posfija
		}

		else if (Aux->prioridad == 7) { // Si es un espacio en blanco, se omite
			Aux = Aux->Siguiente;
			continue;
		}

		else if (Aux->prioridad == 6) { // Si es un numero
			AgregarFinalLista(Posfija, Nuevo); // Se agrega a la lista de posfija
			if (((Aux->Siguiente != NULL) && (Aux->Siguiente->prioridad != 6)) || (Aux->Siguiente == NULL)) { // Si no es el ultimo de la lista y el siguiente no es un numero
				Nuevo = CrearCaracter(' ', 7); // Se crea un espacio en blanco con prioridad 7
				AgregarFinalLista(Posfija, Nuevo); // Se añade al final de la lista
			}
		}

		else if (Aux->prioridad == 1) { // Si es el cierre de un parentesis
			Aux2 = Pop(PilaOperadores); // Se hace Pop al primero de la lista de operadores
			while ((Aux2->caracter != '(') && (Aux2 != NULL)) { // Mientras no llegue a la apertura de parentesis
				Nuevo = CrearCaracter(Aux2->caracter, Aux2->prioridad); // Se crea un nuevo dato con Aux2
				AgregarFinalLista(Posfija, Nuevo); // Se agrega al final de la lista posfija
				Aux2 = Pop(PilaOperadores); // Se hace Pop en la pila de operadores
			}
		}

		else if ((Aux->caracter == '(') && (Aux->Siguiente->caracter == '-')) { // Si es un numero negativo
			Aux = Aux->Siguiente->Siguiente; // Aux es el primer numero
			Nuevo = CrearCaracter('-', 6); // Crea un caracter con menos indicando que es negativo
			AgregarFinalLista(Posfija, Nuevo); // Agrega el menos a la lista

			while (Aux->caracter != ')') { // Mientras no llegue al final del parentesis
				Nuevo = CrearCaracter(Aux->caracter, 6); // Crea un nuevo caracter con el caracter de Aux
				AgregarFinalLista(Posfija, Nuevo); // Añade el caracter al final de la lista posfija
				Aux = Aux->Siguiente; // Aux apunta a siguiente
			}
			Nuevo = CrearCaracter(' ', 7); // Agrega un espacio en blanco al final
			AgregarFinalLista(Posfija, Nuevo);
		}

		else { // Si es un operador
			Aux2 = Top(PilaOperadores); // Aux2 toma el valor del primero de la pila de operadores
			if (Aux2 == NULL) { // Si la pila esta vacia
				Push(PilaOperadores, Nuevo); // Agrega el nuevo dato a la pila
			}

			// Si la prioridad de Aux es menor o igual a la del Top de la pila de operadores y no es un parentesis abierto
			else if ((Aux->prioridad >= Aux2->prioridad) && (Aux->prioridad != 5)) {
				Aux2 = Pop(PilaOperadores); // Elimina el primero de la pila de operadores
				AgregarFinalLista(Posfija, CrearCaracter(Aux2->caracter, Aux2->prioridad)); // Lo agrega al final de la lista posfija
				Aux2 = Top(PilaOperadores);

				if (Aux2 != NULL) { // Si hay mas operadores en la pila
					Aux2 = Pop(PilaOperadores); // Elimina el primero de la pila
					AgregarFinalLista(Posfija, CrearCaracter(Aux2->caracter, Aux2->prioridad)); // Lo agrega al final de la lista posfija
				}
				Push(PilaOperadores, CrearCaracter(Aux->caracter, Aux->prioridad)); // Agrega el operador de Aux a la pila de operadores
			}

			else { // Si la prioridad es mayor
				Push(PilaOperadores, Nuevo); // Agrega el operador al inicio de la pila
			}
		}
		Aux = Aux->Siguiente; // Aux apunta al siguiente
	}
	// Al terminar el ciclo, debe agregar los operadores restantes de la pila a la expresion
	Aux2 = Top(PilaOperadores); // Aux2 se iguala al primero de la pila

	while (Aux2 != NULL) { // Si la pila no esta vacia
		Aux2 = Pop(PilaOperadores); // Elimina el primero de a pila
		AgregarFinalLista(Posfija, CrearCaracter(Aux2->caracter, Aux2->prioridad)); // Lo agrega al final de la lista de posfija
		Aux2 = Top(PilaOperadores); // Aux2 se iguala al primero de la pila
	}
	DestruirLista(PilaOperadores); // Destruye la pila de operadores
}

// Funcion para resolver la lista estando en expresion posfija
PtrOperador resolucion(PtrOperador &Posfija) {
	PtrOperador Aux, Aux2, PilaResolucion, Nuevo; // Se definen dos auxiliares, un puntero para crear nuevos datos y una pila de operadores
	PilaResolucion = NULL; // La pila de operadores se inicia en NULL
	Aux = Posfija; // Aux se igual a pila
	float a, b; // Se declaran dos flotantes para añadir valor a los caracteres

	while (Aux != NULL) { // Mientras Auxiliar no sea NULL
		if (Aux->prioridad == 0) { // Si es una letra 

			if (!Aux->existe) { // Si el caracter no se ha declarado como que ya existe
				printf("Ingrese el valor de %c: \n", Aux->caracter); // Se soliclita darle un valor a la letra
				cin >> Aux->valor; // Se ingresa el valor
				Aux->existe = true; // Se define como existente para no volver a solocitar el valor
				Aux2 = Aux->Siguiente; // Aux2 se iguala al siguiente de la lista posfija

				while (Aux2 != NULL) { // Mientras Aux2 no sea NULL
					if (Aux2->caracter == Aux->caracter) { // Si el caracter de Aux2 es igual al de Aux (La letra esta repetida en la lista)
						Aux2->valor = Aux->valor; // Se le añade el mismo valor
						Aux2->existe = true; // Se declara como existente
					}
					Aux2 = Aux2->Siguiente; // Aux2 apunta al siguiente
				}
			}
		}

		else if (Aux->prioridad == 6) { // Si es un numero
			Aux->valor = Aux->caracter - 48; // Se le da el valor del mismo
		}
		Aux = Aux->Siguiente; // Aux apunta a siguiente
	}
	// Despues de darles valor a los caracteres

	Aux = Posfija; // Aux se vuelve a iniciar en la lista posfija
	while (Aux != NULL) { // Mientras no sea NULL
		if (Aux->prioridad == 0) { // Si es una letra
			Nuevo = CrearCaracter(Aux->caracter, 0); // Crea un nuevo caracter con la misma letra
			Nuevo->valor = Aux->valor; // Le asigna el mismo valor
			Push(PilaResolucion, Nuevo); // Lo agrega en la pila de resolucion
		}

		else if (Aux->prioridad == 6) { // Si es un numero
			Nuevo = CrearCaracter(Aux->caracter, 6); // Crea un nuevo caracter con el mismo numero
			Nuevo->valor = Aux->valor; // Le asigna el mismo valor
			Push(PilaResolucion, Nuevo); // Lo agrega a la pila de operadores
		}

		else if (Aux->prioridad == 7) { // Si es un espacio en blanco (Agregado al usar numeros)
			Aux2 = Pop(PilaResolucion); // Se toma el primero de la pila de resolucion
			a = 1; // Se define el valor de a = 1
			b = 0; // Se define b = 0
			b = a * Aux2->valor; // b se iguala al valor del caracter multiplicado por a
			Aux2 = Top(PilaResolucion); // Se busca el primero de pila de resolucion
										// Mientras Aux2 sea distinto de NULL y su prioridad no es 0 (Un caracter numerico cuyo valor ya esta definido)
			while ((Aux2 != NULL) && (Aux2->prioridad != 0)) {
				Aux2 = Pop(PilaResolucion); // Se elimina de la pila
				if (Aux2->caracter == '-') { // Si es un menos
					b = -b; // Cambia el signo de b
				}

				else {
					a = a * 10; // a se multiplica por 10 para incrementar el orden
					b = b + a * Aux2->valor; // b suma el ultimo valor y el del caracter por a para tener un valor numerico definido
				}
				Aux2 = Top(PilaResolucion); // Aux2 se iguala al top de pila de resolucion
			}
			// Al terminar el ciclo, b tiene el valor numerico equivalente del caracter introducido
			// Se crea un nuevo dato de caracter vacio porque ya no es necesario y de prioridad 0 para definir que ya tiene un valor numerico definido
			Nuevo = CrearCaracter(' ', 0);
			Nuevo->valor = b; // Se le añade el valor de b
			Push(PilaResolucion, Nuevo); // Se agrega al inicio de la pila de resolucion
		}

		else { // Si es un operador
			switch (Aux->caracter) { // Recibe el caracter del operador

			case ('+'): { // Si es una suma
				Aux2 = Pop(PilaResolucion); // Toma el primero de la pila de resolucion
				b = Aux2->valor; // Le añade su valor al flotante b
				Aux2 = Pop(PilaResolucion); // Toma el siguiente en la pila
				a = Aux2->valor; // Le añade su valor al flotante a
				Nuevo = CrearCaracter(' ', 0); // Crea un nuevo caracter de privoridad 0
				Nuevo->valor = a + b; // Le da el valor de la suma de a y b
				Push(PilaResolucion, Nuevo); // Lo agrega al inicio de la pila
				break;
			}
			case ('*'): { // Si es un producto
				Aux2 = Pop(PilaResolucion); // Toma el primero de la pila de resolucion
				b = Aux2->valor; // Le añade su valor al flotante b
				Aux2 = Pop(PilaResolucion); // Toma el siguiente en la pila
				a = Aux2->valor; // Le añade su valor al flotante a
				Nuevo = CrearCaracter(' ', 0); // Crea un nuevo caracter de prioridad 0
				Nuevo->valor = a * b; // Le da el valor del producto entre a y b
				Push(PilaResolucion, Nuevo);
				break;
			}
			case ('-'): {
				Aux2 = Pop(PilaResolucion); // Toma el primero de la pila de resolucion
				b = Aux2->valor; // Le añade su valor al flotante b
				Aux2 = Pop(PilaResolucion); // Toma el primero de la pila de resolucion
				a = Aux2->valor; // Le añade su valor al flotante a
				Nuevo = CrearCaracter(' ', 0); // Crea un nuevo caracter de prioridad 0
				Nuevo->valor = a - b; // Le da el valor de la resta de a y b
				Push(PilaResolucion, Nuevo);
				break;
			}
			case ('/'): {
				Aux2 = Pop(PilaResolucion); // Toma el primero de la pila de resolucion
				b = Aux2->valor; // Le añade su valor al flotante b
				Aux2 = Pop(PilaResolucion); // Toma el primero de la pila de resolucion
				a = Aux2->valor; // Le añade su valor al flotante a
				Nuevo = CrearCaracter(' ', 0); // Crea un nuevo caracter de prioridad 0

				if (b != 0) { // Si b no es 0
					Nuevo->valor = a / b; // Le da el valor de la division de a entre b
				}
				else { // Si b es 0
					printf("NO ES POSIBLE DIVIDIR POR 0\n"); // Imprime un mensaje de error
					return NULL; // Retorna NULL como resultado
				}
				Push(PilaResolucion, Nuevo); // Añade el nuevo dato a la pila de resolucion
				break;
			}
			case ('^'): {
				Aux2 = Pop(PilaResolucion); // Toma el primero de la pila de resolucion
				b = Aux2->valor; // Le añade su valor al flotante b
				Aux2 = Pop(PilaResolucion); // Toma el primero de la pila de resolucion
				a = Aux2->valor; // Le añade su valor al flotante a
				Nuevo = CrearCaracter(' ', 0); // Crea un nuevo caracter de prioridad 0
				Nuevo->valor = pow(a, b); // Le da el valor de a elevado b
				Push(PilaResolucion, Nuevo); // Añade el nuevo dato a la pila de resolucion
				break;
			}
			case '(': { // Entrada POSFIJA de un numero negativo
				if (Aux->Siguiente->caracter == '-') {
					Aux->Siguiente->prioridad = 6; // La prioridad del simbolo menos se iguala a 6 para evaluarla como negativo
				}
				break;
			}
			}
		}
		Aux = Aux->Siguiente; // Aux se iguala a siguiente
	}
	return Top(PilaResolucion); // Retorna el primero de la pila de resolucion (Para este punto debe haber solo un dato en la pila)
}

int main() {
	bool menu = true; // Booleano utilizado para el menu
	PtrOperador Infija, Posfija, Resultado; // Se dinen los punteros para las listas posfija e infija y el utilizado para resolver expresiones
	Posfija = NULL; // Se inician las listas
	Infija = NULL;
	char Entrada[MAX]; // Se declara la cadena de caracteres para ingresar cada expresion
	char opcion; // Se declara un char para la opcion elegida

	while (menu) {
		system("CLS");
		cout << "MENU DE CALCULADORA POSFIJA" << endl << endl; // Imprime el menu

		cout << "1. Convertir de INFIJA a POSFIJA" << endl;
		cout << "2. Resolver una expresion en POSFIJA" << endl;
		cout << "3. Salir de la calculadora" << endl;
		cin >> opcion; // Solicita una opcion

		switch (opcion) {
		case '1': { // Si decide convertir a Posfijo
			char opcion;
			menu = true;
			while (menu) {
				system("CLS");
				cout << "MENU DE CONVERSION DE EXPRESIONES" << endl << endl; // Imprime el menu de conversiones
				cout << "1. Ingresar una nueva expresion" << endl;
				cout << "2. Mostrar la ultima expresion ingresada" << endl;
				cout << "3. Volver al menu de calculadora" << endl;
				cin >> opcion;
				switch (opcion) {
				case '1': { // Si no ha ingresado ninguna expresion antes o quiere ingresar una nueva
					char Entrada[MAX]; // Se inicia Entrada para eliminar lo que pueda haber antes
					DestruirLista(Posfija); DestruirLista(Infija); // Destruye las pilas de infija y posfija
					Posfija = NULL; Infija = NULL; // Vuelve a inicializarlas

					cout << "Ingrese una expresion en INFIJA" << endl;
					/*Despues de leer un numero y antes de leer un texto, queda un Intro en espera
					Si se lee una cadena de texto, el Intro se acepta como si fuera una cadena vacia*/
					getchar(); // getchar "absorbe" el Intro que queda en espera y gets_s funciona después
					gets_s(Entrada); // Toma un string ingresado del teclado y lo almacena en Entrada
					CrearListaEnlazada(Infija, Entrada); // Agrega los caracteres ingresados en una pila dinámica
														 //anadirPrioridad(Infija); // Agrega prioridad de operacion a los operadores
					conversion(Infija, Posfija); // Convierte la pila infija en otra pila posfija
					printf("La expresion posfija es:  "); MostrarLista(Posfija); // Imprime los caracteres en posfija
					system("pause");
					break;
				}
				case '2': { // Si ya habia ingresado una expresion 
					if (Posfija == NULL) { // Si la lista Posfija es NULL, no ha ingresado ninguna expresion
						cout << "No hay ninguna expresion ingresada anteriormente" << endl;
					}
					else { // Si es distinta de NULL
						printf("\nLa expresion ingresada en infijo anteriormente es: "); MostrarLista(Infija); // Muestra la expresion Infija
						printf("\nLa expresion en posfijo es: "); MostrarLista(Posfija); // Muestra la expresion Posfija
					}
					system("pause");
					break;
				}
				case '3': { // Si quiere volver atras
					menu = false; // Menu se declara como falso
					break;
				}
				default: { // Si la opcion escogida no es ninguna de las dadas
					printf("Ingrese una opcion valida\n"); // Imprime un mensaje de error
					system("pause");
					break;
				}
				}
			}
			menu = true; // Se declara menu como verdadero para el menu de calculadora
			break;
		}

		case '2': { // Si quiere evaluar una expresion
			system("CLS");

			char opcion;
			bool menu = true;
			while (menu) {
				system("CLS");
				cout << "MENU DE RESOLUCION DE EXPRESIONES" << endl << endl; // Imprime el menu de Resolucion
				cout << "1. Resolver una expresion ingresada anteriormente" << endl;
				cout << "2. Ingresar una expresion nueva en INFIJO" << endl;
				cout << "3. Ingresar una expresion nueva en POSFIJO" << endl;
				cout << "4. Salir al menu de calculadora" << endl;
				cin >> opcion; // Solicita una opcion

				switch (opcion) {
				case '1': { // Si quiere resolver una expresion ingresada anteriormente
					if (Posfija == NULL) { // Si Posfija esta vacia
						cout << "No ha ingresado ninguna expresion anteriormente" << endl; // Imprime el mensaje de error
					}
					else { // Si posfija tiene algun dato
						printf("La expresion ingresada fue: ");
						if (Infija != NULL) MostrarLista(Infija); // Muestra la expresion infija ingresada
						else if (Posfija != NULL) MostrarLista(Posfija);
						Resultado = resolucion(Posfija); // Resultado toma el valor de la funcion de resolucion
						if (Resultado != NULL) { // Si Resultado es distinto de NULL (No se divide por 0)
							printf("El resultado es: %.3f\n", Resultado->valor); // Imprime el valor de Resultado
						}
					}
					system("pause");
					break;
				}
				case '2': { // Si quiere ingresar una nueva expresion
					char Entrada[MAX];
					DestruirLista(Posfija); DestruirLista(Infija); // Destruye las pilas de infija y posfija
					Posfija = NULL; Infija = NULL; // Vuelve a inicializarlas

					cout << "Ingrese una expresion en INFIJA" << endl;
					/*Despues de leer un numero y antes de leer un texto, queda un Intro en espera
					Si se lee una cadena de texto, el Intro se acepta como si fuera una cadena vacia*/
					getchar(); // getchar "absorbe" el Intro que queda en espera y gets_s funciona después
					gets_s(Entrada); // Toma un string ingresado del teclado y lo almacena en Entrada
					CrearListaEnlazada(Infija, Entrada); // Agrega los caracteres ingresados en una pila dinámica
					anadirPrioridad(Infija); // Agrega prioridad de operacion a los operadores
					conversion(Infija, Posfija); // Convierte la pila infija en otra pila posfija
					Resultado = resolucion(Posfija); // Resultado toma el valor de la funcion de resolucion
					if (Resultado != NULL) { // Si Resultado es distinto de NULL (No se divide por 0)
						printf("El resultado es: %.3f\n", Resultado->valor); // Imprime el valor de Resultado
					}
					system("pause");
					break;
				}
				case '3': { // Si quiere ingresar una nueva expresion
					char Entrada[MAX];
					DestruirLista(Posfija); DestruirLista(Infija); // Destruye las pilas de infija y posfija
					Posfija = NULL; Infija = NULL; // Vuelve a inicializarlas

					cout << "Ingrese una expresion en POSFIJA" << endl;
					/*Despues de leer un numero y antes de leer un texto, queda un Intro en espera
					Si se lee una cadena de texto, el Intro se acepta como si fuera una cadena vacia*/
					getchar(); // getchar "absorbe" el Intro que queda en espera y gets_s funciona después
					gets_s(Entrada); // Toma un string ingresado del teclado y lo almacena en Entrada
					CrearListaEnlazada(Posfija, Entrada); // Agrega los caracteres ingresados en una pila dinámica
					anadirPrioridad(Posfija); // Agrega prioridad de operacion a los operadores
					//conversion(Infija, Posfija); // Convierte la pila infija en otra pila posfija
					Resultado = resolucion(Posfija); // Resultado toma el valor de la funcion de resolucion
					if (Resultado != NULL) { // Si Resultado es distinto de NULL (No se divide por 0)
						printf("El resultado es: %.3f\n", Resultado->valor); // Imprime el valor de Resultado
					}
					system("pause");
					break;
				}

				case '4': { // Si quiere volver al menu de calculadora
					menu = false; // menu se declara como falso
					break;
				}

				default: { // Si la opcion ingresada no es una de la dadas
					printf("Ingrese una opcion valida\n"); // Iprime el mensaje de error
					system("pause");
					break;
				}
				}
			}
			menu = true; // Menu se declara como verdadero
			break;
		}

		case '3': { // Si quiere salir de la calculadora
			system("CLS");
			menu = false; // Menu se declara como falso
			printf("Saliendo de Calculadora\n"); // Imprime el mensaje de que esta saliendo
			DestruirLista(Infija); DestruirLista(Posfija); // Destruye las pilas posfija e infija
			system("pause");
			break;
		}

		default: { // Si la opcion ingresada no es una de la dadas
			printf("Ingrese una opcion valida\n"); // Iprime el mensaje de error
			system("pause");
			break;
		}
		}
	}
}