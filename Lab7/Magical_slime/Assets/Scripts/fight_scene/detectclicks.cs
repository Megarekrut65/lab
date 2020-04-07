using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class detectclicks : MonoBehaviour
{
    public bool is_left = false;
    public GameObject second_click;
    public GameObject fight;
    public int attack = 0;
    private int attack1 = 0;
    private int attack2 = 0;
    public bool is_click = false;
    private bool is_second_click;
    private Vector3 first;
    private Vector3 second;
    public GameObject one;
    public GameObject two;
    public GameObject three;
    public GameObject four;
    public GameObject five;
    public GameObject six;
    private GameObject dice;
    void set_object(int number)
    {
        switch(number)
        {
            case 1: dice = one;
                break;
            case 2: dice = two;
                break;
            case 3: dice = three;
                break;
            case 4: dice = four;
                break;
            case 5: dice = five;
                break;
            case 6: dice = six;
                break;
        }
    }
    void OnMouseDown()
    {
        attack1 = Random.Range(1, 6);
        attack2 = Random.Range(1, 6);
        if(is_left)
        {
            first = new Vector3(-2.5f, -2f, -9f);
            second = new Vector3(1f, -2f, -9f);
        }
        else
        {
            first = new Vector3(1f, -2f, -9f);
            second = new Vector3(2.5f, -2f, -9f);
        }
        StartCoroutine(spawn());
        attack = attack1 + attack2;
        is_click = true;
        is_second_click = second_click.GetComponent<detectclicks>().is_click;
        gameObject.SetActive(false);
    }
    IEnumerator spawn()
    {
        for (int i = 0; i < 10; i++)
        {
            int temp = Random.Range(1, 6);
            set_object(temp);
            Instantiate(dice, first, Quaternion.identity);
            Destroy(dice, 0.5f);
            temp = Random.Range(1, 6);
            set_object(temp);
            Instantiate(dice, second, Quaternion.identity);
            Destroy(dice, 0.5f);
            yield return new WaitForSeconds(0.5f);
        }
        set_object(attack1);
        Instantiate(dice, first, Quaternion.identity);
        Destroy(dice, 5f);
        set_object(attack2);
        Instantiate(dice, second, Quaternion.identity);
        Destroy(dice, 5f);
    }
}
