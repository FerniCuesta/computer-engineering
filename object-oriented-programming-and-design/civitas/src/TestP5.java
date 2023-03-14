
import GUI.CapturaNombres;
import GUI.CivitasView;
import GUI.Dado;
import civitas.CivitasJuego;
import controladorCivitas.Controlador;
import java.util.ArrayList;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */

/**
 *
 * @author Raul
 */
public class TestP5 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        CivitasView vista = new CivitasView();
        Dado.createInstance(vista);
        CapturaNombres captura_nombres = new CapturaNombres (vista, true);
        ArrayList<String> nombres = captura_nombres.getNombres();
        CivitasJuego juego  = new CivitasJuego (nombres, false);
        Controlador controlador = new Controlador(juego, vista);
        
        vista.setCivitasJuego(juego);
        controlador.juega();
        
    }
    
}
