#include "GameOverScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

cocos2d::Scene * GameOverScene::createScene()
{
	return GameOverScene::create();
}

/* initializer */
bool GameOverScene::init()
{
	/* super initialize */
	if (!Scene::init()) {
		return false;
	}
	// get visible size
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// create a menu item
	MenuItemImage * game_over_item = MenuItemImage::create(
		"game_over.png",
		"game_over.png",
		CC_CALLBACK_1(GameOverScene::menuCallBack, this));
	// set the position of the menu item
	game_over_item->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// create a menu with the menu item
	auto menu = Menu::create(game_over_item, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

/*
 * Function: menu call back
 * ------------------------
 * Click the menu, then the game will return to the main menu scene.
 */
void GameOverScene::menuCallBack(Ref * pSender)
{
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.6f, HelloWorld::createScene()));
}
