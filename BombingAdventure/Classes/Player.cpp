//
// Created by Brando Zhang on 2018/5/4.
//

#include "GameScene.h"
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
    if (get_sprite() != NULL) {
        return num_present_bombs < num_max_available_bombs;
    }
    return false;
}

bool Player::is_alive() {
    if (get_sprite() != NULL) {
        return HP > 0;
    }
    return false;
}

float Player::get_moving_speed() {
    if (get_sprite() == NULL) return -1;
    return moving_speed;
}
int Player::get_x_movement() {
    return x_movement;
}
int Player::get_y_movement() {
    return y_movement;
}
int Player::get_HP() {
    if (get_sprite() == NULL) return -1;
    return HP;
}

int Player::get_num_available_bombs() {
    if (get_sprite() == NULL) return -1;
    return num_max_available_bombs - num_present_bombs;
}

Bomb* Player::set_bomb() {
    if (get_sprite() == NULL) return NULL;
    Bomb * bomb = Bomb::create();
	
	Vec2 player_tile_coord = tileCoordFromPosition(Vec2(this->getPosition().x, this->getPosition().y - this->getContentSize().height / 3));

	bomb->setPosition(Vec2(player_tile_coord.x*TILE_SIZE.width + TILE_SIZE.width / 2,
		(MAP_SIZE.height - player_tile_coord.y)*TILE_SIZE.height - TILE_SIZE.height / 2));

	this->getParent()->addChild(bomb);
	bomb->setGlobalZOrder(0);

    ++(this->num_present_bombs);

    bomb->startCounting(2.5f);

	--(this->num_present_bombs);
	
	return bomb;
}

void Player::pick_item(Item & item) {
    if (get_sprite() == NULL) return;   /* Avoid strange things happened :) */
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

void Player::bomb_vs_man(Vec2 bomb_tile_coord, int l, int r, int u, int d)
{
	Vec2 player_tile_coord = tileCoordFromPosition(this->getPosition());
	for (int i = bomb_tile_coord.x - l; i <= bomb_tile_coord.x + r; i++) {
		if (player_tile_coord == Vec2(i, bomb_tile_coord.y)) {
			this->injured();
		}
	}
	for (int j = bomb_tile_coord.y - d; j <= bomb_tile_coord.y + u; j++) {
		if (player_tile_coord == Vec2(bomb_tile_coord.x, j)) {
			this->injured();
		}
	}
}

void Player::injured(int deduct_HP) {
    if (get_sprite() != NULL) {
        HP -= deduct_HP;
        if (HP < 0) {
            HP = 0;
        }
    }
}