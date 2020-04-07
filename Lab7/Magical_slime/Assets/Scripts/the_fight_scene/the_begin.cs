using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class the_begin : MonoBehaviour
{
    public int number_of_skills = 7;
    public int number_of_icons = 6;
    public GameObject left_slime;
    public GameObject right_slime;
    private GameObject[] left_effects;
    private GameObject[] right_effects;
    public GameObject[] dices;
    public GameObject[] good_combo;
    public GameObject[] bad_combo;
    public GameObject[] good_passive;
    public GameObject[] bad_passive;
    private int left_index_of_effects = 0;
    private int right_index_of_effects = 0;

    void Start()
    {
        good_combo = GameObject.FindGameObjectsWithTag("good_combo");
        bad_combo = GameObject.FindGameObjectsWithTag("bad_combo");
        good_passive = GameObject.FindGameObjectsWithTag("good_passive");
        bad_passive = GameObject.FindGameObjectsWithTag("good_passive");
        for (int i = 0; i < number_of_skills; i++)
        {
            good_combo[i].SetActive(false);
            bad_combo[i].SetActive(false);
            good_passive[i].SetActive(false);
            bad_passive[i].SetActive(false);
        }       
        dices = GameObject.FindGameObjectsWithTag("dice");
        for(int i = 0; i < 6; i++) dices[i].SetActive(false);
        left_effects = GameObject.FindGameObjectsWithTag("left_effect");
        right_effects = GameObject.FindGameObjectsWithTag("right_effect");
        for (int i = 0; i < number_of_icons; i++)
        {
            left_effects[i].SetActive(false);
            right_effects[i].SetActive(false);
        }
        left_slime.GetComponent<slime>().choose_slime();
        right_slime.GetComponent<slime>().choose_slime();
    }
    public int add_effect(Sprite effect, bool side)
    {       
        if (side)
        {
            if (right_index_of_effects == number_of_icons) right_index_of_effects--;
            right_effects[right_index_of_effects].SetActive(true);
            right_effects[right_index_of_effects++].GetComponent<SpriteRenderer>().sprite = effect;
            return (right_index_of_effects - 1);
        }
        else
        {
            if (left_index_of_effects == number_of_icons) left_index_of_effects--;
            left_effects[left_index_of_effects].SetActive(true);
            left_effects[left_index_of_effects++].GetComponent<SpriteRenderer>().sprite = effect;
            return (left_index_of_effects - 1);
        }
    }
    public void remove_effect(int index, bool side)
    {
        if (side)
        {
            if (right_index_of_effects == 0) return;
            right_effects[index].SetActive(false);
            for(int i = index; i < number_of_icons - 1; i++)
            {
                right_effects[i] = right_effects[i + 1];
            }
            right_index_of_effects--;
        }
        else
        {
            if (left_index_of_effects == 0) return;
            left_effects[index].SetActive(false);
            for (int i = index; i < number_of_icons - 1; i++)
            {
                left_effects[i] = left_effects[i + 1];
            }
            left_index_of_effects--;
        }
    }
}
