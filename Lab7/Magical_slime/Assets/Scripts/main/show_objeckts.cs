using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class show_objeckts : MonoBehaviour
{
    public Vector2 start_postion;
    public Vector2 end_position;
    public float step;
    private float progress;

    void Start()
    {
        transform.position = start_postion;        
    }
    void FixedUpdate()
    {
        transform.position = Vector2.Lerp(start_postion, end_position, progress);
        progress += step;
    }
}
