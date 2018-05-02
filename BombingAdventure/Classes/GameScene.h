#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(GameScene);
};


#endif