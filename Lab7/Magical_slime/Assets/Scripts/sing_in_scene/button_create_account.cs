using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class button_create_account : MonoBehaviour
{
    void OnMouseDown()
    {
        SceneManager.LoadScene("create_account_scene", LoadSceneMode.Single);
    }
}
