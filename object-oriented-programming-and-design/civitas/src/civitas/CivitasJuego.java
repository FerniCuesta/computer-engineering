/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package civitas;

import GUI.Dado;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

/**
 *
 * @author usuario
 */
public class CivitasJuego {
    private int indiceJugadorActual;
    private ArrayList<Jugador> jugadores = new ArrayList (4);
    private GestorEstados gestor;
    private EstadoJuego estado;
    private MazoSorpresas mazo;
    private Tablero tablero;
    
    public CivitasJuego (ArrayList<String> nombres, boolean debug) {
        
        // Inicializar el atributo jugadores creando y añadiendo un jugador 
        // por cada nombre suministrado como parámetro.
        for (int i=0; i<nombres.size(); i++)
            jugadores.add(new Jugador (nombres.get(i)));
        
        // Crear el gestor de estados y fijar el estado actual como el estado 
        // inicial (método estadoInicial()) indicado por este gestor.
        estado = EstadoJuego.INICIO_TURNO;
        
        // Poner el dado en modo debug/no debug según el argumento 
        // correspondiente del constructor.
        Dado.getInstance().setDebug(debug);
        
        // Inicializar el índice del jugador actual (que será quien tenga el 
        // primer turno). Para obtener ese valor se utilizará el método 
        // adecuado del dado.
        indiceJugadorActual = Dado.getInstance().quienEmpieza(jugadores.size());
        
        // Crear el mazo de sorpresas en el modo debug/no debug según el 
        // argumento correspondiente del constructor
        mazo = new MazoSorpresas (debug);
        inicializaMazoSorpresas();
        
        // Crear el tablero y llamar al método de CivitasJuego para inicializar 
        // el tablero.
        tablero = new Tablero();
        
        gestor = new GestorEstados();
        
        inicializaTablero(mazo);
        
    }
    
    // este método añade al tablero todas las casillas, las cuales se van 
    // creando conforme se añaden.
    private void inicializaTablero (MazoSorpresas mazo) {
        
        Random ran = new Random();
        
        int cont_calle = 1, cont_sorp = 1;
        for (int i=0; i<3; i++, cont_calle++)
        tablero.añadeCasilla(new CasillaCalle ("Casilla (calle) " + String.valueOf(cont_calle), 
                                                ran.nextInt(50)+2000,
                                                ran.nextInt(50)+500,
                                                ran.nextInt(50)+800));

        tablero.añadeCasilla(new CasillaSorpresa ("Casilla (sorpresa) " + String.valueOf(cont_sorp), mazo));
        cont_sorp++;

        for (int i=0; i<4; i++, cont_calle++)
        tablero.añadeCasilla(new CasillaCalle ("Casilla (calle) " + String.valueOf(cont_calle), 
                                                ran.nextInt(50)+2000,
                                                ran.nextInt(50)+500,
                                                ran.nextInt(50)+800));

        tablero.añadeCasilla(new CasillaSorpresa ("Casilla (sorpresa) " + String.valueOf(cont_sorp), mazo));
        cont_sorp++;
        
        tablero.añadeCasilla(new Casilla ("PARKING"));
        
        for (int i=0; i<3; i++, cont_calle++)
        tablero.añadeCasilla(new CasillaCalle ("Casilla (calle) " + String.valueOf(cont_calle), 
                                                ran.nextInt(50)+2000,
                                                ran.nextInt(50)+500,
                                                ran.nextInt(50)+800));

        tablero.añadeCasilla(new CasillaSorpresa ("Casilla (sorpresa) " + String.valueOf(cont_sorp), mazo));
        cont_sorp++;

        for (int i=0; i<4; i++, cont_calle++)
        tablero.añadeCasilla(new CasillaCalle ("Casilla (calle) " + String.valueOf(cont_calle), 
                                                ran.nextInt(50)+2000,
                                                ran.nextInt(50)+500,
                                                ran.nextInt(50)+800));

        tablero.añadeCasilla(new CasillaSorpresa ("Casilla (sorpresa) " + String.valueOf(cont_sorp), mazo));
        cont_sorp++;
        

    }
    
    // este método crea todas las cartas sorpresa y las almacena en el mazo de 
    // sorpresas ya creado en el constructor.
    private void inicializaMazoSorpresas () {
        
        mazo.alMazo(new SorpresaConvertirme ("Sorpresa " + String.valueOf(0)));
        for (int i=1; i<=40; i++){
            Random ran = new Random();
            int tipo = ran.nextInt(2);

            switch (tipo) {
                case 0:
                    mazo.alMazo(new SorpresaPagarCobrar ("Sorpresa " + String.valueOf(i), i));
                    break;
                case 1:
                    mazo.alMazo(new SorpresaPorCasaHotel ("Sorpresa " + String.valueOf(i), i));
                    break;
                default:
                    throw new RuntimeException ("No se pudo inicializar el MazoSorpresas. ");
            }
 
        }
    }
    
