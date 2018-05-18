//
// Created by Brando Zhang on 2018/5/4.
//

#include "Player.h"

USING_NS_CC;

Player::Player() {
    /* Default attributes of a new player   */
    HP = PLAYER_DEFAULT_HP;
    moving_speed = PLAYER_DEFAULT_MOVING_SPEED;
    num_max_available_bombs = PLAYER_DEFAULT_AVAILABLE_BOMBS;
    num_present_bombs = 0;
    /* Default view of a new player         */
//            std::string player_file_name = "player1_default.png";
//            bind_sprite(Sprite::create(player_file_name));
        bind_sprite(Sprite::create("player1_default.png"));
            this->setAnchorPoint(Vec2(0.5,0.5));
			this->_contentSize = getContentSize();
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
bool Player::is_alive() {
    return HP > 0;
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
    Bomb * bomb = Bomb::create();
    bomb->setPosition(this->getPosition());
    this->getParent()->addChild(bomb);
    
    ++(this->num_present_bombs);

    bomb->startCounting(2.5f);

    --(this->num_present_bombs);
}

void Player::pick_item(Item & item) {
    int item_id = item.get_item_id();
    switch (item_id) {
        case Item::POWER_UP:
            /* Not yet  */
            break;
        case Item::SPEED_UP:
            if (moving_speed < PLAYER_MAX_MOVING_SPEED) {
                this->moving_speed += ITEM_SPEED_UP_BY;
            }
            break;
        case Item::HP_UP:
            if (HP < PLAYER_MAX_HP) {
                this->HP += ITEM_CURE_BY;
            }
            break;
        case Item::NUM_BOMBS_UP:
            this->num_max_available_bombs += ITEM_ADD_BOMBS_BY;
            break;
    }
    log("Pick item.");
    log("Now my speed is %f", moving_speed);
    item.is_picked = true;
}