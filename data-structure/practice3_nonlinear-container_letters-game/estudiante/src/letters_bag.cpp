#include "letters_bag.h"
#include "bag.h"

char LettersBag :: extractLetter(  ){
    char caracter; 

    // extraer y eliminar caracter aleatorio con la función get
    caracter = this->letters.get();

    // devolver el caracter
    return caracter;
}

vector<char> LettersBag :: extractLetters( int num ){
    vector <char> resultado;

    for( int i = 0; i < num; i++ )
        resultado.insert( resultado.cend(), this->letters.get() ); // insertar por el final una letra aleatoria

    return resultado;
}
