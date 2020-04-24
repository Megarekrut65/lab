using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class water_combo : MonoBehaviour
{
    public GameObject the_slime;
    public string name_of_animation;
    private int hp = 0;
    public void show(int damage)
    {
        GetComponent<Animation>().Play(name_of_animation);
        hp = damage;
    }
    void health()
    {
        the_slime.GetComponent<slime>().getting_hp(hp);
        gameObject.SetActive(false);
    }
}
