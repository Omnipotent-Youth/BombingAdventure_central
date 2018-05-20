#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

	// initializer
    virtual bool init();
    
    // selector callback functions
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartScene(cocos2d::Ref* pSender);
	void menuRulesScene(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
