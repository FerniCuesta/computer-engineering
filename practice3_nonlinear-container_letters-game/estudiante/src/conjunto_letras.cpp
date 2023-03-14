#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

#include "letters_set.h"

using namespace std;

int main(int argc, char *argv[])
{
    if( argc < 3){
        cout << "Error: se esperaba <conjunto_letras.txt> <palabra>" << endl;
        exit( EXIT_FAILURE );
    }

    // crear conjunto de letras
    LettersSet conjunto;

    // abrir fichero de entrada
    ifstream fi( argv[1] );

    // introducir el contenido del fichero en el LettersSet
    fi >> conjunto;
    
    // obtener la puntuación de la palabra
    cout << conjunto.getScore( argv[2] ) << endl;

    return 0;
}
