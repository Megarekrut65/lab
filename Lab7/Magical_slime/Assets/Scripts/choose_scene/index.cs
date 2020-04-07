using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class index : MonoBehaviour
{
    public GameObject my_camera;
    public GameObject buy;
    public GameObject start_button;
    public Text buy_text;
    private int number_of_slimes;
    public int i = 0;
    private GameObject[] slimes;
    private GameObject[] all_items;
  
    public void setting()
    {
        number_of_slimes = my_camera.GetComponent<the_start>().number_of_slimes;
        slimes = GameObject.FindGameObjectsWithTag("Player");
        all_items = GameObject.FindGameObjectsWithTag("items");
        for (int j = 1; j < number_of_slimes; j++)
        {
            all_items[j].SetActive(false);
        }
        if (my_camera.GetComponent<the_start>().array_slimes[i])
        {
            buy.SetActive(false);
            start_button.SetActive(true);
        }
        else
        {
            buy.SetActive(true);
            start_button.SetActive(false);
            buy_text.text = my_camera.GetComponent<the_start>().prices[i].ToString();
        }
    }
    void purchase()
    {
        if (my_camera.GetComponent<the_start>().array_slimes[i])
        {
            buy.SetActive(false);
            start_button.SetActive(true);
        }
        else
        {
            buy.SetActive(true);
            start_button.SetActive(false);
            buy_text.text = my_camera.GetComponent<the_start>().prices[i].ToString();
        }
    }
    public void right()
    {
        if (i < number_of_slimes - 1)
        {            
            slimes[i].transform.position += new Vector3(0f, 1f, 0f);
            all_items[i].SetActive(false);
            i++;
            purchase();
            all_items[i].SetActive(true);
        }
    }
    public void left()
    {
        if (i > 0)
        {
            slimes[i].transform.position += new Vector3(0f, 1f, 0f);
            all_items[i].SetActive(false);
            i--;
            purchase();
            all_items[i].SetActive(true);
        }
    }
}
