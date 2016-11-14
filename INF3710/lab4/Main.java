import java.sql.*;
import java.util.Scanner;
import java.util.StringJoiner;
import java.util.TimeZone;
import java.util.Vector;
import java.util.stream.StreamSupport;


public class Main {

    public static String stringFill(String targetString,char filling, int repetition){
        for (int j = 0; j < repetition; j++) {
            targetString += filling;
        }
        return targetString;
    }
    public static String formatString(Vector<String> vec){
        String formatedString = "|";
        int stringLen;
        int repetition;
        for (String i:vec) {
            if(i.length() >30){
                i= i.substring(0, 29) + ".";
            }
            stringLen = i.length();
            repetition = (30 - stringLen)/2;
            if((30 - stringLen) % 2 == 0){
                formatedString = stringFill(formatedString,' ',repetition );
            }
            else{
                formatedString = stringFill(formatedString,' ',repetition + 1);
            }
            formatedString += i;
            formatedString = stringFill(formatedString,' ',repetition);
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

            /* variables*/
            Scanner scanner = new Scanner(System.in); //lire le stdin
            String matricule;
            String sigle;
            String cours;
            int choice;
            Statement makeJavaGreatAgain = connexion.createStatement();
            ResultSet queryResults;
            String query;
            Vector<String> vecS = new Vector<>();

            System.out.print("Entrer votre matricule \n~$> ");
            matricule = scanner.next();

            boolean cont=true;
            while (cont) {
                System.out.print("\nChoisissez parmis les options suivantes :\n\t(1) Affichage du choix de cours courant\n\t(2) Suppression d'un cours\n\t(3) Ajout d'un cours\n\t(4) Validation\n\t(5) Quitter\n~$>");
                choice = scanner.nextInt();
                switch (choice) {

                    //Affichage du choix de cours courrant
                    case 1:
                        query = "WITH T AS (SELECT DISTINCT C.TITRE,CT.RESPONSABLE,I.SIGLE,I.NUMSECT FROM COURS C,COURSTRIM CT,INSCRIPTION I WHERE C.SIGLE = I.SIGLE AND C.SIGLE = CT.SIGLE AND I.TRIM = '16-3' AND I.MATRICULE = " + matricule +" AND CT.TRIM = '16-3') select T.SIGLE, T.TITRE, T.NUMSECT, P.PRENOM, P.NOM FROM T LEFT JOIN PERSONNE P on (T.RESPONSABLE = P.NAS)";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        System.out.println("CHOIX DE COURS SESSION AUTOMNE 2016");
                        System.out.println(stringFill("",'-',125));
                        System.out.println("|            SIGLE             |             TITRE            |      NUMERO DE SECTION       |     RESPONSABLE DU COURS     |");
                        System.out.println(stringFill("",'-',125));
                        while (queryResults.next()) {
                            vecS.add(queryResults.getString("sigle"));
                            vecS.add(queryResults.getString("titre"));
                            vecS.add(queryResults.getString("numsect"));
                            vecS.add(queryResults.getString("prenom") + " " + queryResults.getString("nom"));
                            System.out.println(formatString(vecS));
                            vecS.clear();
                        }
                        System.out.println("-----------------------------------------------------------------------------------------------------------------------------");
                        queryResults.close();
                        break;

                    //Suppression d'un cours
                    case 2:
                        System.out.println("Vous avez choisi: Suppression d'un cours.\nVeuillez entrer le sigle du cours à retirer: \n~$>");
                        sigle = scanner.next();

                        /*
                        Vérifier si le sigle est valide
                        si oui, mettre le sigle et le nom du cours dans la variable cours
                        si non, annuler l'opération avec un message d'erreur
                        */
                        query = "SELECT DISTINCT C.TITRE FROM COURS C WHERE C.SIGLE = '" + sigle + "'";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        if(queryResults.next()) {
                            cours = sigle + ": " + queryResults.getString("TITRE");
                        }
                        else {
                            System.out.println(sigle + " n'est pas un sigle valide, la suppression de cours a été annulée. \n");
                            queryResults.close();
                            break;
                        }
                        /*
                        Vérifier si le cours figure dans le choix de cours de l'étudiant
                        si oui, confirmer la suppression
                        si non, annuler l'opération avec un message d'erreur
                        */
                        query = "SELECT I.SIGLE FROM INSCRIPTION I WHERE I.TRIM = '16-3' AND I.MATRICULE  = '" + matricule + "' AND I.SIGLE = '" + sigle + "'";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        if (queryResults.next())
                        {

                            //Si on confirme, on supprime le cours de l'inscription
                            //Si on annule, on quitte l'opération avec un message
                            System.out.println("Voulez-vous vraiment supprimer le cours? "+ cours +"\n\t(1) oui\n\t(2) non\n~$> ");
                            choice = scanner.nextInt();
                            if(choice == 1) {
                                query = "DELETE FROM INSCRIPTION I WHERE I.TRIM = '16-3' AND I.MATRICULE = '" + matricule + "' AND I.SIGLE = '" + sigle + "'";
                                makeJavaGreatAgain.executeQuery(query);
                                System.out.println("Le cours " + cours + ", à été supprimé avec succès.\n");
                            }
                            else{
                                System.out.println("Le cours " + cours + " n'a pas été supprimé.\n");
                            }
                        }
                        else {
                            System.out.println("Le cours " + cours + " ne peut pas être supprimé, car il n'est pas dans votre choix de cours.\n");
                        }
                        queryResults.close();
                        break;

                    // Ajout d'un cours
                    case 3:

                        /* TODO
                        VÉRIFIER SI LE COURS SE DONNE AU TRIMESTRE 16-3,
                        AJOUTER LE COURS
                        */
                        System.out.println("Vous avez choisi: Ajout d'un cours.\nVeuillez entrer le sigle du cours à ajouter. \n"+ "~$>");
                        sigle = scanner.next();

                        /*
                        Vérifier si le sigle est valide
                        si oui, mettre le sigle et le nom du cours dans la variable cours
                        si non, annuler l'opération avec un message d'erreur
                        */
                        query = "SELECT DISTINCT C.TITRE FROM COURS C WHERE C.SIGLE = '" + sigle + "'";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        if(queryResults.next()) {
                            cours = sigle + ": " + queryResults.getString("TITRE");
                        }
                        else {
                            System.out.println(sigle + " n'est pas un sigle valide, l'ajout de cours a été annulée \n");
                            queryResults.close();
                            break;
                        }
                        // Vérifier si le cours ce donne au trimestre 16-3


                        //Vérifier si l'étudiant possède tout les prérequis pour faire le cours
                        query = "SELECT LEPREREQUIS FROM PREREQUIS PR WHERE PR.SIGLE = '" + sigle + "' AND LEPREREQUIS NOT IN (SELECT SIGLE FROM INSCRIPTION I WHERE I.MATRICULE = '"+matricule+"' AND TRIM <> '16-3')";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        if(queryResults.next()){
                            System.out.println("Impossible d'ajouter le cours " + cours +", car il vous manque le(s) cours suivant(s):\t" );
                            do {
                                System.out.println("\t"+ queryResults.getString("LEPREREQUIS"));
                            }
                            while(queryResults.next());
                            queryResults.close();
                            break;
                        }

                        //Ajouter le cours aux choix de cours

                        break;

                    // Validation
                    case 4:
                        connexion.commit();
                        break;

                    // Quitter
                    case 5:
                        cont = false;
                        break;
                }
            }
            makeJavaGreatAgain.close();
            connexion.close();

        }
        catch(ClassNotFoundException ex) {
            System.out.println("Pilote JDBC non trouvé" + ex.getMessage());
        }
        catch(SQLException ex) {
            System.out.println("Connexion impossible" + ex.getMessage());
            ex.printStackTrace();
        }
    }
}


//    Statement monSelect = maConnexion.createStatement(); ResultSet resSelect = monSelect.executeQuery
//        ("SELECT cid, cname, city FROM Customers");