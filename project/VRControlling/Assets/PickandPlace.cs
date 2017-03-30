﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PickandPlace : MonoBehaviour {

	public Transform source;
	public Transform target;
	public Transform hand;
	public Transform cube;
	public Transform sphere;
	public Transform cylinder;

	// Note down the initial positions
	public Vector3 cubeOri;
	public Vector3 sphereOri;
	public Vector3 cylinderOri;

	// for the pick and place logic
	private int status;     // 1 is picked and 0 is empty handed
	private Transform currentObject;
	private int current = 0;

	// for glove signal, yes it's an http request
	private string url = "http://127.0.0.1:5000/";	

	void Start () {
		cubeOri  = cube.position;
		sphereOri = sphere.position;
		cylinderOri = cylinder.position;
	}
	
	// Update is called once per frame
	void Update () {
		float dis_source = Vector3.Distance(target.position, source.position);
		print(dis_source);

		if (status == 1) {
			currentObject.position = new Vector3 (hand.position.x, hand.position.y - 0.05f, hand.position.z);

			float disHandTarget = Vector3.Distance(target.position, hand.position);
			if(disHandTarget<1){
				// put it down
				//WWW www = new WWW(url);
				if (current == 0) {
					currentObject.position = new Vector3 (cubeOri.x, cubeOri.y, cubeOri.z + 2.0f);
				}else if (current == 1) {
					currentObject.position = new Vector3 (sphereOri.x, sphereOri.y, sphereOri.z + 2.0f);
				}else if (current == 2) {
					currentObject.position = new Vector3 (cylinderOri.x, cylinderOri.y, cylinderOri.z + 2.0f);
				}
				current += 1;
				current %= 3;    // since there are 3 objects so far	
				status = 0;
			}
		}
		else{
			float disHandSource = Vector3.Distance(source.position, hand.position);
			if(disHandSource<1){
				// pick
				//WWW www = new WWW(url);
				status = 1;
				if (current == 0) {
					currentObject = cube;
					print ("Changed to cube");
				} else if (current == 1) {
					currentObject = cylinder;
					print ("Changed to cylinder");
				} else if (current == 2) {
					currentObject = sphere;
					print ("Changed to sphere");
				} else {
					Debug.Log("Wrong number of current object");
				}
			}
		}
	}
}