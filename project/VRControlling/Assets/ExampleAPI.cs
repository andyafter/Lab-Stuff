using UnityEngine;
using System.Collections;

public class ExampleAPI : MonoBehaviour {

	// Use this for initialization
    public float speed = 2.0f;
    public GameObject sphereObj = null;
	void Start () {
        Debug.Log("Name: " + this.gameObject.name);
        this.gameObject.transform.position = new Vector3(0, 0, 0);
        //this.gameObject.GetComponent<Renderer>().material.color = Color.green;
        this.gameObject.GetComponent<Renderer>().material.color =
            sphereObj.GetComponent<Renderer>().material.color;
    }
	
	// Update is called once per frame
	void Update () {
        this.gameObject.transform.Translate(Vector3.up * Time.deltaTime * speed);
	}
}
