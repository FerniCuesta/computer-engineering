/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import java.util.ArrayList;
import java.util.Collections;
/**
 *
 * @author Raul
 */
public class MazoSorpresas {
    private ArrayList<Sorpresa> sorpresas;
    private boolean barajada;
    private int usadas;
    private boolean debug;
    
    // Este método inicializa los atributos sorpresas a un contenedor vacío, 
    // barajada a false y usadas a 0. Este método será lo primero que se 
    // invoque desde los constructores, de manera que un constructor primero 
    // inicializa los atributos a su valor por defecto (el que se establece en 
    // el método init para después modificar los atributos que sean necesarios 
    // según lo que le corresponda a cada constructor.
    private void init () {
        sorpresas = new ArrayList();
        barajada = false;
        usadas = 0;
    }
    
    // El constructor de esta clase recibe como parámetro el valor para
    // el atributo debug e inicializa este atributo. Además llama al método 
    // init, y si el modo debug está activado, se informa de este hecho a 
    // través del diario.
    MazoSorpresas (boolean d) {
        debug = d;
        init();
        if (debug)
            Diario.getInstance().ocurreEvento("Modo Debug Activado, creando mazo sorpresa sin barajar");
    }
    
    // Este constructor simplemente llama al método init y fija el valor
    // de debug a false.
    MazoSorpresas () {
        init();
        debug = false;
    }
    
    // si el mazo no ha sido barajado se añade la sorpresa que recibe como 
    // argumento al mazo. En caso contrario no se hace nada ya que no se 
    // permite añadir cartas a un mazo que ya está en uso.
    void alMazo (Sorpresa s) {
        if (barajada == false){
            sorpresas.add(s);
        }
    }
    
    // si el mazo no ha sido barajado o si el número de cartas usadas es igual al
    // tamaño del mazo, se baraja el mazo (salvo que el modo debug esté activo), 
    // se fija el valor de usadas a cero y el de barajada a true.
    Sorpresa siguiente () {
        
        if (barajada == false || usadas == sorpresas.size()){
            
            if (debug == false){
                Collections.shuffle(sorpresas);
            }
            
            usadas = 0;
            barajada = true;
            
        }
        
        usadas++;
        
        Sorpresa sorpresa_temp = sorpresas.get(0);
        
        for (int i = 0; i < sorpresas.size()-1; i++){
            sorpresas.set(i, sorpresas.get(i+1));
        }
        
        sorpresas.set(sorpresas.size()-1, sorpresa_temp);
        
        return sorpresa_temp;
    }
}
