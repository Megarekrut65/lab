using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;
using UnityEngine.SceneManagement;

public class the_begin : MonoBehaviour
{
    public Text round_text;
    public string name_of_scene;
    public string path_of_mode;
    private bool is_bot = false;
    public string path_of_victory;
    private int round = 1;
    public int number_of_skills = 7;
    public int number_of_icons = 6;
    public GameObject left_slime;
    public GameObject right_slime;
    public GameObject left_boll;
    public GameObject right_boll;
    public GameObject right_click_text;
    public GameObject left_click_text;
    public GameObject right_click;
    public GameObject left_click;
    public GameObject right_time_slider;
    public GameObject left_time_slider;
    public int left_attack = 0;
    public int right_attack = 0;
    public bool left_combo = false;
    public bool right_combo = false;
    public bool late_left_combo = false;
    public bool late_right_combo = false;
    private GameObject[] left_effects;
    private GameObject[] right_effects;
    public bool is_click = false;
    public bool no_click = false;
    public GameObject[] dices;
    public GameObject[] good_combo;
    public GameObject[] bad_combo;
    public GameObject[] good_passive;
    public GameObject[] bad_passive;
    public GameObject[] bolls;
    private int[] left_indexes_of_skills;
    private int[] right_indexes_of_skills;
    private int left_index_of_slime = 0;
    private int right_index_of_slime = 0;
    private GameObject left_big_skill;
    private GameObject right_big_skill;
    private GameObject left_water_combo_skill;
    private GameObject right_water_combo_skill;
    private GameObject left_poison_combo_skill;
    private GameObject right_poison_combo_skill;
    private int left_number_of_poison = 0;
    private int right_number_of_poison = 0;
    private int left_poison_attack = 0;
    private int right_poison_attack = 0;
    private GameObject left_wood_combo_skill;
    private GameObject right_wood_combo_skill;
    private int left_number_of_leaf = 0;
    private int right_number_of_leaf = 0;
    private int[] left_wood_indexes;
    private int[] right_wood_indexes;
    public bool left_can_click = true;
    public bool right_can_click = true;
    private GameObject left_dark_combo_skill;
    private GameObject right_dark_combo_skill;
    private GameObject left_girl_combo_skill;
    private GameObject right_girl_combo_skill;
    private bool left_dark_again_life;
    private bool right_dark_again_life;
    private int left_passive_index = 0;
    private int right_passive_index = 0;
    private string left_nickname;
    private string right_nickname;
    private bool left_die = false;
    private bool right_die = false;

