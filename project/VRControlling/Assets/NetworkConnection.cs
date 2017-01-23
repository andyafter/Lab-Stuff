using UnityEngine;
using System.Collections;
using SharpConnect;

public class NetworkConnection : MonoBehaviour {
    public Connector test=new Connector();
    string lastMessage;
    public Transform PlayerCoord;
 
    void Start () 
    {
        Debug.Log(test.fnConnectResult("127.0.0.1",12345,System.Environment.MachineName));
        if (test.res !="")
        {
            Debug.Log(test.res);
        }
    }
    void Update () 
    {
        if(test.strMessage!=""){
            print(test.strMessage);
            // this is kinda dirty. It helps clears all the message from the server
            // every time there is an update
            test.strMessage = "";
        }
    }
 
    void OnApplicationQuit (){
        try{test.fnDisconnect();}
        catch{
            print("disconnect error catched");
        }
    }
}
