using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Threading;
using System.IO;
using System;
using System.Net.Sockets;
using System.Text;

public class URReal : MonoBehaviour {

    private string ip = "172.16.205.134";
    private int port = 30002;
    private Thread clientThread;
    private TcpClient client;
    private string message = "Hello";
    private NetworkStream stream;
    private bool clientListen = true;   // closes client listeing loop in another thread

    private bool sendCommand = false;    // when you want to send a command, set it to true
    private int tickCounter = 0;        // to count time in a game

    void Start () {
        message = "movej(p[0.7, -0.1, 0.1, 0.5, 3, 0.015], a = 1.3962634015954636, v = 0.3071975511965976)\n";
        client = new TcpClient(ip, port);
        stream = client.GetStream();
        clientThread = new Thread(commandAgent);
        sendCommand = true;
        clientThread.Start();
    }
	
	void Update () {
        ++tickCounter;
        if(tickCounter%20 == 0)
        {
            //sendCommand = true;
        }		
	}

    void OnApplicationQuit()
    {
        clientListen = false;
        stream.Close();
        client.Close();
    }

    void commandAgent()
    {
        while (clientListen)
        {
            if (sendCommand)
            {
                Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);
                stream.Write(data, 0, data.Length);
                sendCommand = false;
            }
        }
    }
}
