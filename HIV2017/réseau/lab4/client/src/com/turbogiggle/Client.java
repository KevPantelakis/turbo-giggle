package com.turbogiggle;
import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Client {
    private String serverIpAddress;
    private Integer serverPort;
    private Integer maxAnswerLength;
    private Socket clientSocket;

    Client(String ip, Integer port){
        this.serverIpAddress = ip;
        this.serverPort = port;
        maxAnswerLength = 200;
    }

    void handleServer(){
        try {
            DataOutputStream outputStream = new DataOutputStream(clientSocket.getOutputStream());
            DataInputStream inputStream = new DataInputStream(clientSocket.getInputStream());

            System.out.println("SERVEUR : " + inputStream.readUTF());

            Boolean pollTimeEllapsed = inputStream.readBoolean();

            System.out.println("SERVEUR : " + inputStream.readUTF());

            if (!pollTimeEllapsed) {
                Scanner stdin = new Scanner(System.in);
                String userInput;

                do {
                    System.out.println("Vous devez saisir une réponse de moins de 200 caractères");
                    System.out.println("Inscrivez votre réponse: ");
                    userInput = stdin.nextLine();
                } while (userInput.length() > maxAnswerLength);

                outputStream.writeUTF(userInput);
                System.out.println("SERVEUR : " + inputStream.readUTF());

                clientSocket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    void connectToServer(){
        try {
            clientSocket = new Socket(serverIpAddress, serverPort);
        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
