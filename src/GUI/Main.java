package GUI;




public class Main extends javafx.application.Application {
    static java.lang.String bip = "pacman_beginning.wav";
    static javafx.scene.media.Media hit = new javafx.scene.media.Media(new java.io.File(bip).toURI().toString());
    static javafx.scene.media.MediaPlayer mediaPlayer = new javafx.scene.media.MediaPlayer(hit);
    public static javafx.scene.Scene scene;
    public static javafx.scene.Parent root;
    public static javafx.stage.Stage stage;

    @Override
    public void start(javafx.stage.Stage primaryStage) throws java.io.IOException{

        root = javafx.fxml.FXMLLoader.load(getClass().getResource("sample.fxml"));
        primaryStage.setTitle("PaCEman");
        scene=new javafx.scene.Scene(root, 630, 850);
        primaryStage.setScene(scene);
        primaryStage.show();
        //mediaPlayer.play();
        stage=primaryStage;
    }


    public static void main(String[] args) throws java.io.IOException {
        launch(args);
    }

    public static void stopSong(){
        mediaPlayer.stop();
    }
}
