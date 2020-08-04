package GUI;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

import java.io.File;

public class Main extends Application {
    static String bip = "pacman_beginning.wav";
    static Media hit = new Media(new File(bip).toURI().toString());
    static MediaPlayer mediaPlayer = new MediaPlayer(hit);
    public static Scene scene;
    public static Parent root;
    public static Stage stage;

    @Override
    public void start(Stage primaryStage) throws Exception{
        root = FXMLLoader.load(getClass().getResource("sample.fxml"));
        primaryStage.setTitle("PaCEman");
        scene=new Scene(root, 630, 850);
        primaryStage.setScene(scene);
        primaryStage.show();
        mediaPlayer.play();
        stage=primaryStage;
    }


    public static void main(String[] args) {
        launch(args);
    }

    public static void stopSong(){
        mediaPlayer.stop();
    }
}
