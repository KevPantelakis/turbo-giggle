import java.sql.*;
import java.util.Scanner;
import java.util.StringJoiner;
import java.util.TimeZone;

public class Main {

    public static void main(String[] args) {
        Connection connexion= null;
        try {
            TimeZone timeZone = TimeZone.getTimeZone("Montreal");
            TimeZone.setDefault(timeZone);
            Class.forName("oracle.jdbc.OracleDriver");
            connexion = DriverManager.getConnection("jdbc:oracle:thin:@//ora-labos.labos.polymtl.ca:2001/labos", "INF3710-163-21","9WM6RV");
            System.out.println("Connected!");

            Scanner scanner = new Scanner(System.in);
            String matricule;
            int choice;

            System.out.print("Entrer votre matricule \n~$> ");
            matricule = scanner.nextLine();

            System.out.print("\nChoisissez parmis les options suivantes :\n\t(1) Affichage du choix de cours courrant\n\t(2) Suppression d'un cours\n\t(3) Ajout d'un cours\n\t(4) Validation\n~$>");
            choice = scanner.nextInt();

            Statement makeJavaGreatAgain = connexion.createStatement();
            ResultSet rset;
            String req;
            switch (choice){
                case 1:
                    req = "SELECT DISTINCT C.TITRE,P.NOM,P.PRENOM,I.SIGLE,I.NUMSECT FROM COURS C,PERSONNE P, COURSTRIM CT, INSCRIPTION I WHERE C.SIGLE = I.SIGLE AND C.SIGLE = CT.SIGLE AND I.TRIM = '16-3' AND P.NAS = CT.RESPONSABLE AND I.MATRICULE = " + matricule;
                    rset = makeJavaGreatAgain.executeQuery(req);
                    System.out.println("CHOIX DE COURS SESSION AUTOMNE 2016");
                    System.out.println("-----------------------------------------------------------------------------------------------------------------------------");
                    System.out.println("|            SIGLE             |             TITRE            |      NUMERO DE SECTION       |     RESPONSABLE DU COURS     |");
                    System.out.println("-----------------------------------------------------------------------------------------------------------------------------");
                    while ( rset.next() ) {
                        String sigle = rset.getString("sigle");
                        String titre = rset.getString("titre");
                        String numsect = rset.getString("numsect");
                        String nom = rset.getString("nom") + " " + rset.getString("prenom");
                        System.out.println("| " + sigle + " | " + titre + " | " + numsect + " | "+ nom + " |");
                    }
                    rset.close();
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
            }

            makeJavaGreatAgain.close();


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


//    Statement monSelect = maConnexion.createStatement(); ResultSet resSelect = monSelect.executeQuery
//        ("SELECT cid, cname, city FROM Customers");