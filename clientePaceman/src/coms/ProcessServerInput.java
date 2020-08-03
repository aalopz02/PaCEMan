package coms;

public class ProcessServerInput {

    private final static int ancho = 21;
    private final static int largo = 27;

    public static void read(String in){
        int indice = 0;
        if (in.equals("ok")){
            System.out.println(in);
            return;
        }
        for (int j = 0; j < largo; j ++){
            for (int i = 0; i < ancho; i++){
                System.out.print(in.charAt(indice));
                indice ++;
            }
            System.out.println();
        }
    }

}
