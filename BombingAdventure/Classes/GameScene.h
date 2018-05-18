#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "Player.h"
#include "MonsterController.h"
#include "Monster.h"
#include "Item.h"

const cocos2d::Size TILE_SIZE(40, 40);
const cocos2d::Size MAP_SIZE(24, 16);


class GameScene : public cocos2d::Layer
{
public:
	/* Creates the game scene and returns a pointer to the scene. */
	static cocos2d::Scene* createScene();

	/* Initializes the game scene */
	virtual bool init();

	virtual void update(float delta);

	/**
	 * Method:bomb_explode
	 * Usage: bomb_explode();
	 * ---------------------
	 * psuedo code:
	 * Bomb *Bomb= currentBomb.pop();
	 * bombPower = Bomb->power;
	 * bombPos = Bomb->position;
	 * Size bombTileCoord = tileCoordFromPosition(bombPos);
	 * for (int i = bombTileCoord.x; i <= bombTileCoord+2*bombPower; i++){
	 *		GID = getGID(i, bombTileCoord.y);
	 *		if GID.isInBricksLayer() && ！dectructable : (是砖块，但是炸不了.需要挡住此砖左边/右边的爆炸效果)
	 *		if GID.isDectructable(): removeTile()... (移除砖块，移除可爆炸块，遮挡爆炸效果)
	 * }
	 * for (int j = bombTileCoord.y; j <= bombTileCoord+2*bombPower; j++){
	 *		same operations...
	 * }
	 *
	 * 这个函数实现：判定炸弹爆炸的有效范围（是否被砖块挡住），把范围内的可炸(dectructable)砖块炸掉。
	 * 炸弹炸到人的判定可以再写一个函数？
	 */
	void bomb_explode();

	Vector<Bomb*> get_all_bomb();

	bool isOutOfMap(cocos2d::Vec2 pos);

	bool collideWithBrick(cocos2d::Vec2 targetPos);

	bool collideWithBubble(cocos2d::Vec2 targetPos);

	void makeMove(cocos2d::Vec2 position);

	/* macro for creating layer */
	CREATE_FUNC(GameScene);

	/**
	 * Method: tileCoordFromPosition
	 * Usage: Vec2 Pos = this->tileCoordFromPosition(Vec2 position);
	 * -----------------------------------------------
	 * Takes a parameter of Vec2 type, indicating the position that the user want
	 * to convert. Then, this function will convert it into the tile coordinate.
	 * 
	 * See the illustration:
	 *
	 *	    *-----*-----*-----*-----*---------->  x-axis (tile)
	 *      |   *B|     |     |     |
	 *      |     |		|	  |		|
	 *      *-----*-----*-----*-----*
	 *      |     |	    |     |     |
	 *      |     |     | *A  |     |
	 *      *-----*-----*-----*-----*
	 *      |     |     |     |     |
	 *      |     |     |     |	    |
	 *      *-----*-----*-----*-----*
	 *      |
	 *      |
	 *      v
	 *		y-axis (tile)
	 *
	 *		In this diagram, A and B have position coordinates (90, 50) and (30, 110)
	 *		respectively. In the tile coordinate, A is in tile (2, 1), B is in tile (0, 0).
	 *
	 */

	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);

	/* Test pick item   */
//	Item * speed_up_item;
private:

	Vector<Bomb*> currentBomb;
	cocos2d::TMXTiledMap * map;		/* the tile map for Bombing Adventure game */
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
    Player * hero = NULL;      /* This is the player control by human  */
//    Map<Vec2, STATUS_AT*> status_map;

};


#endif