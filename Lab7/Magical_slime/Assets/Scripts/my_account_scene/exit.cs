using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using System;
using System.IO;

public class exit : MonoBehaviour
{
    public string name_of_scene;
    public string account_path;

    void OnMouseDown()
    {
        File.Delete(account_path);
        File.Create(account_path);
        SceneManager.LoadScene(name_of_scene, LoadSceneMode.Single);
    }
}
