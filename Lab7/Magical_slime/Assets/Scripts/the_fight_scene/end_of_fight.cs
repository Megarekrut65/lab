using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using System.IO;

public class end_of_fight : MonoBehaviour
{
    public GameObject victory;
    public GameObject defeat;
    public string player_left_path;
    public string player_right_path;
    public string date_path;
    public string new_date_path;
    public string account_path;
    public string victory_path;
    private string nickname_of_winner;
    public Text game_text;
    public Text info_text;
    private string[] left_player;
    private string[] right_player;
    private const int number_of_items = 3;
    private int points_of_player = 0;
    private int coins_of_player = 0;
    private bool is_draw = false;

    void read_file(string path, ref string[] player)
    {
        FileStream file = new FileStream(path, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        string[] items = new string[] { "Nickname=", "Points=", "Element=" };
        int[] sizes = new int[] { 9, 7, 8 };
        for (int i = 0; i < number_of_items; i++)
        {           
            string temp = reader.ReadLine();
            if ((temp.Length > sizes[i]) 
                && (temp.Substring(0, sizes[i]) == items[i])) player[i] = temp.Substring(sizes[i]);
        }
        reader.Close();
    }
    void read_victory()
    {
        FileStream file = new FileStream(victory_path, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        if(reader.EndOfStream)
        {
            nickname_of_winner = "";
            file.Close();
            return;
        }
        nickname_of_winner = reader.ReadLine();
        if (nickname_of_winner == "Draw")
        {
            is_draw = true;
        }
        else nickname_of_winner = nickname_of_winner.Substring(7);
        file.Close();
        File.Delete(victory_path);
    }
    void calculate_the_prize(string[] winner, string[] loser)
    {
        points_of_player = 0;
        int winner_points = Convert.ToInt32(winner[1]);
        int loser_points = Convert.ToInt32(loser[1]);
        if (winner_points > loser_points)
        {
            points_of_player = 10 + 6 / (winner_points - loser_points) + UnityEngine.Random.Range(1, 5);
        }
        else
        {
            points_of_player = 15 + (loser_points - winner_points) / 10 + UnityEngine.Random.Range(2, 10);
        }
        coins_of_player = UnityEngine.Random.Range(points_of_player * 5 - 1, points_of_player * 10 + 1);
    }
    void calculate_the_losses()
    {
        points_of_player = points_of_player / 3;
        coins_of_player = coins_of_player / 10;
    }
    void set_winner(string[] winner, string[] loser)
    {
        game_text.text = "Victory!";
        info_text.text = "Congratulations on your victory, " + winner[0] + ".\n\n" +
            loser[0] + " was your enemy and you destroyed him!\n\n" +
            "For winning you get " + points_of_player.ToString() +
            " points and " + coins_of_player.ToString() + " coins.";
    }
    void set_draw(string[] left_player, string[] right_player)
    {
        points_of_player -= 5;
        coins_of_player -= 10;
        game_text.text = "Victory!";
        info_text.text = "Congratulations on your draw, " + left_player[0] + ".\n\n" +
            right_player[0] + " was your enemy.\n\n"+
            "You fought hard, but your strength was equal.\n\n" +
            "For the draw you get " + points_of_player.ToString() +
            " points and " + coins_of_player.ToString() + " coins.";
    }
    void set_loser(string[] loser, string[] winner)
    {
        game_text.text = "Defeat!";
        info_text.text = "Sorry but you lost, " + loser[0] + ".\n\n" +
            winner[0] + " was your enemy and you couldn't defeat him!\n\n" +
            "You get " + coins_of_player.ToString() + " coins and lose " + points_of_player.ToString() + " points.";
    }   
    void append_to_file(string path, string[] date, int size)
    {
        FileStream file = new FileStream(path, FileMode.Append);
        StreamWriter writer = new StreamWriter(file);
        for(int i = 0; i < size; i++)
        {
            writer.WriteLine(date[i]);
        }
        writer.Close();
    }
    void add_to_account_file(string path, string[] date, int size)
    {
        FileStream file = new FileStream(path, FileMode.OpenOrCreate);
        StreamWriter writer = new StreamWriter(file);
        for (int i = 0; i < size; i++)
        {
            writer.WriteLine(date[i]);
        }
        writer.Close();
    }
    void save_date(string[] player, bool is_winner)
    {
        FileStream file = new FileStream(date_path, FileMode.OpenOrCreate);
        StreamReader reader = new StreamReader(file);
        while (!reader.EndOfStream)
        {
            const int number_of_rows = 6;
            string[] temp_player = new string[number_of_rows];
            for(int i = 0; i < number_of_rows; i++)
            {
                temp_player[i] = reader.ReadLine();
            }
            if (temp_player[0] == player[0])
            {
                if(is_winner) points_of_player += Convert.ToInt32(temp_player[3].Substring(7));
                else points_of_player = Convert.ToInt32(temp_player[3].Substring(7)) - points_of_player;
                if (points_of_player < 0) points_of_player = 0;
                temp_player[3] = "Points=" + points_of_player.ToString();
                coins_of_player += Convert.ToInt32(temp_player[4].Substring(6));
                temp_player[4] = "Coins=" + coins_of_player.ToString();
                append_to_file(new_date_path, temp_player, number_of_rows);
                add_to_account_file(account_path, temp_player, number_of_rows);
            }
            else
            {
                append_to_file(new_date_path, temp_player, number_of_rows);
            }
        }
        reader.Close();
        File.Delete(date_path);
        File.Move(new_date_path, date_path);
    }
    void Start()
    {
        left_player = new string[number_of_items];
        right_player = new string[number_of_items];
        read_file(player_left_path, ref left_player);
        read_file(player_right_path, ref right_player);
        read_victory();
        bool is_winer = false;
        if ((nickname_of_winner == left_player[0])||is_draw)
        {
            is_winer = true;
            calculate_the_prize(left_player, right_player);
            if(is_draw) set_draw(left_player, right_player);
            else set_winner(left_player, right_player);
        }
        else if(nickname_of_winner == right_player[0])
        {
            calculate_the_prize(left_player, right_player);
            calculate_the_losses();
            set_loser(left_player, right_player);
        }
        else
        {
            set_winner(left_player, right_player);
        }
        left_player[0] = "Nickname=" + left_player[0];
        save_date(left_player, is_winer);
    }
}
