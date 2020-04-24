using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class start_mode : MonoBehaviour
{
    public const int number_of_items = 6;
    public GameObject left_slime;
    public GameObject right_slime;
    public GameObject[] items;
    public GameObject off_mode;
    private GameObject[] slimes;
    private int number_of_slimes = 7;
    public string left_anim;
    public string right_anim;

    public void set_active_items(bool active)
    {        
        for (int i = 0; i < number_of_items; i++)
        {
            items[i].SetActive(active);
        }
        if(active)
        {
            left_slime.GetComponent<Animation>().Play(left_anim);
            right_slime.GetComponent<Animation>().Play(right_anim);
        }
    }
    public void show_slimes(bool[] array_slimes)
    {
        set_active_items(false);
        for (int i = 0; i < number_of_slimes; i++)
        {
            slimes[i].SetActive(array_slimes[i]);
            slimes[i].GetComponent<set_slime>().index = i;
        }
        off_mode.SetActive(true);
    }
    public void set_active_slimes(bool active)
    {
        for (int i = 0; i < number_of_slimes; i++)
        {
            slimes[i].SetActive(active);
        }
    }
    void Start()
    {
        slimes = GameObject.FindGameObjectsWithTag("left_slime");
        items = GameObject.FindGameObjectsWithTag("items");
        set_active_slimes(false);
        off_mode.SetActive(false);
        left_slime.GetComponent<Animation>().Play(left_anim);
        right_slime.GetComponent<Animation>().Play(right_anim);
        StartCoroutine("start_effects");
    }
    IEnumerator start_effects()
    {
        while (true)
        {
            yield return new WaitForSeconds(0.5f);
            int rand_left = Random.Range(0, 6);
            left_slime.GetComponent<SpriteRenderer>().sprite = slimes[rand_left].GetComponent<SpriteRenderer>().sprite;
            yield return new WaitForSeconds(0.5f);
            int rand_right = Random.Range(0, 6);
            right_slime.GetComponent<SpriteRenderer>().sprite = slimes[rand_right].GetComponent<SpriteRenderer>().sprite;
        }       
    }
}
