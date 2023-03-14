#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

#include<map>
#include <iostream>
#include <string>
using namespace std;
/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

struct LetterInfo 
{
    /**
     * @brief Veces que se repite la letra
     * 
     */
    int repetitions;
    /**
     * @brief Puntuación de la letra
     * 
     */
    int score;
};

/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */


class LettersSet
{
    private:
    /**
     * @brief Contenedor donde vamos a almacenar el conjunto de letras
     * 
     */
        map <char, LetterInfo> letters;

    public:
        // declarar class const_iterator para hacerla friend en class iterator
        class const_iterator;

        /**
         * @brief Esta clase es necesaria para poder recorrer el map de forma secuencial 
         * y realizar operaciones sobre él
         * 
         */
        class iterator
        {
            private:
            /**
             * @brief Este iterador nos permitirá consultar para cada letra 
             * su valor asociado.
             */
                map <char, LetterInfo> :: iterator it;
            
            public:
            /**
             * @brief Constructor por defecto
             * @return Devuelve un iterador vacío
             * 
             */
                inline iterator(  ){}
                /**
                 * @brief Sobrecarga del operador ++ para poder recorrer el map de forma secuencial hacia delante
                 * 
                 */
                inline iterator & operator ++()
                {
                    ++it;
                    return *this;
                }
                /**
                 * @brief Sobrecarga del operador -- para poder recorrer el map de forma secuencial hacia atrás
                 * 
                 */
                inline iterator & operator--()
                {
                    --it;
                    return *this;
                }
                /**
                 * @brief Sobrecarga del operador * para poder ver el valor del iterador
                 * 
                 */
                inline pair <const char, LetterInfo> & operator *()
                {
                    return (*this->it);
                }
                /**
                 * @brief Sobrecarga del operador == para poder comparar iteradores
                 * 
                 * @param i Otro iterador
                 * @return true si son iguales
                 * @return false si son distintos
                 */
                inline bool operator ==(const iterator & i) const
                {
                    return (this->it == i.it);
                }
                /**
                 * @brief Sobrecarga del operador != para poder comparar iteradores
                 * 
                 * @param i Otro iterador
                 * @return true Si son distintos
                 * @return false Si son iguales
                 */
                inline bool operator != (const iterator & i) const
                {
                    return (this->it != i.it);
                }

                friend class LettersSet;
                friend class const_iterator;

        }; // class iterator
        /**
         * @brief Clase para recorrer los objetos LettersSet constantes
         * 
         */
        class const_iterator
        {
            private:
                map <char, LetterInfo> :: const_iterator it;
            
            public:
            /**
             * @brief Constructor por defecto 
             * @return devuelve un iterador que apunta hacia nullptr
             */
                inline const_iterator(  ):it(nullptr){}
                /**
                 * @brief Constructor de copia 
                 * 
                 * @param i iterador con el que se va a crear el nuevo
                 * @return devuelve un iterador igual que el que se pasa por parámetro 
                 */
                inline const_iterator( const iterator & i ):it(i.it){}
                /**
                 * @brief sobrecarga del operador * para poder ver el valor de este
                 *
                 */
                inline const pair <const char, LetterInfo> & operator *()
                {
                    return (*this->it);
                }
                /**
                 * @brief Sobrecarga del operador ++ para poder recorrer el map de forma secuencial hacia delante
                 * 
                 */
                inline const_iterator & operator ++()
                {
                    ++it;
                    return *this;
                }
                /**
                 * @brief Sobrecarga del operador -- para poder recorrer el map de forma secuencial hacia atrás
                 * 
                 */
                inline const_iterator & operator--()
                {
                    --it;
                    return *this;
                }
                /**
                 * @brief Sobrecarga del operador == para poder comparar iteradores   
                 * 
                 * @param i Iterador con el que se va a comparar
                 * @return true si son iguales
                 * @return false si no son iguales
                 */
                inline bool operator==(const const_iterator & i) const
                {
                    return this->it == i.it;
                }
                /**
                 * @brief Sobrecarga del operador != para poder comparar iteradores
                 * 
                 * @param i Iterador con el que se va a comparar
                 * @return true si son distintos
                 * @return false si no son distintos
                 */
                bool operator != (const const_iterator & i) const
                {
                    return this->it != i.it;
                }

