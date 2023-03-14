package civitas;

import java.util.ArrayList;
/**
 *
 * @author Antonio
 */
public class Tablero {
    private final ArrayList<Casilla> casillas;
    private boolean porSalida;
    
    public Tablero () {
        casillas = new ArrayList();
        
        // Añadimos una nueva casilla de nombre "Salida"
        casillas.add(new Casilla ("Salida"));
        
        // Inicializamos "porSalida" a false
        porSalida = false;
    }
    
    // devuelve true si su parámetro es un índice válido para acceder
    // a elementos de casillas.
    public boolean correcto (int numCasilla) {
        return (numCasilla < casillas.size());
    }
    
    // devuelve el atributo porSalida y lo deja en false.
    boolean computarPasoPorSalida () {
        if (porSalida) {
            porSalida = false;
            return true;
        }
        else {
            return false;
        }
    }
    
    // Añade a casillas la casilla pasada como parámetro.
    void añadeCasilla (Casilla casilla) {
        casillas.add(casilla);
    }
    
    // devuelve la casilla de la posición numCasilla si este índice es
    // válido. Devuelve null en otro caso. Utiliza internamente el método 
    // boolean correcto (int numCasilla).
    public Casilla getCasilla (int numCasilla) {
        return casillas.get(numCasilla);
    }
    
    // se calcula la nueva posición en el tablero asumiendo que
    // se parte de la posición actual y se avanza una tirada de unidades. 
    // Esta nueva posición se devuelve.
    int nuevaPosicion (int actual, int tirada) {
        if (actual+tirada != (actual+tirada)%casillas.size())
            porSalida = true;
        
        return (actual+tirada)%casillas.size();
    }

    public int getNumElementos () {
        return casillas.size();
    }
}
