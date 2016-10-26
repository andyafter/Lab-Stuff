using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System;
//using System.Ling;
using System.IO;
//using System.IO.Pipes;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

public class Robot_Control_UR10 : MonoBehaviour {

    public Transform UR10_Base;
    public Transform UR10_Joint_1;
    public Transform UR10_Joint_2;
    public Transform UR10_Joint_3;
    public Transform UR10_Joint_4;//redundant
    public Transform UR10_Joint_5;
    public Transform UR10_Joint_6;
    public Transform UR10_Joint_7;//redundant
    public Transform UR10_Joint_8;
    public Transform UR10_Joint_9;
    public Transform UR10_Joint_EE;
    public Transform Indicator_sphere;
    public Transform MainCamera;

    public float cam_rot_x = 0.0f;
    public float cam_rot_y = 0.0f;
    public float cam_rot_z = 0.0f;
    public float cam_pos_x = 0.0f;
    public float cam_pos_y = 0.0f;
    public float cam_pos_z = 0.0f;

    public float joint_1 = 0.0f;
    public float joint_2 = 0.0f;
    public float joint_3 = 0.0f;
    public float joint_4 = 0.0f;
    public float joint_5 = 0.0f;
    public float joint_6 = 0.0f;
    public float joint_7 = 0.0f;
    public float joint_8 = 0.0f;
    public float joint_9 = 0.0f;
    public float joint_ee = 0.0f;

    public float joint_1_velocity = 7.0f;
    public float joint_2_velocity = 7.0f;
    public float joint_3_velocity = 7.0f;
    public float joint_4_velocity = 7.0f;
    public float joint_5_velocity = 7.0f;
    public float joint_6_velocity = 7.0f;
    public float joint_7_velocity = 7.0f;
    public float joint_8_velocity = 7.0f;
    public float joint_9_velocity = 7.0f;
    public float joint_ee_velocity = 7.0f;

    public Thread receiveThread = null;
    static IPEndPoint ep = new IPEndPoint(IPAddress.Any, 0);
    static UdpClient udpclient = new UdpClient(6600);
    static byte[] receiveBytes = new byte[100];
    static byte[] sendBytes = new byte[100];
    static string sendData = "";
    static string returnData = "";
    static string stringToEdit = "";
    static bool is_begin = false;
    static bool is_end = true;
    static bool is_indicator_set = false;
    static bool send_message = false;
    /// <summary>
    /// the above are the newly added socket stuffs
    /// </summary>
    public float robotBaseSliderValue = 0.0f;
    public float robotUpperArmSliderValue = 0.0f;
    //public float joint_3 = 0.0f;
    //public float joint_4 = 0.0f;
    //public float joint_5 = 0.0f;
    //public float joint_6 = 0.0f;
    public float joint_a = 0.0f;
    public float joint_b = 0.0f;
    public float joint_c = 0.0f;
    public float joint_d = 0.0f;
    public float joint_e = 0.0f;
    public float joint_f = 0.0f;
    public float joint_g = 0.0f;
    public float joint_a0 = 0.0f;
    public float joint_b0 = 0.0f;
    public float joint_c0 = 0.0f;
    public float joint_d0 = 0.0f;
    public float joint_e0 = 0.0f;
    public float joint_f0 = 0.0f;
    public float joint_g0 = 0.0f;
    public float joint_delta_a = 0.0f;
    public float joint_delta_b = 0.0f;
    public float joint_delta_c = 0.0f;
    public float joint_delta_d = 0.0f;
    public float joint_delta_e = 0.0f;
    public float joint_delta_f = 0.0f;
    public float joint_delta_g = 0.0f;
    public float pos_x = 0.0f;
    public float pos_y = 0.0f;
    public float pos_z = 0.0f;
    public string str_1 = "";
    public string str_2 = "";
    public string str_3 = "";
    public string str_4 = "";
    public string str_5 = "";
    public string str_6 = "";
    public string str_7 = "";
    public string str_8 = "";
    public string str_9 = "";
    public string str_10 = "";
    public string str_11 = "";
    public string str_12 = "";
    public string str_13 = "";
    public string str_14 = "";
    public string str_15 = "";
    public string str_16 = "";
    public float baseTurnRate = 30;
    public float upperArmTurnRate = 24.0f;
    public float SpeedJoint_3 = 24.0f;
    public float SpeedJoint_4 = 24.0f;
    public float SpeedJoint_5 = 24.0f;
    public float SpeedJoint_6 = 24.0f;
    //public float del_t = 5.0f;
    public float del_t = 0.2f;

