#include "pch.h"
#include <stdio.h> 
#include <stdlib.h> // Libreria que permite el manejo de memoria dinamica,funciones de numeros aleatorios ,etc
#include <string.h> //Libreria que permite funciones para manipular strings y arreglos en C

using namespace std;


typedef struct TArticulo // Creacion de estructura el cual seradefinido como un registro (coleccion estatica de diferentes tipos de datos)
{
	int Codigo; 
	char Nombre[20]; 
	int Disponible; 
	float Precio; 
	TArticulo *Siguiente; // Puntero para contener la dirección en memoria donde se almacenara el dato siguiente
}*PtrTArticulo; // Define al Puntero de la structura que va a definir la direccion en la memoria dinamica donde este va a estar guardado


			

int i;  //parametro global


void InicializarInventario(PtrTArticulo &Lista)
{
	Lista = NULL;
}

// Función que me limpia el Parametro lsita , este es  por referencia
void DestruirInventario(PtrTArticulo &Lista)
{
	PtrTArticulo Aux; // Puntero que apuntara al primer dato de la lista
	Aux = Lista; // Aux toma el valor de lista
	while (Aux != NULL) // Mientras Aux no termine de leer toda la lista.
	{
		Lista = Lista->Siguiente; // Lista apuntara al siguiente valor de la lista
		delete(Aux); // Borra el valor de Aux
		Aux = Lista; // Aux toma el valor de lista el cual apuntara  al siguiente valor para que continue su recorrido
	}
}

// Funcion para agregar nuevo articulo 
PtrTArticulo CrearArticulo(int NCodigo, int NDisponible, float NPrecio)
{
	PtrTArticulo Pieza = new(TArticulo); // Solicita un Nuevo espacio  en Memoria para ser asignado a un nuevo articulo
	char buffer[5]; 

	Pieza->Codigo = NCodigo; //Asignacion del codigo solicitado por Usuario al Tipo Codigo dentro del struct
	Pieza->Disponible = NDisponible; // Asignacion de la disponiblidad solicitada por Usuario al Tipo Disponible dentro del struct
	Pieza->Precio = NPrecio; // Asignacion del precio solicitado por Usuario al Tipo Precio dentro del struct

	strcpy_s(Pieza->Nombre, "Pieza"); // Agrega el Nombre al  string Pieza
	_itoa_s(NCodigo, buffer, 10); // Convierte el codigo a string, y lo almacena como un float 
	strcat_s(Pieza->Nombre, buffer); // Concatena strings, al nombre se le agrega  el codigo almacenado

	Pieza->Siguiente = NULL; //Al puntero se le asigna el valor NULL
	return Pieza; // Regresa los datos de la Pieza añadida
}

// Funcionque agrega cada articulo nuevo al inicio de lista
void AgregarInicioInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo)
{
	Nuevo->Siguiente = Lista; // Al puntero siguiente del nuevo articulo, se  le asigna la direccion al inicio de la lista
	Lista = Nuevo; // La direccion de la lista se enlaza al nuevo articulo
}




// Funcion para agregar los articulos al final de la lista 
void AgregarFinalInventario(PtrTArticulo &Lista, PtrTArticulo &Nuevo)
{
	PtrTArticulo Aux; // Declaracion del puntero Aux a PtrTArticulo
	Aux = Lista; // Aux almacena la direccion del primer miembro de la lista
	if (Aux != NULL) //Condicional que se cumple si Aux aun no Termina la lista
	{
		while (Aux->Siguiente != NULL) // Mientras el puntero almacenado en Siguiente no sea NULL
		{
			Aux = Aux->Siguiente; // Aux toma la direccion  del siguiente miembro de la lista
		}

		Aux->Siguiente = Nuevo;
	}
	else // Si se llega al final de la lista
	{
		Lista = Nuevo;
	}
}



// Funcion para imprimir lista en pantalla
void ListarInventario(PtrTArticulo &Lista)
{
	int Contador = 1; // Inicio de contador
	PtrTArticulo Aux; // Se declara Aux  a PtrTArticulo
	Aux = Lista; // Aux almacena la direccion  de la lista
	while (Aux != NULL) // Mientras no se llegue al final de la lista
	{
		printf(" %d ", Contador); // Imprime el contador
		printf("%d ", Aux->Codigo); // Imprime el codigo
		printf("%s ", Aux->Nombre); // Imprime el nombre
		printf(" %d ", Aux->Disponible); // Imprime la cantidad disponible
		printf(" %f\n ", Aux->Precio); // Imprime el precio del producto
		Aux = Aux->Siguiente; // Aux almacena la direccion en memoria del siguiente articulo
		Contador++; // Incremento del contador
	}
}

