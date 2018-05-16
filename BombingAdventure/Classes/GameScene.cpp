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

Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	map = TMXTiledMap::create("map/map1.tmx");
	map->setAnchorPoint(Vec2(0.5, 0.5));
	map->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 40));
	this->addChild(map, 0, 100);

	collidable = map->getLayer("collide");
	collidable->setVisible(false);


	TMXObjectGroup *group = map->getObjectGroup("object1");
	ValueMap spawnPoint = group->getObject("spawn");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();
	player = Sprite::create("player1_default.png");
	player->setAnchorPoint(Vec2(0.5, 0.5));
	player->setPosition(Vec2(x+20, y-50));
	addChild(player, 2, 200);
/*
	setTouchEnabled(TRUE);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
*/
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
    game_keyboard_listener->onKeyPressed = [](EventKeyboard::KeyCode keyboard_code, Event* event) {
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
        }
    };
    game_keyboard_listener->onKeyReleased = [](EventKeyboard::KeyCode keyboard_code, Event* event) {
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
    _eventDispatcher->addEventListenerWithSceneGraphPriority(game_keyboard_listener, player);

    /* Enable update function of the GameScene, which controls the refreshments */
    this->scheduleUpdate();

	return true;
}
void GameScene::update(float delta) {

    /* Following part updates the movement of player    */
    float position_x = player->getPositionX();
    float position_y = player->getPositionY();

    float moving_speed = 10.f;

    position_x += x_movement * moving_speed;
    position_y += y_movement * moving_speed;

    player->setPosition(position_x, position_y);
}

/*
void GameScene::setPlayerPosition(Vec2 position)
{
	Vec2 tileCoord = this->tileCoordFromPosition(position);

	int tileGid = collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		auto prop = map->propertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		string _collision_ = propValueMap["collidable"].asString();

		if (_collision_ == "true") {
			return;
		}
	}
	player->setPosition(position);
}

Vec2 GameScene::tileCoordFromPosition(Vec2 position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Vec2(x, y);
}

bool GameScene::onTouchBegan(Touch * touch, Event * event)
{
	return true;
}

void GameScene::onTouchMoved(Touch * touch, Event * event)
{

}

void GameScene::onTouchEnded(Touch * touch, Event * event)
{
	Vec2 touchLocation = touch->getLocation();
	Vec2 playerPos = player->getPosition();
	Vec2 diff(touchLocation - playerPos);

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += map->getTileSize().width;
			player->runAction(MoveTo::create(.30f, playerPos));
		} else {
			playerPos.x -= map->getTileSize().width;
			player->runAction(MoveTo::create(.30f, playerPos));
		}
	} else {
		if (diff.y > 0) {
			playerPos.y += map->getTileSize().height;
		} else {
			playerPos.y -= map->getTileSize().height;
		}
	}
	this->setPlayerPosition(playerPos);
}

*/