    void set_combo_skills()
    {
        left_big_skill = GameObject.Find("left_big_skill");
        left_big_skill.SetActive(false);
        right_big_skill = GameObject.Find("right_big_skill");
        right_big_skill.SetActive(false);
        left_water_combo_skill = GameObject.Find("left_water_combo_skill");
        left_water_combo_skill.SetActive(false);
        right_water_combo_skill = GameObject.Find("right_water_combo_skill");
        right_water_combo_skill.SetActive(false);
        left_poison_combo_skill = GameObject.Find("left_poison_combo_skill");
        left_poison_combo_skill.SetActive(false);
        right_poison_combo_skill = GameObject.Find("right_poison_combo_skill");
        right_poison_combo_skill.SetActive(false);
        left_wood_combo_skill = GameObject.Find("left_wood_combo_skill");
        left_wood_combo_skill.SetActive(false);
        right_wood_combo_skill = GameObject.Find("right_wood_combo_skill");
        right_wood_combo_skill.SetActive(false);
        left_dark_combo_skill = GameObject.Find("left_dark_combo_skill");
        left_dark_combo_skill.SetActive(false);
        right_dark_combo_skill = GameObject.Find("right_dark_combo_skill");
        right_dark_combo_skill.SetActive(false);
        left_girl_combo_skill = GameObject.Find("left_girl_combo_skill");
        left_girl_combo_skill.SetActive(false);
        right_girl_combo_skill = GameObject.Find("right_girl_combo_skill");
        right_girl_combo_skill.SetActive(false);      
    }
    void set_images_of_skills()
    {
        good_combo = GameObject.FindGameObjectsWithTag("good_combo");
        bad_combo = GameObject.FindGameObjectsWithTag("bad_combo");
        good_passive = GameObject.FindGameObjectsWithTag("good_passive");
        bad_passive = GameObject.FindGameObjectsWithTag("bad_passive");
        for (int i = 0; i < number_of_skills; i++)
        {
            good_combo[i].SetActive(false);
            bad_combo[i].SetActive(false);
            good_passive[i].SetActive(false);
            bad_passive[i].SetActive(false);
        }
    }
    void set_bolls()
    {
        left_boll.SetActive(false);
        right_boll.SetActive(false);
        bolls = GameObject.FindGameObjectsWithTag("bolls");
        for (int i = 0; i < number_of_skills; i++)
        {
            bolls[i].SetActive(false);
        }
    }
    void set_effects()
    {
        left_effects = GameObject.FindGameObjectsWithTag("left_effect");
        right_effects = GameObject.FindGameObjectsWithTag("right_effect");
        for (int i = 0; i < number_of_icons; i++)
        {
            left_effects[i].SetActive(false);
            right_effects[i].SetActive(false);
        }
    }
    void set_dices()
    {
        dices = GameObject.FindGameObjectsWithTag("dice");
        for (int i = 0; i < 6; i++) dices[i].SetActive(false);
    }
    void set_indexes()
    {
        left_indexes_of_skills = new int[number_of_skills];
        right_indexes_of_skills = new int[number_of_skills];
        for (int i = 0; i < number_of_skills; i++)
        {
            left_indexes_of_skills[i] = -1;
            right_indexes_of_skills[i] = -1;
        }
        left_wood_indexes = new int[3];
        right_wood_indexes = new int[3];
        for (int i = 0; i < 3; i++)
        {
            left_wood_indexes[i] = -1;
            right_wood_indexes[i] = -1;
        }
    }
    void set_slimes()
    {
        left_click_text.SetActive(false);
        left_click.GetComponent<click>().is_clicked = true;
        right_click_text.SetActive(false);
        right_click.GetComponent<click>().is_clicked = true;
        left_slime.GetComponent<slime>().choose_slime();
        right_slime.GetComponent<slime>().choose_slime();
        left_index_of_slime = left_slime.GetComponent<slime>().index_of_slime;
        right_index_of_slime = right_slime.GetComponent<slime>().index_of_slime;
        left_passive_index = left_index_of_slime;
        right_passive_index = right_index_of_slime;
        left_nickname = left_slime.GetComponent<slime>().nickname;
        right_nickname = right_slime.GetComponent<slime>().nickname;
    }
    void read_mode()
    {
        FileStream file = new FileStream(path_of_mode, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        while (!reader.EndOfStream)
        {
            string mode = reader.ReadLine();
            if ((mode.Length > 5) && (mode.Substring(0, 5) == "Mode="))
            {
                if (mode.Substring(5) == "bot")
                {
                    reader.Close();
                    is_bot = true;
                    return;
                }
                else
                {
                    reader.Close();
                    is_bot = false;
                    return;
                }
            }
        }
        reader.Close();
    }
    void game_bot()
    {
        right_click.GetComponent<click>().OnMouseDown();
    }
    void Start()
    {
        round_text.text = round.ToString();
        left_dark_again_life = true;
        right_dark_again_life = true;
        set_bolls();
        set_effects();
        set_images_of_skills();
        set_dices();
        set_combo_skills();
        set_indexes();
        set_slimes();
        read_mode();
        
    }
    public void show_side(bool side)
    {
        if(side)
        {
            right_click_text.SetActive(true);
            right_click.GetComponent<click>().is_clicked = false;
            if (is_bot) game_bot();
            return;
        }
        left_click_text.SetActive(true);
        left_click.GetComponent<click>().is_clicked = false;      
    }
    public int add_effect(Sprite effect, bool side)
    {       
        if (side)
        {
            int index = -1;
            for(int i = 0; i < number_of_icons; i++)
            {
                if (!right_effects[i].activeInHierarchy)
                {
                    index = i;
                    break;
                }
            }
            if (index == -1) index = number_of_icons - 1;
            right_effects[index].SetActive(true);
            right_effects[index].GetComponent<SpriteRenderer>().sprite = effect;
            return index;
        }
        else
        {
            int index = -1;
            for (int i = 0; i < number_of_icons; i++)
            {
                if (!left_effects[i].activeInHierarchy)
                {
                    index = i;
                    break;
                }
            }
            if (index == -1) index = number_of_icons - 1;
            left_effects[index].SetActive(true);
            left_effects[index].GetComponent<SpriteRenderer>().sprite = effect;
            return index;
        }
    }
    public void remove_effect(int index, bool side)
    {
        if (side)
        {
            right_effects[index].SetActive(false);
        }
        else
        { 
            left_effects[index].SetActive(false);
        }
    }
    void fire_combo(GameObject the_boll, int attack)
    {
        the_boll.SetActive(true);
        the_boll.GetComponent<the_boll>().boll_fly(attack, true, true);
    }
    void water_combo(GameObject skill, int attack)
    {       
        skill.SetActive(true);
        skill.GetComponent<water_combo>().show(attack);
    }
    void poison_combo(GameObject skill, int attack, ref int poison_attack, ref int number_of_poison, bool side, ref int index_of_poison)
    {
        if (skill.activeInHierarchy)
        {
            skill.SetActive(false);
            remove_effect(index_of_poison, side);
        }
        poison_attack = attack/2;
        number_of_poison = 3;
        skill.SetActive(true);
        index_of_poison = add_effect(bad_combo[2].GetComponent<SpriteRenderer>().sprite, side);
        skill.GetComponent<poison_combo>().show();     
    }    
    void add_leaf(int leaf, bool side, ref int[] wood_indexes)
    {
        for(int i = 0; i < 3; i++)
        {
            if(leaf == 0) return;
            if(wood_indexes[i] == -1)
            {
                wood_indexes[i] = add_effect(bad_passive[3].GetComponent<SpriteRenderer>().sprite, side);
                leaf--;
            }
        }
    }
    void wood_combo(int attack, ref int[] wood_indexes, bool side, ref int number_of_leaf)
    {
        int leaf = attack / 4;
        add_leaf(leaf, side, ref wood_indexes);
        number_of_leaf += leaf;
    }
    void remove_wood(ref int[] wood_indexes, bool side)
    {
        for (int i = 0; i < 3; i++)
        {
            if (wood_indexes[i] != -1)
            {
                remove_effect(wood_indexes[i], side);
                wood_indexes[i] = -1;
            }
        }
    }
    void edit_wood(GameObject big_skill, GameObject skill, ref int index_of_wood, ref int[] wood_indexes, bool side, ref int number_of_leaf)
    {
        if(number_of_leaf >= 3)
        {
            if (side) right_can_click = false;
            else left_can_click = false;
            is_click = true;
            big_skill.GetComponent<SpriteRenderer>().sprite = good_combo[3].GetComponent<SpriteRenderer>().sprite;
            big_skill.SetActive(true);
            big_skill.GetComponent<skill>().show(true, false, true);
            number_of_leaf = 0;
            remove_wood(ref wood_indexes, side);
            if(index_of_wood == -1 ) index_of_wood = add_effect(bad_combo[3].GetComponent<SpriteRenderer>().sprite, side);
            skill.SetActive(true);
            skill.GetComponent<wood_combo>().show();
        }
        else if(skill.activeInHierarchy)
        {
            if (side) right_can_click = true;
            else left_can_click = true;
            skill.GetComponent<wood_combo>().clear_wood();
            remove_effect(index_of_wood, side);
            index_of_wood = -1;
        }
    }
    void edit_poison(GameObject skill, ref int poison_attack, ref int number_of_poison, bool side, int index_of_poison)
    {
        if (number_of_poison > 0)
        {
            number_of_poison--;
            if (number_of_poison == 0)
            {
                skill.GetComponent<poison_combo>().is_poison = false;
                remove_effect(index_of_poison, side);
            }
            skill.GetComponent<poison_combo>().hitting(poison_attack);           
        }
    }
    public void dark_attack(int attack, bool side)
    {
        if(side)
        {
            right_boll.GetComponent<SpriteRenderer>().sprite = bolls[left_slime.GetComponent<slime>().index_of_slime].GetComponent<SpriteRenderer>().sprite;
            right_boll.SetActive(true);
            right_boll.GetComponent<the_boll>().boll_fly(attack, true, true);
        }
        else
        {
            left_boll.GetComponent<SpriteRenderer>().sprite = bolls[right_slime.GetComponent<slime>().index_of_slime].GetComponent<SpriteRenderer>().sprite;
            left_boll.SetActive(true);
            left_boll.GetComponent<the_boll>().boll_fly(attack, true, true);
        }
    }
    void dark_combo(GameObject skill, int attack, bool side)
    {
        skill.SetActive(true);
        skill.GetComponent<dark_combo>().show(attack, side);
    }
    void edit_dark(GameObject the_boll)
    {
        the_boll.GetComponent<SpriteRenderer>().sprite = bolls[4].GetComponent<SpriteRenderer>().sprite;
    }
    void girl_combo(GameObject skill, int attack, bool side, ref int index_of_girl)
    {
        if (skill.activeInHierarchy)
        {
            skill.SetActive(false);
            remove_effect(index_of_girl, side);
        }
        index_of_girl = add_effect(good_combo[5].GetComponent<SpriteRenderer>().sprite, side);
        skill.SetActive(true);
        skill.GetComponent<girl_combo>().show(index_of_girl, side, attack);       
    }
    public void remove_girl(int index_of_girl, bool side)
    {
        remove_effect(index_of_girl, side);
    }
    void white_passive(GameObject skill, ref int index_of_white, bool side)
    {
        if (index_of_white != -1) remove_effect(index_of_white, side);
        index_of_white = add_effect(skill.GetComponent<SpriteRenderer>().sprite, side);
    }
    void white_combo(bool side)
    {
        int new_index = UnityEngine.Random.Range(0, 5);
        if (side)
        {
            right_passive_index = new_index;
            white_passive(good_passive[new_index],ref right_indexes_of_skills[6], side);
            right_combo = true;
            right_index_of_slime = new_index;
            right_combos(true);
        }
        else
        {
            left_passive_index = new_index;
            white_passive(good_passive[new_index], ref left_indexes_of_skills[6], side);
            left_combo = true;
            left_index_of_slime = new_index;
            left_combos(true);
        }
    }
    void edit_white(ref int index_of_slime, GameObject the_boll)
    {
        index_of_slime = 6;
        the_boll.GetComponent<SpriteRenderer>().sprite = bolls[6].GetComponent<SpriteRenderer>().sprite;
    }
    public bool edit_girl(bool side, int damage)
    {
        if(side)
        {
            if(right_girl_combo_skill.activeInHierarchy)
            {
                right_girl_combo_skill.GetComponent<girl_combo>().getting_damage(damage);
                return true;
            }
            return false;
        }
        if (left_girl_combo_skill.activeInHierarchy)
        {
            left_girl_combo_skill.GetComponent<girl_combo>().getting_damage(damage);
            return true;
        }
        return false;
    }
    IEnumerator add_passive_skill(GameObject skill, bool side)
    {
        int index_of_passive;
        index_of_passive = add_effect(skill.GetComponent<SpriteRenderer>().sprite, side);
        yield return new WaitForSeconds(1.5f);
        remove_effect(index_of_passive, side);
        StopCoroutine("add_passive_skill");
    }
    void fire_passive(GameObject enemy_slime, GameObject skill, bool combo, bool side)
    {
        if (combo)
        {
            StartCoroutine(add_passive_skill(skill, side));
            enemy_slime.GetComponent<slime>().getting_damage(2);
        }
    }
    void water_passive(GameObject the_slime, GameObject skill, int enemy_hp, bool side)
    {
        if (the_slime.GetComponent<slime>().hp < enemy_hp)
        {
            StartCoroutine(add_passive_skill(skill, side));
            the_slime.GetComponent<slime>().getting_hp(1);
        }
    }
    void poison_passive(GameObject skill, bool side, bool enemy_combo, ref int number_of_poison)
    {
        if ((enemy_combo)&&(number_of_poison > 0))
        {
            StartCoroutine(add_passive_skill(skill, side));
            number_of_poison++;
        }
    }
    void wood_passive(bool side, bool enemy_combo, ref int[] wood_indexes, ref int number_of_leaf)
    {
        if (enemy_combo)
        {
            add_leaf(1, side, ref wood_indexes);
            number_of_leaf++;
            if (!side)
            {
                right_edit_combos();
            }
            else
            {
                left_edit_combos();
            }
        }       
    }
    void girl_passive(GameObject enemy_slime, GameObject skill, int the_attack, int enemy_attack, bool side)
    {
        if (the_attack < enemy_attack)
        {
            StartCoroutine(add_passive_skill(skill, side));
            enemy_slime.GetComponent<slime>().getting_damage(1);
        }
    }
    void left_passive_for_combo()
    {
        switch (left_passive_index)
        {
            case 0:
                fire_passive(right_slime, bad_passive[0], late_right_combo, true);
                break;
            case 2:
                poison_passive(bad_passive[2], true, late_right_combo, ref left_number_of_poison);
                break;
            case 3:
                wood_passive(true, late_right_combo, ref left_wood_indexes, ref left_number_of_leaf);
                break;
            default: return;
        }
        late_right_combo = false;
    }
    void left_passive()
    {
        switch (left_passive_index)
        {
            case 1:
                water_passive(left_slime, good_passive[1], right_slime.GetComponent<slime>().hp, false);
                break;
            case 5:
                girl_passive(right_slime, bad_passive[5], left_attack, right_attack, true);
                break;
            default: return;
        }
    }
    void right_passive_for_combo()
    {
        switch (right_passive_index)
        {
            case 0:
                fire_passive(left_slime, bad_passive[0], late_left_combo, false);
                break;
            case 2:
                poison_passive(bad_passive[2], false, late_left_combo, ref right_number_of_poison);
                break;
            case 3:
                wood_passive(false, late_left_combo, ref right_wood_indexes, ref right_number_of_leaf);
                break;
            default: return;
        }
        late_left_combo = false;
    }
    void right_passive()
    {
        switch (right_passive_index)
        {
            case 1:
                water_passive(right_slime, good_passive[1], left_slime.GetComponent<slime>().hp, true);
                break;
            case 5:
                girl_passive(left_slime, bad_passive[5], right_attack, left_attack, false);
                break;
            default: return;
        }
    }
    void left_edit_combos()
    {       
        edit_wood(left_big_skill, right_wood_combo_skill, ref left_indexes_of_skills[3], ref left_wood_indexes, true, ref left_number_of_leaf);
        edit_poison(right_poison_combo_skill, ref left_poison_attack, ref left_number_of_poison, true, left_indexes_of_skills[2]);
        if (left_slime.GetComponent<slime>().index_of_slime == 4) edit_dark(left_boll);
        if (left_slime.GetComponent<slime>().index_of_slime == 6) edit_white(ref left_index_of_slime, left_boll);
    }
    void right_edit_combos()
    {
        edit_wood(right_big_skill, left_wood_combo_skill, ref right_indexes_of_skills[3], ref right_wood_indexes, false, ref right_number_of_leaf);
        edit_poison(left_poison_combo_skill, ref right_poison_attack, ref right_number_of_poison, false, right_indexes_of_skills[2]);
        if (right_slime.GetComponent<slime>().index_of_slime == 4) edit_dark(right_boll);
        if (right_slime.GetComponent<slime>().index_of_slime == 6) edit_white(ref right_index_of_slime, right_boll);
    }
    public void left_skills(bool edit)
    {
        if (left_big_skill.activeInHierarchy)
        {
            left_big_skill.SetActive(false);
        }
        switch (left_index_of_slime)
        {
            case 0:
                fire_combo(left_boll, left_attack);
                break;
            case 1:
                water_combo(left_water_combo_skill, left_attack);
                break;
            case 2:
                poison_combo(right_poison_combo_skill, left_attack, ref left_poison_attack, ref left_number_of_poison, true, ref left_indexes_of_skills[left_index_of_slime]);
                break;
            case 3:
                wood_combo(left_attack, ref left_wood_indexes, true, ref left_number_of_leaf);
                break;
            case 4:
                dark_combo(left_dark_combo_skill, right_attack, false);
                break;
            case 5:
                girl_combo(left_girl_combo_skill, right_attack, false, ref left_indexes_of_skills[left_index_of_slime]);
                break;
            case 6:
                white_combo(false);
                break;
        }
        if (edit)
        {
            right_passive_for_combo();
            left_edit_combos();         
        }
    }
    public void left_combos(bool edit)
    {
        if (left_combo)
        {
            left_combo = false;
            late_left_combo = true;
            if (left_index_of_slime == 3)
            {
                left_big_skill.GetComponent<SpriteRenderer>().sprite = good_passive[left_index_of_slime].GetComponent<SpriteRenderer>().sprite;
            }
            else
            {
                left_big_skill.GetComponent<SpriteRenderer>().sprite = good_combo[left_index_of_slime].GetComponent<SpriteRenderer>().sprite;
            }
            left_big_skill.SetActive(true);
            if (left_index_of_slime == 6) edit = false;
            left_big_skill.GetComponent<skill>().show(false, true, edit);
        }
        else
        {
            right_passive_for_combo();
            left_edit_combos();
        }
    }
    public void right_skills(bool edit)
    {
        if (right_big_skill.activeInHierarchy)
        {
            right_big_skill.SetActive(false);
        }
        switch (right_index_of_slime)
        {
            case 0:
                fire_combo(right_boll, right_attack);
                break;
            case 1:
                water_combo(right_water_combo_skill, right_attack);
                break;
            case 2:
                poison_combo(left_poison_combo_skill, right_attack, ref right_poison_attack, ref right_number_of_poison, false, ref right_indexes_of_skills[right_index_of_slime]);
                break;
            case 3:
                wood_combo(right_attack, ref right_wood_indexes, false, ref right_number_of_leaf);
                break;
            case 4:
                dark_combo(right_dark_combo_skill, left_attack, true);
                break;
            case 5:
                girl_combo(right_girl_combo_skill, left_attack, true, ref right_indexes_of_skills[right_index_of_slime]);
                break;
            case 6:
                white_combo(true);
                break;
        }
        if (edit)
        {
            left_passive_for_combo();
            right_edit_combos();
        }
    }
    public void right_combos(bool edit)
    {
        if (right_combo)
        {
            right_combo = false;
            late_right_combo = true;
            if (right_index_of_slime == 3)
            {
                right_big_skill.GetComponent<SpriteRenderer>().sprite = good_passive[right_index_of_slime].GetComponent<SpriteRenderer>().sprite;
            }
            else
            {
                right_big_skill.GetComponent<SpriteRenderer>().sprite = good_combo[right_index_of_slime].GetComponent<SpriteRenderer>().sprite;
            }
            right_big_skill.SetActive(true);
            if (right_index_of_slime == 6) edit = false;
            right_big_skill.GetComponent<skill>().show(true, true, edit);
        }
        else
        {
            left_passive_for_combo();
            right_edit_combos();
        }
    }
    void left_hit()
    {
        left_boll.SetActive(true);
        left_boll.GetComponent<the_boll>().boll_fly(left_attack, false, false);
    }
    void right_hit()
    {
        right_boll.SetActive(true);
        right_boll.GetComponent<the_boll>().boll_fly(right_attack, false, true);
    }
    public void start_fight(bool side)
    {
        if (side) right_hit();
        else left_hit();
    }
    void apped_file()
    {
        FileStream create = new FileStream(path_of_victory, FileMode.Create);
        create.Close();
        FileStream file = new FileStream(path_of_victory, FileMode.Append);
        StreamWriter writer = new StreamWriter(file);
        if (left_die && !right_die)
        {
            writer.WriteLine("Winner=" + right_nickname);
        }
        if (!left_die && right_die)
        {
            writer.WriteLine("Winner=" + left_nickname);
        }
        if (left_die && right_die)
        {
            writer.WriteLine("Draw");
        }
        writer.Close();
    }
    IEnumerator the_die(bool left_die, bool right_die)
    {
        yield return new WaitForSeconds(1f);
        apped_file();
        yield return new WaitForSeconds(1.5f);
        StopCoroutine("the_die");
        SceneManager.LoadScene(name_of_scene, LoadSceneMode.Single);        
    }
    void clear_effects(bool side)
    {
        for(int i = 1; i < number_of_icons; i++)
        {
            remove_effect(i, side);
        }
        if(side)
        {
            left_number_of_leaf = 0;
            left_number_of_poison = 0;
            for(int i = 0; i < number_of_skills; i++)
            {
                right_indexes_of_skills[i] = -1;
            }
            for(int i = 0; i < 3; i++)
            {
                right_wood_indexes[i] = -1;
            }
        }
        else
        {
            right_number_of_leaf = 0;
            right_number_of_poison = 0;
            for (int i = 0; i < number_of_skills; i++)
            {
                left_indexes_of_skills[i] = -1;
            }
            for (int i = 0; i < 3; i++)
            {
                left_wood_indexes[i] = -1;
            }
        }
    }
    void can_click()
    {
        round++;
        round_text.text = round.ToString();
        if (left_slime.GetComponent<slime>().hp <= 0)
        {
            left_die = true;
            bool rise_again = false;
            if ((left_index_of_slime == 4) && (left_dark_again_life))
            {
                rise_again = true;
                left_dark_again_life = false;
                left_die = false;
                clear_effects(false);
            }
            left_slime.GetComponent<slime>().set_die(rise_again);
        }
        if (right_slime.GetComponent<slime>().hp <= 0)
        {
            right_die = true;
            bool rise_again = false;
            if ((right_index_of_slime == 4) && (right_dark_again_life))
            {
                rise_again = true;
                right_dark_again_life = false;
                right_die = false;
                clear_effects(true);
            }
            right_slime.GetComponent<slime>().set_die(rise_again);
        }
        if(left_die || right_die)
        {
            left_can_click = false;
            right_can_click = false;
            StartCoroutine(the_die(left_die, right_die));
        }
        if (left_can_click)
        {
            left_click_text.SetActive(true);
            left_time_slider.SetActive(true);
            left_time_slider.GetComponent<time_slider>().start_time();
            left_click.GetComponent<click>().is_clicked = false;
        }
        else no_click = true;
        if (right_can_click)
        {
            right_click_text.SetActive(true);
            right_time_slider.SetActive(true);
            right_time_slider.GetComponent<time_slider>().start_time();
            right_click.GetComponent<click>().is_clicked = false;
            if(is_bot) game_bot();
        }
        else no_click = true;
    }
    IEnumerator check_combo()
    {
        float left_wait = 0.25f;
        float right_wait = 0.25f;
        yield return new WaitForSeconds(0.1f);
        if (left_combo) left_wait = 0.25f;
        else left_wait = 0f;
        left_combos(true);
        yield return new WaitForSeconds(left_wait);
        if (right_combo) right_wait = 0.25f;
        else right_wait = 0f;
        right_combos(true);
        yield return new WaitForSeconds(right_wait);
        left_passive();
        right_passive();
        if (left_number_of_poison > 0) left_wait = 0.3f;
        if (right_number_of_poison > 0) right_wait = 0.3f;
        if ((right_wood_combo_skill.activeInHierarchy) && (left_wood_combo_skill.activeInHierarchy))
        {
            left_edit_combos();
            right_edit_combos();
        }
        yield return new WaitForSeconds(0.6f + 8*left_wait + 8*right_wait);
        can_click();
        StopCoroutine("check_combo");
    }
    public void finish_fight(bool side)
    {
        if(!no_click)
        {
            if (side) left_hit();
            else right_hit();
            no_click = true;
        }
        else
        {
            no_click = false;
            left_boll.SetActive(false);
            right_boll.SetActive(false);
            StartCoroutine("check_combo");
        }
    }
}