// Funcion para buscar articulos en la lista

PtrTArticulo BuscarArticulo(PtrTArticulo &Lista, int cual)
{
	bool encontro = false; // Declaracion de variable tipo booleana
	PtrTArticulo Aux; // Declaracion de puntero Aux a PtrTArticulo
	Aux = Lista; // Se le asigna a Aux la direccion de Lista

	while ((!encontro == true) && (Aux != NULL)) // Mientras que encontro sea falso
	{
		if (Aux->Codigo == cual) // Si el codigo del producto es igual al buscado
		{
			encontro = true; // Se asigna encontro como verdadero
		}
		else // Si el codigo no es igual al buscado
		{
			Aux = Aux->Siguiente; // Aux apunta al siguiente producto en la lista
		}
	}
	return Aux; // Se regresa la direccion en memoria del producto encontrado
}

// Funcion para guardar la lista en memoria secundaria como archivo de texto
void GuardarInventario(PtrTArticulo Lista)
{
	FILE *archivo; // Puntero a archivo que almacena la direccion en memoria donde se guarda el archivo
	fopen_s(&archivo, "ARCHIVO.txt", "w+"); // Copia la informacion del archivo y lo almacena en la memoria como archivo logico
	if (NULL == archivo) // Si la direccion en memoria es igual a NULL, el archivo no fue encontrado
	{
		printf("No se pudo abrir el archivo."); // Imprime un mensaje de error
	}
	else // Si encontro el archivo
	{
		PtrTArticulo AUX = Lista; // Aux almacena la direccion del comienzo de la lista
		while (AUX != NULL) // Mientras no se llega al final de la lista
		{
			fprintf(archivo, "%i\n", AUX->Codigo); // Escribe en el archivo logico el codigo de cada producto del arreglo
			fprintf(archivo, "%s\n", AUX->Nombre); // Escribe en el archivo logico el nombre de cada producto del arreglo
			fprintf(archivo, "%i\n", AUX->Disponible); // Escribe en el archivo logico la cantidad disponible de cada producto del arreglo
			fprintf(archivo, "%f\n", AUX->Precio); // Escribe en el archivo logico el precio de cada producto del arreglo
			AUX = AUX->Siguiente; // Aux apunta al siguiente miembro de la lista
		}
	}
	fclose(archivo); // Como el archivo se cargo en modo de escritura, entonces sobreescribe la informacion al archivo de texto
}

// Funcion para cargar la informacion almacenada del almacenamiento a archivo logico
void CargarInventario(PtrTArticulo &Lista)
{
	PtrTArticulo Nuevo; // Se declara un puntero a PtrTArticulo
	FILE *archivo; // Se almacena la direccion del archivo de texto
	fopen_s(&archivo, "ARCHIVO.txt", "r"); // Se carga la informacion del archivo de texto en la memoria RAM
	if (NULL == archivo) // Si no encuentra el archivo en la memoria 
	{
		printf("No se pudo abrir el archivo"); // imprime un mensaje de error
	}
	else // Si lo encuentra
	{
		while (!feof(archivo)) // Mientras no se llegue al final del archivo en la memoria
		{
			Nuevo = new(TArticulo); // Nuevo solicita un nuevo espacio en la memoria
			char Cadena[20]; // Declaracion de variable tipo caracter
			fscanf_s(archivo, "%i\n", &Nuevo->Codigo); // Lee el codigo del producto y lo almacena en la memoria
			fscanf_s(archivo, "%s\n", Cadena, 20); // Añade el string cadena a la memoria
			fscanf_s(archivo, "%i\n", &Nuevo->Disponible); // Lee la cantidad disponible del producto y lo almacena en la memoria
			fscanf_s(archivo, "%f\n", &Nuevo->Precio); // Lee el precio del producto y lo almacena en la memoria
			strcpy_s(Nuevo->Nombre, Cadena); // Al Nombre del producto le añade el string Cadena
			Nuevo->Siguiente = NULL; // Al puntero Siguiente en Nuevo, lo define como NULL
			AgregarFinalInventario(Lista, Nuevo); // Llama esta funcion para agregar cada articulo al final de la lista
		}
	}
	fclose(archivo); // Como el archivo se cargo en modo de lectura, la informacion de la memoria se borra y no escribe en el archivo
}

