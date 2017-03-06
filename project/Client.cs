using UnityEngine;
using System.Collections;
using System.Net;
using System.Threading;
using System.IO;
using System;
using System.Net.Sockets;
using System.Text;


public class Client : MonoBehaviour {

	private string ip = "127.0.0.1";
	private int port = 1234;
	private Thread clientThread;
	private TcpClient client;
	private string message = "Hello";
	private NetworkStream stream;
	private bool clientListen = true;   // closes client listeing loop in another thread

    private float scale = 0.01F;

    public Transform hand;
    public Transform bascket;
    private Vector3 handPos;
	// Use this for initialization
	void Start () {
		client = new TcpClient (ip, port);
		Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);
		stream = client.GetStream();
		//stream.Write(data, 0, data.Length);
		//Console.WriteLine("Sent: {0}", message); 
		clientThread = new Thread (gesEngineClient);
		clientThread.Start();
	}
	
	// Update is called once per frame
	void Update () {
		print (handPos);
        hand.position = handPos;
	}

	void gesEngineClient(){
		Byte[] data = new Byte[1024];
		String responseData = String.Empty;
		while(clientListen){
			Int32 bytes = stream.Read(data, 0, data.Length);
			responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
            string[] res = responseData.Split(' ');
            handPos = new Vector3(float.Parse(res[0]), float.Parse(res[1]), float.Parse(res[2])) * scale;
		}

	}

	void OnApplicationQuit(){
		clientListen = false;
		stream.Close ();
		client.Close ();
	}

}
