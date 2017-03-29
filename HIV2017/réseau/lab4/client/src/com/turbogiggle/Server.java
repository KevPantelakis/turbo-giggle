package com.turbogiggle;
import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

class Server {
    private String ipAddress;
    private Integer port;
    private Integer pollTimeOut;
    private Boolean pollTimeElapsed;

    private String currentQuestion;
    private List<String> answers;

    Server(String ip, Integer port, Integer pollTimeOut){
        this.ipAddress = ip;
        this.port = port;
        this.pollTimeOut = pollTimeOut;
        this.pollTimeElapsed = true;

        this.answers = new ArrayList<>();
    }

    void ask(String question) {

        this.currentQuestion = question;

        this.pollTimeElapsed = false;

        Timer timer = new Timer();

        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                pollFinished();
            }
        }, this.pollTimeOut);

        checkForClient();

    }

    private void checkForClient(){
        while (!this.pollTimeElapsed) {
            try {
                ServerSocket serverSocket = new ServerSocket(this.port);
                System.out.println("Démarage de l'écoute sur le port " + serverSocket.getLocalPort());
                System.out.println("Attente de client...");

                Socket client = serverSocket.accept();

                Thread clientHandlerThread = new Thread(() -> handleClient(client));

                clientHandlerThread.start();
            }catch(SocketTimeoutException s) {
                System.out.println("Socket timed out!");
                break;
            }catch(IOException e) {
                e.printStackTrace();
                break;
            }
        }
    }

    private void pollFinished(){
        this.pollTimeElapsed = true;
    }

    public void handleClient (Socket socket) {
        try {

            DataOutputStream outputStream = new DataOutputStream(socket.getOutputStream());
            outputStream.writeUTF("Vous êtes connecté au serveur à l'adresse " + socket.getLocalSocketAddress()
                    + " sur le port " + socket.getLocalPort());

            outputStream.writeUTF("Question : " + this.currentQuestion);

            DataInputStream inputStream = new DataInputStream(socket.getInputStream());

            outputStream.writeUTF("Merci pour votre réponse!");
            this.answers.add(inputStream.readUTF());

            socket.close();
        }catch(SocketTimeoutException s) {
            System.out.println("Socket for addr" + socket.getInetAddress().toString() +  "timed out!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