// Funcion principal
void main(int argc, char* argv[])
{
	
	// Punteros a PtrTArticulo
	PtrTArticulo Llantas;
	PtrTArticulo Abarrotes;
	PtrTArticulo Nuevo;
	PtrTArticulo Prueba;

	
	InicializarInventario(Abarrotes); // Se llama la funcion para iniciar el inventario

	for (int i = 100; i <= 200; i++) // Ciclo con inicio en 100 y termina en 200
	{
		Nuevo = CrearArticulo(i, i, i); // Se crea un nuevo articulo con parametros dados por el ciclo
		AgregarInicioInventario(Abarrotes, Nuevo); // Se agrega cada nuevo articulo al final del inventario
	}
	GuardarInventario(Abarrotes); // Se guarda la lista generada en la memoria secundaria
	ListarInventario(Abarrotes); // Se imprime en pantalla la lista
	
								 // Busqueda
	Prueba = BuscarArticulo(Abarrotes, 125); // De la lista abarrotes, se busca el articulo 125 y se obtiene su direccion en memoria
	if (Prueba != NULL) // Si la direccion es distinta de NULL
	{
		printf(" La cantidad disponible es : %i", Prueba->Disponible); // Imprime la cantidad  del producto
	}
	else // Si la direccion es NULL, entonces el articulo no se encuentra 
	{
		printf("No encontrado!!"); // Imprime un mensaje de error
	}
	system("pause");

	DestruirInventario(Abarrotes); // Se borra cada articulo de la memoria
	system("cls"); // Se limpia la pantalla
				   //*************************PRUEBA DE CARGAR********************************
	InicializarInventario(Prueba); // Inicia un nuevo inventario
	CargarInventario(Prueba); // Carga la informacion almacenada en el archivo de texto
	ListarInventario(Prueba); // Muestra la lista de articulos
	system("pause"); // Pausa el sistema
	DestruirInventario(Prueba); // Borra la informacion de la memoria
								
	InicializarInventario(Abarrotes); // Inicia un nuevo inventario
	for (i = 200; i <= 300; i++) // Ciclo que se ejecuta desde 200 hasta 300
	{
		Nuevo = CrearArticulo(i, i, i); // Crea un nuevo articulo con parametros dados por el ciclo
		AgregarFinalInventario(Abarrotes, Nuevo); // Agrega cada articulo al final del inventario 
	}
	ListarInventario(Abarrotes); // Imprime la lista en pantalla
	DestruirInventario(Abarrotes); // Borra la informacion de la memoria

								   	
	InicializarInventario(Llantas); // Inicia un nuevo inventario
	for (i = 100; i <= 200; i++) // Ciclo que se ejecuta desde 100 hasta 200
	{
		Nuevo = CrearArticulo(i, i, i); // Crea un nuevo articulo con parametros dados por el ciclo
		AgregarInicioInventario(Llantas, Nuevo); // Agrega cada articulo al final del inventario
	}
	ListarInventario(Llantas); // Imprime la lista en pantalla
	DestruirInventario(Llantas); // Borra la informacion de la memoria

								 
	InicializarInventario(Llantas); // Inicia un nuevo inventario
	for (i = 200; i <= 300; i++) // Ciclo que se ejecuta desde 200 hasta 300
	{
		Nuevo = CrearArticulo(i, i, i); // Crea un nuevo articulo con parametros dados por el ciclo
		AgregarFinalInventario(Llantas, Nuevo); // Agrega cada articulo al final del inventario 
	}
	ListarInventario(Llantas); // Imprime la lista en pantalla
	
	Prueba = BuscarArticulo(Llantas, 200); // De la lista abarrotes, se busca el articulo 200 y se obtiene su direccion en memoria
	if (Prueba != NULL) // Si la direccion es distinta de NULL
	{
		printf("La cantidad disponible es : %i", Prueba->Disponible); // Imprime la cantidad disponible del producto
	}
	else // Si la direccion es NULL, entonces el articulo no se encuentra en la lista
	{
		printf("No encontrado!!"); // Imprime un mensaje de error
	}
	system("pause");
	DestruirInventario(Llantas); // Borra la informacion de la memoria


	system("pause");
}


