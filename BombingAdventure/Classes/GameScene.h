#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "Player.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float delta);

	CREATE_FUNC(GameScene);
/*
	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);

	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);
*/

private:
	cocos2d::TMXTiledMap * map;
	cocos2d::TMXLayer * collidable;
//	cocos2d::Sprite * player;

	/* Test class Player part   */
    Player * hero;      /* This is the player control by human  */

};


#endif