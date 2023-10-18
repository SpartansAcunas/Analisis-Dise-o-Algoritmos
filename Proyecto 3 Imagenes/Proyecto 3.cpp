#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <string.h>

void InvertirBit(char& Simbolo, int cual)
{
	int Mascara = 1;

	Mascara = Mascara << cual;
	Simbolo = Simbolo ^ Mascara;
}

// A continuaci'on se definen los metodos Veneno_X y Antidoto_X que serviran para Encriptar y Desencriptar el archivo procesado 
// Ojo X puede ser 1,2,3,4...  y siempre el antidoto debera corresponder al veneno.  En este ejemplo solo se usa el 1
void Veneno_1(char Bloque[1000], int limite)
{
	int i;
	int posicion_a_invertir = 0;

	for (i = 0; i <= limite; i++) {
		InvertirBit(Bloque[i], posicion_a_invertir);
	}
}

void Antidoto_1(char Bloque[1000], int limite)
{
	int i;
	int posicion_a_invertir = 0;

	for (i = 0; i <= limite; i++) {
		InvertirBit(Bloque[i], posicion_a_invertir);
	}
}

void Veneno_2(char Bloque[1000], int limite)
{
	int i;

	for (i = 0; i <= limite; i++) {
		InvertirBit(Bloque[i], limite);
	}
}

void Antidoto_2(char Bloque[1000], int limite)
{
	int i;
	for (i = 0; i <= limite; i++) {
		InvertirBit(Bloque[i], limite);
	}
}

void Veneno_3(char Bloque[1000], int limite)
{
	int i;
	int posicion_a_invertir = 1;

	for (i = 0; i <= limite; i++) {
		InvertirBit(Bloque[i], posicion_a_invertir);
	}
}

void Antidoto_3(char Bloque[1000], int limite)
{
	int i;
	int posicion_a_invertir = 1;

	for (i = 0; i <= limite; i++) {
		InvertirBit(Bloque[i], posicion_a_invertir);
	}
}

void Veneno_4(char Bloque[1000], int limite)
{
	int i, a;
	for (i = 0; i <= limite; i++) {
		for (a = 0; a <= 8;)
		{
			InvertirBit(Bloque[i], a);
			a = a + 2;
		}
	}
}

void Antidoto_4(char Bloque[1000], int limite)
{
	int i, a;
	for (i = 0; i <= limite; i++) {
		for (a = 0; a <= 8;)
		{
			InvertirBit(Bloque[i], a);
			a = a + 2;
		}
	}
}


