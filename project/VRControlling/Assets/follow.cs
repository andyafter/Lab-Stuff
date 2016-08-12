using UnityEngine;
using System.Collections;

public class follow : MonoBehaviour {
    public GameObject boss;
   
    // Use this for initialization

    void OnCollisionEnter(Collision col) {
        transform.position = boss.transform.position;
    }
    void Start () {
	    
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
