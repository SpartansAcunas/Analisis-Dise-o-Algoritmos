#include "pch.h"
#include <iostream>
#include <conio.h>
using namespace std;
//Parecido en python  el struct genera un objeto y le da  ciertos atributos
struct alumno {  //definiendo el tipo de dato 
	int carnet;
	char nombre[50];//char asigna valores de tipo strings
	char carrera[5];
	bool activo;
};

int main()
{
	char* carreraq = "IMT";
	char* Nombreq = "Jose";
	alumno Alumno100;     //Definiendo la variable como una estructura
	Alumno100.activo = 1;//Se llama al struct y se asigna el atrubuto que se quiere
	Alumno100.carnet = 201563645;
	strcpy_s(Alumno100.carrera, carreraq);
	strcpy_s(Alumno100.nombre, Nombreq);
	cout << "El alumno " << Alumno100.nombre << " fue resgistrado con el numero de carnet " << Alumno100.carnet << endl;
	cout << "en la carrera " << Alumno100.carrera << "." << endl;
	system("pause");
}
/*El alumno Jose fue registrado con el numero de carnet 201563645
en la carrera IMT.
Presione una tecla para continuar . . .*/