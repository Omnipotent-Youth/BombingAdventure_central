//
// Created by Brando Zhang on 2018/5/19.
//

#ifndef BOMBING_ADVENTURE_ITEMCONTROLLER_H
#define BOMBING_ADVENTURE_ITEMCONTROLLER_H

#include "cocos2d.h"
#include "Item.h"

USING_NS_CC;

/* Following are the attributes of Item Controller   */
const int NUM_ITEMS = 5;

class ItemController : public Node {
public:
    CREATE_FUNC(ItemController);
    /* Initiate Method  */
    virtual bool init();

    /* Override update method   */
    virtual void update(float delta);
private:
    /* Method: create_item
     * ----------------------
     * Create an item
     */
    void create_item();

    /* Store all the Items   */
    Vector<Item*> current_item_vector;
};

#endif //BOMBING_ADVENTURE_ITEMCONTROLLER_H
