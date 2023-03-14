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
public class CasillaCalle extends Casilla {
    
    private float precioCompra;
    private float precioBaseAlquiler;
    private float precioEdificar;
    private int numCasas;
    private int numHoteles;
    private static final float FACTORALQUILERCALLE = 1.0f;
    private static final float FACTORALQUILERCASA = 1.0f;
    private static final float FACTORALQUILERHOTEL = 4.0f;
    private ArrayList<Jugador> propietario = new ArrayList (1);
    
    public CasillaCalle (String unNombre,
        float unPrecioCompra, float unPrecioEdificar, 
        float unPrecioAlquilerBase) {

        super(unNombre);
        precioCompra = unPrecioCompra;
        precioEdificar = unPrecioEdificar;
        precioBaseAlquiler = unPrecioAlquilerBase;
        numCasas = 0;
        numHoteles = 0;
        propietario = new ArrayList();
        
    }
    
    
    //Visibilidad cambiada de paquete a public para usarla en la GUI
    public float getPrecioCompra() {
        return precioCompra;
    }
    
    //Visibilidad cambiada de paquete a public para usarla en la GUI
    public float getPrecioEdificar() {
        return precioEdificar;
    }
    
    //Visibilidad cambiada de paquete a public para usarla en la GUI
    public float getPrecioAlquilerCompleto() {
        return precioBaseAlquiler*FACTORALQUILERCALLE*(1+numCasas*FACTORALQUILERCASA+numHoteles*FACTORALQUILERHOTEL);
    }
    
    //Cambiado de paquete a public para usarlo en PropiedadPanel
    public int getNumCasas() {
        return numCasas;
    }
    
    //Cambiado de paquete a public para usarlo en PropiedadPanel
    public int getNumHoteles() {
        return numHoteles;
    }
    
    
    boolean construirCasa(Jugador j) {
        j.paga(precioEdificar);
        numCasas += 1;
        return true;
    }
    
    boolean construirHotel(Jugador j) {
        j.paga(precioEdificar);
        numHoteles += 1;
        return true;
    }
    
    public boolean tienePropietario(){
        return !propietario.isEmpty();
    }
    
    public boolean esEsteElPropietario (Jugador j){
        
        for (int i=0; i < propietario.size(); i++){
            if (propietario.get(i).getNombre().equals(j.getNombre())){
                return true;
            }
        }
        
        return false;
        
    }
    
    
    public void tramitarAlquiler (Jugador jugador) {
        if (this.tienePropietario() && !esEsteElPropietario(jugador)) {
            jugador.pagaAlquiler(this.getPrecioAlquilerCompleto());
            for (int i=0; i<propietario.size(); i+=1) {
                propietario.get(i).recibe(this.getPrecioAlquilerCompleto()/propietario.size()); //PREGUNTAR SI ES ASÍ
            }
        }
        else {
            jugador.comprar(this);
        }
    }
    
    public int cantidadCasasHoteles () {
        return numCasas + numHoteles;
    }
    
    public boolean derruirCasas (int n, Jugador jugador) {
        boolean derruido;
        
        if (esEsteElPropietario(jugador) && numCasas >= n) {
            numCasas -= n;
            derruido = true;
        }
        else {
            derruido = false;
        }
        
        return derruido;
    }
    
    boolean comprar(Jugador jugador) {
        
        if (propietario.isEmpty()){
         
            propietario.add(jugador);

            jugador.paga(precioCompra);
        
        }
        
        return true;
        
    }
    
    public String toString () {
        String str;

        str = super.toString();
        
        str += ". Precios: Compra: " + String.valueOf(precioCompra);
        str += ", Edificar: " + String.valueOf(precioEdificar);
        str += ", Alquiler base: " + String.valueOf(precioBaseAlquiler);
        str += ", Casas: " + String.valueOf(numCasas);
        str += ", Hoteles: " + String.valueOf(numHoteles);
        
        return str;
    }
    
    //visibilidad de privada a paquete para poder hacer el override
    void recibeJugador (int actual, ArrayList<Jugador> todos) {
        
        super.recibeJugador(actual, todos);
        
        Jugador jugador = todos.get(actual);
        
        if (!tienePropietario()){
            
            jugador.puedeComprarCasilla();
            
        }else{
            
            tramitarAlquiler(jugador);
            
        }
        
    }
    
    public void actualizaPropietarioPorConversion(JugadorEspeculador je) {
        if (propietario.size() > 0) {
            propietario.set(0, je);
        }
    }

}
