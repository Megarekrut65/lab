using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;
using UnityEngine.SceneManagement;

public class the_start : MonoBehaviour
{
    public GameObject place;
    public Text coins_text;
    public int number_of_slimes = 7;
    public string path_account;
    public string path;
    public string new_path;
    public string nickname;
    private string password;
    private string mail;
    public int points = 0;
    public int coins = 0;
    public bool[] array_slimes;
    public int[] prices;

    void Start()
    {
        FileStream file = new FileStream(path_account, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        if(reader.EndOfStream)
        {
            reader.Close();
            SceneManager.LoadScene("main", LoadSceneMode.Single);
            return;
        }
        string coins_string = "0";
        string points_string = "0";
        nickname = reader.ReadLine();
        password = reader.ReadLine();
        mail = reader.ReadLine();
        points_string = reader.ReadLine();
        points_string = points_string.Substring(7);
        points = Convert.ToInt32(points_string);
        coins_string = reader.ReadLine();
        coins_string = coins_string.Substring(6);
        coins = Convert.ToInt32(coins_string);
        string slimes_string = reader.ReadLine();
        slimes_string = slimes_string.Substring(7);
        array_slimes = new bool[number_of_slimes];
        for (int i = 0; i < number_of_slimes; i++)
        {
            if (slimes_string[i] == '1') array_slimes[i] = true;
            else array_slimes[i] = false;
        }
        reader.Close();
        coins_text.text = coins_string;
        prices = new int[number_of_slimes];
        int value = 100;
        for (int i = 0; i < number_of_slimes; i++)
        {
            prices[i] = value;
            value *= 2;
        }
        place.GetComponent<index>().setting();
    }
    void append(string file_nickname, string file_password, string file_mail, string file_points, string file_coins, string file_slimes, string file_path)
    {
        FileStream file = new FileStream(file_path, FileMode.Append);
        StreamWriter writer = new StreamWriter(file);
        writer.WriteLine(file_nickname);
        writer.WriteLine(file_password);
        writer.WriteLine(file_mail);
        writer.WriteLine(file_points);
        writer.WriteLine(file_coins);
        writer.WriteLine(file_slimes);
        writer.Close();
    }
    void renewal_account(string new_points, string new_coins, string new_slimes)
    {
        FileStream file = new FileStream(path_account, FileMode.OpenOrCreate);
        StreamWriter writer = new StreamWriter(file);
        writer.WriteLine(nickname);
        writer.WriteLine(password);
        writer.WriteLine(mail);
        writer.WriteLine(new_points);
        writer.WriteLine(new_coins);
        writer.WriteLine(new_slimes);
        writer.Close();
    }
    public void save_info()
    {
        string points_string = "Points=" + points.ToString();
        string coins_string = "Coins=" + coins.ToString();
        string slimes_string = "Slimes=";
        for(int i = 0; i < number_of_slimes; i++)
        {
            int value;
            if (array_slimes[i]) value = 1;
            else value = 0;
            slimes_string += value.ToString();
        }
        renewal_account(points_string, coins_string, slimes_string);
        FileStream file = new FileStream(path, FileMode.Open);
        StreamReader reader = new StreamReader(file);
        while (!reader.EndOfStream)
        {
            string file_nickname = reader.ReadLine();
            if (file_nickname == nickname)
            {
                append(nickname, password, mail, points_string, coins_string, slimes_string, new_path);               
            }
            else if ((file_nickname.Length > 9) && (file_nickname.Substring(0, 9) == "Nickname="))
            {
                string file_password = reader.ReadLine();
                string file_mail = reader.ReadLine();
                string file_points = reader.ReadLine();
                string file_coins = reader.ReadLine();
                string file_slimes = reader.ReadLine(); 
                append(file_nickname, file_password, file_mail, file_points, file_coins, file_slimes, new_path);
            }
        }
        reader.Close();
        File.Delete(path);
        File.Move(new_path, path);
    }
}
