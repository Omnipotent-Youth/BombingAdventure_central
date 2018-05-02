#include "RulesScene.h"

USING_NS_CC;


Scene * RulesScene::createScene()
{
	return RulesScene::create();
}

bool RulesScene::init() {
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backItem = MenuItemImage::create(
		"_CloseSelected.png",
		"_CloseSelected.png",
		this,
		menu_selector(RulesScene::menuPopBack));
	float x = origin.x + visibleSize.width - backItem->getContentSize().width / 10;
	float y = origin.y + visibleSize.height- backItem->getContentSize().height / 10;
	backItem->setPosition(Vec2(x, y));
	backItem->setScale(0.1);

	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	Sprite* sprite1 = Sprite::create("rule.png");
	sprite1->setPosition(Vec2(visibleSize.width / 2 + 10, visibleSize.height / 2));
	sprite1->setScale(0.4);
	this->addChild(sprite1);

	return true;

}

void RulesScene::menuPopBack(Ref* pSender) {
	Director::getInstance()->popScene();
}