using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class dark_combo : MonoBehaviour
{
    public GameObject my_camera;
    public string name_of_show;
    private bool right = false;
    private int attack = 0;

    void dark_attack()
    {
        my_camera.GetComponent<the_begin>().dark_attack(attack, right);
    }
    public void show(int damage, bool side)
    {
        attack = damage;
        right = side;
        GetComponent<Animation>().Play(name_of_show);
    }
    void set_false()
    {
        gameObject.SetActive(false);
    }
}
