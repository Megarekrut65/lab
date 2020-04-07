using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class press_close : MonoBehaviour
{
    void OnMouseDown()
    {
        gameObject.SetActive(false);
    }
}
