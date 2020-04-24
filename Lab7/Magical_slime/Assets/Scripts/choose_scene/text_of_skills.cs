using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class text_of_skills : MonoBehaviour
{
    public Text type_of_skill;
    public Text name_of_skill;
    public Text about_skill;

    void combo_fire()
    {
        name_of_skill.text = "Double Meteor";
        about_skill.text = "Fire Slime attacks the enemy twice";
    }
    void combo_water()
    {
        name_of_skill.text = "Water Recovery";
        about_skill.text = "Water Slime regains his health equal to the power of his attack";
    }
    void combo_poison()
    {
        name_of_skill.text = "Deadly Poison";
        about_skill.text = "Poison Slime imposes poison on the enemy. The poison acts three times and deals 50% of the initial damage at each turn.";
    }
    void combo_wood()
    {
        name_of_skill.text = "Wild Nature";
        about_skill.text = "Wood Slime imposes on the enemy the effect of Wild Nature. The number of effects is equal to the damage dealt divided by 4. When the number of effects is 3, the next round the enemy will not be able to attack, and the effects of wildlife will disappear.";
    }
    void combo_dark()
    {
        name_of_skill.text = "Nightmare";
        about_skill.text = "Dark Slime redirects normal attack of enemy.";
    }
    void combo_girl()
    {
        name_of_skill.text = "Defender";
        about_skill.text = "Girl Slime forms a defender. The defender receives damage inflicted by the enemy. The amount of health of the defender is equal to the amount of damage inflicted by the opponent during the activation of the skill. The defender stops absorbing damage only after his health drops below 0. (For example, the defender's health is 1, the enemy deals 6 damage - the defender dies, but the rest of the 5 damage does not apply to the Girl Slime.)";
    }
    void combo_white()
    {
        name_of_skill.text = "All Colors";
        about_skill.text = "White Slime copies any combo skill.";
    }
    void combo_message(int index)
    {
        type_of_skill.text = "Combo skill";
        switch (index)
        {
            case 0: combo_fire();
                break;
            case 1: combo_water();
                break;
            case 2: combo_poison();
                break;
            case 3: combo_wood();
                break;
            case 4: combo_dark();
                break;
            case 5: combo_girl();
                break;
            case 6: combo_white();
                break;
        }
    }
    void passive_fire()
    {
        name_of_skill.text = "Revenge of Fire";
        about_skill.text = "When an enemy activates a combo skill, Fire Slime deals 2 damage his.";
    }
    void passive_water()
    {
        name_of_skill.text = "Water Justice";
        about_skill.text = "If the enemy have more unit of health, Water Slime regains 1 unit himself.";
    }
    void passive_poison()
    {
        name_of_skill.text = "Incurable Wound";
        about_skill.text = "When an enemy activates a combo skill, the poison lasts for another 1 round (if the enemy is already poisoned).";
    }
    void passive_wood()
    {
        name_of_skill.text = "Last Leaf";
        about_skill.text = "When an enemy activates a combo skill, it gets 1 more Wild Nature effects.";
    }
    void passive_dark()
    {
        name_of_skill.text = "Eternal Darkness";
        about_skill.text = "After death, Dark Slime comes to life with 1 health unit, all the negative effects disappear.";
    }
    void passive_girl()
    {
        name_of_skill.text = "Girlish Character";
        about_skill.text = "When the enemy deals more damage, he inflicts 1 damage himself.";
    }
    void passive_white()
    {
        name_of_skill.text = "Achromatism";
        about_skill.text = "Copies passive skill after combos skill are activated.";
    }
    void passive_message(int index)
    {
        type_of_skill.text = "Passive skill";
        switch (index)
        {
            case 0: passive_fire();
                break;
            case 1: passive_water();
                break;
            case 2: passive_poison();
                break;
            case 3: passive_wood();
                break;
            case 4: passive_dark();
                break;
            case 5: passive_girl();
                break;
            case 6: passive_white();
                break;
        }
    }
    public void set_message(int index, bool combo)
    {
        switch(combo)
        {
            case true: combo_message(index);
                break;
            case false: passive_message(index);
                break;
        }
    }
    
}
