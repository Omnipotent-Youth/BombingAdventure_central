//
// Created by Brando Zhang on 2018/5/15.
//

#ifndef MYGAME_ENTITY_H
#define MYGAME_ENTITY_H
#include "cocos2d.h"

USING_NS_CC;

/* Following are the attributes of entity    */
const Size ENTITY_DEFAULT_SIZE = Size(40, 40);

class Entity : public Node {
public:
    Entity();
    ~Entity();
    Sprite* get_sprite();                   /* Get the sprite of this entity        */
    void bind_sprite(Sprite* sprite);       /* Bind to sprite object                */
    virtual void reset_position();          /* Reset the position of this entity    */
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);

private:
    Sprite* entity_sprite;                  /* Every entity has at least one sprite */
};

#endif //MYGAME_ENTITY_H
