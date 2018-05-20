#include "GameScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"

USING_NS_CC;

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

	bricks = map->getLayer("bricks");

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
	
	/* create the health point bar for player*/
	HP = ui::LoadingBar::create("hp.png");
	HP->setPosition(Vec2(HP->getContentSize().width / 2, visibleSize.height - HP->getContentSize().height / 2));
	HP->setPercent(100);
	addChild(HP, 101);
	HP->setGlobalZOrder(101);

	MenuItemImage * win_scene = MenuItemImage::create(
		"win.png",
		"win.png",
		CC_CALLBACK_1(GameScene::menuCallBack, this));

	win_scene->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	win_scene->setScale(0.6);

	auto menu = Menu::create(win_scene, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1, "menu");
	menu->setGlobalZOrder(200);
	menu->setVisible(false);


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
                hero->x_movement = MOVE_SIGNAL_X::MOVE_LEFT;
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
                hero->x_movement = MOVE_SIGNAL_X::MOVE_RIGHT;
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            case EventKeyboard::KeyCode::KEY_W:
                hero->y_movement = MOVE_SIGNAL_Y::MOVE_UP;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
                hero->y_movement = MOVE_SIGNAL_Y::MOVE_DOWN;
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
				if (here_can_set(hero->getPosition()) && hero->can_set_bomb()) {
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music&effect/bubbleSet.mp3");
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
                hero->x_movement = MOVE_SIGNAL_X::MOVE_STOP_X;
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
                hero->x_movement = MOVE_SIGNAL_X::MOVE_STOP_X;
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            case EventKeyboard::KeyCode::KEY_W:
                hero->y_movement = MOVE_SIGNAL_Y::MOVE_STOP_Y;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
                hero->y_movement = MOVE_SIGNAL_Y::MOVE_STOP_Y;
                break;
        }
    };

    /* Register keyboard event listener */
    _eventDispatcher->addEventListenerWithSceneGraphPriority(game_keyboard_listener, hero);

    /* Enable update function of the GameScene, which controls the refreshments */
    this->scheduleUpdate();

    /* Initialize a MonsterController   */
    monster_controller = MonsterController::create();
    monster_controller->bind_player(hero);
	monster_controller->bind_layer(bricks);
	monster_controller->create_monster();
    this->addChild(monster_controller,499);

    /* Initialize an ItemController     */
    item_controller = ItemController::create();
    item_controller->bind_player(hero);
	item_controller->bind_bricks_layer(bricks);
	item_controller->bind_destructable_layer(destructable);
	item_controller->create_item();
	this->addChild(item_controller);

    /* If uncomment the following statement, items will be hid under the bricks    */
    monster_controller->setGlobalZOrder(99);
	return true;
}

/* update function to check the state of game scene every delta seconds */
void GameScene::update(float delta) {

	if (!hero->is_alive()) {
		game_over();
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music&effect/game_over.mp3");
	}
	
	if (monster_controller->current_monster_vector.empty()) {
		this->getChildByName("menu")->setVisible(true);
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music&effect/win_game.mp3");
	}
	
	HP->setPercent(100 * hero->get_HP() / PLAYER_MAX_HP);

	/* Following part updates the movement of player    */
	float position_x = hero->getPositionX();
	float position_y = hero->getPositionY();

	float moving_speed = hero->get_moving_speed();

	position_x += hero->get_x_movement() * moving_speed;
	position_y += hero->get_y_movement() * moving_speed;

	makeMove(Vec2(position_x, position_y), hero);

	for (Monster * monster : monster_controller->current_monster_vector) {

	    monster->make_new_direction();
	    /* Following part updates the movement of monster    */
        float monster_position_x = monster->getPositionX();
        float monster_position_y = monster->getPositionY();

        float moving_speed = monster->get_moving_speed();

        monster_position_x += monster->get_x_movement() * moving_speed;
        monster_position_y += monster->get_y_movement() * moving_speed;

        if(!makeMove(Vec2(monster_position_x, monster_position_y), monster)) {
            monster->make_new_direction();
        };
	}

	/* Bombs blow up destructable bricks */
	while (!current_bombs.empty() && current_bombs.front()->bombIsExploded()) {
		Bomb * bomb = current_bombs.front();
		bomb_explode(bomb);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music&effect/bubbleBoom.mp3");
		current_bombs.erase(0);
	}
}