    public int JMF1,JMF2,JMF3,JMF4, JMF5,JMF6,JMF7= 0;  // how many frames you want the joint to move(joint move frames)
    private bool rotating1 = true;
    // Use this for initialization
	void Start () {
        //receiveThread = new Thread(ReceiveData);
        //receiveThread.IsBackground = true;
        //receiveThread.Start();
            JMF1 = 11;
            JMF2 = 15;
            JMF3 = 50;
            JMF5 = 8;
	}
	
	// Update is called once per frame
	void Update () {
        //UR10_Joint_1.Rotate(0, joint_1_velocity * del_t, 0);
        //UR10_Joint_2.Rotate(0, 0, joint_1_velocity * del_t);
        //UR10_Joint_3.Rotate(0, joint_1_velocity * del_t, 0);
        //UR10_Joint_4.Rotate(0, joint_1_velocity * del_t, 0);//redundant
        //UR10_Joint_5.Rotate(0, 0, joint_1_velocity * del_t);
        //UR10_Joint_6.Rotate(0, joint_1_velocity * del_t, 0);
        //UR10_Joint_7.Rotate(0, joint_1_velocity * del_t, 0);//redundant
        //UR10_Joint_8.Rotate(0, 0, joint_1_velocity * del_t);
        //UR10_Joint_9.Rotate(0, joint_1_velocity * del_t, 0);
        //UR10_Joint_EE.Rotate(0, 0, joint_1_velocity * del_t);
        //MainCamera.Rotate(cam_rot_x, cam_rot_y, cam_rot_z);
        Vector3 rot = new Vector3(cam_rot_x, cam_rot_y, cam_rot_z);
        //MainCamera.eulerAngles = rot;
        //rot.Set(cam_pos_x, cam_pos_z, -cam_pos_y);
        //MainCamera.position = rot;
        del_t *= 0.99f;
        if(Indicator_sphere.position.y>-1){
            Debug.Log("uau");
        }

        if(JMF1>0){
            JMF1 -= 1;
            UR10_Joint_1.Rotate(0, joint_1_velocity * del_t, 0);
        }
        if(JMF2>0){
            JMF2 -= 1;
            UR10_Joint_2.Rotate(0, 0, -joint_1_velocity * del_t);
        }
        if(JMF3>0){
            JMF3 -= 1;
            UR10_Joint_3.Rotate(0, joint_1_velocity * del_t, 0);
        }
        if(JMF4>0){
            JMF4 -= 1;
            UR10_Joint_4.Rotate(0, joint_1_velocity * del_t, 0);
        }
        if(JMF5>0){
            JMF5 -= 1;
            UR10_Joint_5.Rotate(0, 0, joint_1_velocity * del_t);
        }
        if(JMF6>0){
            JMF6 -= 1;
            UR10_Joint_6.Rotate(0, joint_1_velocity * del_t, 0);
        }
        if(JMF7>0){
            JMF7 -= 1;
            UR10_Joint_7.Rotate(0, joint_1_velocity * del_t, 0);
        }
        
        
        Indicator_sphere.position = new Vector3(pos_x, pos_y, pos_z);
        

	}

