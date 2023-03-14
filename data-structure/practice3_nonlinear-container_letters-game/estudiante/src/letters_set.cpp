#include <string>
#include <cctype>

#include "letters_set.h"

int LettersSet :: getScore ( string word ){

    int puntuacion = 0;

    for(int i = 0; i < word.length(); i++){
        LetterInfo li = letters[ toupper( word[i] ) ];

        if( li.repetitions > 0){
            puntuacion += li.score;
            li.repetitions--;
        }
    }

    return puntuacion;
}


LettersSet & LettersSet :: operator = ( const LettersSet & cl ){

    if( this != &cl)
        this->letters = cl.letters;

    return *this;
}

LetterInfo & LettersSet :: operator [] (const char & val){
    return this->letters[val];
}


ostream & operator << (ostream & os, const LettersSet & cl){

    map<char, LetterInfo> :: const_iterator i;

    for( i = cl.letters.begin(); i != cl.letters.end(); ++i )
        os << i->first << " " << i->second.repetitions << " " << i->second.score << endl;

    return os;
}

istream & operator >> (istream & is, LettersSet & cl){
    
    // obtener la primera linea que no tiene información
    string aux;

    getline( is, aux );

    // guardar el resto de palabras
    while( !is.eof() ) {
        pair<char, LetterInfo> valor;

        is >> valor.first;
        is >> valor.second.repetitions;
        is >> valor.second.score;

        cl.insert( valor );
    }

    return is;
}