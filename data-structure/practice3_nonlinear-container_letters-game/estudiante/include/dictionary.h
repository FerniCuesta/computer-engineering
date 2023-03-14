#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#include <set>
#include <vector>
#include <string>

using namespace std;

/**
 * @brief TDA Dictionary
 * @details Almacena las palabras de un fichero de texto y permite iterar sobre ellas
 *
 */

class Dictionary
{
    private:
    /**
     * @brief Contenedor de tipo Set para almacenar los elementos del diccionario
     * 
     */
        set <string> words;

    public:
            // declarar class const_iterator para hacerla friend en class iterator
        class const_iterator;
        /**
         * @brief Clases para poder recorrer el set de forma secuencial 
         * y realizar operaciones sobre él
         * 
         */
        class iterator
        {
            
            /**
             * @brief Este iterador nos permitirá recorrer el diccionario 
             */
            private:
                set <string> :: iterator it;
            
            public:
                /**
                 * @brief Constructor por defecto
                 * 
                 */
                inline iterator(  ){}

                /**
                 * @brief Sobrecarga del operador ++ para poder recorrer el set de manera secuencial hacia delante
                 * @return Iterador al siguiente elemento
                 */
                inline iterator & operator ++()
                {
                    ++it;
                    return *this;
                }

                /**
                 * @brief Sobrecarga del operador -- para poder recorrer el set de manera secuencial hacia atrás
                 * @return Itereador al elemento anterior
                 */
                inline iterator & operator--()
                {
                    --it;
                    return *this;
                }

                /**
                 * @brief Sobrecarga del operador * para poder ver el valor del iterador
                 * @return El valor del iterador
                 */
                inline const string & operator *()
                {
                    return (*this->it);
                }

                /**
                 * @brief Sobrecarga del operador == para ver si dos iteradores son iguales
                 * 
                 * @param i iterador para comparar
                 * @return true si son iguales
                 * @return false si no son iguales
                 */
                inline bool operator ==(const iterator & i) const
                {
                    return (this->it == i.it);
                }

                /**
                 * @brief Sobrecarga del operador != para poder comparar iteradores
                 * 
                 * @param i Otro iterador
                 * @return true si son distintos
                 * @return false Si son iguales
                 */
                inline bool operator != (const iterator & i) const
                {
                    return (this->it != i.it);
                }

                friend class Dictionary;
                friend class const_iterator;

        }; // class iterator
    /**
     * @brief Clase constante para recorrer los objetos de la clase Dictionary
     * 
     */
        class const_iterator
        {
            private:
                /**
                 * @brief iterador que recorrerá los objetos
                 * 
                 */
                set <string> :: const_iterator it;
            
            public:
                /**
                 * @brief Constructor por defecto 
                 * @return Inicializa el campo privado del iterador a nullptr
                 */
                inline const_iterator(  ):it(nullptr){}

                /**
                 * @brief Constructor de copia 
                 * 
                 * @param i iterador que se va a copiar en el nuevo
                 * @return Inicializa el campo privado del iterador al pasado como argumento 
                 */
                inline const_iterator( const iterator & i ):it(i.it){}

                /**
                 * @brief sobrecarga del operador * para poder ver el valor de este
                 * 
                 */
                inline const string & operator *()
                {
                    return (*this->it);
                }

                /**
                 * @brief Sobrecarga del operador ++ para poder recorrer el set de manera secuencial hacia delante
                 * 
                 */
                inline const_iterator & operator ++()
                {
                    ++it;
                    return *this;
                }

                /**
                 * @brief Sobrecarga del operador -- para poder recorrer el set de manera secuencial hacia atrás 
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
                 * @return false si son distintos
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
                 * @return false si son iguales
                 */
                bool operator != (const const_iterator & i) const
                {
                    return this->it != i.it;
                }

                friend class Dictionary;

        }; // class const_iterator
        /**
         * @brief Indica el principio del set
         * @return Iterador al primer elemento del Set
         */
        inline iterator begin()
        {
            iterator i;

            i.it = this->words.begin();

            return i;
        }

