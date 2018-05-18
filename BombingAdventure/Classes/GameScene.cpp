#include "GameScene.h"

//using namespace std;
USING_NS_CC;

/* Following constants are the marks of movement status     */
const int MOVE_LEFT = -1;
const int MOVE_RIGHT = 1;
const int MOVE_UP = 1;
const int MOVE_DOWN = -1;
const int MOVE_STOP = 0;

/* Following variables mark the movement status of player   */
int x_movement = MOVE_STOP;         /* Initiate with player stops   */
int y_movement = MOVE_STOP;         /* Initiate with player stops   */

/*
 * Implementation Note: similar to HelloWorldScene::createScene().
 */

Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

/*
 * Implementation Note: initializer
 * --------------------------------
 * The initializer initiates the game map, the player sprite, and the keyboard event listener.
 */

bool GameScene::init() {
	
	// super-init first
	if (!Layer::init()) {
		return false;
	}
	// get visible size of the game window
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// get the origin
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* Create a tile map.
	 * Note that the designed map has the same size as the game window:
	 * 960 * 640, with each tile of size 40*40 (pixes). Therefore, there
	 * are 24 * 16 tiles totally in the tile map.
	 */
	map = TMXTiledMap::create("map/map1.tmx");
	
	// set the anchor point and position of the map
	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	// add the map into the scene
	this->addChild(map, 0, 100);

	// "destructable" layer, indicating the tiles which can be blown up by bubbles
	TMXLayer * destructable = map->getLayer("destructable");
	destructable->setVisible(false);					/* set it transparent*/

	// object layer (probably useless)
	TMXObjectGroup *group = map->getObjectGroup("object1");
	
	// get the spawn point and its coordinate
	ValueMap spawnPoint = group->getObject("spawn");

	/* Initiate the player sprite, set its position at the spawn point,
	 * and add it into the game scene.
	 */


    /* Create the hero  */
    float x = spawnPoint["x"].asFloat();
    float y = spawnPoint["y"].asFloat();
    hero = Player::create();
    hero->setPosition(Vec2(x+20, y+70));
    this->addChild(hero, 2, 200);

    /* Test item    */
    item = Item::create();
    item->setPosition(Vec2(300, 400));
    this->addChild(item, 3, 200);
    /* Following are keyboard listener  */

    /* Callback Function: game_keyboard_listener
     * -----------------------------------------
     *      ->onKeyPressed: listen to the keyboard event "press".
     *                      Mark A or arrow_left as move_left;
     *                           D or arrow_right as move_right;
     *                           W or arrow_up as move_up;
     *                           S or arrow_down as move_down;
     *                      Player can press and hold the key to move,
     *                      instead of pressing the same key repeatedly.
     *      ->onKeyRelease: listen to the keyboard event "release".
     *                      Mark the corresponding key release as the
     *                      end of movement on that direction.
     */
    auto game_keyboard_listener = EventListenerKeyboard::create();
    game_keyboard_listener->onKeyPressed = [&](EventKeyboard::KeyCode keyboard_code, Event* event) {
        switch (keyboard_code) {
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
                x_movement = MOVE_LEFT;
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
                x_movement = MOVE_RIGHT;
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            case EventKeyboard::KeyCode::KEY_W:
                y_movement = MOVE_UP;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
                y_movement = MOVE_DOWN;
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
                if (hero->can_set_bomb()) {
                    hero->set_bomb();
//                    status_map.insert(hero->getPosition(), BOMB);
//                    log("The current position status is %d", status_map.at(hero->getPosition()));
//                    status_map.insert(hero->getPosition(), EMPTY);
//                    log("The current position status is %d", status_map.at(hero->getPosition()));
                }
                break;
        }
    };
    game_keyboard_listener->onKeyReleased = [&](EventKeyboard::KeyCode keyboard_code, Event* event) {
        switch (keyboard_code) {
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
                x_movement = MOVE_STOP;
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
                x_movement = MOVE_STOP;
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            case EventKeyboard::KeyCode::KEY_W:
                y_movement = MOVE_STOP;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
                y_movement = MOVE_STOP;
                break;
        }
    };

    /* Register keyboard event listener */
    _eventDispatcher->addEventListenerWithSceneGraphPriority(game_keyboard_listener, hero);

    /* Enable update function of the GameScene, which controls the refreshments */
    this->scheduleUpdate();

	return true;
}




void GameScene::update(float delta) {

	/* Following part updates the movement of player    */
	float position_x = hero->getPositionX();
	float position_y = hero->getPositionY();

	float moving_speed = hero->get_moving_speed();

	position_x += x_movement * moving_speed;
	position_y += y_movement * moving_speed;

	makeMove(Vec2(position_x, position_y));

//    /* Test pick_item method    */
//    auto item_position = item->getPosition();
//    auto hero_position = hero->getPosition();
//    if (item_position == hero_position) {
//        hero->pick_item(*item);
//    }
}

void GameScene::bomb_explode()
{
}

bool GameScene::isOutOfMap(Vec2 pos) 
{	
	float mapWidth = map->getMapSize().width * map->getTileSize().width;
	float mapHeight = map->getMapSize().height * map->getTileSize().height;

	if (pos.x <= 0 ||
		pos.x >= mapWidth ||
		pos.y <= 0 ||
		pos.y >= mapHeight) return true;
	return false;
}

bool GameScene::collideWithBrick(cocos2d::Vec2 targetPos)
{
	// get the tile coord of the target position
	Vec2 tileCoord = tileCoordFromPosition(targetPos);

	// tiles in the "bricks" layer are "collidable"
	TMXLayer *collide = map->getLayer("bricks");

	// get absolute GID of the tile
	int tileGid = collide->getTileGIDAt(tileCoord);
	// first GID of the "bricks" layer
	int firstGid = collide->getTileSet()->_firstGid;
	// get related GID of the tile
	tileGid -= firstGid;
	
	// if GID >= 0, the tile is in the "brick" layer
	if (tileGid >= 0) {
		return true;
	}
	return false;
}

bool GameScene::collideWithBubble(cocos2d::Vec2 targetPos)
{
	return false;
}

void GameScene::makeMove(Vec2 position)
{
	Vec2 targetPos = position;

	// correct the detection deviation caused by the sprite size
	Size figSize = hero->getContentSize();

	if (y_movement == MOVE_STOP) {
		switch (x_movement) {
		case MOVE_LEFT:
			targetPos.x -= 1 * figSize.width / 3;
			break;
		case MOVE_RIGHT:
			targetPos.x += 1 * figSize.width / 3;
			break;
		}
	}
	else {
		switch (y_movement) {
		case MOVE_UP:
			if (x_movement == MOVE_STOP) {
				break;
			}
			else {
				if (x_movement == MOVE_LEFT) {
					targetPos.x -= 1 * figSize.width / 3;
				}
				else {
					targetPos.x += 1 * figSize.width / 3;
				}
				break;
			}
		case MOVE_DOWN:
			targetPos.y -= figSize.height / 2 + 3;
			if (x_movement == MOVE_STOP) {
				break;
			}
			else {
				if (x_movement == MOVE_LEFT) {
					targetPos.x -= 1 * figSize.width / 3;
				}
				else {
					targetPos.x += 1 * figSize.width / 3;
				}
				break;
			}
		}
	}

	// if the target position is out of bound
	if (isOutOfMap(targetPos)) return;

	if (collideWithBrick(targetPos) || collideWithBubble(targetPos)) return;

	hero->setPosition(position);
}

Vec2 GameScene::tileCoordFromPosition(Vec2 position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Vec2(x, y);
}