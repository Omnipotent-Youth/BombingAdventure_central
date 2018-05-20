//
// Created by Jason Qiu on 2018/5/16.
//
#include "Bomb.h"
#include "cocos2d.h"

USING_NS_CC;

/*
 * initializer
 * -----------
 */

bool Bomb::init() {
    isCounting = false;

	// add animation into the bomb object, and later the effect will be shown
	Animation *animation = Animation::create();
	// add sprite frames from .plist file 
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("alive.plist");
	
	// traverse the .plist and add all frames
	for (int i = 1; i <= 3; i++) {
		__String *frameName = __String::createWithFormat("alive_0%d.png", i);
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}
	
	// delay time between two frame
	animation->setDelayPerUnit(0.2f);
	// repeat while play
	animation->setRestoreOriginalFrame(true);
	
	// create Animate object
	Animate *action = Animate::create(animation);
	
	Sprite *bomb_sprite = Sprite::create("blue_bomb.png");
	
	// bomb runs action
	bomb_sprite->runAction(RepeatForever::create(action));

	// bind the bomb sprite to the bomb object
	this->bind_sprite(bomb_sprite);
    
	this->schedule(schedule_selector(Bomb::bombUpdate), 0.5f);
    return true;
}

/*
 * update
 * ------
 * Implementation Node: the update method is invoked every
 * delta second. It deals with the lifetime of bombs.
 *
 */
void Bomb::bombUpdate(float delta) {
    if (!isCounting) {
        return;
    }

    currentTime += delta;

	// bomb exploded. Effect will be shown
	if (currentTime >= endTime && currentTime < endTime + 0.5f) {
		exploded = true;
		removeAllChildren();
	}

	// bomb and its children removed from the game
	if (currentTime >= endTime + 0.5f) {
		isCounting = false;
		removeAllChildren();
        this->unschedule(schedule_selector(Bomb::bombUpdate));
        removeFromParent();
    }
}

// set isCounting true
void Bomb::startCounting(float time) {
    endTime = time;
    currentTime = 0;
    isCounting = true;
	exploded = false;
}

bool Bomb::bombIsExploded()
{
	return exploded;
}

