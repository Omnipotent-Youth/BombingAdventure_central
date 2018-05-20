#include "GameOverScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

cocos2d::Scene * GameOverScene::createScene()
{
	return GameOverScene::create();
}

bool GameOverScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemImage * game_over_item = MenuItemImage::create(
		"game_over.png",
		"game_over.png",
		CC_CALLBACK_1(GameOverScene::menuCallBack, this));
	game_over_item->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	auto menu = Menu::create(game_over_item, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void GameOverScene::menuCallBack(Ref * pSender)
{
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.6f, HelloWorld::createScene()));
}
