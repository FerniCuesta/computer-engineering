package civitas;

import java.util.ArrayList;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author usuario
 */
public class Casilla {
    
    private String nombre;
    
    public Casilla (String n) {
        nombre = n;
    }
    
    //Visibilidad cambiada de paquete a public para poder usarlo en PropiedadesPanel
    public String getNombre() {
        return nombre;
    }
        
    
    void informe (int actual, ArrayList<Jugador> todos) {
        boolean encontrado = false;
        for (int i=0; i<todos.size() && !encontrado; i++) {
            if (todos.get(i).getCasillaActual() == actual) {
                Diario.getInstance().ocurreEvento(todos.get(i).toString() + 
                        " ha caído en la casilla " + String.valueOf(actual));
                encontrado = true;
            }
        }
    }
    
    public String toString () {
        String str;

        str = nombre;
        
        return str;
    }

    
    void recibeJugador (int actual, ArrayList<Jugador> todos) {
        informe(actual, todos);
    }
    
}

