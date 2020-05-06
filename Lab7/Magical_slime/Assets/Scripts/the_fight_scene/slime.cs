using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;
using UnityEngine.SceneManagement;

public class slime : MonoBehaviour
{
    public string name_of_show;
    public string name_of_fly;
    public string name_of_die;
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
    public GameObject boll;
    private Sprite passive_skill;
    public int number_of_slimes = 7;
    public int index_of_slime;
    private int passive_index;
    private GameObject[] slimes;
    public string nickname;
    private string points;
    private bool again_life = false;

    void read_file()
    {
        FileStream file = new FileStream(slime_path, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        if (reader.EndOfStream)
        {
            reader.Close();
            SceneManager.LoadScene("main", LoadSceneMode.Single);
            return;
        }
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
        GetComponent<Image>().sprite = slimes[index_of_slime].GetComponent<Image>().sprite;
        passive_skill = my_camera.GetComponent<the_begin>().good_passive[index_of_slime].GetComponent<SpriteRenderer>().sprite;
        passive_index = my_camera.GetComponent<the_begin>().add_effect(passive_skill, side);
        boll.GetComponent<SpriteRenderer>().sprite = my_camera.GetComponent<the_begin>().bolls[index_of_slime].GetComponent<SpriteRenderer>().sprite;
        GetComponent<Animation>().Play(name_of_show);
    }
    void start_fly()
    {
        GetComponent<Animation>().Play(name_of_fly);
        my_camera.GetComponent<the_begin>().show_side(side);
    }
    public void choose_slime()
    {
        read_file();
        name_of_player.text = nickname;
        points_text.text = points;
        slimes = GameObject.FindGameObjectsWithTag(tag_slime);
        for (int i = 0; i < number_of_slimes; i++) slimes[i].SetActive(false);
        hp_text.text = hp.ToString();
        hp_slider.value = hp;
        switch (element)
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
    public void getting_hp(int health)
    {
        hp += health;
        if (hp > 110) hp = 110;
        hp_text.text = hp.ToString();
        hp_slider.value = hp;
    }   
    public void getting_damage(int damage)
    {
        GetComponent<AudioSource>().Play();
        if ((index_of_slime == 5)||(index_of_slime == 6))
        {
            if (my_camera.GetComponent<the_begin>().edit_girl(side, damage)) return;
        }
        hp -= damage;
        if (hp < -10) hp = -10;
        hp_text.text = hp.ToString();
        hp_slider.value = hp;
        transform.localScale -= new Vector3(1, 1, 1);     
    }
    void rise_again()
    {
        name_of_player.GetComponent<AudioSource>().Play();
        GetComponent<Animation>().Stop(name_of_fly);        
        gameObject.SetActive(false);
        if (again_life)
        {
            hp = 1;
            hp_text.text = hp.ToString();          
            my_camera.GetComponent<the_begin>().remove_effect(passive_index, side);
            passive_skill = my_camera.GetComponent<the_begin>().bad_passive[index_of_slime].GetComponent<SpriteRenderer>().sprite;
            passive_index = my_camera.GetComponent<the_begin>().add_effect(passive_skill, side);
            gameObject.SetActive(true);
            GetComponent<Animation>().Play(name_of_show);
        }
    }
    public void set_die(bool life = false)
    {
        again_life = life;
        GetComponent<Animation>().Play(name_of_die);       
    }
}