    // devuelve el jugador actual (el referenciado por indiceJugadorActual).
    public Jugador getJugadorActual() {
        return jugadores.get(indiceJugadorActual);
    }
    
    // actualiza el índice del jugador actual como consecuencia del cambio de 
    // turno. Se debe poner atención al caso en que el jugador actual sea el 
    // último de la lista.
    
    // Visibilidad cambiada de privada a publica para poder usarlo en el main de prueba
    public void pasarTurno () {
        indiceJugadorActual = (indiceJugadorActual + 1) % jugadores.size();
    }
    
    // se actualiza el estado del juego obteniendo el siguiente estado del 
    // gestor de estados (método siguienteEstado). Para ello es necesario 
    // obtener el jugador actual.
    public void siguientePasoCompletado (OperacionJuego operacion) {
        
        estado = gestor.siguienteEstado(jugadores.get(indiceJugadorActual), estado, operacion);

    }
    
    // este método delega totalmente en el método con el mismo nombre del 
    // jugador actual.
    public boolean construirCasa (int ip) {
        return getJugadorActual().construirCasa(ip);
    }
    
    // este método delega totalmente en el método con el mismo nombre del 
    // jugador actual.
    public boolean construirHotel(int ip) {
        return getJugadorActual().construirHotel(ip);
    }
    
    // este método devuelve true si alguno de los jugadores está en bancarrota.
    public boolean finalDelJuego () {
        boolean banca_rota = false;
        
        for (int i=0; i<jugadores.size() && !banca_rota; i++)
            if (jugadores.get(i).getSaldo() <= 0)
                banca_rota = true;
        
        return banca_rota;
    }
    
    public int getIndiceJugadorActual() {
        return indiceJugadorActual;
    }
    
    public ArrayList<Jugador> getJugadores() {
        return jugadores;
    }
    
    public Tablero getTablero () {
        return tablero;
    }
    
    // este método ordena la lista de jugadores en función de su saldo. 
    // Investiga como ordenar una colección en Java teniendo en cuenta que ya 
    // creaste el metodo compareTo para la las instancias de la clase Jugador.
    
    //Visibilidad modificada a public para poder realizar la operacion desde el controlador
    public ArrayList<Jugador> ranking() {
        for (int i=0; i<jugadores.size()-1; i++) {
            for (int j=i+1; j<jugadores.size(); j++) {
                if (jugadores.get(i).compareTo(jugadores.get(j)) == -1) {
                        Collections.swap(jugadores, i, j);
                }
            }
        }
        
        return jugadores;
    }
    
    // este método pide al tablero que compruebe y actualice si ha habido paso 
    // por salida (método computarPasoPorSalida) y, si la hubo, premia al 
    // jugador que pasó por ella (el jugador actual), mediante el método de 
    // Jugador pasaPorSalida.
    private void ContabilizarPasosPorSalida() {
        if (tablero.computarPasoPorSalida()) {
            jugadores.get(indiceJugadorActual).pasaPorSalida();
        }
    }    
   
    // Visibilidad cambiada de private a public
    public void avanzaJugador() {
        
        Jugador jugadorActual = getJugadorActual();
        
        int posicionActual = jugadorActual.getCasillaActual();
        
        int tirada = Dado.getInstance().tirar();
        
        int posicionNueva = tablero.nuevaPosicion(posicionActual, tirada);
        
        Casilla casilla = tablero.getCasilla(posicionNueva);
        
        ContabilizarPasosPorSalida();
        
        jugadorActual.moverACasilla(posicionNueva);
        
        casilla.recibeJugador(indiceJugadorActual, jugadores);
                
    }
    
    
    public OperacionJuego siguientePaso () {
        
        Jugador jugadorActual = getJugadorActual();

        OperacionJuego operacion = gestor.siguienteOperacion(jugadorActual, estado);

        if (operacion == OperacionJuego.PASAR_TURNO){
            
            pasarTurno();
            
            siguientePasoCompletado(operacion);
            
        }else if (operacion == OperacionJuego.AVANZAR){
            
            avanzaJugador();
            
            siguientePasoCompletado(operacion);
            
        }
        
        return operacion;
    
    }
    
    
    public boolean comprar() {
    
        Jugador jugadorActual = getJugadorActual();
        
        int numCasillaActual = jugadorActual.getCasillaActual();
        
        CasillaCalle casilla = (CasillaCalle)tablero.getCasilla(numCasillaActual);
        
        boolean res = jugadorActual.comprar(casilla);
        
        return res;
        
    }
    
}
