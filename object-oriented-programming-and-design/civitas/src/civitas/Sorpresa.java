/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author usuario
 */
abstract public class Sorpresa {
    
    private String texto;
    // Visibilidad cambiada de privada a paquete
    int valor;
    private MazoSorpresas mazo;
    
    Sorpresa (String t, int v){
        texto = t;
        valor = v;
        mazo = null;
    }
    
    private void informe(int actual, ArrayList <Jugador> todos){
        
        Diario.getInstance().ocurreEvento(texto);
        
    }
    
    public String toString (){
        return texto;
    }
    
    void aplicarAJugador(int actual, ArrayList<Jugador> todos) {
        informe(actual, todos);
    }
    
}