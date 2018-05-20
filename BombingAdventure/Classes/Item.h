//
// Created by Brando Zhang on 2018/5/17.
//

#ifndef BOMBING_ADVENTURE_ITEM_H
#define BOMBING_ADVENTURE_ITEM_H

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

/* Following are the attributes of items    */
const int ITEM_CURE_BY = 1;
const int ITEM_ADD_BOMBS_BY = 1;
const float ITEM_SPEED_UP_BY = 2.f;

class Item : public Entity {
public:
    /*  Constructor */
    Item();

    /*  Desructor   */
    ~Item();

    CREATE_FUNC(Item);

    /* Initiate Method  */
    virtual bool init();

    int get_item_id();

    enum items {POWER_UP, SPEED_UP, HP_UP, NUM_BOMBS_UP};

    /* Mark whether this item is picked */
    bool is_picked;

private:
    int item_id;
};

#endif //BOMBING_ADVENTURE_ITEM_H
