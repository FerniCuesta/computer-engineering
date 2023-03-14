/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JPanel.java to edit this template
 */
package GUI;

import civitas.CasillaCalle;
import civitas.Jugador;
import civitas.JugadorEspeculador;
import java.util.ArrayList;

/**
 *
 * @author Antonio
 */
public class JugadorPanel extends javax.swing.JPanel {

    /**
     * Creates new form JugadorPanel
     */
    
    private Jugador jugador;
    
    public void setJugador (Jugador j){
        jugador = j;
        text_nombre.setText(jugador.getNombre());
        text_saldo.setText(Float.toString(jugador.getSaldo()));
        text_especulador.setText(Boolean.toString(jugador instanceof JugadorEspeculador));
        rellenaPropiedades(jugador.getPropiedades());
        repaint();
        revalidate();
    }
    
    public JugadorPanel() {
        initComponents();
    }
    
    private void rellenaPropiedades (ArrayList<CasillaCalle> lista) {
        // Se elimina la información antigua
        propiedadesPanel.removeAll();
        // Se recorre la lista de propiedades para ir creando sus vistas individuales y añadirlas al panel
        
        for (CasillaCalle t : lista) {
            PropiedadPanel vistaPropiedad = new PropiedadPanel();
            vistaPropiedad.setPropiedad(t);
            propiedadesPanel.add(vistaPropiedad);
            vistaPropiedad.setVisible(true);
        }
        
        // Se fuerza la actualización visual del panel propiedades y del panel del jugador
        repaint();
        revalidate();
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
        label_saldo = new javax.swing.JLabel();
        text_saldo = new javax.swing.JTextField();
        label_especulador = new javax.swing.JLabel();
        text_especulador = new javax.swing.JTextField();
        propiedadesPanel = new javax.swing.JPanel();

        label_nombre.setText("Nombre:");
        label_nombre.setName("label_nombre"); // NOI18N
        add(label_nombre);
        label_nombre.getAccessibleContext().setAccessibleName("label_nombre");

        text_nombre.setEditable(false);
        text_nombre.setText("text_nombre");
        text_nombre.setName("text_nombre"); // NOI18N
        text_nombre.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                text_nombreActionPerformed(evt);
            }
        });
        add(text_nombre);
        text_nombre.getAccessibleContext().setAccessibleName("text_nombre");

        label_saldo.setText("Saldo:");
        label_saldo.setName("label_saldo"); // NOI18N
        add(label_saldo);
        label_saldo.getAccessibleContext().setAccessibleName("label_saldo");

        text_saldo.setEditable(false);
        text_saldo.setText("text_saldo");
        text_saldo.setName("text_saldo"); // NOI18N
        text_saldo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                text_saldoActionPerformed(evt);
            }
        });
        add(text_saldo);
        text_saldo.getAccessibleContext().setAccessibleName("text_saldo");

        label_especulador.setText("Especulador:");
        label_especulador.setName("label_especulador"); // NOI18N
        add(label_especulador);
        label_especulador.getAccessibleContext().setAccessibleName("label_especulador");

        text_especulador.setEditable(false);
        text_especulador.setText("text_especulador");
        text_especulador.setName("text_especulador"); // NOI18N
        add(text_especulador);
        text_especulador.getAccessibleContext().setAccessibleName("text_especulador");

        propiedadesPanel.setName("propiedadesPanel"); // NOI18N
        add(propiedadesPanel);
        propiedadesPanel.getAccessibleContext().setAccessibleName("propiedadesPanel");
    }// </editor-fold>//GEN-END:initComponents

    private void text_saldoActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_text_saldoActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_text_saldoActionPerformed

    private void text_nombreActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_text_nombreActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_text_nombreActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel label_especulador;
    private javax.swing.JLabel label_nombre;
    private javax.swing.JLabel label_saldo;
    private javax.swing.JPanel propiedadesPanel;
    private javax.swing.JTextField text_especulador;
    private javax.swing.JTextField text_nombre;
    private javax.swing.JTextField text_saldo;
    // End of variables declaration//GEN-END:variables
}