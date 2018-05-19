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

    if (currentTime >= endTime) {
        isCounting = false;
        this->unschedule(schedule_selector(Bomb::bombUpdate));
        this->removeAllChildren();
        this->removeFromParent();
    }
}

void Bomb::startCounting(float time) {
    endTime = time;
    currentTime = 0;
    isCounting = true;
}

int Bomb::getPower()
{
	return power;
}

bool Bomb::bombIsCounting()
{
	return isCounting;
}

