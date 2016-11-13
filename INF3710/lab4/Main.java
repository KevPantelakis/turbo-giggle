import java.sql.*;
import java.util.Scanner;
import java.util.StringJoiner;
import java.util.TimeZone;
import java.util.Vector;


public class Main {

    public static String stringFill(String targetString,char filling, int repetition){
        for (int j = 0; j < repetition; j++) {
            targetString += filling;
        }
        return targetString;
    }
    public static String formatString(Vector<String> vec){
        String formatedString = "|";
        int stringLen = 0;
        int repetition = 0;
        for (String i:vec) {
            stringLen = i.length();
            repetition = (30 - stringLen)/2;
            //formatedString += "|";
            if((30 - stringLen) % 2 == 0){
                formatedString = stringFill(formatedString,' ',repetition );
                formatedString += i;
                formatedString = stringFill(formatedString,' ',repetition );

            }
            else{
                formatedString = stringFill(formatedString,' ',repetition + 1);
                formatedString += i;
                formatedString = stringFill(formatedString,' ',repetition);
            }
            formatedString += "|";
        }
        return formatedString;
    }

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

            System.out.print("\nChoisissez parmis les options suivantes :\n\t(1) Affichage du choix de cours courant\n\t(2) Suppression d'un cours\n\t(3) Ajout d'un cours\n\t(4) Validation\n\t(5) Quitter\n~$>");
            choice = scanner.nextInt();

            Statement makeJavaGreatAgain = connexion.createStatement();
            ResultSet rset;
            String req;
            Vector<String> vecS = new Vector<>();
            while (choice !=5) {
                switch (choice) {
                    case 1:
                        System.out.println("Vous avez choisis: Affichage du choix de cours courant");
                        req ="WITH T AS (SELECT DISTINCT C.TITRE,CT.RESPONSABLE,I.SIGLE,I.NUMSECT FROM COURS C, COURSTRIM CT, INSCRIPTION I WHERE (C.SIGLE = I.SIGLE AND C.SIGLE = CT.SIGLE AND I.TRIM = '16-3' AND I.MATRICULE = " + matricule +" )) select T.SIGLE, T.TITRE, T.NUMSECT, P.PRENOM, P.NOM FROM T LEFT JOIN PERSONNE P on (T.RESPONSABLE = P.NAS)";
                        rset = makeJavaGreatAgain.executeQuery(req);
                        System.out.println("CHOIX DE COURS SESSION AUTOMNE 2016");
                        System.out.println("-----------------------------------------------------------------------------------------------------------------------------");
                        System.out.println("|            SIGLE             |             TITRE            |      NUMERO DE SECTION       |     RESPONSABLE DU COURS     |");
                        System.out.println("-----------------------------------------------------------------------------------------------------------------------------");
                        while (rset.next()) {
                            vecS.add(rset.getString("sigle"));
                            vecS.add(rset.getString("titre"));
                            vecS.add(rset.getString("numsect"));
                            vecS.add(rset.getString("prenom") + " " + rset.getString("nom"));
                            System.out.println(formatString(vecS));
                            vecS.clear();
                        }
                        System.out.println("-----------------------------------------------------------------------------------------------------------------------------");
                        rset.close();
                        break;
                    case 2:
                        System.out.println("Vous avez choisis: Suppression d'un cours\n~$>");
                        String sigle = scanner.nextLine();
                        req = "DELETE FROM INSCRIPTION I WHERE I.MATRICULE = " + matricule + " AND I.SIGLE = " + sigle + " AND I.TRIM='16-3'";
                        rset = makeJavaGreatAgain.executeQuery(req);
                        rset.close();
                        break;
                    case 3:
                        break;
                    case 4:
                        connexion.commit();
                        break;

                }
                System.out.print("\nChoisissez parmis les options suivantes :\n\t(1) Affichage du choix de cours courant\n\t(2) Suppression d'un cours\n\t(3) Ajout d'un cours\n\t(4) Validation\n\t(5) Quitter\n~$>");
                choice = scanner.nextInt();
            }
            makeJavaGreatAgain.close();
            connexion.close();

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