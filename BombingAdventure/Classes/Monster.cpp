//
// Created by Brando Zhang on 2018/5/16.
//
#include "Monster.h"

Monster::Monster() {
    /* Avoid inheriting unnecessary children from superclass    */
    this->removeAllChildren();

    /* Default attributes of a new monster   */
    HP = MONSTER_DEFAULT_HP;
    moving_speed = MONSTER_DEFAULT_MOVING_SPEED;
    num_max_available_bombs = MONSTER_DEFAULT_AVAILABLE_BOMBS;
    num_present_bombs = 0;

    /* Default view of a new monster         */
    bind_sprite(Sprite::create("stone_monster.png"));
    this->setAnchorPoint(Vec2(0.5,0.5));
}
Monster::~Monster() {
    /* Not yet  */
}
bool Monster::init() {
    return true;
}
int Monster::get_new_direction() {
    int new_direction = floor(CCRANDOM_0_1() * 4);
    return new_direction;
}
//void Monster::move_forward(int new_direction) {
//    step = CCRANDOM_0_1() * 100;
//    switch (new_direction) {
//        case MOVE_UP:
//
//    }
//}