/*
***Busqueda en Abarrotes ***
La cantidad disponible es : 125


***Busqueda Llantas****
La cantidad disponible es : 200


***Creacion de Lista en Abarrotes***
  1 200 Pieza200  200  200.000000
  2 199 Pieza199  199  199.000000
  3 198 Pieza198  198  198.000000
  4 197 Pieza197  197  197.000000
  5 196 Pieza196  196  196.000000
  6 195 Pieza195  195  195.000000
  7 194 Pieza194  194  194.000000
  8 193 Pieza193  193  193.000000
  9 192 Pieza192  192  192.000000
  10 191 Pieza191  191  191.000000
  11 190 Pieza190  190  190.000000
  12 189 Pieza189  189  189.000000
  13 188 Pieza188  188  188.000000
  14 187 Pieza187  187  187.000000
  15 186 Pieza186  186  186.000000
  16 185 Pieza185  185  185.000000
  17 184 Pieza184  184  184.000000
  18 183 Pieza183  183  183.000000
  19 182 Pieza182  182  182.000000
  20 181 Pieza181  181  181.000000
  21 180 Pieza180  180  180.000000
  22 179 Pieza179  179  179.000000
  23 178 Pieza178  178  178.000000
  24 177 Pieza177  177  177.000000
  25 176 Pieza176  176  176.000000
  26 175 Pieza175  175  175.000000
  27 174 Pieza174  174  174.000000
  28 173 Pieza173  173  173.000000
  29 172 Pieza172  172  172.000000
  30 171 Pieza171  171  171.000000
  31 170 Pieza170  170  170.000000
  32 169 Pieza169  169  169.000000
  33 168 Pieza168  168  168.000000
  34 167 Pieza167  167  167.000000
  35 166 Pieza166  166  166.000000
  36 165 Pieza165  165  165.000000
  37 164 Pieza164  164  164.000000
  38 163 Pieza163  163  163.000000
  39 162 Pieza162  162  162.000000
  40 161 Pieza161  161  161.000000
  41 160 Pieza160  160  160.000000
  42 159 Pieza159  159  159.000000
  43 158 Pieza158  158  158.000000
  44 157 Pieza157  157  157.000000
  45 156 Pieza156  156  156.000000
  46 155 Pieza155  155  155.000000
  47 154 Pieza154  154  154.000000
  48 153 Pieza153  153  153.000000
  49 152 Pieza152  152  152.000000
  50 151 Pieza151  151  151.000000
  51 150 Pieza150  150  150.000000
  52 149 Pieza149  149  149.000000
  53 148 Pieza148  148  148.000000
  54 147 Pieza147  147  147.000000
  55 146 Pieza146  146  146.000000
  56 145 Pieza145  145  145.000000
  57 144 Pieza144  144  144.000000
  58 143 Pieza143  143  143.000000
  59 142 Pieza142  142  142.000000
  60 141 Pieza141  141  141.000000
  61 140 Pieza140  140  140.000000
  62 139 Pieza139  139  139.000000
  63 138 Pieza138  138  138.000000
  64 137 Pieza137  137  137.000000
  65 136 Pieza136  136  136.000000
  66 135 Pieza135  135  135.000000
  67 134 Pieza134  134  134.000000
  68 133 Pieza133  133  133.000000
  69 132 Pieza132  132  132.000000
  70 131 Pieza131  131  131.000000
  71 130 Pieza130  130  130.000000
  72 129 Pieza129  129  129.000000
  73 128 Pieza128  128  128.000000
  74 127 Pieza127  127  127.000000
  75 126 Pieza126  126  126.000000
  76 125 Pieza125  125  125.000000
  77 124 Pieza124  124  124.000000
  78 123 Pieza123  123  123.000000
  79 122 Pieza122  122  122.000000
  80 121 Pieza121  121  121.000000
  81 120 Pieza120  120  120.000000
  82 119 Pieza119  119  119.000000
  83 118 Pieza118  118  118.000000
  84 117 Pieza117  117  117.000000
  85 116 Pieza116  116  116.000000
  86 115 Pieza115  115  115.000000
  87 114 Pieza114  114  114.000000
  88 113 Pieza113  113  113.000000
  89 112 Pieza112  112  112.000000
  90 111 Pieza111  111  111.000000
  91 110 Pieza110  110  110.000000
  92 109 Pieza109  109  109.000000
  93 108 Pieza108  108  108.000000
  94 107 Pieza107  107  107.000000
  95 106 Pieza106  106  106.000000
  96 105 Pieza105  105  105.000000
  97 104 Pieza104  104  104.000000
  98 103 Pieza103  103  103.000000
  99 102 Pieza102  102  102.000000
  100 101 Pieza101  101  101.000000
  101 100 Pieza100  100  100.000000
  La cantidad disponible es : 125Presione una tecla para continuar . . .*/