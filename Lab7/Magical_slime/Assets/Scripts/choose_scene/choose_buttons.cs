using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class choose_buttons : MonoBehaviour
{  
    public bool direction = true;
    public GameObject index_object;   
    void OnMouseDown()
    {
        if(direction)
        {
            index_object.GetComponent<index>().right();
        }
        else
        {
            index_object.GetComponent<index>().left();
        }
    }
}
