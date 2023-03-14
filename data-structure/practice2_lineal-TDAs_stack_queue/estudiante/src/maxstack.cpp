/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author
 */


#include<iostream>
#include "maxstack.h"

using namespace std;


element MaxStack :: top( )
{
    return pila_max.front();
}

void MaxStack :: pop( )
{
    pila_max.pop();
}

bool MaxStack :: empty( )
{
    return pila_max.empty();
}

int MaxStack :: size( )
{
    return pila_max.size();
}

void MaxStack :: push( int numero )
{
    // crear nuevo elemento y asignarle el valor
    element nuevo_elemento;
    nuevo_elemento.value = numero;

    // asignar el maximo al nuevo elemento
    if( this->size() > 0 && this->top().maximun >= numero ) // si el nuevo valor no es un nuevo maximo
        nuevo_elemento.maximun = this->top().maximun;
    else                                                         // si el nuevo valor es un nuevo maximo
        nuevo_elemento.maximun = numero;

    // crear pila auxiliar
    queue <element> pila_aux;

    // insertar nuevo elemento en el top de la pila auxiliar (externo), es decir, front de la cola (interno)
    pila_aux.push( nuevo_elemento );

    // insertar el resto de valores a continuación
    while( !this->empty() )
    {
        pila_aux.push( this->top() ); // insertar top
        this->pop();                    // quitar top
    }

    // asignar la pila a la pila auxiliar con el nuevo elemento
    this->pila_max = pila_aux;
}

ostream & operator << (ostream & out, const element & e)
{
    out << e.value << "," << e.maximun;

    return (out);
}
