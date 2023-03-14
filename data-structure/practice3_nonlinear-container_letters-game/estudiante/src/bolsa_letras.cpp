#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

#include "letters_bag.h"
#include "letters_set.h"

using namespace std;

int main(int argc, char *argv[])
{
    if( argc < 2){
        cout << "Error: se esperaba <conjunto_letras.txt>" << endl;
        exit( EXIT_FAILURE );
    }

    // crear conjunto de letras
    LettersSet conjunto;

    // abrir fichero de entrada
    ifstream fi( argv[1] );

    // introducir el contenido del fichero en el LettersSet
    fi >> conjunto;

    // crear bolsa de letras
    LettersBag bolsa( conjunto );

    // extraer y mostrar letras aleatoriamente
    while( bolsa.size() )
        cout << bolsa.extractLetter() << endl;

    return 0;
}
