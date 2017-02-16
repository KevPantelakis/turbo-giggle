// -----Nom D'utilisateur pour la BD : INF3710-163-21 

import java.sql.*;
import java.util.Scanner;
import java.util.StringJoiner;
import java.util.TimeZone;
import java.util.Vector;
import java.util.stream.StreamSupport;


public class Main {

    public final static String nomUtilisateur = "INF3710-163-21";
    public final static String password = "9WM6RV";

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
            connexion = DriverManager.getConnection("jdbc:oracle:thin:@//ora-labos.labos.polymtl.ca:2001/labos", nomUtilisateur, password);
            System.out.println("Connected!");

            /* variables*/
            Scanner scanner = new Scanner(System.in); //lire le stdin
            String matricule  = "";
            String sigle = "";
            String cours;
            int nbCredits;
            int choice;
            Statement makeJavaGreatAgain = connexion.createStatement();
            connexion.setAutoCommit(false);
            ResultSet queryResults;
            String query;
            Vector<String> vecS = new Vector<>();
            boolean cont=true;

            //Vérifier si le matricule est valide.
            while(cont) {
                System.out.print("Entrer votre matricule \n~$> ");
                matricule = scanner.next();
                query = "SELECT NOM FROM PERSONNE P WHERE P.MATRICULE = '" + matricule + "'";
                queryResults = makeJavaGreatAgain.executeQuery(query);
                if (!queryResults.next()) {
                    System.out.println(matricule + " n'est pas un matricule valide.\n Choisissez parmis les options suivantes :\n\t(1) Entrer un nouveau matricule\n\t(2) Quitter\n~$>");
                    choice = scanner.nextInt();
                    if(choice == 2){
                        cont = false;
                    }
                }
                else break;
            }

