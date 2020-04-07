using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class start_fly : MonoBehaviour
{
    public Animation anim;
    public string plays = "none";
    public string shows = "none";
    private bool is_showed = false;
    void Start()
    {
        anim.Play(shows);
    }
    void if_showed()
    {
        is_showed = true;
    }
    void Update()
    {
        if(is_showed) anim.Play(plays);
    }
}
