package sample;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.input.MouseEvent;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

import javafx.scene.media.MediaView;

import java.io.File;
import java.time.Duration;

/**
 * Created by Dipto on 01/12/2015.
 */
public class Player {
    Main main;

    Media path;
    private MediaPlayer movie;

    @FXML
    private MediaView VIEW;

    @FXML
    private Button play;

    @FXML
    private Button pause;

    @FXML
    private Button stop;

    @FXML
    private Slider time;
    
    public void setMain(Main main){
        this.main=main;
    }

    public void setPath(File file){
        this.path = new Media(file.toURI().toString());
    }
    
    public void start(){
        movie = new MediaPlayer(path);
        VIEW.setMediaPlayer(movie);
        movie.currentTimeProperty().addListener(new ChangeListener<javafx.util.Duration>() {
            @Override
            public void changed(ObservableValue<? extends javafx.util.Duration> observable, javafx.util.Duration duration, javafx.util.Duration current) {
                time.setValue(current.toSeconds());
            }
        });
        movie.play();

    }

    public void stop(){
        movie.stop();
    }
    @FXML
    public void pauseButton(ActionEvent event){
        movie.pause();
    }
    @FXML
    public void playButton(ActionEvent event){
        movie.play();
    }
    @FXML
    public void stopButton(ActionEvent event){
        movie.stop();
    }
    @FXML
    public void timeKeep(ActionEvent event){

    }
}
