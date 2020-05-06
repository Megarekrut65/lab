using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class click : MonoBehaviour
{
    public GameObject my_camera;
    public GameObject first_dice;
    public GameObject second_dice;
    public GameObject text_click;
    public GameObject time_slider;
    public bool right = false;
    public int attack;
    public bool combo;
    public bool is_clicked = false;
    private int first_attack;
    private int second_attack;

    IEnumerator show_random_dices()
    {
        int number_of_shows = 10;
        for (int i = 0; i < number_of_shows; i++)
        {
            int first_index = Random.Range(0, 5);
            int second_index = Random.Range(0, 5);
            first_dice.GetComponent<SpriteRenderer>().sprite = my_camera.GetComponent<the_begin>().dices[first_index].GetComponent<SpriteRenderer>().sprite;
            second_dice.GetComponent<SpriteRenderer>().sprite = my_camera.GetComponent<the_begin>().dices[second_index].GetComponent<SpriteRenderer>().sprite;
            yield return new WaitForSeconds(0.12f);
        }
        StopCoroutine("show_random_dices");
        first_dice.GetComponent<SpriteRenderer>().sprite = my_camera.GetComponent<the_begin>().dices[first_attack - 1].GetComponent<SpriteRenderer>().sprite;
        second_dice.GetComponent<SpriteRenderer>().sprite = my_camera.GetComponent<the_begin>().dices[second_attack - 1].GetComponent<SpriteRenderer>().sprite;      
        if (my_camera.GetComponent<the_begin>().is_click)
        {
            my_camera.GetComponent<the_begin>().start_fight(right);
            my_camera.GetComponent<the_begin>().is_click = false;
        }
        else
        {
            my_camera.GetComponent<the_begin>().is_click = true;
        }
    }
    public void OnMouseDown()
    {
        if (is_clicked) return;
        GetComponent<AudioSource>().Play();
        text_click.SetActive(false);
        time_slider.SetActive(false);
        is_clicked = true;
        first_attack = Random.Range(1, 6);
        second_attack = Random.Range(1, 6);
        attack = first_attack + second_attack;
        combo = false;
        if (first_attack == second_attack) combo = true;
        if (right)
        {
            my_camera.GetComponent<the_begin>().right_attack = attack;
            my_camera.GetComponent<the_begin>().right_combo = combo;
        }
        else
        {
            my_camera.GetComponent<the_begin>().left_attack = attack;
            my_camera.GetComponent<the_begin>().left_combo = combo;
        }
        StartCoroutine("show_random_dices");       
    }
}
