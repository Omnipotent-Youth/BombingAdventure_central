#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "RulesScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	auto closeItem = MenuItemImage::create(
		"_CloseSelected.png",
		"_CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	auto startItem = MenuItemImage::create(
		"Start.png",
		"Start.png",
		CC_CALLBACK_1(HelloWorld::menuStartScene, this));

	auto rulesItem = MenuItemImage::create(
		"Rules.png",
		"Rules.png",
		CC_CALLBACK_1(HelloWorld::menuRulesScene, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/10;
        float y = origin.y + closeItem->getContentSize().height/10;
        closeItem->setPosition(Vec2(x,y));
		closeItem->setScale(0.1);
    }

	startItem->setPosition(Vec2(visibleSize.width / 2 + 24, 3 * visibleSize.height / 4));
	startItem->setScale(0.5);
	rulesItem->setPosition(Vec2(visibleSize.width / 2 + 15, visibleSize.height / 2));
	rulesItem->setScale(0.5);


    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, startItem, rulesItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Bombing Adventure", "fonts/Marker Felt.ttf", 42);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"

    auto sprite = Sprite::create("p1.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + 10, visibleSize.height / 5));
		sprite->setScale(0.2);
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::menuStartScene(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(CCTransitionMoveInR::create(0.4f, GameScene::createScene()));
}

void HelloWorld::menuRulesScene(cocos2d::Ref * pSender)
{
	Director::getInstance()->pushScene(RulesScene::createScene());
}
