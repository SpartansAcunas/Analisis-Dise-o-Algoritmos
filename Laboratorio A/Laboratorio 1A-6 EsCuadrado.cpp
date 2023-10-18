#include "pch.h"
#include <iostream>
#include <conio.h>
using namespace std;
bool EsCuadrado(int base, int altura) {//bool me indica una funcion boleana
	if (base == altura) {// if me indica  un "si" el cual me indica una condicion que debe cumplirse
		return true;
	}
	else {//else me  indica  lo que debe pasar si no se cumple el condicional del "si"
		return false;//en este caso le solicita que regrese un falso  
	}
}
void main()
{
	//Cuarta  unción
	int base = 0;
	int altura = 2;
	cout << "Ingrese la base: " << endl;//cout le solicita algo al usuario
	cin >> base;//cin  le asigna algo pedidio al usuario a una variable
	printf("Ingrese la altura: ");
	scanf_s("%i", &altura);// scanf_s lee un dato y luego lo asigna 
	bool Cierto = EsCuadrado(base, altura);
	cout << Cierto << endl;
	system("pause");
}
/*Ingrese la base:
2
Ingrese la altura: 3
0
Presione una tecla para continuar . . .*/
/*Ingrese la base:
4
Ingrese la altura: 4
1
Presione una tecla para continuar . . .*/