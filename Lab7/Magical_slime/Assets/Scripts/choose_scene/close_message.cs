using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class close_message : MonoBehaviour
{
    public GameObject place;

    void OnMouseDown()
    {
        place.GetComponent<index>().slimes[place.GetComponent<index>().i].SetActive(true);
        gameObject.SetActive(false);
    }
}
