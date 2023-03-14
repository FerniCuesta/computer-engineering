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
        cout << "Error: se esperaba <diccionario.txt> <letras.txt>" << endl;
        exit( EXIT_FAILURE );
    }

    //*****************************************************************************
    // crear Diccionario
    Dictionary diccionario;

    // abrir fichero de entrada
    ifstream fi( argv[1] );

    // string para almacenar las palabras
    string palabra;

    // introducir palabras en el diccionario
    while( !fi.eof() )
    {
        fi >> palabra;
        diccionario.insert( palabra );
    }

    //*****************************************************************************
    // crear vector de letras
    vector<char> letras;

    fi.close();
    fi.open( argv[2] );

    // quitar la primera linea que no contiene informacion
    getline( fi, palabra );

    // char para almacenar los caracteres
    char caracter;

    while( !fi.eof() )
    {
        fi >> caracter;
        letras.insert( letras.cend(), caracter );

        getline( fi, palabra );
    }

    //*****************************************************************************
    // imprimir información
    cout << "Letra\tFAbs.\tFrel." << endl;

    int apariciones = 0;
    
    // obtener las ocurrencias de cada letra
    for( int i = 0; i < letras.size() - 1; i++ ){
        apariciones = diccionario.getOccurrences( letras[i] );
        cout << letras[i] << "\t" << apariciones << "\t" << (double) apariciones / diccionario.getTotalLetters() << endl;
    }
   
    // cerrar flujo de entrada
    fi.close();

    return 0;
}
