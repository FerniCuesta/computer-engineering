/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author Antonio
 */
public class SorpresaPorCasaHotel extends Sorpresa {

    public SorpresaPorCasaHotel(String t, int v) {
        super(t, v);
    }
    
    protected void aplicarAJugador (int actual, ArrayList<Jugador> todos){
        super.aplicarAJugador(actual, todos);
        todos.get(actual).modificarSaldo(valor*todos.get(actual).cantidadCasasHoteles());
    }
    
}
