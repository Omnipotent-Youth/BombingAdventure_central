//
// Created by Brando Zhang on 2018/5/15.
//

#ifndef MYGAME_ENTITY_H
#define MYGAME_ENTITY_H
#include "cocos2d.h"

/* Following are the attributes of entity    */
const cocos2d::Size ENTITY_DEFAULT_SIZE = cocos2d::Size(40, 40);

class Entity : public cocos2d::Node {
public:
    Entity();
    ~Entity();
    cocos2d::Sprite* get_sprite();                   /* Get the sprite of this entity        */
    void bind_sprite(cocos2d::Sprite* sprite);       /* Bind to sprite object                */
    virtual void reset_position();          		 /* Reset the position of this entity    */
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);

private:
    cocos2d::Sprite* entity_sprite;                  /* Every entity has at least one sprite */
};

#endif //MYGAME_ENTITY_H
