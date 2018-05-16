#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
	/* Creates the game scene and returns a pointer to the scene. */
	static cocos2d::Scene* createScene();

	/* Initializes the game scene */
	virtual bool init();

	virtual void update(float delta);

	bool isOutOfMap(cocos2d::Vec2 pos);

	bool collideWithBrick(cocos2d::Vec2 targetPos);

	bool collideWithBubble(cocos2d::Vec2 targetPos);

	void makeMove(cocos2d::Vec2 position);

	/* macro for creating layer */
	CREATE_FUNC(GameScene);

	/**
	 * Function: tileCoordFromPosition
	 * Usage: Vec2 Pos = this->tileCoordFromPosition();
	 * -----------------------------------------------
	 * Takes a parameter of Vec2 type, indicating the position that the user want
	 * to convert. Then, this function will convert it into the tile coordinate.
	 * 
	 * See the illustration:
	 *
	 *		*-----*-----*-----*-----*---------->  x-axis (tile)
	 *		|	*B|     |     |     |
	 *		|     |		|	  |		|
	 *      *-----*-----*-----*-----*
	 *		|	  |		|	  |		|
	 *		|	  |		| *A  |		|
	 *		*-----*-----*-----*-----*
	 *		|	  |		|     |		|
	 *		|	  |		|	  |		|
	 *		*-----*-----*-----*-----*
	 *		|	
	 *		|
	 *		v
	 *		y-axis (tile)
	 *
	 *		In this diagram, A and B have position coordinates (90, 50) and (30, 110)
	 *		respectively. In the tile coordinate, A is in tile (2, 1), B is in tile (0, 0).
	 *
	 */

	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);

private:
	cocos2d::TMXTiledMap * map;		/* the tile map for Bombing Adventure game */
	cocos2d::Sprite * player;		/* a key-controlled sprite                 */	
};


#endif