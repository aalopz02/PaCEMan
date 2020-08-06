package Logica;
import Comunicacion.Cliente;
import Comunicacion.ProcessServerInput;
import GUI.Controller;
import GUI.Main;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.AnchorPane;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.LinkedList;


public class Tablero implements Cloneable {
    public java.lang.Character[][] matriz_actual;
    public java.lang.Character[][] matriz_anterior;
    public javafx.scene.layout.AnchorPane juego;
    public java.lang.Integer time=0;


    public LinkedList getLista_inanimado() {
        return lista_inanimado;
    }

    public void setLista_inanimado(LinkedList lista_inanimado) {
        this.lista_inanimado = lista_inanimado;
    }

    public KeyCode getLast() {
        return last;
    }

    public void setLast(KeyCode last) {
    }

    private javafx.scene.input.KeyCode last;
    java.util.LinkedList lista_personaje=new java.util.LinkedList();
    java.util.LinkedList lista_inanimado=new java.util.LinkedList();

    public java.lang.Character[][] getMatriz_actual() {
        return matriz_actual;
    }

    public void setMatriz_actual(java.lang.Character[][] matriz_actual) {
        this.matriz_actual = matriz_actual;
    }

    public java.lang.Character[][] getMatriz_anterior() {
        return matriz_anterior;
    }

    public void setMatriz_anterior(java.lang.Character[][] matriz_anterior) {
        this.matriz_anterior = matriz_anterior;
    }

    public void list_to_matrix(java.lang.String lista, java.lang.Integer largo, java.lang.Integer ancho) {

        java.lang.Character[][] matriz_aux = new java.lang.Character[largo][ancho];
        java.lang.Integer indice = 0;
        for (java.lang.Integer j = 0; j < largo; j++) {
            for (java.lang.Integer i = 0; i < ancho; i++) {

                matriz_aux[j][i] = lista.charAt(indice);
                indice++;

            }


        }
        setMatriz_actual(matriz_aux);
        mostrarImagen();

    }


    public void mostrarImagen(){


        for (java.lang.Integer i = 0; i < matriz_actual.length; i++) {

            for (java.lang.Integer j = 0; j < matriz_actual[0].length; j++) {

                get_image(matriz_actual[i][j],j,i);
            }

        }

    }

    public Tablero(javafx.scene.layout.AnchorPane juego) {
        this.juego = juego;
    }

    //metodo que añade un objeto rectangulo a una pantalla
    public void addobject(javafx.scene.shape.Rectangle rectangle){
        juego.getChildren().add(rectangle);
    }

    public void get_image(java.lang.Character tipo,int posx,int posy){

        java.lang.Boolean encontrado=false;
        javafx.scene.image.Image image;
        switch(tipo) {
            case 'O':

                image = new javafx.scene.image.Image(new java.io.File("bolitas_pacman.png").toURI().toString());
                create_rectangle(tipo,image,posx,posy);
                break;
            case 'X':
                image = get_image("pastillas_pacman.png");
                create_rectangle(tipo,image,posx,posy);
                break;
            case 'F':
                image = get_image("uva.png");
                create_rectangle(tipo,image,posx,posy);
                break;
            case 'J':
                image = get_image("pacman.png");
                for(int i=0;i<lista_personaje.size();i++){
                    if(((Personajes) lista_personaje.get(i)).getNombre().equals('J')) {
                        ((Personajes) lista_personaje.get(i)).setRotate(java.lang.Math.toDegrees(java.lang.Math.atan2(((Personajes) lista_personaje.get(i)).getY()-30*posy,((Personajes) lista_personaje.get(i)).getX()-30*posx))+180);
                        ((Personajes) lista_personaje.get(i)).setX(30*posx);
                        ((Personajes) lista_personaje.get(i)).setY(30*posy);
                        encontrado=true;
                    }
                }
                if(!encontrado){
                    create_rectangle(tipo,image,posx,posy);
                }
                break;
            case 'B':
                image = get_image("fantasma.png");
                create_rectangle(tipo,image,posx,posy);
                break;
            case 'P':
                image = get_image("fantasma2.png");
                create_rectangle(tipo,image,posx,posy);
                break;
            case 'I':
                image = get_image("fantasma3.png");
                create_rectangle(tipo,image,posx,posy);
                break;
            case 'C':
                image = get_image("fantasma4.png");
                create_rectangle(tipo,image,posx,posy);
                break;

        }


    }

    public javafx.scene.image.Image get_image(java.lang.String titulo_imagen){
        javafx.scene.image.Image image = new javafx.scene.image.Image(new java.io.File(titulo_imagen).toURI().toString());
        return image;
    }

    public AnchorPane getJuego() {
        return juego;
    }


    public void setJuego(AnchorPane juego) {
        this.juego = juego;
    }

    public LinkedList getLista_personaje() {
        return lista_personaje;
    }

    public void setLista_personaje(LinkedList lista_personaje) {
        this.lista_personaje = lista_personaje;
    }

    public void create_rectangle(java.lang.Character tipo, javafx.scene.image.Image image, java.lang.Integer posx, java.lang.Integer posy){

        if(tipo.equals('O')||tipo.equals('X')||tipo.equals('F')){
            Objeto o=new Objeto(0,0);
            o.setHeight(30);
            o.setWidth(30);
            o.setFill(new javafx.scene.paint.ImagePattern(image));
            o.setX(posx*30);
            o.setY(posy*30);
            lista_inanimado.add(o);
            juego.getChildren().add(o);
        }
        else{
            Personajes p=new Personajes(0,0);
            p.setHeight(30);
            p.setWidth(30);
            p.setFill(new javafx.scene.paint.ImagePattern(image));
            p.setX(posx*30);
            p.setY(posy*30);
            p.setNombre(tipo);
            lista_personaje.add(p);
            juego.getChildren().add(p);

        }

    }

    public void get_server_info(java.lang.String msj) throws java.io.IOException {
       Cliente cliente=new Cliente();
       cliente.setMsj(msj);
       cliente.initClient();
       list_to_matrix(cliente.getArray(),27,21);


    }

    public void game_init(){
        // inicia un gameloop
        javafx.animation.AnimationTimer gameLoop = new javafx.animation.AnimationTimer() {
            @Override

            public void handle(long now) {

                if (time==10) {

                    //Tecla space pulsada por lo que cuando se suelte dispara y la velocidad depende de cuanto tiempo se dejo pulsada
                    Main.scene.setOnKeyPressed(e -> {

                                if (e.getCode() == KeyCode.LEFT || e.getCode() == KeyCode.UP || e.getCode() == KeyCode.RIGHT || e.getCode() == KeyCode.DOWN) {

                                    if (last != e.getCode()) {
                                        last = e.getCode();
                                    }


                                }
                            }
                    );
                    if (last != null) {
                        for (int i = 0; i < lista_inanimado.size(); i++) {
                            juego.getChildren().remove(lista_inanimado.get(i));
                        }
                        try {
                            if (last.name() == "UP") {

                                get_server_info("UPS");
                            } else {
                                get_server_info(last.name());
                            }
                        } catch (IOException e) {
                            e.printStackTrace();

                        }
                    }
                    time=0;
                }
                time++;

            }


        };
        gameLoop.start();
    }

    }










