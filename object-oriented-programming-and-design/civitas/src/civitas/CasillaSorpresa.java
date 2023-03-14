/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author Raul
 */
public class CasillaSorpresa extends Casilla {
    
    private MazoSorpresas mazo;

    public CasillaSorpresa (String n, MazoSorpresas m) {       
        super(n);
        mazo = m;
    }
    
    //visibilidad de privada a paquete para poder hacer el override
    void recibeJugador (int actual, ArrayList<Jugador> todos) {
    
        Sorpresa sorpresa = mazo.siguiente();
        
        super.recibeJugador(actual, todos);
        
        sorpresa.aplicarAJugador(actual, todos);
        
    }
    
}
