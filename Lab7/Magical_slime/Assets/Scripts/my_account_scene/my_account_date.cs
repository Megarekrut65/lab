using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;
using UnityEngine.UI;

public class my_account_date : MonoBehaviour
{
    public Text nickname;
    public Text mail;
    public Text points;
    public Text coins;
    public string path_account;

    void Start()
    {
        FileStream file = new FileStream(path_account, FileMode.Open);
        StreamReader reader = new StreamReader(file);
        nickname.text += " " + reader.ReadLine().Substring(9);
        string temp = reader.ReadLine();
        mail.text += " " + reader.ReadLine().Substring(5);
        points.text += " " + reader.ReadLine().Substring(7);
        coins.text += " " + reader.ReadLine().Substring(6);
        reader.Close();
    }
}
