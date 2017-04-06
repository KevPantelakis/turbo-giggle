package com.turbogiggle;
import java.net.*;
import java.io.*;

public class Client {
    String serverIpAdress;
    Integer serverPort;


    Client(String ip, Integer port){
        this.serverIpAdress = ip;
        this.serverPort = port;
    }

    void connectToServer(){
        Socket socket;
        try {
            socket = new Socket(serverIpAdress, serverPort);
            BufferedReader buffReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream());

            System.out.println("La question demandée est: " + buffReader.readLine());

            System.out.println("Inscrivez votre réponse: ");
            BufferedReader userInputBR = new BufferedReader(new InputStreamReader(System.in));
            String userInput = userInputBR.readLine();

            out.println(userInput);

            socket.close();

        } catch (IOException e){
            e.printStackTrace();
        }
    }
}
