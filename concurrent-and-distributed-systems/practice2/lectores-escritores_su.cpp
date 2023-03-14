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

const int NUM_LECTORES  = 3; // Cantidad de hebras de lectores
const int NUM_ESCRITORES  = 3; // Cantidad de hebras de lectores

// Array de hebras lectores
thread Lector[NUM_LECTORES];

// Array de hebras escritores
thread Escritor[NUM_ESCRITORES];

// *****************************************************************************
// clase para monitor buffer, version FIFO, semántica SU, multiples escritores / lectores

class Lec_Esc : public HoareMonitor
{
 private:
    int n_lec;
    bool escrib;

 CondVar                       // colas condicion:
   lectura,                     //  cola donde esperan los lectores
   escritura ;                  //  cola donde esperan los escritores

 public:                                    // constructor y métodos públicos
    Lec_Esc( ) ;

    void ini_lectura( int num_hebra ) ;
    void fin_lectura( int num_hebra ) ;

    void ini_escritura( int num_hebra ) ;
    void fin_escritura( int num_hebra ) ;
} ;

Lec_Esc::Lec_Esc( )
{
    n_lec = 0;
    escrib = false;

    // inicializar variables de condicion
    lectura = newCondVar();
    escritura = newCondVar();
}

void Lec_Esc::ini_lectura ( int num_hebra )
{
    if ( escrib )
        lectura.wait();

    n_lec += 1;

    cout << "Lector "<< num_hebra << " : Entra un nuevo lector. Ahora hay " << n_lec << endl;

    lectura.signal( );
}

void Lec_Esc::fin_lectura ( int num_hebra )
{
    n_lec -= 1;

    cout << "Lector " << num_hebra << " : Termina un lector. Ahora hay " << n_lec << endl;

    if ( n_lec == 0 )
        escritura.signal( );
}

void Lec_Esc::ini_escritura ( int num_hebra )
{
    if ( n_lec > 0 || escrib )
        escritura.wait();

    cout << "Escritor " << num_hebra << " : Se empieza a escribir." << endl;

    escrib = true;
}

void Lec_Esc::fin_escritura ( int num_hebra )
{
    escrib = false;

    cout << "Escritor " << num_hebra << " : Se termina de escribir." << endl;

    if ( !lectura.empty() )
        lectura.signal();

    else
        escritura.signal();
} 

//----------------------------------------------------------------------
// función que ejecuta la hebra del lector

void funcion_hebra_lector( MRef<Lec_Esc> monitor, int num_hebra)
{
    while( true )
    {
        // iniciar lectura
        monitor->ini_lectura( num_hebra );

        // calcular milisegundos aleatorios de duración de la acción de "leer" y bloquear
        chrono::milliseconds duracion_leer( aleatorio<20,200>() );

        // espera bloqueada un tiempo igual a 'duracion_leer' milisegundos
        this_thread::sleep_for( duracion_leer );

        // terminar lectura
        monitor->fin_lectura( num_hebra );

        // calcular milisegundos aleatorios de duración de la acción de "resto de codigo"
        chrono::milliseconds duracion_resto_codigo( aleatorio<20,200>() );

        // espera bloqueada un tiempo igual a 'duracion_escribir' milisegundos
        this_thread::sleep_for( duracion_resto_codigo );
    }
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del escritor

void funcion_hebra_escritor( MRef<Lec_Esc> monitor, int num_hebra )
{
    while( true )
    {
        // iniciar escritura
        monitor->ini_escritura( num_hebra );

        // calcular milisegundos aleatorios de duración de la acción de "escribir"
        chrono::milliseconds duracion_escribir( aleatorio<20,200>() );

        // espera bloqueada un tiempo igual a 'duracion_escribir' milisegundos
        this_thread::sleep_for( duracion_escribir );

        // terminar lectura
        monitor->fin_escritura( num_hebra );

        // calcular milisegundos aleatorios de duración de la acción de "resto de codigo"
        chrono::milliseconds duracion_resto_codigo( aleatorio<20,200>() );

        // espera bloqueada un tiempo igual a 'duracion_escribir' milisegundos
        this_thread::sleep_for( duracion_resto_codigo );
    }
}

//----------------------------------------------------------------------

int main()
{
    // informacion
    cout << "--------------------------------------------------------------------" << endl
        << "Problema de los lectores - escritores (Monitor SU). " << endl
        << "--------------------------------------------------------------------" << endl
        << flush ;

   // crear monitor  ('monitor' es una referencia al mismo, de tipo MRef<...>)
   MRef<Lec_Esc> monitor = Create<Lec_Esc>() ;

   // iniciar hebras de escritores y lectores
    for (int i = 0; i < NUM_ESCRITORES; i++)
        Escritor[i] = thread( funcion_hebra_escritor, monitor, i );

    for (int i = 0; i < NUM_LECTORES; i++)
        Lector[i] = thread( funcion_hebra_lector, monitor, i );

    // join hebras
  
    for (int i = 0; i < NUM_ESCRITORES; i++)
        Escritor[i].join();

    for (int i = 0; i < NUM_LECTORES; i++)
        Lector[i].join();

    return 0;
}