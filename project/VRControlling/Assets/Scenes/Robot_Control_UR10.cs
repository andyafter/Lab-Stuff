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

    // configurations for communications with UDP
    // because we cannot afford or even bother to buy the DTrack software settings for n
    // unity:)
    public Thread receiveThread = null;
    static IPEndPoint ep = new IPEndPoint(IPAddress.Any, 0);
    static UdpClient udpclient = new UdpClient(6699);
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
    public float scale_speed = 0.02f;

    public Vector3 target = new Vector3(300, 400, 500);

    // Use this for initialization
	void Start () {
        print(Vector3.Distance(UR10_Joint_2.position, UR10_Joint_4.position));
        print(UR10_Joint_1.position);
        print(UR10_Joint_2.position);
        print(UR10_Joint_3.position);
        print(UR10_Joint_4.position);
        print(UR10_Joint_5.position);
        print(UR10_Joint_6.position);
        print(UR10_Joint_7.position);
        print(UR10_Joint_8.position);
        print(UR10_Joint_9.position);
	}
	
	// Update is called once per frame
	void Update () {

        //UR10_Joint_1.Rotate(0, joint_1_velocity * del_t, 0);
        //UR10_Joint_2.Rotate(0, 0, joint_1_velocity * del_t);
        UR10_Joint_1.Rotate( 0,  joint_1_velocity * del_t ,0);

        Debug.Log("I am at place A");
        if ((Math.Abs(joint_delta_a) != 0) || (Math.Abs(joint_delta_b) != 0) || (Math.Abs(joint_delta_c) != 0)
        || (Math.Abs(joint_delta_d) != 0) || (Math.Abs(joint_delta_e) != 0)|| (Math.Abs(joint_delta_f) != 0)
            || (Math.Abs(joint_delta_g) != 0))//absolute != 0
        {
            Debug.Log("I am at place C");
            if (!is_indicator_set)
            {
                Indicator_sphere.position = new Vector3(pos_x, pos_y, pos_z);
                is_indicator_set = true;
            }
            if (Math.Abs(joint_delta_a) != 0)
            {
                //sound.PlayOneShot(motor_running_4, 0.35f);
                if (joint_delta_a > 0)
                {
                    if (joint_delta_a > joint_1_velocity * del_t)
                    {
                        Debug.Log("I am at place G");
                        UR10_Joint_1.Rotate(0, joint_1_velocity * del_t, 0);
                        joint_delta_a -= joint_1_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_1.Rotate(0, joint_delta_a, 0);
                        joint_delta_a = 0;
                    }
                }
                else
                {
                    if (joint_delta_a < -joint_1_velocity * del_t)
                    {
                        UR10_Joint_1.Rotate(0, -joint_1_velocity * del_t, 0);
                        joint_delta_a += joint_1_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_1.Rotate(0, joint_delta_a, 0);
                        joint_delta_a = 0;
                    }
                }
            }
            else if ((Math.Abs(joint_delta_b) != 0) || (Math.Abs(joint_delta_c) != 0)
            || (Math.Abs(joint_delta_d) != 0))
            {
                ///////////////////joint_b
                //sound.Stop();
                //sound.PlayOneShot(motor_running_1, 0.35f);
                if (joint_delta_b > 0)
                {
                    if (joint_delta_b > joint_2_velocity * del_t)
                    {
                        UR10_Joint_2.Rotate(0, 0, -joint_2_velocity * del_t);
                        joint_delta_b -= joint_2_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_2.Rotate(0, 0, -joint_delta_b);
                        joint_delta_b = 0;
                    }
                }
                else
                {
                    if (joint_delta_b < -joint_2_velocity * del_t)
                    {
                        UR10_Joint_2.Rotate(0, 0, joint_2_velocity * del_t);
                        joint_delta_b += joint_2_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_2.Rotate(0, 0, -joint_delta_b);
                        joint_delta_b = 0;
                    }
                }
                /////////////////////////////joint_c
                if (joint_delta_c > 0)
                {
                    if (joint_delta_c > joint_3_velocity * del_t)
                    {
                        UR10_Joint_3.Rotate(0, joint_3_velocity * del_t, 0);
                        joint_delta_c -= joint_3_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_3.Rotate(0, joint_delta_c, 0);
                        joint_delta_c = 0;
                    }
                }
                else
                {
                    if (joint_delta_c < -joint_3_velocity * del_t)
                    {
                        UR10_Joint_3.Rotate(0, -joint_3_velocity * del_t, 0);
                        joint_delta_c += joint_3_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_3.Rotate(0, joint_delta_c, 0);
                        joint_delta_c = 0;
                    }
                }
                /////////////////////////////joint_d
                if (joint_delta_d > 0)
                {
                    if (joint_delta_d > joint_4_velocity * del_t)
                    {
                        UR10_Joint_5.Rotate(0, 0, -joint_4_velocity * del_t);
                        joint_delta_d -= joint_4_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_5.Rotate(0, 0, -joint_delta_d);
                        joint_delta_d = 0;
                    }
                }
                else
                {
                    if (joint_delta_d < -joint_4_velocity * del_t)
                    {
                        UR10_Joint_5.Rotate(0, 0, joint_4_velocity * del_t);
                        joint_delta_d += joint_4_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_5.Rotate(0, 0, -joint_delta_d);
                        joint_delta_d = 0;
                    }
                }
                /////////////////////////////////////////////////////////////////
            }
            else if ((Math.Abs(joint_delta_e) != 0))
            {
                //sound.Stop();
                //sound.PlayOneShot(motor_running_3, 0.35f);
                if (joint_delta_e > 0)
                {
                    if (joint_delta_e > joint_5_velocity * del_t)
                    {
                        UR10_Joint_6.Rotate(0, joint_5_velocity * del_t, 0);
                        joint_delta_e -= joint_5_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_6.Rotate(0, joint_delta_e, 0);
                        joint_delta_e = 0;
                    }
                }
                else
                {
                    if (joint_delta_e < -joint_5_velocity * del_t)
                    {
                        UR10_Joint_6.Rotate(0, -joint_5_velocity * del_t, 0);
                        joint_delta_e += joint_5_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_6.Rotate(0, joint_delta_e, 0);
                        joint_delta_e = 0;
                    }
                }
            }
            else if ((Math.Abs(joint_delta_f) != 0))
            {
                //sound.Stop();
                //sound.PlayOneShot(motor_running_3, 0.35f);
                if (joint_delta_f > 0)
                {
                    if (joint_delta_f > joint_6_velocity * del_t)
                    {
                        UR10_Joint_8.Rotate(0, 0, -joint_6_velocity * del_t);
                        joint_delta_f -= joint_6_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_8.Rotate(0, 0, -joint_delta_f);
                        joint_delta_f = 0;
                    }
                }
                else
                {
                    if (joint_delta_f < -joint_6_velocity * del_t)
                    {
                        UR10_Joint_8.Rotate(0, 0, joint_6_velocity * del_t);
                        joint_delta_f += joint_6_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_8.Rotate(0, 0, -joint_delta_f);
                        joint_delta_f = 0;
                    }
                }
            }
            else if ((Math.Abs(joint_delta_g) != 0))
            {
                //sound.Stop();
                //sound.PlayOneShot(motor_running_3, 0.35f);
                if (joint_delta_g > 0)
                {
                    if (joint_delta_g > joint_7_velocity * del_t)
                    {
                        UR10_Joint_9.Rotate(0, joint_7_velocity * del_t, 0);
                        joint_delta_g -= joint_7_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_9.Rotate(0, joint_delta_g, 0);
                        joint_delta_g = 0;
                    }
                }
                else
                {
                    if (joint_delta_g < -joint_7_velocity * del_t)
                    {
                        UR10_Joint_9.Rotate(0, -joint_7_velocity * del_t, 0);
                        joint_delta_g += joint_7_velocity * del_t;
                    }
                    else
                    {
                        UR10_Joint_9.Rotate(0, joint_delta_g, 0);
                        joint_delta_g = 0;
                    }
                }
            }
        }
        else if ((!is_end) && is_begin)
        {
            //sound.Stop();
            //Debug.Log("At the target position!");
            is_end = true;
            is_begin = false;
            //send_message = true;
        }
        
        Indicator_sphere.position = new Vector3(pos_x, pos_y, pos_z);
        

	}
}
