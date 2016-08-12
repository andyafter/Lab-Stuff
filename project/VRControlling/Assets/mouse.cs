using UnityEngine;
using System.Collections;

public class mouse : MonoBehaviour {
    float distance = 20;
    public GameObject projectile;

    void OnMouseDrag() {
        Vector3 mousePosition = new Vector3(Input.mousePosition.x, Input.mousePosition.y, distance);
        Vector3 objPosition = Camera.main.ScreenToWorldPoint(mousePosition);
        transform.position = objPosition;
    }

        // Update is called once per frame
        void fixedUpdate () {
     
    }
}
