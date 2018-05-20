//
// Created by Brando Zhang on 2018/5/17.
//

#include "Item.h"
#include "Player.h"

Item::Item() {
    /* Default attributes of a new item     */
    is_picked = false;
    item_id = (int) floor(CCRANDOM_0_1() * sizeof(items));
    /* Default view of a new item           */
	__String *itemName = __String::createWithFormat("Item_%d.png", item_id);
    bind_sprite(Sprite::create(itemName->getCString()));
    this->setAnchorPoint(Vec2(0.5,0.5));
}
Item::~Item() {
    /* Not yet  */
}
bool Item::init() {
    /* Enable update    */
//    this->scheduleUpdate();
    return true;
}
int Item::get_item_id() {
    return item_id;
}
//void Item::update(float delta) {
//    if (get_sprite() == NULL) {
//        return;
//    }
//    if (is_picked) {
//        this->removeAllChildren();
//        this->removeFromParent();
//        log("Item is removed");
//    }
//}