                friend class LettersSet;

        }; // class const_iterator
        /**
         * @brief Constructor por defecto.
         * @return Objeto LettersSet vacío.
         * 
         */
        inline LettersSet(  ){}
        /**
         * @brief Constructor de copia.
         * 
         * @param other LettersSet a copiar
         * 
         * @return Objeto con los mismos valores que other.
         */
        inline LettersSet( const LettersSet & other )
        {
            this->letters = other.letters;
        }
        /**
         * @brief Inserta un elemento en el LettersSet
         * 
         * @param val valor que queremos insertar
         * @return booleano que marca si se ha podido insertar la letra en el LettersSet.
         * La letra sólo se inserta correctamente si no estaba aún incluida
         * en la colección
         */
        inline bool insert( const pair<char, LetterInfo> & val )
        {
            return this->letters.insert( val ).second;
        }
        /**
         * @brief Elimina un carácter del LettersSet
         * 
         * @param key Carácter a eliminar
         * @return Booleano que indica si se ha podido eliminar correctamente
         * la letra del LettersSet
         */
        bool erase( const char & key )
        {
            return this->letters.erase( key );
        }
        /**
         * @brief Elimina todo el contenido del LettersSet
         * 
         */
        void clear(  )
        {
            this->letters.clear();
        }
        /**
         * @brief Consulta si el LettersSet está vacío
         * 
         * @return true si el LettersSet está vacío 
         * @return false en caso contrario
         */
        bool empty(  ) const
        {
            return this->letters.empty();
        }
        /**
         * @brief Tamaño del LettersSet
         * 
         * @return Número de elementos en el LettersSet
         */
        unsigned int size(  ) const
        {
            return this->letters.size();
        }
        /**
         * @brief Indica el principio del map
         * 
         */
        inline iterator begin()
        {
            iterator i;

            i.it = this->letters.begin();

            return i;
        }
        /**
         * @brief Indica el final del map
         *  
         */
        inline iterator end()
        {
            iterator i;

            i.it = this->letters.end();

            return i;
        }
        /**
         * @brief Indica el principio del map para objetos constantes
         * 
         */
        inline const_iterator cbegin() const
        {
            const_iterator i;

            i.it = this->letters.cbegin();

            return i;
        }
        /**
         * @brief Indica el final del map para objetos constantes
         * 
         */
        inline const_iterator cend() const
        {
            const_iterator i;

            i.it = this->letters.cend();

            return i;
        }
        /**
         * @brief Calcula la puntuación dada una palabra.
         * 
         * @param word String con la palabra cuya puntuación que queremos calcular
         * @return Puntuación de la palabra, calculada como la suma de las puntuaciones de una de sus letras
         */
        int getScore( string word );
        /**
         * @brief Sobrecarga del operador de asignacion
         * 
         * @param cl LettersSet a copiar
         * @return Referencia al objeto this para poder encadenar el operador
         */
        LettersSet & operator = ( const LettersSet & cl );
        /**
         * @brief Sobrecarga del operador de consulta.
         * @brief Permite acceder a los elementos del map que hay en nuestra clase
         * 
         * @param val Carácter a consultar
         * @return Estructura de tipo LetterInfo con la información del carácter consultado:
         * Número de repeticiones y puntuación
         */
        LetterInfo & operator[] ( const char & val );
        /**
         * @brief Sobrecarga del operador de entrada
         * 
         * @param is Flujo de entrada del que leer el LettersSet
         * @param cl LettersSet en el que almacenar la información leída
         */
        friend istream & operator >> (istream & is, LettersSet & cl);
        /**
         * @brief Sobrecarga del operador de salida
         * 
         * @param os Flujo de salida donde escribir el LettersSet
         * @param cl LettersSet en el que se escribe
         */
        friend ostream & operator << (ostream & os, const LettersSet & cl);

};

#endif