using namespace std;
int main(int argc, char* argv[]) {

	//----------------------------------------------------------------------
	// Pintando a pantalla los argumentos que recibe el programa :  Se esperan en esta prueba 3: 
	// Ejecutable e/d FileOrigen FileDestino
	// e/d = e=encritar   d=desencriptar


	for (int i = 0; i < argc; ++i) {
		cout << "argumento " << i << ": " << argv[i] << "\n";
	}
	//----------------------------------------------------------------------

	// Archivos logicos : Buffers tipo FILE
	FILE* ArchivoOrigen, *ArchivoDestino;

	//----------------------------------------------------------------------
	// APERTURA DE ARCHIVO FUENTE Y DESTINO
	/* Apertura del archivo original, para lectura en binario*/
	fopen_s(&ArchivoOrigen, argv[3], "rb");
	if (ArchivoOrigen == NULL)
	{
		perror("No se puede abrir archivo origen ");//, argv[2]
		return -1;
	}

	/* Apertura del archivo destino, para escritura en binario*/
	fopen_s(&ArchivoDestino, argv[4], "wb");
	if (ArchivoDestino == NULL)
	{
		perror("No se puede abrir archivo destino"); // , argv[2]
		return -1;
	}

	//----------------------------------------------------------------------
	// PROCESAMIENTO DE ARCHIVOS FUENTE Y DESTINO

	/* Bloque de 1000 bytes, para meter lo que vamos leyendo del archivo */
	char buffer[1000];
	/* Para guardar el número de items leidos o si ha habido error */
	int leidos;
	char opcion = argv[1][0]; // (strcmp(opcion, 'e')
	char metodo = argv[2][0];
	if (opcion == 'e') // Da verdadero si se quiere "e"ncriptar, cualquier otro es desencriptar
	{  // ENCRIPTANDO
		if (metodo == '1') {
			leidos = fread(buffer, 1, 1000, ArchivoOrigen);

			/* Mientras se haya leido algo ... */
			while (leidos > 0)
			{

				Veneno_1(buffer, leidos); // Ojo esta usando el mismo metodo de desencriptar ya que solo INVIERTE el Bit 0

				/* ... meterlo en el fichero destino */
				fwrite(buffer, 1, leidos, ArchivoDestino);

				/* y leer siguiente bloque */
				leidos = fread(buffer, 1, 1000, ArchivoOrigen);
			}
		}
		else if (metodo == '2')
		{  // ENCRIPTANDO

			leidos = fread(buffer, 1, 1000, ArchivoOrigen);

			/* Mientras se haya leido algo ... */
			while (leidos > 0)
			{

				Veneno_2(buffer, leidos); // Ojo esta usando el mismo metodo de desencriptar ya que solo INVIERTE el Bit 1

				/* ... meterlo en el fichero destino */
				fwrite(buffer, 1, leidos, ArchivoDestino);

				/* y leer siguiente bloque */
				leidos = fread(buffer, 1, 1000, ArchivoOrigen);
			}
		}
		else if (metodo == '3') // Da verdadero si se quiere "e"ncriptar, cualquier otro es desencriptar
		{  // ENCRIPTANDO

			leidos = fread(buffer, 1, 1000, ArchivoOrigen);

			/* Mientras se haya leido algo ... */
			while (leidos > 0)
			{

				Veneno_3(buffer, leidos); // Ojo esta usando el mismo metodo de desencriptar ya que solo INVIERTE el Bit 1

				/* ... meterlo en el fichero destino */
				fwrite(buffer, 1, leidos, ArchivoDestino);

				/* y leer siguiente bloque */
				leidos = fread(buffer, 1, 1000, ArchivoOrigen);
			}
		}
		else if (metodo == '4') // Da verdadero si se quiere "e"ncriptar, cualquier otro es desencriptar
		{  // ENCRIPTANDO

			leidos = fread(buffer, 1, 1000, ArchivoOrigen);

			/* Mientras se haya leido algo ... */
			while (leidos > 0)
			{

				Veneno_4(buffer, leidos); // Ojo esta usando el mismo metodo de desencriptar ya que solo INVIERTE el Bit 1

				/* ... meterlo en el fichero destino */
				fwrite(buffer, 1, leidos, ArchivoDestino);

				/* y leer siguiente bloque */
				leidos = fread(buffer, 1, 1000, ArchivoOrigen);
			}
		}
	}
	else if (opcion == 'd')
	{
		if (metodo == '1') // DESENCRIPTANDO
		{
			leidos = fread(buffer, 1, 1000, ArchivoOrigen);

			/* Mientras se haya leido algo ... */
			while (leidos > 0)
			{

				Antidoto_1(buffer, leidos); // Ojo esta usando el mismo metodo de encriptar ya que solo INVIERTE el Bit 0

				/* ... meterlo en el fichero destino */
				fwrite(buffer, 1, leidos, ArchivoDestino);

				/* y leer siguiente bloque */
				leidos = fread(buffer, 1, 1000, ArchivoOrigen);
			}
		}

		else if (metodo == '2') // DESENCRIPTANDO
		{
			leidos = fread(buffer, 1, 1000, ArchivoOrigen);

			/* Mientras se haya leido algo ... */
			while (leidos > 0)
			{

				Antidoto_2(buffer, leidos); // Ojo esta usando el mismo metodo de encriptar ya que solo INVIERTE el Bit 1

				/* ... meterlo en el fichero destino */
				fwrite(buffer, 1, leidos, ArchivoDestino);

				/* y leer siguiente bloque */
				leidos = fread(buffer, 1, 1000, ArchivoOrigen);
			}
		}


		else if (metodo == '3') // DESENCRIPTANDO
		{
			leidos = fread(buffer, 1, 1000, ArchivoOrigen);

			/* Mientras se haya leido algo ... */
			while (leidos > 0)
			{

				Antidoto_3(buffer, leidos); // Ojo esta usando el mismo metodo de encriptar ya que solo INVIERTE el Bit 1

				/* ... meterlo en el fichero destino */
				fwrite(buffer, 1, leidos, ArchivoDestino);

				/* y leer siguiente bloque */
				leidos = fread(buffer, 1, 1000, ArchivoOrigen);
			}
		}

		else if (metodo == '4') // DESENCRIPTANDO
		{
			leidos = fread(buffer, 1, 1000, ArchivoOrigen);

			/* Mientras se haya leido algo ... */
			while (leidos > 0)
			{

				Antidoto_4(buffer, leidos); // Ojo esta usando el mismo metodo de encriptar ya que solo INVIERTE el Bit 1

				/* ... meterlo en el fichero destino */
				fwrite(buffer, 1, leidos, ArchivoDestino);

				/* y leer siguiente bloque */
				leidos = fread(buffer, 1, 1000, ArchivoOrigen);
			}
		}
	}


	fclose(ArchivoOrigen);
	fclose(ArchivoDestino);

	// Terminamos .. vaya a ver como quedo el archivo Encriptado o Desencriptado.. no olvide manejar estos nombre 
	// en Proyecto->Propiedades->Depuracion->Argumentos 
	// Ejemplo de parametros ... ojo el parametro "0" es el nombre del ejecutable, el parametro 1 es "e" o "d" 
	// el parametro 2 es el archivoOrigen y el parmetro 3 es el archivo destino  
	// Lectura-Escritura-Archivos-C-xBytes.exe e MiFotoOriginal.jpg MiFotoEncriptada.enc
	// Lectura-Escritura-Archivos-C-xBytes.exe d MiFotoEncriptada.enc MiFotoOriginal-restaurada.jpg
	// 

}