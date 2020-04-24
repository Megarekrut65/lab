using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class the_boll : MonoBehaviour
{
    public GameObject my_camera;
    public GameObject enemy_slime;
    public Animation animatoin;
    public string name_of_animation;
    public int damage = 0;
    private bool double_attack = false;
    private bool right = true;

    public void boll_fly(int attack, bool combo, bool side)
    {
        damage = attack;
        double_attack = combo;
        right = side;
        animatoin.Play(name_of_animation);
    }
    public void hit()
    {
        enemy_slime.GetComponent<slime>().getting_damage(damage);     
    }
    void active_false()
    {
        if (!double_attack)
        {
            my_camera.GetComponent<the_begin>().finish_fight(right);
        }            
    }
}
