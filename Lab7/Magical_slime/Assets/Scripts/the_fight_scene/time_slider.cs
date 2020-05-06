using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class time_slider : MonoBehaviour
{
    public GameObject slime;
    public GameObject round;
    public GameObject click;
    public GameObject bomb;
    public string name_of_animation;

    IEnumerator time()
    {
        for(int i = 10; i >=0 ; i--)
        {
            gameObject.GetComponent<Slider>().value = i;
            yield return new WaitForSeconds(1f);
        }
        time_is_up();
        StopCoroutine("time");
    }
    void Start()
    {
        start_time();
    }
    public void start_time()
    {
        gameObject.GetComponent<Slider>().value = 10;
        StartCoroutine("time");
    }
    public void is_click()
    {
        StopCoroutine("time");
    }
    public void hit()
    {
        round.GetComponent<AudioSource>().Play();
        slime.GetComponent<slime>().getting_damage(6);
        click.GetComponent<click>().OnMouseDown();
    }
    void time_is_up()
    {
        bomb.GetComponent<Animation>().Play(name_of_animation);        
    }
}
