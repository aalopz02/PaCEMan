package GUI;

import Comunicacion.Cliente;
import Logica.Tablero;

public class Controller {
    public javafx.scene.layout.AnchorPane inicio;
    public javafx.scene.control.Button button1;
    public javafx.scene.control.Button button2;
    public javafx.scene.layout.AnchorPane juego;
    private javafx.scene.media.MediaPlayer mediaplayer;

    public void begin_game(javafx.scene.input.MouseEvent mouseEvent) throws java.io.IOException {
        button1.setVisible(false);
        inicio.setVisible(false);
        button1.setVisible(false);
        juego.setVisible(true);
        Main.stopSong();
        Tablero nuevotablero=new Tablero(juego);
        //cliente.initClient();
        //nuevotablero.gen();
        nuevotablero.get_server_info("Inicio");
        nuevotablero.setMatriz_anterior(nuevotablero.getMatriz_actual());
        nuevotablero.game_init();
       /* titulo.setVisible(false);
        juegopantalla.setVisible(true);
        Juego game=new Juego(juegopantalla);
        game.gameinit();
        Main.stopSong();
        timetexto=timetext;
        puntajetexto=puntajetext;*/
    }
}