            while (cont) {
                System.out.print("Choisissez parmis les options suivantes :\n\t(1) Affichage du choix de cours courant\n\t(2) Suppression d'un cours\n\t(3) Ajout d'un cours\n\t(4) Validation\n\t(5) Quitter\n~$>");
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
                        System.out.println(stringFill("",'-',125));
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
                            System.out.println(sigle + " n'est pas un sigle valide, la suppression de cours a été annulée.");
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
                                System.out.println("Le cours " + cours + ", à été supprimé avec succès.");
                            }
                            else{
                                System.out.println("Le cours " + cours + " n'a pas été supprimé.");
                            }
                        }
                        else {
                            System.out.println("Le cours " + cours + " ne peut pas être supprimé, car il n'est pas dans votre choix de cours.");
                        }
                        queryResults.close();
                        break;

                    // Ajout d'un cours
                    case 3:

                        /* TODO
                        Afficher les cours disponnibles.
                        */

                        query = "WITH CPRE AS ( SELECT * FROM PREREQUIS PR WHERE PR.SIGLE IN (SELECT CT.SIGLE FROM COURSTRIM CT WHERE CT.TRIM = '16-3')) SELECT DISTINCT CPR.SIGLE, C.TITRE FROM CPRE CPR, COURS C, INSCRIPTION I WHERE CPR.LEPREREQUIS IN (SELECT SIGLE FROM INSCRIPTION I WHERE I.MATRICULE = " + matricule + " AND TRIM <> '16-3' AND I.NOTEFINALE <> 'F') AND CPR.SIGLE = C.SIGLE AND CPR.SIGLE NOT IN ( SELECT I.SIGLE FROM INSCRIPTION I WHERE I.MATRICULE = " + matricule + " AND I.TRIM = '16-3') UNION SELECT CT.SIGLE, C.TITRE FROM COURSTRIM CT, COURS C WHERE CT.TRIM = '16-3' AND CT.SIGLE NOT IN ( SELECT PR.SIGLE FROM PREREQUIS PR) AND CT.SIGLE = C.SIGLE AND CT.SIGLE NOT IN ( SELECT I.SIGLE FROM INSCRIPTION I WHERE I.MATRICULE = " + matricule + " AND I.TRIM = '16-3')";

                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        System.out.println(stringFill("",'-',64));
                        System.out.println("|            SIGLE             |             TITRE            |");
                        System.out.println(stringFill("",'-',64));
                        while (queryResults.next()) {
                            vecS.add(queryResults.getString("sigle"));
                            vecS.add(queryResults.getString("titre"));
                            System.out.println(formatString(vecS));
                            vecS.clear();
                        }

                        System.out.println(stringFill("",'-',64));

                        System.out.println("Vous avez choisi: Ajout d'un cours.\nVeuillez entrer le sigle du cours à ajouter. \n~$>");
                        sigle = scanner.next();

                        /*
                        Vérifier si le sigle est valide
                        si oui, mettre le sigle et le nom du cours dans la variable cours
                        si non, annuler l'opération avec un message d'erreur
                        */
                        query = "SELECT DISTINCT C.TITRE FROM COURS C WHERE C.SIGLE = '" + sigle + "'";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        if(!queryResults.next()) {
                            System.out.println(sigle + " n'est pas un sigle valide, l'ajout de cours a été annulée");
                            queryResults.close();
                            break;
                        }

                        cours = sigle + ": " + queryResults.getString("TITRE");

                        // Vérifier si le cours est déjà dans le choix de cours.
                        query = "SELECT I.MATRICULE FROM INSCRIPTION I WHERE I.TRIM = '16-3' AND I.MATRICULE = '" + matricule + "' AND I.SIGLE = '" + sigle + "'";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        if (queryResults.next()){
                            System.out.println("Inutile d'ajouter le cours " + cours +", car le cours est déjà dans votre choix de cours" );
                            break;
                        }

                        // Vérifier si le cours ce donne au trimestre 16-3
                        query = "SELECT CT.SIGLE FROM COURSTRIM CT WHERE CT.SIGLE = '" +sigle+ "' AND CT.TRIM = '16-3'";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        if(!queryResults.next()){
                            queryResults.close();
                            System.out.println("Impossible d'ajouter le cours " + cours +", car le cours n'est pas donné à la session d'hiver 2016." );
                            break;
                        }

                        //Vérifier si l'étudiant possède tout les prérequis pour faire le cours
                        query = "SELECT LEPREREQUIS FROM PREREQUIS PR WHERE PR.SIGLE = '" + sigle + "' AND LEPREREQUIS NOT IN (SELECT SIGLE FROM INSCRIPTION I WHERE I.MATRICULE = '" + matricule + "' AND TRIM <> '16-3')";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        if(queryResults.next()){
                            System.out.println("Impossible d'ajouter le cours " + cours +", car il vous manque le(s) cours suivant(s):" );
                            do {
                                System.out.println("\t"+ queryResults.getString("LEPREREQUIS"));
                            }
                            while(queryResults.next());
                            queryResults.close();
                            break;
                        }

                        query = "INSERT INTO INSCRIPTION (sigle, trim, matricule, numSect, cumulatif, noteFinale) VALUES ('"+sigle+"', '16-3', '"+matricule+"', 1, NULL , NULL)";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        System.out.println("Le cours "+ cours + ", à bien été ajouté a votre choix de cours.");
                        queryResults.close();
                        break;

                    // Validation
                    case 4:

                        // Vérifier si l'étudiant a choisi entre 9 et 15 crédits
                        // Si oui, on update la base de données
                        // Si non, on roolback au dernier commit et on ignore les modifications faites durant la session.
                        query = "SELECT SUM(C.NBCREDITS) AS SUMCREDITS FROM COURS C, INSCRIPTION I WHERE I.TRIM = '16-3' AND I.SIGLE = C.SIGLE AND I.MATRICULE = '" + matricule + "'";
                        queryResults = makeJavaGreatAgain.executeQuery(query);
                        if(queryResults.next()){
                            nbCredits = queryResults.getInt("SUMCREDITS");

                            if(nbCredits >= 9 && nbCredits <= 15){
                                System.out.println("Vous avez validé votre choix de cours pour la prochaine session.");
                                System.out.println("Vous aurez donc "+ nbCredits + " crédits lors de votre prochaine session.");
                                connexion.commit();
                            }
                            else{
                                if(nbCredits < 9) {
                                    System.out.println("Vous n'avez pas choisi assez de crédits, vous devez choisir entre 9 et 15 crédits.");
                                    System.out.println("\tVous avez selectionné " + nbCredits + " crédits.");
                                }
                                else{
                                    System.out.println("Vous avez choisi trop de crédits, veuillez retirer des cours.");
                                    System.out.println("\tVous avez selectionné " + nbCredits + " crédits.");
                                }
                            }
                            queryResults.close();
                        }
                        break;

                    // Quitter
                    case 5:
                        cont = false;
                        connexion.rollback();
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
