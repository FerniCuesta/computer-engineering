/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */

import civitas.CivitasJuego;
import java.util.ArrayList;
import vistaTextualCivitas.Vista;
import vistaTextualCivitas.VistaTextual;

/**
 *
 * @author usuario
 */
public class TestP4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        ArrayList<String> nombres = new ArrayList();
        
        nombres.add("Jugador1");
        nombres.add("Jugador2");
        
        CivitasJuego juego = new CivitasJuego(nombres, true);
        
        juego.avanzaJugador();
        juego.comprar();
        juego.construirCasa(0);

        
        juego.avanzaJugador();
        juego.comprar();
        juego.construirCasa(0);

        
        System.out.println(juego.getJugadorActual().toString());
        
        juego.pasarTurno();
        
        juego.avanzaJugador();
        juego.avanzaJugador();
        
        juego.avanzaJugador();
        juego.comprar();
        juego.construirCasa(0);
        juego.construirCasa(0);
        juego.construirCasa(0);
        
        
        System.out.println(juego.getJugadorActual().toString());
        
        juego.pasarTurno();
        
        juego.avanzaJugador();
        juego.avanzaJugador();
        
        System.out.println(juego.getJugadorActual().toString());
        
        juego.avanzaJugador();
        System.out.println(juego.getTablero().getCasilla(juego.getJugadorActual().getCasillaActual()).toString());
        
        juego.comprar();
        System.out.println(juego.getJugadorActual().toString());
    }
    
}
