package Logica;



public class Objeto extends javafx.scene.shape.Rectangle {

    protected java.lang.Integer  posx_siguiente;

    protected java.lang.Integer  posy_siguiente;


    public Objeto(java.lang.Integer posx_siguiente, java.lang.Integer posy_siguiente) {
        this.posx_siguiente = posx_siguiente;
        this.posy_siguiente = posy_siguiente;

    }


    protected  java.lang.Integer  getPosx_siguiente() {
        return posx_siguiente;
    }

    protected void setPosx_siguiente( java.lang.Integer  posx_siguiente) {
        this.posx_siguiente = posx_siguiente;
    }

    protected  java.lang.Integer  getPosy_siguiente() {
        return posy_siguiente;
    }

    protected void setPosy_siguiente( java.lang.Integer  posy_siguiente) {
        this.posy_siguiente = posy_siguiente;
    }
}
