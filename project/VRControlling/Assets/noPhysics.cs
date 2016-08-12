using UnityEngine;
using System.Collections;

public class noPhysics : MonoBehaviour {
    public GameObject player;
    public GameObject basket;
    private bool trigger = false;
 //   private bool trigger2 = true;

   
    // Use this for initialization
    public float speed = 100.0f;

    void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        float dist = Vector3.Distance(player.transform.position, transform.position);
        float dist2 = Vector3.Distance(basket.transform.position, transform.position);
        if (dist < 1)
        {
            trigger = true;
        }
        if (dist2 < 3) {
            trigger = false;
            transform.position = Vector3.MoveTowards(transform.position , basket.transform.position , speed);
        }
        if (trigger) {
            transform.position = Vector3.MoveTowards(transform.position, player.transform.position, speed);
        }
    }
}
