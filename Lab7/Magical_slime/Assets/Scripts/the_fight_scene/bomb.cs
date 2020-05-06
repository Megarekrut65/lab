using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bomb : MonoBehaviour
{
    public GameObject time_slider;

    public void hit()
    {
        time_slider.GetComponent<time_slider>().hit();
    }
}
