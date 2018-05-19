//
// Created by Jason Qiu on 2018/5/16.
//

#include "Bomb.h"

bool Bomb::init() {
    power = 1;
    isCounting = false;
    this->bind_sprite(Sprite::create("blue_bomb.png"));
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
