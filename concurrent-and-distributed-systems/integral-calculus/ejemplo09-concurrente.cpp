// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Alumno: Fernando Cuesta Bueno
// Clase: 2º Ingeniería Informática Grupo A1
//
// Ejemplo 9 (ejemplo9.cpp)
// Calculo concurrente de una integral.
//
// Historial:
// Plantilla creada en Abril de 2017
// Ejercicio realizado por el alumno en Octubre de 2022
//
// Breve descripción:
// El programa calculará una integral cuyo resultado es el número "pi".
//
// Esto lo realizará mediante 3 métodos:
//      - de forma secuencial
//      - de forma concurrente con hebras contiguas
//      - de forma concurrente con hebras entrelazadas
//
// El programa devuelve por pantalla una breve información sobre los resultados.
// -----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>  // incluye now, time\_point, duration
#include <future>
#include <vector>
#include <cmath>

using namespace std ;
using namespace std::chrono;

const long m  = 1024l*1024l*1024l, // número de muestras (del orden de mil millones)
           n  = 4;               // número de hebras concurrentes (divisor de 'm')


// -----------------------------------------------------------------------------
// evalua la función $f$ a integrar ($f(x)=4/(1+x^2)$)
double f ( double x )
{
  return 4.0/(1.0+x*x) ;
}
// -----------------------------------------------------------------------------
// calcula la integral de forma secuencial, devuelve resultado:
double calcular_integral_secuencial()
{
   double suma = 0.0 ;                        // inicializar suma
   for( long j = 0 ; j < m ; j++ )            // para cada $j$ entre $0$ y $m-1$:
   {  const double xj = double(j+0.5)/m ;     //      calcular $x_j$
      suma += f( xj );                        //      añadir $f(x_j)$ a la suma actual
   }

   return suma/m ;                            // devolver valor promedio de $f$
}

// -----------------------------------------------------------------------------
// función que ejecuta cada hebra: recibe $i$ ==índice de la hebra, ($0\leq i<n$)
double funcion_hebra_contigua ( long i )
{
	double suma_parcial = 0.0;                        // Inicializar la suma

	for(long j = i*(m/n); j < (i+1)*(m/n); j++){      // Para cada $j$ entre $0$ y $m-1$:
		const double xj = double(j+0.5)/m;        //      calcular
		suma_parcial += f(xj);                    //      añadir $f(x_j)$ a la suma actual
	}

	return suma_parcial/m;                            // Devolver el valor promedio de $f$
}

// -----------------------------------------------------------------------------
// función que ejecuta cada hebra: recibe $i$ ==índice de la hebra, ($0\leq i<n$)
double funcion_hebra_entrelazada ( long i )
{
    double suma_parcial = 0.0;                          // Inicializar la suma

    for(long j = i; j < m; j += n){      		// Para cada $j$ entre $0$ y $m-1$:
        const double xj = double(j+0.5)/m;              //      calcular
        suma_parcial += f(xj);                      	//      añadir $f(x_j)$ a la suma actual
    }

    return suma_parcial/m;                         	// Devolver el valor promedio de $f$
}

// -----------------------------------------------------------------------------
// calculo de la integral de forma concurrente
double calcular_integral_concurrente(int metodo)
{
	double suma_total = 0.0;

	future<double> futuros[n];

    if(metodo == 1)
      for(int i = 0; i < n; i++)
        futuros[i] = async(launch::async, funcion_hebra_contigua, i);

    else if(metodo == 2)
        for(int i = 0; i < n; i++)
            futuros[i] = async(launch::async, funcion_hebra_entrelazada, i);

    for (int i = 0; i < n; i++)
        suma_total += futuros[i].get();
	
	return suma_total;
}
// -----------------------------------------------------------------------------

int main()
{
  // Calculamos el inicio y el fin de la forma secuencial
  time_point<steady_clock> inicio_sec  = steady_clock::now() ;
  const double             result_sec  = calcular_integral_secuencial(  );
  time_point<steady_clock> fin_sec     = steady_clock::now() ;
  double x = sin(0.4567);

  // Calculamos el inicio y el fin de la forma concurrente con hebras contiguas
  time_point<steady_clock> inicio_conc_cont = steady_clock::now() ;
  const double             result_conc_cont = calcular_integral_concurrente(1);
  time_point<steady_clock> fin_conc_cont    = steady_clock::now() ;

  // Calculamos el inicio y el fin de la forma concurrente con hebras entrelazadas
  time_point<steady_clock> inicio_conc_entr = steady_clock::now() ;
  const double             result_conc_entr = calcular_integral_concurrente(2);
  time_point<steady_clock> fin_conc_entr    = steady_clock::now() ;

  // Calculamos los tiempos de cada forma
  duration<float,milli>    tiempo_sec       = fin_sec  - inicio_sec ,
                           tiempo_conc_cont = fin_conc_cont - inicio_conc_cont ,
                           tiempo_conc_entr = fin_conc_entr - inicio_conc_entr;

  // Calculamos la diferencia de tiempo entre los diferentes metodos en forma porcentual
  const float              porc_sec_cont        = 100.0*tiempo_conc_cont.count()/tiempo_sec.count();
  const float              porc_sec_entr        = 100.0*tiempo_conc_entr.count()/tiempo_sec.count();

  constexpr double pi = 3.14159265358979323846l ;

  // Mostramos los resultados
  cout << "Número de muestras (m)        : " << m << endl
       << "Número de hebras (n)          : " << n << endl
       << setprecision(18)
       << "Valor de PI                   : " << pi << endl
       << "Resultado secuencial          : " << result_sec  << endl
       << "Resultado concurrente_cont    : " << result_conc_cont << endl
       << "Resultado concurrente_entr    : " << result_conc_entr << endl
       << setprecision(5)
       << "Tiempo secuencial             : " << tiempo_sec.count()  << " milisegundos. " << endl
       << "Tiempo concurrente_cont       : " << tiempo_conc_cont.count() << " milisegundos. " << endl
       << "Tiempo concurrente_entr       : " << tiempo_conc_entr.count() << " milisegundos. " << endl
       << setprecision(4)
       << "Porcentaje t.conc_cont/t.sec. : " << porc_sec_cont << "%" << endl
       << "Porcentaje t.conc_entr/t.sec. : " << porc_sec_entr << "%" << endl;
}
