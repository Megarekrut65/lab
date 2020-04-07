using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;

public class slime : MonoBehaviour
{
    public string slime_path;
    public Text name_of_player;
    public Text points_text;
    public string tag_slime;
    public int hp = 100;
    public string element;
    public bool side = false;
    public Text hp_text;
    public Slider hp_slider;
    public GameObject my_camera;
    private Sprite passive_skill;
    public int number_of_slimes = 7;
    public int index_of_slime;
    private int passive_index;
    private GameObject[] slimes;
    private string nickname;
    private string points;

    void read_file()
    {
        FileStream file = new FileStream(slime_path, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        nickname = reader.ReadLine();
        nickname = nickname.Substring(9);
        points = reader.ReadLine();
        points = points.Substring(7);
        element = reader.ReadLine();
        element = element.Substring(8);
        reader.Close();
    }
    void set_images()
    {
        gameObject.GetComponent<SpriteRenderer>().sprite = slimes[index_of_slime].GetComponent<SpriteRenderer>().sprite;
        passive_skill = my_camera.GetComponent<the_begin>().good_passive[index_of_slime].GetComponent<SpriteRenderer>().sprite;
        passive_index = my_camera.GetComponent<the_begin>().add_effect(passive_skill, side);
    }   
    public void choose_slime()
    {
        switch(element)
        {
            case "fire": index_of_slime = 0;
                break;
            case "water": index_of_slime = 1;
                break;
            case "poison": index_of_slime = 2;
                break;
            case "wood": index_of_slime = 3;
                break;
            case "dark": index_of_slime = 4;
                break;
            case "girl": index_of_slime = 5;
                break;
            case "white": index_of_slime = 6;
                break;
        }
        set_images();
    }   
    void Start()
    {
        read_file();
        name_of_player.text = nickname;
        points_text.text = points;
        slimes = GameObject.FindGameObjectsWithTag(tag_slime);
        for (int i = 0; i < number_of_slimes; i++) slimes[i].SetActive(false);
        hp_text.text = hp.ToString();
        hp_slider.value = hp;      
    }
    public void getting_damage(int damage)
    {
        hp -= damage;
        hp_text.text = hp.ToString();
        hp_slider.value = hp;
    }
}
