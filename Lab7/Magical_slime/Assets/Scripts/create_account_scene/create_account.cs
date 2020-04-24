using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;
using UnityEngine.SceneManagement;

public class create_account : MonoBehaviour
{
    public InputField input_nickname;
    public InputField input_mail;
    public InputField input_password;
    public InputField input_password_again;
    public GameObject incorrect_text;
    public GameObject error_message;
    public string path;

    bool find_nickname(string nickname)
    {
        FileStream file = new FileStream(path, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        while (!reader.EndOfStream)
        {
            string file_nickname;
            file_nickname = reader.ReadLine();
            if (file_nickname == nickname)
            {
                return true;
            }
        }
        reader.Close();
        return false;
    }
    void apped_file(string nickname, string password)
    {
        string mail = "Mail=" + input_mail.text;
        FileStream file = new FileStream(path, FileMode.Append);
        StreamWriter writer = new StreamWriter(file);
        writer.WriteLine(nickname);
        writer.WriteLine(password);
        writer.WriteLine(mail);
        writer.WriteLine("Points=100");
        writer.WriteLine("Coins=300");
        writer.WriteLine("Slimes=0000000");
        writer.Close();
    }
    void exists_nickname()
    {
        Text text = input_nickname.transform.Find("Text").GetComponent<Text>();
        text.color = Color.white;
        input_nickname.image.color = Color.red;
        input_nickname.text = "This nickname already exists!";
    }
    void incorrect_password()
    {
        incorrect_text.SetActive(true);
        input_password.image.color = Color.red;
        input_password_again.image.color = Color.red;
    }
    bool empty_input(InputField input)
    {
        if (input.text.Length > 3) return false;
        input.image.color = Color.red;
        input.text = "";
        error_message.SetActive(true);
        return true;
    }
    void OnMouseDown()
    {
        incorrect_text.SetActive(false);        
        if(empty_input(input_nickname)|| empty_input(input_mail)|| empty_input(input_password)|| empty_input(input_password_again)) return;
        string nickname = "Nickname=" + input_nickname.text;
        if(find_nickname(nickname))
        {
            exists_nickname();
        }
        else
        {        
            string password = "Password=" + input_password.text;         
            string password_again = "Password=" + input_password_again.text;         
            if (password == password_again)
            {                
                apped_file(nickname, password);
                SceneManager.LoadScene("sign_in_scene", LoadSceneMode.Single);
            }
            else
            {
                incorrect_password();
            }
        }
    }
}
