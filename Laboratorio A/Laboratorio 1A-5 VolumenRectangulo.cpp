#include "pch.h"
#include <iostream>
#include <conio.h>
using namespace std;
void VolumenRectangulo(float largo, float ancho, float alto) {
	//al igual que el programa anterior se define esta funcion para ser llamada  en el main sin embargo el cout esta dentro de la funcion en vez del main
	float Volumen = largo * ancho*alto;
	cout << "El volumen del rectangulo es: " << Volumen << endl;
}
void main()
{
	VolumenRectangulo(2, 4, 6);
	system("pause");
}
/*El volumen del rectangulo es: 48
Presione una tecla para continuar . . .*/