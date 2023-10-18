#include "pch.h"
#include <iostream>
#include <conio.h>
using namespace std;

void PerimetroRectangulo(int largo, int ancho, int &Perimetro) {
	//Se Crea  esta fucion aparte para ser luego llamada en el cuerpo principal
	Perimetro = (2 * largo) + (2 * ancho);
}

void main()
{
	//Segunda Funcion
	int Perim = 0;
	PerimetroRectangulo(2, 6, Perim);
	cout << "Perimetro: " << Perim << endl << endl;
	system("pause");
}

/*Perimetro: 16

Presione una tecla para continuar . . .*/