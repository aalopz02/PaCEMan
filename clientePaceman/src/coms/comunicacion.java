package coms;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public abstract class comunicacion {

    private final int puerto = 8080;
    private final String nombreHost = "192.168.1.6";
    protected ServerSocket server;
    protected Socket client;
    protected DataOutputStream msjOut;

    public comunicacion(String init) throws IOException {
        if (init.equals("cliente")){
            client = new Socket(nombreHost,puerto);
        } else {
            server = new ServerSocket(puerto);
            client = new Socket();
        }

    }

}
