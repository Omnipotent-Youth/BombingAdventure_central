//
// Created by Brando Zhang on 2018/5/15.
//

#include "Entity.h"

Entity::Entity() {
    entity_spirte = NULL;
}

Entity::~Entity() {

}
Sprite* Entity::get_sprite() {
    return this->entity_spirte;
}
void Entity::bind_sprite(Sprite *sprite) {
    this->entity_spirte = sprite;
    this->addChild(entity_spirte);
}