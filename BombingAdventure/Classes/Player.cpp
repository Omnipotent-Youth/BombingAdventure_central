//
// Created by Brando Zhang on 2018/5/4.
//

#include "GameScene.h"
#include "Player.h"
#include "Bomb.h"
USING_NS_CC;



Player::Player() {
    /* Default attributes of a new player   */
    HP = PLAYER_DEFAULT_HP;
    moving_speed = PLAYER_DEFAULT_MOVING_SPEED;
    num_max_available_bombs = PLAYER_DEFAULT_AVAILABLE_BOMBS;
    num_present_bombs = 0;
    /* Default view of a new player         */
            bind_sprite(Sprite::create("player/player-front.png"));
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
Bomb* Player::set_bomb() {
    Bomb * bomb = Bomb::create();
	
	Vec2 player_tile_coord = tileCoordFromPosition(Vec2(this->getPosition().x, this->getPosition().y - this->getContentSize().height / 3));

	bomb->setPosition(Vec2(player_tile_coord.x*TILE_SIZE.width + TILE_SIZE.width / 2,
		(MAP_SIZE.height - player_tile_coord.y)*TILE_SIZE.height - TILE_SIZE.height / 2));

    ++(this->num_present_bombs);

    bomb->startCounting(2.5f);

	--(this->num_present_bombs);
	
	return bomb;
}

void Player::set_moving_speed(float new_speed) {
    moving_speed = new_speed;
}
void Player::pick_item(Item & item) {
    int item_id = item.get_item_id();
    switch (item_id) {
        case Item::POWER_UP:
            /* Not yet  */
            break;
        case Item::SPEED_UP:
            this->set_moving_speed(++moving_speed);
            break;
        case Item::HP_UP:
            ++(this->HP);
            break;
        case Item::NUM_BOMBS_UP:
            ++(this->num_max_available_bombs);
            break;
    }
    item.removeFromParent();
}