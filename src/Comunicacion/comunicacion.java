package Comunicacion;


import Logica.Tablero;

public abstract class comunicacion {

    private final java.lang.Integer puerto = 8080;
    private final java.lang.String nombreHost = "192.168.1.6";
    protected java.net.ServerSocket server;
    protected java.net.Socket client;
    protected java.io.DataOutputStream msjOut;

    public comunicacion(java.lang.String init) throws java.io.IOException {
        if (init.equals("cliente")){
            client = new java.net.Socket(nombreHost,puerto);
        } else {
            server = new java.net.ServerSocket(puerto);
            client = new java.net.Socket();
        }

    }

}
