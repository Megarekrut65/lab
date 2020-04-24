using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class poison_combo : MonoBehaviour
{
    public GameObject enemy_slime;
    public string name_of_show;
    public string name_of_hit;
    public string name_of_end;
    private int attack = 0;
    public bool is_poison = false;
    public void show()
    {
        GetComponent<Animation>().Play(name_of_show);
        is_poison = true;
    }
    public void hitting(int damage)
    {
        attack = damage;
        GetComponent<Animation>().Play(name_of_hit);
    }
    void set_false()
    {
        gameObject.SetActive(false);
    }
    public void clear_poison()
    {
        if (is_poison) return;
        GetComponent<Animation>().Play(name_of_end);
    }
    void hit()
    {
        enemy_slime.GetComponent<slime>().getting_damage(attack);
    }
}
