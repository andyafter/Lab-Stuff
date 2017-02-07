using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
using SharpConnect;
using System.Security.Permissions;
using System.Globalization;

public class NetworkConnection : MonoBehaviour {
    public Connector test=new Connector();
    string lastMessage;
    public Transform hand;
 
    void Start () 
    {
        Debug.Log(test.fnConnectResult("127.0.0.1", 1234, System.Environment.MachineName));
        if (test.res !="")
        {
            Debug.Log(test.res);
        }
    }
    void Update () 
    {
        if(test.strMessage!=""){
            string[] data = test.strMessage.Split();
            if(data.Length == 3)
            {
                if (data[0] != "nan")
                {
                    // here you should adjust the hand position
                    print(float.Parse(data[0], CultureInfo.InvariantCulture.NumberFormat));
                }
            }
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
