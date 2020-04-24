using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class close_message_multi : MonoBehaviour
{
    public GameObject my_camera;

    void OnMouseDown()
    {
        gameObject.SetActive(false);
        my_camera.GetComponent<start_mode>().set_active_items(true);
    }
}
