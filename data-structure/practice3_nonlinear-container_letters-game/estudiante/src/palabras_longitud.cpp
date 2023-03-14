#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

#include "../include/dictionary.h"
#include "../include/letters_set.h"

using namespace std;

int main(int argc, char *argv[])
{
    if( argc < 3){
        cout << "Error: se esperaba <diccionario.txt> <longitud>" << endl;
        exit( EXIT_FAILURE );
    }

    // crear Diccionario
    Dictionary diccionario;

    // abrir fichero de entrada
    ifstream fi( argv[1] );

    // string para almacenar las palabras
    string aux;

    // introducir palabras en el diccionario
    while( !fi.eof() )
    {
        fi >> aux;
        diccionario.insert( aux );
    }
    
    // obtener la longitud de palabras buscada
    int longitud = atoi( argv[2] );

    // almacenar las palabras de la longitud dada
    vector<string> palabras;

    for( auto it = diccionario.cbegin(); it != diccionario.cend(); ++it)    // recorrer todo el diccionario
        if( (*it).length() == longitud )
            palabras.insert( palabras.end(), (*it) );

    // imprimir información por pantalla
    cout << "Palabras de longitud " << longitud << endl;

    // imprimir palabras por pantalla
    for( int i = 0; i < palabras.size(); ++i )
        cout << palabras[i] << endl;

    // cerrar flujo de entrada
    fi.close();
    
    return 0;
}