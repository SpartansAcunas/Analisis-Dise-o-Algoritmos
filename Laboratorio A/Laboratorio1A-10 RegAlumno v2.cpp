#include "pch.h"
#include <iostream>
#include <conio.h>
using namespace std;
struct alumno {
	int carnet;
	char nombre[50];
	char carrera[5];
	bool activo;
};
int main()
{
	char * carreraq = "IMT";
	char * Nombreq = "Jose";
	alumno Alumno100[1000];
	Alumno100[1].activo = 1;
	Alumno100[1].carnet = 201563645;
	strcpy_s(Alumno100[1].carrera, carreraq);
	strcpy_s(Alumno100[1].nombre, Nombreq);
	cout << "El alumno " << Alumno100[1].nombre << " fue resgistrado con el numero de carnet " << Alumno100[1].carnet << endl;
	cout << "en la carrera " << Alumno100[1].carrera << "." << endl;
	system("pause");
}
/*El alumno Jose fue registrado con el numero de carnet 201563645
en la carrera IMT.
Presione una tecla para continuar . . .*/