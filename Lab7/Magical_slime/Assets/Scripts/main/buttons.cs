﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class buttons : MonoBehaviour
{
    void OnMouseDown()
    {
        GetComponent<AudioSource>().Play();
        transform.localScale = new Vector3 (1.1f, 1.1f, 1.1f);
    }
    void OnMouseUp()
    {
        transform.localScale = new Vector3 (1, 1, 1);
    }
}
