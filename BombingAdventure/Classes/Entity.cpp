//
// Created by Brando Zhang on 2018/5/15.
//

#include "Entity.h"
#include "GameScene.h"

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

    /* Reset the content size and fit the mid-points    */
	Size entity_size = entity_sprite->getContentSize();
	entity_sprite->setAnchorPoint(Vec2(0.5,0.5));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	entity_sprite->setPosition(Vec2(entity_size.width * 0.5f, entity_size.height * 0.5f));
	this->setContentSize(entity_size);

}
void Entity::reset_position() {
    if(get_sprite() != NULL) {
        /* Generate a position in unit Tile     */
        int target_tile_x = (int) floor(CCRANDOM_0_1() * MAP_SIZE.width);
        int target_tile_y = (int) floor(CCRANDOM_0_1() * MAP_SIZE.height);
        /* Set to the position in unit pixel, did not add robust part   */
        setPosition(Vec2(target_tile_x * TILE_SIZE.width + TILE_SIZE.width / 2, target_tile_y * TILE_SIZE.height + TILE_SIZE.height / 2));
    }
}
Vec2 Entity::tileCoordFromPosition(Vec2 position)
{
	int x = position.x / TILE_SIZE.width;
	int y = ((MAP_SIZE.height * TILE_SIZE.height) - position.y) / TILE_SIZE.height;
	return Vec2(x, y);
}
