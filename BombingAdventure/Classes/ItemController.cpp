//
// Created by Brando Zhang on 2018/5/19.
//

#include "ItemController.h"

bool ItemController::init() {
    /* Get current time to initialize a random seed     */
//    timeval now;
//    gettimeofday(&now, NULL);
//    auto seed = (unsigned) (now.tv_sec * 1000 + now.tv_usec / 1000);
//    srand(seed);

    create_item();
    /* Enable update    */
    this->scheduleUpdate();
    return true;
}
void ItemController::update(float delta) {
    for (Item * item : current_item_vector) {
        /* Check whether this item is picked by the monitored player    */
        if (is_picked(item)) {
            monitored_player->pick_item(*item);
            item->removeAllChildren();
            item->removeFromParent();
            current_item_vector.eraseObject(item);
            log("Item is removed.");
        }
    }
}
void ItemController::create_item() {
    for (int i = 0; i < NUM_ITEMS; i++) {

        /* Create NUM_ITEMS items */
        Item * item = Item::create();
        item->reset_position();

        /* Make the item under the control of ItemController  */
        this->addChild(item);
        current_item_vector.pushBack(item);
    }
}
void ItemController::bind_player(Player *player) {
    monitored_player = player;
}
bool ItemController::is_picked(Item *item) {
    /* Get the bounding box of the player   */
    Rect player_bounding_box = monitored_player->getBoundingBox();
    Vec2 item_position = item->getPosition();
    /* Check whether the player and the item has intersection   */
    item->is_picked = player_bounding_box.containsPoint(item_position);
    return item->is_picked;
}