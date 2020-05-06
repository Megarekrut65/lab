using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class multiplayer : MonoBehaviour
{
    public GameObject my_camera;
    public GameObject message;
    public GameObject backgraund;

    void OnMouseDown()
    {
        backgraund.GetComponent<AudioSource>().Play();
        my_camera.GetComponent<start_mode>().set_active_items(false);
        message.SetActive(true);
    }
}
