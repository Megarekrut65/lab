using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class wood_combo : MonoBehaviour
{
    public GameObject enemy_slime;
    public string name_of_show;
    public string name_of_end;

    public void show()
    {
        GetComponent<Animation>().Play(name_of_show);
    }
    void set_false()
    {
        gameObject.SetActive(false);
    }
    public void clear_wood()
    {
        GetComponent<Animation>().Play(name_of_end);
    }
}
