//
// Created by Brando Zhang on 2018/5/4.
//

#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include "cocos2d.h"
#include "Entity.h"
//#include "Bomb.h"

USING_NS_CC;

/* Following are the attributes of player   */
const int DEFAULT_HP = 3;
const int DEFAULT_AVAILABLE_BOMBS = 3;
const float DEFAULT_MOVING_SPEED = 3.0f;


class Player : public Entity {
public:
    /*  Constructor */
    Player();

    /*  Desructor   */
    ~Player();

    CREATE_FUNC(Player);

    /* Initiate Method  */
    virtual bool init();

    /* Method: set_bomb
     * Usage: Player->set_bomb();
     * --------------------------
     * Set a bomb on the current position.
     */
    void set_bomb();
//  View

//  Models

    /* Method: get_HP
     * Usage: int HP = Player->get_HP;
     * --------------------------
     * Get the HP of the Player.
     * If HP equals to 0, then game is over.
     */
    int get_HP();

    /* Method: get_num_available_bombs
     * Usage: int available_bombs = Player->get_num_available_bombs();
     * ---------------------------------------------------------------
     * Get the number of available bombs which can be set by the Player.
     */
    int get_num_available_bombs();

    /* Method: can_set_bomb
     * Usage: if (Player->can_set_bomb()) do...
     * ----------------------------------------
     * Return true if player can set bombs.
     */
    bool can_set_bomb();

    /* Method: get_moving_speed
     * Usage: float moving_speed = Player->get_moving_speed();
     * -------------------------------------------------------
     * Get the moving speed of the player.
     */
    float get_moving_speed();



private:
//    Instance variables
    //  Models
    int HP;
    float moving_speed;
    int num_max_available_bombs;
    int num_present_bombs;
//    int cool_down_time;
//    void set_HP(int new_HP);
//    void set_moving_speed(int new_speed);
//    void set_cool_down_time(int new_time);
//
//    Label* player_name = Label::create("Player1", "Arial", 24);
};

#endif //MYGAME_PLAYER_H
