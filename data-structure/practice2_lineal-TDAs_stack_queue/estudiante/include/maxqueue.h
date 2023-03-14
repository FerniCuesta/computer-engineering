/**
 * @file maxqueue.h
 * @brief  Archivo de especificación del TDA MaxQueue
 * @author Antonio Manuel Garcia Mesa
 * @author Fernando Cuesta Bueno
 */

#include <iostream>
#include <stack>

using namespace std;

struct element
{

    int value,     // Current value to store
        maximun  ; // Current max value in the structure
};

/**
* @brief Clase que implementa el TDA cola.
*/
class MaxQueue
{
    private:
    /**
     * @brief Pila con la que vamos a representar el TDA MaxQueue.
     * 
     */
        stack<element> cola_max;

    public:
    /**
     * @brief Método que devuelve el front de la cola.
     * 
     * @return Dato de tipo <element>.
     */
        element front();

    /**
     * @brief Método que extrae el elemento del front de la cola.
     * 
     */
        void pop();

    /**
     * @brief Método comprueba si la cola está vacía.
     * @return True si está vacía, false si contiene elementos.
     */
        bool empty( );

    /**
     * @brief Método que devuelve el tamaño de la cola.
     * @return Entero con el tamaño de la cola.
     */
        int size( );

    /**
     * @brief Método que se encarga de añadir un elemento en el back de la cola.
     * 
     * @param numero Valor del elemento que se va a insertar.
     */
        void push(int numero);
};
    /**
     * @brief Sobrecarga del operador << para poder realizar un flujo de salida de un elemento de la cola.
     * 
     * @param out Flujo de salida de los datos.
     * @param e Elemento que se va a enviar al flujo de salida.
     * @return El flujo de salida con el elemento a devolver.
     */
        ostream & operator << (ostream & out, const element & e);
