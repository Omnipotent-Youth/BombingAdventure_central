//
// Created by Brando Zhang on 2018/5/19.
//

#include "ItemController.h"

bool ItemController::init() {
    /* Get current time to initialize a random seed     */
    timeval now;
    gettimeofday(&now, NULL);
    auto seed = (unsigned) (now.tv_sec * 1000 + now.tv_usec / 1000);
    srand(seed);

    create_item();
    /* Enable update    */
    this->scheduleUpdate();
    return true;
}
void ItemController::update(float delta) {

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