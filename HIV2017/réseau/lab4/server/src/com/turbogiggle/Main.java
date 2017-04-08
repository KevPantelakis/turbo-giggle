package com.turbogiggle;

import java.io.IOException;
import java.io.PrintStream;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Server server;
        String status = "";
        int maxQuestionLength = 500;

        Scanner stdin = new Scanner(System.in);
        PrintStream stdout = new PrintStream(System.out);

        stdout.println("Entrez votre adresse IP :");
        String ip = stdin.nextLine();

        stdout.println("Entrez votre numéro de port (entre 10000 et 10050) :");
        Integer port = Integer.parseInt(stdin.nextLine());
        while( port < 10000 || port > 10050) {
            stdout.println("Mauvais numéro de port");
            stdout.println("Entrez votre numéro de port (entre 10000 et 10050) :");
            port = Integer.parseInt(stdin.nextLine());
        }

        stdout.println("Entrez le temps de sondage :");
        Integer time = Integer.parseInt(stdin.nextLine());

        try {

            server = new Server(ip, port, time);

            server.start();

            String question = "";

            while(!status.toLowerCase().equals("quitter")) {
                do {
                    stdout.println("Vous devez saisir une question de moins de 500 caractères.");
                    stdout.println("Entrez votre question :");
                    question = stdin.nextLine();
                } while (question.length() > maxQuestionLength);

                server.writeInOutputFile(question+ "\r\n");
                server.ask(question);


                stdout.println("Appuyez sur entrer pour poser une nouvelle question ou entrez \"quitter\" pour quitter :");
                status = stdin.nextLine();
                if(!status.toLowerCase().equals("quitter")) {
                    server.stop();
                    server = new Server(ip, port, time);
                    server.start();
                }
            }
            server.stop();

        } catch (IOException e) {
            stdout.println("Un problème est survenu lors de la création du serveur. Fin du programme.");
            e.printStackTrace();
        }

    }
}
