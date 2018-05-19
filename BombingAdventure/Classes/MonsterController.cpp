//
// Created by Brando Zhang on 2018/5/16.
//

#include "MonsterController.h"

bool MonsterController::init() {
    /* Get current time to initialize a random seed     */
    timeval now;
    gettimeofday(&now, NULL);
    auto seed = (unsigned) (now.tv_sec * 1000 + now.tv_usec / 1000);
    srand(seed);

    create_monster();
    /* Enable update    */
    this->scheduleUpdate();
    return true;
}
void MonsterController::update(float delta) {
    for (Monster* monster: current_monster_vector) {
        if (monster->is_alive()) {
            Vec2 monster_pos_in_pixel = monster->getPosition();
            Vec2 monster_pos_in_tile = monster->tileCoordFromPosition(monster_pos_in_pixel);
        if (monster_pos_in_tile.x < 0 || monster_pos_in_tile.x > 40
                || monster_pos_in_tile.y < 0 || monster_pos_in_tile.y > 40) {
            monster->reset_position();
        }
        }
    }
}
void MonsterController::create_monster() {
    for (int i = 0; i < NUM_MONSTERS; i++) {

        /* Create NUM_MONSTERS monsters */
        Monster * monster = Monster::create();
        monster->reset_position();

        /* Make the monster under the control of MonsterController  */
        this->addChild(monster);
        current_monster_vector.pushBack(monster);
    }
}
