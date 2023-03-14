/***************************************************************************/
/***************************************************************************/
// SISTEMAS CONCURRENTES Y DISTRIBUIDOS
//
// (C) FERNANDO CUESTA BUENO
// 2º INGENIERIA INFORMATICA GRUPO A1
//
// Fichero: fumadores.cpp
//
// Problema de los fumadores
// 
// Fecha: 19 de octubre de 2022
// 
// Este archivo es una modificación de la plantilla suministrada
//
/***************************************************************************/
/***************************************************************************/

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;

// Numero de fumadores 

const int num_fumadores = 3 ;

// Semáforos
Semaphore mostr_vacio = 1;
Semaphore ingr_disp[num_fumadores] = {0, 0, 0};

// Array de fumadores
thread fumadores[num_fumadores];

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)

int producir_ingrediente()
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero(  )
{
   while (true){
      // Obtenemos el indice del ingrediente producido
      int ingrediente = producir_ingrediente();

      // Comprobamos que el mostrador este vacio
      sem_wait(mostr_vacio);

      // Indicamos el ingrediente que hemos puesto en el mostrador
      cout << "Puesto ingrediente " << ingrediente << endl;

      // Aumentamos la disponibilidad de dicho ingrediente
      sem_signal(ingr_disp[ingrediente]);
   }
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
   while( true )
   {
      // Comprobar que haya disponibilidad del ingrediente
      sem_wait(ingr_disp[num_fumador]);
      
      // Informar del ingrediente retirado
      cout << "Retirado ingrediente " << num_fumador << endl;

      // Indicar que el mostrador está vacío
      sem_signal(mostr_vacio);

      // Fumar
      fumar(num_fumador);
   }
}

//----------------------------------------------------------------------

int main()
{
   // Ponemos al estanquero en marcha
   thread hebra_estanquero (funcion_hebra_estanquero);

   // Ponemos a los fumadores en marcha
   for (int i = 0; i < num_fumadores; i++)
      fumadores[i] = thread(funcion_hebra_fumador, i);

   // Join
   hebra_estanquero.join();
  
   for (int i = 0; i < num_fumadores; i++)
      fumadores[i].join();

   return 0;
}
