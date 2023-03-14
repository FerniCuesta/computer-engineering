// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-plantilla.cpp
// Implementación del problema de los filósofos (sin camarero).
// Plantilla para completar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------


#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_filosofos    = 5 ,                   // número de filósofos 
   num_filo_ten     = 2*num_filosofos,      // número de filósofos y tenedores 
   num_procesos     = num_filo_ten + 1,     // número de procesos total (filosofos + tenedores + camarero)
   etiq_tenedor     = 0,                    // etiqueta de los procesos tenedor
   id_camarero      = num_procesos - 1,     // id del camarero
   etiq_sentarse    = 1,					// etiqueta para solicitar sentarse en la mesa
   etiq_levantarse  = 2;					// etiqueta para solicitar levantarse de la mesa

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

// ---------------------------------------------------------------------

void funcion_filosofos( int id )
{
  int id_ten_izq = (id+1)              % num_filo_ten, //id. tenedor izq.
      id_ten_der = (id+num_filo_ten-1) % num_filo_ten, //id. tenedor der.
      peticion;

  while ( true )
  {
    // 1. Sentarse
    MPI_Ssend( &peticion, 1, MPI_INT, id_camarero, etiq_sentarse, MPI_COMM_WORLD );
	cout << "Filósofo " << id << " se sienta a comer." << endl;

    // 2. Tomar tenedores
    // solicitar tenedor izquierdo
    cout << "Filósofo " << id << " solicita ten. izq." << id_ten_izq << endl;
    MPI_Ssend( &peticion, 1, MPI_INT, id_ten_izq, etiq_tenedor, MPI_COMM_WORLD );

    // solicitar tenedor derecho
    cout << "Filósofo " << id << " solicita ten. der." << id_ten_der << endl;
    MPI_Ssend( &peticion, 1, MPI_INT, id_ten_der, etiq_tenedor, MPI_COMM_WORLD );

    // 3. Comer
    cout << "Filósofo " << id << " comienza a comer" << endl ;
    sleep_for( milliseconds( aleatorio<10,100>() ) );

    // 4. Soltar tenedores
    // soltar el tenedor izquierdo
    cout << "Filósofo " << id << " suelta ten. izq. " << id_ten_izq << endl;
    MPI_Ssend( &peticion, 1, MPI_INT, id_ten_izq, etiq_tenedor, MPI_COMM_WORLD );

    // soltar el tenedor derecho
    cout << "Filósofo " << id << " suelta ten. der. " << id_ten_der << endl;
    MPI_Ssend( &peticion, 1, MPI_INT, id_ten_der, etiq_tenedor, MPI_COMM_WORLD );

    // 5. Levantarse
    MPI_Ssend( &peticion, 1, MPI_INT, id_camarero, etiq_levantarse, MPI_COMM_WORLD );
	cout << "Filósofo " << id << " se levanta de la mesa." << endl;

    // 6. Pensar
    cout << "Filosofo " << id << " comienza a pensar" << endl;
    sleep_for( milliseconds( aleatorio<10,100>() ) );
 }
}
// ---------------------------------------------------------------------

void funcion_tenedores( int id )
{
  int valor, id_filosofo ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones

  while( true )
  {
      // recibir petición de cualquier filósofo
      MPI_Recv( &valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_tenedor, MPI_COMM_WORLD, &estado );

      // guardar en 'id_filosofo' el id. del emisor
      id_filosofo = estado.MPI_SOURCE;
      cout << "Ten. " << id << " ha sido cogido por filo. " << id_filosofo << endl;

      // recibir liberación de filósofo 'id_filosofo'
      MPI_Recv( &valor, 1, MPI_INT, id_filosofo, etiq_tenedor, MPI_COMM_WORLD, &estado );
      cout << "Ten. " << id << " ha sido liberado por filo. " << id_filosofo << endl ;
  }
}
// ---------------------------------------------------------------------

void funcion_camarero(  )
{
    int valor,                  // valor recibido
        cantidad = 0,           // número de filósofos entados en cada momento
        etiq_emisor_aceptable;  // etiqueta del emisor del que se puede rescibir un mensaje

	MPI_Status estado ;         // metadatos de las dos recepciones
    
	while( true )
	{
		if( cantidad == 4 )								// si ya hay 4 filósofos sentados
			etiq_emisor_aceptable = etiq_levantarse;	//	solo se pueden levantar
		else											// si hay menos de 4 filósofos
			etiq_emisor_aceptable = MPI_ANY_TAG; 		//	se pueden levantar o sentar

		MPI_Recv( &valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_emisor_aceptable, MPI_COMM_WORLD, &estado );

		if( estado.MPI_TAG == etiq_sentarse )
		{
			cantidad++;
			cout << "Camarero: se sienta otro filósofo a comer. Ahora hay " << cantidad << endl;
		}
		else
		{
			cantidad--;
			cout << "Camarero: se levanta un filósofo de la mesa. Ahora hay " << cantidad << endl;
		}
	}
}
// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if( num_procesos == num_procesos_actual )
   {
      // ejecutar la función correspondiente a 'id_propio'
      if( id_propio == id_camarero )    // si es el último proceso
        funcion_camarero(  );           //   es el camarero
      else if ( id_propio % 2 == 0 )    // si es par
        funcion_filosofos( id_propio ); //   es un filósofo
      else                              // si es impar
        funcion_tenedores( id_propio ); //   es un tenedor
   }
   else
   {
      if( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { 
        cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
