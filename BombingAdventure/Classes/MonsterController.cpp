//
// Created by Brando Zhang on 2018/5/16.
//

#include "MonsterController.h"
#include "GameScene.h"

bool MonsterController::init() {
    /* Get current time to initialize a random seed     */
    timeval now;
    gettimeofday(&now, NULL);
    auto seed = (unsigned) (now.tv_sec * 1000 + now.tv_usec / 1000);
    srand(seed);

    /* Enable update    */
    this->scheduleUpdate();
    return true;
}

void MonsterController::update(float delta) {
	int count = 0;
	for (auto iter = current_monster_vector.begin(); iter != current_monster_vector.end(); ) {
		Monster *monster = current_monster_vector.at(count);
		if (monster->is_alive()) {
            Vec2 monster_pos_in_pixel = monster->getPosition();
            Vec2 monster_pos_in_tile = monster->tileCoordFromPosition(monster_pos_in_pixel);
			if (monster_pos_in_tile.x < 0 || monster_pos_in_tile.x > 40
                || monster_pos_in_tile.y < 0 || monster_pos_in_tile.y > 40) {
				monster->reset_position();
			}

			if (monster->collided_with(monitored_player)) {
				monitored_player->injured();
				log("The HP of the player is %d", monitored_player->get_HP());
			}
			iter++;
			count++;
		}
		else {
			monster->removeAllChildren();
			monster->removeFromParent();
			iter = current_monster_vector.erase(iter);
			log("Monster is removed.");
		}
    }
}

void MonsterController::create_monster() {
    for (int i = 0; i < NUM_MONSTERS; i++) {

        /* Create NUM_MONSTERS monsters */
        Monster * monster = Monster::create();
		
		monster->reset_position();
		while (is_in_brick(monster->getPosition())) {
			monster->reset_position();
		}
        /* Make the monster under the control of MonsterController  */
        this->addChild(monster);
        current_monster_vector.pushBack(monster);
    }
}

void MonsterController::bind_player(Player * player) {
    monitored_player = player;
}

void MonsterController::bind_layer(TMXLayer* layer)
{
	_bricks = layer;
}

bool MonsterController::is_in_brick(Vec2 pos)
{
	int firstGID = _bricks->getTileSet()->_firstGid;

	Vec2 tile_coord = Vec2(pos.x / TILE_SIZE.width, (MAP_SIZE.height * TILE_SIZE.height - pos.y) / TILE_SIZE.height);
	int GID = _bricks->getTileGIDAt(tile_coord);

	return (GID - firstGID >= 0);
}
