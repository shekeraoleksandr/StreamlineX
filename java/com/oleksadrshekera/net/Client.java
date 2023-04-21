package com.oleksadrshekera.net;

import java.io.IOException;
import java.net.*;
import java.util.Scanner;

public class Client {

    private final int port;
    private final String ipaddress;
    private InetAddress serveraddress = null;
    private DatagramSocket socket;
    private final Scanner scanner = new Scanner(System.in);

    public Client(int port, String ipaddress) {
        this.port = port;
        this.ipaddress = ipaddress;
    }

    public void init() {
        Thread t2 = new Thread(this::receive);
        try {
            socket = new DatagramSocket();
        } catch (SocketException e) {
            throw new RuntimeException(e);
        }

        try {
            serveraddress = InetAddress.getByName(ipaddress);
        } catch (UnknownHostException e) {
            throw new RuntimeException(e);
        }
        t2.start();
    }

    public void connect() {
        init();
        for (; ; ) {
            System.out.print("Enter a message: ");
            String message = scanner.nextLine();
            send(message.getBytes());
        }
    }

    private void receive() {
        byte[] data = new byte[1024];
        DatagramPacket packet = new DatagramPacket(data, data.length);
        try {
            socket.receive(packet);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        process(packet.getData());
    }

    private void send(byte[] data) {
        DatagramPacket packet = new DatagramPacket(data, data.length, serveraddress, port);
        try {
            socket.send(packet);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void process(byte[] data) {
        System.out.println("packet from: " + port + ":" + ipaddress);
        System.out.println("data: " + new String(data));
    }

    public static void main(String[] args) {
        Client client = new Client(8888, "localhost");
        client.connect();
    }
}
