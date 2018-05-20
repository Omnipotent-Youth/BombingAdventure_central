//
// Created by Jason Qiu on 2018/5/16.
//

#ifndef BOMBING_ADVENTURE_BOMB_H
#define BOMBING_ADVENTURE_BOMB_H

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

/* Class: Bomb
 * -------------------------
 * This is a class for bomb. This class is
 * inherited from the Entity class. The design
 * of the bomb includes the timing function.
 */

class Bomb : public Entity {

public:

    /*
     * Constructor: CREATE_FUNC(Bomb)
     * ------------------------------
     * This is a macro for the creation
     * of Bomb.
     */

    CREATE_FUNC(Bomb)

    /*
     * virtual method: init(Bomb)
     * ------------------------------
     * This is the initiation method
     * for this Bomb class.
     */

    virtual bool init();

    /*
     * virtual method: bombUpdate(delta)
     * ------------------------------
     * This is the update method
     * for this Bomb class.
     */

    virtual void bombUpdate(float delta);

    /*
     * method: startCounting(time)
     * ------------------------------
     * This is the start function for
     * the timing function of the bomb.
     */

    void startCounting(float time);

	/*
	 * method: bombIsExploded()
	 * ------------------------
	 * Returns bool member exploded of the bomb, which 
	 * indicates whether it has been blown up.
	 */

	bool bombIsExploded();

private:
    float currentTime;      /* Current Time of timing               */
    float endTime;          /* The End Time set for explosion       */
    
	/* isCounting and exploded have some differences: when the bomb is going 
	   to explode, exploded set true, and continue timing; then, the GameScene
	   will show the explosion effect; finally, isCounting set false, and all 
	   children of the bombs will be removed.						*/ 
	bool isCounting;        /* Whether counting is being processed. */
	bool exploded;			/* Whether bomb has exploded			*/
};


#endif //BOMBING_ADVENTURE_BOMB_H
