using UnityEngine;
using System.Collections;

public class child : MonoBehaviour {
    public GameObject player;
    public Transform newParent;
	// Use this for initialization
	void Start () {
	
	}
    void OnCollisionEnter()
    {
        //Sets "newParent" as the new parent of the player GameObject.
        player.transform.SetParent(newParent);

    }
    // Update is called once per frame
    void Update()
    {

    }
  
}
