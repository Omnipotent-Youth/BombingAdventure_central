#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "Player.h"
#include "Item.h"

//#include "Monster.h"

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

    enum STATUS_AT {
        EMPTY,      /* Corresponding position is empty              */
        ITEM,       /* There is an item at corresponding position   */
        BOMB,       /* There is a bomb at corresponding position    */
        BRICK,      /* Brick cannot be passed, but can be destroyed */
        WALL        /* Wall cannot be passed or destroyed           */
    };

    /* This is the monsters in this scene   */
//    Monster * monster1;
//    Monster * monster2;
//    Monster * monster3;

	/* Test class Player part   */
    Player * hero;      /* This is the player control by human  */
	Item * item;
//    Map<Vec2, STATUS_AT*> status_map;
};


#endif