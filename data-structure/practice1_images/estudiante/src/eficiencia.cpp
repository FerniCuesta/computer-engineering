/***************************************************************************/
/***************************************************************************/
// Estructura de Datos
//
// (C) FERNANDO CUESTA BUENO
// (C) ANTONIO MANUEL GARCIA MESA
//
// 2º INGENIERIA INFORMATICA GRUPO A1
//
// Fichero: eficiencia.cpp
//
// Programa que recibe 
// <valor>
// 
// <valor> será el parámetro que estemos midiendo en cada momento.
// 
// Según lo que estemos estudiando en cada caso tendremos:
//
// <valor> filas y una cantidad fija de columnas
// <valor> columnas y una cantidad fija de filas
// <valor> llamadas a la funcion ShuffleRows
//
// Fecha: 24 de octubre de 2022
//
/***************************************************************************/
/***************************************************************************/

#include <iostream>
#include <chrono>

#include <image.h>

using namespace std;

// Constantes globales
int MAX = 255;
int VALOR_FIJO = 10;

void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << "  FIL: Numero de filas (>0)" << endl;
  cerr << "  COL: Numero de columnas (>0)" << endl;
  cerr << "Se genera una imagen de tamaño FIL * COL con valores aleatorios en [0,255]" << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[]) {
    // Lectura de parámetros
    if (argc != 3)
        sintaxis();

    int valor = atoi(argv[1]);     // Valor pasado como parámetro

    // Generación de la imagen aleatoria
    Image aleatoria (VALOR_FIJO, VALOR_FIJO);

    srand(time(0));            // Inicialización del generador de números pseudoaleatorios
    for (int i=0; i<aleatoria.size(); i++)  // Recorrer vector
        aleatoria.set_pixel(i,rand() % MAX);    // Generar aleatorio [0,vmax[
    
    clock_t tini;    // Anotamos el tiempo de inicio
    tini=clock();
    
    for (int i = 0; i < valor; i++)
        aleatoria.ShuffleRows();
    
    
    clock_t tfin;    // Anotamos el tiempo de finalización
    tfin=clock();

    // Mostramos resultados
    cout << valor << "\t" << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;

    return 0;
}