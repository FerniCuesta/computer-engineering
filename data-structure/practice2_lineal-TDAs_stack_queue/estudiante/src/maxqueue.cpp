/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author
 */

#include<iostream>
#include "maxqueue.h"

element MaxQueue :: front( )
{
    return cola_max.top();
}

void MaxQueue :: pop( )
{
    cola_max.pop();
}

bool MaxQueue :: empty( )
{
    return cola_max.empty();
}

int MaxQueue :: size( )
{
    return cola_max.size();
}

void MaxQueue :: push( int numero )
{
    // crear nuevo elemento y asignarle el valor
    element nuevo_elemento;
    nuevo_elemento.value = numero;
    nuevo_elemento.maximun = numero;

    // crear cola auxiliar
    stack <element> cola_aux;

    // insertar los valores de la cola original en la auxiliar
    // resultado de la cola aux: valores invertidos
    while ( !this->empty() )
    {
        // si el nuevo valor es maximo, actualizamos los maximos de la cola
        if ( numero > this->cola_max.top().maximun )
            this->cola_max.top().maximun = numero;

        cola_aux.push ( this->cola_max.top() );
        this->cola_max.pop();
    }

    // insertar valor nuevo en la cola original (queda en el back)
    this->cola_max.push ( nuevo_elemento );

    // insertar los valores de la cola auxiliar de nuevo en la original
    // resultado de la cola original: nuevo valor en el back y todos los valores
    // anteriores ordenados
    while ( !cola_aux.empty() )
    {
        this->cola_max.push( cola_aux.top() );
        cola_aux.pop();
    }
}

ostream & operator << ( ostream & out, const element & e )
{
    out << e.value << "," << e.maximun;

    return (out);
}