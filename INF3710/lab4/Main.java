import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.TimeZone;

public class Main {

    public static void main(String[] args) {
        System.out.println("Hello World!");

        Connection maConnexion= null;
        try {

            System.out.println("trying to connect");

            TimeZone timeZone = TimeZone.getTimeZone("Montreal");
            TimeZone.setDefault(timeZone);
            Class.forName("oracle.jdbc.OracleDriver");
            maConnexion = DriverManager.getConnection("jdbc:oracle:thin:@//ora-labos.labos.polymtl.ca:2001/labos", "INF3710-163-21","9WM6RV");

            System.out.println("Connected!");
        }
        catch(ClassNotFoundException ex) {
            System.out.println("Pilote JDBC non trouve" + ex.getMessage());
        }
        catch(SQLException ex) {
            System.out.println("Connexion impossible" + ex.getMessage());
            ex.printStackTrace();
        }
    }
}