#include "GameScene.h"

using namespace std;
USING_NS_CC;


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
	return true;

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