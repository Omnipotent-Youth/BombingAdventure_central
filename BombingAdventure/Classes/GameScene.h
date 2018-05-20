#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "MonsterController.h"
#include "ItemController.h"

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
	 *
	 */
	void bomb_explode(Bomb *bomb);

	bool isOutOfMap(cocos2d::Vec2 pos);

	bool here_can_set(Vec2 pos);

	bool collideWithBrick(cocos2d::Vec2 targetPos);

	bool collideWithBubble(cocos2d::Vec2 playerPos, cocos2d::Vec2 targetPos);

	bool makeMove(cocos2d::Vec2 position, Player * player);

	void game_over();


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

	Vector<Bomb*> current_bombs;
	cocos2d::TMXTiledMap * map;			/* the tile map for Bombing Adventure game */
	cocos2d::TMXLayer * bricks;
	cocos2d::TMXLayer * destructable;	/* destructable layer                      */

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
        MonsterController * monster_controller = NULL;
        ItemController * item_controller = NULL;

};


#endif