/***************************************************************************/
/***************************************************************************/
// SISTEMAS CONCURRENTES Y DISTRIBUIDOS
//
// (C) FERNANDO CUESTA BUENO
// 2º INGENIERIA INFORMATICA GRUPO A1
//
// Fichero: prodcons-multi-fifo.cpp
//
// Problema de varios productores y varios consumidores con semáforos
// Solución implementada con un buffer tipo FIFO (cola circular)
// 
// Fecha: 17 de octubre de 2022
// 
// Este archivo es una modificación de la plantilla suministrada
//
/***************************************************************************/
/***************************************************************************/

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include <future>
#include "scd.h"

using namespace std ;
using namespace scd ;

//**********************************************************************
// Variables globales

const unsigned 
   num_items = 80 ,   // número de items
   tam_vec   = 10 ;   // tamaño del buffer

unsigned  
   cont_prod[num_items] = {0}, // contadores de verificación: para cada dato, número de veces que se ha producido.
   cont_cons[num_items] = {0}; // contadores de verificación: para cada dato, número de veces que se ha consumido.

// Semáforos
Semaphore
    libres      = tam_vec,
    ocupadas    = 0      ,
    acceso_prod = 1      ,
    acceso_cons = 1      ;



// Buffer intermedio y variable para controlar qué dato se va a leer
    unsigned buffer[tam_vec];
    int primera_libre   = 0;
    int primera_ocupada = 0;

const int NUM_HEBRAS_PROD  = 4,  // número de hebras productoras
           NUM_HEBRAS_CONS = 4;  // número de hebras consumidoras

const int p = num_items / NUM_HEBRAS_PROD, // Lo que acceso cada productor
          c = num_items / NUM_HEBRAS_CONS; // Lo que consume cada consumidor

// Vector con el número de items producidos por cada hebra productora
int items_producidos[NUM_HEBRAS_PROD] = {0};

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

unsigned producir_dato(unsigned ih) // Con $ih$ indicamos el índice de la hebra productora
{
   // Retraso aleatorio
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   // Producimos el dato
   const unsigned dato_producido = ih * p +  items_producidos[ih];

   // Contabilizamos el dato producido
   cont_prod[dato_producido] ++ ;

   // Aumentamos el contador de items producidos por cada hebra
   items_producidos[ih]++;

   // Imprimimos por pantalla el dato producido
   cout << "producido: " << dato_producido << " | Hebra: " << ih << endl << flush;

   // Devolvemos el dato producido
   return dato_producido ;
}
//----------------------------------------------------------------------

void consumir_dato(unsigned dato, int ih) // Con $ih$ indicamos el índice de la hebra consumidora
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                              consumido: " << dato << " | Hebra: " << ih << endl ;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora(unsigned ih) // Con $ih$ indicamos el índice de la hebra productora
{
   for( unsigned i = 0; i < p ; i++ )
   {
      int dato = producir_dato(ih) ;
        sem_wait(libres);
        sem_wait(acceso_prod);
        buffer[primera_ocupada % tam_vec] = dato;
        primera_ocupada++;
        sem_signal(acceso_prod);
        sem_signal(ocupadas);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(unsigned ih) // Con $ih$ indicamos el índice de la hebra consumidora
{
   for( unsigned i = 0 ; i < c ; i++ )
   {
      int dato;
      sem_wait(ocupadas);
      sem_wait(acceso_cons);
      dato = buffer[primera_libre % tam_vec];
      primera_libre++;
      sem_signal(libres);
      sem_signal(acceso_cons);
      consumir_dato( dato, ih ) ;
    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los múltiples productores-consumidores (solución FIFO)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

   // Vector de hebras
	thread productoras[NUM_HEBRAS_PROD];

	thread consumidoras[NUM_HEBRAS_CONS];

   // Lanzamos las hebras productoras
   for(int i = 0; i < NUM_HEBRAS_PROD; i++)
      productoras[i] = thread(funcion_hebra_productora, i);


   // Lanzamos las hebras consumidoras
   for(int i = 0; i < NUM_HEBRAS_CONS; i++)
      consumidoras[i] = thread(funcion_hebra_consumidora, i);


   // Join
   for(int i = 0; i < NUM_HEBRAS_PROD; i++)
      productoras[i].join();

   for(int i = 0; i < NUM_HEBRAS_PROD; i++)
      consumidoras[i].join();

   // Fin del programa
   cout << "FIN" << endl;
   
   test_contadores();
}
