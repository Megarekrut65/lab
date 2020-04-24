using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class girl_combo : MonoBehaviour
{
    public GameObject my_camera;
    public Slider hp_slider;
    public string name_of_show;
    public string name_of_fly;
    public string name_of_clear;
    private int hp = 0;
    private int index = 0;
    private bool right = false;

    public void getting_damage(int damage)
    {
        hp -= damage;
        hp_slider.value = hp;
        if (hp <= 0)
        {
            GetComponent<Animation>().Play(name_of_clear);
            my_camera.GetComponent<the_begin>().remove_girl(index, right);
        }
    }
    void fly()
    {
        GetComponent<Animation>().Play(name_of_fly);
    }
    public void show(int index_of_girl, bool side, int damage)
    {
        index = index_of_girl;
        right = side;
        hp = damage;
        hp_slider.value = hp;
        GetComponent<Animation>().Play(name_of_show);
    }
    void set_false()
    {
        gameObject.SetActive(false);
    }
}
