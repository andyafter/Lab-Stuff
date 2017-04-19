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
    private Vector3 urBase;
    private Vector3 handBase;

    // game objects 
    public Transform endEffector;

    void Start () {
        urBase = new Vector3(1.0f, -0.161f, 0f);
        handBase = new Vector3(158.0f, 8.0f, 233.0f);
        message = "movej(p[1.0, -0.16, 0, 0.5, 3, 0.015], a = 1.3962634015954636, v = 0.3071975511965976)\n";
        client = new TcpClient(ip, port);
        stream = client.GetStream();
        clientThread = new Thread(commandAgent);
        sendCommand = true;
        clientThread.Start();
    }
	
	void Update () {
        ++tickCounter;
        if(tickCounter%10 == 0)
        {
            Vector3 urRefresh = new Vector3(0f, 0f, 0f);
            urRefresh[0] = urBase[0] + (handBase[2] - endEffector.position.z) / 100f;
            urRefresh[1] = urBase[1] + (-handBase[0] + endEffector.position.x) / 100f;
            urRefresh[2] = urBase[2] + (-handBase[1] + endEffector.position.y) / 100f;
            // here the conversion of x, y, z should be written
            message = "movep(p[";
            message += Convert.ToString(urRefresh[0]);
            message += ",";
            message += Convert.ToString(urRefresh[1]);
            message += ",";
            message += Convert.ToString(urRefresh[2]);
            message += ", 0.5, 3, 0.015], a = 1.3962634015954636, v = 0.3071975511965976, r = 0.1)\n";
            print(message);
            sendCommand = true;
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