void GameScene::bomb_explode(Bomb *bomb)
{
	int power = hero->getPower();
	// ranges in four directioins
	int l_range = 0;
	int r_range = 0;
	int u_range = 0;
	int d_range = 0;

	Vec2 bomb_tile_coord = tileCoordFromPosition(bomb->getPosition());
	// first Gid of the two layers
	int firstGid_of_des = destructable->getTileSet()->_firstGid;
	int firstGid_of_brk = bricks->getTileSet()->_firstGid;

	for (; l_range < power && bomb_tile_coord.x - l_range - 1 >= 0; l_range++) {
		// get Gid at brick layer
		int GID_brk = bricks->getTileGIDAt(Vec2(bomb_tile_coord.x - l_range - 1, bomb_tile_coord.y));
		// if the tile contains a brick
		if (GID_brk - firstGid_of_brk >= 0){
			// get Gid at destructable layer
			int GID_des = destructable->getTileGIDAt(Vec2(bomb_tile_coord.x - l_range - 1, bomb_tile_coord.y));
			// if the brick is destructable
			if (GID_des - firstGid_of_des >= 0) {
				// remove (destruct) the brick
				bricks->removeTileAt(Vec2(bomb_tile_coord.x - l_range - 1, bomb_tile_coord.y));
				if (bomb_tile_coord.y > 0) {
					// reomve the top of the brick
					map->getLayer("tops")->removeTileAt(Vec2(bomb_tile_coord.x - l_range - 1, bomb_tile_coord.y - 1));
				}
				// remove the destructable property
				destructable->removeTileAt(Vec2(bomb_tile_coord.x - l_range  - 1, bomb_tile_coord.y));
			}
			break;
		}
	}
	// the traversing strategy is similar to the above one
	for (; r_range < power && bomb_tile_coord.x + r_range + 1 < MAP_SIZE.width; r_range++) {
		int GID_brk = bricks->getTileGIDAt(Vec2(bomb_tile_coord.x + r_range + 1, bomb_tile_coord.y));
		if (GID_brk - firstGid_of_brk >= 0) {
			int GID_des = destructable->getTileGIDAt(Vec2(bomb_tile_coord.x + r_range + 1, bomb_tile_coord.y));
			if (GID_des - firstGid_of_des >= 0) {
				bricks->removeTileAt(Vec2(bomb_tile_coord.x + r_range + 1, bomb_tile_coord.y));
				if (bomb_tile_coord.y > 0) {
					map->getLayer("tops")->removeTileAt(Vec2(bomb_tile_coord.x + r_range + 1, bomb_tile_coord.y - 1));
				}
				destructable->removeTileAt(Vec2(bomb_tile_coord.x + r_range + 1, bomb_tile_coord.y));
			}
			break;
		}
	}

	for (; d_range < power && bomb_tile_coord.y + d_range + 1 < MAP_SIZE.height; d_range++) {
		int GID_brk = bricks->getTileGIDAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y + d_range + 1));
		if (GID_brk - firstGid_of_brk >= 0) {
			int GID_des = destructable->getTileGIDAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y + d_range + 1));
			if (GID_des - firstGid_of_des >= 0) {
				bricks->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y + d_range + 1));
				map->getLayer("tops")->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y + d_range));
				destructable->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y + d_range + 1));
			}
			break;
		}
	}

	for (; u_range < power && bomb_tile_coord.y - u_range - 1 >= 0; u_range++) {
		int GID_brk = bricks->getTileGIDAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y - u_range - 1));
		if (GID_brk - firstGid_of_brk >= 0) {
			int GID_des = destructable->getTileGIDAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y - u_range - 1));
			if (GID_des - firstGid_of_des >= 0) {
				bricks->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y - u_range - 1));
				if (bomb_tile_coord.y - u_range - 1 != 0) {
					map->getLayer("tops")->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y - u_range - 2));
				}
				destructable->removeTileAt(Vec2(bomb_tile_coord.x, bomb_tile_coord.y - u_range - 1));
			}
			break;
		}
	}

	hero->bomb_vs_man(bomb_tile_coord, l_range, r_range, u_range, d_range);

    for (Monster * monster : monster_controller->current_monster_vector) {
        monster->bomb_vs_man(bomb_tile_coord, l_range, r_range, u_range, d_range);
    }

	/* Now we have l_range, r_value, u_value, d_value, which indicate the explosion
	 * range of the bomb in the four directions. What you need to do now is to 
	 * display the animation effect of bombs.
	 */

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Explosion.plist");
	// the center explosion effect
	Sprite *wave = Sprite::createWithSpriteFrameName("ExplosionCenter_01.png");
	bomb->addChild(wave);
	wave->setPosition(Vec2(TILE_SIZE.width/2, TILE_SIZE.height/2));

	// the left explosion effect
	for (int i = 0; i < l_range; i++) {
		Sprite *l_wave;
		// if is the end of the explosion range
		if (i == l_range - 1) {
			l_wave = Sprite::createWithSpriteFrameName("ExplosionLEFT_01.png");
		} else {
			l_wave = Sprite::createWithSpriteFrameName("ExplosionLEFT_02.png");
		}
		bomb->addChild(l_wave);
		l_wave->setPosition(Vec2((-i - 1) * TILE_SIZE.width + TILE_SIZE.width / 2, TILE_SIZE.height / 2));
	}
	// the traversing strategy is similar to the above one
	for (int i = 0; i < r_range; i++) {
		Sprite *r_wave;
		if (i == r_range - 1) {
			r_wave = Sprite::createWithSpriteFrameName("ExplosionRIGHT_01.png");
		} else {
			r_wave = Sprite::createWithSpriteFrameName("ExplosionRIGHT_02.png");
		}
		bomb->addChild(r_wave);
		r_wave->setPosition(Vec2((i + 1) * TILE_SIZE.width + TILE_SIZE.width / 2, TILE_SIZE.height / 2));
	}
	for (int i = 0; i < d_range; i++) {
		Sprite *d_wave;
		if (i == d_range - 1) {
			d_wave = Sprite::createWithSpriteFrameName("ExplosionDOWN_01.png");
		} else {
			d_wave = Sprite::createWithSpriteFrameName("ExplosionDOWN_02.png");
		}	
		bomb->addChild(d_wave);
		d_wave->setPosition(Vec2(TILE_SIZE.width / 2, (- i - 1) * TILE_SIZE.height + TILE_SIZE.height / 2));
	}
	for (int i = 0; i < u_range; i++) {
		Sprite *u_wave;
		if (i == u_range - 1) {
			u_wave = Sprite::createWithSpriteFrameName("ExplosionUP_01.png");
		} else {
			u_wave = Sprite::createWithSpriteFrameName("ExplosionUP_02.png");
		}
		u_wave->setPosition(Vec2(TILE_SIZE.width / 2, (i + 1) * TILE_SIZE.height + TILE_SIZE.height / 2));
		bomb->addChild(u_wave);
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

bool GameScene::here_can_set(Vec2 pos)
{
	pos = Vec2(pos.x, pos.y - hero->getContentSize().height / 3);
	Vec2 tile_coord = tileCoordFromPosition(pos);

	// traverse to get all bomb currently
	for (Bomb *bomb : current_bombs) {
		Vec2 bomb_tile_coord = tileCoordFromPosition(bomb->getPosition());
		if (bomb_tile_coord == tile_coord) {
			return false;
		}
	}
	return true;
}

bool GameScene::collideWithBrick(cocos2d::Vec2 targetPos)
{
	// get the tile coord of the target position
	Vec2 tileCoord = tileCoordFromPosition(targetPos);

	// get absolute GID of the tile
	int tileGid = bricks->getTileGIDAt(tileCoord);
	// first GID of the "bricks" layer
	int firstGid = bricks->getTileSet()->_firstGid;
	// get related GID of the tile
	tileGid -= firstGid;
	
	// if GID >= 0, the tile is in the "brick" layer
	if (tileGid >= 0) {
		return true;
	}
	return false;
}

bool GameScene::collideWithBubble(Vec2 playerPos, Vec2 targetPos)
{
	Vec2 target_tileCoord = tileCoordFromPosition(targetPos);
	Vec2 now_tileCoord = tileCoordFromPosition(Vec2(playerPos.x, playerPos.y));

	if (now_tileCoord == target_tileCoord) return false;

	for (Bomb *bomb : current_bombs) {
		if (tileCoordFromPosition(bomb->getPosition()) == target_tileCoord) {
			return true;
		}
	}
	return false;
}

bool GameScene::makeMove(Vec2 position, Player * player)
{
	// correct the detection deviation caused by the sprite size
	Size figSize = player->getContentSize();
	
	// check the top and the down side of the player respectively
	Vec2 targetPos_down(position.x,  position.y - figSize.height / 2);
	Vec2 targetPos_top = position;

	switch (player->get_x_movement()) {
	    case MOVE_SIGNAL_X::MOVE_LEFT:
		targetPos_down.x -= 1 * figSize.width / 3;
		targetPos_top.x -= 1 * figSize.width / 3;
		break;
	    case MOVE_SIGNAL_X::MOVE_RIGHT:
		targetPos_down.x += 1 * figSize.width / 3;
		targetPos_top.x += 1 * figSize.width / 3;
		break;
	}
	// if the target position is out of bound
	if (isOutOfMap(targetPos_down) || isOutOfMap(targetPos_top)) return false;
	// if the target does not collide
	if (collideWithBrick(targetPos_down) || collideWithBrick(targetPos_top)) return false;
	if (collideWithBubble(player->getPosition(), targetPos_top)) return false;

	player->setPosition(position);
    return true;
}

// This method convert the position into the tile coordinate.
Vec2 GameScene::tileCoordFromPosition(Vec2 position)
{
	int x = position.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - position.y) / map->getTileSize().height;
	return Vec2(x, y);
}

void GameScene::game_over()
{
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.6f, GameOverScene::createScene()));
}

void GameScene::menuCallBack(Ref *pSender)
{
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.6f, HelloWorld::createScene()));
}

