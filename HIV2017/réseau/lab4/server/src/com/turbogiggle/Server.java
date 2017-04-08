package com.turbogiggle;
import java.io.*;
import java.net.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

class Server {
    public static final String TEXTFILEPATH = System.getProperty("user.dir")+ "/src/reponses.txt";
    private Integer pollTimeOut;
    private Boolean pollTimeElapsed;
    private Boolean serverRunning;
    private String currentQuestion;
    private ServerSocket serverSocket;

    Server(String ip, Integer port, Integer pollTimeOut) throws IOException {

        InetAddress addr = InetAddress.getByName(ip);
        this.serverSocket = new ServerSocket(port, 0, addr);

        this.pollTimeOut = pollTimeOut;
        this.pollTimeElapsed = true;
        this.currentQuestion = null;
    }

    void start() {
        this.serverRunning = true;

        Thread mainServerThread = new Thread(this::checkForClient);
        mainServerThread.start();
    }
    //192.168.0.113
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

        this.currentQuestion = null;

    }

    private void checkForClient(){
        System.out.println("Démarage de l'écoute sur " + serverSocket.getInetAddress() + ":" + serverSocket.getLocalPort());
        while (this.serverRunning) {
            try {
                Socket client = serverSocket.accept();

                Thread clientHandlerThread = new Thread(() -> handleClient(client));

                clientHandlerThread.start();
            }catch(SocketTimeoutException s) {
                System.out.println("Socket expiré");
            }catch(SocketException e) {
                System.out.println("Écoute intérompu");
            }catch(IOException e) {
                e.printStackTrace();
                break;
            }
        }
    }

    private void pollFinished(){
        this.pollTimeElapsed = true;
        System.out.println("Sondage terminé");
        System.out.println("Le réponses reçu ont été écrite sur le disque");

    }

    public void writeInOutputFile(String str){
        try {
            Files.write(Paths.get(TEXTFILEPATH), str.getBytes(), StandardOpenOption.APPEND);
        }catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void handleClient (Socket socket) {
        try {

            DataOutputStream outputStream = new DataOutputStream(socket.getOutputStream());
            DataInputStream inputStream = new DataInputStream(socket.getInputStream());

            outputStream.writeUTF("Vous êtes connecté au serveur à l'adresse " + socket.getLocalSocketAddress()
                    + " sur le port " + socket.getLocalPort());

            outputStream.writeBoolean(this.pollTimeElapsed);

            if (this.currentQuestion == null) {
                outputStream.writeUTF("Aucune question disponible pour l'instant, veillez réessayer plus tard.");
            } else if (this.pollTimeElapsed) {
                outputStream.writeUTF("Le temps alloué pour répondre est écoulé.");
            } else {
                outputStream.writeUTF("Question : " + this.currentQuestion);

                if (this.pollTimeElapsed) {
                    outputStream.writeUTF("Le temps alloué pour répondre est écoulé.\nVotre réponse ne sera pas prise en compte");
                } else {
                    outputStream.writeUTF("Merci pour votre réponse!");

                    String clientAnswer = "CLIENT -> " + socket.getRemoteSocketAddress().toString() + " Réponse : " + inputStream.readUTF();

                    System.out.println(clientAnswer);

                    // Écrire la réponse dans un Fichier Texte.
                    this.writeInOutputFile("\t" + clientAnswer + "\r\n");
                }
            }
            socket.close();
        }catch(SocketTimeoutException s) {
            System.out.println("Le socket pour " + socket.getInetAddress().toString() +  " à expiré");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}