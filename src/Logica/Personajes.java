package Logica;

import javafx.scene.image.Image;

public class Personajes extends Objeto {
    private java.lang.Float velocidad= 3.0f;
    private java.lang.Integer modo=0;
    private java.lang.Character nombre;

    public Character getNombre() {
        return nombre;
    }

    public void setNombre(Character nombre) {
        this.nombre = nombre;
    }

    public java.lang.Integer getModo() {
        return modo;
    }

    public void setModo(java.lang.Integer modo) {
        this.modo = modo;
    }

    public Personajes( java.lang.Integer posx_siguiente,java.lang.Integer posy_siguiente) {
        super(posx_siguiente, posy_siguiente);
    }

    public java.lang.Float getVelocidad() {
        return velocidad;
    }

    public void setVelocidad(java.lang.Float velocidad) {
        this.velocidad = velocidad;
    }
}
