/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

/**
 *
 * @author Fernando
 */
public class GestionInmobiliaria {
    
    private int propiedad;
    private OperacionInmobiliaria operacion;
    
    public GestionInmobiliaria (OperacionInmobiliaria gest, int ip){
        propiedad = ip;
        operacion = gest;
    }
    
    public  OperacionInmobiliaria getOperacion(){
        return operacion;
    }
    
    public int getPropiedad(){
        return propiedad;
    }
    
}
