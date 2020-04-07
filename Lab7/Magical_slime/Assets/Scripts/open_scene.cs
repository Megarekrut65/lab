using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class open_scene : MonoBehaviour
{
    public string name_of_scene;

    void OnMouseDown()
    {
        SceneManager.LoadScene(name_of_scene, LoadSceneMode.Single);
    }
}
