using UnityEngine;
using System.Collections;
using System.Net;
using System.Threading;
using System.IO;
using System;
using System.Net.Sockets;
using System.Text;


public class Client : MonoBehaviour {

	private string ip = "169.254.9.189";
	private int port = 1234;
	private Thread clientThread;
	private TcpClient client;
	private string message = "Hello";
	private NetworkStream stream;
	private bool clientListen = true;   // closes client listeing loop in another thread

	void OnGUI(){
		// if (Network.peerType == NetworkPeerType.Disconnected) {
		// 	if (GUI.Button (new Rect (100, 100, 100, 25), "Start Client")) {
		// 		Network.Connect (ip, port);	
		// 	}
		// } else {
		// 	if (Network.peerType == NetworkPeerType.Client) {
		// 		GUI.Label (new Rect(100,100,100,25), "Client");
		// 		if (GUI.Button (new Rect (100, 125, 100, 25), "Logout")) {
		// 			Network.Disconnect (250);
		// 		}
		// 	}
		// }
	}
	// Use this for initialization
	void Start () {
		client = new TcpClient (ip, port);
		Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);
		stream = client.GetStream();
		stream.Write(data, 0, data.Length);
		Console.WriteLine("Sent: {0}", message); 
		clientThread = new Thread (gesEngineClient);
		clientThread.Start();
	}
	
	// Update is called once per frame
	void Update () {
		print ("inside update");
	}

	void gesEngineClient(){
		Byte[] data = new Byte[1024];
		String responseData = String.Empty;
		while(clientListen){
			Int32 bytes = stream.Read(data, 0, data.Length);
			responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
			print(responseData);
			print("Here ");
		}

	}

	void OnApplicationQuit(){
		clientListen = false;
		stream.Close ();
		client.Close ();
	}

}
