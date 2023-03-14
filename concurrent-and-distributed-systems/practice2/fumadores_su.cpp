/***************************************************************************/
/***************************************************************************/
// SISTEMAS CONCURRENTES Y DISTRIBUIDOS
//
// (C) FERNANDO CUESTA BUENO
// 2º INGENIERIA INFORMATICA GRUPO A1
//
// Fichero: fumadores_su.cpp
//
// Problema de los fumadores resuelto con un monitor 
// en C++11 con semántica SU, con estanquero único y varios fumadores.
// 
// Fecha: 4 de noviembre de 2022
//
/***************************************************************************/
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

// Numero de fumadores 
const int NUM_FUMADORES = 3 ;

// Array de  hebras fumadores
thread Fumador[NUM_FUMADORES];

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)

int ProducirIngrediente()
{
    // calcular milisegundos aleatorios de duración de la acción de fumar)
    chrono::milliseconds duracion_produ( aleatorio<10,100>() );

    // informa de que comienza a producir
    cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

    // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
    this_thread::sleep_for( duracion_produ );

    // produce ingrediente aleatorio
    const int num_ingrediente = aleatorio<0, NUM_FUMADORES - 1>() ;

    // informa de que ha terminado de producir
    cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

    // devuelve ingrediente
    return num_ingrediente ;
}


//-------------------------------------------------------------------------
// Función que simula la acción de fumar como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{
    // calcular milisegundos aleatorios de duración de la acción de fumar
    chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

    // informa de que comienza a fumar
    cout << "Fumador " << num_fumador << "  :"
            << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

    // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
    this_thread::sleep_for( duracion_fumar );

    // informa de que ha terminado de fumar
    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
}


// *****************************************************************************
// clase para monitor buffer, version FIFO, semántica SC, único prod/cons

class Estanco : public HoareMonitor
{
 private:
    int mostrador;         // el mostrador almacena el indice del ingrediente que contiene
                           // si vale -1 implica que está vacío

 CondVar                       // colas condicion:
   estanquero,                 //  cola donde espera el estanquero (mostrador lleno)
   fumadores[NUM_FUMADORES] ;  //  array de colas donde esperan los fumadores (mostrador vacío)

 public:                                    // constructor y métodos públicos
   Estanco() ;                              // constructor
   void obtenerIngrediente ( int num_ingrediente ) ;                 
   void ponerIngrediente ( int num_ingrediente ) ;
   void esperarRecogidaIngrediente ( ) ; 
} ;

// -----------------------------------------------------------------------------
// Metodos del monitor

Estanco::Estanco(  )
{
    mostrador = -1;                 // mostrador vacío
    estanquero = newCondVar();

    for(int i = 0; i < NUM_FUMADORES; i++)
        fumadores[i]  = newCondVar();
}

void Estanco::obtenerIngrediente( int num_ingrediente )
{
    // si no está su ingrediente, se bloquea
    if ( mostrador != num_ingrediente )
        fumadores[num_ingrediente].wait();

    // retirar ingrediente, mostrador vacío
    mostrador = -1;

    // Informar del ingrediente retirado
    cout << "Retirado ingrediente " << num_ingrediente << endl;
        
    // desbloquear al estanquero
    estanquero.signal() ;
}

void Estanco::ponerIngrediente( int num_ingrediente )
{
    // informa de que ha puesto un ingrediente
    cout << "Estanquero : pone ingrediente " << num_ingrediente << " en el mostrador." << endl;

    // poner ingrediente
    mostrador = num_ingrediente;

    // desbloquear al fumador
    fumadores[num_ingrediente].signal();
}

void Estanco::esperarRecogidaIngrediente (  )
{
    // bloquear al estanquero si el mostrador está lleno
    if( mostrador != -1 ){
        // informa de que va a bloquearse
        cout << "Estanquero : espera recogida del ingrediente." << endl;
        estanquero.wait() ;
    }
}


//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador

void funcion_hebra_fumador( MRef<Estanco> monitor, int num_fumador )
{
    while( true )
    {
        // comprobar que el mostrador este lleno
        monitor->obtenerIngrediente( num_fumador );
        
        // fumar
        fumar( num_fumador );
    }
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero( MRef<Estanco> monitor )
{
   while ( true )
   {
        // obtener el indice del ingrediente
        int ingrediente = ProducirIngrediente(  ) ;

        monitor->ponerIngrediente( ingrediente ) ;
        monitor->esperarRecogidaIngrediente(  ) ;
   }
}

//----------------------------------------------------------------------

int main()
{
    // informacion
    cout << "--------------------------------------------------------------------" << endl
        << "Problema de los fumadores (Monitor SU, buffer LIFO). " << endl
        << "--------------------------------------------------------------------" << endl
        << flush ;

   // crear monitor  ('monitor' es una referencia al mismo, de tipo MRef<...>)
   MRef<Estanco> monitor = Create<Estanco>() ;

   // iniciar hebra estanquero
   thread hebra_estanquero( funcion_hebra_estanquero, monitor ) ;

   // iniciar hebras fumadores
   for (int i = 0; i < NUM_FUMADORES; i++)
      Fumador[i] = thread( funcion_hebra_fumador, monitor, i );

   // join hebras
   hebra_estanquero.join();
  
   for (int i = 0; i < NUM_FUMADORES; i++)
      Fumador[i].join();

   return 0;
}