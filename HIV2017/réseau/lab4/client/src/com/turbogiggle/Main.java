package com.turbogiggle;
import java.io.PrintStream;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Client client;
        Scanner stdin = new Scanner(System.in);
        PrintStream stdout = new PrintStream(System.out);

        stdout.println("Entrez l'adresse ip du serveur : ");
        String ip = stdin.nextLine();

        stdout.println("Entrez le numero de port : ");
        Integer port = Integer.parseInt(stdin.nextLine());
//        while( port < 10000 || port > 10050) {
//            stdout.println("Mauvais numéro de port");
//            stdout.println("Entrez votre numéro de port (entre 10000 et 10050) :");
//            port = Integer.parseInt(stdin.nextLine());
//        }

        client =  new Client(ip, port);
        client.connectToServer();
        client.handleServer();
    }
}