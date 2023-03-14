/**
 * @file maxstack.h
 * @brief  Archivo de especificación del TDA MaxStack
 * @author Garcia Mesa, Antonio Manuel
 * @author Cuesta Bueno, Fernando
 */

#include <iostream>
#include <queue>

using namespace std;

/**
 * @brief Struct que almacena los campos de cada elemento de la pila o la cola.
 * 
 */
struct element
{
    /**
     * @brief Valor entero del elemento.
     * 
     */
    int value,     // Current value to store
    /**
     * @brief Valor máximo que hay almacenado en la estructura (pila o cola).
     * 
     */
        maximun  ; // Current max value in the structure
};
/**
 * @brief Clase que implementa el TDA pila.
 */
class MaxStack
{
    public:
    /**
     * @brief Cola con la que se va a representar el TDA MaxStack.
     * 
     */
        queue<element> pila_max;

    public:
    /**
     * @brief Método que devuelve el top de la pila.
     * 
     * @return Instancia de tipo elemento con el top de la pila.
     */
        element top( );

    /**
     * @brief Método que extrae un elemento del top de la pila.
     * 
     */
        void pop( );

    /**
     * @brief Método comprueba si la pila está vacía.
     * @return True si está vacía, false si contiene elementos.
     */
        bool empty( );

    /**
     * @brief Método que devuelve el tamaño de la pila.
     * @return Entero con el tamaño de la pila.
     */
        int size( );
        
    /**
     * @brief Método que se encarga de añadir un elemento en el top de la pila.
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
