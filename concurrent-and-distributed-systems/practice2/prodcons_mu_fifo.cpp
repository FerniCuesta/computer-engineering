// -----------------------------------------------------------------------------
//
// Fernando Cuesta Bueno
// 2º Ingeniería Informática Grupo A1
//
// Sistemas concurrentes y Distribuidos.
// Seminario 2. Introducción a los monitores en C++11.
//
// Archivo: prodcons_mu_fifo.cpp
//
// Ejemplo de un monitor en C++11 con semántica SU, para el problema
// de los múltiples productores/consumidores.
//
// Opcion FIFO
//
// Historial:
// Creado el 30 Sept de 2022. (adaptado de prodcons2_su.cpp)
// 20 oct 22 --> paso este archivo de FIFO a LIFO, para que se corresponda con lo que dicen las transparencias
// 28 oct 22 --> ejercicio resuelto por el alumno a partir de la plantilla suministrada
// -----------------------------------------------------------------------------------


#include <iostream>
#include <iomanip>
#include <cassert>
#include <random>
#include <thread>
#include "scd.h"

using namespace std ;
using namespace scd ;

constexpr int num_items = 1500 ;   // número de items a producir/consumir

constexpr int  min_ms    = 5,     // tiempo minimo de espera en sleep_for
               max_ms    = 20 ;   // tiempo máximo de espera en sleep_for

mutex
   mtx ;                 // mutex de escritura en pantalla

unsigned
   cont_prod[num_items] = {0}, // contadores de verificación: producidos
   cont_cons[num_items] = {0}; // contadores de verificación: consumidos

const int NUM_HEBRAS_PRODUCTORAS  = 5, // Cantidad de hebras productoras
          NUM_HEBRAS_CONSUMIDORAS = 3; // Cantidad de herbas consumidoras

int const 
    p = num_items/NUM_HEBRAS_PRODUCTORAS , // Cantidad de valores que produce cada hebra productora
    c = num_items/NUM_HEBRAS_CONSUMIDORAS; // Cantidad de valores que consume cada hebra consumidora

// Vector con el número de items producidos por cada hebra productora
int items_producidos[NUM_HEBRAS_PRODUCTORAS] = {0};

// Numero de valores con los que cuenta el vector en cada instante
int num_valores = 0;

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato( int ih )
{
   this_thread::sleep_for( chrono::milliseconds( aleatorio<min_ms,max_ms>() ));
   const int valor_producido = ih * p + items_producidos[ih];
   items_producidos[ih] ++ ;
   mtx.lock();
   cout << "Produce " << valor_producido << " | Hebra " << ih << endl << flush ;
   mtx.unlock();
   cont_prod[valor_producido]++ ;
   return valor_producido ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned valor_consumir, int ih)
{
   if ( num_items <= valor_consumir )
   {
      cout << " valor a consumir === " << valor_consumir << ", num_items == " << num_items << endl ;
      assert( valor_consumir < num_items );
   }
   cont_cons[valor_consumir] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<min_ms,max_ms>() ));
   mtx.lock();
   cout << "                  Consume: " << valor_consumir << " | Hebra " << ih << endl ;
   mtx.unlock();
}
//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." << endl ;

   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

// *****************************************************************************
// clase para monitor buffer, version FIFO, semántica SC, multiples prod/cons

class ProdConsSU1 : public HoareMonitor
{
 private:
 static const int           // constantes ('static' ya que no dependen de la instancia)
   num_celdas_total = 10;   //   núm. de entradas del buffer
 int                        // variables permanentes
   buffer[num_celdas_total],//   buffer de tamaño fijo, con los datos
   primera_libre ,          //   indice de celda de la próxima inserción ( == número de celdas ocupadas)
   primera_ocupada;         //   indice de celda de la próxima extracción

 CondVar                    // colas condicion:
   ocupadas,                //  cola donde espera el consumidor (n>0)
   libres ;                 //  cola donde espera el productor  (n<num_celdas_total)

 public:                    // constructor y métodos públicos
   ProdConsSU1() ;             // constructor
   int  leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir( int valor ); // insertar un valor (sentencia E) (productor)
} ;
// -----------------------------------------------------------------------------

ProdConsSU1::ProdConsSU1(  )
{
   primera_libre   = 0 ;
   primera_ocupada = 0;
   ocupadas        = newCondVar();
   libres          = newCondVar();
}
// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato

int ProdConsSU1::leer(  )
{
   // esperar bloqueado hasta que 0 < primera_libre
   if ( num_valores == 0 )
      ocupadas.wait();

   //cout << "leer: ocup == " << primera_libre << ", total == " << num_celdas_total << endl ;
   assert( 0 < num_valores );

   // hacer la operación de lectura, actualizando estado del monitor
   const int valor = buffer[primera_ocupada % num_celdas_total] ;
   primera_ocupada++;
   num_valores--;

   // señalar al productor que hay un hueco libre, por si está esperando
   libres.signal();

   // devolver valor
   return valor ;
}
// -----------------------------------------------------------------------------

void ProdConsSU1::escribir( int valor )
{
   // esperar bloqueado hasta que primera_libre < num_celdas_total
   if ( num_valores == num_celdas_total )
      libres.wait();

   //cout << "escribir: ocup == " << primera_libre << ", total == " << num_celdas_total << endl ;
   assert( num_valores < num_celdas_total );

   // hacer la operación de inserción, actualizando estado del monitor
   buffer[primera_libre % num_celdas_total] = valor ;
   primera_libre++ ;
   num_valores++;

   // señalar al consumidor que ya hay una celda ocupada (por si esta esperando)
   ocupadas.signal();
}
// *****************************************************************************
// funciones de hebras

void funcion_hebra_productora( MRef<ProdConsSU1> monitor, int ih) // Con $ih$ indicamos el índice de la hebra productora
{
   for( unsigned i = 0 ; i < p ; i++ )
   {
      int valor = producir_dato( ih ) ;
      monitor->escribir( valor );
   }
}
// -----------------------------------------------------------------------------

void funcion_hebra_consumidora( MRef<ProdConsSU1>  monitor, int ih) // Con $ih$ indicamos el índice de la hebra consumidora
{
   for( unsigned i = 0 ; i < c ; i++ )
   {
      int valor = monitor->leer();
      consumir_dato( valor, ih ) ;
   }
}
// -----------------------------------------------------------------------------

int main()
{
    cout << "-----------------------------------------------------------------------------" << endl
        << "Problema de los múltiples productores-consumidores (Monitor SU, buffer FIFO). " << endl
        << "------------------------------------------------------------------------------" << endl
        << flush ;

    // crear monitor  ('monitor' es una referencia al mismo, de tipo MRef<...>)
    MRef<ProdConsSU1> monitor = Create<ProdConsSU1>() ;

    // crear y lanzar las hebras
    thread   productoras  [NUM_HEBRAS_PRODUCTORAS],
            consumidoras [NUM_HEBRAS_CONSUMIDORAS];

    for(int i = 0; i < NUM_HEBRAS_PRODUCTORAS; i++)
        productoras[i] = thread(funcion_hebra_productora, monitor, i);

    for(int i = 0; i < NUM_HEBRAS_CONSUMIDORAS; i++)
        consumidoras[i] = thread(funcion_hebra_consumidora, monitor, i);

    // esperar a que terminen las hebras
    for(int i = 0; i < NUM_HEBRAS_PRODUCTORAS; i++)
        productoras[i].join();

    for(int i = 0; i < NUM_HEBRAS_CONSUMIDORAS; i++)
        consumidoras[i].join();

    test_contadores() ;
}
