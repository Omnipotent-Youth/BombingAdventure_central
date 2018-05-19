//
// Created by Brando Zhang on 2018/5/16.
//

#ifndef BOMBING_ADVENTURE_MONSTERCONTROLLER_H
#define BOMBING_ADVENTURE_MONSTERCONTROLLER_H

#include "cocos2d.h"
#include "Monster.h"


USING_NS_CC;

/* Following are the attributes of Monster Controller   */
const int NUM_MONSTERS = 5;

class MonsterController : public Node {
public:
//    /*  Constructor */
//    MonsterController();
//
//    /*  Destructor   */
//    ~MonsterController();

    CREATE_FUNC(MonsterController);

    /* Initiate Method  */
    virtual bool init();

    /* Override update method   */
    virtual void update(float delta);
private:
    /* Method: create_monster
     * ----------------------
     * Create a monster
     */
    void create_monster();
    /* Store all the Monsters   */
    Vector<Monster*> current_monster_vector;
};

#endif //BOMBING_ADVENTURE_MONSTERCONTROLLER_H
