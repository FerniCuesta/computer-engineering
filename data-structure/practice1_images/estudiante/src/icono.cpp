/***************************************************************************/
/***************************************************************************/
// Estructura de Datos
//
// (C) FERNANDO CUESTA BUENO
// (C) ANTONIO MANUEL GARCIA MESA
//
// 2º INGENIERIA INFORMATICA GRUPO A1
//
// Fichero: icono.cpp
//
// Programa que recibe 
// <Imagen original> <Imagen de destino> <Fila inicial> <Columna inicial> <Alto> <Ancho>
// y almacena en el destino la subimagen requerida
//
// Fecha: 22 de octubre de 2022
//
/***************************************************************************/
/***************************************************************************/

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){
 
  char *origen, *destino; // nombres de los ficheros
  Image image;

  // Comprobar validez de la llamada
  if (argc != 4){
    cerr << "Error: Numero incorrecto de parametros.\n";
    cerr << "Uso: icono.cpp <fich_orig> <fich_rdo> <factor>\n";
    exit (1);
  }

  // Obtener argumentos
  origen  = argv[1];
  destino = argv[2];

  int factor = atoi(argv[3]);

  // Mostramos argumentos
  cout << endl;
  cout << "Fichero origen: " << origen << endl;
  cout << "Fichero resultado: " << destino << endl;

  // Leer la imagen del fichero de entrada
  if (!image.Load(origen)){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  // Mostrar los parametros de la Imagen
  cout << endl;
  cout << "Dimensiones de " << origen << ":" << endl;
  cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

  // Calcular la subimagen
  Image icono = image.Subsample(factor);

  // Guardar la imagen resultado en el fichero
  if (icono.Save(destino))
    cout  << "La imagen se guardo en " << destino << endl;
  else{
    cerr << "Error: No pudo guardarse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    return 1;
  }

  return 0;
}
