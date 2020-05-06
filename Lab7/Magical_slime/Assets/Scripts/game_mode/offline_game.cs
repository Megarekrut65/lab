using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;
using UnityEngine.SceneManagement;

public class offline_game : MonoBehaviour
{
    public GameObject my_camera;
    public GameObject backgraund;
    public GameObject back;
    public string path_of_player1;
    public string path_of_player2;
    public string path_of_mode;
    public string account_path;
    private string element;
    public string name_of_scene;
    private bool[] array_slimes;

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
        writer.WriteLine("Mode=offline");
        writer.Close();
    }
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
    public void set_element(int index)
    {
        choose_element(index);
        FileStream file = new FileStream(path_of_player2, FileMode.OpenOrCreate);
        StreamWriter writer = new StreamWriter(file);
        int points = read_points();
        if (points < 0) points = 10;
        writer.WriteLine("Nickname=Player2");
        writer.WriteLine("Points=" + points.ToString());
        writer.WriteLine("Element=" + element);
        writer.Close();
        add_mode();
        SceneManager.LoadScene(name_of_scene, LoadSceneMode.Single);
    }
    void read_account()
    {
        FileStream file = new FileStream(account_path, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        string slimes = "0000000";
        while (!reader.EndOfStream)
        {
            slimes = reader.ReadLine();
            if ((slimes.Length > 7) && (slimes.Substring(0, 7) == "Slimes="))
            {
                slimes = slimes.Substring(7);
                break;
            }
        }
        reader.Close();
        const int number_of_slimes = 7;
        array_slimes = new bool[number_of_slimes];
        for (int i = 0; i < number_of_slimes; i++)
        {
            if (slimes[i] == '1') array_slimes[i] = true;
            else array_slimes[i] = false;
        }
    }
    void OnMouseDown()
    {
        backgraund.GetComponent<AudioSource>().Play();
        back.SetActive(true);
        read_account();
        my_camera.GetComponent<start_mode>().show_slimes(array_slimes);
    }
}
