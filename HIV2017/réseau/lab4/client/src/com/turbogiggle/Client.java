package com.turbogiggle;
import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Client {
    private String serverIpAdress;
    private Integer serverPort;


    Client(String ip, Integer port){
        this.serverIpAdress = ip;
        this.serverPort = port;
    }

    void connectToServer(){
        Socket socket;
        try {
            socket = new Socket(serverIpAdress, serverPort);

            DataOutputStream outputStream = new DataOutputStream(socket.getOutputStream());
            DataInputStream inputStream = new DataInputStream(socket.getInputStream());

            System.out.println("SERVEUR : " + inputStream.readUTF());

            Boolean pollTimeEllapsed = inputStream.readBoolean();

            System.out.println("SERVEUR : " + inputStream.readUTF());

            if (!pollTimeEllapsed) {
                System.out.println("Inscrivez votre réponse: ");
                Scanner stdin = new Scanner(System.in);
                String userInput = stdin.nextLine();
                outputStream.writeUTF(userInput);
                System.out.println("SERVEUR : " + inputStream.readUTF());
            }

            socket.close();

        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
