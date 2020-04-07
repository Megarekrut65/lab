using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;
using UnityEngine.SceneManagement;

public class start_button : MonoBehaviour
{
    public string name_of_scene;
    public GameObject my_camera;
    public GameObject place;
    public string slime_path;
    private string element;

    void choose_element(int index)
    {
        switch(index)
        {
            case 0: element = "fire";
                break;
            case 1: element = "water";
                break;
            case 2: element = "poison";
                break;
            case 3: element = "wood";
                break;
            case 4: element = "dark";
                break;
            case 5: element = "girl";
                break;
            case 6:  element = "white";
                break;
        }
    }
    void OnMouseDown()
    {
        choose_element(place.GetComponent<index>().i);
        FileStream file = new FileStream(slime_path, FileMode.OpenOrCreate);
        StreamWriter writer = new StreamWriter(file);
        writer.WriteLine(my_camera.GetComponent<the_start>().nickname);
        writer.WriteLine("Points=" + my_camera.GetComponent<the_start>().points.ToString());
        writer.WriteLine("Element=" + element);
        writer.Close();
        SceneManager.LoadScene(name_of_scene, LoadSceneMode.Single);
    }
}
