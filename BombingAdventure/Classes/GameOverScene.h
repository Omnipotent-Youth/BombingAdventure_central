#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void menuCallBack(cocos2d::Ref* pSender);

	CREATE_FUNC(GameOverScene);
};

#endif //_GAME_OVER_SCENE_H_
