/* File: RuleScene2.cpp
 * --------------------
 * This file contains the implementation of a class
 * called RuleScene2 which displays a scene with instruction
 * manual of this game. Including the introduction
 * of items which can improve the ability of the player.
 */
#include "RulesScene2.h"
#include "RulesScene.h"

USING_NS_CC;

Scene * RulesScene2::createScene() {
    return RulesScene2::create();
}
bool RulesScene2::init() {

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
            menu_selector(RulesScene2::menuPopBack));
    float x = origin.x + visibleSize.width - backItem->getContentSize().width;
    float y = origin.y + visibleSize.height - backItem->getContentSize().height;
    backItem->setPosition(Vec2(x, y));

    /* prev_rule_item: Click item for returning to the previous scene */
    auto prev_rule_item = MenuItemImage::create(
            "prev.png",
            "prev_pressed.png",
            this,
            menu_selector(RulesScene2::menuPrevPage));
    float prev_page_x = origin.x + prev_rule_item->getContentSize().width / 2;
    float prev_page_y = origin.y + visibleSize.height / 2 - prev_rule_item->getContentSize().height / 2;
    prev_rule_item->setPosition(Vec2(prev_page_x, prev_page_y));

    /* Add these two sprites to menu    */
    auto menu = Menu::create(backItem, prev_rule_item, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /* Create the sprite for rule2  */
    auto rule2_layer = Layer::create();
    Sprite* rule2_sprite = Sprite::create("rule2.png");
    rule2_sprite->setPosition(Vec2(visibleSize.width / 2 + 10, visibleSize.height / 2));
    rule2_sprite->setScale(0.4);
    rule2_layer->addChild(rule2_sprite);
    this->addChild(rule2_layer);

    return true;
}
void RulesScene2::menuPopBack(Ref* pSender) {
    Director::getInstance()->popScene();
}
void RulesScene2::menuPrevPage(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(CCTransitionMoveInL::create(0.6f, RulesScene::createScene()));
}