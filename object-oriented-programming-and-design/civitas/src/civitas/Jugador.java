/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import static java.lang.Double.compare;
import java.util.ArrayList;

/**
 *
 * @author Antonio
 */
public class Jugador implements Comparable<Jugador> {
    
    protected static final int CasasMax = 4;
    protected static final int CasasPorHotel = 4;
    private int casillaActual;
    protected static final int HotelesMax = 4;
    private String nombre;
    protected static final float PasoPorSalida = 1000;
    private boolean puedeComprar;
    private float saldo;
    private static final float SaldoInicial = 7500;
    private ArrayList<CasillaCalle> propiedades;
    
    protected Jugador (String n){
        
        nombre = n;
        saldo = SaldoInicial;
        casillaActual = 0;
        propiedades = new ArrayList();

    }
    
    protected Jugador (Jugador j) {
        casillaActual = j.casillaActual;
        nombre = j.nombre;
        saldo = j.saldo;
        propiedades = j.propiedades;
    }
        
    //Visibilidad cambiada de protected a public para usarlo en la GUI
    public String getNombre(){
        return nombre;
    }
    
    static final int getCasasPorHotel(){
        return CasasPorHotel;
    }
    
    
    //He cambiado la visivilidad de paquete a publica para poder saber en que
    //casilla se encuentra para realizar el actualiza de la vista
    public int getCasillaActual(){
        return casillaActual;
    }
    
    // Visibilidad cambiada de protected a public para usarlo en la vista
    public ArrayList<CasillaCalle> getPropiedades(){
        return propiedades;
    }
    
    public int getNumPropiedades(){
        return propiedades.size();
    }
    
    static public int getCasasMax(){
        return CasasMax;
    }
    
    static public int getHotelesMax(){
        return HotelesMax;
    }
    
    //Visibilidad cambiada de protected a public para usarlo en la GUI
    public float getSaldo () {
        return saldo;
    }
    
    static final float getPremioPasoSalida(){
        return PasoPorSalida;
    }

    private boolean existeLaPropiedad (int ip){
        
        boolean existe = false;
        
        if (ip < propiedades.size() && ip >= 0)
            if (propiedades.get(ip).esEsteElPropietario(this))
                existe = true;
        
        return  existe;
        
    }
    
    boolean puedeComprarCasilla (){
        puedeComprar = true;
        return puedeComprar;
    }
    
    boolean getPuedeComprar (){
        return puedeComprar;
    }

    boolean modificarSaldo (float cantidad){
        saldo += cantidad;
        Diario.getInstance().ocurreEvento("Modificando saldo: " + String.valueOf(saldo) + " a " + nombre);
        return true;
    }
    
    boolean paga (float cantidad){
        return modificarSaldo(-1 * cantidad);
    }
    
    boolean pagaAlquiler (float cantidad){
        return paga(cantidad);
    }
    
    boolean recibe (float cantidad){
        return modificarSaldo(cantidad);
    }
    
    boolean moverACasilla (int c){
        casillaActual = c;
        puedeComprar = false;
        Diario.getInstance().ocurreEvento("Moviendo Jugador " + nombre + " a casilla " + String.valueOf(c));
        return true;
    }
    
    // Visibilidad cambiada de private a protected para poder hacer override
    // en la clase JugadorEspeculador
    protected boolean puedoGastar (float precio){
        return saldo >= precio;
    }
    
    boolean tieneAlgoQueGestionar (){
        return (!propiedades.isEmpty());
    }
    
    boolean pasaPorSalida(){
        this.recibe(PasoPorSalida);
        Diario.getInstance().ocurreEvento(nombre + " ha pasado por la salida y ha recibido " + String.valueOf(PasoPorSalida));
        return true;
    }
    
    public int compareTo (Jugador otro) {
        return compare (saldo, otro.getSaldo());
    }
    
    private boolean puedoEdificarCasa (CasillaCalle propiedad){

        if (puedoGastar(propiedad.getPrecioEdificar())){
            if (CasasMax > propiedad.getNumCasas()){
                if (HotelesMax > propiedad.getNumHoteles()){
                    return true;
                }
            }
        }
        
        return false;
    
    }
    
    private boolean puedoEdificarHotel (CasillaCalle propiedad){

        if (puedoGastar(propiedad.getPrecioEdificar())){
            if (HotelesMax > propiedad.getNumHoteles()){
                if (propiedad.getNumCasas()>=getCasasPorHotel()){
                    return true;
                }
            }
        }
        
        return false;
    }
    
    
    public boolean comprar (CasillaCalle titulo) {
        
        boolean result = false;
        float precio = 0;
        
        if (getPuedeComprar())
        
        {
            precio = titulo.getPrecioCompra();
        
            if (puedoGastar(precio)){

                result = titulo.comprar(this);

                propiedades.add(titulo);

                Diario.getInstance().ocurreEvento("El jugador" + nombre + " compra la propiedad " + titulo);

                puedeComprar = false;

            }else{

                Diario.getInstance().ocurreEvento("El jugador " + this + " no tiene saldo para comprar la propiedad" + titulo);

            }
        }
            
        return result;
    }
    
    
    public boolean construirHotel (int i) {
    
        boolean result = false;
        
        if (existeLaPropiedad(i)){
            
            CasillaCalle propiedad = propiedades.get(i);
            
            boolean puedoEdificarHotel = puedoEdificarHotel(propiedad);

            if (puedoEdificarHotel){
                
                result = propiedad.construirHotel(this);
                
                propiedad.derruirCasas (CasasPorHotel, this);
                
                Diario.getInstance().ocurreEvento("El jugador " + nombre + " construye hotel en la propiedad" + i);
                
            }
            
        }
        
        return result;
        
    }
    
    public boolean construirCasa (int i) {
    
        boolean result = false;
        
        if (existeLaPropiedad(i)){
            
            CasillaCalle propiedad = propiedades.get(i);
            
            boolean puedoEdificarCasa = puedoEdificarCasa(propiedad);

            if (puedoEdificarCasa){
                
                result = propiedad.construirCasa(this);
                
                Diario.getInstance().ocurreEvento("El jugador " + nombre + " construye casa en la propiedad" + i);
                
            }
            
        }
        
        return result;
        
    }
    
    int cantidadCasasHoteles() {
        int cont = 0;
        for (int i=0; i<propiedades.size(); i++) {
            cont += propiedades.get(i).cantidadCasasHoteles();
        }
        
        return cont;
    }
    
    public String toString(){
        
        String cadena;
        
        cadena = "Jugador: " + nombre;
        cadena += "\nSaldo actual: " + saldo;
        cadena += "\nPropiedades: \n";
        
        for (int i=0; i < propiedades.size(); i++){
            cadena += propiedades.get(i).toString() + "\n";
        }
        
        return cadena;
        
    }
    
    public Jugador convertir() {
        Jugador j = new JugadorEspeculador(this);
        
        return j;
    }
    
}
