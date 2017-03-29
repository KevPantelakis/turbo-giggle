package com.turbogiggle;

import java.io.PrintStream;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Server server;
        String status = "";

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

        server = new Server(ip, port, time);

        String question;

        while(!status.toLowerCase().equals("quitter")) {
            stdout.println("Entrez votre question :");
            question = stdin.nextLine();

            server.ask(question);

            stdout.println("Sondage terminé, Appuyez sur entrer pour poser une nouvelle question ou entrez \"quitter\" pour quitter :");
            status = stdin.nextLine();
        }
    }
}
