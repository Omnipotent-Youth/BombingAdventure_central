/* File: RuleScene.cpp
 * -------------------
 * This file contains the implementation of a class
 * called RuleScene which displays a scene with instruction
 * manual of this game. Including how to control
 * the player sprite, and some basic introduction
 * of the enemy (stone monster).
 */
#include "RulesScene.h"

USING_NS_CC;

Scene * RulesScene::createScene() {
	return RulesScene::create();
}
bool RulesScene::init() {

	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /* backItem: Click item for returning to the home scene */
	auto backItem = MenuItemImage::create(
		"home.png",
		"home_pressed.png",
		this,
		menu_selector(RulesScene::menuPopBack));
	float x = origin.x + visibleSize.width - backItem->getContentSize().width;
	float y = origin.y + visibleSize.height - backItem->getContentSize().height;
	backItem->setPosition(Vec2(x, y));

    /* next_rule_item: Click item for going to the next scene */
	auto next_rule_item = MenuItemImage::create(
	        "next.png",
            "next_pressed.png",
            this,
            menu_selector(RulesScene::menuNextPage));
    float next_page_x = origin.x + visibleSize.width - next_rule_item->getContentSize().width / 2;
    float next_page_y = origin.y + visibleSize.height / 2 - next_rule_item->getContentSize().height / 2;
    next_rule_item->setPosition(Vec2(next_page_x, next_page_y));

    /* Add these two sprites to menu    */
	auto menu = Menu::create(backItem, next_rule_item, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/* Create the sprite for rule1  */
    auto rule1_layer = Layer::create();
    Sprite* rule1_sprite = Sprite::create("rule1.png");
    rule1_sprite->setPosition(Vec2(visibleSize.width / 2 + 10, visibleSize.height / 2));
    rule1_sprite->setScale(0.4);
    rule1_layer->addChild(rule1_sprite);
    this->addChild(rule1_layer);

	return true;

}
void RulesScene::menuPopBack(Ref* pSender) {
	Director::getInstance()->popScene();
}
void RulesScene::menuNextPage(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(CCTransitionMoveInR::create(0.6f, RulesScene2::createScene()));
}