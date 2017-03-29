package com.turbogiggle;

import com.sun.xml.internal.xsom.impl.scd.Iterators;

import java.lang.reflect.Array;

public class Server {
    private String ipAddress;
    private String port;
    private Double pollTimeOut;

    private String currentQuestion;
    private String[] answers;

    public Server(String ip, String port, Double pollTimeOut){
        this.ipAddress = ip;
        this.port = port;
        this.pollTimeOut = pollTimeOut;
    }

    public void ask(String question) {

    }

    private Integer send(String message){
        return 0;
    }

    private Integer recv(){
        return 0;
    }


}
