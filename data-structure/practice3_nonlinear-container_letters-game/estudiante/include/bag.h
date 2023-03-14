#ifndef __BAG_H__
#define __BAG_H__

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

/**
 *  @brief TDA Bolsa con las
 *
 *  @details Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */

template <class T>
class Bag
{
    private:
    /**
     * @brief Vector en el que se va a almacenar los elementos extraidos
     * 
     */
        vector <T> v;

    public:
    /**
     * @brief Clase para recorrer el vector de Bag 
     * 
     */
        class iterator
        {
            private:
                typename vector <T> :: iterator it;

            public:
                // constructor por defecto
                iterator(): it(nullptr){}

                T & operator*(){
                    return (*it);
                }

            friend class bag;

        };
        /**
         * @brief Constructor por defecto
         * @return Objeto vacío
         */
        inline Bag(  ){}        
        /**
         * @brief Constructor de copia
         * Crea una copia exacta de otro objeto de tipo Bag
         * 
         * @param other Objeto de tipo Bag<T> del que se va a realizar la copia
         */
        inline Bag( const Bag<T> & other )
        {
            this.v = other.v;
        }
        /**
         * @brief Añade un elemento a la bolsa
         * 
         * @param element elemento del tipo T a añadir a la bolsa
         */
        inline void add( const T & element )
        {
            this->v.push_back( element );
        }
        /**
         * @brief Extrae un elemento aleatorio de la bolsa
         * Devuelve un elemento aleatorio de la bolsa y lo elimina de la misma
         * 
         * @return Elemento de tipo T extraído de la bolsa
         * @pre La bolsa no está vacía
         * @post El elemento devuelto se ha eliminado de la bolsa
         */
        inline T get(  )
        {
            if( this->empty() ) // si está vacía sair del método
                exit(-1);

            // obtener un elemento aleatorio entre [ 0, size() )
            srand(( unsigned int ) time(NULL) );
            int indice = rand() % this->size();

            T elemento = this->v[indice];

            // crear un iterador 
            typename vector<T>::iterator it;

            // apuntar el iterador al inicio
            it = this->v.begin();

            // apuntar con el iterador al elemento que queremos eliminar
            for(int i = 0; i < indice; i++)
                ++it;

            // eliminar el elemento extraido
            this->v.erase( it );

            // devolver el elemento
            return elemento;
        }
        /**
         * @brief Método que elimina un elemento
         * 
         * @param indice posición del elemento que se va a elimina
         */
        inline void erase( int indice )
        {
            this->erase( indice );
        }
        /**
         * @brief Elimina todos los elementos de la bolsa
         * Borra todos los elementos almacenados en la bolsa
         * 
         */

        inline void clear(  )
        {
            this->v.clear();
        }
        /**
         * @brief Tamaño de la bolsa
         * @return Número de elementos que hay en la bolsa
         * 
         */
        inline unsigned int size(  )
        {
            return this->v.size();
        }
        /**
         * @brief Comprueba si la bolsa está vacía
         * 
         * @return true si la bolsa está vacía
         * @return false en caso contrario
         */
        inline bool empty(  )
        {
            return this->v.empty();
        }
        /**
         * @brief Sobrecarga del operador de asignación
         * 
         * @param other Bag<T> a copiar
         * @return Referencia a this para poder encadenar el operador
         */
        inline const Bag<T> & operator=( const Bag<T> & other )
        {
            this->v = other.v;

            return *this;
        }

};

#endif