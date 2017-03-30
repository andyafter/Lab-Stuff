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
    private Vector3 locator = new Vector3(160f, 0f, 240f);

    private float scale = 0.05F;

    public Transform hand;
    private Vector3 handPos;
	// Use this for initialization
	void Start () {
        handPos = new Vector3(0f, 0f, 0f);
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
        // change y to minus 10 instead of plus
        hand.position = new Vector3(160f - handPos.x, handPos.z + 10f, 240f + handPos.y);   
	}

	void gesEngineClient(){
		Byte[] data = new Byte[1024];
		String responseData = String.Empty;
		while(clientListen){
			Int32 bytes = stream.Read(data, 0, data.Length);
			responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
            string[] res = responseData.Split(' ');
            handPos.x = float.Parse(res[0]) * scale;
            handPos.y = -float.Parse(res[1]) * scale;
            handPos.z = float.Parse(res[2]) * scale;
            //handPos = new Vector3(float.Parse(res[0]), -float.Parse(res[1]), float.Parse(res[2])) * scale;
		}

	}

	void OnApplicationQuit(){
		clientListen = false;
		stream.Close ();
		client.Close ();
	}

}
