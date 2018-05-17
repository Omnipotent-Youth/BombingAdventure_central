//
// Created by Brando Zhang on 2018/5/15.
//

#include "Entity.h"

Entity::Entity() {
    entity_sprite = NULL;
}

Entity::~Entity() {

}
Sprite* Entity::get_sprite() {
    return this->entity_sprite;
}
void Entity::bind_sprite(Sprite *sprite) {

    this->entity_sprite = sprite;
    this->addChild(entity_sprite);
}
const Size& Entity::getContentSize() {
    return this->get_sprite()->getContentSize();

}