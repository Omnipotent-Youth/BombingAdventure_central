//
// Created by Brando Zhang on 2018/5/16.
//

#ifndef BOMBING_ADVENTURE_MONSTER_H
#define BOMBING_ADVENTURE_MONSTER_H

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;
//enum direction { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

/* Following are the attributes of Monster   */
const int MONSTER_DEFAULT_HP = 2;
const int MONSTER_DEFAULT_AVAILABLE_BOMBS = 10;
const float MONSTER_DEFAULT_MOVING_SPEED = 8.0f;

class Monster : public Player {
public:
    /* Constructor  */
    Monster();
    /* Destructor   */
    ~Monster();

    CREATE_FUNC(Monster);

    /* Initiate Method  */
    virtual bool init();

    bool collided_with(Player * player);

    /* Method: get_new_direction */
    int get_new_direction();

    /* Method: move_forward  */
//    void move_forward(int new_direction);


private:
    enum direction { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

};

#endif //BOMBING_ADVENTURE_MONSTER_H
