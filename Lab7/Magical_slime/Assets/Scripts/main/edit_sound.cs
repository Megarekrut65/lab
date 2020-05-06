using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;

public class edit_sound : MonoBehaviour
{
    public Sprite on_sound;
    public Sprite off_sound;
    public string path;

    void write_mode(bool is_on)
    {
        FileStream file = new FileStream(path, FileMode.OpenOrCreate);
        StreamWriter writer = new StreamWriter(file);
        if(is_on) writer.WriteLine("Mode=true");
        else writer.WriteLine("Mode=false");
        writer.Close();
    }
    void Start()
    {
        FileStream file = new FileStream(path, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        if(reader.EndOfStream)
        {
            GetComponent<Image>().sprite = on_sound;
            AudioListener.pause = false;
            reader.Close();
            return;
        }
        if (reader.ReadLine().Substring(5) == "true")
        {
            GetComponent<Image>().sprite = on_sound;
            AudioListener.pause = false;
        }
        else
        {
            GetComponent<Image>().sprite = off_sound;
            AudioListener.pause = true;
        }
        reader.Close();

    }
    void OnMouseDown()
    {
        if (AudioListener.pause)
        {
            GetComponent<Image>().sprite = on_sound;
            AudioListener.pause = false;
            write_mode(true);
        }
        else
        {
            GetComponent<Image>().sprite = off_sound;
            AudioListener.pause = true;
            write_mode(false);
        }
    }
}
