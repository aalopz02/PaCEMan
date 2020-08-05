package Comunicacion;
import Logica.Tablero;


public class ProcessServerInput {

    private final static java.lang.Integer ancho = 21;
    private final static java.lang.Integer largo = 27;

    public static java.lang.String read(java.lang.String in){
        java.lang.Integer indice = 0;
        if (in.equals("ok")){
            System.out.println(in);

        }
        for (java.lang.Integer j = 0; j < largo; j ++){
            for (java.lang.Integer i = 0; i < ancho; i++){
                System.out.print(in.charAt(indice));
                indice ++;
            }
            System.out.println();

        }


      return in;
    }

}
