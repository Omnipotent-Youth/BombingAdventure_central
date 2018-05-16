//
// Created by Brando Zhang on 2018/5/4.
//

#include "Player.h"
USING_NS_CC;

Player::Player() {
    /* Default attributes of a new player   */
    HP = DEFAULT_HP;
    moving_speed = DEFAULT_MOVING_SPEED;
    num_max_available_bombs = DEFAULT_AVAILABLE_BOMBS;
    num_present_bombs = 0;
    /* Default view of a new player         */
            bind_sprite(Sprite::create("player/player-front.png"));
            this->setAnchorPoint(Vec2(0.5,0.5));
}
Player::~Player() {
    /* Not yet  */
}
bool Player::init() {
    return true;
}
bool Player::can_set_bomb() {
    return num_present_bombs < num_max_available_bombs;
}
float Player::get_moving_speed() {
    return moving_speed;
}
int Player::get_HP() {
    return HP;
}
int Player::get_num_available_bombs() {
    return num_max_available_bombs - num_present_bombs;
}
void Player::set_bomb() {
    Sprite* bomb = Sprite::create("blue_bomb.png");
    bomb->setPosition(this->getPosition());
    this->getParent()->addChild(bomb);
    ++(this->num_present_bombs);
}