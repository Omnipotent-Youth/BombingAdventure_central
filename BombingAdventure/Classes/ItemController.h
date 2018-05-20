//
// Created by Brando Zhang on 2018/5/19.
//

#ifndef BOMBING_ADVENTURE_ITEMCONTROLLER_H
#define BOMBING_ADVENTURE_ITEMCONTROLLER_H

#include "cocos2d.h"
#include "Item.h"
#include "Player.h"

USING_NS_CC;

/* Following are the attributes of Item Controller   */
const int NUM_ITEMS = 10;

class ItemController : public Node {
public:
    CREATE_FUNC(ItemController);
    /* Initiate Method  */
    virtual bool init();

    /* Override update method   */
    virtual void update(float delta);

	/* Method: create_item
	* ----------------------
	* Create an item
	*/
	void create_item();

    /* Method: bind_player
     * ----------------------
     * Bind the player to item controller, which
     * enables it to monitor the operation of
     * this player.
     */
    void bind_player(Player * player);

	void bind_bricks_layer(TMXLayer * bricks);

	void bind_destructable_layer(TMXLayer * destructable);

	bool cannot_be_placed(Vec2 pos);

    /* Method: is_picked
     * Usage: if (is_picked(item)) do ...
     * ---------------------------------------
     * Returns true if the bounding box of the player
     * intersects with the position of this item. i.e.
     * The item is picked by the monitored player.
     * It will also set the status of item to is_picked = true.
     */
    bool is_picked(Item * item);

private:

    /* Store all the Items   */
    Vector<Item*> current_item_vector;

    Player * monitored_player = NULL;
	TMXLayer * _bricks = NULL;
	TMXLayer * _destructable = NULL;
};

#endif //BOMBING_ADVENTURE_ITEMCONTROLLER_H
