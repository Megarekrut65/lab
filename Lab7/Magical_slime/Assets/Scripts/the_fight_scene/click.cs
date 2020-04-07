using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class click : MonoBehaviour
{
    public GameObject my_camera;
    public GameObject first_dice;
    public GameObject second_dice;
    public int attack;
    public bool combo;
    private int first_attack;
    private int second_attack;

    IEnumerator show_random_dices()
    {
        int number_of_shows = 18;
        for(int i = 0; i < number_of_shows; i++)
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
    }
    void OnMouseDown()
    {
        first_attack = Random.Range(1, 6);
        second_attack = Random.Range(1, 6);
        attack = first_attack + second_attack;
        if (first_attack == second_attack) combo = true;
        StartCoroutine("show_random_dices");       
    }
}
