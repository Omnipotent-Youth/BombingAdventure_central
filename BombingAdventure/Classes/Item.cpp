//
// Created by Brando Zhang on 2018/5/17.
//

#include "Item.h"

Item::Item() {
    /* Default attributes of a new item     */
    item_id = floor(CCRANDOM_0_1() * sizeof(items));
    /* Default view of a new item         */
    bind_sprite(Sprite::create("item_0.png"));
    this->setAnchorPoint(Vec2(0.5,0.5));
}
Item::~Item() {
    /* Not yet  */
}
bool Item::init() {
    return true;
}
int Item::get_item_id() {
    return item_id;
}