/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author Fernando
 */
public class SorpresaConvertirme extends Sorpresa {
    
    public SorpresaConvertirme(String t) {
        super(t, 0);
    }
    
    protected void aplicarAJugador(int actual, ArrayList <Jugador> todos) {
        todos.set(actual, todos.get(actual).convertir());
        super.aplicarAJugador(actual, todos);
    }
}
