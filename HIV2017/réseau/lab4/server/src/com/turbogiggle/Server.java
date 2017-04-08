package com.turbogiggle;
import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

class Server {
    private Integer pollTimeOut;
    private Boolean pollTimeElapsed;
    private Boolean serverRunning;

    private String currentQuestion;
    private List<String> answers;

    private ServerSocket serverSocket;

    Server(String ip, Integer port, Integer pollTimeOut) throws IOException {

        InetAddress addr = InetAddress.getByName(ip);
        this.serverSocket = new ServerSocket(port, 0, addr);

        this.pollTimeOut = pollTimeOut;
        this.pollTimeElapsed = true;

        this.answers = new ArrayList<>();

        this.currentQuestion = null;
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
        System.out.println("Le réponses reçu sont:");
        for (int i = 0; i < this.answers.size(); i++) {
            System.out.println(answers.get(i));
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
                outputStream.writeUTF("Aucune question pour l'instant, veillez réessayer plus tard");
            } else if (this.pollTimeElapsed) {
                outputStream.writeUTF("Le temps alloué pour répondre est écoulé.");
            } else {
                outputStream.writeUTF("Question : " + this.currentQuestion);

                if (this.pollTimeElapsed) {
                    outputStream.writeUTF("Le temps alloué pour répondre est écoulé.\nVotre réponse ne sera pas prise en compte");
                } else {
                    outputStream.writeUTF("Merci pour votre réponse!");
                    this.answers.add("CLIENT -> " + socket.getRemoteSocketAddress().toString() + ":" + socket.getPort() + " Réponse : " + inputStream.readUTF());
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