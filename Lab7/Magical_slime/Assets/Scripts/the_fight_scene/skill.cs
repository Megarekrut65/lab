using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class skill : MonoBehaviour
{
    public GameObject my_camera;
    public string name_of_animation;
    private bool right = false;
    private bool show_skill = true;
    private bool need_edit = true;

    public void show(bool side, bool show_skills, bool edit)
    {
        need_edit = edit;
        right = side;
        show_skill = show_skills;
        GetComponent<Animation>().Play(name_of_animation);
        GetComponent<AudioSource>().Play();
    }
    void check_skills()
    {
       if (!show_skill) return;
       if(right) my_camera.GetComponent<the_begin>().right_skills(need_edit);
       else my_camera.GetComponent<the_begin>().left_skills(need_edit);
    }
}
