using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;
using UnityEngine.SceneManagement;

public class data_base : MonoBehaviour
{
    public InputField input_nickname;
    public InputField input_password;
    public string path;
    public string account_path;
    public string name_of_scene;

    void create_account_file(string nickname, string password, string mail, string points, string coins, string slimes)
    {
        FileStream file = new FileStream(account_path, FileMode.OpenOrCreate);
        StreamWriter writer = new StreamWriter(file);
        writer.WriteLine(nickname);
        writer.WriteLine(password);
        writer.WriteLine(mail);
        writer.WriteLine(points);
        writer.WriteLine(coins);
        writer.WriteLine(slimes);
        writer.Close();
    }
    bool find_player(string nickname, string password)
    {
        FileStream file = new FileStream(path, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        while(!reader.EndOfStream)
        {
            string file_nickname = reader.ReadLine();          
            if (file_nickname == nickname)
            {
                string file_password = reader.ReadLine();
                if (file_password == password)
                {
                    string mail = reader.ReadLine();
                    string points = reader.ReadLine();
                    string coins = reader.ReadLine();
                    string slimes = reader.ReadLine();
                    create_account_file(nickname, password, mail, points, coins, slimes);
                    reader.Close();
                    return true;
                }
                else
                {
                    reader.Close();
                    return false;
                }
                
            }
        }
        reader.Close();
        return false;
    }
    void incorrect_date()
    {
        Text text = input_nickname.transform.Find("Text").GetComponent<Text>();
        text.color = Color.white;
        text.fontSize = 6;
        text = input_password.transform.Find("Text").GetComponent<Text>();
        text.color = Color.white;
        text.fontSize = 6;
        input_nickname.image.color = Color.red;
        input_password.image.color = Color.red;
        input_nickname.text = "Nickname or password are incorrect!";
    }
    void OnMouseDown()
    {
        GetComponent<AudioSource>().Play();
        string nickname = "Nickname=";
        string password = "Password=";
        nickname += input_nickname.text;
        password += input_password.text;
        if(!find_player(nickname, password))
        {
            incorrect_date();
        }
        else
        {
            SceneManager.LoadScene(name_of_scene, LoadSceneMode.Single);          
        }      
    }
}
