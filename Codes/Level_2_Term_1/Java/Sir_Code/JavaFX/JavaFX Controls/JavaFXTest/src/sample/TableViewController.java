package sample;

import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.util.Callback;

public class TableViewController {

    @FXML
    private TableView tableView;

    @FXML
    private Button button;

    private boolean init = true;

    void initializeColumns() {
        TableColumn<Person, String> firstNameCol = new TableColumn<>("First Name");
        firstNameCol.setMinWidth(100);
        firstNameCol.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        firstNameCol.setCellFactory(TextFieldTableCell.<Person>forTableColumn());

        firstNameCol.setOnEditCommit(
                (TableColumn.CellEditEvent<Person, String> t) -> {
                    ((Person) t.getTableView().getItems().get(
                            t.getTablePosition().getRow())
                    ).setFirstName(t.getNewValue());
                }
        );

        TableColumn<Person, String> lastNameCol = new TableColumn<>("Last Name");
        lastNameCol.setMinWidth(100);
        lastNameCol.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        lastNameCol.setCellFactory(TextFieldTableCell.<Person>forTableColumn());

        lastNameCol.setOnEditCommit(
                (TableColumn.CellEditEvent<Person, String> t) -> {
                    ((Person) t.getTableView().getItems().get(
                            t.getTablePosition().getRow())
                    ).setLastName(t.getNewValue());
                }
        );

        TableColumn<Person, String> emailCol = new TableColumn<>("Email");
        emailCol.setMinWidth(200);
        emailCol.setCellValueFactory(new PropertyValueFactory<>("email"));
        emailCol.setCellFactory(TextFieldTableCell.<Person>forTableColumn());
        emailCol.setOnEditCommit(
                (TableColumn.CellEditEvent<Person, String> t) -> {
                    ((Person) t.getTableView().getItems().get(
                            t.getTablePosition().getRow())
                    ).setEmail(t.getNewValue());
                }
        );

        TableColumn<Person, String> actionCol = new TableColumn<>("Action");
        actionCol.setCellValueFactory(new PropertyValueFactory<>("action"));

        Callback<TableColumn<Person, String>, TableCell<Person, String>> cellFactory =
            new Callback<TableColumn<Person, String>, TableCell<Person, String>>() {
                @Override
                public TableCell call( final TableColumn<Person, String> param ) {
                    final TableCell<Person, String> cell = new TableCell<Person, String>() {
                        final Button btn = new Button("Select");

                        @Override
                        public void updateItem(String item, boolean empty) {
                            super.updateItem( item, empty );
                            if (empty) {
                                setGraphic(null);
                                setText(null);
                            }
                            else {
                                // action of 'Select' button click
                                btn.setOnAction((ActionEvent event) -> {
                                            Person person = getTableView().getItems().get(getIndex());
                                            String name = person.getFirstName() + " " + person.getLastName() + "@" + person.getEmail();
                                            Alert a = new Alert(Alert.AlertType.CONFIRMATION);
                                            a.setContentText(name);
                                            a.showAndWait();
                                        }
                                );
                                setGraphic(btn);
                                setText(null);
                            }
                        }
                    };
                    return cell;
                }
            };
        actionCol.setCellFactory(cellFactory);

        tableView.getColumns().addAll(firstNameCol, lastNameCol, emailCol, actionCol);
    }

    @FXML
    void buttonAction(ActionEvent event) {

        if (init) {
            initializeColumns();
            init = false;
        }

        final ObservableList<Person> data = FXCollections.observableArrayList(
                new Person("Jacob", "Smith", "jacob.smith@example.com"),
                new Person("Isabella", "Johnson", "isabella.johnson@example.com"),
                new Person("Ethan", "Williams", "ethan.williams@example.com"),
                new Person("Emma", "Jones", "emma.jones@example.com"),
                new Person("Michael", "Brown", "michael.brown@example.com")
        );

        tableView.setEditable(true);
        tableView.setItems(data);

        //Person p = new Person("A", "B", "C@D.com");
        //tableView.getItems().add(p);

    }
}
