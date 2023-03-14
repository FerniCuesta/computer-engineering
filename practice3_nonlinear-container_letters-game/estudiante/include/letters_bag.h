#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__

#include "bag.h"
#include "letters_set.h"

using namespace std;
/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */

class LettersBag
{
    private:
		/**
		 * @brief Bolsa de la que vamos a extraer aleatoriamente el número de letras
		 * 
		 */
        Bag <char> letters;

    public:
        /**
         * @brief Constructor por defecto
         * @return devuelve un objeto vacío
         */
        inline LettersBag(  ){}

		/**
		 * @brief Constructor dado un LettersSet
		 * Dado un LettersSet como argumento, este constructor debe rellenar la LettersBag con las letras
		 * que contiene el LettersSet, introduciendo cada letra el número de veces indicado por el campo LetterInfo::repetitions.
		 * 
		 * 
		 * @param letterSet TDA LettersSet a parsear 
		 */
        inline LettersBag( const LettersSet & letterSet )
        {
            for( auto i = letterSet.cbegin(); i != letterSet.cend(); ++i)
                for( int j = 0; j < (*i).second.repetitions; j++ )
                    this->letters.add( (*i).first );
        }

        /**
         * @brief Introduce una letra en la bolsa
         * 
         * @param l Letra a añadir a la LettersBag
         */
        inline void insertLetter( const char & l )
        {
            this->letters.add( l );
        }

        /**
         * @brief Vacía la LettersBag
         * Elimina todo el contenido de la LettersBag
         * 
         */
        inline void clear(  )
        {
            this->letters.clear();
        }

        /**
         * @brief Tamaño de la bolsa
         * 
         * @return int con el tamaño de la bolsa
         */
        inline unsigned int size(  )
        {
            return this->letters.size();
        }

        /**
         * @brief Sobrecarga del operador de asignación
         * 
         * @return Referencia a this, de esta forma el operador puede ser encadenado 
         */
        inline LettersBag & operator =( const LettersBag & other )
        {
            this->letters = other.letters;

            return *this;
        }
		
        /**
         * @brief Extrae una letra aleatoria de la bolsa eliminándola del conjunto.
         * 
         * @return char con la letra extraída
         */
        char extractLetter(  );
		
        /**
         * @brief Extrae un conjunto de letras de la LettersBag, eliminándolas del conjunto
         * 
         * @param num Número de letras a extraer
         * @return contenedor de tipo <vector> con las letras extraídas aleatoriamente
         */
        vector<char> extractLetters( int num );

};
#endif
