//
// Created by Jason Qiu on 2018/5/16.
//
#include "Bomb.h"
#include "cocos2d.h"

USING_NS_CC;

bool Bomb::init() {
    power = 1;
    isCounting = false;

	Animation *animation = Animation::create();
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("alive.plist");
	for (int i = 1; i <= 3; i++) {
		__String *frameName = __String::createWithFormat("alive_0%d.png", i);
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);
	Animate *action = Animate::create(animation);
	
	Sprite *bomb_sprite = Sprite::create("blue_bomb.png");
	bomb_sprite->runAction(RepeatForever::create(action));

	this->bind_sprite(bomb_sprite);
    
	this->schedule(schedule_selector(Bomb::bombUpdate), 0.5f);
    return true;
}

void Bomb::bombUpdate(float delta) {
    if (!isCounting) {
        return;
    }

    currentTime += delta;

	if (currentTime >= endTime && currentTime < endTime + 0.5f) {
		exploded = true;
		removeAllChildren();
	}

	if (currentTime >= endTime + 0.5f) {
		isCounting = false;
		removeAllChildren();
        this->unschedule(schedule_selector(Bomb::bombUpdate));
        removeFromParent();
    }
}

void Bomb::startCounting(float time) {
    endTime = time;
    currentTime = 0;
    isCounting = true;
	exploded = false;
}

int Bomb::getPower()
{
	return power;
}

bool Bomb::bombIsExploded()
{
	return exploded;
}
