using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;

public class fight : MonoBehaviour
{
    private const float max_hp = 100;

    public GameObject left_click;
    public GameObject left_text_hp;
    private float left_hp = max_hp;
    private int left_attack = 0;
    public GameObject left_hp_red;
    private float left_width = 1f;
    private Transform left_transfrom;
    private bool left_the_end;

    public GameObject right_click;
    public GameObject right_text_hp;
    private float right_hp = max_hp;
    private int right_attack = 0;
    public GameObject right_hp_red;
    private float right_width = 1f;
    private Transform right_transfrom;
    private bool right_the_end;
   
    void Start()
    {       
        left_text_hp.GetComponent<Text>().text = left_hp.ToString();
        left_transfrom = left_hp_red.GetComponent<Transform>();
        left_the_end = false;
        right_text_hp.GetComponent<Text>().text = right_hp.ToString();
        right_transfrom = right_hp_red.GetComponent<Transform>();
        right_the_end = false;
        gameObject.SetActive(false);
    }
    void OnMouseDown()
    {             
        if (!left_the_end)
        {
            right_attack = right_click.GetComponent<detectclicks>().attack;
            left_hp -= right_attack;
            if (left_hp < 0) left_width = 0;
            else left_width = left_hp / max_hp;
            left_text_hp.GetComponent<Text>().text = left_hp.ToString();
            left_transfrom.localScale = new Vector3(left_width, 1f, 1f);
            if (left_hp <= 0)
            {
                left_text_hp.GetComponent<Text>().text = "The end!";
                left_the_end = true;
            }
            left_click.SetActive(true);
            left_click.GetComponent<detectclicks>().is_click = false;
        }
        if (!right_the_end)
        {
            left_attack = left_click.GetComponent<detectclicks>().attack;
            right_hp -= left_attack;
            if (right_hp < 0) right_width = 0;
            else right_width = right_hp / max_hp;
            right_text_hp.GetComponent<Text>().text = right_hp.ToString();
            right_transfrom.localScale = new Vector3(right_width, 1f, 1f);
            if (right_hp <= 0)
            {
                right_text_hp.GetComponent<Text>().text = "The end!";
                right_the_end = true;
            }
            right_click.SetActive(true);
            right_click.GetComponent<detectclicks>().is_click = false;
        }
        gameObject.SetActive(false);
    }
    void Update()
    {
        
       
    }
}
