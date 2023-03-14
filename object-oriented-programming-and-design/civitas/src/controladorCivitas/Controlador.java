package controladorCivitas;

import civitas.Casilla;
import civitas.CasillaCalle;
import vistaTextualCivitas.Vista;
import civitas.CivitasJuego;
import civitas.OperacionInmobiliaria;
import civitas.OperacionJuego;
import civitas.GestionInmobiliaria;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Raul
 */
public class Controlador {
    
    private CivitasJuego juego;
    private Vista vista;

    //He cambiado la visibilidad a public para poder usar el controlador en el main
    public Controlador(CivitasJuego modelo, Vista v) {
    
        juego = modelo;
        vista = v;
    
    }
    
    public void juega (){
        
        boolean fin = juego.finalDelJuego();
        
        while (!fin){
            
            vista.actualiza();
            
            vista.pausa();
            
            OperacionJuego operacion = juego.siguientePaso();
            
            System.err.println("\n");
            
            vista.mostrarSiguienteOperacion(operacion);
            
            if (operacion != OperacionJuego.PASAR_TURNO){
                vista.mostrarEventos();
            }
            
            fin = juego.finalDelJuego();
            
            if (!fin){
                
                Casilla casilla_actual = juego.getTablero().getCasilla(juego.getJugadorActual().getCasillaActual());
                
                if (operacion == OperacionJuego.COMPRAR){
                    
                    if (!((CasillaCalle)casilla_actual).tienePropietario())
                        if (vista.comprar() == Respuesta.SI){
                            juego.comprar();
                        }
                    
                    juego.siguientePasoCompletado(operacion);
                
                }else if (operacion == OperacionJuego.GESTIONAR) {
                    
                    OperacionInmobiliaria operacion_i = vista.elegirOperacion();
                    
                    if (operacion_i != OperacionInmobiliaria.TERMINAR){
                        
                        int ip_propiedad = vista.elegirPropiedad();
                        GestionInmobiliaria gestion = new GestionInmobiliaria(operacion_i, ip_propiedad);
                        
                        switch (gestion.getOperacion()) {
                            case TERMINAR:
                                juego.siguientePasoCompletado(operacion);
                                break;
                            case CONSTRUIR_CASA:
                                juego.construirCasa(ip_propiedad);
                                break;
                            case CONSTRUIR_HOTEL:
                                juego.construirHotel(ip_propiedad);
                                break;
                        }
                        
                    }
                    
                    juego.siguientePasoCompletado(operacion);
                    
                }
                
            }
            
        }
        
        juego.ranking();
        
        vista.actualiza();
        
    }
    
}
