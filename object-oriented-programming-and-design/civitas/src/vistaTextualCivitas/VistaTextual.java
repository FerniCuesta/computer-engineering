package vistaTextualCivitas;

import civitas.Casilla;
import civitas.CasillaCalle;
import civitas.CivitasJuego;
import civitas.Diario;
import civitas.OperacionJuego;
import controladorCivitas.Respuesta;
import civitas.OperacionInmobiliaria;
import civitas.Jugador;
import civitas.Tablero;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import vistaTextualCivitas.Vista;



public class VistaTextual implements Vista {
  
    
    private static String separador = "=====================";

    private Scanner in;

    CivitasJuego juegoModel;

    public VistaTextual (CivitasJuego juegoModel) {
        in = new Scanner (System.in);
        this.juegoModel=juegoModel;
    }



    public void pausa() {
        System.out.print ("\nPulsa una tecla");
        in.nextLine();
    }

    int leeEntero (int max, String msg1, String msg2) {
        Boolean ok;
        String cadena;
        int numero = -1;
        do {
            System.out.print (msg1);
            cadena = in.nextLine();
            try {  
                numero = Integer.parseInt(cadena);
                ok = true;
            } catch (NumberFormatException e) { // No se ha introducido un entero
                System.out.println (msg2);
                ok = false;  
            }
            if (ok && (numero < 0 || numero >= max)) {
                System.out.println (msg2);
                ok = false;
            }
        } while (!ok);

        return numero;
    }

    int menu (String titulo, ArrayList<String> lista) {
        String tab = "  ";
        int opcion;
        System.out.println (titulo);
        for (int i = 0; i < lista.size(); i++) {
            System.out.println (tab+i+"-"+lista.get(i));
        }

        opcion = leeEntero(lista.size(),
                              "\n"+tab+"Elige una opción: ",
                              tab+"Valor erróneo");
        return opcion;
    }

    public Respuesta comprar(){

        String respuesta_s;
        Respuesta respuesta;

        System.out.println("¿Desea comprar la calle? [SI/NO]: \n");

        do {
        respuesta_s = in.nextLine();
        } while (!respuesta_s.equals(String.valueOf("SI")) && !respuesta_s.equals("NO"));

        if (respuesta_s.equals(String.valueOf("SI"))){
            respuesta = Respuesta.SI;
        }
        else {
            respuesta = Respuesta.NO;
        }


        return respuesta;

    }

    public void actualiza(){
        
        if (!juegoModel.finalDelJuego()){

            System.out.println("\n" + juegoModel.getJugadorActual().toString());

            Casilla casilla_actual = juegoModel.getTablero().getCasilla(juegoModel.getJugadorActual().getCasillaActual());

            System.out.println("\nInformación de la casilla actual: " + casilla_actual.toString());
            
        }else{

            System.out.println("\n\nFIN DEL JUEGO: \n\n");

            for (int i=0; i < juegoModel.getJugadores().size(); i++){
                
                System.out.println("Puesto número " + String.valueOf(i+1) + ": \n" + juegoModel.getJugadores().get(i).toString());
                
            }
            
        }

    }

    public OperacionInmobiliaria elegirOperacion(){

        ArrayList<String> posibles_elecciones = new ArrayList();

        posibles_elecciones.add ("CONSTRUIR_CASA");
        posibles_elecciones.add ("CONSTRUIR_HOTEL");
        posibles_elecciones.add ("TERMINAR");

        int eleccion = menu("Elige una operación inmoviliaria", posibles_elecciones);

        switch (eleccion) {
            case 0:
                return OperacionInmobiliaria.CONSTRUIR_CASA;
            case 1:
                return OperacionInmobiliaria.CONSTRUIR_HOTEL;
            default:
                return OperacionInmobiliaria.TERMINAR;
        }

    }

    public int elegirPropiedad(){
           
        ArrayList<String> propiedades = new ArrayList();
        for (int i=0; i < juegoModel.getTablero().getNumElementos(); i++){
            if (juegoModel.getTablero().getCasilla(i) instanceof CasillaCalle)
                if (((CasillaCalle)juegoModel.getTablero().getCasilla(i)).esEsteElPropietario(juegoModel.getJugadorActual())){
                    propiedades.add("Casilla " + i);
                }
        }
        
        int opcion;
        do {
            opcion = menu("Elige la propiedad donde quieres hacer una gestión\n", 
                propiedades);
        } while (opcion < 0 && opcion >= propiedades.size());
        
        return opcion;
    }
    
    public void mostrarSiguienteOperacion(OperacionJuego operacion) {
        
        System.out.println(operacion.toString());
        
    }
    
    public void mostrarEventos() {
        while (Diario.getInstance().getEventos().size() > 0)
            System.out.println(Diario.getInstance().leerEvento());
    }
    
}