    void ReceiveData()
    {
        //returnData = "";
        char temp = '0'; char sign = '0';
        Debug.Log("I am at place B");
        while (true)
        {

            Debug.Log("I am here!!!");

            receiveBytes = udpclient.Receive(ref ep);
            
            returnData = Encoding.ASCII.GetString(receiveBytes);
            Debug.Log(returnData);
            //if(send_message)
            //{
            //    sendData = "Ready";
            //    sendBytes = Encoding.ASCII.GetBytes(sendData);
            //    udpclient.Send(sendBytes, sendBytes.Length, ep);
            //}
            //else
            //{
            //    sendData = "Unready";
            //    sendBytes = Encoding.ASCII.GetBytes(sendData);
            //    udpclient.Send(sendBytes, sendBytes.Length, ep);
            //}

            if (returnData != "")
            {
                Debug.Log(returnData);
                str_1 = null; str_2 = null; str_3 = null; str_4 = null;
                str_5 = null; str_6 = null; str_13 = null;
                str_7 = null; str_8 = null; str_9 = null;
                str_10 = null; str_11 = null; str_12 = null;
                str_14 = null; str_15 = null; str_16 = null;

                for (int i = 0; i < returnData.Length; i++)
                {
                    temp = returnData[i];
                    if (temp == 'A')
                    {
                        sign = 'A';
                    }
                    else if (temp == 'B')
                    {
                        sign = 'B';
                    }
                    else if (temp == 'C')
                    {
                        sign = 'C';
                    }
                    else if (temp == 'D')
                    {
                        sign = 'D';
                    }
                    else if (temp == 'E')
                    {
                        sign = 'E';
                    }
                    else if (temp == 'F')
                    {
                        sign = 'F';
                    }
                    else if (temp == 'G')
                    {
                        sign = 'G';
                    }
                    else if (temp == 'H')
                    {
                        sign = 'H';
                    }
                    else if (temp == 'I')
                    {
                        sign = 'I';
                    }
                    else if (temp == 'J')
                    {
                        sign = 'J';
                    }
                    else if (temp == 'U')
                    {
                        sign = 'U';
                    }
                    else if (temp == 'V')
                    {
                        sign = 'V';
                    }
                    else if (temp == 'N')
                    {
                        sign = 'N';
                        Debug.Log("I am at place D");
                        break;
                    }
                    else if (temp == 'O')
                    {
                        sign = 'O';
                        Debug.Log("I am at place D");
                        break;
                    }
                    else if (temp == 'P')
                    {
                        sign = 'P';
                        Debug.Log("I am at place D");
                        break;
                    }
                    else if (temp == 'K')
                    {
                        sign = 'K';
                        //Debug.Log("I am at place D");
                        break;
                    }
                    else if (temp == 'W')
                    {
                        sign = 'W';
                    }
                    else if (temp == 'X')
                    {
                        sign = 'X';
                    }
                    else if (temp == 'Y')
                    {
                        sign = 'Y';
                    }
                    else if (temp == 'Z')
                    {
                        sign = 'Z';
                    }
                    else
                    {
                        if (sign == 'A')
                        {
                            str_1 += temp;
                        }
                        else if (sign == 'B')
                        {
                            str_2 += temp;
                        }
                        else if (sign == 'C')
                        {
                            str_3 += temp;
                        }
                        else if (sign == 'D')
                        {
                            str_4 += temp;
                        }
                        else if (sign == 'E')
                        {
                            str_5 += temp;
                        }
                        else if (sign == 'F')
                        {
                            str_6 += temp;
                        }
                        else if (sign == 'G')
                        {
                            str_7 += temp;
                        }
                        else if (sign == 'U')
                        {
                            str_8 += temp;
                        }
                        else if (sign == 'V')
                        {
                            str_9 += temp;
                        }
                        else if (sign == 'W')
                        {
                            str_10 += temp;
                        }
                        else if (sign == 'X')
                        {
                            str_11 += temp;
                        }
                        else if (sign == 'Y')
                        {
                            str_12 += temp;
                        }
                        else if (sign == 'Z')
                        {
                            str_13 += temp;
                        }
                        else if (sign == 'H')
                        {
                            str_14 += temp;
                        }
                        else if (sign == 'I')
                        {
                            str_15 += temp;
                        }
                        else if (sign == 'J')
                        {
                            str_16 += temp;
                        }
                    }
                }
                //Debug.Log(str_1);
                //Debug.Log(str_2);
                //Debug.Log(str_3);
                //Debug.Log(str_4);
                //Debug.Log(str_5);
                //Debug.Log(str_6);
                //Debug.Log(str_10);
                //Debug.Log(str_11);
                //Debug.Log(str_12);
                Debug.Log("I am at Place E");
                if (sign == 'N')
                {
                    Debug.Log("I am at Place F");
                    joint_a = float.Parse(str_1);
                    joint_b = float.Parse(str_2);
                    //joint_b = -joint_b;
                    joint_c = float.Parse(str_3);
                    joint_d = float.Parse(str_4);
                    //joint_d = -joint_d;
                    joint_e = float.Parse(str_5);
                    joint_f = float.Parse(str_6);
                    //joint_f = -joint_f;
                    joint_g = float.Parse(str_7);
                    Debug.Log(str_1);
                    Debug.Log(str_2);
                    Debug.Log(str_3);
                    Debug.Log(str_4);
                    Debug.Log(str_5);
                    Debug.Log(str_6);
                    Debug.Log(str_7);
                    
                    

                    joint_delta_a = joint_a - joint_a0; joint_delta_b = joint_b - joint_b0; joint_delta_c = joint_c - joint_c0;
                    joint_delta_d = joint_d - joint_d0; joint_delta_e = joint_e - joint_e0; joint_delta_f = joint_f - joint_f0;
                    joint_delta_g = joint_g - joint_g0;

                    joint_a0 = joint_a; joint_b0 = joint_b; joint_c0 = joint_c; joint_d0 = joint_d;
                    joint_e0 = joint_e; joint_f0 = joint_f; joint_g0 = joint_g;

                    is_begin = true;
                    is_end = false;
                    is_indicator_set = false;
                    //send_message = false;
                }
                if (sign == 'K')
                {
                    //Debug.Log("I am at Place F");
                    joint_a = float.Parse(str_1);
                    joint_b = float.Parse(str_2);
                    //joint_b = -joint_b;
                    joint_c = float.Parse(str_3);
                    joint_d = float.Parse(str_4);
                    //joint_d = -joint_d;
                    joint_e = float.Parse(str_5);
                    joint_f = float.Parse(str_6);
                    //joint_f = -joint_f;
                    joint_g = float.Parse(str_7);
                    //Debug.Log(str_1);
                    //Debug.Log(str_2);
                    //Debug.Log(str_3);
                    //Debug.Log(str_4);
                    //Debug.Log(str_5);
                    //Debug.Log(str_6);
                    //Debug.Log(str_7);

                    joint_delta_a = joint_a - joint_a0; joint_delta_b = joint_b - joint_b0; joint_delta_c = joint_c - joint_c0;
                    joint_delta_d = joint_d - joint_d0; joint_delta_e = joint_e - joint_e0; joint_delta_f = joint_f - joint_f0;
                    joint_delta_g = joint_g - joint_g0;

                    joint_a0 = joint_a; joint_b0 = joint_b; joint_c0 = joint_c; joint_d0 = joint_d;
                    joint_e0 = joint_e; joint_f0 = joint_f; joint_g0 = joint_g;

                    is_begin = true;
                    is_end = false;
                    is_indicator_set = false;
                    //send_message = false;
                }
                else if (sign == 'L')
                {
                    pos_x = float.Parse(str_10);
                    pos_x = pos_x / 10.0f;
                    pos_y = float.Parse(str_11);
                    pos_y = pos_y / 10.0f;
                    pos_z = float.Parse(str_12);
                    pos_z = -1 * pos_z / 10.0f;
                }
                else if (sign == 'O')
                {
                    Debug.Log("Seems OK!");
                    cam_rot_x = float.Parse(str_8);
                    cam_rot_y = float.Parse(str_9);
                    cam_rot_z = float.Parse(str_10);
                    cam_pos_x = float.Parse(str_11);
                    cam_pos_y = float.Parse(str_12);
                    cam_pos_z = float.Parse(str_13);

                    
                        pos_x = float.Parse(str_14);
                        //pos_x = pos_x / 10.0f;
                        pos_y = float.Parse(str_16);
                        //pos_y = pos_y / 10.0f;
                        pos_z = -1 * float.Parse(str_15);
                        //pos_z = -1 * pos_z / 10.0f;
                    
                }
                //else if (sign == 'P')
                //{
                    
                //}



            }
            //joint_4 = float.Parse(returnData);
        }

    }
    void OnApplicationQuit()
    {
        stopThread();
    }

    private void stopThread()
    {
        if (receiveThread.IsAlive)
        {
            receiveThread.Abort();
        }
        udpclient.Close();
    }
}
