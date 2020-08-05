package Logica;
import Comunicacion.Cliente;
import GUI.Controller;


public class Tablero implements Cloneable {
    public java.lang.Character[][] matriz_actual;
    public java.lang.Character[][] matriz_anterior;
    public javafx.scene.layout.AnchorPane juego;

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
        System.out.println("--------------------");
        System.out.println(juego.getHeight());
        setMatriz_actual(matriz_aux);
        mostrarImagen();

    }


    public void mostrarImagen(){
        System.out.println(matriz_actual.length);
        System.out.println(matriz_actual[0].length);


        for (java.lang.Integer i = 0; i < matriz_actual.length; i++) {
            System.out.println("HOla");
            for (java.lang.Integer j = 0; j < matriz_actual[0].length; j++) {

                get_image(matriz_actual[i][j],j,i);
                System.out.println(matriz_actual[i][j]);
            }

        }

    }
    public void gen(){
        Objeto o=new Objeto(0,0);
        o.setHeight(30);
        o.setWidth(30);
        javafx.scene.image.Image image = new javafx.scene.image.Image(new java.io.File("bolitas_pacman.png").toURI().toString());
        o.setFill(new javafx.scene.paint.ImagePattern(image));
        o.setX(30);
        o.setY(30);
        juego.getChildren().add(o);

    }

    public Tablero(javafx.scene.layout.AnchorPane juego) {
        this.juego = juego;
    }

    //metodo que añade un objeto rectangulo a una pantalla
    public void addobject(javafx.scene.shape.Rectangle rectangle){
        juego.getChildren().add(rectangle);
    }

    public void get_image(java.lang.Character tipo,int posx,int posy){
        System.out.println(tipo);
        javafx.scene.image.Image image;
        switch(tipo) {
            case 'O':
                System.out.println("hola");
                image = new javafx.scene.image.Image(new java.io.File("bolitas_pacman.png").toURI().toString());
                create_rectangle(image,posx,posy);
                break;
            case 'X':
                image = get_image("pastillas_pacman.png");
                create_rectangle(image,posx,posy);
                break;
            case 'F':
                image = get_image("uva.png");
                create_rectangle(image,posx,posy);
                break;
            case 'J':
                image = get_image("pacman.png");
                create_rectangle(image,posx,posy);
                break;
            case 'B':
                image = get_image("fantasma.png");
                create_rectangle(image,posx,posy);
                break;
            case 'P':
                image = get_image("fantasma2.png");
                create_rectangle(image,posx,posy);
                break;
            case 'I':
                image = get_image("fantasma3.png");
                create_rectangle(image,posx,posy);
                break;
            case 'C':
                image = get_image("fantasma4.png");
                create_rectangle(image,posx,posy);
                break;

        }


    }

    public javafx.scene.image.Image get_image(java.lang.String titulo_imagen){
        javafx.scene.image.Image image = new javafx.scene.image.Image(new java.io.File(titulo_imagen).toURI().toString());
        return image;
    }

    public void create_rectangle(javafx.scene.image.Image image, java.lang.Integer posx,java.lang.Integer posy){
        System.out.println("hola");
        Objeto o=new Objeto(0,0);
        o.setHeight(30);
        o.setWidth(30);
        o.setFill(new javafx.scene.paint.ImagePattern(image));
        o.setX(posx*30);
        o.setY(posy*30);
        juego.getChildren().add(o);

    }

    public void get_server_info() throws java.io.IOException {
        Cliente cliente=new Cliente();
        cliente.initClient();
        list_to_matrix(cliente.getArray(),27,21);



    }



    }






