using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;
using UnityEngine.SceneManagement;

public class game_with_bot : MonoBehaviour
{
    public string path_of_player1;
    public string path_of_player2;
    public string path_of_mode;
    private string element;
    public string name_of_scene;
    public GameObject backgraund;

    void choose_element(int index)
    {
        switch (index)
        {
            case 0:
                element = "fire";
                break;
            case 1:
                element = "water";
                break;
            case 2:
                element = "poison";
                break;
            case 3:
                element = "wood";
                break;
            case 4:
                element = "dark";
                break;
            case 5:
                element = "girl";
                break;
            case 6:
                element = "white";
                break;
        }
    }
    int read_points()
    {
        FileStream file = new FileStream(path_of_player1, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        while (!reader.EndOfStream)
        {
            string points = reader.ReadLine();
            if ((points.Length > 7) && (points.Substring(0, 7) == "Points="))
            {
                reader.Close();
                return Convert.ToInt32(points.Substring(7));
            }
        }
        reader.Close();
        return 0;
    }
    void add_mode()
    {
        FileStream file = new FileStream(path_of_mode, FileMode.OpenOrCreate);
        StreamWriter writer = new StreamWriter(file);
        writer.WriteLine("Mode=bot");
        writer.Close();
    }
    void OnMouseDown()
    {
        backgraund.GetComponent<AudioSource>().Play();
        int index = UnityEngine.Random.Range(0, 6);
        choose_element(index);
        FileStream file = new FileStream(path_of_player2, FileMode.OpenOrCreate);
        StreamWriter writer = new StreamWriter(file);
        int points = read_points() + UnityEngine.Random.Range(-40, 50);
        if (points < 0) points = 10;
        writer.WriteLine("Nickname=" + element);
        writer.WriteLine("Points=" + points.ToString());
        writer.WriteLine("Element=" + element);
        writer.Close();
        add_mode();
        SceneManager.LoadScene(name_of_scene, LoadSceneMode.Single);
    }
}
