package GUI;


import Comunicacion.Cliente;
import Logica.Tablero;

public class Controller {
    public javafx.scene.layout.AnchorPane inicio;
    public javafx.scene.control.Button button1;
    public javafx.scene.control.Button button2;
    public javafx.scene.layout.AnchorPane juego;
    private javafx.scene.media.MediaPlayer mediaplayer;
    static java.lang.String bip = "pacman-intermission.mp3";
    static javafx.scene.media.Media hit = new javafx.scene.media.Media(new java.io.File(bip).toURI().toString());
    static javafx.scene.media.MediaPlayer mediaPlayer = new javafx.scene.media.MediaPlayer(hit);


    public void begin_game(javafx.scene.input.MouseEvent mouseEvent) throws java.io.IOException {
        Main.stopSong();
        button1.setVisible(false);
        inicio.setVisible(false);
        button1.setVisible(false);
        juego.setVisible(true);
        //mediaPlayer.play();
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

    public void spectator_mode(javafx.scene.input.MouseEvent mouseEvent) throws java.io.IOException {
        Main.stopSong();
        button1.setVisible(false);
        inicio.setVisible(false);
        button1.setVisible(false);
        juego.setVisible(true);
        //mediaPlayer.play();
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
