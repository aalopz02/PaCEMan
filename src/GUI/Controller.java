package GUI;

import javafx.scene.control.Button;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.media.MediaPlayer;

public class Controller {
    public AnchorPane inicio;
    public Button button1;
    public Button button2;
    public AnchorPane juego;
    private MediaPlayer mediaplayer;



    public void begin_game(MouseEvent mouseEvent) {

        button1.setVisible(false);
        inicio.setVisible(false);
        button1.setVisible(false);
        juego.setVisible(true);
        Main.stopSong();
       /* titulo.setVisible(false);
        juegopantalla.setVisible(true);
        Juego game=new Juego(juegopantalla);
        game.gameinit();
        Main.stopSong();
        timetexto=timetext;
        puntajetexto=puntajetext;*/
    }
}
