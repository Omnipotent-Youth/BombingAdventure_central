#include "GameScene.h"

USING_NS_CC;


Scene * GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"_CloseSelected.png",
		"_CloseSelected.png",
		this,
		menu_selector(GameScene::menuCloseCallback));
	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 10;
	float y = origin.y + visibleSize.height - closeItem->getContentSize().height / 10;
	closeItem->setPosition(Vec2(x, y));
	closeItem->setScale(0.1);

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	Sprite* sprite1 = Sprite::create("p1.png");
	sprite1->setPosition(Vec2(visibleSize.width / 2 + 10, visibleSize.height / 2));
	sprite1->setScale(0.3);
	this->addChild(sprite1);

	return true;

}


void GameScene::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
}