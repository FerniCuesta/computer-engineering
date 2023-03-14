/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

/**
 *
 * @author usuario
 */
public class JugadorEspeculador extends Jugador {
    
    static private final int FactorEspeculador = 2;
    protected static final int HotelesMax = Jugador.getHotelesMax() * FactorEspeculador;
    protected static final int CasasMax = Jugador.getCasasMax() * FactorEspeculador;

    
    protected JugadorEspeculador(Jugador j) {
        super(j);
        actualizaPropiedadesPorConversion();
    }

    public void actualizaPropiedadesPorConversion() {
        for (int i=0; i<getPropiedades().size(); i++) {
            getPropiedades().get(i).actualizaPropietarioPorConversion(this);
        }
    }
    
    @Override
    boolean paga (float cantidad){
        return super.paga(cantidad/2);
    }
    
    @Override
    protected boolean puedoGastar (float precio){
        return super.puedoGastar(precio/2);
    }
        
    @Override
    public String toString(){
        
        String cadena;
        cadena = super.toString();
        
        cadena += "\n(Jugador especulador).\n";
        
        return cadena;
        
    }
    
    static public final int getCasasMax(){
        return CasasMax;
    }
    
    static public final int getHotelesMax(){
        return HotelesMax;
    }
}
