using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class click_sound : MonoBehaviour
{
    void OnMouseDown()
    {
        GetComponent<AudioSource>().Play();
    }
}
