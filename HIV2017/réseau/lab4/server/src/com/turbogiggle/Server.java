package com.turbogiggle;
import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

//TODO Write text file w\ answer | when poll is over, show question w/ received answers.

class Server {
    private String ipAddress;
    private Integer port;
    private Integer pollTimeOut;
    private Boolean pollTimeElapsed;
    private Boolean serverRunning;

    private String currentQuestion;
    private List<String> answers;

    private ServerSocket serverSocket;

    Server(String ip, Integer port, Integer pollTimeOut){
        this.ipAddress = ip;
        this.port = port;
        this.pollTimeOut = pollTimeOut;
        this.pollTimeElapsed = true;

        this.answers = new ArrayList<>();
    }

    void start() {
        this.serverRunning = true;

        Thread mainServerThread = new Thread(this::checkForClient);
        mainServerThread.start();
    }

    void stop() {
        this.serverRunning = false;

        try {
            serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    void ask(String question) {

        this.currentQuestion = question;

        this.pollTimeElapsed = false;

        System.out.println("Début du sondage");

        try {
            TimeUnit.SECONDS.sleep(this.pollTimeOut);
        } catch (InterruptedException e) {
            System.out.println("Écoute intérompu");
        }

        pollFinished();

    }

    private void checkForClient(){
        while (this.serverRunning) {
            try {
                this.serverSocket = new ServerSocket(this.port);
                System.out.println("Démarage de l'écoute sur le port " + serverSocket.getLocalPort());
                System.out.println("Attente de client...");

                Socket client = serverSocket.accept();

                Thread clientHandlerThread = new Thread(() -> handleClient(client));

                clientHandlerThread.start();
            }catch(SocketTimeoutException s) {
                System.out.println("Écoute intérompu, Socket expiré");
                break;
            }catch(SocketException e) {
                System.out.println("Écoute intérompu");
                break;
            }catch(IOException e) {
                e.printStackTrace();
                break;
            }
        }
    }

    private void pollFinished(){
        this.pollTimeElapsed = true;

        System.out.println("Sondage terminé");
    }

    public void handleClient (Socket socket) {
        try {

            DataOutputStream outputStream = new DataOutputStream(socket.getOutputStream());
            DataInputStream inputStream = new DataInputStream(socket.getInputStream());

            if (this.pollTimeElapsed) {

                outputStream.writeUTF("Le temps alloué pour répondre est écoulé.");

            } else {

                outputStream.writeUTF("Vous êtes connecté au serveur à l'adresse " + socket.getLocalSocketAddress()
                        + " sur le port " + socket.getLocalPort());

                outputStream.writeUTF("Question : " + this.currentQuestion);

                if (this.pollTimeElapsed) {
                    outputStream.writeUTF("Le temps alloué pour répondre est écoulé.");
                    outputStream.writeUTF("Votre réponse ne sera pas prise en compte");
                } else {
                    outputStream.writeUTF("Merci pour votre réponse!");
                    this.answers.add(inputStream.readUTF());
                }
            }

            socket.close();
        }catch(SocketTimeoutException s) {
            System.out.println("Socket for addr" + socket.getInetAddress().toString() +  "timed out!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
