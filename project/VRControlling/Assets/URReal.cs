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
        handBase = new Vector3();
        message = "movej(p[1.0, -0.16, 0, 0.5, 3, 0.015], a = 1.3962634015954636, v = 0.3071975511965976)\n";
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
            // here the conversion of x, y, z should be written
            message = "movej(p[";
            message += Convert.ToString(Convert.ToInt32(endEffector.position.x));
            message += ",";
            message += Convert.ToString(Convert.ToInt32(endEffector.position.y));
            message += ",";
            message += Convert.ToString(Convert.ToInt32(endEffector.position.z));
            message += ", 0.5, 3, 0.015], a = 1.3962634015954636, v = 0.3071975511965976)\n";
            print(message);
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
