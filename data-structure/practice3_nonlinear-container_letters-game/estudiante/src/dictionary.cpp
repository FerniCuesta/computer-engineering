#include <iostream>

#include "../include/dictionary.h"

int Dictionary :: getOccurrences( const char c  )
{
    int apariciones = 0;

    for( auto it = this->words.cbegin(); it != this->words.cend(); ++it )   // recorrer todo el diccionario
        for( int i = 0; i < (*it).length(); i++ )                           // recorrer cada palabra
            if( toupper((*it)[i]) == toupper( c ) )                                    
                apariciones++;                                

    return apariciones;
}

int Dictionary :: getTotalLetters(  )
{
    int total_letras = 0;

    for( auto it = this->words.cbegin(); it != this->words.cend(); ++it )
        total_letras += (*it).size();

    return total_letras;
}

vector<string> Dictionary :: wordsOfLength( int length )
{
    // vector donde almacenar las palabras seleccionadas
    vector<string> resultado;

    for( auto it = this->words.cbegin(); it != this->words.cend(); ++it ) // recorrer todo el diccionario
        if( (*it).length() == length )                                    // comprobar si cada palabra tiene la longitud buscada
            resultado.push_back(*it);

    return resultado;
}

ostream & operator << ( ostream & os, const Dictionary & dic )
{

    for(auto it = dic.words.cbegin(); it != dic.words.cend(); ++it)
        os << (*it);

    return os;
}

istream & operator >> ( istream & is, Dictionary & dic )
{

    string aux;

    getline( is, aux );

    
    while( !is.eof() ) {

        vector<string> vec;
        is >> vec[0];    
        dic.insert( vec[0] );
    
    }

    return is;
}