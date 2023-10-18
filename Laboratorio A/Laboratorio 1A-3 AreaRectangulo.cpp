#include "pch.h"
#include <iostream>
#include <conio.h>
using namespace std;
int AreaRectangulo(int base, int altura) {// se define la base y altura como variables  pero antes se les denomina com enteros
	int area = base * altura;
	return area;
	// otra forma: return base*altura;
}
void main()
{
	//A continuaci�n se llaman las funciones
	//Primera funcion
	int Area = AreaRectangulo(2, 6);
	cout << "Area: " << Area << endl;
	system("pause");
}

/*Area: 12
Presione una tecla para continuar . . .*/