        /**
         * @brief indica el fin del set
         * @return Iterador al último elemento del Set
         */
        inline iterator end()
        {
            iterator i;

            i.it = this->words.end();

            return i;
        }
        /**
         * @brief indica el principio del set de objetos constantes
         * @return Iterador constante al primer elemento del Set
         */
        inline const_iterator cbegin() const
        {
            const_iterator i;

            i.it = this->words.cbegin();

            return i;
        }
        /**
         * @brief indica el fin del set de objetos constantes
         * @return Iterador constante al último elemento del Set
         */
        inline const_iterator cend() const
        {
            const_iterator i;

            i.it = this->words.cend();

            return i;
        }
        /**
         * @brief Constructor por defecto.
         * Crea un Dictionary vacío
         * 
         */
        inline Dictionary(  ){}

        /**
         * @brief Constructor de copia
         * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
         * @param other Dictionary que se quiere copiar
         */
        inline Dictionary( const Dictionary & other )
        {
            this->words = other.words;
        }

        /**
         * @brief Indica si una palabra está en el diccionario o no.
         * Este método comprueba si una determinada palabra se encuentra o no en el diccionario.
         * 
         * @param val la palabra que se quiere buscar
         * @return True si la palabra existe en el diccionario, false en caso contrario
         */
        inline bool exists( const string & val ) const
        {
            return this->words.count( val );
        }

        /**
         * @brief Inserta una palabra en el diccionario
         * 
         * @param val palabra a insertar en el diccionario
         * @return True si la palabra insertada no existía previamente en el diccionario, false si ya estaba
         */
        inline bool insert( const string & val )
        {
            return this->words.insert( val ).second;
        }

        /**
         * @brief Elimina una palabra del diccionario
         * 
         * @param val Palabra a borrar del diccionario
         * @return Booleano que indica si la palabra se ha borrado del diccionario
         */
        inline bool erase( const string & val )
        {
            return this->words.erase( val );
        }

        /**
         * @brief Limpia el Dictionary
         * Elimina todas las palabras contenidas en el conjunto
         */
        inline void clear(  )
        {
            this->words.clear();
        }

        /**
         * @brief Comprueba si el diccionario está vacío
         * 
         * @return true si el diccionario está vacío
         * @return false en caso contrario
         */
        inline bool empty(  ) const
        {
            return this->words.empty();
        }

        /**
         * @brief Tamaño del diccionario
         * 
         * @return Número de palabras guardadas en el diccionario
         */
        inline unsigned int size(  ) const
        {
            return this->words.size();
        }

        /**
         * @brief Indica el número de apariciones de una letra
         * 
         * @param c letra a buscar
         * @return un entero indicando el número de apariciones
         */

        int getOccurrences( const char c );
        /**
         * @brief Cuenta el total de letras de un diccionario
         * 
         * @return Entero con el total de letras.
         */

        int getTotalLetters(  );
        /**
         * @brief Devuelve las palabras en el diccionario con una longitud dad
         * 
         * @param length Longitud de las palabras buscadas 
         * @return Vector de palabras con la longitud deseada
         */

        vector<string> wordsOfLength( int length );
        /**
         * @brief Sobrecarga del operador de salida.
         * Permite imprimir el diccionario completo a un flujo de salida
         * 
         * @param os Flujo de salida, donde imprimir el diccionario
         * @param dic Diccionario a imprimir
         * @return Flujo de salida, para poder encadenar el operador
         */

        friend ostream & operator<<( ostream & os, const Dictionary & dic );
        
        /**
         * @brief Sobrecarga del operador de entrada
         * Permite leer las palabras de un fichero de texto e introducirlas en el diccionario
         * @param is Flujo de entrada
         * @param dic Diccionario a rellenar
         * @return Flujo de entrada para poder encadenar el operador
         */

        friend istream & operator>>( istream & is, const Dictionary & dic );

};

#endif
