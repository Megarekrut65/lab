using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;
using UnityEngine.SceneManagement;

public class chek_account : MonoBehaviour
{
    public string name_of_scene;
    public string path;
    private bool is_account = true;
    void Start()
    {
        if(!File.Exists(path)) is_account = false;
        else
        {            
            FileStream file = new FileStream(path, FileMode.Open);
            StreamReader reader = new StreamReader(file);
            const int size = 6;
            int[] size_of_lines = new int[size] { 9, 9, 5, 7, 6, 7 };
            string[] name_of_lines = new string[size] { "Nickname=", "Password=", "Mail=", "Points=", "Coins=", "Slimes=" };
            for(int i = 0; i < size; i++)
            {
                if (!reader.EndOfStream)
                {
                    string line = reader.ReadLine();
                    if ((line.Length <= size_of_lines[i]) || (line.Substring(0, size_of_lines[i]) != name_of_lines[i]))
                    {
                        is_account = false;
                        break;
                    }
                }
                else
                {
                    is_account = false;
                    break;
                }
            }                       
        }
        if (!is_account) SceneManager.LoadScene(name_of_scene, LoadSceneMode.Single);
    }
}
