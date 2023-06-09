/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JPanel.java to edit this template
 */
package GUI;

import civitas.Casilla;
import civitas.CasillaCalle;

/**
 *
 * @author Fernando
 */
public class CasillaActualPanel extends javax.swing.JPanel {

    private Casilla casilla;
    
    public void setCasilla (Casilla c){
        
        casilla = c;
        
        text_nombre.setText(casilla.getNombre());
        
        if (casilla instanceof CasillaCalle){
            label_n_casas.setVisible(true);
            text_n_casas.setVisible(true);
            text_n_casas.setText(Integer.toString(((CasillaCalle)casilla).getNumCasas()));
            
            label_n_hoteles.setVisible(true);
            text_n_hoteles.setVisible(true);
            text_n_hoteles.setText(Integer.toString(((CasillaCalle)casilla).getNumHoteles()));
            
            label_precio_compra.setVisible(true);
            text_precio_compra.setVisible(true);
            text_precio_compra.setText(Float.toString(((CasillaCalle)casilla).getPrecioCompra()));
            
            label_precio_alquiler.setVisible(true);
            text_precio_alquiler.setVisible(true);
            text_precio_alquiler.setText(Float.toString(((CasillaCalle)casilla).getPrecioAlquilerCompleto()));
            
            label_precio_edificar.setVisible(true);
            text_precio_edificar.setVisible(true);
            text_precio_edificar.setText(Float.toString(((CasillaCalle)casilla).getPrecioEdificar()));            
        }else{
            
            label_n_casas.setVisible(false);
            text_n_casas.setVisible(false);
            
            label_n_hoteles.setVisible(false);
            text_n_hoteles.setVisible(false);
            
            label_precio_compra.setVisible(false);
            text_precio_compra.setVisible(false);
            
            label_precio_alquiler.setVisible(false);
            text_precio_alquiler.setVisible(false);
            
            label_precio_edificar.setVisible(false);
            text_precio_edificar.setVisible(false);
            
        }
        
        repaint();
        revalidate();
    }
    
    /**
     * Creates new form CasillaActualPanel
     */
    public CasillaActualPanel() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        label_nombre = new javax.swing.JLabel();
        text_nombre = new javax.swing.JTextField();
        label_n_casas = new javax.swing.JLabel();
        text_n_casas = new javax.swing.JTextField();
        label_n_hoteles = new javax.swing.JLabel();
        text_n_hoteles = new javax.swing.JTextField();
        label_precio_compra = new javax.swing.JLabel();
        text_precio_compra = new javax.swing.JTextField();
        label_precio_alquiler = new javax.swing.JLabel();
        text_precio_alquiler = new javax.swing.JTextField();
        label_precio_edificar = new javax.swing.JLabel();
        text_precio_edificar = new javax.swing.JTextField();

        label_nombre.setText("Nombre:");
        add(label_nombre);

        text_nombre.setEditable(false);
        text_nombre.setText("nombre");
        add(text_nombre);

        label_n_casas.setText("Casas:");
        add(label_n_casas);

        text_n_casas.setEditable(false);
        text_n_casas.setText("casas");
        add(text_n_casas);

        label_n_hoteles.setText("Hoteles:");
        add(label_n_hoteles);

        text_n_hoteles.setEditable(false);
        text_n_hoteles.setText("hoteles");
        add(text_n_hoteles);

        label_precio_compra.setText("PrecioCompra:");
        add(label_precio_compra);

        text_precio_compra.setEditable(false);
        text_precio_compra.setText("preciocompra");
        add(text_precio_compra);

        label_precio_alquiler.setText("PrecioAlquiler:");
        add(label_precio_alquiler);

        text_precio_alquiler.setEditable(false);
        text_precio_alquiler.setText("precioalquiler");
        add(text_precio_alquiler);

        label_precio_edificar.setText("PrecioEdificar:");
        add(label_precio_edificar);

        text_precio_edificar.setEditable(false);
        text_precio_edificar.setText("precioedificar");
        add(text_precio_edificar);
    }// </editor-fold>//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel label_n_casas;
    private javax.swing.JLabel label_n_hoteles;
    private javax.swing.JLabel label_nombre;
    private javax.swing.JLabel label_precio_alquiler;
    private javax.swing.JLabel label_precio_compra;
    private javax.swing.JLabel label_precio_edificar;
    private javax.swing.JTextField text_n_casas;
    private javax.swing.JTextField text_n_hoteles;
    private javax.swing.JTextField text_nombre;
    private javax.swing.JTextField text_precio_alquiler;
    private javax.swing.JTextField text_precio_compra;
    private javax.swing.JTextField text_precio_edificar;
    // End of variables declaration//GEN-END:variables
}
