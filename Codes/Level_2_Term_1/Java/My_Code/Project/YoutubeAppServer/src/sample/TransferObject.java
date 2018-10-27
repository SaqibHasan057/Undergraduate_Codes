package sample;

import javafx.collections.ObservableList;

import java.io.Serializable;
import java.util.List;

/**
 * Created by Dipto on 03/12/2015.
 */
public class TransferObject implements Serializable {
    List<Table> mine;
    public TransferObject(ObservableList<Table> param){
        this.mine = param;
    }
    public List<Table> getMine(){
        return mine;
    }
}
