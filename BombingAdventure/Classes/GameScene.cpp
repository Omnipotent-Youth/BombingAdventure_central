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
	this->addChild(map, 1, 100);
	map->getLayer("background")->setGlobalZOrder(-1);

	// "destructable" layer, indicating the tiles which can be blown up by bubbles
	destructable = map->getLayer("destructable");
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
    this->addChild(hero, 100, 200);


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
                    Bomb *bomb = hero->set_bomb();
					current_bombs.pushBack(bomb);
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

    /* Initialize a MonsterController   */
    MonsterController * monster_controller = MonsterController::create();
    this->addChild(monster_controller,499);

    /* Initialize an ItemController     */
    ItemController * item_controller = ItemController::create();
    item_controller->bind_player(hero);
    this->addChild(item_controller);

    /* If uncomment the following statement, items will be hid under the bricks    */
//    item_controller->setGlobalZOrder(0);
    monster_controller->setGlobalZOrder(99);
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

	/* Bombs blow up destructable bricks */
	while (!current_bombs.empty() && !current_bombs.front()->bombIsCounting()) {
		Bomb * bomb = current_bombs.front();
		bomb_explode(bomb);
		current_bombs.erase(0);
	}

    /* Test pick_item method    */
//    Item * speed_up_item = Item::create();
//    speed_up_item->setPosition(Vec2(500, 380));
//    this->addChild(speed_up_item);
//
//    auto item_position = tileCoordFromPosition(speed_up_item->getPosition());
//    auto hero_position = tileCoordFromPosition(hero->getPosition());
//    if (item_position == hero_position) {
//        hero->pick_item(*speed_up_item);
//    }
}

void GameScene::bomb_explode(Bomb *bomb)
{
	int power = bomb->getPower();
	Vec2 bomb_tile_coord = tileCoordFromPosition(bomb->getPosition());
	int firstGid = destructable->getTileSet()->_firstGid;

	int i = 0;
	for (; i < power && bomb_tile_coord.x - i - 1 >= 0; i++) {
		int GID = destructable->getTileGIDAt(Vec2(bomb_tile_coord.x - i - 1, bomb_tile_coord.y));
		if (GID - firstGid >= 0) {
			map->getLayer("bricks")->removeTileAt(Vec2(bomb_tile_coord.x - i - 1, bomb_tile_coord.y));
			if (bomb_tile_coord.y > 0) {
				map->getLayer("tops")->removeTileAt(Vec2(bomb_tile_coord.x - i - 1, bomb_tile_coord.y - 1));
			}
				destructable->removeTileAt(Vec2(bomb_tile_coord.x - i - 1, bomb_tile_coord.y));
			break;
		}
	}
	i = 0;
	for (; i < power && bomb_tile_coord.x + i + 1 < MAP_SIZE.width; i++) {
		int GID = destructable->getTileGIDAt(Vec2(bomb_tile_coord.x + i + 1, bomb_tile_coord.y));
		if (GID - firstGid >= 0) {
			map->getLayer("bricks")->removeTileAt(Vec2(bomb_tile_coord.x + i + 1, bomb_tile_coord.y));
			if (bomb_tile_coord.y > 0) {
				map->getLayer("tops")->removeTileAt(Vec2(bomb_tile_coord.x + i + 1, bomb_tile_coord.y - 1));
			}
				destructable->removeTileAt(Vec2(bomb_tile_coord.x + i + 1, bomb_tile_coord.y));
			break;
		}
	}
	int j = 0;
	for (; j < power && bomb_tile_coord.y + j + 1 < MAP_SIZE.height; j++) {
		int GID = destructable->getTileGIDAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y + j + 1));
		if (GID - firstGid >= 0) {
			map->getLayer("bricks")->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y + j + 1));
			map->getLayer("tops")->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y + j));
			destructable->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y + j + 1));
			break;
		}
	}
	j = 0;
	for (; j < power && bomb_tile_coord.y - j - 1 >= 0; j++) {
		int GID = destructable->getTileGIDAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y - j - 1));
		if (GID - firstGid >= 0) {
			map->getLayer("bricks")->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y - j - 1));
			if (bomb_tile_coord.y - j - 1 != 0) {
				map->getLayer("tops")->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y - j - 2));
			}
				destructable->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y - j - 1));
			break;
		}
	}
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
	// correct the detection deviation caused by the sprite size
	Size figSize = hero->getContentSize();
	
	Vec2 targetPos_down(position.x,  position.y - figSize.height / 2);
	Vec2 targetPos_top = position;

	switch (x_movement) {
	case MOVE_LEFT:
		targetPos_down.x -= 1 * figSize.width / 3;
		targetPos_top.x -= 1 * figSize.width / 3;
		break;
	case MOVE_RIGHT:
		targetPos_down.x += 1 * figSize.width / 3;
		targetPos_top.x += 1 * figSize.width / 3;
		break;
	}
	// if the target position is out of bound
	if (isOutOfMap(targetPos_down) || isOutOfMap(targetPos_top)) return;

	if (collideWithBrick(targetPos_down) || collideWithBrick(targetPos_top) || collideWithBubble(targetPos_down) || collideWithBubble(targetPos_top)) return;

	hero->setPosition(position);
}

Vec2 GameScene::tileCoordFromPosition(Vec2 position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Vec2(x, y);
}