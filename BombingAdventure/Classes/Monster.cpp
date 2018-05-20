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
    this->setAnchorPoint(Vec2(0.35, 0.25));
}
Monster::~Monster() {
    /* Not yet  */
}
bool Monster::init() {
    return true;
}
int Monster::get_new_direction() {
    int new_direction = (int) floor(CCRANDOM_0_1() * 4);
    return new_direction;
}
void Monster::make_new_direction() {
    auto new_direction = get_new_direction();
    switch (new_direction) {
        case direction::MOVE_UP:
            y_movement = MOVE_SIGNAL_Y::MOVE_UP;
            break;
        case direction::MOVE_DOWN:
            y_movement = MOVE_SIGNAL_Y::MOVE_DOWN;
            break;
        case direction::MOVE_RIGHT:
            x_movement = MOVE_SIGNAL_X::MOVE_RIGHT;
            break;
        case direction::MOVE_LEFT:
            x_movement = MOVE_SIGNAL_X::MOVE_LEFT;
            break;
        default:
            x_movement = MOVE_SIGNAL_X::MOVE_STOP_X;
            y_movement = MOVE_SIGNAL_Y::MOVE_STOP_Y;
            break;
    }
}
//void Monster::move_forward(int new_direction) {
//    switch (new_direction) {
//        case MOVE_UP:
//
//
//    }
//}
bool Monster::collided_with(Player * player) {
    /* Get the bounding box of the player   */
    Rect player_bounding_box = player->getBoundingBox();
    Vec2 monster_position = this->getPosition();
    /* Check whether the player and the monster has intersection   */
    bool is_collided = player_bounding_box.containsPoint(monster_position);
    return is_collided;
}
