using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class show_message : MonoBehaviour
{
    public GameObject place;
    public GameObject message_image;
    public int index;
    public bool combo;

    void OnMouseDown()
    {
        place.GetComponent<index>().slimes[place.GetComponent<index>().i].SetActive(false);
        message_image.SetActive(true);
        message_image.GetComponent<text_of_skills>().set_message(index, combo);       
    }
}
